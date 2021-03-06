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
//MUSICA
#include <irrKlang.h>

//TOROIDES
#include "Toroide.h"

#include "Toroide_f.h"

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

//VARIABLES ANIMACION 1 CORTADORA
float giraHacha;
float giraHachaOffset;
float giroArbol;
float giroHojas;
float giroHojasOffset;
float rotahacha;
bool retrocede;
bool sacudehojas;
bool sacude_der;
int contador_sacude;

//VARIABLES ANIMACION AIRE
bool bandera_aire;
bool bandera_sacude;
bool bandera_sacude_lado;
float sacude_tronco;
float sacude_hojas;
float tira_hojas;
float sacude_troncoOffset;
float sacude_hojasOffset;
float tira_hojasOffset;
int conta_aire = 0;

//VARIABLES ANIMACION AVATAR
float giroAvanza;
float giroAvanzaOffset;
float giroLado;
float giroLadoOffset;
bool banderaAvanza;
bool banderaLado;

//Variables SHOW DE LUCES
bool bandera_show_luces;
bool bandera_giro;
bool bandera_prende_apaga;
int contador_show;
float giro_luz;
float giro_lamp_1;
float giro_lamp_2;
float giro_lamp_3;
float giro_lamp_4;
float giro_lamp_5;
float giro_luz_X;
float giroLuzOffset;
float valX;
float valY;
glm::vec3 pos_lampara1;
glm::vec3 pos_lampara2;
glm::vec3 pos_lampara3;
glm::vec3 pos_lampara4;
glm::vec3 pos_lampara5;

glm::vec3 dir_lampara1;
glm::vec3 dir_lampara2;
glm::vec3 dir_lampara3;
glm::vec3 dir_lampara4;
glm::vec3 dir_lampara5;

bool banderaLamparaPrendida;
bool banderaShowLuces;

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

Texture salvavidasTexture;

Texture prueba;


Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;
Model Aspas_M;
Model ArmaKND_M;
Model LanzaderaKND_M;
Model Pelota_M;
Model CasaLorax_M;
Model SimioArcoiris_M;
Model AntenaSimio_M;
Model Cuatro_M;
Model Fuente_M;
Model Hojas_Piso_M;
Model Hojas_q_caen;

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
Model lampara;
Model base_show;
Model lamp_show;
int inidice_spotlights;
int conteo_spotlights;
bool bandera_lamp;


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

Material Material_opaco;
Material Material_brillante;

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
GLfloat giroSimios = 0.0f;
GLfloat giroArma = 0.0f;
GLboolean banderaArma = true;
// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

PointLight arrPointLights[20];
SpotLight arrSpotLigths[20];

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
	dado->CreateMesh(cubo_vertices, cubo_indices, sizeof(cubo_vertices) / 4, sizeof(cubo_indices) / 4);
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
		22, 23, 20 };

	GLfloat verticesCuerpo[] = {

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
		-0.4f, -0.6f, 0.2f,		0.71317f,	0.71366f,		1.0f, 0.0f, 0.0f,
		-0.4f, -0.6f, -0.2f,	0.42684f,	0.71366f,			1.0f, 0.0f, 0.0f,
		-0.4f, 0.6f, -0.2f,		0.42684f,	0.85658f,		1.0f, 0.0f, 0.0f,
		-0.4f, 0.6f, 0.2f,		0.71317f,	0.85658f,	1.0f, 0.0f, 0.0f,

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
		0.4f, -0.6f, 0.2f,		0.71317f,	0.57073f,	0.0f, 1.0f, 0.0f };
	Mesh* cuerpo = new Mesh();
	cuerpo->CreateMesh(verticesCuerpo, indices, sizeof(verticesCuerpo) / 4, sizeof(indices) / 4);
	meshList.push_back(cuerpo);





	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
	// average normals
	GLfloat verticesCabeza[] = {

		//CABEZA
		//FRENTE
		-0.4f, -0.4f, 0.4f,		0.11579f,	0.62839f,	0.0f, 0.0f, -1.0f,
		0.4f, -0.4f, 0.4f,		0.24872f,	0.62839f,	0.0f, 0.0f, -1.0f,
		0.4f, 0.4f, 0.4f,		0.24872f,	0.74273f,		0.0f, 0.0f, -1.0f,
		-0.4f, 0.4f, 0.4f,		0.11579f,	0.74273f,		0.0f, 0.0f, -1.0f,

		//DERECHA
		0.4f, -0.4f, 0.4f,		0.24872f,	0.62839f,		-1.0f, 0.0f, 0.0f,
		0.4f, -0.4f, -0.4f,		0.37209f,	0.62839f,		-1.0f, 0.0f, 0.0f,
		0.4f, 0.4f, -0.4f,		0.37209f,	0.74273f,		-1.0f, 0.0f, 0.0f,
		0.4f, 0.4f, 0.4f,		0.24872f,	0.74273f,		-1.0f, 0.0f, 0.0f,

		//IZQUIERDA
		-0.4f, -0.4f, 0.4f,		0.11579f,	0.62839f,		1.0f, 0.0f, 0.0f,
		-0.4f, -0.4f, -0.4f,		0.0f,		0.62839f,		1.0f, 0.0f, 0.0f,
		-0.4f, 0.4f, -0.4f,		0.0f,		0.74273f,		1.0f, 0.0f, 0.0f,
		-0.4f, 0.4f, 0.4f,		0.11579f,	0.74273f,		1.0f, 0.0f, 0.0f,

		//ATRAS
		-0.4f, -0.4f, -0.4f,		0.11579f,	0.97189f,		0.0f, 0.0f, 1.0f,
		0.4f, -0.4f, -0.4f,		0.24872f,	0.97189f,		0.0f, 0.0f, 1.0f,
		0.4f, 0.4f, -0.4f,		0.24872f,	0.85755f,		0.0f, 0.0f, 1.0f,
		-0.4f, 0.4f, -0.4f,		0.11579f,	0.85755f,		0.0f, 0.0f, 1.0f,

		//ARRIBA
		0.4f, 0.4f, 0.4f,		0.24872f, 0.74273f,		0.0f, -1.0f, 0.0f,
		0.4f, 0.4f, -0.4f,		0.24872f, 0.85755f,		0.0f, -1.0f, 0.0f,
		-0.4f, 0.4f, -0.4f,		0.11579f, 0.85755f,		0.0f, -1.0f, 0.0f,
		-0.4f, 0.4f, 0.4f,		0.11579f, 0.74273f,		0.0f, -1.0f, 0.0f,

		//ABAJO
		0.4f, -0.4f, -0.4f,		0.24872f, 0.51453f,		0.0f, 1.0f, 0.0f,
		-0.4f, -0.4f, -0.4f,		0.11579f, 0.51453f,		0.0f, 1.0f, 0.0f,
		-0.4f, -0.4f, 0.4f,		0.11579f, 0.62839f,		0.0f, 1.0f, 0.0f,
		0.4f, -0.4f, 0.4f,		0.24872f, 0.62839f,		0.0f, 1.0f, 0.0f };

	Mesh* cabeza = new Mesh();
	cabeza->CreateMesh(verticesCabeza, indices, sizeof(verticesCabeza) / 4, sizeof(indices) / 4);
	meshList.push_back(cabeza);

	GLfloat verticesPiernaIzq[] = {
		//PIERNA IZQ
		//FRENTE
		-0.2f, -0.6f, 0.2f,		0.12693f, 0.05859f,		0.0f, 0.0f, -1.0f,
		0.2f, -0.6f, 0.2f,		0.18410f, 0.05859f,		0.0f, 0.0f, -1.0f,
		0.2f, 0.6f, 0.2f,		0.18410f, 0.22916f,	0.0f, 0.0f, -1.0f,
		-0.2f, 0.6f, 0.2f,		0.12693f, 0.22916f,	0.0f, 0.0f, -1.0f,

		//DERECHA
		0.2f, -0.6f, 0.2f,		0.18410f, 0.05859f,		-1.0f, 0.0f, 0.0f,
		0.2f, -0.6f, -0.2f,		0.24127f, 0.05859,		-1.0f, 0.0f, 0.0f,
		0.2f, 0.6f, -0.2f,		0.24127f, 0.22916f,	-1.0f, 0.0f, 0.0f,
		0.2f, 0.6f, 0.2f,		0.18410f, 0.22916f,		-1.0f, 0.0f, 0.0f,

		//IZQUIERDA
		-0.2f, -0.6f, 0.2f,		0.12693f, 0.05859f,		1.0f, 0.0f, 0.0f,
		-0.2f, -0.6f, -0.2f,	0.06976f, 0.05859f,		1.0f, 0.0f, 0.0f,
		-0.2f, 0.6f, -0.2f,	0.06976f, 0.22916f,		1.0f, 0.0f, 0.0f,
		-0.2f, 0.6f, 0.2f,		0.12693f, 0.22916f,		1.0f, 0.0f, 0.0f,

		//ATRAS
		0.2f, -0.6f, -0.2f,		0.24127f, 0.05859,		0.0f, 0.0f, 1.0f,
		-0.2f, -0.6f, -0.2f,	0.29844f, 0.05859,		0.0f, 0.0f, 1.0f,
		-0.2f, 0.6f, -0.2f,	0.29844f, 0.22916f,		0.0f, 0.0f, 1.0f,
		0.2f, 0.6f, -0.2f,		0.24127f, 0.22916f,		0.0f, 0.0f, 1.0f,

		//ARRIBA
		0.2f, 0.6f, 0.2f,		0.24127f, 0.22916f,		0.0f, -1.0f, 0.0f,
		0.2f, 0.6f, -0.2f,		0.24127f, 0.28585f,		0.0f, -1.0f, 0.0f,
		-0.2f, 0.6f, -0.2f,	0.1841f, 0.28585f,		0.0f, -1.0f, 0.0f,
		-0.2f, 0.6f, 0.2f,		0.18410f, 0.22916f,		0.0f, -1.0f, 0.0f,

		//ABAJO
		0.2f, -0.6f, 0.2f,		0.18410f, 0.05859f,		0.0f, 1.0f, 0.0f,
		0.2f, -0.6f, -0.2f,		0.18410f, 0.0f,			0.0f, 1.0f, 0.0f,
		-0.2f, -0.6f, -0.2f,	0.12693f, 0.0f,		0.0f, 1.0f, 0.0f,
		-0.2f, -0.6f, 0.2f,		0.12693f, 0.05859f,		0.0f, 1.0f, 0.0f };
	Mesh* p_izq = new Mesh();
	p_izq->CreateMesh(verticesPiernaIzq, indices, sizeof(verticesPiernaIzq) / 4, sizeof(indices) / 4);
	meshList.push_back(p_izq);

	GLfloat verticesPiernaDer[] = {
		//PIERNA DER
		//FRENTE
		-0.2f, -0.6f, 0.2f,		0.12693f, 0.05859f,		0.0f, 0.0f, -1.0f,
		0.2f, -0.6f, 0.2f,		0.18410f, 0.05859f,		0.0f, 0.0f, -1.0f,
		0.2f, 0.6f, 0.2f,		0.18410f, 0.22916f,	0.0f, 0.0f, -1.0f,
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
		0.0f, -1.8f, 0.2f,		0.12693f, 0.05859f,		0.0f, 1.0f, 0.0f };
	Mesh* p_der = new Mesh();
	p_der->CreateMesh(verticesPiernaDer, indices, sizeof(verticesPiernaDer) / 4, sizeof(indices) / 4);
	meshList.push_back(p_der);


	GLfloat verticesBrazoIzq[] = {
		//BRAZO IZQ////////////////////////////////////////////////////////////->
		//FRENTE
		-0.2f, -0.6f, 0.2f,		0.69282f, 0.33478f,		0.0f, 0.0f, -1.0f,
		0.2f, -0.6f, 0.2f,		0.72093f, 0.33478f,		0.0f, 0.0f, -1.0f,
		0.2f, 0.6f, 0.2f,			0.72093f, 0.47819f,		0.0f, 0.0f, -1.0f,
		-0.2f, 0.6f, 0.2f,		0.69282f, 0.47819f,		0.0f, 0.0f, -1.0f,

		//DERECHA
		0.2f, -0.6f, 0.2f,		0.72093f, 0.33478f,		-1.0f, 0.0f, 0.0f,
		0.2f, -0.6f, -0.2f,		0.7495f, 0.33478f,		-1.0f, 0.0f, 0.0f,
		0.2f, 0.6f, -0.2f,		0.7495f, 0.47819f,		-1.0f, 0.0f, 0.0f,
		0.2f, 0.6f, 0.2f,		0.72093f, 0.47819f,		-1.0f, 0.0f, 0.0f,

		//IZQUIERDA
		-0.2f, -0.6f, 0.2f,		0.80668f, 0.33478f,		1.0f, 0.0f, 0.0f,
		-0.2f, -0.6f, -0.2f,	0.778585f, 0.33478f,		1.0f, 0.0f, 0.0f,
		-0.2f, 0.6f, -0.2f,		0.778585f, 0.47819f,	1.0f, 0.0f, 0.0f,
		-0.2f, 0.6f, 0.2f,		0.80668f, 0.47819f,	1.0f, 0.0f, 0.0f,

		//ATRAS
		0.2f, -0.6f, -0.2f,		0.7495f, 0.33478f,		0.0f, 0.0f, 1.0f,
		-0.2f, -0.6f, -0.2f,		0.778585f, 0.33478f,	0.0f, 0.0f, 1.0f,
		-0.2f, 0.6f, -0.2f,		0.778585f, 0.47819f,	0.0f, 0.0f, 1.0f,
		0.2f, 0.6f, -0.2f,		0.7495f, 0.47819f,		0.0f, 0.0f, 1.0f,

		//ARRIBA
		0.2f, 0.6f, 0.2f,		0.778585f, 0.47819f,	0.0f, -1.0f, 0.0f,
		0.2f, 0.6f, -0.2f,		0.80668f, 0.47819f,		0.0f, -1.0f, 0.0f,
		-0.2f, 0.6f, -0.2f,		0.80668f, 0.50678f,		0.0f, -1.0f, 0.0f,
		-0.2f, 0.6f, 0.2f,		0.778585f, 0.50678f,		0.0f, -1.0f, 0.0f,

		//ABAJO
		0.2f, -0.6f, 0.2f,		0.69282f, 0.3062f,	0.0f, 1.0f, 0.0f,
		0.2f, -0.6f, -0.2f,		0.72093f, 0.3062f,	0.0f, 1.0f, 0.0f,
		-0.2f, -0.6f, -0.2f,		0.72093f, 0.33478f,		0.0f, 1.0f, 0.0f,
		-0.2f, -0.6f, 0.2f,		0.69282f, 0.33478f,		0.0f, 1.0f, 0.0f };
	Mesh* b_iz = new Mesh();
	b_iz->CreateMesh(verticesBrazoIzq, indices, sizeof(verticesBrazoIzq) / 4, sizeof(indices) / 4);
	meshList.push_back(b_iz);

	GLfloat verticesBrazoDer[] = {
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
	Mesh* b_der = new Mesh();
	b_der->CreateMesh(verticesBrazoDer, indices, sizeof(verticesBrazoDer) / 4, sizeof(indices) / 4);
	meshList.push_back(b_der);

}

void CrearEscenarioShow()
{
	unsigned int indices_escenario[] = {
		// front
		0, 1, 2,
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
		22, 23, 20 };
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
	GLfloat vertices_escenario[] = {
		//FRENTE
		//X		Y		Z		S		T		NX		NY		NZ
		-5.0f, -0.5f, 3.0f,		0.3125f, 0.5f,		0.0f, 0.0f, 1.0f,
		5.0f, -0.5f,  3.0f,		0.4375f, 0.5f,		0.0f, 0.0f, 1.0f,
		5.0f,  0.5f,  3.0f,		0.4375f, 0.6875f,	0.0f, 0.0f, 1.0f,
		-5.0f, 0.5f,  3.0f,		0.3125f, 0.6875f,	0.0f, 0.0f, 1.0f,

		//DERECHA
		5.0f, -0.5f, 3.0f,		0.4375f, 0.5f,		1.0f, 0.0f, 0.0f,
		5.0f, -0.5f, -3.0f,		0.5f, 0.5f,			1.0f, 0.0f, 0.0f,
		5.0f, 0.5f, -3.0f,		0.5f, 0.6875f,		1.0f, 0.0f, 0.0f,
		5.0f, 0.5f, 3.0f,		0.4375f, 0.6875f,	1.0f, 0.0f, 0.0f,

		//IZQUIERDA
		-5.0f, -0.5f, 3.0f,		0.4375f, 0.5f,		-1.0f, 0.0f, 0.0f,
		-5.0f, -0.5f, -3.0f,	0.5f, 0.5f,			-1.0f, 0.0f, 0.0f,
		-5.0f, 0.5f, -3.0f,		0.5f, 0.6875f,		-1.0f, 0.0f, 0.0f,
		-5.0f, 0.5f, 3.0f,		0.4375f, 0.6875f,	-1.0f, 0.0f, 0.0f,

		//ATRAS
		-5.0f, -0.5f, -3.0f,	0.5f, 0.5f,			0.0f, 0.0f, -1.0f,
		5.0f, -0.5f, -3.0f,		0.625f, 0.5f,		0.0f, 0.0f, -1.0f,
		5.0f, 0.5f, -3.0f,		0.625f, 0.6875f,	0.0f, 0.0f, -1.0f,
		-5.0f, 0.5f, -3.0f,		0.5f, 0.6875f,		0.0f, 0.0f, -1.0f,

		//ARRIBA
		5.0f, 0.5f, 3.0f,		0.4375f, 0.5f,		0.0f, 1.0f, 0.0f,
		5.0f, 0.5f, -3.0f,		0.5f, 0.5f,			0.0f, 1.0f, 0.0f,
		-5.0f, 0.5f, -3.0f,		0.5f, 0.6875f,		0.0f, 1.0f, 0.0f,
		-5.0f, 0.5f, 3.0f,		0.4375f, 0.6875f,	0.0f, 1.0f, 0.0f,

		//ABAJO
		5.0f, -0.5f, -3.0f,		0.4375f, 0.5f,		0.0f, -1.0f, 0.0f,
		-5.0f, -0.5f, -3.0f,	0.5f, 0.5f,			0.0f, -1.0f, 0.0f,
		-5.0f, -0.5f, 3.0f,		0.5f, 0.6875f,		0.0f, -1.0f, 0.0f,
		5.0f, -0.5f, 3.0f,		0.4375f, 0.6875f,	0.0f, -1.0f, 0.0f,


	};

	Mesh* escenario = new Mesh();
	escenario->CreateMesh(vertices_escenario, indices_escenario, sizeof(vertices_escenario) / 4, sizeof(indices_escenario) / 4);
	meshList.push_back(escenario);

}

Toroide toro = Toroide(3.0f, 1.0f, 0.5f);
//float raInt, float raExt, int reExt, int reInt
Toroide_f toroide = Toroide_f(1.0f,3.0f, 20,20);

using namespace irrklang;

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearCuatro();
	CrearLorax();
	CrearEscenarioShow();
	CreateShaders();

	toro.init();
	toro.load();

	

	toroide.Crear_Toroide_f();
	toroide.load();

	//camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);
	cameraP = Camera(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 0.1f, 0.5f);
	cameraA = Camera(glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.1f, 0.5f);

	ISoundEngine* engine = createIrrKlangDevice();
	if (!engine)
		return 0; // Error al inicial el motor de sonidos
	//Sonido Ambiental
	engine->play2D("Media/Bosque.wav", true);
	//Sonido Espacial
	ISound* music = engine->play3D("Media/Fogata.wav", vec3df(0, 0, 0), true, false, true);
	music->setMinDistance(3.0f);

	inidice_spotlights = 0;
	conteo_spotlights = 0;

	

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

	salvavidasTexture = Texture("Textures/salvavidas.png");
	salvavidasTexture.LoadTexture();





	ArmaKND_M = Model();
	ArmaKND_M.LoadModel("Models/base_arma.obj");

	LanzaderaKND_M = Model();
	LanzaderaKND_M.LoadModel("Models/lanzadera_armaA.obj");

	Pelota_M = Model();
	Pelota_M.LoadModel("Models/Pelota.obj");

	CasaLorax_M = Model();
	//CasaLorax_M.LoadModel("Models/casa_Lorax.obj");

	Fuente_M = Model();
	Fuente_M.LoadModel("Models/Fuente.obj");

	//////PROYECTO FINAL

	arbol_T = Model();
	arbol_T.LoadModel("Models/tronco.obj");

	arbol_H = Model();
	arbol_H.LoadModel("Models/hojas.obj");

	Hojas_Piso_M = Model();
	Hojas_Piso_M.LoadModel("Models/hojas_tiradas.obj");

	Hojas_q_caen = Model();
	Hojas_q_caen.LoadModel("Models/hojas_caen.obj");

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

	lampara = Model();
	lampara.LoadModel("Models/street_lamp.obj");

	base_show = Model();
	base_show.LoadModel("Models/base_luces.obj");

	lamp_show = Model();
	lamp_show.LoadModel("Models/lampara_luces.obj");

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

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

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
	//model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));

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

	//model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
	arrPointLights[7] = PointLight(1.0f, 0.2156f, 0.2156f,
		1.0f, 1.0f,
		0.0f, -3.0f, 0.0f, //posición
		0.3f, 0.2f, 0.1f); //coeficientes de la ecuación de 2do grado


	//linterna
	//spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
	//	0.0f, 2.0f,
	//	0.0f, 0.0f, 0.0f,
	//	0.0f, -1.0f, 0.0f,
	//	1.0f, 0.0f, 0.0f,
	//	5.0f);
	//spotLightCount++;

	//
	arrSpotLigths[0] = SpotLight(0.8627f, 1.0f, 0.0f,
		0.7f, 2.0f,
		26.0f, 10.0f, 4.2f,//posición
		//5.0f, 15.0f, -18.0f,
		0.0f, -5.0f, -1.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);


	//SHOW DE LUCES
	//model = glm::translate(model, glm::vec3(5.0f, 6. 8f, -18.0f));
	arrSpotLigths[1] = SpotLight(0.0f, 0.0f, 1.0f,//azul
		0.7f, 2.0f,
		//26.0f, 0.0f, 4.2f,//posición
		5.0f, 6.8f, -18.0f,
		//1.0f, -1.7320f, 0.0f,
		0.0f, -1.0f, 0.0f,
		//0.864218f,-5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		10.0f);


	//		model = glm::translate(model, glm::vec3(5.0f, 6.8f, -16.0f));
	arrSpotLigths[2] = SpotLight(1.0f, 0.0f, 1.0f, //magenta
		0.7f, 2.0f,
		5.0f, 6.8f, -16.0f,//posición
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		10.0f);
	//model = glm::translate(model, glm::vec3(5.0f, 6.8f, -14.0f));
	arrSpotLigths[3] = SpotLight(0.0f, 1.0f, 0.0f,//verde
		0.7f, 2.0f,
		5.0f, 6.8f, -14.0f,//posición
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		10.0f);

	// model = glm::translate(model, glm::vec3(5.0f, 6.8f, -20.0f));
	arrSpotLigths[4] = SpotLight(0.0f, 1.0f, 1.0f, //cyan
		0.7f, 2.0f,
		5.0f, 6.8f, -20.0f,//posición
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		10.0f);

	//model = glm::translate(model, glm::vec3(5.0f, 6.8f, -22.0f));
	arrSpotLigths[5] = SpotLight(1.0f, 1.0f, 0.0f,//amarillo
		0.7f, 2.0f,
		5.0f, 6.8f, -22.0f,//posición
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		10.0f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	banderaLamparaPrendida = false;
	banderaShowLuces = false;

	//ANIMACION 1 CORTADORA
	//Cuando se apriete la tecla 'P' se hace el movimiento de las hachas y los árboles se sacuden 
	giraHacha = 10.0;
	giraHachaOffset = 0.005;
	giroArbol = 0.0;
	giroHojas = 0.0;
	giroHojasOffset = 0.0005;
	rotahacha = 0.0;
	retrocede = true;
	sacudehojas = false;
	sacude_der = 0.0;
	contador_sacude = 0;

	//ANIMACION AIRE
	bandera_aire = false;
	bandera_sacude = true;
	bandera_sacude_lado = true; 
	sacude_tronco = 0.0;
	sacude_hojas = 0.0;
	tira_hojas = 0.0;
	sacude_troncoOffset = 0.05;
	sacude_hojasOffset = 0.05;
	tira_hojasOffset = 0.005;
	conta_aire = 0;

	//ANIMACION AVATAR
	giroAvanza = 0.0;
	giroAvanzaOffset = 0.005;
	giroLado = 0.0;
	giroLadoOffset = 0.0;
	banderaAvanza = true;
	banderaLado = true;

	//SHOW DE LUCES
	bandera_show_luces = false;
	//bandera_show_luces = true;
	bandera_giro = true;
	bandera_prende_apaga = true;

	contador_show = 0;
	giro_luz = 0.0;

	giro_lamp_1 = 0.0;
	giro_lamp_2 = 0.0;
	giro_lamp_3 = 0.0;
	giro_lamp_4 = 0.0;
	giro_lamp_5 = 0.0;

	giroLuzOffset = 0.05;
	pos_lampara1 = glm::vec3(5.0f, 6.8f, -18.0f);
	pos_lampara2 = glm::vec3(5.0f, 6.8f, -16.0f);
	pos_lampara3 = glm::vec3(5.0f, 6.8f, -14.0f);
	pos_lampara4 = glm::vec3(5.0f, 6.8f, -20.0f);
	pos_lampara5 = glm::vec3(5.0f, 6.8f, -22.0f);

	dir_lampara1 = glm::vec3(0.0f, -1.0f, 0.0f);
	dir_lampara2 = glm::vec3(0.0f, -1.0f, 0.0f);
	dir_lampara3 = glm::vec3(0.0f, -1.0f, 0.0f);
	dir_lampara4 = glm::vec3(0.0f, -1.0f, 0.0f);
	dir_lampara5 = glm::vec3(0.0f, -1.0f, 0.0f);

	valX = 0.0f;
	valY = 0.0f;

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		pos_per = cameraP.getCameraPosition();

		engine->setListenerPosition(vec3df(pos_per.x, pos_per.y, pos_per.z), vec3df(0, 1, 0));
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		////ANIMACION AIRE
		//bandera_aire = false;
		//bandera_sacude = true;
		//sacude_tronco = 0.0;
		//sacude_hojas = 0.0;
		//tira_hojas = 0.0;
		//sacude_troncoOffset = 0.0005;
		//sacude_hojasOffset = 0.0005;
		////tira_hojasOffset = 0.0005;
		//giro_luz += 1.2 * deltaTime;
		//if (giro_luz < 40.0) {
		//	giro_luz -= giroLuzOffset * deltaTime;


		if (bandera_aire) {
			if (bandera_sacude) {
				if (sacude_tronco < 10) {
					sacude_tronco += 1.2 * deltaTime;
					sacude_tronco -= sacude_troncoOffset * deltaTime;
				}
				else {
					if (conta_aire < 10) {
						if (bandera_sacude_lado) {
							if (sacude_hojas < 5) {
								sacude_hojas += 1.8 * deltaTime;
								sacude_hojas -= sacude_hojasOffset * deltaTime;
							}
							else
							{
								bandera_sacude_lado = false;
							}
						}
						else
						{
							if (sacude_hojas > -5) {
								sacude_hojas -= 1.8 * deltaTime;
								sacude_hojas -= sacude_hojasOffset * deltaTime;
							}
							else
							{
								conta_aire++;
								bandera_sacude_lado = true;
							}
							
						}
					}
					else
					{
						bandera_sacude = false;
					}
					tira_hojas += 0.1 * deltaTime;
					tira_hojas -= tira_hojasOffset * deltaTime;
				}


			}
			else
			{
				if (sacude_tronco > 0) {
					sacude_tronco -= 1.2 * deltaTime;
					sacude_tronco -= sacude_troncoOffset * deltaTime;
				}
				else
				{
					sacude_tronco = 0;
					sacude_hojas = 0;
					conta_aire = 0;
					bandera_sacude = true;
					bandera_aire = false;
					tira_hojas = 0;
				}
			}
		}

		//ANIMACION CORTADORA
		if (mainWindow.gettala() == 1) {
			if (sacudehojas) {
				if (contador_sacude < 2) {
					if (sacude_der) {
						giroHojas += 0.8 * deltaTime;
						giroArbol += 0.4 * deltaTime;
						if (giroHojas < 5) {
							giroHojas -= giroHojasOffset * deltaTime;
							giroArbol -= giroHojasOffset * deltaTime;
						}
						else
						{
							sacude_der = false;
						}
					}
					else
					{
						giroHojas -= 0.8 * deltaTime;
						giroArbol -= 0.4 * deltaTime;
						if (giroHojas > -5) {
							giroHojas -= giroHojasOffset * deltaTime;
							giroArbol -= giroHojasOffset * deltaTime;
						}
						else
						{
							sacude_der = true;
							contador_sacude++;
						}

					}
				}
				else
				{
					giroHojas += 0.8 * deltaTime;
					giroArbol += 0.4 * deltaTime;
					if (giroHojas < 0) {
						giroHojas -= giroHojasOffset * deltaTime;
						giroArbol -= giroHojasOffset * deltaTime;
					}
					else
					{
						sacudehojas = false;
						giroHojas = 0.0;
						rotahacha = 0.0;
						retrocede = true;
						sacude_der = 0.0;
						contador_sacude = 0;
					}
				}
			}
			else
			{
				if (retrocede) {
					giraHacha += 0.2 * deltaTime;
					if (giraHacha < 25) {
						giraHacha -= giraHachaOffset * deltaTime;
					}
					else {
						retrocede = false;
					}
				}
				else {
					giraHacha -= 0.2 * deltaTime;
					if (giraHacha > 1) {
						giraHacha -= giraHachaOffset * deltaTime;
					}
					else {
						sacudehojas = true;
					}
				}
			}

		}

		if (mainWindow.getCamina() == 1 && mainWindow.gettipoCamara() == 0) {
			if (banderaAvanza) {
				giroAvanza += 0.8 * deltaTime;
				if (giroAvanza < 10.0) {
					giroAvanza -= giroAvanzaOffset * deltaTime;
				}
				else
				{
					banderaAvanza = false;
				}
			}
			else
			{
				giroAvanza -= 0.8 * deltaTime;
				if (giroAvanza > -10.0) {
					giroAvanza -= giroAvanzaOffset * deltaTime;
				}
				else
				{
					banderaAvanza = true;
				}
			}

		}

		if (mainWindow.getDesplaza() == 1 && mainWindow.gettipoCamara() == 0) {
			if (banderaLado) {
				giroLado += 0.8 * deltaTime;
				if (giroLado < 15.0) {
					giroLado -= giroLadoOffset * deltaTime;
				}
				else
				{
					banderaLado = false;
				}
			}
			else
			{
				giroLado -= 0.8 * deltaTime;
				if (giroLado > 0.0) {
					giroLado -= giroLadoOffset * deltaTime;
				}
				else
				{
					banderaLado = true;
				}
			}

		}

		//printf("LUCES SPOTLIGHT: %i \n", spotLightCount);
		mainWindow.gettipoCamara() == 0;

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

		if (contadorSkybox < (20000)) { //20000
			if (banderaSkybox) {
				skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
				mainLight.SetIntensity(1.0f);
				bandera_show_luces = false;
				pointLightCount = 0;
			}
			else {
				//Es de noche
				bandera_show_luces = true;
				skyboxNoche.DrawSkybox(camera.calculateViewMatrix(), projection);
				mainLight.SetIntensity(0.3f);
				pointLights[0] = arrPointLights[7];
				if (pos_per.z < -10) {
					pointLights[1] = arrPointLights[0];
					pointLights[2] = arrPointLights[1];
					pointLightCount = 3;
				}
				else if (pos_per.x > 10) {
					pointLights[1] = arrPointLights[6];
					pointLights[2] = arrPointLights[5];
					pointLightCount = 3;
				}
				else if (pos_per.z > 10) {
					pointLights[1] = arrPointLights[3];
					pointLights[2] = arrPointLights[4];
					pointLightCount = 3;
				}
				else {
					pointLights[1] = arrPointLights[2];
					pointLightCount = 2;
				}
			}
			contadorSkybox++;
		}
		else {
			contadorSkybox = 0;
			banderaSkybox = !banderaSkybox;
		}
		printf(" \n %d", contadorSkybox);
		//HABILITACION DE AIRE
		if (contadorSkybox %2000 == 0) {
			bandera_aire = true;
		}

		//SHOW DE LUCES /DEL INDICE 1 AL 5
		if (bandera_show_luces && banderaShowLuces) {
			//printf("EL VECTOR 0 TIENE ESTA EN %f, %f, %f  | | apunta a %f, %f, %f \n",spotLights[0])
			contador_show++;
			if (contador_show < 400)
			{
				if (contador_show % 6 == 0) {
					bandera_prende_apaga = !bandera_prende_apaga;
					inidice_spotlights = 0;
				}
				if (bandera_prende_apaga) {
					spotLights[0] = arrSpotLigths[1];
					spotLights[1] = arrSpotLigths[3];
					spotLights[2] = arrSpotLigths[5];
					spotLightCount = 3;
				}
				else {
					spotLights[0] = arrSpotLigths[2];
					spotLights[1] = arrSpotLigths[4];
					spotLightCount = 2;
				}


			}
			else if (contador_show == 400) {
				inidice_spotlights = 0;
			}
			else if (contador_show < 600) {
				spotLights[0] = arrSpotLigths[3];
				inidice_spotlights++;
				spotLights[1] = arrSpotLigths[5];
				spotLightCount = 2;
				if (bandera_giro) { //esta viendo con unángulo de 0° y se debe girar hasta llegar a los 20
					giro_luz += 1.2 * deltaTime;
					if (giro_luz < 40.0) {
						giro_luz -= giroLuzOffset * deltaTime;

					}
					else
					{
						bandera_giro = false;
					}
				}
				else
				{
					giro_luz -= 1.2 * deltaTime;
					if (giro_luz > 0)
					{
						giro_luz -= giroLuzOffset * deltaTime;
					}
					else
					{
						bandera_giro = true;
					}
				}
				giro_lamp_3 = giro_luz;
				giro_lamp_5 = giro_luz;

				valX = sin(giro_luz * toRadians);
				valY = cos(giro_luz * toRadians);

				if (valY > 0) {
					valY = valY * -1;
				}
				//valX += 0.01;

				dir_lampara3.x = valX;
				dir_lampara3.y = valY;

				dir_lampara5.x = valX;
				dir_lampara5.y = valY;

				//printf("El anguo al que se encuentra la lampar es: %f y la X estaría en: %f\n", giro_luz, dir_lampara1.x);
				//printf("\nEn z: %f", dir_lampara1.z);
				spotLights[0].SetFlash(pos_lampara3, dir_lampara3);
				spotLights[1].SetFlash(pos_lampara5, dir_lampara5);
				//spotLights[0].SetPos(dir_lampara1);

			}
			else if (contador_show == 600) {
				dir_lampara3 = glm::vec3(0.0f, -1.0f, 0.0f);
				dir_lampara5 = glm::vec3(0.0f, -1.0f, 0.0f);
				giro_luz = 0.0f;
				giro_lamp_3 = 0.0f;
				giro_lamp_5 = 0.0f;
				inidice_spotlights = 0;

			}
			else if (contador_show < 800) {
				spotLights[0] = arrSpotLigths[2];
				inidice_spotlights++;
				spotLights[1] = arrSpotLigths[4];
				inidice_spotlights++;
				spotLightCount = 2;
				if (bandera_giro) { //esta viendo con unángulo de 0° y se debe girar hasta llegar a los 20
					giro_luz += 1.2 * deltaTime;
					if (giro_luz < 40.0) {
						giro_luz -= giroLuzOffset * deltaTime;

					}
					else
					{
						bandera_giro = false;
					}
				}
				else
				{
					giro_luz -= 1.2 * deltaTime;
					if (giro_luz > 0)
					{
						giro_luz -= giroLuzOffset * deltaTime;
					}
					else
					{
						bandera_giro = true;
					}
				}
				giro_lamp_2 = giro_luz;
				giro_lamp_4 = giro_luz;

				valX = sin(giro_luz * toRadians);
				valY = cos(giro_luz * toRadians);

				if (valY > 0) {
					valY = valY * -1;
				}
				//valX += 0.01;

				dir_lampara2.x = valX;
				dir_lampara2.y = valY;

				dir_lampara4.x = valX;
				dir_lampara4.y = valY;

				//printf("El anguo al que se encuentra la lampar es: %f y la X estaría en: %f\n", giro_luz, dir_lampara1.x);
				//printf("\nEn z: %f", dir_lampara1.z);
				spotLights[0].SetFlash(pos_lampara2, dir_lampara2);
				spotLights[1].SetFlash(pos_lampara4, dir_lampara4);
				//spotLights[0].SetPos(dir_lampara1);

			}
			else if (contador_show == 800) {
				dir_lampara2 = glm::vec3(0.0f, -1.0f, 0.0f);
				dir_lampara4 = glm::vec3(0.0f, -1.0f, 0.0f);
				giro_luz = 0.0f;
				giro_lamp_2 = 0.0f;
				giro_lamp_4 = 0.0f;
				inidice_spotlights = 0;
			}
			else {
				dir_lampara2 = glm::vec3(0.0f, -1.0f, 0.0f);
				dir_lampara4 = glm::vec3(0.0f, -1.0f, 0.0f);
				dir_lampara1 = glm::vec3(0.0f, -1.0f, 0.0f);
				dir_lampara3 = glm::vec3(0.0f, -1.0f, 0.0f);
				dir_lampara5 = glm::vec3(0.0f, -1.0f, 0.0f);
				giro_luz = 0.0f;
				giro_lamp_1 = 0.0f;
				giro_lamp_2 = 0.0f;
				giro_lamp_3 = 0.0f;
				giro_lamp_4 = 0.0f;
				giro_lamp_5 = 0.0f;
				giro_luz = 0.0f;
				contador_show = 0;
			}
			//printf("\nLa luz 0 esta en %f, %f, %f \n Y apunta a %f, %f, %f", spotLights[0].getPos().x, spotLights[0].getPos().y, spotLights[0].getPos().z, spotLights[0].getDir().x, spotLights[0].getDir().y, spotLights[0].getDir().z);
		}
		else {
			//spotLightCount = 0;

		}
		//printf(" \n %d", contador_show);

		if (mainWindow.getLuzLampara() == 1 && !banderaLamparaPrendida && !banderaShowLuces) {
			spotLights[0] = arrSpotLigths[0];
			spotLightCount = 1;
			banderaLamparaPrendida = true;
		}

		if (banderaLamparaPrendida && mainWindow.getLuzLampara() == 0) {
			spotLightCount = 0;
			banderaLamparaPrendida = false;
		}

		if (mainWindow.getShowLuces() == 1 && !banderaLamparaPrendida && !banderaShowLuces) {
			banderaShowLuces = true;
		}
		if (banderaShowLuces && mainWindow.getShowLuces() == 0) {
			banderaShowLuces = false;
		}

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
		glm::mat4 avatar_aux(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 simios_aux(1.0);
		glm::mat4 cortadora_aux(1.0);
		glm::mat4 cortadora_hacha_aux(1.0);
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

		/*model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, 5.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArmaKND_M.RenderModel();*/


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
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		cortadora_hacha_aux = model;
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
		model = glm::translate(model, glm::vec3(6.8f, 0.0f, 0.0f));
		model = glm::rotate(model, giraHacha * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));


		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 6.0f));
		cortadora_hacha_aux = model;
		//model = glm::translate(model, glm::vec3(6.8f, 0.0f, 6.0f));
		//model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hacha_M.RenderModel();

		//ÁRBOL ROJO |1
		model = cortadora_aux;
		//model = glm::translate(model, glm::vec3(-3.0f, -2.5f, 4.0f));
		model = glm::translate(model, glm::vec3(4.8f, -2.5f, 10.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, giroArbol * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, giroHojas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//////////////////////////////////////////////////////////////////////////////

		model = cortadora_aux;
		model = glm::translate(model, glm::vec3(9.4f, 0.0f, 0.0f));
		model = glm::rotate(model, -giraHacha * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -6.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, giraHacha* toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hacha_M.RenderModel();

		//ÁRBOL ROJO |2
		model = cortadora_aux;
		model = glm::translate(model, glm::vec3(7.4f, -2.5f, -10.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, -giroHojas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, -giroArbol * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//////////////////////////////////////////////////////////////////////////////

		model = cortadora_aux;
		model = glm::translate(model, glm::vec3(13.3f, 0.0f, 0.0f));
		model = glm::rotate(model, giraHacha * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 6.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hacha_M.RenderModel();

		////ÁRBOL ROSA |3
		model = cortadora_aux;
		model = glm::translate(model, glm::vec3(11.3f, -2.5f, 10.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, giroArbol * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, giroHojas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		/////////////////////////////////////////////////////////////////////////////

		model = cortadora_aux;
		model = glm::translate(model, glm::vec3(17.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -giraHacha * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -6.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hacha_M.RenderModel();

		////ÁRBOL ROSA |4
		model = cortadora_aux;
		model = glm::translate(model, glm::vec3(15.0f, -2.5f, -10.0f));
		model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, -giroArbol * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();

		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, -giroHojas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 10.0));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		cuatroTexture.UseTexture();
		meshList[3]->RenderMesh();

		//PErsonaje LORAX jeraquizado//////////////////////////////////////
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(pos_per.x, pos_per.y, pos_per.z - 3.5));
		//model = glm::translate(model, glm::vec3(5,5,5));
		avatar_aux = model;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		loraxTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		model = avatar_aux;
		model = glm::translate(model, glm::vec3(0, 0.5, 0));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		model = glm::translate(model, glm::vec3(0, 0.5, 0));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		loraxTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = avatar_aux;
		model = glm::translate(model, glm::vec3(0.2, -0.6, 0));
		model = glm::rotate(model, giroAvanza * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, giroLado * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(model, glm::vec3(0.0, -0.6, 0));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		loraxTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		model = avatar_aux;
		model = glm::translate(model, glm::vec3(-0.2, -0.6, 0));
		model = glm::rotate(model, giroAvanza * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, giroLado * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));

		model = glm::translate(model, glm::vec3(0.0, -0.6, 0));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		loraxTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		model = avatar_aux;
		model = glm::translate(model, glm::vec3(0.3, 0.5, 0));
		model = glm::rotate(model, giroAvanza * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));

		model = glm::translate(model, glm::vec3(0.3, -0.5, 0));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		loraxTexture.UseTexture();
		meshList[8]->RenderMesh();

		model = avatar_aux;
		model = glm::translate(model, glm::vec3(-0.3, 0.5, 0));
		model = glm::rotate(model, giroAvanza * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));

		model = glm::translate(model, glm::vec3(-0.3, -0.5, 0));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		loraxTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[8]->RenderMesh();


		//ESCENARIO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(9.5f, -0.5f, -18.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 2.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[10]->RenderMesh();


		// ROCA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(27.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		piedra.RenderModel();

		////ARBOLES

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -30.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -30.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -28.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -26.0f));
		model = glm::scale(model, glm::vec3(0.88f, 0.88f, 0.88f));
		model = glm::rotate(model, 60 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -26.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -24.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -22.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::rotate(model, 60 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -20.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -18.0f));
		model = glm::scale(model, glm::vec3(0.96f, 0.96f, 0.96f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -16.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, 75 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -16.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -14.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -12.0f));
		model = glm::scale(model, glm::vec3(0.65f, 0.65f, 0.65f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -12.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -10.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, 20 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -8.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, 35 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-27.0f, -1.0f, -9.0f));
		model = glm::scale(model, glm::vec3(0.82f, 0.82f, 0.82f));
		model = glm::rotate(model, 27 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-26.0f, -1.0f, -12.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-28.0f, -1.0f, -15.0f));
		model = glm::scale(model, glm::vec3(0.90f, 0.90f, 0.90f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-27.0f, -1.0f, -18.0f));
		model = glm::scale(model, glm::vec3(0.80f, 0.80f, 0.80f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-26.0f, -1.0f, -21.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, 360 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-26.0f, -1.0f, -21.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-28.0f, -1.0f, -24.0f));
		model = glm::scale(model, glm::vec3(0.70f, 0.70f, 0.70f));
		model = glm::rotate(model, 80 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-27.0f, -1.0f, -27.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, 160 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-24.0f, -1.0f, -30.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-24.0f, -1.0f, -30.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-24.0f, -1.0f, -27.0f));
		model = glm::scale(model, glm::vec3(0.55f, 0.55f, 0.55f));
		model = glm::rotate(model, 100 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-25.0f, -1.0f, -24.0f));
		model = glm::scale(model, glm::vec3(0.70f, 0.70f, 0.70f));
		model = glm::rotate(model, 100 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-24.0f, -1.0f, -20.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, 100 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();


		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-23.0f, -1.0f, -16.0f));
		model = glm::scale(model, glm::vec3(0.46f, 0.46f, 0.46f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-24.0f, -1.0f, -12.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, 85 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-25.0f, -1.0f, -8.0f));
		model = glm::scale(model, glm::vec3(0.96f, 0.96f, 0.96f));
		model = glm::rotate(model, 185 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-21.0f, -1.0f, -9.0f));
		model = glm::scale(model, glm::vec3(0.86f, 0.86f, 0.86f));
		model = glm::rotate(model, 185 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-21.0f, -1.0f, -9.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();
		

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-22.0f, -1.0f, -12.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, -1.0f, -15.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, -1.0f, -15.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-21.0f, -1.0f, -18.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		model = glm::rotate(model, 85 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-21.0f, -1.0f, -21.0f));
		model = glm::scale(model, glm::vec3(0.92f, 0.92f, 0.92f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-22.0f, -1.0f, -24.0f));
		model = glm::scale(model, glm::vec3(0.49f, 0.49f, 0.49f));
		model = glm::rotate(model, 5 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-22.0f, -1.0f, -27.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-22.0f, -1.0f, -27.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, -1.0f, -30.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::rotate(model, 110 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-18.0f, -1.0f, -10.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-19.0f, -1.0f, -13.0f));
		model = glm::scale(model, glm::vec3(0.97f, 0.97f, 0.97f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-17.0f, -1.0f, -16.0f));
		model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
		model = glm::rotate(model, 190 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-19.0f, -1.0f, -19.0f));
		model = glm::scale(model, glm::vec3(0.88f, 0.88f, 0.88f));
		model = glm::rotate(model, 35 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-18.0f, -1.0f, -22.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-17.0f, -1.0f, -25.0f));
		model = glm::scale(model, glm::vec3(0.72f, 0.72f, 0.72f));
		model = glm::rotate(model, 145 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();



		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-18.0f, -1.0f, -28.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-19.0f, -1.0f, -31.0f));
		model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-16.0f, -1.0f, -7.0f));
		model = glm::scale(model, glm::vec3(0.76f, 0.76f, 0.76f));
		model = glm::rotate(model, 19 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();


		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-17.0f, -1.0f, -13.0f));
		model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
		model = glm::rotate(model, 190 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-17.0f, -1.0f, -14.0f));
		model = glm::scale(model, glm::vec3(0.78f, 0.78f, 0.78f));
		model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-17.0f, -1.0f, -14.0f));
		model = glm::scale(model, glm::vec3(0.78f, 0.78f, 0.78f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-16.0f, -1.0f, -17.0f));
		model = glm::scale(model, glm::vec3(0.55f, 0.55f, 0.55f));
		model = glm::rotate(model, 110 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.0f, -20.0f));
		model = glm::scale(model, glm::vec3(0.98f, 0.98f, 0.98f));
		model = glm::rotate(model, 330 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-16.0f, -1.0f, -23.0f));
		model = glm::scale(model, glm::vec3(0.73f, 0.73f, 0.73f));
		model = glm::rotate(model, 195 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-16.0f, -1.0f, -23.0f));
		model = glm::scale(model, glm::vec3(0.73f, 0.73f, 0.73f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();


		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-17.0f, -1.0f, -26.0f));
		model = glm::scale(model, glm::vec3(0.57f, 0.57f, 0.57f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-16.0f, -1.0f, -29.0f));
		model = glm::scale(model, glm::vec3(0.72f, 0.72f, 0.72f));
		model = glm::rotate(model, 25 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.0f, -1.0f, -9.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::rotate(model, 33 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.0f, -1.0f, -12.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, 119 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, -1.0f, -15.0f));
		model = glm::scale(model, glm::vec3(0.82f, 0.82f, 0.82f));
		model = glm::rotate(model, 110 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-11.0f, -1.0f, -18.0f));
		model = glm::scale(model, glm::vec3(0.62f, 0.62f, 0.62f));
		model = glm::rotate(model, 225 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.0f, -1.0f, -21.0f));
		model = glm::scale(model, glm::vec3(0.73f, 0.73f, 0.73f));
		model = glm::rotate(model, 155 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, -1.0f, -24.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, 110 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();



		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-11.0f, -1.0f, -27.0f));
		model = glm::scale(model, glm::vec3(0.77f, 0.77f, 0.77f));
		model = glm::rotate(model, 185 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, -1.0f, -30.0f));
		model = glm::scale(model, glm::vec3(0.97f, 0.97f, 0.97f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

				//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.0f, -1.0f, -9.0f));
		model = glm::scale(model, glm::vec3(0.97f, 0.97f, 0.97f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.0f, -1.0f, -12.0f));
		model = glm::scale(model, glm::vec3(0.91f, 0.91f, 0.91f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 83 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));;
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -1.0f, -15.0f));
		model = glm::scale(model, glm::vec3(0.72f, 0.72f, 0.72f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 110 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -1.0f, -15.0f));
		model = glm::scale(model, glm::vec3(0.72f, 0.72f, 0.72f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-9.0f, -1.0f, -18.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-9.0f, -1.0f, -21.0f));
		model = glm::scale(model, glm::vec3(0.68f, 0.68f, 0.68f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 23 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -1.0f, -25.0f));
		model = glm::scale(model, glm::vec3(0.87f, 0.87f, 0.87f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.7764f, 0.1254f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -1.0f, -25.0f));
		model = glm::scale(model, glm::vec3(0.87f, 0.87f, 0.87f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -1.0f, -26.0f));
		model = glm::scale(model, glm::vec3(0.48f, 0.48f, 0.48f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 33 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -1.0f, -26.0f));
		model = glm::scale(model, glm::vec3(0.48f, 0.48f, 0.48f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-9.0f, -1.0f, -31.0f));
		model = glm::scale(model, glm::vec3(0.94f, 0.94f, 0.94f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 140 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(0.9137f, 0.4196f, 0.9803f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-9.0f, -1.0f, -31.0f));
		model = glm::scale(model, glm::vec3(0.94f, 0.94f, 0.94f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

//		//z POSITIVAS//////////////////////////////////////////////////////// No se mueven////////

				//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, 30.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f)); 
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, 28.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, 28.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, 26.0f));
		model = glm::scale(model, glm::vec3(0.88f, 0.88f, 0.88f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, 24.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, 22.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, 20.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, 18.0f));
		model = glm::scale(model, glm::vec3(0.96f, 0.96f, 0.96f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, 16.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 75 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, 14.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, 12.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, 12.0f));
		model = glm::scale(model, glm::vec3(0.65f, 0.65f, 0.65f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();


		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, 10.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 20 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, 8.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 35 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, 8.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-27.0f, -1.0f, 9.0f));
		model = glm::scale(model, glm::vec3(0.82f, 0.82f, 0.82f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 27 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-26.0f, -1.0f, 12.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-28.0f, -1.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.90f, 0.90f, 0.90f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-28.0f, -1.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.90f, 0.90f, 0.90f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-27.0f, -1.0f, 18.0f));
		model = glm::scale(model, glm::vec3(0.80f, 0.80f, 0.80f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-26.0f, -1.0f, 21.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 360 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-28.0f, -1.0f, 24.0f));
		model = glm::scale(model, glm::vec3(0.70f, 0.70f, 0.70f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 80 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-27.0f, -1.0f, 27.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 160 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-24.0f, -1.0f, 30.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-24.0f, -1.0f, 27.0f));
		model = glm::scale(model, glm::vec3(0.55f, 0.55f, 0.55f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 100 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-25.0f, -1.0f, 24.0f));
		model = glm::scale(model, glm::vec3(0.70f, 0.70f, 0.70f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 100 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-24.0f, -1.0f, 20.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 100 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-23.0f, -1.0f, 16.0f));
		model = glm::scale(model, glm::vec3(0.46f, 0.46f, 0.46f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();


		/////////////////////	 prueba //////
		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-24.0f, -1.0f, 12.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f)); 
		model = glm::rotate(model, 85 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		arbol_aux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		color = glm::vec3(1.0f, 0.2274f, 0.0001f);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-24.0f, -1.0f, 12.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, 85 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 2.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-25.0f, -1.0f, 8.0f));
		model = glm::scale(model, glm::vec3(0.96f, 0.96f, 0.96f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 185 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-21.0f, -1.0f, 9.0f));
		model = glm::scale(model, glm::vec3(0.86f, 0.86f, 0.86f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 185 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-22.0f, -1.0f, 12.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-22.0f, -1.0f, 12.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, -1.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-21.0f, -1.0f, 18.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 85 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-21.0f, -1.0f, 18.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-21.0f, -1.0f, 21.0f));
		model = glm::scale(model, glm::vec3(0.92f, 0.92f, 0.92f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-22.0f, -1.0f, 24.0f));
		model = glm::scale(model, glm::vec3(0.49f, 0.49f, 0.49f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 5 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-22.0f, -1.0f, 27.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, -1.0f, 30.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 110 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-18.0f, -1.0f, 10.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-18.0f, -1.0f, 10.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-19.0f, -1.0f, 13.0f));
		model = glm::scale(model, glm::vec3(0.97f, 0.97f, 0.97f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-17.0f, -1.0f, 16.0f));
		model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 190 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-19.0f, -1.0f, 19.0f));
		model = glm::scale(model, glm::vec3(0.88f, 0.88f, 0.88f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 35 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-18.0f, -1.0f, 22.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-18.0f, -1.0f, 22.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-17.0f, -1.0f, 25.0f));
		model = glm::scale(model, glm::vec3(0.72f, 0.72f, 0.72f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 145 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();


		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-18.0f, -1.0f, 28.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-19.0f, -1.0f, 31.0f));
		model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		/////////////

////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-16.0f, -1.0f, 7.0f));
		model = glm::scale(model, glm::vec3(0.76f, 0.76f, 0.76f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 19 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-16.0f, -1.0f, 7.0f));
		model = glm::scale(model, glm::vec3(0.76f, 0.76f, 0.76f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();


		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-17.0f, -1.0f, 13.0f));
		model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 190 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-17.0f, -1.0f, 14.0f));
		model = glm::scale(model, glm::vec3(0.78f, 0.78f, 0.78f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-16.0f, -1.0f, 17.0f));
		model = glm::scale(model, glm::vec3(0.55f, 0.55f, 0.55f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 110 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -1.0f, 20.0f));
		model = glm::scale(model, glm::vec3(0.98f, 0.98f, 0.98f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 330 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-16.0f, -1.0f, 23.0f));
		model = glm::scale(model, glm::vec3(0.73f, 0.73f, 0.73f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 195 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-16.0f, -1.0f, 23.0f));
		model = glm::scale(model, glm::vec3(0.73f, 0.73f, 0.73f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-17.0f, -1.0f, 26.0f));
		model = glm::scale(model, glm::vec3(0.57f, 0.57f, 0.57f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-16.0f, -1.0f, 29.0f));
		model = glm::scale(model, glm::vec3(0.72f, 0.72f, 0.72f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 25 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//////////////////////////////
				/////////////

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.0f, -1.0f, 9.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 33 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.0f, -1.0f, 12.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 119 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();


		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, -1.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.82f, 0.82f, 0.82f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 110 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, -1.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.82f, 0.82f, 0.82f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-11.0f, -1.0f, 18.0f));
		model = glm::scale(model, glm::vec3(0.62f, 0.62f, 0.62f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 225 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.0f, -1.0f, 21.0f));
		model = glm::scale(model, glm::vec3(0.73f, 0.73f, 0.73f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 155 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, -1.0f, 24.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 110 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();



		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-11.0f, -1.0f, 27.0f));
		model = glm::scale(model, glm::vec3(0.77f, 0.77f, 0.77f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 185 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, -1.0f, 30.0f));
		model = glm::scale(model, glm::vec3(0.97f, 0.97f, 0.97f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//
				//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.0f, -1.0f, 9.0f));
		model = glm::scale(model, glm::vec3(0.97f, 0.97f, 0.97f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.0f, -1.0f, 12.0f));
		model = glm::scale(model, glm::vec3(0.91f, 0.91f, 0.91f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 83 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -1.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.72f, 0.72f, 0.72f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 110 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -1.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.72f, 0.72f, 0.72f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-9.0f, -1.0f, 18.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-9.0f, -1.0f, 21.0f));
		model = glm::scale(model, glm::vec3(0.68f, 0.68f, 0.68f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 23 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -1.0f, 25.0f));
		model = glm::scale(model, glm::vec3(0.87f, 0.87f, 0.87f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -1.0f, 26.0f));
		model = glm::scale(model, glm::vec3(0.48f, 0.48f, 0.48f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 33 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -1.0f, 26.0f));
		model = glm::scale(model, glm::vec3(0.48f, 0.48f, 0.48f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-9.0f, -1.0f, 31.0f));
		model = glm::scale(model, glm::vec3(0.94f, 0.94f, 0.94f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 140 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//X POSITIVAS///////////////////
				//z POSITIVAS

				//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -1.0f, 30.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -1.0f, 28.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -1.0f, 26.0f));
		model = glm::scale(model, glm::vec3(0.88f, 0.88f, 0.88f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -1.0f, 24.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -1.0f, 22.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -1.0f, 20.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -1.0f, 18.0f));
		model = glm::scale(model, glm::vec3(0.96f, 0.96f, 0.96f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -1.0f, 16.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 75 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -1.0f, 16.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -1.0f, 14.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -1.0f, 12.0f));
		model = glm::scale(model, glm::vec3(0.65f, 0.65f, 0.65f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f)); 
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -1.0f, 10.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 20 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -1.0f, 8.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 35 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, -1.0f, 8.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(27.0f, -1.0f, 9.0f));
		model = glm::scale(model, glm::vec3(0.82f, 0.82f, 0.82f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 27 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(26.0f, -1.0f, 12.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(28.0f, -1.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.90f, 0.90f, 0.90f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(23.0f, -1.0f, 16.0f));
		model = glm::scale(model, glm::vec3(0.46f, 0.46f, 0.46f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(27.0f, -1.0f, 18.0f));
		model = glm::scale(model, glm::vec3(0.80f, 0.80f, 0.80f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(26.0f, -1.0f, 21.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 360 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(28.0f, -1.0f, 24.0f));
		model = glm::scale(model, glm::vec3(0.70f, 0.70f, 0.70f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 80 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(27.0f, -1.0f, 27.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 160 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(24.0f, -1.0f, 30.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(24.0f, -1.0f, 27.0f));
		model = glm::scale(model, glm::vec3(0.55f, 0.55f, 0.55f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 100 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, -1.0f, 24.0f));
		model = glm::scale(model, glm::vec3(0.70f, 0.70f, 0.70f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 100 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(24.0f, -1.0f, 20.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 100 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(23.0f, -1.0f, 16.0f));
		model = glm::scale(model, glm::vec3(0.46f, 0.46f, 0.46f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(23.0f, -1.0f, 16.0f));
		model = glm::scale(model, glm::vec3(0.46f, 0.46f, 0.46f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(24.0f, -1.0f, 12.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 85 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, -1.0f, 8.0f));
		model = glm::scale(model, glm::vec3(0.96f, 0.96f, 0.96f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 185 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(21.0f, -1.0f, 9.0f));
		model = glm::scale(model, glm::vec3(0.86f, 0.86f, 0.86f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 185 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(22.0f, -1.0f, 12.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, -1.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, -1.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(21.0f, -1.0f, 18.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 85 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(21.0f, -1.0f, 21.0f));
		model = glm::scale(model, glm::vec3(0.92f, 0.92f, 0.92f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(22.0f, -1.0f, 24.0f));
		model = glm::scale(model, glm::vec3(0.49f, 0.49f, 0.49f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 5 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(22.0f, -1.0f, 27.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, -1.0f, 30.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 110 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(18.0f, -1.0f, 10.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(19.0f, -1.0f, 13.0f));
		model = glm::scale(model, glm::vec3(0.97f, 0.97f, 0.97f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(17.0f, -1.0f, 16.0f));
		model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 190 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(19.0f, -1.0f, 19.0f));
		model = glm::scale(model, glm::vec3(0.88f, 0.88f, 0.88f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 35 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(18.0f, -1.0f, 22.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(18.0f, -1.0f, 22.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(17.0f, -1.0f, 25.0f));
		model = glm::scale(model, glm::vec3(0.72f, 0.72f, 0.72f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 145 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();



		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(18.0f, -1.0f, 28.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(19.0f, -1.0f, 31.0f));
		model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(19.0f, -1.0f, 31.0f));
		model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		/////////////

////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(16.0f, -1.0f, 7.0f));
		model = glm::scale(model, glm::vec3(0.76f, 0.76f, 0.76f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 19 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();



		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(17.0f, -1.0f, 13.0f));
		model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 190 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(17.0f, -1.0f, 14.0f));
		model = glm::scale(model, glm::vec3(0.78f, 0.78f, 0.78f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(17.0f, -1.0f, 14.0f));
		model = glm::scale(model, glm::vec3(0.78f, 0.78f, 0.78f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(16.0f, -1.0f, 17.0f));
		model = glm::scale(model, glm::vec3(0.55f, 0.55f, 0.55f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 110 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.0f, -1.0f, 20.0f));
		model = glm::scale(model, glm::vec3(0.98f, 0.98f, 0.98f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 330 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(16.0f, -1.0f, 23.0f));
		model = glm::scale(model, glm::vec3(0.73f, 0.73f, 0.73f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 195 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(16.0f, -1.0f, 23.0f));
		model = glm::scale(model, glm::vec3(0.73f, 0.73f, 0.73f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();


		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(17.0f, -1.0f, 26.0f));
		model = glm::scale(model, glm::vec3(0.57f, 0.57f, 0.57f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(16.0f, -1.0f, 29.0f));
		model = glm::scale(model, glm::vec3(0.72f, 0.72f, 0.72f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 25 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//////////////////////////////
				/////////////

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(12.0f, -1.0f, 9.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 33 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(12.0f, -1.0f, 12.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 119 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();



		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(13.0f, -1.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.82f, 0.82f, 0.82f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 110 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(13.0f, -1.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.82f, 0.82f, 0.82f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(11.0f, -1.0f, 18.0f));
		model = glm::scale(model, glm::vec3(0.62f, 0.62f, 0.62f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 225 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(12.0f, -1.0f, 21.0f));
		model = glm::scale(model, glm::vec3(0.73f, 0.73f, 0.73f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 155 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(13.0f, -1.0f, 24.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.95f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 110 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();



		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(11.0f, -1.0f, 27.0f));
		model = glm::scale(model, glm::vec3(0.77f, 0.77f, 0.77f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 185 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();


		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(13.0f, -1.0f, 30.0f));
		model = glm::scale(model, glm::vec3(0.97f, 0.97f, 0.97f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//
				//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(8.0f, -1.0f, 9.0f));
		model = glm::scale(model, glm::vec3(0.97f, 0.97f, 0.97f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(8.0f, -1.0f, 12.0f));
		model = glm::scale(model, glm::vec3(0.91f, 0.91f, 0.91f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 83 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(8.0f, -1.0f, 12.0f));
		model = glm::scale(model, glm::vec3(0.91f, 0.91f, 0.91f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, -1.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.72f, 0.72f, 0.72f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 110 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(9.0f, -1.0f, 18.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(9.0f, -1.0f, 21.0f));
		model = glm::scale(model, glm::vec3(0.68f, 0.68f, 0.68f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 23 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();

		////árbol amarillo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, -1.0f, 25.0f));
		model = glm::scale(model, glm::vec3(0.87f, 0.87f, 0.87f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, -1.0f, 25.0f));
		model = glm::scale(model, glm::vec3(0.87f, 0.87f, 0.87f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();

		//árbol rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, -1.0f, 26.0f));
		model = glm::scale(model, glm::vec3(0.48f, 0.48f, 0.48f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 33 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();

		//árbol rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(9.0f, -1.0f, 31.0f));
		model = glm::scale(model, glm::vec3(0.94f, 0.94f, 0.94f));
		model = glm::rotate(model, sacude_tronco * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 140 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol_H.RenderModel();
		model = arbol_aux;
		model = glm::translate(model, glm::vec3(0.0f, 10.0f - tira_hojas, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, sacude_hojas * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_q_caen.RenderModel();
		//Hojas tiradas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(9.0f, -1.0f, 31.0f));
		model = glm::scale(model, glm::vec3(0.94f, 0.94f, 0.94f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Hojas_Piso_M.RenderModel();




		/////////////////////////////////////////////////////////////TERMINAN ARBOLES////////////////////////////////////////////////

		//ILUMINACION


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.0f, -0.5f, -25.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
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
		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		antorcha.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(26.0f, -1.0f, 4.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		lampara.RenderModel();



		//FOGATA
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fogata_M.RenderModel();

		//SHOW DE LUCES//////////////
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 6.8f, -18.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		base_show.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(4.5f, -1.0f, -12.5f));
		model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.35f));
		model = glm::rotate(model, 160 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.1f, -1.0f, -23.5f));
		model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.35f));
		model = glm::rotate(model, 340 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_T.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 6.8f, -18.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, giro_lamp_1 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lamp_show.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 6.8f, -16.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, giro_lamp_2 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lamp_show.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 6.8f, -14.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, giro_lamp_3 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lamp_show.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 6.8f, -20.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, giro_lamp_4 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lamp_show.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 6.8f, -22.0f));
		model = glm::rotate(model, giro_lamp_5 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lamp_show.RenderModel();


		///////////////////////TERMINA ILUMINACION////////////////////////////

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
		model = glm::translate(model, glm::vec3(6.0f * (sin((giroSimios + 90.0f) * toRadians)), abs(sin((giroSimios * 0.5f))), 6.0f * (cos((giroSimios + 90.0f) * toRadians))));
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
		model = glm::translate(model, glm::vec3(6.0f * (sin((giroSimios - 90.0f) * toRadians)), abs(sin((giroSimios * 0.5f))), 6.0f * (cos((giroSimios - 90.0f) * toRadians))));
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
		model = glm::translate(model, glm::vec3(6.0f * (sin((giroSimios + 0.0f) * toRadians)), abs(sin((giroSimios * 0.5f))), 6.0f * (cos((giroSimios + 0.0f) * toRadians))));
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
		model = glm::translate(model, glm::vec3(6.0f * (sin((giroSimios + 180.0f) * toRadians)), abs(sin((giroSimios * 0.5f))), 6.0f * (cos((giroSimios + 180.0f) * toRadians))));
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
		model = glm::translate(model, glm::vec3(6.0f * (sin((giroSimios + 135.0f) * toRadians)), abs(sin((giroSimios * 0.5f) + 90.0f)), 6.0f * (cos((giroSimios + 135.0f) * toRadians))));
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
		model = glm::translate(model, glm::vec3(6.0f * (sin((giroSimios + 225.0f) * toRadians)), abs(sin((giroSimios * 0.5f) + 90.0f)), 6.0f * (cos((giroSimios + 225.0f) * toRadians))));
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
		model = glm::translate(model, glm::vec3(6.0f * (sin((giroSimios + 315.0f) * toRadians)), abs(sin((giroSimios * 0.5f) + 90.0f)), 6.0f * (cos((giroSimios + 315.0f) * toRadians))));
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
		model = glm::translate(model, glm::vec3(6.0f * (sin((giroSimios + 45.0f) * toRadians)), abs(sin((giroSimios * 0.5f) + 90.0f)), 6.0f * (cos((giroSimios + 45.0f) * toRadians))));
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
		if (mainWindow.getlanzadera() == 1) {
			if (giroArma <= 60.0f) {
				giroArma += 1.0;
			}
		}
		else {
			if (giroArma >= 50.0f) {
				giroArma = 0;
			}
		}


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 30.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArmaKND_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(1.0f, 0.1f, 0.0087f));
		model = glm::rotate(model, giroArma * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LanzaderaKND_M.RenderModel();

		model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-0.5f, 1.2f, 31.0f));
		if (((10.0f * cos(giroArma * toRadians)) - 8.8f) >= -1.0f) {
			model = glm::translate(model, glm::vec3((10.0f * sin(giroArma * toRadians)) - 0.5f, (10.0f * cos(giroArma * toRadians)) - 8.8f, 30.2f));
		}
		else {

			model = glm::translate(model, glm::vec3((10.0f * sin(giroArma * toRadians)) - 0.5f, -1.0f, 30.2f));
			model = glm::rotate(model, giroArma * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		}
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Pelota_M.RenderModel();

		//FUENTE
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, -3.0f, -20.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fuente_M.RenderModel();

		//TOROIDES

		color = glm::vec3(1.0f, 0.0f, 0.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 10.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Usamos una textura lisa 
		caminoTexture.UseTexture(); 
		//RENDER
		toro.render();


		//RENDER
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(pos_per.x, pos_per.y-0.85, pos_per.z - 3.5));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		salvavidasTexture.UseTexture();
		toroide.render();


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}