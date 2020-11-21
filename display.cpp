#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "octahedron.h"
#include "cylinder.h"

#include <iostream>

//create window
void Display::Init(int w, int h, const char* title)
{
	m_width = w;
	m_height = h;

	m_mesh = nullptr;
	m_shader = nullptr;

	//init glfw
	glfwInit();

	//create window
	m_window = glfwCreateWindow(w, h, title, NULL, NULL);
	glfwSetFramebufferSizeCallback(m_window, Display::Resize);
	glfwMakeContextCurrent(m_window);

	//bind events
	glfwSetKeyCallback(m_window, Display::Keyboard);
	glfwSetMouseButtonCallback(m_window, Display::MouseButton);
	glfwSetCursorPosCallback(m_window, Display::MouseMove);

	//init glew
	glewInit();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//set variables
	m_lightA = m_lightB = 0.0f;
	m_transformA = m_transformB = 0.0f;
	m_mousePrevX = m_mousePrevY = -1.0;
	m_drag = false;
	m_animation = false;

	//print help
	std::cout <<
		"1 -- show octahedron\n"
		"2 -- show cylinder\n"
		"S -- reload shaders\n"
		"C -- change cylinder params\n"
		"Mouse drag -- rotate mesh\n"
		"Arrow keys - rotate source of light\n"
		"R - reset source of light\n"
		"A - toggle shader animation\n"
		<< std::endl;
}

//close window
void Display::Close()
{
	if (m_mesh) delete m_mesh;
	if (m_shader) delete m_shader;

	glfwTerminate();
}

//events
//keyboard
void Display::Keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//light settings
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		int dx = (key == GLFW_KEY_RIGHT) - (key == GLFW_KEY_LEFT);
		int dy = (key == GLFW_KEY_UP) - (key == GLFW_KEY_DOWN);
		float k = 0.025f;

		m_lightA += dx * k;
		m_lightB += dy * k;
	}

	//key presses
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		//change mesh
		case GLFW_KEY_1: SetMesh(new Octahedron()); break;
		case GLFW_KEY_2: SetMesh(new Cylinder()); break;

		//reload shaders
		case GLFW_KEY_S:
			SetShader(new Shader("basic"));
			if (m_shader && m_shader->IsGood())
				std::cout << "Shaders loaded successfully!\n" << std::endl;
			break;

		//reset light
		case GLFW_KEY_R: m_lightA = m_lightB = 0.0f; break;

		//toggle animation
		case GLFW_KEY_A:
			m_animation = !m_animation;
			m_timeStart = (float)glfwGetTime();

			if (m_animation) std::cout << "Animation started" << std::endl << std::endl;
			else std::cout << "Animation ended" << std::endl << std::endl;

			break;

		//change cylinder
		case GLFW_KEY_C: 
		{
			if (!m_mesh || !m_shader || !m_shader->IsGood()) break;

			Cylinder* cylinder = dynamic_cast<Cylinder*>(m_mesh);
			if (!cylinder) break;

			//read k
			float k;
			std::cout << "Input ratio of sizes of ellipse (0.01 - 1.0, default 0.75): " << std::flush;
			std::cin >> k;
			if (k < 0.01f || k > 1.0f) k = 0.75f;

			//read n
			int n;
			std::cout << "Input number of sides (lagrer than 2, default 10): " << std::flush;
			std::cin >> n;
			if (n < 3) n = 10;

			//update mesh
			cylinder->SetNumber(k, n);
			std::cout << std::endl << std::endl;
			break;
		}
		}
	}
}
//mouse button
void Display::MouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
		{
			glfwGetCursorPos(m_window, &m_mousePrevX, &m_mousePrevY);
			m_drag = true;
		}
		else if (action == GLFW_RELEASE) m_drag = false;
	}
}
//mouse movement
void Display::MouseMove(GLFWwindow* window, double x, double y)
{
	if (m_drag)
	{
		float k = 2.0f / std::min(m_width, m_height);
		m_transformA += k * float(x - m_mousePrevX);
		m_transformB += k * float(y - m_mousePrevY);

		m_mousePrevX = x;
		m_mousePrevY = y;
	}
}

//draw mesh with shader
void Display::Draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_mesh && m_shader && m_shader->IsGood())
	{
		m_shader->Bind();
		m_mesh->Draw();
	}

	//swap front and back buffers
	glfwSwapBuffers(m_window);
}
//resize window
void Display::Resize(GLFWwindow* window, int width, int height)
{
	m_width = width;
	m_height = height;

	glViewport(0, 0, width, height);

	Draw();
}

//start loop
void Display::Start()
{
	while (!glfwWindowShouldClose(m_window))
	{
		//update
		m_shader->SetTransform(m_transformA, m_transformB);
		m_shader->SetCamera((float)m_width / m_height);

		m_shader->SetLight(m_lightA, m_lightB);
		m_shader->SetTimer(m_animation ? ((float)glfwGetTime() - m_timeStart) : 0.0f);

		//render
		Draw();

		//Poll for and process events
		glfwPollEvents();
	}
}

//setters
void Display::SetMesh(Mesh* mesh)
{
	if (m_mesh) delete m_mesh;
	m_mesh = mesh;
}
void Display::SetShader(Shader* shader)
{
	if (m_shader) delete m_shader;
	m_shader = shader;
}