#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "../headers/memory.hpp"

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

TEST_CASE( "Store byte: Should accept different addres & immediate combinations", "[sb]" ) {
    sb(4,2,0x1);
    REQUIRE( mem[1] == 0x10000 );
    sb(3,3,0x2);
    REQUIRE( mem[1] == 0x20000 );
    sb(2,4,0x3);
    REQUIRE( mem[1] == 0x30000 );
    sb(1,5,0x4);
    REQUIRE( mem[1] == 0x40000 );
    sb(0,6,0x5);
    REQUIRE( mem[1] == 0x50000 );
    sb(6,0,0x6);
    REQUIRE( mem[1] == 0x60000 );
    sb(5,1,0x7);
    REQUIRE( mem[1] == 0x70000 );
    mem[1] = 0x0; // memory clean
}

TEST_CASE( "Store half word: Should modify only 2 bytes", "[sh]" ) {
    sh(8,0,0xfff0);
    REQUIRE( mem[2] == 0xfff0 );
    sh(8,2,0x8c);
    REQUIRE( mem[2] == 0x8cfff0 );
    mem[2] = 0x0; // memory clean
}

TEST_CASE( "Store word: Should modify 4 bytes", "[sw]" ) {
    sw(12,0,0xffffffff);
    REQUIRE( mem[3] == 0xffffffff );
    mem[12] = 0x0; // memory clean
}

TEST_CASE( "Load word: Should read 4 bytes", "[lw]" ) {
    mem[0] = 0xff;
    REQUIRE( lw(0,0) == 0xff );
    mem[0] = 0x0;  // memory clean
}

/*
TEST_CASE( "Load byte: Should read 1 byte", "[lw]" ) {
    mem[0] = 0xff;
    REQUIRE( lw(0,0) == 0xff );
    mem[0] = 0x0;  // memory clean
}

TEST_CASE( "Load byte unsigned: Should read 1 byte", "[lw]" ) {
    mem[0] = 0xff;
    REQUIRE( lw(0,0) == 0xff );
    mem[0] = 0x0;  // memory clean
}

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
    print("%08x %d\n", lw(20,0));
//*/