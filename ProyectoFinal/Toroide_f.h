/*
 * Sphere.h
 *Basado en el código creado por
 *  Created on: 06/09/2016
 *      Author: reynaldo Martell
 */

#ifndef TOROIDE_F_H_
#define TOROIDE_F_H_

#include <vector>
#include"Model.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "definition.h"

class Toroide_f {
public:
	//Sphere(float ratio, int slices, int stacks, MODEL_MODE mode);
	//Sphere(float ratio, int slices, int stacks);
	//void init();
	void load();
	void render();
	void Crear_Toroide_f();
	Toroide_f(float ratioInt, float ratioExt, int resolutionExt, int resolutionInt);
	virtual ~Toroide_f();
private:
	//std::vector<VertexColor> vertexC;
	///*std::vector<VertexLightColor> vertexLC;
	//std::vector<VertexLightTexture> vertexLT;*/
	//std::vector<GLuint> index;
	std::vector<float> vert;
	std::vector<unsigned int> index;
	int contIndex;
	float ratioInt;
	float ratioExt;
	int resolutionInt;
	int resolutionExt;
	const float toRadians = 3.14159265f / 180.0f;
	const float PI = 3.14159265f;
	//MODEL_MODE mode;
	GLuint VAO, VBO, EBO;
};

#endif /* SPHERE_H_ */
