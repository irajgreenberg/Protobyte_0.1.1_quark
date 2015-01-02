#include "Testing_Tessellation.h"
GLUtesselator* iraTesselator2 = gluNewTess();

int iraInit() {
	// Create a new tessellation object 
	
	if (!iraTesselator2) return 0;

	// Set callback functions
	gluTessCallback(iraTesselator2, GLU_TESS_VERTEX, (GLvoid(__stdcall *)()) &iraVertexCallback);
	gluTessCallback(iraTesselator2, GLU_TESS_BEGIN, (GLvoid(__stdcall *)()) &iraTestMeBegin);
	gluTessCallback(iraTesselator2, GLU_TESS_END, (GLvoid(__stdcall *)()) &iraTestMeEnd);
	gluTessCallback(iraTesselator2, GLU_TESS_COMBINE, (GLvoid(__stdcall *)()) &iraCombineCallback);
	gluTessCallback(iraTesselator2, GLU_TESS_ERROR, (GLvoid(__stdcall *)()) &iraTesellationError);
	return 1;
}

void iraSetWindingRule(GLenum windingRule) {
	gluTessProperty(iraTesselator2, GLU_TESS_WINDING_RULE, windingRule);
}

void iraBeginPolygon() {
	gluTessBeginPolygon(iraTesselator2, NULL);
}

void iraBeginContour() {
	gluTessBeginContour(iraTesselator2);
}

void iraCountourVertex(std::vector<GLdouble> data) {
	std::cout << "data.size() = " << data.size() << std::endl;

	//loop through the vertices
	for (int i = 0; i < data.size() - 7; i += 7){
		//std::cout << "data = " << data[i] << std::endl;
		GLdouble tempVals[] = { data.at(i), data.at(i + 1), data.at(i + 2), data.at(i + 3), data.at(i + 4), data.at(i + 5), data.at(i + 6) };
		gluTessVertex(iraTesselator2, tempVals, (void*)tempVals); //store the vertex
	}
}

void iraAddContourVertex(GLdouble obj_data[][6], int num_vertices) {
	std::cout << "in addContourVertex" << std::endl;
	//loop through the vertices
	for (int i = 0; i < num_vertices; ++i){
		gluTessVertex(iraTesselator2, obj_data[i], obj_data[i]); //store the vertex
	}
}

void iraEndContour() {
	gluTessEndContour(iraTesselator2);
}

void iraEndPolygon() {
	gluTessEndPolygon(iraTesselator2);


}



void iraEnd() {
	std::cout << "here" << std::endl;
	gluDeleteTess(iraTesselator2);
}



void CALLBACK iraTestMeBegin(GLenum triangleMode) {
	std::cout << "in testMeBegin callback, triangleMode = " << triangleMode << std::endl;
	//std::cout << "in testMeBegin callback" << std::endl;
}



void CALLBACK iraVertexCallback(GLvoid *vertex) {
	std::cout << "in vertex callback" << std::endl;
}


void CALLBACK iraTestMeEnd() {
	std::cout << "in testMeEnd callback" << std::endl;
}

void CALLBACK iraTesellationError(GLenum errorCode) {
	const GLubyte *estring;

	estring = gluErrorString(errorCode);
	fprintf(stderr, "Tessellation Error: %s\n", estring);
	//exit(0);
}

void CALLBACK iraCombineCallback(GLdouble coords[3],
	GLdouble *vertex_data[4], GLfloat weight[4], GLdouble **dataOut) {
	GLdouble *vertex;
	int i;

	vertex = (GLdouble *)malloc(6 * sizeof(GLdouble));
	vertex[0] = coords[0];
	vertex[1] = coords[1];
	vertex[2] = coords[2];
	for (i = 3; i < 6; i++)
		vertex[i] = weight[0] * vertex_data[0][i]
		+ weight[1] * vertex_data[1][i]
		+ weight[2] * vertex_data[2][i]
		+ weight[3] * vertex_data[3][i];
	*dataOut = vertex;
}



