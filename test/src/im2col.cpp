//=======================================================================
// Copyright (c) 2014-2015 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#include "test.hpp"

#include "conv_test.hpp"

//Note: The results of the tests have been validated with one of (octave/matlab/matlab)

TEMPLATE_TEST_CASE_2("im2col/im2col_1", "im2col", Z, double, float) {
    etl::dyn_matrix<Z> I(4, 4, etl::values(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
    etl::dyn_matrix<Z> C(4, 9);
    ;

    etl::im2col_direct(C, I, 2, 2);

    REQUIRE(C(0, 0) == 1);
    REQUIRE(C(1, 0) == 5);
    REQUIRE(C(2, 0) == 2);
    REQUIRE(C(3, 0) == 6);

    REQUIRE(C(0, 2) == 9);
    REQUIRE(C(1, 2) == 13);
    REQUIRE(C(2, 2) == 10);
    REQUIRE(C(3, 2) == 14);

    REQUIRE(C(0, 5) == 10);
    REQUIRE(C(1, 5) == 14);
    REQUIRE(C(2, 5) == 11);
    REQUIRE(C(3, 5) == 15);

    REQUIRE(C(0, 8) == 11);
    REQUIRE(C(1, 8) == 15);
    REQUIRE(C(2, 8) == 12);
    REQUIRE(C(3, 8) == 16);
}

TEMPLATE_TEST_CASE_2("im2col/im2col_2", "im2col", Z, double, float) {
    etl::dyn_matrix<Z> I(3, 3, etl::values(1, 2, 3, 4, 5, 6, 7, 8, 9));
    etl::dyn_matrix<Z> C(4, 4);
    ;

    etl::im2col_direct(C, I, 2, 2);

    REQUIRE(C(0, 0) == 1);
    REQUIRE(C(1, 0) == 4);
    REQUIRE(C(2, 0) == 2);
    REQUIRE(C(3, 0) == 5);

    REQUIRE(C(0, 1) == 4);
    REQUIRE(C(1, 1) == 7);
    REQUIRE(C(2, 1) == 5);
    REQUIRE(C(3, 1) == 8);

    REQUIRE(C(0, 2) == 2);
    REQUIRE(C(1, 2) == 5);
    REQUIRE(C(2, 2) == 3);
    REQUIRE(C(3, 2) == 6);

    REQUIRE(C(0, 3) == 5);
    REQUIRE(C(1, 3) == 8);
    REQUIRE(C(2, 3) == 6);
    REQUIRE(C(3, 3) == 9);
}

TEMPLATE_TEST_CASE_2("im2col/im2col_3", "im2col", Z, double, float) {
    etl::dyn_matrix<Z> I(3, 3, etl::values(1, 2, 3, 4, 5, 6, 7, 8, 9));
    etl::dyn_matrix<Z> C(2, 6);
    ;

    etl::im2col_direct(C, I, 2, 1);

    REQUIRE(C(0, 0) == 1);
    REQUIRE(C(1, 0) == 4);

    REQUIRE(C(0, 1) == 4);
    REQUIRE(C(1, 1) == 7);

    REQUIRE(C(0, 2) == 2);
    REQUIRE(C(1, 2) == 5);

    REQUIRE(C(0, 3) == 5);
    REQUIRE(C(1, 3) == 8);

    REQUIRE(C(0, 4) == 3);
    REQUIRE(C(1, 4) == 6);

    REQUIRE(C(0, 5) == 6);
    REQUIRE(C(1, 5) == 9);
}

TEMPLATE_TEST_CASE_2("im2col/im2col_4", "im2col", Z, double, float) {
    etl::dyn_matrix<Z> I(3, 3, etl::values(1, 2, 3, 4, 5, 6, 7, 8, 9));
    etl::dyn_matrix<Z> C(2, 6);
    ;

    etl::im2col_direct(C, I, 1, 2);

    REQUIRE(C(0, 0) == 1);
    REQUIRE(C(1, 0) == 2);

    REQUIRE(C(0, 1) == 4);
    REQUIRE(C(1, 1) == 5);

    REQUIRE(C(0, 2) == 7);
    REQUIRE(C(1, 2) == 8);

    REQUIRE(C(0, 3) == 2);
    REQUIRE(C(1, 3) == 3);

    REQUIRE(C(0, 4) == 5);
    REQUIRE(C(1, 4) == 6);

    REQUIRE(C(0, 5) == 8);
    REQUIRE(C(1, 5) == 9);
}
