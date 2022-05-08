/*
Semestre 2022-2
PrÃ¡ctica 5: Carga de Modelos
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

//para iluminación
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
Camera cameraA;
Camera cameraP;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture cuatroTexture;
Texture caminoTexture;
Texture loraxTexture;
Texture fogataTexture;


Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;
Model Aspas_M;
Model ArmaKND_M;
Model LanzaderaKND_M;
Model CasaLorax_M;
Model SimioArcoiris_M;
Model AntenaSimio_M;
Model Cuatro_M;

//PEZ QUE JUEGA POQUER
Model cuerpo_pez;
Model hombro_pez;
Model brazo_der_pez;
Model conejo_izq_pez;
Model mano_izq_pez;
Model pie_izq;
Model pie_der;
Model piedra;

//ILUMINACION
Model antorcha;



//BASE
Model Camino_M;
Model Pasto_M;

//CORTADORA DE ARBOLES
Model Cortadora_M;
Model Rueda_M;
Model Hacha_M;
Model Chimenea_M;
Model Ruedita_M;

Model arbol_T;
Model Fogata_M;
Model arbol_H;


Skybox skybox;
Skybox skyboxNoche;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

glm::vec3 camaraPiso;
glm::vec3 camaraAerea;
GLint contadorSkybox = 0;
GLboolean banderaSkybox = true;
GLfloat giroSimios =0.0f;
// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

PointLight arrPointLights[20];

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

void CrearLorax() {

	unsigned int indices[] = {
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
GLfloat vertices[] = {

	//CUERPO
	//FRENTE
	//X		Y		Z		S		T		NX		NY		NZ
	-0.4f, -0.6f, 0.2f,		0.57025f,	0.71366f,		0.0f, 0.0f, -1.0f,
	0.4f, -0.6f, 0.2f,		0.71317f,	0.71366f,		0.0f, 0.0f, -1.0f,
	0.4f, 0.6f, 0.2f,		0.71317f,	0.85658f,		0.0f, 0.0f, -1.0f,
	-0.4f, 0.6f, 0.2f,		0.57025f,	0.85658f,		0.0f, 0.0f, -1.0f,
	//DERECHA
	0.4f, -0.6f, 0.2f,		0.71317f,	0.71366f,		-1.0f, 0.0f, 0.0f,
	0.4f, -0.6f, -0.2f,		0.8561f,	0.71366f,		-1.0f, 0.0f, 0.0f,
	0.4f, 0.6f, -0.2f,		0.8561f,	0.85658f,		-1.0f, 0.0f, 0.0f,
	0.4f, 0.6f, 0.2f,		0.71317f,	0.85658f,		-1.0f, 0.0f, 0.0f,

	//IZQUIERDA
	-0.4f, -0.6f, 0.2f,		0.57025f,	0.71366f,		1.0f, 0.0f, 0.0f,
	-0.4f, -0.6f, -0.2f,	0.42684f,	0.71366f,			1.0f, 0.0f, 0.0f,
	-0.4f, 0.6f, -0.2f,		0.42684f,	0.6875f,		1.0f, 0.0f, 0.0f,
	-0.4f, 0.6f, 0.2f,		0.57025f,	0.6875f,	1.0f, 0.0f, 0.0f,

	//ATRAS
	-0.4f, -0.6f, -0.2f,	0.8561f,	0.71366f,			0.0f, 0.0f, 1.0f,
	0.4f, -0.6f, -0.2f,		0.99903f,	0.71366f,		0.0f, 0.0f, 1.0f,
	0.4f, 0.6f, -0.2f,		0.99903f,	0.85658f,	0.0f, 0.0f, 1.0f,
	-0.4f, 0.6f, -0.2f,		0.8561f,	0.85658f,		0.0f, 0.0f, 1.0f,

	//ARRIBA
	0.4f, 0.6f, 0.2f,		0.71317f,	0.85658f,	0.0f, -1.0f, 0.0f,
	0.4f, 0.6f, -0.2f,		0.71317f,	0.99903f,	0.0f, -1.0f, 0.0f,
	-0.4f, 0.6f, -0.2f,		0.57025f,	0.99903f,	0.0f, -1.0f, 0.0f,
	-0.4f, 0.6f, 0.2f,		0.57025f,	0.85658f,	0.0f, -1.0f, 0.0f,

	//ABAJO
	0.4f, -0.6f, -0.2f,		0.71317f,	0.71366f,	0.0f, 1.0f, 0.0f,
	-0.4f, -0.6f, -0.2f,	0.57025f,	0.71366f,	0.0f, 1.0f, 0.0f,
	-0.4f, -0.6f, 0.2f,		0.57025f,	0.57073f,	0.0f, 1.0f, 0.0f,
	0.4f, -0.6f, 0.2f,		0.71317f,	0.57073f,	0.0f, 1.0f, 0.0f,

	//CABEZA
	//FRENTE
	-0.4f, 0.6f, 0.4f,		0.11579f,	0.62839f,	0.0f, 0.0f, -1.0f,
	0.4f, 0.6f, 0.4f,		0.24872f,	0.62839f,	0.0f, 0.0f, -1.0f,
	0.4f, 1.4f, 0.4f,		0.24872f,	0.74273f,		0.0f, 0.0f, -1.0f,
	-0.4f, 1.4f, 0.4f,		0.11579f,	0.74273f,		0.0f, 0.0f, -1.0f,

	//DERECHA
	0.4f, 0.6f, 0.4f,		0.24872f,	0.62839f,		-1.0f, 0.0f, 0.0f,
	0.4f, 0.6f, -0.4f,		0.37209f,	0.62839f,		-1.0f, 0.0f, 0.0f,
	0.4f, 1.4f, -0.4f,		0.37209f,	0.74273f,		-1.0f, 0.0f, 0.0f,
	0.4f, 1.4f, 0.4f,		0.24872f,	0.74273f,		-1.0f, 0.0f, 0.0f,

	//IZQUIERDA
	-0.4f, 0.6f, 0.4f,		0.11579f,	0.62839f,		1.0f, 0.0f, 0.0f,
	-0.4f, 0.6f, -0.4f,		0.0f,		0.62839f,		1.0f, 0.0f, 0.0f,
	-0.4f, 1.4f, -0.4f,		0.0f,		0.74273f,		1.0f, 0.0f, 0.0f,
	-0.4f, 1.4f, 0.4f,		0.11579f,	0.74273f,		1.0f, 0.0f, 0.0f,

	//ATRAS
	-0.4f, 0.6f, -0.4f,		0.11579f,	0.97189f,		0.0f, 0.0f, 1.0f,
	0.4f, 0.6f, -0.4f,		0.24872f,	0.97189f,		0.0f, 0.0f, 1.0f,
	0.4f, 1.4f, -0.4f,		0.24872f,	0.85755f,		0.0f, 0.0f, 1.0f,
	-0.4f, 1.4f, -0.4f,		0.11579f,	0.85755f,		0.0f, 0.0f, 1.0f,

	//ARRIBA
	0.4f, 1.4f, 0.4f,		0.24872f, 0.74273f,		0.0f, -1.0f, 0.0f,
	0.4f, 1.4f, -0.4f,		0.24872f, 0.85755f,		0.0f, -1.0f, 0.0f,
	-0.4f, 1.4f, -0.4f,		0.11579f, 0.85755f,		0.0f, -1.0f, 0.0f,
	-0.4f, 1.4f, 0.4f,		0.11579f, 0.74273f,		0.0f, -1.0f, 0.0f,

	//ABAJO
	0.4f, 0.6f, -0.4f,		0.24872f, 0.51453f,		0.0f, 1.0f, 0.0f,
	-0.4f, 0.6f, -0.4f,		0.11579f, 0.51453f,		0.0f, 1.0f, 0.0f,
	-0.4f, 0.6f, 0.4f,		0.11579f, 0.62839f,		0.0f, 1.0f, 0.0f,
	0.4f, 0.6f, 0.4f,		0.24872f, 0.62839f,		0.0f, 1.0f, 0.0f,
	/////////
	//PIERNA IZQ
	//FRENTE
	-0.4f, -1.8f, 0.2f,		0.12693f, 0.05859f,		0.0f, 0.0f, -1.0f,
	0.0f, -1.8f, 0.2f,		0.18410f, 0.05859f,		0.0f, 0.0f, -1.0f,
	0.0f, -0.6f, 0.2f,		0.18410f, 0.22916f,	0.0f, 0.0f, -1.0f,
	-0.4f, -0.6f, 0.2f,		0.12693f, 0.22916f,	0.0f, 0.0f, -1.0f,

	//DERECHA
	0.0f, -1.8f, 0.2f,		0.18410f, 0.05859f,		-1.0f, 0.0f, 0.0f,
	0.0f, -1.8f, -0.2f,		0.24127f, 0.05859,		-1.0f, 0.0f, 0.0f,
	0.0f, -0.6f, -0.2f,		0.24127f, 0.22916f,	-1.0f, 0.0f, 0.0f,
	0.0f, -0.6f, 0.2f,		0.18410f, 0.22916f,		-1.0f, 0.0f, 0.0f,

	//IZQUIERDA
	-0.4f, -1.8f, 0.2f,		0.12693f, 0.05859f,		1.0f, 0.0f, 0.0f,
	-0.4f, -1.8f, -0.2f,	0.06976f, 0.05859f,		1.0f, 0.0f, 0.0f,
	-0.4f, -0.6f, -0.2f,	0.06976f, 0.22916f,		1.0f, 0.0f, 0.0f,
	-0.4f, -0.6f, 0.2f,		0.12693f, 0.22916f,		1.0f, 0.0f, 0.0f,

	//ATRAS
	0.0f, -1.8f, -0.2f,		0.24127f, 0.05859,		0.0f, 0.0f, 1.0f,
	-0.4f, -1.8f, -0.2f,	0.29844f, 0.05859,		0.0f, 0.0f, 1.0f,
	-0.4f, -0.6f, -0.2f,	0.29844f, 0.22916f,		0.0f, 0.0f, 1.0f,
	0.0f, -0.6f, -0.2f,		0.24127f, 0.22916f,		0.0f, 0.0f, 1.0f,

	//ARRIBA
	0.0f, -0.6f, 0.2f,		0.24127f, 0.22916f,		0.0f, -1.0f, 0.0f,
	0.0f, -0.6f, -0.2f,		0.24127f, 0.28585f,		0.0f, -1.0f, 0.0f,
	-0.4f, -0.6f, -0.2f,	0.1841f, 0.28585f,		0.0f, -1.0f, 0.0f,
	-0.4f, -0.6f, 0.2f,		0.18410f, 0.22916f,		0.0f, -1.0f, 0.0f,

	//ABAJO
	0.0f, -1.8f, 0.2f,		0.18410f, 0.05859f,		0.0f, 1.0f, 0.0f,
	0.0f, -1.8f, -0.2f,		0.18410f, 0.0f,			0.0f, 1.0f, 0.0f,
	-0.4f, -1.8f, -0.2f,	0.12693f, 0.0f,		0.0f, 1.0f, 0.0f,
	-0.4f, -1.8f, 0.2f,		0.12693f, 0.05859f,		0.0f, 1.0f, 0.0f,

	//PIERNA DER
	//FRENTE
	0.0f, -1.8f, 0.2f,		0.12693f, 0.05859f,		0.0f, 0.0f, -1.0f,
	0.4f, -1.8f, 0.2f,		0.18410f, 0.05859f,		0.0f, 0.0f, -1.0f,
	0.4f, -0.6f, 0.2f,		0.18410f, 0.22916f,	0.0f, 0.0f, -1.0f,
	0.0f, -0.6f, 0.2f,		0.12693f, 0.22916f,	0.0f, 0.0f, -1.0f,

	//DERECHA
	0.4f, -1.8f, 0.2f,		0.18410f, 0.05859f,		-1.0f, 0.0f, 0.0f,
	0.4f, -1.8f, -0.2f,		0.24127f, 0.05859,		-1.0f, 0.0f, 0.0f,
	0.4f, -0.6f, -0.2f,		0.24127f, 0.22916f,	-1.0f, 0.0f, 0.0f,
	0.4f, -0.6f, 0.2f,		0.18410f, 0.22916f,		-1.0f, 0.0f, 0.0f,

	//IZQUIERDA
	0.0f, -1.8f, 0.2f,		0.12693f, 0.05859f,		1.0f, 0.0f, 0.0f,
	0.0f, -1.8f, -0.2f,		0.06976f, 0.05859f,		1.0f, 0.0f, 0.0f,
	0.0f, -0.6f, -0.2f,		0.06976f, 0.22916f,	1.0f, 0.0f, 0.0f,
	0.0f, -0.6f, 0.2f,		0.12693f, 0.22916f,		1.0f, 0.0f, 0.0f,

	//ATRAS
	0.4f, -1.8f, -0.2f,		0.24127f, 0.05859,		0.0f, 0.0f, 1.0f,
	0.0f, -1.8f, -0.2f,		0.29844f, 0.05859,		0.0f, 0.0f, 1.0f,
	0.0f, -0.6f, -0.2f,		0.29844f, 0.22916f,		0.0f, 0.0f, 1.0f,
	0.4f, -0.6f, -0.2f,		0.24127f, 0.22916f,		0.0f, 0.0f, 1.0f,

	//ARRIBA
	0.4f, -0.6f, 0.2f,		0.24127f, 0.22916f,	0.0f, -1.0f, 0.0f,
	0.4f, -0.6f, -0.2f,		0.24127f, 0.28585f,	0.0f, -1.0f, 0.0f,
	0.0f, -0.6f, -0.2f,		0.1841f, 0.28585f,		0.0f, -1.0f, 0.0f,
	0.0f, -0.6f, 0.2f,		0.18410f, 0.22916f,		0.0f, -1.0f, 0.0f,

	//ABAJO
	0.4f, -1.8f, 0.2f,		0.18410f, 0.05859f,	0.0f, 1.0f, 0.0f,
	0.4f, -1.8f, -0.2f,		0.18410f, 0.0f,		0.0f, 1.0f, 0.0f,
	0.0f, -1.8f, -0.2f,		0.12693f, 0.0f,		0.0f, 1.0f, 0.0f,
	0.0f, -1.8f, 0.2f,		0.12693f, 0.05859f,		0.0f, 1.0f, 0.0f,

	//BRAZO IZQ////////////////////////////////////////////////////////////->
	//FRENTE
	0.4f, -0.6f, 0.2f,		0.69282f, 0.33478f,		0.0f, 0.0f, -1.0f,
	0.8f, -0.6f, 0.2f,		0.72093f, 0.33478f,		0.0f, 0.0f, -1.0f,
	0.8f, 0.6f, 0.2f,		0.72093f, 0.47819f,		0.0f, 0.0f, -1.0f,
	0.4f, 0.6f, 0.2f,		0.69282f, 0.47819f,		0.0f, 0.0f, -1.0f,

	//DERECHA
	0.8f, -0.6f, 0.2f,		0.72093f, 0.33478f,		-1.0f, 0.0f, 0.0f,
	0.8f, -0.6f, -0.2f,		0.7495f, 0.33478f,		-1.0f, 0.0f, 0.0f,
	0.8f, 0.6f, -0.2f,		0.7495f, 0.47819f,		-1.0f, 0.0f, 0.0f,
	0.8f, 0.6f, 0.2f,		0.72093f, 0.47819f,		-1.0f, 0.0f, 0.0f,

	//IZQUIERDA
	0.4f, -0.6f, -0.2f,		0.80668f, 0.33478f,		1.0f, 0.0f, 0.0f,
	0.4f, -0.6f, 0.2f,		0.778585f, 0.33478f,		1.0f, 0.0f, 0.0f,
	0.4f, 0.6f, 0.2f,		0.778585f, 0.47819f,	1.0f, 0.0f, 0.0f,
	0.4f, 0.6f, -0.2f,		0.80668f, 0.47819f,	1.0f, 0.0f, 0.0f,

	//ATRAS
	0.8f, -0.6f, -0.2f,		0.7495f, 0.33478f,		0.0f, 0.0f, 1.0f,
	0.4f, -0.6f, -0.2f,		0.778585f, 0.33478f,	0.0f, 0.0f, 1.0f,
	0.4f, 0.6f, -0.2f,		0.778585f, 0.47819f,	0.0f, 0.0f, 1.0f,
	0.8f, 0.6f, -0.2f,		0.7495f, 0.47819f,		0.0f, 0.0f, 1.0f,

	//ARRIBA
	0.4f, 0.6f, 0.2f,		0.778585f, 0.47819f,	0.0f, -1.0f, 0.0f,
	0.8f, 0.6f, 0.2f,		0.80668f, 0.47819f,		0.0f, -1.0f, 0.0f,
	0.8f, 0.6f, -0.2f,		0.80668f, 0.50678f,		0.0f, -1.0f, 0.0f,
	0.4f, 0.6f, -0.2f,		0.778585f, 0.50678f,		0.0f, -1.0f, 0.0f,

	//ABAJO
	0.4f, -0.6f, -0.2f,		0.69282f, 0.3062f,	0.0f, 1.0f, 0.0f,
	0.8f, -0.6f, -0.2f,		0.72093f, 0.3062f,	0.0f, 1.0f, 0.0f,
	0.8f, -0.6f, 0.2f,		0.72093f, 0.33478f,		0.0f, 1.0f, 0.0f,
	0.4f, -0.6f, 0.2f,		0.69282f, 0.33478f,		0.0f, 1.0f, 0.0f,

	//BRAZO DER////////////////////////////77 - >
	//FRENTE
	-0.4f, -0.6f, 0.2f,		0.69282f, 0.33478f,		0.0f, 0.0f, -1.0f,
	-0.8f, -0.6f, 0.2f,		0.72093f, 0.33478f,		0.0f, 0.0f, -1.0f,
	-0.8f, 0.6f, 0.2f,		0.72093f, 0.47819,		0.0f, 0.0f, -1.0f,
	-0.4f, 0.6f, 0.2f,		0.69282f, 0.47819f,	0.0f, 0.0f, -1.0f,

	//DERECHA
	-0.8f, -0.6f, 0.2f,		0.72093f, 0.33478f,		-1.0f, 0.0f, 0.0f,
	-0.8f, -0.6f, -0.2f,	0.7495f, 0.33478f,		-1.0f, 0.0f, 0.0f,
	-0.8f, 0.6f, -0.2f,		0.7495f, 0.47819f,		-1.0f, 0.0f, 0.0f,
	-0.8f, 0.6f, 0.2f,		0.72093f, 0.47819f,		-1.0f, 0.0f, 0.0f,

	//IZQUIERDA
	-0.4f, -0.6f, -0.2f,	0.80668f, 0.33478f,		1.0f, 0.0f, 0.0f,
	-0.4f, -0.6f, 0.2f,		0.778585f, 0.33478f,	1.0f, 0.0f, 0.0f,
	-0.4f, 0.6f, 0.2f,		0.778585f, 0.47819f,	1.0f, 0.0f, 0.0f,
	-0.4f, 0.6f, -0.2f,		0.80668f, 0.47819f,		1.0f, 0.0f, 0.0f,

	//ATRAS
	-0.8f, -0.6f, -0.2f,	0.7495f, 0.33478f,		0.0f, 0.0f, 1.0f,
	-0.4f, -0.6f, -0.2f,	0.778585f, 0.33478f,	0.0f, 0.0f, 1.0f,
	-0.4f, 0.6f, -0.2f,		0.778585f, 0.47819f,	0.0f, 0.0f, 1.0f,
	-0.8f, 0.6f, -0.2f,		0.7495f, 0.47819f,		0.0f, 0.0f, 1.0f,

	//ARRIBA
	-0.4f, 0.6f, 0.2f,		0.778585f, 0.47819f,	0.0f, -1.0f, 0.0f,
	-0.8f, 0.6f, 0.2f,		0.80668f, 0.47819f,		0.0f, -1.0f, 0.0f,
	-0.8f, 0.6f, -0.2f,		0.80668f, 0.50678f,		0.0f, -1.0f, 0.0f,
	-0.4f, 0.6f, -0.2f,		0.778585f, 0.50678f,		0.0f, -1.0f, 0.0f,

	//ABAJO
	-0.4f, -0.6f, -0.2f,	0.69282f, 0.3062f,		0.0f, 1.0f, 0.0f,
	-0.8f, -0.6f, -0.2f,	0.72093f, 0.3062f,		0.0f, 1.0f, 0.0f,
	-0.8f, -0.6f, 0.2f,		0.72093f, 0.33478f,		0.0f, 1.0f, 0.0f,
	-0.4f, -0.6f, 0.2f,		0.69282f, 0.33478f,		0.0f, 1.0f, 0.0f,

};

	Mesh* lorax = new Mesh();
	lorax->CreateMesh(vertices, indices, sizeof(vertices) / 4, sizeof(indices) / 4);
	meshList.push_back(lorax);


}

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearCuatro();
	CrearLorax();
	CreateShaders();


	//camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);
	cameraP = Camera(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 0.1f, 0.5f);
	cameraA = Camera(glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.1f, 0.5f);

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

	loraxTexture = Texture("Textures/textura_LORAX.png");
	loraxTexture.LoadTextureA();

	caminoTexture = Texture("Textures/camino.png");
	caminoTexture.LoadTexture();

	fogataTexture = Texture("Textures/Fogata.png");
	fogataTexture.LoadTexture();

	
	

		
	ArmaKND_M = Model();
	ArmaKND_M.LoadModel("Models/base_arma.obj");

	LanzaderaKND_M = Model();
	LanzaderaKND_M.LoadModel("Models/lanzadera_arma.obj");

	CasaLorax_M = Model();
	//CasaLorax_M.LoadModel("Models/casa_Lorax.obj");

	//////PROYECTO FINAL

	arbol_T = Model();
	arbol_T.LoadModel("Models/tronco.obj");

	arbol_H = Model();
	arbol_H.LoadModel("Models/hojas.obj");

	cuerpo_pez = Model();
	cuerpo_pez.LoadModel("Models/cuerpo_pez.obj");
	hombro_pez = Model();
	hombro_pez.LoadModel("Models/hombro_pez.obj");
	brazo_der_pez = Model();
	brazo_der_pez.LoadModel("Models/brazo_der_pez.obj");
	conejo_izq_pez = Model();
	conejo_izq_pez.LoadModel("Models/conejo_izq_pez.obj");
	mano_izq_pez = Model();
	mano_izq_pez.LoadModel("Models/mano_izq_pez.obj");
	pie_izq = Model();
	pie_izq.LoadModel("Models/pie_izq_pez.obj");
	pie_der = Model();
	pie_der.LoadModel("Models/pie_der_pez.obj");
	piedra = Model();
	piedra.LoadModel("Models/piedras_bueno.obj");

	//ILUMINACION
	antorcha = Model();
	antorcha.LoadModel("Models/Torch.obj");

	Fogata_M = Model();
	Fogata_M.LoadModel("Models/Fogata.obj");

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
	//Chimenea_M.LoadModel("Models/chimenea_opt.obj");

	Ruedita_M = Model();
	Ruedita_M.LoadModel("Models/tire-tx.obj");

	SimioArcoiris_M = Model();
	SimioArcoiris_M.LoadModel("Models/SimioArcoiris_obj_Texture_C.obj");

	AntenaSimio_M = Model();
	AntenaSimio_M.LoadModel("Models/SimioArcoiris_obj_Texture_A.obj");

	Camino_M = Model();
	Camino_M.LoadModel("Models/camino.obj");

	Pasto_M = Model();
	Pasto_M.LoadModel("Models/pasto.obj");

	std::vector<std::string> skyboxFaces;
	std::vector<std::string> skyboxFacesN;
	
	//Texturas de skyboard
	skyboxFaces.push_back("Textures/Skybox/desert_bk.tga"); //bk
	skyboxFaces.push_back("Textures/Skybox/desert_ft.tga"); //ft
	skyboxFaces.push_back("Textures/Skybox/desert_dn.tga"); //dn
	skyboxFaces.push_back("Textures/Skybox/desert_up.tga"); //up
	skyboxFaces.push_back("Textures/Skybox/desert_lt.tga"); //lt
	skyboxFaces.push_back("Textures/Skybox/desert_rt.tga"); //rt

	skybox = Skybox(skyboxFaces);
	//SKYBOX NOCHE
	skyboxFacesN.push_back("Textures/Skybox/desert_noche_bk.tga"); //bk
	skyboxFacesN.push_back("Textures/Skybox/desert_noche_ft.tga"); //ft
	skyboxFacesN.push_back("Textures/Skybox/desert_noche_dn.tga"); //dn
	skyboxFacesN.push_back("Textures/Skybox/desert_noche_up.tga"); //up
	skyboxFacesN.push_back("Textures/Skybox/desert_noche_lt.tga"); //lt
	skyboxFacesN.push_back("Textures/Skybox/desert_noche_rt.tga"); //rt

	skyboxNoche = Skybox(skyboxFacesN);

	//Material_brillante = Material(4.0f, 256);
	//Material_opaco = Material(0.3f, 4);

	//ILUMINACION
	//luz direccional, sólo 1 y siempre debe de existir

	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, //el primero la luz 1 - DIA 0.3 NOCHE
		0.0f, 0.0f, -1.0f);


	//contadores de luces puntuales y spotlight
	unsigned int pointLightCount = 0;
	unsigned int spotLightCount = 0;
	glm::vec3 pos_per = cameraP.getCameraPosition();

	//Declaración de primer luz puntual
			//model = glm::translate(model, glm::vec3(2.0f, -0.5f, -25.0f));
		//model = glm::translate(model, glm::vec3(-1.0f, -0.5f, -15.0f));
		//model = glm::translate(model, glm::vec3(-5.0f, -0.5f, 2.0f));
		//model = glm::translate(model, glm::vec3(-2.0f, -0.5f, 15.0f));
		//model = glm::translate(model, glm::vec3(1.0f, -0.5f, 25.0f));
		//model = glm::translate(model, glm::vec3(25.0f, -0.5f, -2.0f));
		//model = glm::translate(model, glm::vec3(15.0f, -0.5f, 1.0f));

	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.4f, 0.2f,
		0.0f, 0.0f, -1.0f);
	////model = glm::translate(model, glm::vec3(2.0f, -0.5f, -25.0f));
	arrPointLights[0] = PointLight(0.8980f, 0.4901f, 0.2078f,
		1.0f, 0.7f,
		2.0f, 1.0f, -25.0f, //posición
		0.3f, 0.2f, 0.1f); //coeficientes de la ecuación de 2do grado


	////model = glm::translate(model, glm::vec3(-1.0f, -0.5f, -15.0f));
	arrPointLights[1] = PointLight(0.8980f, 0.4901f, 0.2078f,
		1.0f, 0.7f,
		-1.0f, 1.0f, -15.0f, //posición
		0.3f, 0.2f, 0.1f); //coeficientes de la ecuación de 2do grado

	/*model = glm::translate(model, glm::vec3(-5.0f, -0.5f, 2.0f));*/
	arrPointLights[2] = PointLight(0.8980f, 0.4901f, 0.2078f,
		1.0f, 0.7f,
		-5.0f, 1.0f, 2.0f, //posición
		0.3f, 0.2f, 0.1f); //coeficientes de la ecuación de 2do grado
	
	//model = glm::translate(model, glm::vec3(-2.0f, -0.5f, 15.0f));
	arrPointLights[3] = PointLight(0.8980f, 0.4901f, 0.2078f,
		1.0f, 0.7f,
		-2.0f, 1.0f, 15.0f, //posición
		0.3f, 0.2f, 0.1f); //coeficientes de la ecuación de 2do grado

	//model = glm::translate(model, glm::vec3(1.0f, -0.5f, 25.0f));
	arrPointLights[4] = PointLight(0.8980f, 0.4901f, 0.2078f,
		1.0f, 0.7f,
		1.0f, 1.0f, 25.0f, //posición
		0.3f, 0.2f, 0.1f); //coeficientes de la ecuación de 2do grado

	//model = glm::translate(model, glm::vec3(25.0f, -0.5f, -2.0f));
	arrPointLights[5] = PointLight(0.8980f, 0.4901f, 0.2078f,
		1.0f, 0.7f,
		25.0f, 1.0f, -2.0f, //posición
		0.3f, 0.2f, 0.1f); //coeficientes de la ecuación de 2do grado

	//model = glm::translate(model, glm::vec3(15.0f, -0.5f, 1.0f));
	arrPointLights[6] = PointLight(0.8980f, 0.4901f, 0.2078f,
		1.0f, 0.7f,
		15.0f, 1.0f, 1.0f, //posición
		0.3f, 0.2f, 0.1f); //coeficientes de la ecuación de 2do grado



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
		pos_per = cameraP.getCameraPosition();
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;




		//Recibir eventos del usuario
		glfwPollEvents();
		
		//TIPO DE CAMARA
		if (mainWindow.gettipoCamara() == 0) { //0 = PEGADA AL PISO, 1= AEREA
			cameraP.mouseControl(mainWindow.getXChange(), mainWindow.getYChange(), mainWindow.gettipoCamara());
			cameraP.keyControl(mainWindow.getsKeys(), deltaTime, mainWindow.gettipoCamara());
			//pegada al piso
			camera = cameraP;
		}
		else {
			//aerea
			cameraA.mouseControl(0.0f, -90.0f, mainWindow.gettipoCamara());
			cameraA.keyControl(mainWindow.getsKeys(), deltaTime, mainWindow.gettipoCamara());
			camera = cameraA;
		}

		//printf("( %f , %f , %f ) %f \n", camera.getCameraPosition().x, camera.getCameraPosition().y , camera.getCameraPosition().z, camera.getCameraDirection());
		
		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	if (contadorSkybox < (40000)) {
		if (banderaSkybox) {
			skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
			mainLight.SetIntensity(1.0f);
			pointLightCount = 0;
		}
		else {
			//Es de noche
			skyboxNoche.DrawSkybox(camera.calculateViewMatrix(), projection);
			mainLight.SetIntensity(0.3f);
			if (pos_per.z <-10 ) {
				pointLights[0] = arrPointLights[0];
				pointLights[1] = arrPointLights[1];
				pointLightCount = 2;
			}
			else if(pos_per.x >10){
				pointLights[0] = arrPointLights[6];
				pointLights[1] = arrPointLights[5];
				pointLightCount = 2;
			}
			else if (pos_per.z > 10) {
				pointLights[0] = arrPointLights[3];
				pointLights[1] = arrPointLights[4];
				pointLightCount = 2;
			}
			else {
				pointLights[0] = arrPointLights[2];
				pointLightCount = 1;
			}
		}
		contadorSkybox++;
	}
	else {
		contadorSkybox = 0;
		banderaSkybox = !banderaSkybox;
	}
	printf(" \n %d", contadorSkybox);
	//printf("la camara piso: %f | %f | %f \n", pos)
	//printf(" \n %d", contadorSkybox);

	shaderList[0].UseShader();
	uniformModel = shaderList[0].GetModelLocation();
	uniformProjection = shaderList[0].GetProjectionLocation();
	uniformView = shaderList[0].GetViewLocation();
	uniformEyePosition = shaderList[0].GetEyePositionLocation();
	uniformColor = shaderList[0].getColorLocation();

	//información en el shader de intensidad especular y brillo
	uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
	uniformShininess = shaderList[0].GetShininessLocation();

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
	glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

	// luz ligada a la cámara de tipo flash
	//glm::vec3 lowerLight = camera.getCameraPosition();
	//lowerLight.y -= 0.3f;
	// spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

	//información al shader de fuentes de iluminación
	shaderList[0].SetDirectionalLight(&mainLight);
	shaderList[0].SetPointLights(pointLights, pointLightCount);
	shaderList[0].SetSpotLights(spotLights, spotLightCount);


		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 simios_aux(1.0);
		glm::mat4 cortadora_aux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::mat4 pezpoq_aux(1.0);
		glm::mat4 pezpoq_aux_2(1.0);
		glm::mat4 pezpoq_aux_3(1.0);
		glm::mat4 arbol_aux(1.0);


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 1.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, 5.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArmaKND_M.RenderModel();


		//pisoTexture.UseTexture();
		//meshList[2]->RenderMesh();
		//PISO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.2f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		//PEZ POK
		//		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//		model = glm::translate(model, glm::vec3(-90.0f, 0.0f, -1.0));
		//
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::translate(model, glm::vec3(90.0f, 2.0f, -5.0));
		pezpoq_aux = model; // se guarda el centro del pez
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		pezpoq_aux_3 = model;
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuerpo_pez.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux;
		model = glm::translate(model, glm::vec3(1.3f, 0.32f, -0.21f));
		pezpoq_aux_2 = model;
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hombro_pez.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux;
		model = glm::translate(model, glm::vec3(-1.2f, 0.32f, 0.11f));
		pezpoq_aux = model;
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hombro_pez.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux;
		model = glm::translate(model, glm::vec3(-0.3f, 0.0f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazo_der_pez.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux_2;
		model = glm::translate(model, glm::vec3(0.2f, -0.1f, 0.4f));
		pezpoq_aux_2 = model;
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		conejo_izq_pez.RenderModel();

		//es el codo va aaqui

		model = glm::mat4(1.0);
		model = pezpoq_aux_2;
		model = glm::translate(model, glm::vec3(-0.1f, 0.2f, 0.6f));
		pezpoq_aux_2 = model;
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mano_izq_pez.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux_3;
		model = glm::translate(model, glm::vec3(-0.2f, -2.6f, -0.2f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pie_izq.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux_3;
		model = glm::translate(model, glm::vec3(0.23f, -2.5f, -0.2f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pie_der.RenderModel();

		//PEZ 2
				//PEZ POK
		//		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//		model = glm::translate(model, glm::vec3(-90.0f, 0.0f, -1.0));
		//
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::translate(model, glm::vec3(85.0f, 2.0f, -1.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		pezpoq_aux = model; // se guarda el centro del pez
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		pezpoq_aux_3 = model;
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuerpo_pez.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux;
		model = glm::translate(model, glm::vec3(1.3f, 0.32f, -0.21f));
		pezpoq_aux_2 = model;
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hombro_pez.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux;
		model = glm::translate(model, glm::vec3(-1.2f, 0.32f, 0.11f));
		pezpoq_aux = model;
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hombro_pez.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux;
		model = glm::translate(model, glm::vec3(-0.3f, 0.0f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazo_der_pez.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux_2;
		model = glm::translate(model, glm::vec3(0.2f, -0.1f, 0.4f));
		pezpoq_aux_2 = model;
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		conejo_izq_pez.RenderModel();

		//es el codo va aaqui

		model = glm::mat4(1.0);
		model = pezpoq_aux_2;
		model = glm::translate(model, glm::vec3(-0.1f, 0.2f, 0.6f));
		pezpoq_aux_2 = model;
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mano_izq_pez.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux_3;
		model = glm::translate(model, glm::vec3(-0.2f, -2.6f, -0.2f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pie_izq.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux_3;
		model = glm::translate(model, glm::vec3(0.23f, -2.5f, -0.2f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pie_der.RenderModel();



		//pez 3
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::translate(model, glm::vec3(90.0f, 2.0f, 5.0));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		pezpoq_aux = model; // se guarda el centro del pez
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		pezpoq_aux_3 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuerpo_pez.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux;
		model = glm::translate(model, glm::vec3(1.3f, 0.32f, -0.21f));
		pezpoq_aux_2 = model;
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hombro_pez.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux;
		model = glm::translate(model, glm::vec3(-1.2f, 0.32f, 0.11f));
		pezpoq_aux = model;
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hombro_pez.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux;
		model = glm::translate(model, glm::vec3(-0.3f, 0.0f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazo_der_pez.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux_2;
		model = glm::translate(model, glm::vec3(0.2f, -0.1f, 0.4f));
		pezpoq_aux_2 = model;
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		conejo_izq_pez.RenderModel();

		//es el codo va aaqui

		model = glm::mat4(1.0);
		model = pezpoq_aux_2;
		model = glm::translate(model, glm::vec3(-0.1f, 0.2f, 0.6f));
		pezpoq_aux_2 = model;
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mano_izq_pez.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux_3;
		model = glm::translate(model, glm::vec3(-0.2f, -2.6f, -0.2f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pie_izq.RenderModel();

		model = glm::mat4(1.0);
		model = pezpoq_aux_3;
		model = glm::translate(model, glm::vec3(0.23f, -2.5f, -0.2f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pie_der.RenderModel();


		model = modelaux;
		model = glm::translate(model, glm::vec3(-12.6f, 0.0f, 12.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();
    
		model = modelaux;
		model = glm::translate(model, glm::vec3(-12.6f, 0.0f, -12.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(12.6f, 0.0f, 12.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(12.6f, 0.0f, -12.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(25.2f, 0.0f, -25.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(12.6f, 0.0f, -25.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(25.2f, 0.0f, -12.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		//

		model = modelaux;
		model = glm::translate(model, glm::vec3(-25.2f, 0.0f, -25.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-12.6f, 0.0f, -25.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-25.2f, 0.0f, -12.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();
		//

		model = modelaux;
		model = glm::translate(model, glm::vec3(-25.2f, 0.0f, 25.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-12.6f, 0.0f, 25.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-25.2f, 0.0f, 12.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();
		//

		model = modelaux;
		model = glm::translate(model, glm::vec3(25.2f, 0.0f, 25.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(12.6f, 0.0f, 25.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(25.2f, 0.0f, 12.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();
		//

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 12.6f));
		model = glm::rotate(model, 90*toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Camino_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 25.2f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Camino_M.RenderModel();

		//


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -12.6f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Camino_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -25.2f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Camino_M.RenderModel();
		//

		//
		model = modelaux;
		model = glm::translate(model, glm::vec3(12.6f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Camino_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(25.2f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Camino_M.RenderModel();
		//
		//
		model = modelaux;
		model = glm::translate(model, glm::vec3(-12.6f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Camino_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-25.2f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Camino_M.RenderModel();
		//
	
		//BORDE EXT
		model = modelaux;
		model = glm::translate(model, glm::vec3(-37.8f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-37.8f, 0.0f, 12.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-37.8f, 0.0f, -12.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-37.8f, 0.0f, 25.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-37.8f, 0.0f, -25.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-37.8f, 0.0f, 37.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-37.8f, 0.0f, -37.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();
		//**
		model = modelaux;
		model = glm::translate(model, glm::vec3(37.8f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(37.8f, 0.0f, 12.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(37.8f, 0.0f, -12.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(37.8f, 0.0f, 25.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(37.8f, 0.0f, -25.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(37.8f, 0.0f, 37.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(37.8f, 0.0f, -37.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -37.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(12.6f, 0.0f, -37.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(25.2f, 0.0f, -37.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-12.6f, 0.0f, -37.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-25.2f, 0.0f, -37.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		//**
		// 
		model = modelaux;
		model = glm::translate(model, glm::vec3(37.8f, 0.0f, 37.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 37.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(12.6f, 0.0f, 37.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(25.2f, 0.0f, 37.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-12.6f, 0.0f, 37.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-25.2f, 0.0f, 37.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto_M.RenderModel();
		//


		//	Simio Arcoiris
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0));

		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		//Cortadora_M.RenderModel();
		//Blackhawk_M.RenderModel();
	

		//CORTADORA DE ARBOLES
		//Se hace una jerarquizaciÃ³n partiendo del cuerpo de la cortadora
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		model = glm::translate(model, glm::vec3(-30.0f, 1.5f, -1.0));
		cortadora_aux = model;
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

	
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 10.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuatroTexture.UseTexture();
		//meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(pos_per.x, pos_per.y-2, pos_per.z));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		loraxTexture.UseTexture();
		meshList[4]->RenderMesh();

		// ROCA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(27.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piedra.RenderModel();

		//ARBOLES

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -30.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();

		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -28.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));		
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();

		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -26.0f));
		model = glm::scale(model, glm::vec3(0.88f, 0.88f, 0.88f));
		model = glm::rotate(model, 60 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();

		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		//ILUMINACION


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.0f, -0.5f, -25.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		antorcha.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.0f, -0.5f, -15.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		antorcha.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.0f, -0.5f, 15.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		antorcha.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, -0.5f, 25.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		antorcha.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, -0.5f, -2.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		antorcha.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.0f, -0.5f, 1.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		antorcha.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -0.5f, 2.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		antorcha.RenderModel();


		antorcha.RenderModel();


		//FOGATA
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fogata_M.RenderModel();

		//model = glm::mat4(1.0);
		if (giroSimios >= 360.0f) {
			giroSimios = 0.0f;
		}
		giroSimios += 0.1;
		

		//pivote
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.7f, 0.0f));
		//model = glm::rotate(model, ,);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		modelaux = model;
		//r*sin(giroSimios)
		
		//rojo
		model = modelaux;
		model = glm::translate(model, glm::vec3(6.0f*(sin((giroSimios+90.0f)*toRadians)), 0.0f, 6.0f * (cos((giroSimios+90.0f) * toRadians))));
		model = glm::rotate(model, (giroSimios + 0.0f) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		simios_aux = model;
		color = glm::vec3(0.9058f, 0.298f, 0.2352f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SimioArcoiris_M.RenderModel();

		model = simios_aux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AntenaSimio_M.RenderModel();

		//cyan
		model = modelaux;
		model = glm::translate(model, glm::vec3(6.0f * (sin((giroSimios - 90.0f) * toRadians)), 0.0f, 6.0f * (cos((giroSimios - 90.0f) * toRadians))));
		model = glm::rotate(model, (giroSimios + 180.0f) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		simios_aux = model;
		color = glm::vec3(0.3647f, 0.6784f, 0.8862f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SimioArcoiris_M.RenderModel();

		model = simios_aux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AntenaSimio_M.RenderModel();

		//morado
		model = modelaux;
		model = glm::translate(model, glm::vec3(6.0f * (sin((giroSimios + 0.0f) * toRadians)), 0.0f, 6.0f * (cos((giroSimios + 0.0f) * toRadians))));
		model = glm::rotate(model, (giroSimios - 90.0f) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		simios_aux = model;
		color = glm::vec3(0.5568f, 0.2666f, 0.6784f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SimioArcoiris_M.RenderModel();

		model = simios_aux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AntenaSimio_M.RenderModel();

		//amarillo
		model = modelaux;
		model = glm::translate(model, glm::vec3(6.0f * (sin((giroSimios + 180.0f) * toRadians)), 0.0f, 6.0f * (cos((giroSimios + 180.0f) * toRadians))));
		model = glm::rotate(model, (giroSimios + 90.0f) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		simios_aux = model;
		color = glm::vec3(0.9568f, 0.8156f, 0.2470f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SimioArcoiris_M.RenderModel();

		model = simios_aux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AntenaSimio_M.RenderModel();

		//naranja
		model = modelaux;
		model = glm::translate(model, glm::vec3(6.0f * (sin((giroSimios + 135.0f) * toRadians)), 0.0f, 6.0f * (cos((giroSimios + 135.0f) * toRadians))));
		model = glm::rotate(model, (giroSimios + 45.0f) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		simios_aux = model;
		color = glm::vec3(0.9019f, 0.4941f, 0.1333f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SimioArcoiris_M.RenderModel();

		model = simios_aux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AntenaSimio_M.RenderModel();

		//verde
		model = modelaux;
		model = glm::translate(model, glm::vec3(6.0f * (sin((giroSimios + 225.0f) * toRadians)), 0.0f, 6.0f * (cos((giroSimios + 225.0f) * toRadians))));
		model = glm::rotate(model, (giroSimios + 135.0f) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		simios_aux = model;
		color = glm::vec3(0.1529f, 0.6823f, 0.3764f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SimioArcoiris_M.RenderModel();

		model = simios_aux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AntenaSimio_M.RenderModel();

		//azul
		model = modelaux;
		model = glm::translate(model, glm::vec3(6.0f * (sin((giroSimios + 315.0f) * toRadians)), 0.0f, 6.0f * (cos((giroSimios + 315.0f) * toRadians))));
		model = glm::rotate(model, (giroSimios + 225.0f) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		simios_aux = model;
		color = glm::vec3(0.1215f, 0.4392f, 0.7764f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SimioArcoiris_M.RenderModel();

		model = simios_aux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AntenaSimio_M.RenderModel();

		//rosa
		model = modelaux;
		model = glm::translate(model, glm::vec3(6.0f * (sin((giroSimios + 45.0f) * toRadians)), 0.0f, 6.0f * (cos((giroSimios + 45.0f) * toRadians))));
		model = glm::rotate(model, (giroSimios + 315.0f) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		simios_aux = model;
		color = glm::vec3(0.9372f, 0.2491f, 0.9176f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SimioArcoiris_M.RenderModel();

		model = simios_aux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AntenaSimio_M.RenderModel();

		//ARMA KND
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, 5.0f, 10.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		ArmaKND_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LanzaderaKND_M.RenderModel();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
