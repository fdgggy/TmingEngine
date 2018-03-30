
//= INCLUDES ================
#include "BoundingBox.h"
//#include "../Graphics/Mesh.h"
#include "MathHelper.h"
#include "Matrix.h"
//===========================

namespace TmingEngine::Math
{
	const BoundingBox BoundingBox::Zero(Vector3::Zero, Vector3::Zero);

	BoundingBox::BoundingBox()
	{
		min = Vector3::Infinity;
		max = Vector3::InfinityNeg;
	}

	BoundingBox::BoundingBox(const Vector3& min, const Vector3& max)
	{
		this->min = min;
		this->max = max;
	}

	BoundingBox::~BoundingBox()
	{
	}

	//void BoundingBox::ComputeFromVertices(const std::vector<VertexPosTexTBN>& vertices)
	//{
	//	min = Vector3::Infinity;
	//	max = Vector3::InfinityNeg;

	//	for (const auto& vertex : vertices)
	//	{
	//		max.x = Max(max.x, vertex.position.x);
	//		max.y = Max(max.y, vertex.position.y);
	//		max.z = Max(max.z, vertex.position.z);

	//		min.x = Min(min.x, vertex.position.x);
	//		min.y = Min(min.y, vertex.position.y);
	//		min.z = Min(min.z, vertex.position.z);
	//	}
	//}

	Intersection BoundingBox::IsInside(const Vector3& point) const
	{
		if (point.x < min.x || point.x > max.x ||
			point.y < min.y || point.y > max.y ||
			point.z < min.z || point.z > max.z)
		{
			return Outside;
		}
		else
		{
			return Inside;
		}
	}

	Intersection BoundingBox::IsInside(const BoundingBox& box) const
	{
		if (box.max.x < min.x || box.min.x > max.x ||
			box.max.y < min.y || box.min.y > max.y ||
			box.max.z < min.z || box.min.z > max.z)
		{
			return Outside;
		}
		else if (
			box.min.x < min.x || box.max.x > max.x ||
			box.min.y < min.y || box.max.y > max.y ||
			box.min.z < min.z || box.max.z > max.z)
		{
			return Intersects;
		}
		else
		{
			return Inside;
		}
	}

	BoundingBox BoundingBox::Transformed(const Matrix& transform)
	{
		Vector3 newCenter = transform * GetCenter();
		Vector3 oldEdge = GetSize() * 0.5f;
		Vector3 newEdge = Vector3
		(
			Abs(transform.m00) * oldEdge.x + Abs(transform.m10) * oldEdge.y + Abs(transform.m20) * oldEdge.z,
			Abs(transform.m01) * oldEdge.x + Abs(transform.m11) * oldEdge.y + Abs(transform.m21) * oldEdge.z,
			Abs(transform.m02) * oldEdge.x + Abs(transform.m12) * oldEdge.y + Abs(transform.m22) * oldEdge.z
		);

		return BoundingBox(newCenter - newEdge, newCenter + newEdge);
	}

	void BoundingBox::Merge(const BoundingBox& box)
	{
		if (box.min.x < min.x) min.x = box.min.x;
		if (box.min.y < min.y) min.y = box.min.y;
		if (box.min.z < min.z) min.z = box.min.z;
		if (box.max.x > max.x) max.x = box.max.x;
		if (box.max.y > max.y) max.y = box.max.y;
		if (box.max.z > max.z) max.z = box.max.z;
	}
}