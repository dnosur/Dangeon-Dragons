// Dangeon&Dragons.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#define _CRTDBG_MAP_ALLOC
#define STB_IMAGE_IMPLEMENTATION
#define GL_GLEXT_PROTOTYPES

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Dodge/MainWindow.h"
#include "Dodge/audio/SoundSystem.h"

#include "Dodge/tiny/TinyXml.h"

#include <cstdlib>
#include <crtdbg.h>

int main(int argc, char** argv)
{
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    srand(time(NULL));
    glutInit(&argc, argv);
    if (!glfwInit())
        return -1;

    SoundSystem soundSystem;
    MainWindow main(Size(1280, 720), "Sample", Color(.4f, .6f, 0));

    main.MakeContext();
    main.Initialize();
    main.Update();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
