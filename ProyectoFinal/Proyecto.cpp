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

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;


Model Kitt_M;
Model Llanta_M;
Model Camino_M;
Model Blackhawk_M;
Model Aspas_M;
Model ArmaKND_M;
Model CasaLorax_M;
Model Dado_M;

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



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	//camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);
	camera = Camera(glm::vec3(0.0f, 0.25f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);

	//Aqui se importan texturas
	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();

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
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

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
		//meshList[2]->RenderMesh();

		/*
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, -1.0));
		modelaux = model;
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cortadora_M.RenderModel();
		//Blackhawk_M.RenderModel();
		*/

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

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
