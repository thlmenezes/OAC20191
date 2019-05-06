/**
 * id      17/0045919
 * author  Thales Menezes
 * GitHub  @thaleslim
 * date    03/05/2019
 * brief   Define instruction
 * simulation procedures.
 */
// TODO: 4
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
        case AUIPC:
            
            break;
        // type J
        case JAL:
            
            break;
        // Type I
        case JALR:
        case ECALL:
            ecall(reg[17]); // ecall a7
            break;
        case ILType:
        case ILAType:

            // shift related operations
            if (funct3 == SLLI3 || funct3 == SRI3) {
                // shamt   = get_field(ri,20,0x1f);
                (void) 0;
            } else 
                (void) 0;
            break;
        // Type R
        case RegType:

        // Type S&B
        case StoreType:
        case BType:
            if( opcode == StoreType)
                (void) 0;
            else if (opcode == BType)
                (void) 0;
            break;
    }
}

void step(){
    fetch();
    decode();
    execute();
}

void run(){
    while( !end_program && pc < 0xffd )
        step();
    
    printf("-- program is finished running ");
    
    if( !end_program )
        printf("(dropped off bottom) --");
    else
        printf("--");
}
#endif