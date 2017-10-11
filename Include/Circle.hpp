/**
 * \file Circle.hpp
 * \brief todo
 * \author Thomas Margier
 * \version 1.0
 * \date 04/10/17
 * \copyright Copyright (c) 2017 Thomas Margier
 *  This file is licensed under the MIT License, see https://opensource.org/licenses/MIT
 */
#pragma once
#include "Vec2.hpp"

namespace Math
{
	class Circle
	{
	public:
		Circle(Math::Vec2d& p1, Math::Vec2d& p2, Math::Vec2d& p3);
		bool IsPointInside(const Math::Vec2d& point) const;

	private:
		Vec2d mP1;
		Vec2d mP2;
		Vec2d mP3;
	};
}
