#pragma once
#include <queue>
#include <unordered_map>
#include <cmath>

#include "../../../Dodge/Coord.h"
#include "Movement.h"

// ��������� ���� ��� A*
struct Node {
    std::shared_ptr<Movement> movement;
    float gCost; // ��������� ���� �� ��������� �����
    float hCost; // ������������� ��������� �� ����
    float fCost() const { return gCost + hCost; } // ����� ���������
    std::shared_ptr<Node> parent;

    Node(std::shared_ptr<Movement> movement,
        float gCost, float hCost, 
        std::shared_ptr<Node> parent = nullptr
    )
        : movement(movement), gCost(gCost), hCost(hCost), parent(parent) {}

    //~Node() {
    //    delete parent;
    //};
};

// ��������� ����� ��� ������������ �������
struct CompareNodes {
    bool operator()(std::shared_ptr<Node> a, std::shared_ptr<Node> b) { 
        return a->fCost() > b->fCost(); 
    }
};