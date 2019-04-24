#include <stdio.h>
#include <stdint.h>

#define MEM_SIZE 4096
#define print printf

int32_t mem[MEM_SIZE];

void dump_mem(uint32_t addr, uint32_t wsize);

int main(){
    print("0x%x", 256);
    return 0;
}

void dump_mem(uint32_t addr, uint32_t wsize) {
    /**
     * Print \a{wsize} word' content as hex,
     * beginning from \a{addr}
     */
    // int32_t konstante = 0;
    while(wsize--)
        print("0x%x", 0); // print
        // { print("0x%x", lw(addr,konstante)); konstante += 4; }
}

/* int32_t lw(uint32_t address, int32_t kte){
    // if address not alligned throw Exception
    return mem[] 
} */