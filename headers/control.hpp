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
// TODO: 3
#ifndef __CONTROL_HPP__
#define __CONTROL_HPP__

#include <stdint.h>

// Compact memory default
uint32_t pc = 0x00000000,
         ri = 0x00000000,
         sp = 0x00003ffc,
         gp = 0x00001800;

// Registers
int32_t reg[32];
float  freg[32];

// Random Access Memory
#define MEM_SIZE 4096
int32_t mem[MEM_SIZE];

inline void fetch(){
    ri = mem[pc];
    pc += 4;
}

#endif