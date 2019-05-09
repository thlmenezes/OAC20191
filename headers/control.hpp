/**
 * id      17/0045919
 * author  Thales Menezes
 * GitHub  @thaleslim
 * date    03/05/2019
 * brief   Define simulated primary memories:
 * registers (integers, floats and controlers),
 * 4096 4bytes array as Random Access Memory and
 * fetch() procedure, helper in code simulation.
 */
#ifndef __CONTROL_HPP__
#define __CONTROL_HPP__

#include <stdint.h>
#include <stdio.h>

// Compact memory default
uint32_t pc = 0x00000000,
         ri = 0x00000000,
         sp = 0x00003ffc,
         gp = 0x00001800;

// Registers
int32_t reg[32];
// float  freg[32]; TODO: extra

static void dump_breg(char format = 'h'){
    int32_t konstante = 0;
    while( konstante < 32 ){
        if( format == 'h' )
            printf("reg[ x%2d ] = 0x%08x\n", konstante, reg[konstante]);
        else
            printf("reg[ x%2d ] = %8d\n", konstante, reg[konstante]);
        konstante++;
    }
}

void dump_reg(char format = 'h'){
    if(format == 'h'){
        printf("pc:\t0x%08x\n", pc);
        printf("ri:\t0x%08x\n", ri);
        printf("sp:\t0x%08x\n", sp);
        printf("gp:\t0x%08x\n", gp);
    }
    else{
        printf("pc:\t%8d\n", pc);
        printf("ri:\t%8d\n", ri);
        printf("sp:\t%8d\n", sp);
        printf("gp:\t%8d\n", gp);
    }
    dump_breg(format);
}

// Random Access Memory
#define MEM_SIZE 4096
int32_t mem[MEM_SIZE];

inline void fetch(){
    ri = mem[pc >> 2];
    pc += 4;
}

#endif