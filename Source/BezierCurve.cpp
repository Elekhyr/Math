#include "BezierCurve.hpp"
#include "Vec2.hpp"

std::vector<Math::Vec3d> Math::BezierCurve::ComputeWithDeCasteljau (
	const std::vector<Vec4d>& controlPoints, const unsigned nbPoints)
{
	std::vector<Vec3d> curve(nbPoints + 2);
	curve[0] = Vec3d(controlPoints[0]);
	curve[curve.size() - 1] = Vec3d(controlPoints[controlPoints.size() - 1]);

	std::vector<Vec4d> temp_points(controlPoints.size());
	
	const auto step = 1.0 / (double(nbPoints) + 1.0);
	size_t index = 1;

	for (auto u = step; u < 1 && index < curve.size(); u += step, ++index)
	{
		for (unsigned i = 0; i < controlPoints.size(); ++i)
		{
			temp_points[i] = controlPoints[i].w * controlPoints[i];
			temp_points[i].w = controlPoints[i].w;
		}

		for (unsigned j = 1; j < controlPoints.size(); ++j)
		{
			for (unsigned i = 0; i < controlPoints.size() - j; ++i)
			{
				temp_points[i] = (1 - u) * temp_points[i] + u* temp_points[i + 1];
			}
		}

		curve[index] = Vec3d(temp_points[0]) / temp_points[0].w;
	}

	return move(curve);
}
