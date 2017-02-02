#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include <vector>
#include <map>
#include <list>
using namespace DirectX::SimpleMath;
namespace NGame {
	struct Cluster {
		std::list<int> light, decal, reflection;
	};
	struct KFrustum {
		DirectX::SimpleMath::Plane plane;
		bool isColllided;
	};
	struct KBox {
		DirectX::SimpleMath::Vector3
			a0, a1, a2, a3, 
			b0, b1, b2, b3;
	};
	class Frustum {
	private:
	public:
		Vector3 m_size;
		float m_angle;
		float m_division;
		std::map<int, KBox> m_cubes;
		std::vector<DirectX::SimpleMath::Plane> planesX,planesY,planesZ;
		std::vector<Cluster> m_clusters;

		void init(float angle, float nearDistance, float farDistance, int divisionX, int divisionY, int divisionZ);
		void testPointlight(Vector3 center, float radius);
		bool test(std::pair<int, int> &result,std::vector<Plane> planes, DirectX::SimpleMath::Vector3 center, float radius);
	};
}