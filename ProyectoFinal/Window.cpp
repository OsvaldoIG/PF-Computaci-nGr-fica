#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	muevex = 2.0f;
	tipoCamara = 0;

	//animación tala
	tala_arbol = 0;
	bandera_tala = true ;

	camina = 0;
	desplaza = 0;

	lanzadera = 0;
	luz_lampara = 0;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "PROYECTO FINAL MAYA-IBANEZ", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_W) {
		if (action == GLFW_PRESS)
		{
			theWindow->camina = 1;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->camina = 0;
		}
	}

	if (key == GLFW_KEY_D) {
		if (action == GLFW_PRESS)
		{
			theWindow->desplaza = 1;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->desplaza = 0;
		}
	}
	if (key == GLFW_KEY_S) {
		if (action == GLFW_PRESS)
		{
			theWindow->camina = 1;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->camina = 0;
		}
	}

	if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS)
		{
			theWindow->desplaza = 1;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->desplaza = 0;
		}
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_Y)
	{
		if(theWindow->muevex <= 111)
			theWindow-> muevex += 1.0;
	}
	if (key == GLFW_KEY_U)
	{
		if (theWindow->muevex >= -111)
			theWindow-> muevex -= 1.0;
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		if (theWindow->tipoCamara == 0) {
			theWindow->tipoCamara = 1;
		}
		else {
			theWindow->tipoCamara = 0;
		}
	}
	if (key == GLFW_KEY_P) {
			theWindow->tala_arbol = 1; //Comienza la animación
	}
	if (key == GLFW_KEY_L) {
		theWindow->tala_arbol = 0; //Para la animación
	}
	if (key == GLFW_KEY_K) {
		theWindow->luz_lampara = 1; //Se prende la lámpara
	}
	if (key == GLFW_KEY_M) {
		theWindow->luz_lampara = 0; //Se apaga la lámpara
	}
	if (key == GLFW_KEY_O) {
		theWindow->lanzadera = 1;
	}
	if (key == GLFW_KEY_K) {
		theWindow->lanzadera = 0;
	}

	GLint tala_arbol;
	GLint bandera_tala;


	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
