/**
 * id      17/0045919
 * author  Thales Menezes
 * GitHub  @thaleslim
 * date    01/05/2019
 * brief   Define access and update
 * procedures to a simulated random
 * access memory.
 */

#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include <stdio.h>
#include <stdint.h>
#include "word.hpp"
#include "control.hpp"

inline uint32_t get_address(uint32_t address, int32_t kte);
// Loads
inline int32_t  lw (uint32_t address, int32_t kte);
inline int32_t  lh (uint32_t address, int32_t kte);
inline int32_t  lhu(uint32_t address, int32_t kte);
inline int32_t  lb (uint32_t address, int32_t kte);
inline int32_t  lbu(uint32_t address, int32_t kte);
// Stores
inline void     sw (uint32_t address, int32_t kte, int32_t dado);
inline void     sh (uint32_t address, int32_t kte, int16_t dado);
inline void     sb (uint32_t address, int32_t kte, int8_t dado);
// Showcase
void   dump_mem (uint32_t start, uint32_t end, char format = 'h');
//TODO: dump_mem return string
//TODO: loads -> kte = 0 / stores -> dado, address, kte = 0
//--------------------------------------------------------------
inline uint32_t get_address(uint32_t address, int32_t kte){
    /**
     * Calculate a memory index ( mem[idx] ) from \a{address}
     * note: equivalent return floor( (address + kte) / 4 ); 
     */
    return ( address + kte ) >> 2;
}//End get_address()

// Loads
//--------------------------------------------------------------
inline int32_t  lw (uint32_t address, int32_t kte){
    /**
     * Extract a word from memory
     * exceptions: if ( address % 4 != 0 ) throw Not Alligned
     * TODO:
     *   Error in <file> line 7: \
     *   Runtime exception at 0x00000008: \
     *   Load address not aligned to word boundary 0x00002002
     */
    if( (address + kte) & 0x3 )
        throw "Load address not aligned to word boundary";
    return mem[get_address(address,kte)];
}//End lw()

//--------------------------------------------------------------
inline int32_t  lh (uint32_t address, int32_t kte){
    /**
     * Sign-extended load half-word 
     */
    return extend_signal(lhu(address,kte),16);
}//End lh()

//--------------------------------------------------------------
inline int32_t  lhu(uint32_t address, int32_t kte){
    /**
     * Load unsigned half-word from memory
     * exceptions: if ( address % 2 != 0 ) throw Not Alligned
     */
    if ( (address + kte) & 0x1 )
        throw "Load address not aligned on halfword boundary ";
    return get_field( mem[get_address(address,kte)], ( (address + kte) & 0x3 ) << 3, 0xffff);
}//End lhu()

//--------------------------------------------------------------
inline int32_t  lb (uint32_t address, int32_t kte){
    /**
     * Sign-extended load byte 
     */
    return extend_signal(lbu(address,kte),8);
}//End lb()

//--------------------------------------------------------------
inline int32_t  lbu(uint32_t address, int32_t kte){
    /**
     * Load unsigned byte from memory
     */
    return get_field( mem[get_address(address,kte)], ( (address + kte) & 0x3 ) << 3, 0xff);
}//End lbu()

// Stores
//--------------------------------------------------------------
inline void sw(uint32_t address, int32_t kte, int32_t dado){
    /**
     * Write a word in memory
     */
    if( (address + kte) & 0x3 )
        throw "Load address not aligned to word boundary";
    mem[get_address(address,kte)] = dado;
}//End sw()

//--------------------------------------------------------------
inline void sh(uint32_t address, int32_t kte, int16_t dado){
    /**
     * Write a half-word in memory
     * note: (address + kte) % 4 * 8 -> upper(1) or lower(0) half-word
     */
    if ( (address + kte) & 0x1 )
        throw "Load address not aligned on halfword boundary ";
    mem[get_address(address,kte)] = set_field(mem[get_address(address,kte)], ( (address + kte) & 0x3 ) << 3, 0xffff, dado);
}//End sh()

//--------------------------------------------------------------
inline void sb(uint32_t address, int32_t kte, int8_t dado){
    /**
     * Write a byte in memory
     * note: (address + kte) % 4 * 8 -> byte index inside word [0,8,16,24]
     * note: (address + kte) % 4 == (address + kte) & 0x3, because selects
     * the first 2 bits from the word (0b11 = 0x3)
     */
    mem[get_address(address,kte)] = set_field(mem[get_address(address,kte)], ( (address + kte) & 0x3 ) << 3, 0xff, dado);
}//End sb()

// Showcase
//--------------------------------------------------------------
void   dump_mem (uint32_t start, uint32_t end, char format) {
    /**
     * Print content from mem[\a{start}] to mem[\a{end}] as hex or dec
     */
    int32_t konstante = 0;
    while( start + konstante <= end ){
        if( format == 'h' )
            printf("mem[ 0x%08x ] = 0x%08x\n", start + konstante, lw(start,konstante));
        else
            printf("mem[ 0x%08x ] = %8d\n", start + konstante, lw(start,konstante));
        konstante += 4;
    }
}//End dump_mem()

#endif