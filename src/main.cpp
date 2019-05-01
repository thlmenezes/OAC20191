/**
 * Id:     17/0045919
 * Name:   Thales Menezes
 * GitHub: @thaleslim
 */
#include <stdio.h>
#include <stdint.h>

#define print printf
#define MEM_SIZE 4096

int32_t mem[MEM_SIZE];

void dump_mem(uint32_t addr, uint32_t wsize);

inline uint32_t get_address(uint32_t address, int32_t kte);
inline int32_t  extend_signal(int32_t word, uint32_t wsize);

inline int32_t  get_field(int32_t word, uint32_t index, uint32_t mask);
inline int32_t  lw (uint32_t address, int32_t kte);
inline int32_t  lh (uint32_t address, int32_t kte);
inline int32_t  lhu(uint32_t address, int32_t kte);
inline int32_t  lb (uint32_t address, int32_t kte);
inline int32_t  lbu(uint32_t address, int32_t kte);

inline int32_t  set_field(int32_t word, uint32_t index, uint32_t mask, int32_t value);
inline void sw(uint32_t address, int32_t kte, int32_t dado);
inline void sh(uint32_t address, int32_t kte, int16_t dado);
inline void sb(uint32_t address, int32_t kte, int8_t dado);

int main(){

    sb(0,0,0x04);
    sb(0,1,0x03);
    sb(0,2,0x02);
    sb(0,3,0x01);

    sb(4,0,0xff);
    sb(4,1,0xfe);
    sb(4,2,0xfd);
    sb(4,3,0xfc);

    sh(8,0,0xfff0);
    sh(8,2,0x8c);

    sw(12,0,0xff);
    sw(16,0,0xffff);
    sw(20,0,0xffffffff);
    sw(24,0,0x80000000);
    dump_mem(0,7);

    print("%02x %d\n", lb(0,0), lb(0,0));
    print("%02x %d\n", lb(0,1), lb(0,1));
    print("%02x %d\n", lb(0,2), lb(0,2));
    print("%02x %d\n", lb(0,3), lb(0,3));
    
    print("%02x %d\n", lb(4,0) & 0xff, lb(4,0));
    print("%02x %d\n", lb(4,1) & 0xff, lb(4,1));
    print("%02x %d\n", lb(4,2) & 0xff, lb(4,2));
    print("%02x %d\n", lb(4,3) & 0xff, lb(4,3));

    print("%d\n", lbu(4,0));
    print("%d\n", lbu(4,1));
    print("%d\n", lbu(4,2));
    print("%d\n", lbu(4,3));
        
    print("%04x %d\n", lh(8,0) & 0xffff, lh(8,0) & 0xffff);
    print("%04x %d\n", lh(8,2) & 0xffff, lh(8,2) & 0xffff);

    print("%04x %d\n", lhu(8,0) & 0xffff, lhu(8,0) & 0xffff);
    print("%04x %d\n", lhu(8,2) & 0xffff, lhu(8,2) & 0xffff);

    print("%08x %d\n", lw(12,0));
    print("%08x %d\n", lw(16,0));
    print("%08x %d\n", lw(20,0));

    return 0;
}

void dump_mem(uint32_t addr, uint32_t wsize) {
    /**
     * Print \a{wsize} word' as hex, beginning from \a{addr}
     */
    int32_t konstante = 0;
    while(wsize--){
        print("mem[%d] = 0x%08x\n", get_address(addr,konstante), lw(addr,konstante));
        konstante += 4;
    }
}

inline uint32_t get_address(uint32_t address, int32_t kte){
    /**
     * Calculate a memory index ( mem[idx] ) from \a{address}
     * @note: equivalent return floor( (address + kte) / 4 ); 
     */
    return ( address + kte ) >> 2;
}

inline int32_t  extend_signal(int32_t word, uint32_t wsize){
    /**
     * Signal extension method
     * if ( word < 0 )
     *      extend 1
     * else
     *      extend 0
     */
    return word >> (wsize-1) ? word | (-1 << wsize) : word;
}

inline int32_t  get_field(int32_t word, uint32_t index, uint32_t mask){
    /**
     * Isolate \a{mask} bytes from \a{word}, startin' from \a{index}
     */
    return word >> index & mask;
}

inline int32_t  lw (uint32_t address, int32_t kte){
    /**
     * Extract a word from memory
     * @exceptions: if ( address % 4 != 0 ) throw Not Alligned
     * @todo:
     *   Error in <file> line 7: \
     *   Runtime exception at 0x00000008: \
     *   Load address not aligned to word boundary 0x00002002
     */
    if( address + kte & 0x3 )
        throw "Load address not aligned to word boundary";
    return mem[get_address(address,kte)];
}

inline int32_t  lh (uint32_t address, int32_t kte){
    /**
     * Sign-extended load half-word 
     */
    return extend_signal(lhu(address,kte),16);
}

inline int32_t  lhu(uint32_t address, int32_t kte){
    /**
     * Load half-word from memory
     * @exceptions: if ( address % 2 != 0 ) throw Not Alligned
     */
    if ( address + kte & 0x1 )
        throw "Load address not aligned on halfword boundary ";
    return get_field( mem[get_address(address,kte)], ( (address + kte) & 0x3 ) << 3, 0xffff);
}

inline int32_t  lb (uint32_t address, int32_t kte){
    /**
     * Sign-extended load byte 
     */
    return extend_signal(lbu(address,kte),8);
}

inline int32_t  lbu(uint32_t address, int32_t kte){
    /**
     * Load byte from memory
     */
    return get_field( mem[get_address(address,kte)], ( (address + kte) & 0x3 ) << 3, 0xff);
}

inline int32_t  set_field(int32_t word, uint32_t index, uint32_t mask, int32_t value){
    /**
     * Inserts \a{mask} bytes from \a{value} to \a{word}, startin' from \a{index}
     */
    return (word & ~(mask << index)) | ((value & mask) << index);
}

inline void sw(uint32_t address, int32_t kte, int32_t dado){
    /**
     * Write a word in memory
     */
    if( address + kte & 0x3 )
        throw "Load address not aligned to word boundary";
    mem[get_address(address,kte)] = dado;
}

inline void sh(uint32_t address, int32_t kte, int16_t dado){
    /**
     * Write a half-word in memory
     * @note: (address + kte) % 4 * 8 -> upper(1) or lower(0) half-word
     */
    if ( address + kte & 0x1 )
        throw "Load address not aligned on halfword boundary ";
    mem[get_address(address,kte)] = set_field(mem[get_address(address,kte)], ( (address + kte) & 0x3 ) << 3, 0xffff, dado);
}

inline void sb(uint32_t address, int32_t kte, int8_t dado){
    /**
     * Write a byte in memory
     * @note: (address + kte) % 4 * 8 -> byte index inside word [0,8,16,24]
     * @note: (address + kte) % 4 == (address + kte) & 0x3, because selects
     * the first 2 bits from the word (0b11 = 0x3)
     */
    mem[get_address(address,kte)] = set_field(mem[get_address(address,kte)], ( (address + kte) & 0x3 ) << 3, 0xff, dado);
    // print("%d\n0x%08x\n", (address + kte) & 0x3 ,mem[get_address(address,kte)]);
}
