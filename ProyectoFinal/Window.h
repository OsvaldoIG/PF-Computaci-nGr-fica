#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }
	GLint gettipoCamara() { return tipoCamara;  }
	GLint gettala() { return tala_arbol; }

	GLint getCamina() { return camina; }
	GLint getDesplaza() { return desplaza; }

	GLint getLuzLampara() { return luz_lampara; }
	GLint getShowLuces() { return show_luces; }

	bool getbandera() { return bandera_tala; }
	GLint getlanzadera() { return lanzadera; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	GLint tipoCamara;
	GLint tala_arbol;
	GLint camina;
	GLint desplaza;
	GLint lanzadera;
	GLint luz_lampara;
	GLint show_luces;
	bool bandera_tala;
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

