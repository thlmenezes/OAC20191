/**
 * id      17/0045919
 * author  Thales Menezes
 * GitHub  @thaleslim
 */
#include "../headers/decode.hpp"
#include "../headers/memory.hpp"
#include "../headers/word.hpp"
#include "../headers/execute.hpp"
#include <stdio.h>
#include <stdint.h>

#define print printf

bool load_file(FILE* bin_file, uint32_t begin, uint32_t max);
bool load_text(FILE* bin_text, uint32_t begin = 0x0);
bool load_data(FILE* bin_data, uint32_t begin = 0x2000);

int main(){
    FILE * file;
    file = fopen("text.bin","rb");
    load_text(file);
    fclose(file);
    dump_mem(0,0x54);
    print("\n\n");
    file = fopen("data.bin","rb");
    load_data(file);
    dump_mem(0x2000,0x204c);
    
    run();
    
}

bool load_file(FILE* bin_file, uint32_t begin, uint32_t max){
    if( bin_file == NULL )
        return false;
    
    long fStart = ftell(bin_file), fSize;
    
    fseek (bin_file, 0 , SEEK_END);

    fSize  = ftell(bin_file) - fStart;
    
    fseek (bin_file, -1*fSize, SEEK_CUR);

    if( fSize & 0x3 || fSize > max )
        return false;

    int32_t instruction = 0x0;
    int32_t konstant = begin;

    while( fread(&instruction,4,1,bin_file) ){
        sw(konstant,0,instruction);
        konstant += 4;
    }

    return true;
}

bool load_text(FILE* bin_text, uint32_t begin){
    return load_file(bin_text, begin, 0xffc);
}

bool load_data(FILE* bin_data, uint32_t begin){
    return load_file(bin_data, begin, 0x2fff);
}
