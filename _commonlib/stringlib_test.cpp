#include <catch2/catch_test_macros.hpp>

#include "adventlib.hpp"

TEST_CASE( "trim", "[stringlib]" ) {
    REQUIRE( adventlib::trim(" hello    ") == "hello" );
    REQUIRE( adventlib::trim("hello") == "hello" );
    REQUIRE( adventlib::trim("    ") == "" );
}