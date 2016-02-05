//=======================================================================
// Copyright (c) 2014-2016 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

/*!
 * \file
 * \brief Contains utility checks
 *
 * The functions are using assertions to validate their conditions. When
 * possible, static assertions are used.
 */

#pragma once

namespace etl {

/*!
 * \brief Make sure the two expressions have the same size
 *
 * This function uses assertion to validate the condition. If possible, the
 * assertion is done at compile time.
 *
 * \param lhs The left hand side expression
 * \param rhs The right hand side expression
 */
template <typename LE, typename RE, cpp_enable_if(etl_traits<LE>::is_generator || etl_traits<RE>::is_generator)>
void validate_expression_impl(const LE& lhs, const RE& rhs) noexcept {
    //Nothing to test, generators are of infinite size
    cpp_unused(lhs);
    cpp_unused(rhs);
}

/*!
 * \brief Make sure the two expressions have the same size
 *
 * This function uses assertion to validate the condition. If possible, the
 * assertion is done at compile time.
 *
 * \param lhs The left hand side expression
 * \param rhs The right hand side expression
 */
template <typename LE, typename RE, cpp_enable_if(!(etl_traits<LE>::is_generator || etl_traits<RE>::is_generator), all_etl_expr<LE, RE>::value, !all_fast<LE, RE>::value)>
void validate_expression_impl(const LE& lhs, const RE& rhs) {
    cpp_assert(size(lhs) == size(rhs), "Cannot perform element-wise operations on collections of different size");
    cpp_unused(lhs);
    cpp_unused(rhs);
}

/*!
 * \brief Make sure the two expressions have the same size
 *
 * This function uses assertion to validate the condition. If possible, the
 * assertion is done at compile time.
 *
 * \param lhs The left hand side expression
 * \param rhs The right hand side expression
 */
template <typename LE, typename RE, cpp_enable_if(!(etl_traits<LE>::is_generator || etl_traits<RE>::is_generator), all_etl_expr<LE, RE>::value, all_fast<LE, RE>::value)>
void validate_expression_impl(const LE& lhs, const RE& rhs) {
    static_assert(etl_traits<LE>::size() == etl_traits<RE>::size(), "Cannot perform element-wise operations on collections of different size");
    cpp_unused(lhs);
    cpp_unused(rhs);
}

#define validate_expression(lhs, rhs) \
    static_assert(is_etl_expr<decltype(lhs)>::value && is_etl_expr<decltype(rhs)>::value, "ETL functions are only made for ETL expressions "); \
    validate_expression_impl(lhs, rhs);

/*!
 * \brief Make sure that rhs can assigned to lhs.
 *
 * This function uses assertion to validate the condition. If possible, the
 * assertion is done at compile time.
 *
 * \param lhs The left hand side expression
 * \param rhs The right hand side expression
 */
template <typename LE, typename RE, cpp_enable_if(etl_traits<RE>::is_generator)>
void validate_assign(const LE& lhs, const RE& rhs) noexcept {
    static_assert(is_etl_expr<LE>::value, "Assign can only work on ETL expressions");
    //Nothing to test, generators are of infinite size
    cpp_unused(lhs);
    cpp_unused(rhs);
}

/*!
 * \brief Make sure that rhs can assigned to lhs.
 *
 * This function uses assertion to validate the condition. If possible, the
 * assertion is done at compile time.
 *
 * \param lhs The left hand side expression
 * \param rhs The right hand side expression
 */
template <typename LE, typename RE, cpp_enable_if(!etl_traits<RE>::is_generator, all_etl_expr<RE>::value, !all_fast<LE, RE>::value)>
void validate_assign(const LE& lhs, const RE& rhs) {
    static_assert(is_etl_expr<LE>::value, "Assign can only work on ETL expressions");
    cpp_assert(size(lhs) == size(rhs), "Cannot perform element-wise operations on collections of different size");
    cpp_unused(lhs);
    cpp_unused(rhs);
}

/*!
 * \brief Make sure that rhs can assigned to lhs.
 *
 * This function uses assertion to validate the condition. If possible, the
 * assertion is done at compile time.
 *
 * \param lhs The left hand side expression
 * \param rhs The right hand side expression
 */
template <typename LE, typename RE, cpp_enable_if(!etl_traits<RE>::is_generator, all_etl_expr<RE>::value, all_fast<LE, RE>::value)>
void validate_assign(const LE& lhs, const RE& rhs) {
    static_assert(is_etl_expr<LE>::value, "Assign can only work on ETL expressions");
    static_assert(etl_traits<LE>::size() == etl_traits<RE>::size(), "Cannot perform element-wise operations on collections of different size");
    cpp_unused(lhs);
    cpp_unused(rhs);
}

/*!
 * \brief Make sure that rhs can assigned to lhs.
 *
 * This function uses assertion to validate the condition. If possible, the
 * assertion is done at compile time.
 *
 * \param lhs The left hand side expression
 * \param rhs The right hand side expression
 */
template <typename LE, typename RE, cpp_enable_if(!all_etl_expr<RE>::value)>
void validate_assign(const LE& lhs, const RE& rhs) {
    static_assert(is_etl_expr<LE>::value, "Assign can only work on ETL expressions");
    cpp_assert(size(lhs) == size(rhs), "Cannot perform element-wise operations on collections of different size");
    cpp_unused(lhs);
    cpp_unused(rhs);
}

/*!
 * \brief Make sure that the expression is square
 *
 * This function uses assertion to validate the condition. If possible, the
 * assertion is done at compile time.
 *
 * \param expr The expression to assert
 */
template <typename E, cpp_enable_if(all_fast<E>::value)>
void assert_square(E&& expr){
    static_assert(decay_traits<E>::dimensions() == 2, "Function undefined for non-square matrix");
    static_assert(decay_traits<E>::template dim<0>() == decay_traits<E>::template dim<1>(), "Function undefined for non-square matrix");
    cpp_unused(expr);
}

/*!
 * \brief Make sure that the expression is square
 *
 * This function uses assertion to validate the condition. If possible, the
 * assertion is done at compile time.
 *
 * \param expr The expression to assert
 */
template <typename E, cpp_disable_if(all_fast<E>::value)>
void assert_square(E&& expr){
    static_assert(decay_traits<E>::dimensions() == 2, "Function undefined for non-square matrix");
    cpp_assert(etl::dim<0>(expr) == etl::dim<1>(expr), "Function undefined for non-square matrix");
    cpp_unused(expr);
}

namespace detail {

template <std::size_t C1, std::size_t C2, typename E, cpp_enable_if(etl_traits<E>::dimensions() == 2, !etl_traits<E>::is_fast)>
void validate_pmax_pooling_impl(const E& e) {
    cpp_assert(etl::template dim<0>(e) % C1 == 0 && etl::template dim<1>(e) % C2 == 0, "Dimensions not divisible by the pooling ratio");
    cpp_unused(e);
}

template <std::size_t C1, std::size_t C2, typename E, cpp_enable_if(etl_traits<E>::dimensions() == 3, !etl_traits<E>::is_fast)>
void validate_pmax_pooling_impl(const E& e) {
    cpp_assert(etl::template dim<1>(e) % C1 == 0 && etl::template dim<2>(e) % C2 == 0, "Dimensions not divisible by the pooling ratio");
    cpp_unused(e);
}

template <std::size_t C1, std::size_t C2, typename E, cpp_enable_if(etl_traits<E>::dimensions() == 2, etl_traits<E>::is_fast)>
void validate_pmax_pooling_impl(const E& /*unused*/) {
    static_assert(etl_traits<E>::template dim<0>() % C1 == 0 && etl_traits<E>::template dim<1>() % C2 == 0, "Dimensions not divisible by the pooling ratio");
}

template <std::size_t C1, std::size_t C2, typename E, cpp_enable_if(etl_traits<E>::dimensions() == 3, etl_traits<E>::is_fast)>
void validate_pmax_pooling_impl(const E& /*unused*/) {
    static_assert(etl_traits<E>::template dim<1>() % C1 == 0 && etl_traits<E>::template dim<2>() % C2 == 0, "Dimensions not divisible by the pooling ratio");
}

} //end of namespace detail

/*!
 * \brief Make sure that the pooling ratios are correct and that the expression can be pooled from.
 *
 * This function uses assertion to validate the condition. If possible, the
 * assertion is done at compile time.
 *
 * \tparam C1 The pooling ratio of the first dimension
 * \tparam C2 The pooling ratio of the second dimension
 * \param expr The expression to assert
 */
template <std::size_t C1, std::size_t C2, typename E>
void validate_pmax_pooling(const E& expr) {
    static_assert(is_etl_expr<E>::value, "Prob. Max Pooling only defined for ETL expressions");
    static_assert(etl_traits<E>::dimensions() == 2 || etl_traits<E>::dimensions() == 3, "Prob. Max Pooling only defined for 2D and 3D");

    detail::validate_pmax_pooling_impl<C1, C2>(expr);
}

} //end of namespace etl
