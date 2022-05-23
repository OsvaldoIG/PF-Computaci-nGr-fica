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
//MUSICA
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

//TOROIDE
#include "Toroide.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
std::vector<MeshColor*> meshColorList;

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

Texture prueba;



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




Toroide toro = Toroide(3.0f, 1.0f, 0.5f);


int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();
	//MUSICA





	toro.init();
	toro.load();

	inidice_spotlights = 0;
	conteo_spotlights = 0;

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

	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.4f, 0.2f,
		0.0f, 0.0f, -1.0f);
	

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

		
				skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
				mainLight.SetIntensity(1.0f);
			


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

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);


		glm::mat4 model(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		//TOROIDE
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.0f, 0.5f, 10.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//model = glm::rotate(model,90*toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pisoTexture.UseTexture();
		toro.render();

		//color = glm::vec3(1.0f, 0.0f, 1.0f);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(4.0f, 0.5f, 10.0f));
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//plainTexture.UseTexture();
		//toro.render();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
