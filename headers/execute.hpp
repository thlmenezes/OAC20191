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
#include "word.hpp"
#include "decode.hpp"
#include "control.hpp"

void execute(){
    switch(opcode){
        default:
            break;
    }
}

void step(){
    fetch();
    decode();
    execute();
}

void run(){
    // TODO: ecall exit && pc < 0xffd
    while(opcode != 10 && pc < 0xffd){
        step();
    }
}
#endif