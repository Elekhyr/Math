/**
 * \file BezierCurve.hpp
 * \brief todo
 * \author Thomas Margier
 * \version 1.0
 * \date 04/10/17
 * \copyright Copyright (c) 2017 Thomas Margier
 *  This file is licensed under the MIT License, see https://opensource.org/licenses/MIT
 */

#pragma once
#include <vector>
#include "Vec4.hpp" //todo : fix issue when including vec3 before vec4
#include "Vec3.hpp"

namespace Math
{
	struct BezierCurve
	{
		static std::vector<Vec3d> ComputeWithDeCasteljau(const std::vector<Vec4d>& controlPoints, unsigned nbPoints);
	};
}
