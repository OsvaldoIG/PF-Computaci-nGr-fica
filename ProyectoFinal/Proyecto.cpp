/*
Semestre 2022-2
Práctica 5: Carga de Modelos
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminaci�n
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture cuatroTexture;


Model Kitt_M;
Model Llanta_M;
Model Camino_M;
Model Blackhawk_M;
Model Aspas_M;
Model ArmaKND_M;
Model CasaLorax_M;
Model SimioArcoiris_M;
Model Cuatro_M;

//CORTADORA DE ARBOLES
Model Cortadora_M;
Model Rueda_M;
Model Hacha_M;
Model Chimenea_M;
Model Ruedita_M;

Skybox skybox;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";



void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};


	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void CrearCuatro()
{
	unsigned int cubo_indices[] = {
		// front
		/*0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,*/
		//CUERPO
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20,
		//CABEZA
		24, 25, 26,
		26, 27, 24,

		28, 29, 30,
		30, 31, 28,

		32, 33, 34,
		34, 35, 32,

		36, 37, 38,
		38, 39, 36, 

		40, 41, 42,
		42, 43, 40,

		44, 45, 46,
		46, 47, 44,
		 
		//PIERNA IZQ
		48, 49, 50,
		50, 51, 48,

		52, 53, 54,
		54, 55, 52,

		56, 57, 58,
		58, 59, 56,

		60, 61, 62,
		62, 63, 60,

		64, 65, 66,
		66, 67, 64,

		68, 69, 70,
		70, 71, 68,

		//PIERNA DER
		72, 73, 74,
		74, 75, 72,

		76, 77, 78,
		78, 79, 76,

		80, 81, 82,
		82, 83, 80,

		84, 85, 86,
		86, 87, 84,

		88, 89, 90,
		90, 91, 88,

		92, 93, 94,
		94, 95, 92,

		//BRAZO IZQ
		96, 97, 98,
		98, 99, 96,

		100, 101, 102,
		102, 103, 100,

		104, 105, 106,
		106, 107, 104,

		108, 109, 110,
		110, 111, 108,

		112, 113, 114,
		114, 115, 112,

		116, 117, 118, 
		118, 119, 116,

		//BRAZO DER
		120, 121, 122, 
		122, 123, 120,

		124, 125, 126,
		126, 127, 124,

		128, 129, 130,
		130, 131, 128,

		132, 133, 134,
		134, 135, 132,

		136, 137, 138,
		138, 139, 136,

		140, 141, 142,
		142, 143, 140,

	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
	GLfloat cubo_vertices[] = {
		
		//CUERPO
		//FRENTE
		//X		Y		Z		S		T		NX		NY		NZ
		-0.4f, -0.6f, 0.2f,		0.3125f, 0.5f,		0.0f, 0.0f, -1.0f,
		0.4f, -0.6f, 0.2f,		0.4375f, 0.5f,		0.0f, 0.0f, -1.0f,
		0.4f, 0.6f, 0.2f,		0.4375f, 0.6875f,	0.0f, 0.0f, -1.0f,
		-0.4f, 0.6f, 0.2f,		0.3125f, 0.6875f,	0.0f, 0.0f, -1.0f,
		//DERECHA
		0.4f, -0.6f, 0.2f,		0.4375f, 0.5f,		-1.0f, 0.0f, 0.0f,	
		0.4f, -0.6f, -0.2f,		0.5f, 0.5f,			-1.0f, 0.0f, 0.0f,
		0.4f, 0.6f, -0.2f,		0.5f, 0.6875f,		-1.0f, 0.0f, 0.0f,
		0.4f, 0.6f, 0.2f,		0.4375f, 0.6875f,	-1.0f, 0.0f, 0.0f,

		//IZQUIERDA
		-0.4f, -0.6f, 0.2f,		0.4375f, 0.5f,		1.0f, 0.0f, 0.0f,
		-0.4f, -0.6f, -0.2f,	0.5f, 0.5f,			1.0f, 0.0f, 0.0f,
		-0.4f, 0.6f, -0.2f,		0.5f, 0.6875f,		1.0f, 0.0f, 0.0f,
		-0.4f, 0.6f, 0.2f,		0.4375f, 0.6875f,	1.0f, 0.0f, 0.0f,

		//ATRAS
		-0.4f, -0.6f, -0.2f,	0.5f, 0.5f,			0.0f, 0.0f, 1.0f,
		0.4f, -0.6f, -0.2f,		0.625f, 0.5f,		0.0f, 0.0f, 1.0f,
		0.4f, 0.6f, -0.2f,		0.625f, 0.6875f,	0.0f, 0.0f, 1.0f,
		-0.4f, 0.6f, -0.2f,		0.5f, 0.6875f,		0.0f, 0.0f, 1.0f,
		
		//ARRIBA
		0.4f, 0.6f, 0.2f,		0.4375f, 0.5f,		0.0f, -1.0f, 0.0f,
		0.4f, 0.6f, -0.2f,		0.5f, 0.5f,			0.0f, -1.0f, 0.0f,
		-0.4f, 0.6f, -0.2f,		0.5f, 0.6875f,		0.0f, -1.0f, 0.0f,
		-0.4f, 0.6f, 0.2f,		0.4375f, 0.6875f,	0.0f, -1.0f, 0.0f,

		//ABAJO
		0.4f, -0.6f, -0.2f,		0.4375f, 0.5f,		0.0f, 1.0f, 0.0f,
		-0.4f, -0.6f, -0.2f,	0.5f, 0.5f,			0.0f, 1.0f, 0.0f,
		-0.4f, -0.6f, 0.2f,		0.5f, 0.6875f,		0.0f, 1.0f, 0.0f,
		0.4f, -0.6f, 0.2f,		0.4375f, 0.6875f,	0.0f, 1.0f, 0.0f,

		//CABEZA
		//FRENTE
		-0.4f, 0.6f, 0.4f,		0.125f, 0.75f,		0.0f, 0.0f, -1.0f,
		0.4f, 0.6f, 0.4f,		0.25f, 0.75f,		0.0f, 0.0f, -1.0f,
		0.4f, 1.4f, 0.4f,		0.25f, 0.875f,		0.0f, 0.0f, -1.0f,
		-0.4f, 1.4f, 0.4f,		0.125f, 0.875f,		0.0f, 0.0f, -1.0f,

		//DERECHA
		0.4f, 0.6f, 0.4f,		0.25f, 0.75f,		-1.0f, 0.0f, 0.0f,
		0.4f, 0.6f, -0.4f,		0.375f, 0.75f,		-1.0f, 0.0f, 0.0f,
		0.4f, 1.4f, -0.4f,		0.375f, 0.875f,		-1.0f, 0.0f, 0.0f,
		0.4f, 1.4f, 0.4f,		0.25f, 0.875f,		-1.0f, 0.0f, 0.0f,

		//IZQUIERDA
		-0.4f, 0.6f, 0.4f,		0.125f, 0.76f,		1.0f, 0.0f, 0.0f,
		-0.4f, 0.6f, -0.4f,		0.01f, 0.76f,		1.0f, 0.0f, 0.0f,
		-0.4f, 1.4f, -0.4f,		0.01f, 0.865f,		1.0f, 0.0f, 0.0f,
		-0.4f, 1.4f, 0.4f,		0.125f, 0.865f,		1.0f, 0.0f, 0.0f,

		//ATRAS
		-0.4f, 0.6f, -0.4f,		0.375f, 0.75f,		0.0f, 0.0f, 1.0f,
		0.4f, 0.6f, -0.4f,		0.49f, 0.75f,		0.0f, 0.0f, 1.0f,
		0.4f, 1.4f, -0.4f,		0.49f, 0.865f,		0.0f, 0.0f, 1.0f,
		-0.4f, 1.4f, -0.4f,		0.375f, 0.865f,		0.0f, 0.0f, 1.0f,

		//ARRIBA
		0.4f, 1.4f, 0.4f,		0.145f, 0.875f,		0.0f, -1.0f, 0.0f,
		0.4f, 1.4f, -0.4f,		0.25f, 0.875f,		0.0f, -1.0f, 0.0f,
		-0.4f, 1.4f, -0.4f,		0.25f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.4f, 1.4f, 0.4f,		0.145f, 1.0f,		0.0f, -1.0f, 0.0f,

		//ABAJO
		0.4f, 0.6f, -0.4f,		0.27f, 0.875f,		0.0f, 1.0f, 0.0f,
		-0.4f, 0.6f, -0.4f,		0.375f, 0.875f,		0.0f, 1.0f, 0.0f,
		-0.4f, 0.6f, 0.4f,		0.27f, 1.0f,		0.0f, 1.0f, 0.0f,
		0.4f, 0.6f, 0.4f,		0.375f, 1.0f,		0.0f, 1.0f, 0.0f,

		//PIERNA IZQ
		//FRENTE
		-0.4f, -1.8f, 0.2f,		0.0625f, 0.5f,		0.0f, 0.0f, -1.0f,
		0.0f, -1.8f, 0.2f,		0.125f, 0.5f,		0.0f, 0.0f, -1.0f,
		0.0f, -0.6f, 0.2f,		0.125f, 0.6875f,	0.0f, 0.0f, -1.0f,
		-0.4f, -0.6f, 0.2f,		0.0625f, 0.6875f,	0.0f, 0.0f, -1.0f,

		//DERECHA
		0.0f, -1.8f, 0.2f,		0.01f, 0.5f,		-1.0f, 0.0f, 0.0f,
		0.0f, -1.8f, -0.2f,		0.0625f, 0.5f,		-1.0f, 0.0f, 0.0f,
		0.0f, -0.6f, -0.2f,		0.0625f, 0.6875f,	-1.0f, 0.0f, 0.0f,
		0.0f, -0.6f, 0.2f,		0.01f, 0.6875f,		-1.0f, 0.0f, 0.0f,

		//IZQUIERDA
		-0.4f, -1.8f, 0.2f,		0.01f, 0.5f,		1.0f, 0.0f, 0.0f,
		-0.4f, -1.8f, -0.2f,	0.0625f, 0.5f,		1.0f, 0.0f, 0.0f,
		-0.4f, -0.6f, -0.2f,	0.0625f, 0.6875f,	1.0f, 0.0f, 0.0f,
		-0.4f, -0.6f, 0.2f,		0.01f, 0.6875f,		1.0f, 0.0f, 0.0f,

		//ATRAS
		0.0f, -1.8f, -0.2f,		0.01f, 0.5f,		0.0f, 0.0f, 1.0f,
		-0.4f, -1.8f, -0.2f,	0.0625f, 0.5f,		0.0f, 0.0f, 1.0f,
		-0.4f, -0.6f, -0.2f,	0.0625f, 0.6875f,	0.0f, 0.0f, 1.0f,
		0.0f, -0.6f, -0.2f,		0.01f, 0.6875f,		0.0f, 0.0f, 1.0f,

		//ARRIBA
		0.0f, -0.6f, 0.2f,		0.0625f, 0.6875f,	0.0f, -1.0f, 0.0f,
		0.0f, -0.6f, -0.2f,		0.125f, 0.6875f,	0.0f, -1.0f, 0.0f,
		-0.4f, -0.6f, -0.2f,	0.125f, 0.75f,		0.0f, -1.0f, 0.0f,
		-0.4f, -0.6f, 0.2f,		0.0625f, 0.75f,		0.0f, -1.0f, 0.0f,

		//ABAJO
		0.0f, -1.8f, 0.2f,		0.135f, 0.6975f,	0.0f, 1.0f, 0.0f,
		0.0f, -1.8f, -0.2f,		0.1775f, 0.6975f,	0.0f, 1.0f, 0.0f,
		-0.4f, -1.8f, -0.2f,	0.1775f, 0.74f,		0.0f, 1.0f, 0.0f,
		-0.4f, -1.8f, 0.2f,		0.135f, 0.74f,		0.0f, 1.0f, 0.0f,

		//PIERNA DER
		//FRENTE
		0.0f, -1.8f, 0.2f,		0.0625f, 0.51f,		0.0f, 0.0f, -1.0f,
		0.4f, -1.8f, 0.2f,		0.125f, 0.51f,		0.0f, 0.0f, -1.0f,
		0.4f, -0.6f, 0.2f,		0.125f, 0.6775f,	0.0f, 0.0f, -1.0f,
		0.0f, -0.6f, 0.2f,		0.0625f, 0.6775f,	0.0f, 0.0f, -1.0f,

		//DERECHA
		0.4f, -1.8f, 0.2f,		0.01f, 0.51f,		-1.0f, 0.0f, 0.0f,
		0.4f, -1.8f, -0.2f,		0.0625f, 0.51f,		-1.0f, 0.0f, 0.0f,
		0.4f, -0.6f, -0.2f,		0.0625f, 0.6775f,	-1.0f, 0.0f, 0.0f,
		0.4f, -0.6f, 0.2f,		0.01f, 0.6775f,		-1.0f, 0.0f, 0.0f,

		//IZQUIERDA
		0.0f, -1.8f, 0.2f,		0.01f, 0.51f,		1.0f, 0.0f, 0.0f,
		0.0f, -1.8f, -0.2f,		0.0625f, 0.51f,		1.0f, 0.0f, 0.0f,
		0.0f, -0.6f, -0.2f,		0.0625f, 0.6775f,	1.0f, 0.0f, 0.0f,
		0.0f, -0.6f, 0.2f,		0.01f, 0.6775f,		1.0f, 0.0f, 0.0f,

		//ATRAS
		0.4f, -1.8f, -0.2f,		0.01f, 0.51f,		0.0f, 0.0f, 1.0f,
		0.0f, -1.8f, -0.2f,		0.0625f, 0.51f,		0.0f, 0.0f, 1.0f,
		0.0f, -0.6f, -0.2f,		0.0625f, 0.6775f,	0.0f, 0.0f, 1.0f,
		0.4f, -0.6f, -0.2f,		0.01f, 0.6775f,		0.0f, 0.0f, 1.0f,

		//ARRIBA
		0.4f, -0.6f, 0.2f,		0.0625f, 0.6975f,	0.0f, -1.0f, 0.0f,
		0.4f, -0.6f, -0.2f,		0.125f, 0.6975f,	0.0f, -1.0f, 0.0f,
		0.0f, -0.6f, -0.2f,		0.125f, 0.74f,		0.0f, -1.0f, 0.0f,
		0.0f, -0.6f, 0.2f,		0.0625f, 0.74f,		0.0f, -1.0f, 0.0f,

		//ABAJO
		0.4f, -1.8f, 0.2f,		0.135f, 0.6975f,	0.0f, 1.0f, 0.0f,
		0.4f, -1.8f, -0.2f,		0.1775f, 0.6975f,	0.0f, 1.0f, 0.0f,
		0.0f, -1.8f, -0.2f,		0.1775f, 0.74f,		0.0f, 1.0f, 0.0f,
		0.0f, -1.8f, 0.2f,		0.135f, 0.74f,		0.0f, 1.0f, 0.0f,

		//BRAZO IZQ
		//FRENTE
		0.4f, -0.6f, 0.2f,		0.635f, 0.5f,		0.0f, 0.0f, -1.0f,
		0.8f, -0.6f, 0.2f,		0.6775f, 0.5f,		0.0f, 0.0f, -1.0f,
		0.8f, 0.6f, 0.2f,		0.6775f, 0.6875f,	0.0f, 0.0f, -1.0f,
		0.4f, 0.6f, 0.2f,		0.635f, 0.6875f,	0.0f, 0.0f, -1.0f,

		//DERECHA
		0.8f, -0.6f, 0.2f,		0.635f, 0.5f,		-1.0f, 0.0f, 0.0f,
		0.8f, -0.6f, -0.2f,	0.6775f, 0.5f,		-1.0f, 0.0f, 0.0f,
		0.8f, 0.6f, -0.2f,		0.6775f, 0.6875f,	-1.0f, 0.0f, 0.0f,
		0.8f, 0.6f, 0.2f,		0.635f, 0.6875f,	-1.0f, 0.0f, 0.0f,

		//IZQUIERDA
		0.4f, -0.6f, -0.2f,	0.635f, 0.5f,		1.0f, 0.0f, 0.0f,
		0.4f, -0.6f, 0.2f,		0.6775f, 0.5f,		1.0f, 0.0f, 0.0f,
		0.4f, 0.6f, 0.2f,		0.6775f, 0.6875f,	1.0f, 0.0f, 0.0f,
		0.4f, 0.6f, -0.2f,		0.635f, 0.6875f,	1.0f, 0.0f, 0.0f,

		//ATRAS
		0.8f, -0.6f, -0.2f,	0.635f, 0.5f,		0.0f, 0.0f, 1.0f,
		0.4f, -0.6f, -0.2f,	0.6775f, 0.5f,		0.0f, 0.0f, 1.0f,
		0.4f, 0.6f, -0.2f,		0.6775f, 0.6875f,	0.0f, 0.0f, 1.0f,
		0.8f, 0.6f, -0.2f,		0.635f, 0.6875f,	0.0f, 0.0f, 1.0f,

		//ARRIBA
		0.4f, 0.6f, 0.2f,		0.6975f, 0.6875f,	0.0f, -1.0f, 0.0f,
		0.8f, 0.6f, 0.2f,		0.74f, 0.6875f,		0.0f, -1.0f, 0.0f,
		0.8f, 0.6f, -0.2f,		0.74f, 0.75f,		0.0f, -1.0f, 0.0f,
		0.4f, 0.6f, -0.2f,		0.6975f, 0.75f,		0.0f, -1.0f, 0.0f,

		//ABAJO
		0.4f, -0.6f, -0.2f,		0.76f, 0.6975f,	0.0f, 1.0f, 0.0f,
		0.8f, -0.6f, -0.2f,		0.8025f, 0.6975f,	0.0f, 1.0f, 0.0f,
		0.8f, -0.6f, 0.2f,		0.8025f, 0.74f,		0.0f, 1.0f, 0.0f,
		0.4f, -0.6f, 0.2f,		0.76f, 0.74f,		0.0f, 1.0f, 0.0f,

		//BRAZO DER
		//FRENTE
		-0.4f, -0.6f, 0.2f,		0.635f, 0.5f,		0.0f, 0.0f, -1.0f,
		-0.8f, -0.6f, 0.2f,		0.6775f, 0.5f,		0.0f, 0.0f, -1.0f,
		-0.8f, 0.6f, 0.2f,		0.6775f, 0.6875f,	0.0f, 0.0f, -1.0f,
		-0.4f, 0.6f, 0.2f,		0.635f, 0.6875f,	0.0f, 0.0f, -1.0f,

		//DERECHA
		-0.8f, -0.6f, 0.2f,		0.635f, 0.5f,		-1.0f, 0.0f, 0.0f,
		-0.8f, -0.6f, -0.2f,	0.6775f, 0.5f,		-1.0f, 0.0f, 0.0f,
		-0.8f, 0.6f, -0.2f,		0.6775f, 0.6875f,	-1.0f, 0.0f, 0.0f,
		-0.8f, 0.6f, 0.2f,		0.635f, 0.6875f,	-1.0f, 0.0f, 0.0f,

		//IZQUIERDA
		-0.4f, -0.6f, -0.2f,	0.635f, 0.5f,		1.0f, 0.0f, 0.0f,
		-0.4f, -0.6f, 0.2f,		0.6775f, 0.5f,		1.0f, 0.0f, 0.0f,
		-0.4f, 0.6f, 0.2f,		0.6775f, 0.6875f,	1.0f, 0.0f, 0.0f,
		-0.4f, 0.6f, -0.2f,		0.635f, 0.6875f,	1.0f, 0.0f, 0.0f,

		//ATRAS
		-0.8f, -0.6f, -0.2f,	0.635f, 0.5f,		0.0f, 0.0f, 1.0f,
		-0.4f, -0.6f, -0.2f,	0.6775f, 0.5f,		0.0f, 0.0f, 1.0f,
		-0.4f, 0.6f, -0.2f,		0.6775f, 0.6875f,	0.0f, 0.0f, 1.0f,
		-0.8f, 0.6f, -0.2f,		0.635f, 0.6875f,	0.0f, 0.0f, 1.0f,

		//ARRIBA
		-0.4f, 0.6f, 0.2f,		0.6975f, 0.6875f,	0.0f, -1.0f, 0.0f,
		-0.8f, 0.6f, 0.2f,		0.74f, 0.6875f,		0.0f, -1.0f, 0.0f,
		-0.8f, 0.6f, -0.2f,		0.74f, 0.75f,		0.0f, -1.0f, 0.0f,
		-0.4f, 0.6f, -0.2f,		0.6975f, 0.75f,		0.0f, -1.0f, 0.0f,

		//ABAJO
		-0.4f, -0.6f, -0.2f,	0.76f, 0.6975f,	0.0f, 1.0f, 0.0f,
		-0.8f, -0.6f, -0.2f,	0.8025f, 0.6975f,	0.0f, 1.0f, 0.0f,
		-0.8f, -0.6f, 0.2f,		0.8025f, 0.74f,		0.0f, 1.0f, 0.0f,
		-0.4f, -0.6f, 0.2f,		0.76f, 0.74f,		0.0f, 1.0f, 0.0f,

	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(cubo_vertices, cubo_indices, sizeof(cubo_vertices)/4, sizeof(cubo_indices)/4);
	meshList.push_back(dado);

}

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearCuatro();
	CreateShaders();


	//camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);
	camera = Camera(glm::vec3(0.0f, 0.25f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.1f, 0.5f);

	//Aqui se importan texturas
	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();

	cuatroTexture = Texture("Textures/cuatro_Texturas.tga");
	cuatroTexture.LoadTextureA();

	Kitt_M = Model();
	//Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	//SE IMPORTAN LOS MODELOS
	//Kitt_M.LoadModel("Models/kitt_obj.obj");
	Kitt_M.LoadModel("Models/Vazz_obj.obj");

	Llanta_M = Model();
	Llanta_M.LoadModel("Models/Vazz_rueda_obj.obj");

	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/Black Hawk uh-60_Carcasa.obj");

	Camino_M = Model();
	Camino_M.LoadModel("Models/railroad track.obj");

	Aspas_M = Model();
	Aspas_M.LoadModel("Models/Black Hawk uh-60_Aspas.obj");

	ArmaKND_M = Model();
	ArmaKND_M.LoadModel("Models/KNDSPANKLER.obj");

	CasaLorax_M = Model();
	CasaLorax_M.LoadModel("Models/casa_Lorax.obj");

	/*Model Cortadora_M;
Model Rueda_M;
Model Hacha_M;
Model Chimenea_M;
Model Ruedita_M;*/

	Cortadora_M = Model();
	Cortadora_M.LoadModel("Models/cortadora_opt.obj");

	Rueda_M = Model();
	Rueda_M.LoadModel("Models/rueda.obj");

	Hacha_M = Model();
	Hacha_M.LoadModel("Models/hacha_opt.obj");

	Chimenea_M = Model();
	Chimenea_M.LoadModel("Models/chimenea_opt.obj");

	Ruedita_M = Model();
	Ruedita_M.LoadModel("Models/tire-tx.obj");

	SimioArcoiris_M = Model();
	SimioArcoiris_M.LoadModel("Models/SimioArcoiris_obj_Texture.obj");

	std::vector<std::string> skyboxFaces;
	//Texturas de skyboard
	/*skyboxFaces.push_back("Textures/Skybox/desert_bk.tga"); //bk
	skyboxFaces.push_back("Textures/Skybox/desert_ft.tga"); //ft
	skyboxFaces.push_back("Textures/Skybox/desert_dn.tga"); //dn
	skyboxFaces.push_back("Textures/Skybox/desert_up.tga"); //up
	skyboxFaces.push_back("Textures/Skybox/desert_lt.tga"); //lt
	skyboxFaces.push_back("Textures/Skybox/desert_rt.tga"); //rt */

	//SKYBOX NOCHE
	skyboxFaces.push_back("Textures/Skybox/desert_noche_bk.tga"); //bk
	skyboxFaces.push_back("Textures/Skybox/desert_noche_ft.tga"); //ft
	skyboxFaces.push_back("Textures/Skybox/desert_noche_dn.tga"); //dn
	skyboxFaces.push_back("Textures/Skybox/desert_noche_up.tga"); //up
	skyboxFaces.push_back("Textures/Skybox/desert_noche_lt.tga"); //lt
	skyboxFaces.push_back("Textures/Skybox/desert_noche_rt.tga"); //rt

	skybox = Skybox(skyboxFaces);

	//Material_brillante = Material(4.0f, 256);
	//Material_opaco = Material(0.3f, 4);


	//luz direccional, s�lo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaraci�n de primer luz puntual
	

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la c�mara de tipo flash
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 cortadora_aux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();


	
		//	Simio Arcoiris
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0));
		modelaux = model;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		Cortadora_M.RenderModel();
		//Blackhawk_M.RenderModel();
	

		//CORTADORA DE ARBOLES
		//Se hace una jerarquización partiendo del cuerpo de la cortadora
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, -1.0));
		cortadora_aux = model;
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cortadora_M.RenderModel();


		model = cortadora_aux;
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Chimenea_M.RenderModel();

		model = cortadora_aux;
		model = glm::translate(model, glm::vec3(-3.0f, -1.0f, -3.0f));
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rueda_M.RenderModel();

		model = cortadora_aux;
		model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 3.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rueda_M.RenderModel();

		model = cortadora_aux;
		model = glm::translate(model, glm::vec3(1.0f, -2.0f, -3.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rueda_M.RenderModel();

		model = cortadora_aux;
		model = glm::translate(model, glm::vec3(1.0f, -2.0f, 3.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rueda_M.RenderModel();

		model = cortadora_aux;
		model = glm::translate(model, glm::vec3(6.8f, 0.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hacha_M.RenderModel();
		//////////////////////////////////////////////////////////////////////////////
		model = cortadora_aux;
		model = glm::translate(model, glm::vec3(9.4f, 0.0f, -6.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hacha_M.RenderModel();

		model = cortadora_aux;
		model = glm::translate(model, glm::vec3(13.3f, 0.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hacha_M.RenderModel();
		/////////////////////////////////////////////////////////////////////////////
		
		model = cortadora_aux;
		model = glm::translate(model, glm::vec3(17.0f, 0.0f, -6.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hacha_M.RenderModel();

		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		SimioArcoiris_M.RenderModel();
	
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 5.0f, 0.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuatroTexture.UseTexture();
		meshList[3]->RenderMesh();
		

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
