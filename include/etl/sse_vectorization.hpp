//=======================================================================
// Copyright (c) 2014-2015 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#pragma once

#include <immintrin.h>

#ifdef VECT_DEBUG
#include <iostream>
#endif

#ifdef __clang__
#define ETL_INLINE_VEC_128 inline __m128 __attribute__((__always_inline__, __nodebug__))
#define ETL_INLINE_VEC_128D inline __m128d __attribute__((__always_inline__, __nodebug__))
#else
#define ETL_INLINE_VEC_128 inline __m128 __attribute__((__always_inline__))
#define ETL_INLINE_VEC_128D inline __m128d __attribute__((__always_inline__))
#endif

namespace etl {

template<>
struct intrinsic_traits <float> {
    static constexpr const bool vectorizable = true;
    static constexpr const std::size_t size = 4;
    static constexpr const std::size_t alignment = 16;

    using intrinsic_type = __m128;
};

template<>
struct intrinsic_traits <double> {
    static constexpr const bool vectorizable = true;
    static constexpr const std::size_t size = 2;
    static constexpr const std::size_t alignment = 16;

    using intrinsic_type = __m128d;
};

template<>
struct intrinsic_traits <std::complex<float>> {
    static constexpr const bool vectorizable = true;
    static constexpr const std::size_t size = 2;
    static constexpr const std::size_t alignment = 16;

    using intrinsic_type = __m128;
};

template<>
struct intrinsic_traits <std::complex<double>> {
    static constexpr const bool vectorizable = true;
    static constexpr const std::size_t size = 1;
    static constexpr const std::size_t alignment = 16;

    using intrinsic_type = __m128d;
};

namespace vec {

#ifdef VEC_DEBUG

template<typename T>
void debug_d(T value){
    union test {
        __m128d vec; // a data field, maybe a register, maybe not
        double array[2];
        test(__m128d vec) : vec(vec) {}
    };

    test u_value = value;
    std::cout << "[" << u_value.array[0] << "," << u_value.array[1] << "]" << std::endl;
}

template<typename T>
void debug_s(T value){
    union test {
        __m128 vec; // a data field, maybe a register, maybe not
        float array[4];
        test(__m128 vec) : vec(vec) {}
    };

    test u_value = value;
    std::cout << "[" << u_value.array[0] << "," << u_value.array[1] << ","<< u_value.array[2] << ","<< u_value.array[3] << "]" << std::endl;
}

#else

template<typename T>
std::string debug_d(T){}

template<typename T>
std::string debug_s(T){}

#endif

inline void storeu(float* memory, __m128 value){
    _mm_storeu_ps(memory, value);
}

inline void storeu(double* memory, __m128d value){
    _mm_storeu_pd(memory, value);
}

inline void storeu(std::complex<float>* memory, __m128 value){
    _mm_storeu_ps(reinterpret_cast<float*>(memory), value);
}

inline void storeu(std::complex<double>* memory, __m128d value){
    _mm_storeu_pd(reinterpret_cast<double*>(memory), value);
}

inline void store(float* memory, __m128 value){
    _mm_store_ps(memory, value);
}

inline void store(double* memory, __m128d value){
    _mm_store_pd(memory, value);
}

inline void store(std::complex<float>* memory, __m128 value){
    _mm_store_ps(reinterpret_cast<float*>(memory), value);
}

inline void store(std::complex<double>* memory, __m128d value){
    _mm_store_pd(reinterpret_cast<double*>(memory), value);
}

ETL_INLINE_VEC_128 loadu(const float* memory){
    return _mm_loadu_ps(memory);
}

ETL_INLINE_VEC_128D loadu(const double* memory){
    return _mm_loadu_pd(memory);
}

ETL_INLINE_VEC_128 loadu(const std::complex<float>* memory){
    return _mm_loadu_ps(reinterpret_cast<const float*>(memory));
}

ETL_INLINE_VEC_128D loadu(const std::complex<double>* memory){
    return _mm_loadu_pd(reinterpret_cast<const double*>(memory));
}

ETL_INLINE_VEC_128D set(double value){
    return _mm_set1_pd(value);
}

ETL_INLINE_VEC_128 set(float value){
    return _mm_set1_ps(value);
}

ETL_INLINE_VEC_128D add(__m128d lhs, __m128d rhs){
    return _mm_add_pd(lhs, rhs);
}

ETL_INLINE_VEC_128D sub(__m128d lhs, __m128d rhs){
    return _mm_sub_pd(lhs, rhs);
}

ETL_INLINE_VEC_128D sqrt(__m128d x){
    return _mm_sqrt_pd(x);
}

ETL_INLINE_VEC_128D minus(__m128d x){
    return _mm_xor_pd(x, _mm_set1_pd(-0.f));
}

ETL_INLINE_VEC_128 add(__m128 lhs, __m128 rhs){
    return _mm_add_ps(lhs, rhs);
}

ETL_INLINE_VEC_128 sub(__m128 lhs, __m128 rhs){
    return _mm_sub_ps(lhs, rhs);
}

ETL_INLINE_VEC_128 sqrt(__m128 x){
    return _mm_sqrt_ps(x);
}

ETL_INLINE_VEC_128 minus(__m128 x){
    return _mm_xor_ps(x, _mm_set1_ps(-0.f));
}

template<bool Complex = false>
ETL_INLINE_VEC_128 div(__m128 lhs, __m128 rhs){
    return _mm_div_ps(lhs, rhs);
}

template<bool Complex = false>
ETL_INLINE_VEC_128D div(__m128d lhs, __m128d rhs){
    return _mm_div_pd(lhs, rhs);
}

template<bool Complex = false>
ETL_INLINE_VEC_128 mul(__m128 lhs, __m128 rhs){
    return _mm_mul_ps(lhs, rhs);
}

template<>
ETL_INLINE_VEC_128 mul<true>(__m128 lhs, __m128 rhs){
    //lhs = [x1.real, x1.img, x2.real, x2.img]
    //rhs = [y1.real, y1.img, y2.real, y2.img]

    //ymm1 = [y1.real, y1.real, y2.real, y2.real]
    __m128 ymm1 = _mm_moveldup_ps(rhs);

    //ymm2 = lhs * ymm1
    __m128 ymm2 = _mm_mul_ps(lhs, ymm1);

    //ymm3 = [x1.img, x1.real, x2.img, x2.real]
    __m128 ymm3 = _mm_shuffle_ps(lhs, lhs, _MM_SHUFFLE(2, 3, 0, 1));

    //ymm1 = [y1.imag, y1.imag, y2.imag, y2.imag]
    ymm1 = _mm_movehdup_ps(rhs);

    //ymm4 = ymm3 * ymm1
    __m128 ymm4 = _mm_mul_ps(ymm3, ymm1);

    //result = [ymm2 -+ ymm4];
    return _mm_addsub_ps(ymm2, ymm4);
}

template<bool Complex = false>
ETL_INLINE_VEC_128D mul(__m128d lhs, __m128d rhs){
    return _mm_mul_pd(lhs, rhs);
}

template<>
ETL_INLINE_VEC_128D mul<true>(__m128d lhs, __m128d rhs){
    //lhs = [x.real, x.img]
    //rhs = [y.real, y.img]

    //ymm1 = [y.real, y.real]
    __m128d ymm1 = _mm_movedup_pd(rhs);

    //ymm2 = [x.real * y.real, x.img * y.real]
    __m128d ymm2 = _mm_mul_pd(lhs, ymm1);

    //ymm1 = [x.img, x.real]
    ymm1 = _mm_shuffle_pd(lhs, lhs, _MM_SHUFFLE2(0, 1));

    //ymm2 =  [y.img, y.img]
    __m128d ymm3 = _mm_shuffle_pd(rhs, rhs, _MM_SHUFFLE2(0, 1));
    __m128d ymm4 = _mm_movedup_pd(ymm3);

    //ymm3 = [x.img * y.img, x.real * y.img]
    ymm3 = _mm_mul_pd(ymm1, ymm4);

    //result = [x.real * y.real - x.img * y.img, x.img * y.real - x.real * y.img]
    return _mm_addsub_pd(ymm2, ymm3);
}

//The Intel C++ Compiler (icc) has more intrinsics.
//ETL uses them when compiled with icc

#ifdef __INTEL_COMPILER

//Exponential

ETL_INLINE_VEC_128D exp(__m128d x){
    return _mm_exp_pd(x);
}

ETL_INLINE_VEC_128 exp(__m128 x){
    return _mm_exp_ps(x);
}

//Logarithm

ETL_INLINE_VEC_128D log(__m128d x){
    return _mm_log_pd(x);
}

ETL_INLINE_VEC_128 log(__m128 x){
    return _mm_log_ps(x);
}

//Min

ETL_INLINE_VEC_128D min(__m128d lhs, __m128d rhs){
    return _mm_min_pd(lhs, rhs);
}

ETL_INLINE_VEC_128 min(__m128 lhs, __m128 rhs){
    return _mm_min_ps(lhs, rhs);
}

//Max

ETL_INLINE_VEC_128D max(__m128d lhs, __m128d rhs){
    return _mm_max_pd(lhs, rhs);
}

ETL_INLINE_VEC_128 max(__m128 lhs, __m128 rhs){
    return _mm_max_ps(lhs, rhs);
}

#endif

} //end of namespace vec

} //end of namespace etl
