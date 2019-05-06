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
    // TODO: ECALL exit??
    switch(opcode){
        case 
    }
}

void step(){
    fetch();
    decode();
    execute();
}

void run(){
    while(pc < 0xffd){
        step();
    }
}
#endif