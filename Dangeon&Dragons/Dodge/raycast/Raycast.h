#pragma once

#include <vector>
#include "../IGameObject.h"

#include "../Figures.h"


static class Raycast
{
public:
	static std::weak_ptr<IGameObject> RaycastFirst(std::unique_ptr<Ray>& ray, bool debug = false, Color debugColor = Color(1, 0, 0));
	static std::vector<std::weak_ptr<IGameObject>> RaycastAll(std::unique_ptr<Ray>&, bool debug = false, Color debugColor = Color(1, 0, 0));

	template<typename T = IGameObject*>
	static T* RaycastFirstDynamic(Ray* ray, bool debug = false, Color debugColor = Color(1, 0, 0));

	template<typename T = IGameObject*>
	static std::vector<T*> RaycastAllDynamic(Ray* ray, bool debug = false, Color debugColor = Color(1, 0, 0));

	//Helpers
	// Проверка пересечения луча с AABB
	static bool CheckRayAABBIntersection(
		const Coord& rayOrigin, const Coord& rayDir, float rayWidth,
		double objLeft, double objRight, double objBottom, double objTop
	);

	// Проверка пересечения луча с многоугольником
	static bool CheckRayPolygonIntersection(
		const Coord& rayOrigin, const Coord& rayDir, 
		const std::vector<Coord>& polygon
	);
};

template<typename T>
inline T* Raycast::RaycastFirstDynamic(Ray* ray, bool debug, Color debugColor)
{
	if (debug) {
		drawRay(ray, debugColor);
	}

	return dynamic_cast<T*>(Raycast::RaycastFirst(ray));
}

template<typename T>
inline std::vector<T*> Raycast::RaycastAllDynamic(Ray* ray, bool debug, Color debugColor)
{
	if (debug) {
		drawRay(ray, debugColor);
	}

	return dynamic_cast<std::vector<T*>>(Raycast::RaycastAll(ray));
}
