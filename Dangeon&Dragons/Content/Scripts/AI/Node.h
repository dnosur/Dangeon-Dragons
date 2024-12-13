#pragma once
#include <queue>
#include <unordered_map>
#include <cmath>

#include "../../../Dodge/Coord.h"
#include "Movement.h"

// ��������� ���� ��� A*
struct Node {
    Movement* movement;
    float gCost; // ��������� ���� �� ��������� �����
    float hCost; // ������������� ��������� �� ����
    float fCost() const { return gCost + hCost; } // ����� ���������
    Node* parent;

    Node(Movement* movement, float gCost, float hCost, Node* parent = nullptr)
        : movement(movement), gCost(gCost), hCost(hCost), parent(parent) {}

    ~Node() {
        delete parent;
    };
};

// ��������� ����� ��� ������������ �������
struct CompareNodes {
    bool operator()(Node* a, Node* b) { return a->fCost() > b->fCost(); }
};