﻿#include "Figures.h"
#include "functions.h"

#include "Window.h"

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(.0f, 1.0f, .0f, 1.0f);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++)
    {
        float theta = 2.0f * M_PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawRectangle(float x1, float y1, float x2, float y2)
{
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawLine(Coord a, Coord b, Color color, int lineWidth)
{
    glLineWidth(lineWidth);
    // Âû÷èñëÿåì êîîðäèíàòû
    glColor3f(color.r, color.g, color.b);

    Size windowSize = Window::GetRenderResolution();

    Coord first = Coord(
        2.0f * a.X / windowSize.GetWidth() - 1.0f,
        1.0f - 2.0f * a.Y / windowSize.GetHeight()
    );

    Coord second = Coord(
        2.0f * b.X / windowSize.GetWidth() - 1.0f,
        1.0f - 2.0f * b.Y / windowSize.GetHeight()
    );

    // Ðèñóåì ëèíèþ
    glBegin(GL_LINES);
    glVertex2f(first.X, first.Y);
    glVertex2f(second.X, second.Y);
    glEnd();
}

void drawRay(Ray*& ray, Color& color)
{
    glLineWidth(ray->rayWidth);
    // Âû÷èñëÿåì êîîðäèíàòû
    glColor3f(color.r, color.g, color.b);

    Size windowSize = Window::GetRenderResolution();

    Coord* first = new Coord(
        2.0f * ray->origin->X / windowSize.GetWidth() - 1.0f,
        1.0f - 2.0f * ray->origin->Y / windowSize.GetHeight()
    );

    Coord* second = new Coord(
        2.0f * ray->direction->X / windowSize.GetWidth() - 1.0f,
        1.0f - 2.0f * ray->direction->Y / windowSize.GetHeight()
    );

    // Ðèñóåì ëèíèþ
    glBegin(GL_LINES);
    glVertex2f(first->X, first->Y);
    glVertex2f(second->X, second->Y);
    glEnd();
}

void drawRay(std::unique_ptr<Ray>& ray, Color& color)
{
    drawRay(ray, color);
}