/**
 * id      17/0045919
 * author  Thales Menezes
 * GitHub  @thaleslim
 */
#include "../headers/decode.hpp"
#include "../headers/memory.hpp"
#include "../headers/word.hpp"
#include <stdio.h>
#include <stdint.h>

#define print printf
// TODO: 2
bool load_text(FILE* bin_text, uint32_t begin);
bool load_data(FILE* bin_data, uint32_t begin);

int main(){
    ri = 0x01c000ef;
    print("rd : 0x%08x\nfunct3 : 0x%08x\nrs1 :0x%08x\nimm12_i : 0x%08x\n", get_field(0x38393,7,0x1f), get_field(0x38393,12,0x7), get_field(0x38393,15,0x1f), get_field(0x38393,20,0xfff));
    /**
     * Ler e inserir na memória
     */
    /*
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
    print("%08x %d\n", lw(20,0)); //*/
    
    return 0;
}