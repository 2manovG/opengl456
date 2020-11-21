#pragma once
#include <string>

//class, that loads shaders and binds it
class Shader
{
public:
	Shader(const std::string& fname); //load shaders
	~Shader(); //unload shaders

	void Bind(); //use shaders

	void SetTransform(float angle1, float angle2); //set transform
	void SetCamera(float aspect); //set camera

	void SetLight(float angle1, float angle2); //set light direction
	void SetTimer(float timer); //set timer value

	bool IsGood() { return m_good; } //does shader works properly?

private:
	unsigned int m_program; //whole shader itself
	bool m_good; //does shader works properly?

	enum
	{
		U_TRANSFORM,
		U_CAMERA,
		U_LIGHT,
		U_TIMER,
		U_COUNT
	};
	unsigned int m_uniforms[U_COUNT]; //uniforms
};