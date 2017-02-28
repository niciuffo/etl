//=======================================================================
// Copyright (c) 2014-2017 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#include "test_light.hpp"
#include "catch_complex_approx.hpp"
#include "scalar_test.hpp"

SCALAR_ADD_TEST_CASE("scalar/add/0", "[scalar]") {
    etl::fast_matrix<T, 8> c{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

    Impl::apply(c, 1.0);

    REQUIRE_EQUALS(c(0), T(2.0));
    REQUIRE_EQUALS(c(1), T(3.0));
    REQUIRE_EQUALS(c(2), T(4.0));
    REQUIRE_EQUALS(c(3), T(5.0));
    REQUIRE_EQUALS(c(4), T(6.0));
    REQUIRE_EQUALS(c(5), T(7.0));
    REQUIRE_EQUALS(c(6), T(8.0));
    REQUIRE_EQUALS(c(7), T(9.0));
}

SCALAR_ADD_TEST_CASE("scalar/add/1", "[scalar]") {
    etl::fast_matrix<T, 8> c{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

    Impl::apply(c, -1.0);

    REQUIRE_EQUALS(c(0), T(0.0));
    REQUIRE_EQUALS(c(1), T(1.0));
    REQUIRE_EQUALS(c(2), T(2.0));
    REQUIRE_EQUALS(c(3), T(3.0));
    REQUIRE_EQUALS(c(4), T(4.0));
    REQUIRE_EQUALS(c(5), T(5.0));
    REQUIRE_EQUALS(c(6), T(6.0));
    REQUIRE_EQUALS(c(7), T(7.0));
}

SCALAR_SUB_TEST_CASE("scalar/sub/0", "[scalar]") {
    etl::fast_matrix<T, 8> c{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

    Impl::apply(c, 1.0);

    REQUIRE_EQUALS(c(0), T(0.0));
    REQUIRE_EQUALS(c(1), T(1.0));
    REQUIRE_EQUALS(c(2), T(2.0));
    REQUIRE_EQUALS(c(3), T(3.0));
    REQUIRE_EQUALS(c(4), T(4.0));
    REQUIRE_EQUALS(c(5), T(5.0));
    REQUIRE_EQUALS(c(6), T(6.0));
    REQUIRE_EQUALS(c(7), T(7.0));
}

SCALAR_SUB_TEST_CASE("scalar/sub/1", "[scalar]") {
    etl::fast_matrix<T, 8> c{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

    Impl::apply(c, -1.0);

    REQUIRE_EQUALS(c(0), T(2.0));
    REQUIRE_EQUALS(c(1), T(3.0));
    REQUIRE_EQUALS(c(2), T(4.0));
    REQUIRE_EQUALS(c(3), T(5.0));
    REQUIRE_EQUALS(c(4), T(6.0));
    REQUIRE_EQUALS(c(5), T(7.0));
    REQUIRE_EQUALS(c(6), T(8.0));
    REQUIRE_EQUALS(c(7), T(9.0));
}

SCALAR_MUL_TEST_CASE("scalar/mul/0", "[scalar]") {
    etl::fast_matrix<T, 8> c{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

    Impl::apply(c, 2.0);

    REQUIRE_EQUALS(c(0), T(2.0));
    REQUIRE_EQUALS(c(1), T(4.0));
    REQUIRE_EQUALS(c(2), T(6.0));
    REQUIRE_EQUALS(c(3), T(8.0));
    REQUIRE_EQUALS(c(4), T(10.0));
    REQUIRE_EQUALS(c(5), T(12.0));
    REQUIRE_EQUALS(c(6), T(14.0));
    REQUIRE_EQUALS(c(7), T(16.0));
}

SCALAR_DIV_TEST_CASE("scalar/div/0", "[scalar]") {
    etl::fast_matrix<T, 8> c{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

    Impl::apply(c, 0.5);

    REQUIRE_EQUALS(c(0), T(2.0));
    REQUIRE_EQUALS(c(1), T(4.0));
    REQUIRE_EQUALS(c(2), T(6.0));
    REQUIRE_EQUALS(c(3), T(8.0));
    REQUIRE_EQUALS(c(4), T(10.0));
    REQUIRE_EQUALS(c(5), T(12.0));
    REQUIRE_EQUALS(c(6), T(14.0));
    REQUIRE_EQUALS(c(7), T(16.0));
}