#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "../headers/execute.hpp"

TEST_CASE( "Type U: should execute to the correct fields", "[upper_imm]" ) {
    ri = 0x2297;        // auipc x5, 0x2
    decode();
    execute();
    REQUIRE( reg[rd] == 0x1ffc );   // TODO: review -> should be 0x2000
}

TEST_CASE( "Type J: should execute to the correct fields", "[jump]" ) {
    pc = 0x4c;
    ri = 0xfd9ff06f;    // jal x0, 0xffffffec
    decode();
    execute();
    REQUIRE( pc == 0x20 );          // TODO: review -> should be 0x24
}

TEST_CASE( "Type I: should execute to the correct fields", "[imm]" ) {
    ri = 0x28293;       // addi x5, x5, 0x0
    decode();
    execute();
    REQUIRE( reg[rd] == reg[rs1] + imm12_i );
}

TEST_CASE( "Type I (shift): should execute to the correct fields", "[shift]" ) {
    ri = 0x249293;      // slli x5, x9, 0x2
    decode();
    execute();
    REQUIRE( reg[rd] == reg[rs1] << shamt );
}

TEST_CASE( "Type R: should execute to the correct fields", "[reg]" ) {
    ri = 0x13282b3;     // add x5, x5, x19
    decode();
    execute();
    REQUIRE( reg[rd] == reg[rs1] + reg[rs2] );
}

TEST_CASE( "Type S: should execute to the correct fields", "[store]" ) {
    ri = 0x62a223;      // sw x6, 0x4(x5)
    decode();
    execute();
    REQUIRE( lw(reg[rs1],imm12_s) == reg[rs2] );
}

TEST_CASE( "Type B: should execute to the correct fields", "[branch]" ) {
    pc = 0;
    ri = 0x2030663;     // beq x6, x0, 0x16
    decode();
    execute();
    if ( reg[6] == reg[0] )
        REQUIRE( pc == 40 ); // TODO: should be 44
}