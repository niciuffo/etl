//=======================================================================
// Copyright (c) 2014-2017 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#pragma once

namespace etl {

cuComplex complex_cast(const std::complex<float>& alpha){
    return *reinterpret_cast<const cuComplex*>(&alpha);
}

cuComplex complex_cast(const etl::complex<float>& alpha){
    return *reinterpret_cast<const cuComplex*>(&alpha);
}

cuDoubleComplex complex_cast(const std::complex<double>& alpha){
    return *reinterpret_cast<const cuDoubleComplex*>(&alpha);
}

cuDoubleComplex complex_cast(const etl::complex<double>& alpha){
    return *reinterpret_cast<const cuDoubleComplex*>(&alpha);
}

} //end of namespace etl