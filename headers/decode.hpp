/**
 * id      17/0045919
 * author  Thales Menezes
 * GitHub  @thaleslim
 * date    03/05/2019
 * brief   Define RISC-V instruction
 * decoding procedures and resulting
 * fields.
 */
// TODO: 1
#ifndef __DECODE_HPP__
#define __DECODE_HPP__

#include <stdint.h>
#include "word.hpp"
#include "control.hpp"

uint8_t opcode, rs1, rs2, rd, shamt, funct3, funct7;
int32_t imm12_i, imm12_s, imm13, imm20_u, imm21;

// RISC-V ISA

void decode(){
    return;
}

#endif