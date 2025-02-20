#pragma once
#include <memory>
#include "RenderInstance.h"

#include "../Coord.h"
#include "../IGameObject.h"

extern std::vector<unsigned int> defaultIndicies1;

class RectRenderInstance :
    public RenderInstance
{
    Coord vertex1;
    Coord vertex2;

    std::shared_ptr<Material> material;

    void GenerateVertices() override;
public:
    RectRenderInstance();
    RectRenderInstance(Coord vertex1, Coord vertex2);
    RectRenderInstance(std::shared_ptr<Material> material);
    RectRenderInstance(unsigned int VAO, unsigned int VBO, unsigned int EBO);

    static void InitQuads(
        unsigned int& VAO, unsigned int& VBO, unsigned int& EBO,
        std::vector<float>& vertices, std::vector<unsigned int>& indices = defaultIndicies1
    );

    void Initialize() override;

	void SetVertexes(Coord vertex1, Coord vertex2);

    const Coord& GetVertex1();
    void SetVertex1(Coord vertex1);

    const Coord& GetVertex2();
    void SetVertex2(Coord vertex2);

    std::weak_ptr<Material> GetMaterial();

    void SetMaterial(std::shared_ptr<Material> material);
    void MoveMaterial(std::shared_ptr<Material> material);

    void Render() override;

    bool operator == (RectRenderInstance& other);
};

