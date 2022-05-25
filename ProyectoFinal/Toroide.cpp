#include "Toroide.h"

Toroide::Toroide(float RCirculo, float RAmplitud, float resolution) :
	RCirculo(RCirculo), RAmplitud(RAmplitud), resolution(resolution), VAO(0), VBO(0), EBO(0) {
}

Toroide::~Toroide() {

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDeleteBuffers(1, &EBO);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);

}

void Toroide::init() {
	vertexC.resize((360/resolution) * (360/resolution));
	index.resize((360/resolution) * (360/resolution) * 6);
	//Radio amplitud R
	//float RCirculo = 3.0;
	//Radio Circulo Toroide r
	//float RAmplitud = 1.0;
	//cuantos puntos existen
	int numPuntos = 0;
	//circulo interno
	float alpha = 0;
	//incremento circulo interno
	float incAlpha = resolution;
	//circulo amplitud
	float betha = 0;
	//incremento circulo amplitud
	float incBetha = resolution;

	for (int i = 0; i < (360.0f / incBetha); i++) {
		alpha = 0;
		for (int j = 0; j < (360.0f / incAlpha); j++) {
			alpha += incAlpha;
			float X = (RCirculo + (RAmplitud * cos(alpha))) * cos(betha);
			float Y = (RCirculo + (RAmplitud * cos(alpha))) * sin(betha);
			float Z = RAmplitud * sin(alpha);
			vertexC[i * ((360) + 1) + j].position = glm::vec3(X, Y, Z);
			vertexC[i * ((360) + 1) + j].color = glm::vec3(1.0f,1.0f,1.0f);
		}
		betha += incBetha;
	}

	for (int i = 0; i < 360 * (360.0f / incAlpha); ++i) {  //0.5 -- 43
		index[i * 6] = i;
		index[i * 6 + 1] = i + (360) + 1;
		index[i * 6 + 2] = i + (360) + 1;
		index[i * 6 + 3] = i + (360) + 1;
		index[i * 6 + 4] = i;
		index[i * 6 + 5] = i + 1;
	}

}

void Toroide::load() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	size_t stride;

	size_t offset1 = 0;
	size_t offset2 = 0;
	size_t offset3 = 0;

	glBufferData(GL_ARRAY_BUFFER, vertexC.size() * sizeof(glm::vec3) * 2,
		vertexC.data(),
		GL_STATIC_DRAW);
	stride = sizeof(vertexC[0]);
	offset1 = 0;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(GLuint),
		index.data(),
		GL_STATIC_DRAW);

	// First attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset1);
	glEnableVertexAttribArray(0);
	// Second attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
		(GLvoid*)offset2);
	glEnableVertexAttribArray(1);
	// Thrid attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset3);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}

void Toroide::render() {

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_INT,
		(GLvoid*)(sizeof(GLuint) * 0));
	glBindVertexArray(0);

}