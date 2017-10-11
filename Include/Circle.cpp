#include "Circle.hpp"

Math::Circle::Circle (Math::Vec2d& p1, Math::Vec2d& p2, Math::Vec2d& p3)
	: mP1(p1), mP2(p2), mP3(p3)
{
}

bool Math::Circle::IsPointInside (const Math::Vec2d& point) const
{
	return Dot((mP2 - mP1) * (mP3 - mP1), mP1 - point) < 0;
}
