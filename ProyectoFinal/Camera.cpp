#include "Camera.h"

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition; //posición de la cámara
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f); //Hace que la cámara apunte a z negativo, 

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}




void Camera::keyControl(bool* keys, GLfloat deltaTime, GLint tipo)
{
	GLfloat velocity = moveSpeed * deltaTime;
	if (tipo == 0) {
		if (position.y != 1.0f) {
			position.y = 1.0f;
		}

		if (position.x >= 27.0f) {
			position.x = 27.0f;
		}
		if (position.x <= -27.0f) {
			position.x = -27.0f;
		}
		if (position.z >= 27.0f) {
			position.z = 27.0f;
		}
		if (position.z <= -27.0f) {
			position.z = -27.0f;
		}

		if (keys[GLFW_KEY_W])
		{
			position += front * velocity;
		}

		if (keys[GLFW_KEY_S])
		{
			position -= front * velocity;
		}

		if (keys[GLFW_KEY_A])
		{
			position -= right * velocity;
		}

		if (keys[GLFW_KEY_D])
		{
			position += right * velocity;
		}

		if (keys[GLFW_KEY_Q])
		{
			position += up * velocity;
		}

		if (keys[GLFW_KEY_E])
		{
			position -= up * velocity;
		}
	}
	else {
		if (keys[GLFW_KEY_W] && position.y >= 10.0f)
		{
			position += front * velocity;
		}

		if (keys[GLFW_KEY_S] && position.y <= 30.0f)
		{
			position -= front * velocity;
		}

		if (keys[GLFW_KEY_A] && position.z <= (30.4f - position.y))
		{
			position -= right * velocity;
		}

		if (keys[GLFW_KEY_D] && position.z >= (-30.6f + position.y))
		{
			position += right * velocity;
		}

		if (keys[GLFW_KEY_Q] && position.x >= (-35.3f + position.y))
		{
			position += up * velocity;
		}

		if (keys[GLFW_KEY_E] && position.x <= (35.5f - position.y))
		{
			position -= up * velocity;
		}
	}
	

}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange, GLint tipo)
{
	

	if (tipo == 0) {
		xChange *= turnSpeed;
		yChange *= turnSpeed;
		yaw += xChange;
		pitch += yChange;
	}
	else {
		yaw = xChange; //DIRECCION EN X
		pitch = yChange;
	}


	if (pitch > 89.0f)
	{
		pitch = 90.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -90.0f;
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}


glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

void Camera::setCameraPosition(glm::vec3 pos)
{
	position = glm::vec3(10.0f,0.0,0.0);
}




void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp)); // (0,1,0)
	up = glm::normalize(glm::cross(right, front));


}


Camera::~Camera()
{
}
