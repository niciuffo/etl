//=======================================================================
// Copyright (c) 2014-2015 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#pragma once

/*!
 * \file comparable.hpp
 * \brief Use CRTP technique to inject comparison operators to expressions and value classes.
 */

namespace etl {

/*!
 * \brief CRTP class to inject comparison operators.
 */
template<typename D>
struct comparable {
    using derived_t = D;

    /*!
     * \brief Returns a reference to the derived object, i.e. the object using the CRTP injector.
     * \return a reference to the derived object.
     */
    derived_t& as_derived() noexcept {
        return *static_cast<derived_t*>(this);
    }

    /*!
     * \brief Compare the expression with another expression.
     *
     * \return true if the expressions contains the same sequence of values, false othwerise.
     */
    template<typename E>
    bool operator==(const E& rhs){
        if(etl::size(as_derived()) != etl::size(rhs)){
            return false;
        }

        //TODO DO a deep comparison of dimensions

        return std::equal(as_derived().begin(), as_derived().end(), rhs.begin());
    }

    /*!
     * \brief Compare the expression with another expression for inequality.
     *
     * \return false if the expressions contains the same sequence of values, true othwerise.
     */
    template<typename E>
    bool operator!=(const E& rhs){
        return !(as_derived() == rhs);
    }
};

} //end of namespace etl
