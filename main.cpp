#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.h"
#include "octahedron.h"
#include "cylinder.h"

#include "display.h"

int main(void)
{
    Display::Init(480, 480, "Lab 4,5,6");

    Display::SetMesh(new Octahedron());
    Display::SetShader(new Shader("basic"));

    Display::Start();

    Display::Close();
    return 0;
}