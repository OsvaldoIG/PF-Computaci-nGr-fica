
#ifndef TOROIDE_H_
#define TOROIDE_H_

#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

#include "definition.h"

class Toroide {
public:
	Toroide(float RCirculo, float RAmplitud, float resolution);
	void init();
	void load();
	void render();
	virtual ~Toroide();
private:
	std::vector<VertexColor> vertexC;
	std::vector<GLuint> index;
	float* matpuntos;
	float RCirculo;
	float RAmplitud;
	float resolution;
	GLuint VAO, VBO, EBO, numPuntos;
};

#endif /* SPHERE_H_ */
