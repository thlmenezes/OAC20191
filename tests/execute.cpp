#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "../headers/execute.hpp"

TEST_CASE( "Type U: should execute the decoded instruction", "[upper_imm]" ) {
    pc = 0x4;
    
    SECTION("LUI: Load Upper Immediate"){
        ri = 0xffffe37;     // lui x28, 0xffff
        decode();
        execute();
        REQUIRE( reg[rd] == imm20_u );
    }

    SECTION("AUIPC: Add Upper Immediate to PC"){
        ri = 0x2297;        // auipc x5, 0x2
        decode();
        execute();
        REQUIRE( reg[rd] == 0x2000 );
    }
}

TEST_CASE( "Type J: should execute the decoded instruction", "[jump]" ) {
    pc = 0x50;

    SECTION("JAL: Jump And Link"){
        ri = 0xfd9ff06f;    // jal x0, 0xffffffec
        decode();
        execute();
        REQUIRE( pc == 0x24 );
    }
}

TEST_CASE( "Type I: should execute the decoded instruction", "[imm]" ) {
        
    SECTION("JALR: Jump And Link Register"){
        pc = 0x74;
        reg[1] = 0;     // ra = 0
        ri = 0x8067;    // jalr x0, x1, 0x0
        decode();
        execute();
        REQUIRE( !pc );
    }

    SECTION("LB: Load Byte"){
        ri = 0x30283;    // lb x5, 0x0(x6)
        decode();
        execute();
        REQUIRE( reg[rd] == lb(reg[rs1],imm12_i) );
    }

    SECTION("LH: Load Half Word"){
        ri = 0x31283;    // lh x5, 0x0(x6)
        decode();
        execute();
        REQUIRE( reg[rd] == lh(reg[rs1],imm12_i) );
    }

    SECTION("LW: Load Word"){
        ri = 0x32283;    // lw x5, 0x0(x6)
        decode();
        execute();
        REQUIRE( reg[rd] == lw(reg[rs1],imm12_i) );
    }

    SECTION("LBU: Load Byte, Unsigned"){
        ri = 0x34283;    // lbu x5, 0x0(x6)
        decode();
        execute();
        REQUIRE( reg[rd] == lbu(reg[rs1],imm12_i) );
    }

    SECTION("LHU: Load Half Word, Unsigned"){
        ri = 0x35283;    // lhu x5, 0x0(x6)
        decode();
        execute();
        REQUIRE( reg[rd] == lhu(reg[rs1],imm12_i) );
    }

    SECTION("ADDI: Add Immediate"){
        ri = 0x28293;       // addi x5, x5, 0x0
        decode();
        execute();
        REQUIRE( reg[rd] == reg[rs1] + imm12_i );
    }

    SECTION("SLTI: Set if Less Than Immediate"){
        ri = 0xfff2ae93;    // slti x29, x5, -1
        decode();
        execute();
        REQUIRE( reg[rd] == reg[rs1] < imm12_i );
    }

    SECTION("SLTIU: Set if Less Than Immediate, Unsigned"){
        ri = 0xfff2bf13;    // sltiu x30, x5, -1
        decode();
        execute();
        REQUIRE( reg[rd] == uint32_t(reg[rs1]) < uint32_t(imm12_i) );
    }

    SECTION("XORI: Exclusive-OR Immediate"){
        ri = 0x592c413;     // xori x8, x5, 0x59
        decode();
        execute();
        REQUIRE( (reg[rd] == reg[rs1] ^ imm12_i) );
    }

    SECTION("ORI: OR Immediate"){
        ri = 0x262e493;     // ori x9, x5, 0x26
        decode();
        execute();
        REQUIRE( (reg[rd] == reg[rs1] | imm12_i) );
    }

    SECTION("ANDI: AND Immediate"){
        ri = 0x312ff93;     // andi x31, x5, 0x31
        decode();
        execute();
        REQUIRE( (reg[rd] == reg[rs1] & imm12_i) );
    }
    
    SECTION("SLLI: Shift Left Logical Immediate"){
        ri = 0x249293;      // slli x5, x9, 0x2
        decode();
        execute();
        REQUIRE( reg[rd] == reg[rs1] << shamt );
    }

    // SECTION("SRLI: Shift Right Logical Immediate"){}

    SECTION("SRAI: Shift Right Arithmetic Immediate"){
        ri = 0x4022de93;    // srai x29, x5, 0x2
        decode();
        execute();
        REQUIRE( reg[rd] == reg[rs1] >> shamt );
    }
    
}

TEST_CASE( "Type R: should execute the decoded instruction", "[reg]" ) {
    
    SECTION("ADD: Add"){
        ri = 0x13282b3;     // add x5, x5, x19
        decode();
        execute();
        REQUIRE( reg[rd] == reg[rs1] + reg[rs2] );
    }

    SECTION("SLT: Set if Less Than"){
        ri = 0x1c322b3;    // slt x5, x6, x28
        decode();
        execute();
        REQUIRE( reg[rd] == reg[rs1] < reg[rs2] );
    }

    SECTION("SLTU: Set if Less Than, Unsigned"){
        ri = 0x1c332b3;    // sltu x5, x6, x28
        decode();
        execute();
        REQUIRE( reg[rd] == uint32_t(reg[rs1]) < uint32_t(reg[rs2]) );
    }

    SECTION("XOR: Exclusive-OR"){
        ri = 0x72c433;     // xor x8, x5, x7
        decode();
        execute();
        REQUIRE( (reg[rd] == reg[rs1] ^ reg[rs2]) );
    }

    SECTION("OR: OR"){
        ri = 0x72e4b3;     // or x9, x5, x7
        decode();
        execute();
        REQUIRE( (reg[rd] == reg[rs1] | reg[rs2]) );
    }

    SECTION("AND: AND"){
        ri =  0x72ffb3;    // and x31, x5, x7
        decode();
        execute();
        REQUIRE( (reg[rd] == (reg[rs1] & reg[rs2])) );
    }
    
    SECTION("SLL: Shift Left Logical"){
        ri = 0x7312b3;      // sll x5, x6, x7
        decode();
        execute();
        REQUIRE( reg[rd] == reg[rs1] << reg[rs2] );
    }

    // SECTION("SRL: Shift Right Logical"){}
    
    SECTION("SRAI: Shift Right Arithmetic Immediate"){
        ri = 0x407352b3;      // sra x5, x6, x7
        decode();
        execute();
        REQUIRE( reg[rd] == reg[rs1] >> reg[rs2] );
    }
}

TEST_CASE( "Type S: should execute the decoded instruction", "[store]" ) {
    
    SECTION("SB: Store Byte"){
        ri = 0x628223;      // sb x6, 0x4(x5)
        decode();
        execute();
        REQUIRE( lb(reg[rs1],imm12_s) == reg[rs2] );
    }

    SECTION("SH: Store Half Word"){
        ri = 0x629223;      // sh x6, 0x4(x5)
        decode();
        execute();
        REQUIRE( lh(reg[rs1],imm12_s) == reg[rs2] );
    }

    SECTION("SW: Store Word"){
        ri = 0x62a223;      // sw x6, 0x4(x5)
        decode();
        execute();
        REQUIRE( lw(reg[rs1],imm12_s) == reg[rs2] );
    }
}

TEST_CASE( "Type B: should execute the decoded instruction", "[branch]" ) {
    pc = 4;

    SECTION("BEQ: Branch if Equal"){
        ri = 0x2030663;     // beq x6, x0, 0x16
        decode();
        execute();
        if ( reg[6] == reg[0] )
            REQUIRE( pc == 44 );
    }

    SECTION("BNE: Branch if Not Equal"){
        reg[6] = 1;
        ri = 0x31863;      // bne x6, x0, 0x8
        decode();
        execute();
        while ( reg[6] != reg[0] ){
            REQUIRE( pc == 16 );
            reg[6]--;
        }
    }
    
    SECTION("BLT: Branch if Less Than"){
        reg[6] = -1;
        ri = 0x34863;      // blt x6, x0, 0x8
        decode();
        execute();
        while ( reg[6] < reg[0] ){
            REQUIRE( pc == 16 );
            reg[6]++;
        }
    }

    SECTION("BGE: Branch if Greater or Equal"){
        ri = 0x35863;      // bge x6, x0, 0x8
        decode();
        execute();
        while ( reg[6] >= reg[0] ){
            REQUIRE( pc == 16 );
            reg[6]--;
        }
    }

    SECTION("BLTU: Branch if Less Than, Unsigned"){
        reg[5] = 1;
        ri = 0x536863;      // bltu x6, x5, 0x8
        decode();
        execute();
        while ( uint32_t(reg[6]) < uint32_t(reg[5]) ){
            REQUIRE( pc == 16 );
            reg[5]--;
        }
    }

    SECTION("BGEU: Branch if Greater or Equal, Unsigned"){
        reg[6] = 1;
        ri = 0x37863;      // bgeu x6, x0, 0x8
        decode();
        execute();
        while ( reg[6] >= reg[0] ){
            REQUIRE( pc == 16 );
            reg[6]--;
        }
    }

}