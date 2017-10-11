/**
 * \file Vec2.hpp
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
struct Vec3;
template <typename T>
struct Vec4;

namespace Math
{
	template <typename T>
	struct Vec2
	{
		static_assert(std::is_arithmetic<T>::value, "T must be numeric");

		// Constructors
		Vec2(); /// Default constructor
		Vec2(T x, T y); /// Parameterized constructor from 2 arithmetic values 
		Vec2(const Vec2& rhs); /// Copy constructor from Vec2
		explicit Vec2(const Vec3<T>& rhs); /// Copy constructor from Vec3
		explicit Vec2(const Vec4<T>& rhs); /// Copy constructor from Vec4
		~Vec2();

		// Functions 
		T Sum() const; /// Sum the components of the vector.
		double Length() const; /// Length of the vector, also called the magnitude.
		void Normalize(); /// Normalize the vector.

		bool IsOrthogonal(const Vec2& Q) const;

		// Arithmetic operators
		Vec2& operator=(const Vec2& rhs); /// Copy assignement

		Vec2& operator+=(const Vec2& rhs);
		Vec2& operator-=(const Vec2& rhs);
		Vec2& operator*=(const Vec2& rhs);

		Vec2& operator+=(const T& rhs);
		Vec2& operator-=(const T& rhs);
		Vec2& operator*=(const T& rhs);
		Vec2& operator/=(const T& rhs);

		T operator[](unsigned i) const;
		// Attributes
		T x;
		T y;
	};

	template <typename T>
	Vec2<T>::Vec2() {
		x = 0;
		y = 0;
	}

	template <typename T>
	Vec2<T>::Vec2(T x, T y) {
		this->x = x;
		this->y = y;
	}

	template <typename T>
	Vec2<T>::Vec2(const Vec2& rhs) {
		x = rhs.x;
		y = rhs.y;
	}

	template <typename T>
	Vec2<T>::Vec2(const Vec3<T>& rhs) {
		x = rhs.x;
		y = rhs.y;
	}

	template <typename T>
	Vec2<T>::Vec2 (const Vec4<T>& rhs) {
		x = rhs.x;
		y = rhs.y;
	}

	template <typename T>
	Vec2<T>::~Vec2() {
	}

	template <typename T>
	T Vec2<T>::Sum() const {
		return x + y;
	}

	template <typename T>
	double Vec2<T>::Length() const {
		return std::sqrt(double(x)*double(x) + double(y)*double(y));
	}

	template <typename T>
	void Vec2<T>::Normalize() {
		auto length = Length();
		x = x / length;
		y = y / length;
	}

	template <typename T>
	bool Vec2<T>::IsOrthogonal(const Vec2& Q) const {
		return Dot(*this, Q) == 0 ? true : false;
	}

	template <typename T>
	Vec2<T>& Vec2<T>::operator= (const Vec2& rhs) {
		if (this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
		}
		return *this;
	}

	template <typename T>
	Vec2<T>& Vec2<T>::operator+= (const Vec2& rhs) {
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	template <typename T>
	Vec2<T>& Vec2<T>::operator-= (const Vec2& rhs) {
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}


	template <typename T>
	Vec2<T>& Vec2<T>::operator*= (const Vec2& rhs)
	{
		return x * rhs.x - y * rhs.y;
	}

	template <typename T>
	Vec2<T>& Vec2<T>::operator+= (const T& rhs) {
		x += rhs;
		y += rhs;
		return *this;
	}

	template <typename T>
	Vec2<T>& Vec2<T>::operator-= (const T& rhs) {
		x -= rhs;
		y -= rhs;
		return *this;
	}

	template <typename T>
	Vec2<T>& Vec2<T>::operator*= (const T& rhs) {
		x *= rhs;
		y *= rhs;
		return *this;
	}

	template <typename T>
	Vec2<T>& Vec2<T>::operator/= (const T& rhs) {
		x /= rhs;
		y /= rhs;
		return *this;
	}

	template <typename T>
	T Vec2<T>::operator[] (unsigned i) const {
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		default:
			throw std::out_of_range("Index out of range");;
		}
	}

	typedef Vec2<int> Vec2i;
	typedef Vec2<unsigned> Vec2u;
	typedef Vec2<float> Vec2f;
	typedef Vec2<double> Vec2d;


	//Stream operator
	template <typename T>
	std::ostream& operator<<(std::ostream& out, const Vec2<T>& vec2)
	{
		return out << vec2.x << ';' << vec2.y;
	}

	// Relational operators 
	template <typename T>
	bool operator==(const Vec2<T>& lhs, const Vec2<T>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	template <typename T>
	bool operator!=(const Vec2<T>& lhs, const Vec2<T>& rhs)
	{
		return !(lhs == rhs);
	}

	/**
	 * Compute the dot product of two Vec2 P and Q.
	 * Also called the inner product or the scalar product.
	 */
	template <typename T>
	T Dot(const Vec2<T>& P, const Vec2<T>& Q)
	{
		return P.x * Q.x + P.y * Q.y;
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
	Vec2<T> Proj(const Vec2<T>& P, const Vec2<T>& Q)
	{
		return (Dot(P, Q) / pow(Q.Length(), 2)) * Q;
	}

	/**
	 * Component of P perpendiculare to Q
	 */
	template <typename T>
	Vec2<T> Perp(const Vec2<T>& P, const Vec2<T>& Q)
	{
		return P - Proj(P, Q);
	}

	// Operators
	template <typename T>
	Vec2<T> operator+ (Vec2<T> lhs, const Vec2<T>& rhs) {
		return lhs += rhs;
	}

	template <typename T>
	Vec2<T> operator- (Vec2<T> lhs, const Vec2<T>& rhs) {
		return lhs -= rhs;
	}

	template <typename T>
	Vec2<T> operator* (Vec2<T> lhs, const Vec2<T>& rhs) {
		return lhs *= rhs;
	}

	template <typename T>
	Vec2<T> operator+ (Vec2<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs += rhs;
	}

	template <typename T>
	Vec2<T> operator- (Vec2<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs -= rhs;
	}

	template <typename T>
	Vec2<T> operator* (Vec2<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs *= rhs;
	}

	template <typename T>
	Vec2<T> operator/ (Vec2<T> lhs, const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs) {
		return lhs /= rhs;
	}
	
	template <typename T>
	Vec2<T> operator+ (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Vec2<T> lhs) {
		return lhs += rhs;
	}

	template <typename T>
	Vec2<T> operator- (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Vec2<T> lhs) {
		return lhs -= rhs;
	}

	template <typename T>
	Vec2<T> operator* (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Vec2<T> lhs) {
		return lhs *= rhs;
	}

	template <typename T>
	Vec2<T> operator/ (const typename std::enable_if<std::is_arithmetic<T>::value, T>::type& rhs, Vec2<T> lhs) {
		return lhs /= rhs;
	}
}