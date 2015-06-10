#include "ShaderProgram2D.h"


ShaderProgram2D::ShaderProgram2D(void)
{
	programID = LoadShaders("GUIVertexShader.vertexshader","GUIFragmentShader.fragmentshader");
}


void ShaderProgram2D::CleanUp()
{
	glDeleteProgram(programID);
}

void ShaderProgram2D::UseProgram()
{
	glUseProgram(programID);

}

ShaderProgram2D::~ShaderProgram2D(void)
{
}
