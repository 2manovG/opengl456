#include "shader.h"

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

//help functions
std::string File2String(const std::string& fname);
static int CompileShader(const std::string& shader, unsigned int type);

//load shaders
Shader::Shader(const std::string& fname)
{
    //create shader
    m_program = glCreateProgram();
    m_good = false;

    //load all sub-shaders
    unsigned int vs = CompileShader(File2String(fname + ".vs"), GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(File2String(fname + ".fs"), GL_FRAGMENT_SHADER);

    //error
    if (!vs || !fs)
    {
        glDeleteShader(vs);
        glDeleteShader(fs);

        glDeleteProgram(m_program);
        return;
    }

    //attach them
    glAttachShader(m_program, vs);
    glAttachShader(m_program, fs);

    //compile them
    glLinkProgram(m_program);
    glValidateProgram(m_program);

    //setup uniforms
    m_uniforms[U_TRANSFORM] = glGetUniformLocation(m_program, "transform");
    m_uniforms[U_CAMERA] = glGetUniformLocation(m_program, "camera");
    m_uniforms[U_LIGHT] = glGetUniformLocation(m_program, "light");
    m_uniforms[U_TIMER] = glGetUniformLocation(m_program, "timer");

    //remove shaders
    glDetachShader(m_program, vs);
    glDetachShader(m_program, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);

    //everything ok
    m_good = true;
}

//unload shaders
Shader::~Shader()
{
    glDeleteProgram(m_program);
}

//use shaders
void Shader::Bind()
{
    glUseProgram(m_program);
}

//set transform
void Shader::SetTransform(float angle1, float angle2)
{
    glm::mat4 rot =
        glm::rotate(angle2, glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(angle1, glm::vec3(0.0f, 1.0f, 0.0f));

    glUniformMatrix4fv(m_uniforms[U_TRANSFORM], 1, GL_FALSE, &rot[0][0]);
}
//set camera
void Shader::SetCamera(float aspect)
{
    float scl = std::min(aspect, 1.0f) * 0.9f;

    glm::mat4 cam =
        glm::perspective(3.14159265f / 2, aspect, 0.01f, 1000.0f) *
        glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::scale(glm::vec3(scl, scl, scl));

    glUniformMatrix4fv(m_uniforms[U_CAMERA], 1, GL_FALSE, &cam[0][0]);
}

//set light
void Shader::SetLight(float angle1, float angle2)
{
    float cos1 = cosf(angle1), sin1 = sinf(angle1);
    float cos2 = cosf(angle2), sin2 = sinf(angle2);

    glUniform3f(m_uniforms[U_LIGHT], sin1 * cos2, sin2, cos1 * cos2);
}
//set timer value
void Shader::SetTimer(float timer)
{
    glUniform1f(m_uniforms[U_TIMER], timer);
}

//help functions
std::string File2String(const std::string& fname)
{
    //open file
    std::ifstream file(fname);

    //can't open file
    if (!file.good())
    {
        std::cout << "Can't open file " << fname << std::endl;
        return "";
    }

    //resulting string and temp string
    std::string res = "", line;

    //read lines
    while (!file.eof())
    {
        std::getline(file, line);
        res += line + '\n';
    }
    return res;
}
static int CompileShader(const std::string& shader, unsigned int type)
{
    //create shader
    unsigned int id = glCreateShader(type);

    //write source code
    const char* src = shader.c_str();
    glShaderSource(id, 1, &src, nullptr);

    //compile
    glCompileShader(id);

    //error handling
    int res;
    glGetShaderiv(id, GL_COMPILE_STATUS, &res);

    if (res == GL_FALSE) //show error
    {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

        char* message = new char[len];
        glGetShaderInfoLog(id, len, &len, message);

        std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") <<
            " shader ERROR:\n" << message << std::endl;

        delete[] message;

        glDeleteShader(id);
        return 0;
    }

    return id;
}