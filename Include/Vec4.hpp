/**
 * \file Vec4.hpp
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
#include <stdexcept>
#include <cmath>

template <typename T>
struct Vec2;
template <typename T>
struct Vec3;

namespace Math
{
	template <typename T>
	struct Vec4
	{
		static_assert(std::is_arithmetic<T>::value, "T must be numeric");

		// Constructors
		Vec4(); /// Default constructor
		Vec4(T x, T y, T z, T w); /// Parameterized constructor from 2 arithmetic values 
		Vec4(const Vec2<T>& rhs, T z, T w); /// Parameterized constructor from 2 arithmetic values 
		Vec4(const Vec3<T>& rhs, T w); /// Parameterized constructor from 2 arithmetic values 
		Vec4(const Vec4& rhs); /// Copy constructor from Vec4
		~Vec4();

		// Functions 
		T Sum() const; /// Sum the components of the vector.
		double Length() const; /// Length of the vector, also called the magnitude.
		void Normalize(); /// Normalize the vector.

		bool IsOrthogonal(const Vec4& Q) const;

		// Arithmetic operators
		Vec4& operator=(const Vec4& rhs); /// Copy assignement

		Vec4& operator+=(const Vec4& rhs);
		Vec4& operator-=(const Vec4& rhs);

		Vec4& operator+=(const T& rhs);
		Vec4& operator-=(const T& rhs);
		Vec4& operator*=(const T& rhs);
		Vec4& operator/=(const T& rhs);

		T operator[](unsigned i) const; // accessor

		// Attributes
		T x;
		T y;
		T z;
		T w;
	};

	template <typename T>
	Vec4<T>::Vec4() {
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	template <typename T>
	Vec4<T>::Vec4(T x, T y, T z, T w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	template <typename T>
	Vec4<T>::Vec4(const Vec2<T>& rhs, T z, T w)
	{
		x = rhs.x;
		y = rhs.y;
		this->z = z;
		this->w = w;
	}

	template <typename T>
	Vec4<T>::Vec4(const Vec3<T>& rhs, T w)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		this->w = w;
	}

	template <typename T>
	Vec4<T>::Vec4(const Vec4& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
	}


	template <typename T>
	Vec4<T>::~Vec4() {
	}

	template <typename T>
	T Vec4<T>::Sum() const {
		return x + y + z + w;
	}

	template <typename T>
	double Vec4<T>::Length() const {
		return std::sqrt(double(x)*double(x) + double(y)*double(y) + double(z) * double(z) + double(w) * double(w));
	}

	template <typename T>
	void Vec4<T>::Normalize() {
		const auto length = Length();
		x = x / length;
		y = y / length;
		z = z / length;
		w = w / length;
	}

	template <typename T>
	bool Vec4<T>::IsOrthogonal(const Vec4& Q) const {
		return Dot(*this, Q) == 0 ? true : false;
	}

	template <typename T>
	Vec4<T>& Vec4<T>::operator= (const Vec4& rhs) {
		if (this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;
		}
		return *this;
	}

	template <typename T>
	Vec4<T>& Vec4<T>::operator+= (const Vec4& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	template <typename T>
	Vec4<T>& Vec4<T>::operator-= (const Vec4& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	template <typename T>
	Vec4<T>& Vec4<T>::operator+= (const T& rhs) {
		x += rhs;
		y += rhs;
		z += rhs;
		w += rhs;
		return *this;
	}

	template <typename T>
	Vec4<T>& Vec4<T>::operator-= (const T& rhs) {
		x -= rhs;
		y -= rhs;
		z -= rhs;
		w -= rhs;
		return *this;
	}

	template <typename T>
	Vec4<T>& Vec4<T>::operator*= (const T& rhs) {
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return *this;
	}

	template <typename T>
	Vec4<T>& Vec4<T>::operator/= (const T& rhs) {
		x /= rhs;
		y /= rhs;
		z /= rhs;
		w /= rhs;
		return *this;
	}

	template <typename T>
	T Vec4<T>::operator[] (unsigned i) const { 
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		default: 
			throw std::out_of_range("Index out of range");;
		}
	}

	typedef Vec4<int> Vec4i;
	typedef Vec4<unsigned> Vec4u;
	typedef Vec4<float> Vec4f;
	typedef Vec4<double> Vec4d;


	//Stream operator
	template <typename T>
	std::ostream& operator<<(std::ostream& out, const Vec4<T>& Vec4)
	{
		return out << Vec4.x << ';' << Vec4.y << ';' << Vec4.z << ';' << Vec4.w;
	}

	// Relational operators 
	template <typename T>
	bool operator==(const Vec4<T>& lhs, const Vec4<T>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
	}

	template <typename T>
	bool operator!=(const Vec4<T>& lhs, const Vec4<T>& rhs)
	{
		return !(lhs == rhs);
	}

	/**
	* Compute the dot product of two Vec4 P and Q.
	* Also called the inner product or the scalar product.
	*/
	template <typename T>
	T Dot(const Vec4<T>& P, const Vec4<T>& Q)
	{
		return P.x * Q.x + P.y * Q.y + P.z * Q.z + P.w * Q.w;
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
	Vec4<T> Proj(const Vec4<T>& P, const Vec4<T>& Q)
	{
		return (Dot(P, Q) / pow(Q.Length(), 2)) * Q;
	}

	/**
	* Component of P perpendiculare to Q
	*/
	template <typename T>
	Vec4<T> Perp(const Vec4<T>& P, const Vec4<T>& Q)
	{
		return P - Proj(P, Q);
	}

	// Operators
	template <typename T>
	Vec4<T> operator+ (Vec4<T> lhs, const Vec4<T>& rhs) {
		return lhs += rhs;
	}

	template <typename T>
	Vec4<T> operator- (Vec4<T> lhs, const Vec4<T>& rhs) {
		return lhs -= rhs;
	}

	template <typename T>
	Vec4<T> operator* (Vec4<T> lhs, const Vec4<T>& rhs) {
		return lhs *= rhs;
	}


	template <typename T>
	Vec4<T> operator+ (Vec4<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs += rhs;
	}

	template <typename T>
	Vec4<T> operator- (Vec4<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs -= rhs;
	}

	template <typename T>
	Vec4<T> operator* (Vec4<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs *= rhs;
	}

	template <typename T>
	Vec4<T> operator/ (Vec4<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs /= rhs;
	}

	template <typename T>
	Vec4<T> operator+ (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Vec4<T> lhs) {
		return lhs += rhs;
	}

	template <typename T>
	Vec4<T> operator- (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Vec4<T> lhs) {
		return lhs -= rhs;
	}

	template <typename T>
	Vec4<T> operator* (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Vec4<T> lhs) {
		return lhs *= rhs;
	}

	template <typename T>
	Vec4<T> operator/ (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Vec4<T> lhs) {
		return lhs /= rhs;
	}
}
