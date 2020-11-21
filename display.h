#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//predefine classes
class Mesh;
class Shader;

//create and proceed window
class Display
{
public:
	static void Init(int w, int h, const char* title); //create window
	static void Close(); //close window

	static void Start(); //start loop

	//setters
	static void SetMesh(Mesh* mesh);
	static void SetShader(Shader* shader);

private:
	static inline GLFWwindow* m_window; //window handle
	static inline int m_width, m_height; //size of window

	static inline Mesh* m_mesh; //mesh for render
	static inline Shader* m_shader; //mesh for render

	static inline float m_lightA, m_lightB; //angles of light
	static inline float m_transformA, m_transformB; //angles of model

	static inline bool m_drag; //is mouse dragging
	static inline double m_mousePrevX, m_mousePrevY; //previous mouse pos

	static inline bool m_animation; //perform animation or not
	static inline float m_timeStart; //time, when animation started

	static void Draw(); //draw mesh with shader
	static void Resize(GLFWwindow* window, int width, int height); //resize window

	//events
	static void Keyboard(GLFWwindow* window, int key, int scancode, int action, int mods); //keyboard
	static void MouseButton(GLFWwindow* window, int button, int action, int mods); //mouse button
	static void MouseMove(GLFWwindow* window, double x, double y); //mouse movement
};
