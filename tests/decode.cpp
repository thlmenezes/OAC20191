#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#endif
#include "catch.hpp"

#include "../headers/decode.hpp"

TEST_CASE( "Type U: should decode to the correct fields", "[upper_imm]" ) {
    ri = 0x2297;        // auipc x5, 0x2
    decode();
    REQUIRE( rd == 5 );
    REQUIRE( imm20_u == 0x2000 );
}

TEST_CASE( "Type J: should decode to the correct fields", "[jump]" ) {
    ri = 0xfd9ff06f;    // jal x0, 0xffffffec
    decode();
    REQUIRE( !rd );
    REQUIRE( imm21 == 0xffffffd8 );
}

TEST_CASE( "Type I: should decode to the correct fields", "[imm]" ) {
    ri = 0x28293;       // addi x5, x5, 0x0
    decode();
    REQUIRE( rd  == 5 );
    REQUIRE( rs1 == 5 );
    REQUIRE( !funct3 );
    REQUIRE( !imm12_i );
}

TEST_CASE( "Type I (shift): should decode to the correct fields", "[shift]" ) {
    ri = 0x249293;      // slli x5, x9, 0x2
    decode();
    REQUIRE( rd  == 5 );
    REQUIRE( funct3   );
    REQUIRE( rs1 == 9 );
    REQUIRE( shamt == 2 );
    REQUIRE( !funct7  );
}

TEST_CASE( "Type R: should decode to the correct fields", "[reg]" ) {
    ri = 0x13282b3;     // add x5, x5, x19
    decode();
    REQUIRE( rd  == 5 );
    REQUIRE( !funct3  );
    REQUIRE( rs1 == 5 );
    REQUIRE( rs2 == 19);
    REQUIRE( !funct7  );
}

TEST_CASE( "Type S: should decode to the correct fields", "[store]" ) {
    ri = 0x62a223;      // sw x6, 0x4(x5)
    decode();
    REQUIRE( imm12_s == 4 );
    REQUIRE( funct3  == 2 );
    REQUIRE( rs1 == 5 );
    REQUIRE( rs2 == 6 );
}

TEST_CASE( "Type B: should decode to the correct fields", "[branch]" ) {
    ri = 0x2030663;     // beq x6, x0, 0x16
    decode();
    REQUIRE( imm13   == 44 );
    REQUIRE( !funct3  );
    REQUIRE( rs1 == 6 );
    REQUIRE( rs2 == 0 );
}