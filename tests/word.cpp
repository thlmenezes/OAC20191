#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "../headers/word.hpp"

TEST_CASE( "Extend signal: should sign extend to 4 bytes [...]", "[ext]" ) {
    SECTION("with positive numbers having preceding zeros"){
        REQUIRE( ( extend_signal(0x1,8)   == extend_signal(0x1,16) == 0x1 ) );
    }
    SECTION("and negative numbers having preceding ones"){
        REQUIRE(   extend_signal(0xff,8)  == -1   );
    }
}

TEST_CASE( "Get field: should be able to extract bytes from word [...]", "[get]" ) {
    int32_t  word = 0x01020304;
    uint32_t mask = 0xff;
    SECTION("using multiple index values"){
        REQUIRE( get_field(word, 0,mask) == 0x04 );
        REQUIRE( get_field(word, 8,mask) == 0x03 );
        REQUIRE( get_field(word,16,mask) == 0x02 );
        REQUIRE( get_field(word,24,mask) == 0x01 );
    }
    SECTION("using any index values"){
        // note: weird behaviour with index' greater than 31
        auto i = GENERATE(range(0,32));
        REQUIRE( get_field(word, i, 0x1) == (word >> i & 1) );
    } 
    SECTION("index is unsigned, and unsigned not equal |index|"){
        REQUIRE( get_field(word,8,mask) != get_field(word,-8,mask) );
    }
}

TEST_CASE( "Set Field: should exchange the value from a field", "[set]" ) {
    int32_t  word = 0x0;
    SECTION("using any index values"){
        // note: weird behaviour with index' greater than 31
        auto i = GENERATE(range(0,32));
        REQUIRE( (set_field(word, i, 0x1, 1) >> i & 1) );
    } 
}