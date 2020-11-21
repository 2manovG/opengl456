#pragma once
#include "mesh.h"

class Cylinder : public Mesh
{
public:
	Cylinder(); //create initial cylinder

	void SetNumber(float k, int n); //rebuild cylinder
};
