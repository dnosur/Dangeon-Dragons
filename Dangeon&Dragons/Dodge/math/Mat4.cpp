#include "Mat4.h"

Mat4::Mat4()
{
    for (int i = 0; i < 16; i++) elements[i] = 0.0f;
}

Mat4 Mat4::Identity()
{
    Mat4 result;
    for (int i = 0; i < 4; i++) {
        result.elements[i + i * 4] = 1.0f;
    }
    return result;
}

Mat4 Mat4::Translate(const Vec2& position)
{
    Mat4 result = Mat4::Identity();
    result.elements[12] = position.x; // X-координата
    result.elements[13] = position.y; // Y-координата
    return result;
}

Mat4 Mat4::Translate(const Coord& position)
{
    Mat4 result = Mat4::Identity();
    result.elements[12] = position.X; // X-координата
    result.elements[13] = position.Y; // Y-координата
    return result;
}

Mat4 Mat4::Ortho(float left, float right, float bottom, float top)
{
    Mat4 result = Mat4::Identity();
    result.elements[0] = 2.0f / (right - left);           // [0][0]
    result.elements[5] = 2.0f / (top - bottom);           // [1][1]
    result.elements[12] = -(right + left) / (right - left); // [3][0]
    result.elements[13] = -(top + bottom) / (top - bottom); // [3][1]
    return result;
}