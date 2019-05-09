/**
 * id      17/0045919
 * author  Thales Menezes
 * GitHub  @thaleslim
 * date    03/05/2019
 * brief   Define instruction
 * simulation procedures.
 */
#ifndef __EXECUTE_HPP__
#define __EXECUTE_HPP__

#include <stdint.h>
#include <stdio.h>
#include "word.hpp"
#include "memory.hpp"
#include "decode.hpp"
#include "control.hpp"

static bool end_program = false;

static void ecall(int32_t service){
    switch (service)
    {
        case 1:
            printf("%d", reg[10]);
            break;
        case 4:
            {int32_t start = reg[10];
            char charactere = lbu(start,0);
            while( charactere ){
                printf("%c", charactere);
                charactere = lbu(++start,0);
            }
            break;}
        case 10:
            end_program = true;
            break;
    }
}

void execute(){
    switch(opcode){
        // type U
        case LUI:
            reg[rd] = imm20_u;
            break;
        case AUIPC:
            reg[rd] = pc - 4 + imm20_u;
            break;
        // type J
        case JAL:
            reg[rd] = pc;
            pc = pc - 4 + imm21;
            break;
        // Type I
        case JALR:
            reg[rd] = pc;
            pc = (reg[rs1] + imm12_i) & ~1;
            break;
        case ECALL:
            ecall(reg[17]); // ecall a7
            break;
        case ILType:{
            int32_t (*load)(uint32_t,int32_t);
            switch (funct3)
            {
                case LB3:
                    load = &lb;
                    break;
                case LH3:
                    load = &lh;
                    break;
                case LW3:
                    load = &lw;
                    break;
                case LBU3:
                    load = &lbu;
                    break;
                case LHU3:
                    load = &lhu;
                    break;
            }
            reg[rd] = load(reg[rs1],imm12_i);
            break;
        }
        case ILAType:
            switch (funct3)
            {
                case ADDI3:
                    reg[rd] = reg[rs1] + imm12_i;
                    break;
                case SLTI3:
                    reg[rd] = reg[rs1] < imm12_i;
                    break;
                case SLTIU3:
                    reg[rd] = uint32_t(reg[rs1]) < uint32_t(imm12_i);
                    break;
                case XORI3:
                    reg[rd] = reg[rs1] ^ imm12_i;
                    break;
                case ORI3:
                    reg[rd] = reg[rs1] | imm12_i;
                    break;
                case ANDI3:
                    reg[rd] = reg[rs1] & imm12_i;
                    break;
                case SLLI3:
                    reg[rd] = reg[rs1] << shamt;
                    break;
                case SR3:
                    switch(funct7){
                        case SRLI7:{
                            int32_t mask = 0;
                            for(int i = 0; i < shamt; i++)
                                mask = (mask << 1) + 1; 
                            reg[rd] = reg[rs1] >> shamt & ~(mask << (32 - shamt));
                            break;
                        }
                        case SRAI7:
                            reg[rd] = reg[rs1] >> shamt;
                    }
                    break;
            }
            break;
        // Type R
        case RegType:
            switch (funct3)
            {
                case ADDSUB3:
                    if(funct7 == SUB7)
                        reg[rd] = reg[rs1] - reg[rs2];
                    else    
                        reg[rd] = reg[rs1] + reg[rs2];
                    break;
                case SLT3:
                    reg[rd] = reg[rs1] < reg[rs2];
                    break;
                case SLTU3:
                    reg[rd] = uint32_t(reg[rs1]) < uint32_t(reg[rs2]);
                    break;
                case XOR3:
                    reg[rd] = reg[rs1] ^ reg[rs2];
                    break;
                case OR3:
                    reg[rd] = reg[rs1] | reg[rs2];
                    break;
                case AND3:
                    reg[rd] = reg[rs1] & reg[rs2];
                    break;
                case SLL3:
                    reg[rd] = reg[rs1] << reg[rs2];
                    break;
                case SR3:
                    switch(funct7){
                        case SRL7:{
                            int32_t mask = 0;
                            for(int i = 0; i < reg[rs2]; i++)
                                mask = (mask << 1) + 1; 
                            reg[rd] = reg[rs1] >> reg[rs2] & ~(mask << (32 - reg[rs2]));
                            break;
                        }
                        case SRA7:
                            reg[rd] = reg[rs1] >> reg[rs2];
                    }
                    break;
            }
            break;
        // Type S&B
        case StoreType:
            switch (funct3){
                case SB3:
                    sb(reg[rs1],imm12_s,reg[rs2] & 0xff);
                    break;
                case SH3:
                    sh(reg[rs1],imm12_s,reg[rs2] & 0xffff);
                    break;
                case SW3:
                    sw(reg[rs1],imm12_s,reg[rs2]);
                    break;
            }
            break;
        case BType:
            switch (funct3){
                case BEQ3:
                    if (reg[rs1] == reg[rs2])
                        pc = pc - 4 + imm13;
                    break;
                case BNE3:
                    if (reg[rs1] != reg[rs2])
                        pc = pc - 4 + imm13;
                    break;
                case BLT3:
                    if (reg[rs1] < reg[rs2])
                        pc = pc - 4 + imm13;
                    break;
                case BGE3:
                    if (reg[rs1] >= reg[rs2])
                        pc = pc - 4 + imm13;
                    break;
                case BLTU3:
                    if (uint32_t(reg[rs1]) < uint32_t(reg[rs2]))
                        pc = pc - 4 + imm13;
                    break;
                case BGEU3:
                    if (uint32_t(reg[rs1]) >= uint32_t(reg[rs2]))
                        pc = pc - 4 + imm13;
                    break;                
            }
            break;
    }
    reg[0] = 0;
}

void step(){
    fetch();
    decode();
    execute();
}

void run(){
    //TODO: Move this initialize to another place 
    // sp = 0x3ffc; gp = 0x1800
    reg[2] = 0x3ffc; reg[3] = 0x1800;
    while( !end_program && pc < 0xffd )
        step();
    printf("\n-- program is finished running ");
    if( !end_program )
        printf("(dropped off bottom) --");
    else
        printf("--");
    printf("\n");
}
#endif