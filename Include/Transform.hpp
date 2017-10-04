/**
 * \file Transform.hpp
 * \brief todo
 * \author Elekhyr
 * \version 1.0
 * \date 19/09/2017
 * \copyright Copyright (c) 2017 Thomas Margier
 *  This file is licensed under the MIT License, see https://opensource.org/licenses/MIT
 */
#pragma once
#include "Mat4.hpp"
#include <stdexcept>
#include <cmath>

namespace Math
{
	template<typename T>
	class Transform
	{
	public:
		Transform() = delete;
		Transform(const Transform&) = delete;
		Transform(const Transform&&) = delete;
		~Transform() = delete;

		static Mat4<T> Rotation(const T& angle, const Vec3<T>& axis);
		static Mat4<T> Translation(const Vec3<T>& vec3);		
		static Mat4<T> Scaling(const Vec3<T>& vec3);

		static Mat4<T>& Rotate(const Mat4<T>& mat4, const T& angle, const Vec3<T>& axis);
		static Mat4<T>& RotateX(const Mat4<T>& mat4, const T& angle);
		static Mat4<T>& RotateY(const Mat4<T>& mat4, const T& angle);
		static Mat4<T>& RotateZ(const Mat4<T>& mat4, const T& angle);

		static Mat4<T>& Translate(const Mat4<T>& mat4, const Vec3<T>& vec3);
		static Mat4<T>& TranslateX(const Mat4<T>& mat4, const T& x);
		static Mat4<T>& TranslateY(const Mat4<T>& mat4, const T& y);
		static Mat4<T>& TranslateZ(const Mat4<T>& mat4, const T& z);

		static Mat4<T>& Scale(const Mat4<T>& mat4, const Vec3<T>& vec3);
		static Mat4<T>& ScaleX(const Mat4<T>& mat4, const T& x);
		static Mat4<T>& ScaleY(const Mat4<T>& mat4, const T& y);
		static Mat4<T>& ScaleZ(const Mat4<T>& mat4, const T& z);
	};

	template <typename T>
	Mat4<T> Transform<T>::Rotation (const T& angle, const Vec3<T>& axis) {
		
	}

	template <typename T>
	Mat4<T> Transform<T>::Translation (const Vec3<T>& vec3) {
	}

	template <typename T>
	Mat4<T> Transform<T>::Scaling (const Vec3<T>& vec3) {
		return Mat4<T>(
		);
	}

	template <typename T>
	Mat4<T>& Transform<T>::Rotate (const Mat4<T>& mat4, const T& angle, const Vec3<T>& axis) {
	}

	template <typename T>
	Mat4<T>& Transform<T>::RotateX (const Mat4<T>& mat4, const T& angle) {
	}

	template <typename T>
	Mat4<T>& Transform<T>::RotateY (const Mat4<T>& mat4, const T& angle) {
	}

	template <typename T>
	Mat4<T>& Transform<T>::RotateZ (const Mat4<T>& mat4, const T& angle) {
	}

	template <typename T>
	Mat4<T>& Transform<T>::Translate (const Mat4<T>& mat4, const Vec3<T>& vec3) {
	}

	template <typename T>
	Mat4<T>& Transform<T>::TranslateX (const Mat4<T>& mat4, const T& x) {
	}

	template <typename T>
	Mat4<T>& Transform<T>::TranslateY (const Mat4<T>& mat4, const T& y) {
	}

	template <typename T>
	Mat4<T>& Transform<T>::TranslateZ (const Mat4<T>& mat4, const T& z) {
	}

	template <typename T>
	Mat4<T>& Transform<T>::Scale (const Mat4<T>& mat4, const Vec3<T>& vec3) {
	}

	template <typename T>
	Mat4<T>& Transform<T>::ScaleX (const Mat4<T>& mat4, const T& x) {
	}

	template <typename T>
	Mat4<T>& Transform<T>::ScaleY (const Mat4<T>& mat4, const T& y) {
	}

	template <typename T>
	Mat4<T>& Transform<T>::ScaleZ (const Mat4<T>& mat4, const T& z) {
	}
}

