#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "../headers/memory.hpp"

TEST_CASE( "Get address: should accept different address & immediate combinations", "[ga]" ) {
    REQUIRE( (get_address(0,6) ==
              get_address(1,5) ==
              get_address(2,4) ==
              get_address(3,3) ==
              get_address(4,2) ==
              get_address(5,1) ==
              get_address(6,0)) );
}

TEST_CASE( "Store byte: should modify only a byte", "[sb]" ) {
    sb(0,0,0x04);
    REQUIRE( mem[0] == 0x04 );
    sb(0,1,0x03);
    REQUIRE( mem[0] == 0x0304 );
    sb(0,2,0x02);
    REQUIRE( mem[0] == 0x020304 );
    sb(0,3,0x01);
    REQUIRE( mem[0] == 0x01020304 );
    mem[0] = 0x0; // memory clean
}

TEST_CASE( "Store half word: should modify only 2 bytes", "[sh]" ) {
    sh(0,0,0xfff0);
    REQUIRE( mem[0] == 0xfff0 );
    sh(0,2,0x8c);
    REQUIRE( mem[0] == 0x8cfff0 );
    mem[0] = 0x0; // memory clean
}

TEST_CASE( "Store word: should modify 4 bytes", "[sw]" ) {
    sw(0,0,-1);
    REQUIRE( mem[0] == -1 );
    mem[0] = 0x0; // memory clean
}

TEST_CASE( "Load byte unsigned: should read 1 byte", "[lbu]" ) {
    mem[0] = 0xff;
    REQUIRE( lbu(0,0) == 0xff );
    mem[0] = 0x0;  // memory clean
    REQUIRE( (!lbu(0,0) && !mem[0]) );
}

TEST_CASE( "Load byte: should read 1 byte sign extended ", "[lb]" ) {
    mem[0] = 0xff;
    REQUIRE( lb(0,0) == -1 );
    mem[0] = 0x0;  // memory clean
    REQUIRE( (!lb(0,0) && !mem[0]) );
}

TEST_CASE( "Load half word unsigned: should read 2 bytes", "[lhu]" ) {
    mem[0] = 0xffff;
    REQUIRE( lhu(0,0) == 0xffff );
    mem[0] = 0x0;  // memory clean
    REQUIRE( (!lhu(0,0) && !mem[0]) );
}

TEST_CASE( "Load half word: should read 2 bytes sign extend", "[lhu]" ) {
    mem[0] = 0xffff;
    REQUIRE( lh(0,0) == -1 );
    mem[0] = 0x0;  // memory clean
    REQUIRE( (!lh(0,0) && !mem[0]) );
}

TEST_CASE( "Load word: should read 4 bytes", "[lw]" ) {
    mem[0] = -1;
    REQUIRE( lw(0,0) == -1 );
    mem[0] = 0x0;  // memory clean
    REQUIRE( (!lw(0,0) && !mem[0]) );
}