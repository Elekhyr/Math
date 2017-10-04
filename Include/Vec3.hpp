/**
 * \file Vec3.hpp
 * \brief todo
 * \author Elekhyr
 * \version 1.0
 * \date 11/09/2017
 * \copyright Copyright (c) 2017 Thomas Margier
 *  This file is licensed under the MIT License, see https://opensource.org/licenses/MIT
 */
#pragma once
#include <type_traits>
#include <ostream>
#include "Vec3.hpp"
#include <stdexcept>
#include <cmath>

template <typename T>
struct Vec2;
template <typename T>
struct Vec4;

namespace Math
{
	template <typename T>
	struct Vec3
	{
		static_assert(std::is_arithmetic<T>::value, "T must be numeric");

		// Constructors
		Vec3(); /// Default constructor
		Vec3(T x, T y, T z); /// Construct from 2 arithmetic values 
		Vec3(const Vec2<T>& rhs, T z); /// Construct from Vec2 plus an arithmetic value 
		Vec3(const Vec3& rhs); /// Copy constructor
		explicit Vec3(const Vec4<T>& rhs); /// Constructor from Vec4
		~Vec3();

		// Functions 
		T Sum() const; /// Sum the components of the vector.
		double Length() const; /// Length of the vector, also called the magnitude.
		void Normalize(); /// Normalize the vector.

		bool IsOrthogonal(const Vec3& Q) const;

		// Arithmetic operators
		Vec3& operator=(const Vec3& rhs); /// Copy assignement

		Vec3& operator+=(const Vec3& rhs);
		Vec3& operator-=(const Vec3& rhs);
		Vec3& operator*=(const Vec3& rhs);

		Vec3& operator+=(const T& rhs);
		Vec3& operator-=(const T& rhs);
		Vec3& operator*=(const T& rhs);
		Vec3& operator/=(const T& rhs);

		T operator[](unsigned i) const;

		// Attributes
		T x;
		T y;
		T z;
	};

	template <typename T>
	Vec3<T>::Vec3() {
		x = 0;
		y = 0;
		z = 0;
	}

	template <typename T>
	Vec3<T>::Vec3(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	template <typename T>
	Vec3<T>::Vec3(const Vec2<T>& rhs, T z)
	{
		x = rhs.x;
		y = rhs.y;
		this->z = z;
	}

	template <typename T>
	Vec3<T>::Vec3(const Vec3& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
	}

	template <typename T>
	Vec3<T>::Vec3(const Vec4<T>& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
	}


	template <typename T>
	Vec3<T>::~Vec3() {
	}

	template <typename T>
	T Vec3<T>::Sum() const {
		return x + y + z;
	}

	template <typename T>
	double Vec3<T>::Length() const {
		return std::sqrt(double(x)*double(x) + double(y)*double(y) + double(z) * double (z));
	}

	template <typename T>
	void Vec3<T>::Normalize() {
		const auto length = Length();
		x = x / length;
		y = y / length;
		z = z / length;
	}

	template <typename T>
	bool Vec3<T>::IsOrthogonal(const Vec3& Q) const {
		return Dot(*this, Q) == 0 ? true : false;
	}

	template <typename T>
	Vec3<T>& Vec3<T>::operator= (const Vec3& rhs) {
		if (this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
		}
		return *this;
	}

	template <typename T>
	Vec3<T>& Vec3<T>::operator+= (const Vec3& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	template <typename T>
	Vec3<T>& Vec3<T>::operator-= (const Vec3& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	template <typename T>
	Vec3<T>& Vec3<T>::operator*= (const Vec3& rhs) {
		Vec3<T> P = *this;

		x = P.y * rhs.z - P.z * rhs.y;
		y = P.z * rhs.x - P.x * rhs.z;
		z = P.x * rhs.y - P.y * rhs.x;
		return *this;
	}

	template <typename T>
	Vec3<T>& Vec3<T>::operator+= (const T& rhs) {
		x += rhs;
		y += rhs;
		z += rhs;
		return *this;
	}

	template <typename T>
	Vec3<T>& Vec3<T>::operator-= (const T& rhs) {
		x -= rhs;
		y -= rhs;
		z -= rhs;
		return *this;
	}

	template <typename T>
	Vec3<T>& Vec3<T>::operator*= (const T& rhs) {
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	template <typename T>
	Vec3<T>& Vec3<T>::operator/= (const T& rhs) {
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	template <typename T>
	T Vec3<T>::operator[] (unsigned i) const {
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			throw std::out_of_range("Index out of range");;
		}
	}

	typedef Vec3<int> Vec3i;
	typedef Vec3<unsigned> Vec3u;
	typedef Vec3<float> Vec3f;
	typedef Vec3<double> Vec3d;


	//Stream operator
	template <typename T>
	std::ostream& operator<<(std::ostream& out, const Vec3<T>& Vec3)
	{
		return out << Vec3.x << ';' << Vec3.y << ';' << Vec3.z;
	}

	// Relational operators 
	template <typename T>
	bool operator==(const Vec3<T>& lhs, const Vec3<T>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
	}

	template <typename T>
	bool operator!=(const Vec3<T>& lhs, const Vec3<T>& rhs)
	{
		return !(lhs == rhs);
	}

	/**
	* Compute the dot product of two Vec3 P and Q.
	* Also called the inner product or the scalar product.
	*/
	template <typename T>
	T Dot(const Vec3<T>& P, const Vec3<T>& Q)
	{
		return P.x * Q.x + P.y * Q.y + P.z * Q.z;
	}

	/**
	* Projection of a vector P onto a vector Q
	* \details A projection of a vector P on another one
	*	means that it will be "flattened" on the other vector.
	*	The formula is : (P.Q / ||Q||) * Q/||Q||
	*	Where (P.Q / ||Q||) is the length of the projection of P
	* \image html <file>
	*/
	template <typename T>
	Vec3<T> Proj(const Vec3<T>& P, const Vec3<T>& Q)
	{
		return (Dot(P, Q) / pow(Q.Length(), 2)) * Q;
	}

	/**
	* Component of P perpendiculare to Q
	*/
	template <typename T>
	Vec3<T> Perp(const Vec3<T>& P, const Vec3<T>& Q)
	{
		return P - Proj(P, Q);
	}

	// Operators
	template <typename T>
	Vec3<T> operator+ (Vec3<T> lhs, const Vec3<T>& rhs) {
		return lhs += rhs;
	}

	template <typename T>
	Vec3<T> operator- (Vec3<T> lhs, const Vec3<T>& rhs) {
		return lhs -= rhs;
	}

	template <typename T>
	Vec3<T> operator* (Vec3<T> lhs, const Vec3<T>& rhs) {
		return lhs *= rhs;
	}


	template <typename T>
	Vec3<T> operator+ (Vec3<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs += rhs;
	}

	template <typename T>
	Vec3<T> operator- (Vec3<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs -= rhs;
	}

	template <typename T>
	Vec3<T> operator* (Vec3<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs *= rhs;
	}

	template <typename T>
	Vec3<T> operator/ (Vec3<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs /= rhs;
	}

	template <typename T>
	Vec3<T> operator+ (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Vec3<T> lhs) {
		return lhs += rhs;
	}

	template <typename T>
	Vec3<T> operator- (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Vec3<T> lhs) {
		return lhs -= rhs;
	}

	template <typename T>
	Vec3<T> operator* (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Vec3<T> lhs) {
		return lhs *= rhs;
	}

	template <typename T>
	Vec3<T> operator/ (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Vec3<T> lhs) {
		return lhs /= rhs;
	}
}
