/**
 * id      17/0045919
 * author  Thales Menezes
 * GitHub  @thaleslim
 * date    03/05/2019
 * brief   Define RISC-V instruction
 * decoding procedures and resulting
 * fields.
 */
#ifndef __DECODE_HPP__
#define __DECODE_HPP__

#include <stdint.h>
#include "word.hpp"
#include "control.hpp"

uint8_t opcode, rs1, rs2, rd, shamt, funct3, funct7;
int32_t imm12_i, imm12_s, imm13, imm20_u, imm21;

// RISC-V ISA
enum OPCODES { // lembrem que so sao considerados os 7 primeiros bits dessas constantes
    LUI = 0x37,   AUIPC = 0x17,         // atribui 20 bits mais significativos
    ILType = 0x03,                      // Load type
    BType = 0x63,                       // branch condicional
    JAL = 0x6F,   JALR = 0x67,          // jumps - JAL formato UJ, JALR formato I
    StoreType = 0x23,                   // store
    ILAType = 0x13,                     // logico-aritmeticas com imediato
    RegType = 0x33,                     // operacoes LA com registradores
    ECALL = 0x73                        // chamada do sistema - formato I
};

enum FUNCT3 { // campo auxiliar de 3 bits
    BEQ3=0, BNE3=01, BLT3=04, BGE3=05, BLTU3=0x06, BGEU3=07, // branches
    LB3=0, LH3=01, LW3=02, LBU3=04, LHU3=05,                 // loads
    SB3=0, SH3=01, SW3=02,                                   // stores
    ADDSUB3=0, SLL3=01, SLT3=02, SLTU3=03,                   // LA com
    XOR3=04, SR3=05, OR3=06, AND3=07,                        // registradores
    ADDI3=0, ORI3=06, SLTI3=02, XORI3=04, ANDI3=07,          // LA com
    SLTIU3=03, SLLI3=01, SRI3=05                             // imediatos
};

enum FUNCT7 {

    // campo auxiliar de 7 bits para as instrucoes SRLI/SRAI, ADD/SUB, SRL/SRA
    
    ADD7=0, SUB7=0x20, SRA7=0x20, SRL7=0, SRLI7=0x00, SRAI7=0x20
};

static void clear(){
    opcode = 0; rs1 = 0; rs2 = 0; rd = 0; shamt = 0; funct3 = 0; funct7 = 0;
    imm12_i = 0; imm12_s = 0; imm13 = 0; imm20_u = 0; imm21 = 0;
    return;
}

void decode(){
    /**
     * Split ri in different instruction possible fields
     */
    clear();
    opcode = get_field(ri,0,0x7f);
    switch(opcode){
        // type U
        case LUI:
        case AUIPC:
            rd      = get_field(ri,7,0x1f);
            imm20_u = extend_signal(get_field(ri,12,0xfffff) << 12 | 0x0, 20);
            break;
        // type J
        case JAL:
            rd      = get_field(ri,7,0x1f);
            imm21   = extend_signal(
                        get_field(ri,31,0x1)   << 20 | /* [20]*/
                        get_field(ri,12,0xff)  << 12 | /* [19:12]*/
                        get_field(ri,20,0x1)   << 11 | /* [11]*/
                        get_field(ri,21,0x3ff) << 1  | /* [10:1]*/
                        0x0, 21);
            break;
        // Type I
        case JALR:
        case ECALL:
        case ILType:
        case ILAType:
            rd      = get_field(ri,7,0x1f);
            funct3  = get_field(ri,12,0x7);
            rs1     = get_field(ri,15,0x1f);
            // shift related operations
            if (funct3 == SLLI3 || funct3 == SRI3) {
                shamt   = get_field(ri,20,0x1f);
                funct7  = get_field(ri,25,0x3f);
            } else 
                imm12_i = extend_signal(get_field(ri,20,0xfff), 12);
            break;
        // Type R
        case RegType:
            rd      = get_field(ri,7,0x1f);
            funct7  = get_field(ri,25,0x3f);
        // Type S&B
        case StoreType:
        case BType:
            if( opcode == StoreType)
                imm12_s = extend_signal(
                            get_field(ri,25,0x3f) << 5 | /* [11:5]*/
                            get_field(ri, 7,0x1f), 12);  /* [4:0]*/
            else if (opcode == BType)
                imm13 = extend_signal(
                            get_field(ri,31,0x1)  << 12 | /* [12]*/
                            get_field(ri, 7,0x1)  << 11 | /* [11]*/
                            get_field(ri,25,0x3f) << 5  | /* [10:5]*/
                            get_field(ri, 8,0x1f) << 1  | /* [4:1]*/
                            0x0,13);
            funct3  = get_field(ri,12,0x7);
            rs1     = get_field(ri,15,0x1f);
            rs2     = get_field(ri,20,0x1f);
            break;
    }
    return;
}

#endif