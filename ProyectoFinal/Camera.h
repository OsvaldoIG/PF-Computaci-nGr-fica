#pragma once

#include <glew.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void keyControl(bool* keys, GLfloat deltaTime, GLint tipo);
	void mouseControl(GLfloat xChange, GLfloat yChange, GLint tipo);

	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();
	bool getFrente(){ return frente; };
	bool getAtras() { return atras; };
	bool getDerecha() { return derecha; };
	bool getIzquierda() { return izquierda; };
	void setCameraPosition(glm::vec3 pos);
	void setCameraDirection();
	glm::mat4 calculateViewMatrix();

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	bool frente;
	bool atras;
	bool derecha;
	bool izquierda;

	void update();
};

