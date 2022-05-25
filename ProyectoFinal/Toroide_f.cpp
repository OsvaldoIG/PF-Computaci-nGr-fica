
/*
* Sphere.cpp
*Basado en el código creado por
*  Created on: 06/09/2016
*      Author: reynaldo Martell
*/
#include "Toroide_f.h"

//slices->ratioInt   stacks->ratioExt
//Toroide_f(float ratioInt, float ratioExt, int resolutionExt, int resolutionInt);

Toroide_f::Toroide_f(float raInt, float raExt, int reExt, int reInt):
	ratioInt(raInt),ratioExt (raExt),resolutionInt (reInt),resolutionExt (reExt), VAO(0), VBO(0), EBO(0) {
}

Toroide_f::~Toroide_f() {

}



void Toroide_f::Crear_Toroide_f() {
	//CREACION DEL TOROIDE
	for (int i = 0; i < resolutionExt; i++) { 
		for (int j = 0; j <= resolutionInt; j++) { 
			for (int k = 1; k >= 0; k--) { 
				float alfa = (i + k) % resolutionExt + 0.5; 
				float beta = j % resolutionInt; 

				float x = (ratioExt + (ratioInt)*cos(alfa * 2 * PI / resolutionInt)) * cos(beta * 2 * PI / resolutionExt);
				float y = (ratioExt + (ratioInt)*cos(alfa * 2 * PI / resolutionInt)) * sin(beta * 2 * PI / resolutionExt);
				float z = (ratioInt)*sin(alfa * 2 * PI / resolutionExt);
				vert.push_back(x); 
				vert.push_back(y);
				vert.push_back(z);

				vert.push_back(1.0f);
				vert.push_back(1.0f);
				vert.push_back(1.0f);

				index.push_back(contIndex - 1);
				index.push_back(contIndex);
				index.push_back(contIndex + 1);
				index.push_back(contIndex);
				contIndex++;
				index.push_back(contIndex);
				contIndex++;
				index.push_back(contIndex);
				contIndex++;

				index.push_back(contIndex - 2);
				index.push_back(contIndex - 1);
				index.push_back(contIndex);

			}
		}
	}

}


void Toroide_f::load() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index[0]) * index.size(), index.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert[0]) * vert.size(), vert.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vert[0]), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vert[0]), (void*)(3 * sizeof(vert[0])));//Offset de los 3 vértices para tomar los 3 de color
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Toroide_f::render() {

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, contIndex, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}


