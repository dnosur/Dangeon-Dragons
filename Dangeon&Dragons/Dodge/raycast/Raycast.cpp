#include "Raycast.h"
#include "../GameObjects.h"

std::weak_ptr<IGameObject> Raycast::RaycastFirst(std::unique_ptr<Ray> ray, bool debug, Color debugColor)
{
	if (debug) {
		drawRay(ray, debugColor);
	}

	for (std::weak_ptr<IGameObject> object : *GameObjects::GetAll()) {
		if (!object.lock()) {
			continue;
		}

		if (IsObjectBetween(ray, object)) {
			return object;
		}
	}
	return std::shared_ptr<IGameObject>(nullptr);
}

std::vector<std::weak_ptr<IGameObject>> Raycast::RaycastAll(std::unique_ptr<Ray> ray, bool debug, Color debugColor)
{
	if (debug) {
		drawRay(ray, debugColor);
	}

	std::vector<std::weak_ptr<IGameObject>> result;
	for (std::shared_ptr<IGameObject>& object : *GameObjects::GetAll()) {
		if (!object.get()) {
			continue;
		}

		if (IsPointBetween(ray, object.get()->GetPos())) {
			result.push_back(object);
		}
	}

	return result;
}

bool Raycast::CheckRayAABBIntersection(
	const Coord& rayOrigin, const Coord& rayDir, float rayWidth,
	double objLeft, double objRight, double objBottom, double objTop)
{
	double t1 = (objLeft - rayOrigin.X) / rayDir.X;
	double t2 = (objRight - rayOrigin.X) / rayDir.X;
	double t3 = (objBottom - rayOrigin.Y) / rayDir.Y;
	double t4 = (objTop - rayOrigin.Y) / rayDir.Y;

	double tMin = std::max(std::min(t1, t2), std::min(t3, t4));
	double tMax = std::min(std::max(t1, t2), std::max(t3, t4));

	// Ïðîâåðêà íà ïåðåñå÷åíèå
	if (tMax < 0 || tMin > tMax) {
		return false; // Ëó÷ íå ïåðåñåêàåò îáúåêò
	}

	// Ó÷èòûâàåì øèðèíó ëó÷à (îïöèîíàëüíî)
	if (rayWidth > 0) {
		double halfWidth = rayWidth / 2.0;

		double expandedLeft = objLeft - halfWidth;
		double expandedRight = objRight + halfWidth;
		double expandedBottom = objBottom - halfWidth;
		double expandedTop = objTop + halfWidth;

		t1 = (expandedLeft - rayOrigin.X) / rayDir.X;
		t2 = (expandedRight - rayOrigin.X) / rayDir.X;
		t3 = (expandedBottom - rayOrigin.Y) / rayDir.Y;
		t4 = (expandedTop - rayOrigin.Y) / rayDir.Y;

		tMin = std::max(std::min(t1, t2), std::min(t3, t4));
		tMax = std::min(std::max(t1, t2), std::max(t3, t4));

		if (tMax < 0 || tMin > tMax) {
			return false;
		}
	}

	return true;
}

bool Raycast::CheckRayPolygonIntersection(
	const Coord& rayOrigin, const Coord& rayDir,
	const std::vector<Coord>& polygon)
{
	size_t n = polygon.size();
	if (n < 3) {
		return false; // Ìíîãîóãîëüíèê äîëæåí èìåòü õîòÿ áû 3 âåðøèíû
	}

	for (size_t i = 0; i < n; ++i) {
		Coord v1 = polygon[i];
		Coord v2 = polygon[(i + 1) % n];

		// Âû÷èñëÿåì ïåðåñå÷åíèå ëó÷à ñ êàæäûì ðåáðîì ìíîãîóãîëüíèêà
		double det = (v2.X - v1.X) * rayDir.Y - (v2.Y - v1.Y) * rayDir.X;
		if (std::abs(det) < 1e-9) {
			continue; // Ëó÷ ïàðàëëåëåí ðåáðó
		}

		double t = ((rayOrigin.X - v1.X) * (v2.Y - v1.Y) - (rayOrigin.Y - v1.Y) * (v2.X - v1.X)) / det;
		double u = ((rayOrigin.X - v1.X) * rayDir.Y - (rayOrigin.Y - v1.Y) * rayDir.X) / det;

		if (t >= 0 && u >= 0 && u <= 1) {
			return true; // Ïåðåñå÷åíèå íàéäåíî
		}
	}

	return false; // Ïåðåñå÷åíèé íåò
}