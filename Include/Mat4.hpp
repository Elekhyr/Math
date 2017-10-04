/**
 * \file Mat4.hpp
 * \brief todo
 * \author Elekhyr
 * \version 1.0
 * \date 12/09/2017
 * \copyright Copyright (c) 2017 Thomas Margier
 *  This file is licensed under the MIT License, see https://opensource.org/licenses/MIT
 */
#pragma once
#include <type_traits>
#include <ostream>
#include "Vec4.hpp"
#include "Mat3.hpp"
#include <stdexcept>
#include <cmath>

namespace Math
{
	template<typename T>
	struct Mat4
	{
		static_assert(std::is_arithmetic<T>::value, "T must be numeric");

		// Constructors
		Mat4();
		Mat4(T v00, T v10, T v20, T v30,
			T v01, T v11, T v21, T v31,
			T v02, T v12, T v22, T v32,
			T v03, T v13, T v23, T v33
		);
		Mat4(const Vec4<T>& c0, const Vec4<T>& c1, const Vec4<T>& c2, const Vec4<T>& c3);
		explicit Mat4(const T values[16]);
		Mat4(const Mat4& rhs);
		~Mat4();

		// Functions

		T Determinant() const;
		Mat4 Inverse() const;
		Mat4 Inverse(const T& determinant) const;
		// Operators

		Mat4& operator=(const Mat4& rhs); /// Copy assignement

		Mat4& operator+=(const Mat4& rhs);
		Mat4& operator-=(const Mat4& rhs);
		Mat4& operator*=(const Mat4& rhs);

		Mat4& operator+=(const T& rhs);
		Mat4& operator-=(const T& rhs);
		Mat4& operator*=(const T& rhs);
		Mat4& operator/=(const T& rhs);

		T operator[](unsigned i) const;

		static Mat4 Identity();

		// Attributes
		T v00, v10, v20, v30;
		T v01, v11, v21, v31;
		T v02, v12, v22, v32;
		T v03, v13, v23, v33;
	};

	template <typename T>
	Mat4<T>::Mat4 () :
		v00(1), v10(0), v20(0), v30(0),
		v01(0), v11(1), v21(0), v31(0),
		v02(0), v12(0), v22(1), v32(0),
		v03(0), v13(0), v23(0), v33(1) {
	}

	template <typename T>
	Mat4<T>::Mat4 (T v00, T v10, T v20, T v30, T v01, T v11, T v21, T v31, T v02, T v12, T v22, T v32, T v03, T v13, T v23, T v33) :
		v00(v00), v10(v10), v20(v20), v30(v30),
		v01(v01), v11(v11), v21(v21), v31(v31),
		v02(v02), v12(v12), v22(v22), v32(v32),
		v03(v03), v13(v13), v23(v23), v33(v33) {
	}

	template <typename T>
	Mat4<T>::Mat4 (const Vec4<T>& c0, const Vec4<T>& c1, const Vec4<T>& c2, const Vec4<T>& c3) :
		v00(c0.x), v10(c1.x), v20(c2.x), v30(c3.x),
		v01(c0.y), v11(c1.y), v21(c2.y), v31(c3.y),
		v02(c0.z), v12(c1.z), v22(c2.z), v32(c3.z),
		v03(c0.w), v13(c1.w), v23(c2.w), v33(c3.w) {
	}

	template <typename T>
	Mat4<T>::Mat4 (const T values[16]) :
		v00(values[0]), v10(values[1]), v20(values[2]), v30(values[3]),
		v01(values[4]), v11(values[5]), v21(values[6]), v31(values[7]),
		v02(values[8]), v12(values[9]), v22(values[10]), v32(values[11]),
		v03(values[12]), v13(values[13]), v23(values[14]), v33(values[15]) {
	}

	template <typename T>
	Mat4<T>::Mat4 (const Mat4& rhs) {
		v00 = rhs.v00;
		v10 = rhs.v10;
		v20 = rhs.v20;
		v30 = rhs.v30;

		v01 = rhs.v01;
		v11 = rhs.v11;
		v21 = rhs.v21;
		v31 = rhs.v31;

		v02 = rhs.v02;
		v12 = rhs.v12;
		v22 = rhs.v22;
		v32 = rhs.v32;

		v03 = rhs.v03;
		v13 = rhs.v13;
		v23 = rhs.v23;
		v33 = rhs.v33;
	}

	template <typename T>
	Mat4<T>::~Mat4 () {
	}

	template <typename T>
	T Mat4<T>::Determinant () const {
		T inv[16], det;

		inv[0] = v11 * v22 * v33 -
			v11 * v32 * v23 -
			v12 * v21 * v33 +
			v12 * v31 * v23 +
			v13 * v21 * v32 -
			v13 * v31 * v22;

		inv[4] = -v01 * v22 * v33 +
			v01 * v32 * v23 +
			v02 * v21 * v33 -
			v02 * v31 * v23 -
			v03 * v21 * v32 +
			v03 * v31 * v22;

		inv[8] = v01 * v12 * v33 -
			v01 * v32 * v13 -
			v02 * v11 * v33 +
			v02 * v31 * v13 +
			v03 * v11 * v32 -
			v03 * v31 * v12;

		inv[12] = -v01 * v12 * v23 +
			v01 * v22 * v13 +
			v02 * v11 * v23 -
			v02 * v21 * v13 -
			v03 * v11 * v22 +
			v03 * v21 * v12;

		inv[1] = -v10 * v22 * v33 +
			v10 * v32 * v23 +
			v12 * v20 * v33 -
			v12 * v30 * v23 -
			v13 * v20 * v32 +
			v13 * v30 * v22;

		inv[5] = v00 * v22 * v33 -
			v00 * v32 * v23 -
			v02 * v20 * v33 +
			v02 * v30 * v23 +
			v03 * v20 * v32 -
			v03 * v30 * v22;

		inv[9] = -v00 * v12 * v33 +
			v00 * v32 * v13 +
			v02 * v10 * v33 -
			v02 * v30 * v13 -
			v03 * v10 * v32 +
			v03 * v30 * v12;

		inv[13] = v00 * v12 * v23 -
			v00 * v22 * v13 -
			v02 * v10 * v23 +
			v02 * v20 * v13 +
			v03 * v10 * v22 -
			v03 * v20 * v12;

		inv[2] = v10 * v21 * v33 -
			v10 * v31 * v23 -
			v11 * v20 * v33 +
			v11 * v30 * v23 +
			v13 * v20 * v31 -
			v13 * v30 * v21;

		inv[6] = -v00 * v21 * v33 +
			v00 * v31 * v23 +
			v01 * v20 * v33 -
			v01 * v30 * v23 -
			v03 * v20 * v31 +
			v03 * v30 * v21;

		inv[10] = v00 * v11 * v33 -
			v00 * v31 * v13 -
			v01 * v10 * v33 +
			v01 * v30 * v13 +
			v03 * v10 * v31 -
			v03 * v30 * v11;

		inv[14] = -v00 * v11 * v23 +
			v00 * v21 * v13 +
			v01 * v10 * v23 -
			v01 * v20 * v13 -
			v03 * v10 * v21 +
			v03 * v20 * v11;

		inv[3] = -v10 * v21 * v32 +
			v10 * v31 * v22 +
			v11 * v20 * v32 -
			v11 * v30 * v22 -
			v12 * v20 * v31 +
			v12 * v30 * v21;

		inv[7] = v00 * v21 * v32 -
			v00 * v31 * v22 -
			v01 * v20 * v32 +
			v01 * v30 * v22 +
			v02 * v20 * v31 -
			v02 * v30 * v21;

		inv[11] = -v00 * v11 * v32 +
			v00 * v31 * v12 +
			v01 * v10 * v32 -
			v01 * v30 * v12 -
			v02 * v10 * v31 +
			v02 * v30 * v11;

		inv[15] = v00 * v11 * v22 -
			v00 * v21 * v12 -
			v01 * v10 * v22 +
			v01 * v20 * v12 +
			v02 * v10 * v21 -
			v02 * v20 * v11;

		return v00 * inv[0] + v10 * inv[4] + v20 * inv[8] + v30 * inv[12];
	}

	template <typename T>
	Mat4<T> Mat4<T>::Inverse () const {
		T inv[16];

		inv[0] = v11 * v22 * v33 -
			v11 * v32 * v23 -
			v12 * v21 * v33 +
			v12 * v31 * v23 +
			v13 * v21 * v32 -
			v13 * v31 * v22;

		inv[4] = -v01 * v22 * v33 +
			v01 * v32 * v23 +
			v02 * v21 * v33 -
			v02 * v31 * v23 -
			v03 * v21 * v32 +
			v03 * v31 * v22;

		inv[8] = v01 * v12 * v33 -
			v01 * v32 * v13 -
			v02 * v11 * v33 +
			v02 * v31 * v13 +
			v03 * v11 * v32 -
			v03 * v31 * v12;

		inv[12] = -v01 * v12 * v23 +
			v01 * v22 * v13 +
			v02 * v11 * v23 -
			v02 * v21 * v13 -
			v03 * v11 * v22 +
			v03 * v21 * v12;

		inv[1] = -v10 * v22 * v33 +
			v10 * v32 * v23 +
			v12 * v20 * v33 -
			v12 * v30 * v23 -
			v13 * v20 * v32 +
			v13 * v30 * v22;

		inv[5] = v00 * v22 * v33 -
			v00 * v32 * v23 -
			v02 * v20 * v33 +
			v02 * v30 * v23 +
			v03 * v20 * v32 -
			v03 * v30 * v22;

		inv[9] = -v00 * v12 * v33 +
			v00 * v32 * v13 +
			v02 * v10 * v33 -
			v02 * v30 * v13 -
			v03 * v10 * v32 +
			v03 * v30 * v12;

		inv[13] = v00 * v12 * v23 -
			v00 * v22 * v13 -
			v02 * v10 * v23 +
			v02 * v20 * v13 +
			v03 * v10 * v22 -
			v03 * v20 * v12;

		inv[2] = v10 * v21 * v33 -
			v10 * v31 * v23 -
			v11 * v20 * v33 +
			v11 * v30 * v23 +
			v13 * v20 * v31 -
			v13 * v30 * v21;

		inv[6] = -v00 * v21 * v33 +
			v00 * v31 * v23 +
			v01 * v20 * v33 -
			v01 * v30 * v23 -
			v03 * v20 * v31 +
			v03 * v30 * v21;

		inv[10] = v00 * v11 * v33 -
			v00 * v31 * v13 -
			v01 * v10 * v33 +
			v01 * v30 * v13 +
			v03 * v10 * v31 -
			v03 * v30 * v11;

		inv[14] = -v00 * v11 * v23 +
			v00 * v21 * v13 +
			v01 * v10 * v23 -
			v01 * v20 * v13 -
			v03 * v10 * v21 +
			v03 * v20 * v11;

		inv[3] = -v10 * v21 * v32 +
			v10 * v31 * v22 +
			v11 * v20 * v32 -
			v11 * v30 * v22 -
			v12 * v20 * v31 +
			v12 * v30 * v21;

		inv[7] = v00 * v21 * v32 -
			v00 * v31 * v22 -
			v01 * v20 * v32 +
			v01 * v30 * v22 +
			v02 * v20 * v31 -
			v02 * v30 * v21;

		inv[11] = -v00 * v11 * v32 +
			v00 * v31 * v12 +
			v01 * v10 * v32 -
			v01 * v30 * v12 -
			v02 * v10 * v31 +
			v02 * v30 * v11;

		inv[15] = v00 * v11 * v22 -
			v00 * v21 * v12 -
			v01 * v10 * v22 +
			v01 * v20 * v12 +
			v02 * v10 * v21 -
			v02 * v20 * v11;

		T det = v00 * inv[0] + v10 * inv[4] + v20 * inv[8] + v30 * inv[12];
		det = 1.0 / det;

		return Mat4(
			inv[0] * det, inv[1] * det, inv[2] * det, inv[3] * det,
			inv[4] * det, inv[5] * det, inv[6] * det, inv[7] * det,
			inv[8] * det, inv[9] * det, inv[10] * det, inv[11] * det,
			inv[12] * det, inv[13] * det, inv[14] * det, inv[15] * det
		);
	}

	template <typename T>
	Mat4<T> Mat4<T>::Inverse (const T& det) const {
		T inv[16];

		inv[0] = v11 * v22 * v33 -
			v11 * v32 * v23 -
			v12 * v21 * v33 +
			v12 * v31 * v23 +
			v13 * v21 * v32 -
			v13 * v31 * v22;

		inv[4] = -v01 * v22 * v33 +
			v01 * v32 * v23 +
			v02 * v21 * v33 -
			v02 * v31 * v23 -
			v03 * v21 * v32 +
			v03 * v31 * v22;

		inv[8] = v01 * v12 * v33 -
			v01 * v32 * v13 -
			v02 * v11 * v33 +
			v02 * v31 * v13 +
			v03 * v11 * v32 -
			v03 * v31 * v12;

		inv[12] = -v01 * v12 * v23 +
			v01 * v22 * v13 +
			v02 * v11 * v23 -
			v02 * v21 * v13 -
			v03 * v11 * v22 +
			v03 * v21 * v12;

		inv[1] = -v10 * v22 * v33 +
			v10 * v32 * v23 +
			v12 * v20 * v33 -
			v12 * v30 * v23 -
			v13 * v20 * v32 +
			v13 * v30 * v22;

		inv[5] = v00 * v22 * v33 -
			v00 * v32 * v23 -
			v02 * v20 * v33 +
			v02 * v30 * v23 +
			v03 * v20 * v32 -
			v03 * v30 * v22;

		inv[9] = -v00 * v12 * v33 +
			v00 * v32 * v13 +
			v02 * v10 * v33 -
			v02 * v30 * v13 -
			v03 * v10 * v32 +
			v03 * v30 * v12;

		inv[13] = v00 * v12 * v23 -
			v00 * v22 * v13 -
			v02 * v10 * v23 +
			v02 * v20 * v13 +
			v03 * v10 * v22 -
			v03 * v20 * v12;

		inv[2] = v10 * v21 * v33 -
			v10 * v31 * v23 -
			v11 * v20 * v33 +
			v11 * v30 * v23 +
			v13 * v20 * v31 -
			v13 * v30 * v21;

		inv[6] = -v00 * v21 * v33 +
			v00 * v31 * v23 +
			v01 * v20 * v33 -
			v01 * v30 * v23 -
			v03 * v20 * v31 +
			v03 * v30 * v21;

		inv[10] = v00 * v11 * v33 -
			v00 * v31 * v13 -
			v01 * v10 * v33 +
			v01 * v30 * v13 +
			v03 * v10 * v31 -
			v03 * v30 * v11;

		inv[14] = -v00 * v11 * v23 +
			v00 * v21 * v13 +
			v01 * v10 * v23 -
			v01 * v20 * v13 -
			v03 * v10 * v21 +
			v03 * v20 * v11;

		inv[3] = -v10 * v21 * v32 +
			v10 * v31 * v22 +
			v11 * v20 * v32 -
			v11 * v30 * v22 -
			v12 * v20 * v31 +
			v12 * v30 * v21;

		inv[7] = v00 * v21 * v32 -
			v00 * v31 * v22 -
			v01 * v20 * v32 +
			v01 * v30 * v22 +
			v02 * v20 * v31 -
			v02 * v30 * v21;

		inv[11] = -v00 * v11 * v32 +
			v00 * v31 * v12 +
			v01 * v10 * v32 -
			v01 * v30 * v12 -
			v02 * v10 * v31 +
			v02 * v30 * v11;

		inv[15] = v00 * v11 * v22 -
			v00 * v21 * v12 -
			v01 * v10 * v22 +
			v01 * v20 * v12 +
			v02 * v10 * v21 -
			v02 * v20 * v11;

		return Mat4(
			inv[0] * det, inv[1] * det, inv[2] * det, inv[3] * det,
			inv[4] * det, inv[5] * det, inv[6] * det, inv[7] * det,
			inv[8] * det, inv[9] * det, inv[10] * det, inv[11] * det,
			inv[12] * det, inv[13] * det, inv[14] * det, inv[15] * det
		);
	}

	template <typename T>
	Mat4<T>& Mat4<T>::operator= (const Mat4& rhs) {
		if (this != &rhs)
		{
			v00 = rhs.v00;
			v10 = rhs.v10;
			v20 = rhs.v20;
			v30 = rhs.v30;

			v01 = rhs.v01;
			v11 = rhs.v11;
			v21 = rhs.v21;
			v31 = rhs.v31;

			v02 = rhs.v02;
			v12 = rhs.v12;
			v22 = rhs.v22;
			v32 = rhs.v32;

			v03 = rhs.v03;
			v13 = rhs.v13;
			v23 = rhs.v23;
			v33 = rhs.v33;
		}
		return *this;
	}

	template <typename T>
	Mat4<T>& Mat4<T>::operator+= (const Mat4& rhs) {
		v00 += rhs.v00;
		v10 += rhs.v10;
		v20 += rhs.v20;
		v30 += rhs.v30;
		v01 += rhs.v01;
		v11 += rhs.v11;
		v21 += rhs.v21;
		v31 += rhs.v31;
		v02 += rhs.v02;
		v12 += rhs.v12;
		v22 += rhs.v22;
		v32 += rhs.v32;
		v03 += rhs.v03;
		v13 += rhs.v13;
		v23 += rhs.v23;
		v33 += rhs.v33;
		return *this;
	}

	template <typename T>
	Mat4<T>& Mat4<T>::operator-= (const Mat4& rhs) {
		v00 -= rhs.v00;
		v10 -= rhs.v10;
		v20 -= rhs.v20;
		v30 -= rhs.v30;
		v01 -= rhs.v01;
		v11 -= rhs.v11;
		v21 -= rhs.v21;
		v31 -= rhs.v31;
		v02 -= rhs.v02;
		v12 -= rhs.v12;
		v22 -= rhs.v22;
		v32 -= rhs.v32;
		v03 -= rhs.v03;
		v13 -= rhs.v13;
		v23 -= rhs.v23;
		v33 -= rhs.v33;
		return *this;
	}

	template <typename T>
	Mat4<T>& Mat4<T>::operator*= (const Mat4& rhs) {
		T tv00 = v00*rhs.v00 + v10 * rhs.v01 + v20 * rhs.v02 + v30 * v03;
		T tv10 = v00*rhs.v10 + v10 * rhs.v11 + v20 * rhs.v12 + v30 * v13;
		T tv20 = v00*rhs.v20 + v10 * rhs.v21 + v20 * rhs.v22 + v30 * v23;
		T tv30 = v00*rhs.v20 + v10 * rhs.v21 + v20 * rhs.v22 + v30 * v33;

		T tv01 = v01*rhs.v00 + v11 * rhs.v01 + v21 * rhs.v02 + v31 * v03;
		T tv11 = v01*rhs.v10 + v11 * rhs.v11 + v21 * rhs.v12 + v31 * v13;
		T tv21 = v01*rhs.v20 + v11 * rhs.v21 + v21 * rhs.v22 + v31 * v23;
		T tv31 = v01*rhs.v20 + v11 * rhs.v21 + v21 * rhs.v22 + v31 * v33;

		T tv02 = v02*rhs.v00 + v12 * rhs.v01 + v22 * rhs.v02 + v32 * v03;
		T tv12 = v02*rhs.v10 + v12 * rhs.v11 + v22 * rhs.v12 + v32 * v13;
		T tv22 = v02*rhs.v20 + v12 * rhs.v21 + v22 * rhs.v22 + v32 * v23;
		T tv32 = v02*rhs.v20 + v12 * rhs.v21 + v22 * rhs.v22 + v32 * v33;

		T tv03 = v02*rhs.v00 + v12 * rhs.v01 + v22 * rhs.v02 + v33 * v03;
		T tv13 = v02*rhs.v10 + v12 * rhs.v11 + v22 * rhs.v12 + v33 * v13;
		T tv23 = v02*rhs.v20 + v12 * rhs.v21 + v22 * rhs.v22 + v33 * v23;
		T tv33 = v02*rhs.v20 + v12 * rhs.v21 + v22 * rhs.v22 + v33 * v33;

		v00 = tv00;
		v10 = tv10;
		v20 = tv20;
		v30 = tv30;

		v01 = tv01;
		v11 = tv11;
		v21 = tv21;
		v31 = tv31;

		v02 = tv02;
		v12 = tv12;
		v22 = tv22;
		v32 = tv32;

		v03 = tv03;
		v13 = tv13;
		v23 = tv23;
		v33 = tv33;
		return *this;
	}

	template <typename T>
	Mat4<T>& Mat4<T>::operator+= (const T& rhs) {
		v00 += rhs;
		v10 += rhs;
		v20 += rhs;
		v30 += rhs;
		v01 += rhs;
		v11 += rhs;
		v21 += rhs;
		v31 += rhs;
		v02 += rhs;
		v12 += rhs;
		v22 += rhs;
		v32 += rhs;
		v03 += rhs;
		v13 += rhs;
		v23 += rhs;
		v33 += rhs;
		return *this;
	}

	template <typename T>
	Mat4<T>& Mat4<T>::operator-= (const T& rhs) {
		v00 -= rhs;
		v10 -= rhs;
		v20 -= rhs;
		v30 -= rhs;
		v01 -= rhs;
		v11 -= rhs;
		v21 -= rhs;
		v31 -= rhs;
		v02 -= rhs;
		v12 -= rhs;
		v22 -= rhs;
		v32 -= rhs;
		v03 -= rhs;
		v13 -= rhs;
		v23 -= rhs;
		v33 -= rhs;
		return *this;
	}

	template <typename T>
	Mat4<T>& Mat4<T>::operator*= (const T& rhs) {
		v00 *= rhs;
		v10 *= rhs;
		v20 *= rhs;
		v30 *= rhs;
		v01 *= rhs;
		v11 *= rhs;
		v21 *= rhs;
		v31 *= rhs;
		v02 *= rhs;
		v12 *= rhs;
		v22 *= rhs;
		v32 *= rhs;
		v03 *= rhs;
		v13 *= rhs;
		v23 *= rhs;
		v33 *= rhs;
		return *this;
	}

	template <typename T>
	Mat4<T>& Mat4<T>::operator/= (const T& rhs) {
		v00 /= rhs;
		v10 /= rhs;
		v20 /= rhs;
		v30 /= rhs;
		v01 /= rhs;
		v11 /= rhs;
		v21 /= rhs;
		v31 /= rhs;
		v02 /= rhs;
		v12 /= rhs;
		v22 /= rhs;
		v32 /= rhs;
		v03 /= rhs;
		v13 /= rhs;
		v23 /= rhs;
		v33 /= rhs;
		return *this;
	}

	template <typename T>
	T Mat4<T>::operator[] (unsigned i) const {
		return *(&v00 + i);
	}

	template <typename T>
	Mat4<T> Mat4<T>::Identity () {
		return Mat4();
	}

	typedef Mat4<int> Mat4i;
	typedef Mat4<unsigned> Mat4u;
	typedef Mat4<float> Mat4f;
	typedef Mat4<double> Mat4d;

	//Stream operator
	template <typename T>
	std::ostream& operator<<(std::ostream& out, const Mat4<T>& Mat4)
	{
		return out << Mat4.v00 << ';' << Mat4.v10 << ';' << Mat4.v20 << ';' << Mat4.v30 << '\n'
				<< Mat4.v01 << ';' << Mat4.v11 << ';' << Mat4.v11 << ';' << Mat4.v31 << '\n'
				<< Mat4.v02 << ';' << Mat4.v12 << ';' << Mat4.v12 << ';' << Mat4.v32 << '\n' 
				<< Mat4.v03 << ';' << Mat4.v13 << ';' << Mat4.v13 << ';' << Mat4.v33 << '\n';
	}

	// Relational operators 
	template <typename T>
	bool operator==(const Mat4<T>& lhs, const Mat4<T>& rhs)
	{
		return
			lhs.v00 == rhs.v00 &&
			lhs.v10 == rhs.v10 &&
			lhs.v20 == rhs.v20 &&
			lhs.v30 == rhs.v30 &&
			lhs.v01 == rhs.v01 &&
			lhs.v11 == rhs.v11 &&
			lhs.v21 == rhs.v21 &&
			lhs.v31 == rhs.v31 &&
			lhs.v02 == rhs.v02 &&
			lhs.v12 == rhs.v12 &&
			lhs.v22 == rhs.v22 &&
			lhs.v32 == rhs.v32 &&
			lhs.v03 == rhs.v03 &&
			lhs.v13 == rhs.v13 &&
			lhs.v23 == rhs.v23 &&
			lhs.v33 == rhs.v33;
	}

	template <typename T>
	bool operator!=(const Mat4<T>& lhs, const Mat4<T>& rhs)
	{
		return !(lhs == rhs);
	}

	// Operators
	template <typename T>
	Mat4<T> operator+ (Mat4<T> lhs, const Mat4<T>& rhs) {
		return lhs += rhs;
	}

	template <typename T>
	Mat4<T> operator- (Mat4<T> lhs, const Mat4<T>& rhs) {
		return lhs -= rhs;
	}

	template <typename T>
	Mat4<T> operator* (Mat4<T> lhs, const Mat4<T>& rhs) {
		return lhs *= rhs;
	}


	template <typename T>
	Mat4<T> operator+ (Mat4<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs += rhs;
	}

	template <typename T>
	Mat4<T> operator- (Mat4<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs -= rhs;
	}

	template <typename T>
	Mat4<T> operator* (Mat4<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs *= rhs;
	}

	template <typename T>
	Mat4<T> operator/ (Mat4<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs /= rhs;
	}

	template <typename T>
	Mat4<T> operator+ (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Mat4<T> lhs) {
		return lhs += rhs;
	}

	template <typename T>
	Mat4<T> operator- (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Mat4<T> lhs) {
		return lhs -= rhs;
	}

	template <typename T>
	Mat4<T> operator* (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Mat4<T> lhs) {
		return lhs *= rhs;
	}

	template <typename T>
	Mat4<T> operator/ (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Mat4<T> lhs) {
		return lhs /= rhs;
	}
}

