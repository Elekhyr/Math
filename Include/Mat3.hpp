/**
 * \file Mat3.hpp
 * \brief todo
 * \author Elekhyr
 * \version 1.0
 * \date 17/09/2017
 * \copyright Copyright (c) 2017 Thomas Margier
 *  This file is licensed under the MIT License, see https://opensource.org/licenses/MIT
 */
#pragma once
#include "Vec3.hpp"
#include <stdexcept>
#include <cmath>

namespace Math
{
	template <typename T>
	struct Mat3
	{
		static_assert(std::is_arithmetic<T>::value, "T must be numeric");
		Mat3(); /// Default constructor, return identity matrix
		Mat3(T v00, T v10, T v20,
			T v01, T v11, T v21,
			T v02, T v12, T v22); /// Construct 3x3 matrix from 9 values;
		Mat3(const Vec3<T>& c0, const Vec3<T>& c1, const Vec3<T>& c2); /// Construct from 3 vectors
		explicit Mat3(T values[9]); /// Contruct from an array of 9 arithmetic values
		Mat3(const Mat3& rhs);
		~Mat3();

		T Determinant() const;
		Mat3 Inverse() const;
		Mat3 Inverse(const T& det) const;

		// Arithmetic operators
		Mat3& operator=(const Mat3& rhs); /// Copy assignement

		Mat3& operator+=(const Mat3& rhs);
		Mat3& operator-=(const Mat3& rhs);
		Mat3& operator*=(const Mat3& rhs);

		Mat3& operator+=(const T& rhs);
		Mat3& operator-=(const T& rhs);
		Mat3& operator*=(const T& rhs);
		Mat3& operator/=(const T& rhs);

		T operator[](unsigned i) const;

		static Mat3 Identity();

		// Attributes
		T v00, v10, v20;
		T v01, v11, v21;
		T v02, v12, v22;
	};

	template <typename T>
	Mat3<T>::Mat3 () : 
		v00(1), v10(0), v20(0),
		v01(0), v11(1), v21(0),
		v02(0), v12(0), v22(1) {
	}

	template <typename T>
	Mat3<T>::Mat3 (T v00, T v10, T v20, T v01, T v11, T v21, T v02, T v12, T v22) :
		v00(v00), v10(v10), v20(v20),
		v01(v01), v11(v11), v21(v21),
		v02(v02), v12(v12), v22(v22) {
	}

	template <typename T>
	Mat3<T>::Mat3 (const Vec3<T>& c0, const Vec3<T>& c1, const Vec3<T>& c2) :
		v00(c0.x), v10(c1.x), v20(c2.x),
		v01(c0.y), v11(c1.y), v21(c2.y),
		v02(c0.z), v12(c1.z), v22(c2.z) {
	}

	template <typename T>
	Mat3<T>::Mat3 (T values[9]) :
		v00(values[0]), v10(values[1]), v20(values[2]),
		v01(values[3]), v11(values[4]), v21(values[5]),
		v02(values[6]), v12(values[7]), v22(values[8]) {
	}

	template <typename T>
	Mat3<T>::Mat3 (const Mat3& rhs) :
		v00(rhs.v00), v10(rhs.v10), v20(rhs.v20),
		v01(rhs.v01), v11(rhs.v11), v21(rhs.v21),
		v02(rhs.v02), v12(rhs.v12), v22(rhs.v22) {
	}

	template <typename T>
	Mat3<T>::~Mat3 () {
	}

	template <typename T>
	T Mat3<T>::Determinant () const
	{
		return v00*(v11*v22-v12*v21) - v01*(v10*v22-v12*v20) + v02*(v10*v21-v11*v20);
	}

	template <typename T>
	Mat3<T> Mat3<T>::Inverse () const
	{
		return (T(1)/Determinant()) * Mat3(
			v11*v22 - v12*v21, v02*v21 - v01*v22, v01*v12 - v02*v11,
			v12*v20 - v10*v22, v00*v22 - v02*v20, v02*v10 - v00*v12,
			v10*v21 - v11*v20, v01*v20 - v00*v21, v00*v11 - v01*v10);
	}

	template <typename T>
	Mat3<T> Mat3<T>::Inverse (const T& det) const {
		return (T(1) / det) * Mat3(
			v11*v22 - v12*v21, v02*v21 - v01*v22, v01*v12 - v02*v11,
			v12*v20 - v10*v22, v00*v22 - v02*v20, v02*v10 - v00*v12,
			v10*v21 - v11*v20, v01*v20 - v00*v21, v00*v11 - v01*v10);
	}

	template <typename T>
	Mat3<T>& Mat3<T>::operator= (const Mat3& rhs) {
		if (this != &rhs)
		{
			v00 = rhs.v00;
			v10 = rhs.v10;
			v20 = rhs.v20;
			v01 = rhs.v01;
			v11 = rhs.v11;
			v21 = rhs.v21;
			v02 = rhs.v02;
			v12 = rhs.v12;
			v22 = rhs.v22;
		}
		return *this;
	}

	template <typename T>
	Mat3<T>& Mat3<T>::operator+= (const Mat3& rhs) {
		v00 += rhs.v00;
		v10 += rhs.v10;
		v20 += rhs.v20;
		v01 += rhs.v01;
		v11 += rhs.v11;
		v21 += rhs.v21;
		v02 += rhs.v02;
		v12 += rhs.v12;
		v22 += rhs.v22;
		return *this;
	}

	template <typename T>
	Mat3<T>& Mat3<T>::operator-= (const Mat3& rhs) {
		v00 -= rhs.v00;
		v10 -= rhs.v10;
		v20 -= rhs.v20;
		v01 -= rhs.v01;
		v11 -= rhs.v11;
		v21 -= rhs.v21;
		v02 -= rhs.v02;
		v12 -= rhs.v12;
		v22 -= rhs.v22;
		return *this;
	}

	template <typename T>
	Mat3<T>& Mat3<T>::operator*= (const Mat3& rhs) {

		T tv00 = v00*rhs.v00 + v10 * rhs.v01 + v20 * rhs.v02;
		T tv10 = v00*rhs.v10 + v10 * rhs.v11 + v20 * rhs.v12;
		T tv20 = v00*rhs.v20 + v10 * rhs.v21 + v20 * rhs.v22;

		T tv01 = v01*rhs.v00 + v11 * rhs.v01 + v21 * rhs.v02;
		T tv11 = v01*rhs.v10 + v11 * rhs.v11 + v21 * rhs.v12;
		T tv21 = v01*rhs.v20 + v11 * rhs.v21 + v21 * rhs.v22;

		T tv02 = v02*rhs.v00 + v12 * rhs.v01 + v22 * rhs.v02;
		T tv12 = v02*rhs.v10 + v12 * rhs.v11 + v22 * rhs.v12;
		T tv22 = v02*rhs.v20 + v12 * rhs.v21 + v22 * rhs.v22;
		
		v00 = tv00;
		v10 = tv10;
		v20 = tv20;
		v01 = tv01;
		v11 = tv11;
		v21 = tv21;
		v02 = tv02;
		v12 = tv12;
		v22 = tv22;

		return *this;
	}

	template <typename T>
	Mat3<T>& Mat3<T>::operator+= (const T& rhs) {
		v00 += rhs;
		v10 += rhs;
		v20 += rhs;
		v01 += rhs;
		v11 += rhs;
		v21 += rhs;
		v02 += rhs;
		v12 += rhs;
		v22 += rhs;
		return *this;
	}

	template <typename T>
	Mat3<T>& Mat3<T>::operator-= (const T& rhs) {
		v00 -= rhs;
		v10 -= rhs;
		v20 -= rhs;
		v01 -= rhs;
		v11 -= rhs;
		v21 -= rhs;
		v02 -= rhs;
		v12 -= rhs;
		v22 -= rhs;
		return *this;
	}

	template <typename T>
	Mat3<T>& Mat3<T>::operator*= (const T& rhs) {
		v00 *= rhs;
		v10 *= rhs;
		v20 *= rhs;
		v01 *= rhs;
		v11 *= rhs;
		v21 *= rhs;
		v02 *= rhs;
		v12 *= rhs;
		v22 *= rhs;
		return *this;
	}

	template <typename T>
	Mat3<T>& Mat3<T>::operator/= (const T& rhs) {
		v00 /= rhs;
		v10 /= rhs;
		v20 /= rhs;
		v01 /= rhs;
		v11 /= rhs;
		v21 /= rhs;
		v02 /= rhs;
		v12 /= rhs;
		v22 /= rhs;
		return *this;
	}

	template <typename T>
	T Mat3<T>::operator[] (unsigned i) const {
		return *(&v00 + i);
	}

	template <typename T>
	Mat3<T> Mat3<T>::Identity () {
		return Mat3();
	}

	typedef Mat3<int> Mat3i;
	typedef Mat3<unsigned> Mat3u;
	typedef Mat3<float> Mat3f;
	typedef Mat3<double> Mat3d;

	//Stream operator
	template <typename T>
	std::ostream& operator<<(std::ostream& out, const Mat3<T>& mat3)
	{
		return out << mat3.v00 << ';' << mat3.v10 << ';' << mat3.v20 << '\n'
			<< mat3.v01 << ';' << mat3.v11 << ';' << mat3.v11 << '\n'
			<< mat3.v02 << ';' << mat3.v12 << ';' << mat3.v12 << '\n';
	}

	// Relational operators 
	template <typename T>
	bool operator==(const Mat3<T>& lhs, const Mat3<T>& rhs)
	{
		return
			lhs.v00 == rhs.v00 &&
			lhs.v10 == rhs.v10 &&
			lhs.v20 == rhs.v20 &&
			lhs.v01 == rhs.v01 &&
			lhs.v11 == rhs.v11 &&
			lhs.v21 == rhs.v21 &&
			lhs.v02 == rhs.v02 &&
			lhs.v12 == rhs.v12 &&
			lhs.v22 == rhs.v22;
	}

	template <typename T>
	bool operator!=(const Mat3<T>& lhs, const Mat3<T>& rhs)
	{
		return !(lhs == rhs);
	}

	// Operators
	template <typename T>
	Mat3<T> operator+ (Mat3<T> lhs, const Mat3<T>& rhs) {
		return lhs += rhs;
	}

	template <typename T>
	Mat3<T> operator- (Mat3<T> lhs, const Mat3<T>& rhs) {
		return lhs -= rhs;
	}

	template <typename T>
	Mat3<T> operator* (Mat3<T> lhs, const Mat3<T>& rhs) {
		return lhs *= rhs;
	}


	template <typename T>
	Mat3<T> operator+ (Mat3<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs += rhs;
	}

	template <typename T>
	Mat3<T> operator- (Mat3<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs -= rhs;
	}

	template <typename T>
	Mat3<T> operator* (Mat3<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs *= rhs;
	}

	template <typename T>
	Mat3<T> operator/ (Mat3<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs /= rhs;
	}

	template <typename T>
	Mat3<T> operator+ (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Mat3<T> lhs) {
		return lhs += rhs;
	}

	template <typename T>
	Mat3<T> operator- (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Mat3<T> lhs) {
		return lhs -= rhs;
	}

	template <typename T>
	Mat3<T> operator* (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Mat3<T> lhs) {
		return lhs *= rhs;
	}

	template <typename T>
	Mat3<T> operator/ (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Mat3<T> lhs) {
		return lhs /= rhs;
	}
}
