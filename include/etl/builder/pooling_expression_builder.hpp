//=======================================================================
// Copyright (c) 2014-2016 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

/*!
 * \file pooling_expression_builder.hpp
 * \brief Contains all the pooling operators and functions to build expressions.
*/

#pragma once

#include "etl/expression_helpers.hpp"

namespace etl {

/*!
 * \brief 2D Max Pooling of the given matrix expression
 * \param value The matrix expression
 * \tparam C1 The first pooling ratio
 * \tparam C2 The second pooling ratio
 * \return A expression representing the 2D Max Pooling of the input expression.
 */
template <std::size_t C1, std::size_t C2, std::size_t S1 = C1, std::size_t S2 = C2, typename E>
auto max_pool_2d(E&& value) {
    return temporary_unary_expr<value_t<E>, detail::build_type<E>, max_pool_2d_expr<value_t<E>, C1, C2, S1, S2>>{value};
}

/*!
 * \brief 2D Max Pooling of the given matrix expression
 * \param value The matrix expression
 * \param c1 The first pooling ratio
 * \param c2 The second pooling ratio
 * \return A expression representing the 2D Max Pooling of the input expression.
 */
template <typename E>
auto max_pool_2d(E&& value, std::size_t c1, std::size_t c2) {
    return temporary_unary_expr_state<value_t<E>, detail::build_type<E>, dyn_max_pool_2d_expr<value_t<E>>>{{c1, c2}, value};
}

/*!
 * \brief 2D Average Pooling of the given matrix expression
 * \param value The matrix expression
 * \tparam C1 The first pooling ratio
 * \tparam C2 The second pooling ratio
 * \return A expression representing the 2D Average Pooling of the input expression.
 */
template <std::size_t C1, std::size_t C2, std::size_t S1 = C1, std::size_t S2 = C2, typename E>
auto avg_pool_2d(E&& value) {
    return temporary_unary_expr<value_t<E>, detail::build_type<E>, avg_pool_2d_expr<value_t<E>, C1, C2, S1, S2>>{value};
}

/*!
 * \brief 2D Average Pooling of the given matrix expression
 * \param value The matrix expression
 * \param c1 The first pooling ratio
 * \param c2 The second pooling ratio
 * \return A expression representing the 2D Average Pooling of the input expression.
 */
template <typename E>
auto avg_pool_2d(E&& value, std::size_t c1, std::size_t c2) {
    return temporary_unary_expr_state<value_t<E>, detail::build_type<E>, dyn_avg_pool_2d_expr<value_t<E>>>{{c1, c2}, value};
}

/*!
 * \brief 3D Max Pooling of the given matrix expression
 * \param value The matrix expression
 * \tparam C1 The first pooling ratio
 * \tparam C2 The second pooling ratio
 * \tparam C3 The third pooling ratio
 * \return A expression representing the 3D Max Pooling of the input expression.
 */
template <std::size_t C1, std::size_t C2, std::size_t C3, typename E>
auto max_pool_3d(E&& value) {
    return temporary_unary_expr<value_t<E>, detail::build_type<E>, max_pool_3d_expr<value_t<E>, C1, C2, C3>>{value};
}

/*!
 * \brief 3D Max Pooling of the given matrix expression
 * \param value The matrix expression
 * \param c1 The first pooling ratio
 * \param c2 The second pooling ratio
 * \param c3 The third pooling ratio
 * \return A expression representing the 3D Max Pooling of the input expression.
 */
template <typename E>
auto max_pool_3d(E&& value, std::size_t c1, std::size_t c2, std::size_t c3) {
    return temporary_unary_expr_state<value_t<E>, detail::build_type<E>, dyn_max_pool_3d_expr<value_t<E>>>{{c1, c2, c3}, value};
}

/*!
 * \brief 3D Average Pooling of the given matrix expression
 * \param value The matrix expression
 * \tparam C1 The first pooling ratio
 * \tparam C2 The second pooling ratio
 * \tparam C3 The third pooling ratio
 * \return A expression representing the 3D Average Pooling of the input expression.
 */
template <std::size_t C1, std::size_t C2, std::size_t C3, typename E>
auto avg_pool_3d(E&& value) {
    return temporary_unary_expr<value_t<E>, detail::build_type<E>, avg_pool_3d_expr<value_t<E>, C1, C2, C3>>{value};
}

/*!
 * \brief 3D Average Pooling of the given matrix expression
 * \param value The matrix expression
 * \param c1 The first pooling ratio
 * \param c2 The second pooling ratio
 * \param c3 The third pooling ratio
 * \return A expression representing the 3D Average Pooling of the input expression.
 */
template <typename E>
auto avg_pool_3d(E&& value, std::size_t c1, std::size_t c2, std::size_t c3) {
    return temporary_unary_expr_state<value_t<E>, detail::build_type<E>, dyn_avg_pool_3d_expr<value_t<E>>>{{c1, c2, c3}, value};
}

/*!
 * \brief Derivative of the 2D Average Pooling of the given matrix expression
 * \param input The input
 * \param output The output
 * \tparam C1 The first pooling ratio
 * \tparam C2 The second pooling ratio
 * \return A expression representing the Derivative of 2D Average Pooling of the input expression.
 */
template <std::size_t C1, std::size_t C2, typename E, typename F>
auto avg_pool_derivative_2d(E&& input, F&& output) {
    cpp_unused(input);
    cpp_unused(output);
    return 1.0 / (C1 * C2);
}

/*!
 * \brief Derivative of the 2D Average Pooling of the given matrix expression
 * \param input The input
 * \param output The output
 * \param c1 the first pooling ratio
 * \param c2 the second pooling ratio
 * \return A expression representing the Derivative of 2D Average Pooling of the input expression.
 */
template <typename E, typename F>
auto avg_pool_derivative_2d(E&& input, F&& output, std::size_t c1, std::size_t c2) {
    cpp_unused(input);
    cpp_unused(output);
    return 1.0 / (c1 * c2);
}

/*!
 * \brief Derivative of the 3D Average Pooling of the given matrix expression
 * \param input The input
 * \param output The output
 * \tparam C1 The first pooling ratio
 * \tparam C2 The second pooling ratio
 * \tparam C3 The third pooling ratio
 * \return A expression representing the Derivative of 3D Average Pooling of the input expression.
 */
template <std::size_t C1, std::size_t C2, std::size_t C3, typename E, typename F>
auto avg_pool_derivative_3d(E&& input, F&& output) {
    cpp_unused(input);
    cpp_unused(output);
    return 1.0 / (C1 * C2 * C3);
}

/*!
 * \brief Derivative of the 3D Average Pooling of the given matrix expression
 * \param input The input
 * \param output The output
 * \param c1 the first pooling ratio
 * \param c2 the second pooling ratio
 * \param c3 the third pooling ratio
 * \return A expression representing the Derivative of 3D Average Pooling of the input expression.
 */
template <typename E, typename F>
auto avg_pool_derivative_3d(E&& input, F&& output, std::size_t c1, std::size_t c2, std::size_t c3) {
    cpp_unused(input);
    cpp_unused(output);
    return 1.0 / (c1 * c2 * c3);
}

/*!
 * \brief Derivative of the 2D Max Pooling of the given matrix expression
 * \param input The input
 * \param output The output
 * \tparam C1 The first pooling ratio
 * \tparam C2 The second pooling ratio
 * \return A expression representing the Derivative of 2D Max Pooling of the input expression.
 */
template <std::size_t C1, std::size_t C2, typename E, typename F>
auto max_pool_derivative_2d(E&& input, F&& output) {
    return temporary_binary_expr<value_t<E>, detail::build_type<E>, detail::build_type<F>, max_pool_derivative_2d_expr<value_t<E>, C1, C2>>{input, output};
}

/*!
 * \brief Derivative of the 2D Max Pooling of the given matrix expression
 * \param input The input
 * \param output The output
 * \param c1 The first pooling ratio
 * \param c2 The second pooling ratio
 * \return A expression representing the Derivative of 2D Max Pooling of the input expression.
 */
template <typename E, typename F>
auto max_pool_derivative_2d(E&& input, F&& output, std::size_t c1, std::size_t c2) {
    return temporary_binary_expr_state<value_t<E>, detail::build_type<E>, detail::build_type<F>, dyn_max_pool_derivative_2d_expr<value_t<E>>>{{c1, c2}, input, output};
}

/*!
 * \brief Derivative of the 3D Max Pooling of the given matrix expression
 * \param input The input
 * \param output The output
 * \tparam C1 The first pooling ratio
 * \tparam C2 The second pooling ratio
 * \tparam C3 The third pooling ratio
 * \return A expression representing the Derivative of 3D Max Pooling of the input expression.
 */
template <std::size_t C1, std::size_t C2, std::size_t C3, typename E, typename F>
auto max_pool_derivative_3d(E&& input, F&& output) {
    return temporary_binary_expr<value_t<E>, detail::build_type<E>, detail::build_type<F>, max_pool_derivative_3d_expr<value_t<E>, C1, C2, C3>>{input, output};
}

/*!
 * \brief Derivative of the 3D Max Pooling of the given matrix expression
 * \param input The input
 * \param output The output
 * \param c1 The first pooling ratio
 * \param c2 The second pooling ratio
 * \param c3 The third pooling ratio
 * \return A expression representing the Derivative of 3D Max Pooling of the input expression.
 */
template <typename E, typename F>
auto max_pool_derivative_3d(E&& input, F&& output, std::size_t c1, std::size_t c2, std::size_t c3) {
    return temporary_binary_expr_state<value_t<E>, detail::build_type<E>, detail::build_type<F>, dyn_max_pool_derivative_3d_expr<value_t<E>>>{{c1, c2, c3}, input, output};
}

/*!
 * \brief Upsample the given 2D matrix expression
 * \param value The input expression
 * \tparam C1 The first pooling ratio
 * \tparam C2 The second pooling ratio
 * \return A expression representing the Upsampling of the given expression
 */
template <std::size_t C1, std::size_t C2, typename E>
auto upsample_2d(E&& value) {
    return temporary_unary_expr<value_t<E>, detail::build_type<E>, upsample_2d_expr<value_t<E>, C1, C2>>{value};
}

/*!
 * \brief Upsample the given 2D matrix expression
 * \param value The input expression
 * \param c1 The first pooling ratio
 * \param c2 The second pooling ratio
 * \return A expression representing the Upsampling of the given expression
 */
template <typename E>
auto upsample_2d(E&& value, std::size_t c1, std::size_t c2) {
    return temporary_unary_expr_state<value_t<E>, detail::build_type<E>, dyn_upsample_2d_expr<value_t<E>>>{{c1, c2}, value};
}

/*!
 * \brief Upsample the given 3D matrix expression
 * \param value The input expression
 * \tparam C1 The first pooling ratio
 * \tparam C2 The second pooling ratio
 * \tparam C3 The third pooling ratio
 * \return A expression representing the Upsampling of the given expression
 */
template <std::size_t C1, std::size_t C2, std::size_t C3, typename E>
auto upsample_3d(E&& value) {
    return temporary_unary_expr<value_t<E>, detail::build_type<E>, upsample_3d_expr<value_t<E>, C1, C2, C3>>{value};
}

/*!
 * \brief Upsample the given 3D matrix expression
 * \param value The input expression
 * \param c1 The first pooling ratio
 * \param c2 The second pooling ratio
 * \param c3 The third pooling ratio
 * \return A expression representing the Upsampling of the given expression
 */
template <typename E>
auto upsample_3d(E&& value, std::size_t c1, std::size_t c2, std::size_t c3) {
    return temporary_unary_expr_state<value_t<E>, detail::build_type<E>, dyn_upsample_3d_expr<value_t<E>>>{{c1, c2, c3}, value};
}

/*!
 * \brief Probabilistic Max Pooling for hidden units
 * \param value The input expression
 * \tparam C1 The first pooling ratio
 * \tparam C2 The second pooling ratio
 * \return A expression representing the Probabilistic Max Pooling of hidden units
 */
template <std::size_t C1, std::size_t C2, typename E, cpp_enable_if(is_etl_expr<E>::value)>
auto p_max_pool_h(E&& value) {
    validate_pmax_pooling<C1, C2>(value);
    return unary_expr<value_t<E>, p_max_pool_h_transformer<detail::build_type<E>, C1, C2>, transform_op>{p_max_pool_h_transformer<detail::build_type<E>, C1, C2>(value)};
}

/*!
 * \brief Probabilistic Max Pooling for hidden units
 * \param value The input expression
 * \param c1 The first pooling ratio
 * \param c2 The second pooling ratio
 * \return A expression representing the Probabilistic Max Pooling of hidden units
 */
template <typename E, cpp_enable_if(is_etl_expr<E>::value)>
auto p_max_pool_h(E&& value, std::size_t c1, std::size_t c2) {
    validate_pmax_pooling(value, c1, c2);
    return unary_expr<value_t<E>, dyn_p_max_pool_h_transformer<detail::build_type<E>>, transform_op>{dyn_p_max_pool_h_transformer<detail::build_type<E>>(value, c1, c2)};
}

/*!
 * \brief Probabilistic Max Pooling for pooling units
 * \param value The input expression
 * \tparam C1 The first pooling ratio
 * \tparam C2 The second pooling ratio
 * \return A expression representing the Probabilistic Max Pooling of pooling units
 */
template <std::size_t C1, std::size_t C2, typename E, cpp_enable_if(is_etl_expr<E>::value)>
auto p_max_pool_p(E&& value) {
    validate_pmax_pooling<C1, C2>(value);
    return unary_expr<value_t<E>, p_max_pool_p_transformer<detail::build_type<E>, C1, C2>, transform_op>{p_max_pool_p_transformer<detail::build_type<E>, C1, C2>(value)};
}

/*!
 * \brief Probabilistic Max Pooling for pooling units
 * \param value The input expression
 * \param c1 The first pooling ratio
 * \param c2 The second pooling ratio
 * \return A expression representing the Probabilistic Max Pooling of pooling units
 */
template <typename E, cpp_enable_if(is_etl_expr<E>::value)>
auto p_max_pool_p(E&& value, std::size_t c1, std::size_t c2) {
    validate_pmax_pooling(value, c1, c2);
    return unary_expr<value_t<E>, dyn_p_max_pool_p_transformer<detail::build_type<E>>, transform_op>{dyn_p_max_pool_p_transformer<detail::build_type<E>>(value, c1, c2)};
}

} //end of namespace etl
