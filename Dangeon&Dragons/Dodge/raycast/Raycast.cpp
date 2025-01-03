#include "Raycast.h"
#include "../GameObjects.h"

IGameObject* Raycast::RaycastFirst(Ray* ray, bool debug, Color debugColor)
{
	if (debug) {
		drawRay(ray, debugColor);
	}

	for (IGameObject*& object : *GameObjects::GetAll()) {
		//if (object->GetCollision()->GetRootId() == 223) {
		//	if (IsObjectBetween(ray, object)) {
		//		return object;
		//	}
		//	continue;
		//}
		if (IsObjectBetween(ray, object)) {
			return object;
		}
	}
	return nullptr;
}

std::vector<IGameObject*> Raycast::RaycastAll(Ray* ray, bool debug, Color debugColor)
{
	if (debug) {
		drawRay(ray, debugColor);
	}

	std::vector<IGameObject*> result;
	for (IGameObject*& object : *GameObjects::GetAll()) {
		if (IsPointBetween(ray, object->GetPos())) {
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

	// �������� �� �����������
	if (tMax < 0 || tMin > tMax) {
		return false; // ��� �� ���������� ������
	}

	// ��������� ������ ���� (�����������)
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
		return false; // ������������� ������ ����� ���� �� 3 �������
	}

	for (size_t i = 0; i < n; ++i) {
		Coord v1 = polygon[i];
		Coord v2 = polygon[(i + 1) % n];

		// ��������� ����������� ���� � ������ ������ ��������������
		double det = (v2.X - v1.X) * rayDir.Y - (v2.Y - v1.Y) * rayDir.X;
		if (std::abs(det) < 1e-9) {
			continue; // ��� ���������� �����
		}

		double t = ((rayOrigin.X - v1.X) * (v2.Y - v1.Y) - (rayOrigin.Y - v1.Y) * (v2.X - v1.X)) / det;
		double u = ((rayOrigin.X - v1.X) * rayDir.Y - (rayOrigin.Y - v1.Y) * rayDir.X) / det;

		if (t >= 0 && u >= 0 && u <= 1) {
			return true; // ����������� �������
		}
	}

	return false; // ����������� ���
}
