#pragma once
#include <glad/glad.h>
#include "../Size.h"

struct Character {
    GLuint textureId;
    Size size;
    Size bearing;
    GLuint advance;

    Character();
    Character(GLuint textureId, Size size, Size bearing, GLuint advance);

	~Character();

	bool operator==(const Character& other) const;
    bool operator!=(Character& other);

	Character& operator=(Character& other);
};