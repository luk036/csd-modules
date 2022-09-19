/*
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>  // for ResultBuilder, CHECK_EQ, TEST_CASE

import csd;

TEST_CASE("test to_csd") {
    CHECK_EQ(csd::to_csd(28.5, 2), "+00-00.+0");
    CHECK_EQ(csd::to_csd(-0.5, 2), "0.-0");
}

TEST_CASE("test to_decimal") {
    CHECK_EQ(csd::to_decimal("+00-00.+"), 28.5);
    CHECK_EQ(csd::to_decimal("0.-"), -0.5);
}

TEST_CASE("test to_csdfixed") {
    CHECK_EQ(csd::to_csdfixed(28.5, 4), "+00-00.+");
    CHECK_EQ(csd::to_csdfixed(-0.5, 4), "0.-");
}

// Driver Code
TEST_CASE("test lcsre") { CHECK_EQ(csd::longest_repeated_substring("+-00+-00+-00+-0"), "+-00+-0"); }

*/ 

import <iostream>;
import csd;

int main() {
    std::cout << csd::to_csd(28.5, 2) << std::endl;
    std::cout << csd::to_decimal("+00-00.+0") << std::endl;
    return 0;
}
