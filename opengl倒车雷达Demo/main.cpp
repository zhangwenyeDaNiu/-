#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include<cv.h>
#include<highgui.h>
#include<opencv2/opencv.hpp>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <time.h>
using namespace cv;
using namespace std;

GLuint ShaderProgram;
GLuint ShaderProgramLeft;
GLuint ShaderProgramLeftRoate;
GLuint ShaderProgramRightRoate;

GLuint ShaderProgramYellow;
GLuint ShaderProgramLeftYellow;
GLuint ShaderProgramLeftRoateYellow;
GLuint ShaderProgramRightRoateYellow;

GLuint ShaderProgramGreen;
GLuint ShaderProgramLeftGreen;
GLuint ShaderProgramLeftRoateGreen;
GLuint ShaderProgramRightRoateGreen;

GLuint ShaderProgramTex;
GLuint textureId;
float radarVertices[800] = {};
float radarVerticesYellow[800] = {};
float radarVerticesGreen[800] = {};

float R3 = 0.94f;
float R2 = 0.77f;
float R = 0.62f;
float pi = 3.1415926535898;
GLushort indicesRadar[100];
float mat[4][4] = { { 1, 0, 0, 0 },
{ 0, 1, 0, 0 },
{ 0, 0, 1, 0 },
{ 0, 0, 0, 1 }
};

float a = pi / 180 * 23;
float matRoateLeft[4][4] = { { cos(a), -sin(a), 0, 0 },
{ sin(a), cos(a), 0, 0 },
{ 0, 0, 1, 0 },
{ 0, 0, 0, 1 }
};
float b = -pi / 180 * 23;
float matRoateRight[4][4] = { { cos(b), -sin(b), 0, 0 },
{ sin(b), cos(b), 0, 0 },
{ 0, 0, 1, 0 },
{ 0, 0, 0, 1 }
};;;;;;
GLfloat verticesTex[32] =
{
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // 0
	1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // 1
	-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // 2
	1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f     // 3
};

GLushort indicesTex[] =
{
	0, 1, 2,  // ��һ��������
	2, 1, 3,   // �ڶ���������
};
void setRadarYellow()
{
	for (int i = 0; i < 50; i++)
	{
		radarVerticesYellow[8 * i] = R2*sin(0.1*pi / 50 * i);
		radarVerticesYellow[8 * i + 1] = R2*cos(0.1*pi / 50 * i);
		radarVerticesYellow[8 * i + 2] = 0;
		radarVerticesYellow[8 * i + 3] = 0;
		radarVerticesYellow[8 * i + 4] = 1;
		radarVerticesYellow[8 * i + 5] = 1;
		radarVerticesYellow[8 * i + 6] = 0;
		radarVerticesYellow[8 * i + 7] = 1;
		indicesRadar[i] = i;
	}
	for (int i = 49; i > -1; i--)
	{
		radarVerticesYellow[8 * (49 - i) + 400] = R2 *0.85 * sin(0.1*pi / 50 * i);
		radarVerticesYellow[8 * (49 - i) + 1 + 400] = R2 *0.85 * cos(0.1*pi / 50 * i);
		radarVerticesYellow[8 * (49 - i) + 2 + 400] = 0;
		radarVerticesYellow[8 * (49 - i) + 3 + 400] = 0;
		radarVerticesYellow[8 * (49 - i) + 4 + 400] = 1;
		radarVerticesYellow[8 * (49 - i) + 5 + 400] = 0;
		radarVerticesYellow[8 * (49 - i) + 6 + 400] = 0;
		radarVerticesYellow[8 * (49 - i) + 7 + 400] = 1;
		indicesRadar[(49 - i) + 50] = (49 - i) + 50;
	}

}

void setRadarGreen()
{
	for (int i = 0; i < 50; i++)
	{
		radarVerticesGreen[8 * i] = R3*sin(0.1*pi / 50 * i);
		radarVerticesGreen[8 * i + 1] = R3*cos(0.1*pi / 50 * i);
		radarVerticesGreen[8 * i + 2] = 0;
		radarVerticesGreen[8 * i + 3] = 0;
		radarVerticesGreen[8 * i + 4] = 1;
		radarVerticesGreen[8 * i + 5] = 1;
		radarVerticesGreen[8 * i + 6] = 0;
		radarVerticesGreen[8 * i + 7] = 1;
		indicesRadar[i] = i;
	}
	for (int i = 49; i > -1; i--)
	{
		radarVerticesGreen[8 * (49 - i) + 400] = R3 *0.85 * sin(0.1*pi / 50 * i);
		radarVerticesGreen[8 * (49 - i) + 1 + 400] = R3 *0.85 * cos(0.1*pi / 50 * i);
		radarVerticesGreen[8 * (49 - i) + 2 + 400] = 0;
		radarVerticesGreen[8 * (49 - i) + 3 + 400] = 0;
		radarVerticesGreen[8 * (49 - i) + 4 + 400] = 1;
		radarVerticesGreen[8 * (49 - i) + 5 + 400] = 0;
		radarVerticesGreen[8 * (49 - i) + 6 + 400] = 0;
		radarVerticesGreen[8 * (49 - i) + 7 + 400] = 1;
		indicesRadar[(49 - i) + 50] = (49 - i) + 50;
	}

}

void setRadar()
{
	for (int i = 0; i < 50; i++)
	{
		radarVertices[8 * i] = R*sin(0.1*pi / 50 * i);
		radarVertices[8 * i + 1] = R*cos(0.1*pi / 50 * i);
		radarVertices[8 * i + 2] = 0;
		radarVertices[8 * i + 3] = 0;
		radarVertices[8 * i + 4] = 1;
		radarVertices[8 * i + 5] = 0;
		radarVertices[8 * i + 6] = 0;
		radarVertices[8 * i + 7] = 1;
		indicesRadar[i] = i;
	}
	for (int i = 49; i > -1; i--)
	{
		radarVertices[8 * (49 - i) + 400] = R *0.8 * sin(0.1*pi / 50 * i);
		radarVertices[8 * (49 - i) + 1 + 400] = R *0.8 * cos(0.1*pi / 50 * i);
		radarVertices[8 * (49 - i) + 2 + 400] = 0;
		radarVertices[8 * (49 - i) + 3 + 400] = 0;
		radarVertices[8 * (49 - i) + 4 + 400] = 1;
		radarVertices[8 * (49 - i) + 5 + 400] = 0;
		radarVertices[8 * (49 - i) + 6 + 400] = 0;
		radarVertices[8 * (49 - i) + 7 + 400] = 1;
		indicesRadar[(49 - i) + 50] = (49 - i) + 50;
	}

}

void initVerticesTex()
{
	//����λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(GLfloat), &verticesTex[0]);
	glEnableVertexAttribArray(0);
	//������ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), &verticesTex[0] + 3);
	glEnableVertexAttribArray(1);
	//������������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), &verticesTex[0] + 6);
	glEnableVertexAttribArray(2);
}
void randerTex()
{

	glUniform1i(glGetUniformLocation(ShaderProgramTex, "tex"), 0);
	//ʹ����������
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, &indicesTex[0]);

}

void initTexture2D()
{
	//step1 �������������
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	//step2 �趨warp����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//LoadImageFile("C:\\Users\\zhufeng\\Desktop\\new.bmp");


	cv::Mat pic = cv::imread("C:\\Users\\Administrator\\Desktop\\car1.png");
	//imshow("ddd", pic);
	//waitKey();
	flip(pic, pic, 1);




	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pic.cols, pic.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, pic.data);
	//glGenerateMipmap(GL_TEXTURE_2D);
	//step5 �ͷ�����ͼƬ��Դ
	//free(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

static void RenderSceneCB()
{
	glUseProgram(ShaderProgramTex);
	initVerticesTex();
	randerTex();


	glUseProgram(ShaderProgram);
	GLint g_mvpMatrix = glGetUniformLocation(ShaderProgram, "u_mvpMat");
	glUniformMatrix4fv(g_mvpMatrix, 1, false, &mat[0][0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), radarVertices);
	glEnableVertexAttribArray(0);
	glDrawElements(GL_POLYGON, 100, GL_UNSIGNED_SHORT, &indicesRadar[0]);
	glDisableVertexAttribArray(0);

	glUseProgram(ShaderProgramLeft);
	GLint g_mvpMatrixLeft = glGetUniformLocation(ShaderProgramLeft, "u_mvpMatLeft");
	glUniformMatrix4fv(g_mvpMatrixLeft, 1, false, &mat[0][0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), radarVertices);
	glEnableVertexAttribArray(0);
	glDrawElements(GL_POLYGON, 100, GL_UNSIGNED_SHORT, &indicesRadar[0]);
	glDisableVertexAttribArray(0);

	glUseProgram(ShaderProgramLeftRoate);
	GLint g_mvpMatrixLeftRoate = glGetUniformLocation(ShaderProgramLeftRoate, "u_mvpMatLeftRoate");
	glUniformMatrix4fv(g_mvpMatrixLeftRoate, 1, false, &matRoateLeft[0][0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), radarVertices);
	glEnableVertexAttribArray(0);
	glDrawElements(GL_POLYGON, 100, GL_UNSIGNED_SHORT, &indicesRadar[0]);
	glDisableVertexAttribArray(0);


	glUseProgram(ShaderProgramRightRoate);
	GLint g_mvpMatrixRightRoate = glGetUniformLocation(ShaderProgramRightRoate, "u_mvpMatRightRoate");
	glUniformMatrix4fv(g_mvpMatrixRightRoate, 1, false, &matRoateRight[0][0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), radarVertices);
	glEnableVertexAttribArray(0);
	glDrawElements(GL_POLYGON, 100, GL_UNSIGNED_SHORT, &indicesRadar[0]);
	glDisableVertexAttribArray(0);

	///////////////////////////////////////////////////////////////////////////////////////////////

	glUseProgram(ShaderProgramYellow);
	GLint g_mvpMatrixYellow = glGetUniformLocation(ShaderProgramYellow, "u_mvpMatYellow");
	glUniformMatrix4fv(g_mvpMatrixYellow, 1, false, &mat[0][0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), radarVerticesYellow);
	glEnableVertexAttribArray(0);
	glDrawElements(GL_POLYGON, 100, GL_UNSIGNED_SHORT, &indicesRadar[0]);
	glDisableVertexAttribArray(0);

	glUseProgram(ShaderProgramLeftYellow);
	GLint g_mvpMatrixLeftYellow = glGetUniformLocation(ShaderProgramLeftYellow, "u_mvpMatLeftYellow");
	glUniformMatrix4fv(g_mvpMatrixLeftYellow, 1, false, &mat[0][0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), radarVerticesYellow);
	glEnableVertexAttribArray(0);
	glDrawElements(GL_POLYGON, 100, GL_UNSIGNED_SHORT, &indicesRadar[0]);
	glDisableVertexAttribArray(0);

	glUseProgram(ShaderProgramLeftRoateYellow);
	GLint g_mvpMatrixLeftRoateYellow = glGetUniformLocation(ShaderProgramLeftRoateYellow, "u_mvpMatLeftRoateYellow");
	glUniformMatrix4fv(g_mvpMatrixLeftRoateYellow, 1, false, &matRoateLeft[0][0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), radarVerticesYellow);
	glEnableVertexAttribArray(0);
	glDrawElements(GL_POLYGON, 100, GL_UNSIGNED_SHORT, &indicesRadar[0]);
	glDisableVertexAttribArray(0);


	glUseProgram(ShaderProgramRightRoateYellow);
	GLint g_mvpMatrixRightRoateYellow = glGetUniformLocation(ShaderProgramRightRoateYellow, "u_mvpMatRightRoateYellow");
	glUniformMatrix4fv(g_mvpMatrixRightRoateYellow, 1, false, &matRoateRight[0][0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), radarVerticesYellow);
	glEnableVertexAttribArray(0);
	glDrawElements(GL_POLYGON, 100, GL_UNSIGNED_SHORT, &indicesRadar[0]);
	glDisableVertexAttribArray(0);

	/////////////////////////////////////////////////////////////////////////////////////////////
	glUseProgram(ShaderProgramGreen);
	GLint g_mvpMatrixGreen = glGetUniformLocation(ShaderProgramGreen, "u_mvpMatGreen");
	glUniformMatrix4fv(g_mvpMatrixGreen, 1, false, &mat[0][0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), radarVerticesGreen);
	glEnableVertexAttribArray(0);
	glDrawElements(GL_POLYGON, 100, GL_UNSIGNED_SHORT, &indicesRadar[0]);
	glDisableVertexAttribArray(0);

	glUseProgram(ShaderProgramLeftGreen);
	GLint g_mvpMatrixLeftGreen = glGetUniformLocation(ShaderProgramLeftGreen, "u_mvpMatLeftGreen");
	glUniformMatrix4fv(g_mvpMatrixLeftGreen, 1, false, &mat[0][0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), radarVerticesGreen);
	glEnableVertexAttribArray(0);
	glDrawElements(GL_POLYGON, 100, GL_UNSIGNED_SHORT, &indicesRadar[0]);
	glDisableVertexAttribArray(0);

	glUseProgram(ShaderProgramLeftRoateGreen);
	GLint g_mvpMatrixLeftRoateGreen = glGetUniformLocation(ShaderProgramLeftRoateGreen, "u_mvpMatLeftRoateGreen");
	glUniformMatrix4fv(g_mvpMatrixLeftRoateGreen, 1, false, &matRoateLeft[0][0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), radarVerticesGreen);
	glEnableVertexAttribArray(0);
	glDrawElements(GL_POLYGON, 100, GL_UNSIGNED_SHORT, &indicesRadar[0]);
	glDisableVertexAttribArray(0);


	glUseProgram(ShaderProgramRightRoateGreen);
	GLint g_mvpMatrixRightRoateGreen = glGetUniformLocation(ShaderProgramRightRoateGreen, "u_mvpMatRightRoateGreen");
	glUniformMatrix4fv(g_mvpMatrixRightRoateGreen, 1, false, &matRoateRight[0][0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), radarVerticesGreen);
	glEnableVertexAttribArray(0);
	glDrawElements(GL_POLYGON, 100, GL_UNSIGNED_SHORT, &indicesRadar[0]);
	glDisableVertexAttribArray(0);



	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutSwapBuffers();
}


//static void InitializeGlutCallbacks()
//{
//	glutDisplayFunc(RenderSceneCB);
//}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
	// ����Ⱦ�ص�ע��Ϊȫ�����ûص�
	glutIdleFunc(RenderSceneCB);
}

// ʹ��shader�ı�����shader���󣬲���shader���뵽��ɫ��������
static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	// ����shader���Ͳ�����������shader����
	GLuint ShaderObj = glCreateShader(ShaderType);
	// ����Ƿ���ɹ�
	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}

	// ����shader�Ĵ���Դ
	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	glShaderSource(ShaderObj, 1, p, Lengths);
	glCompileShader(ShaderObj);// ����shader����

	// ����shader��صĴ���
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}

	// ������õ�shader����󶨵�program object���������
	glAttachShader(ShaderProgram, ShaderObj);
}






void CompileShadersTex()
{
	ShaderProgramTex = glCreateProgram();
	std::string vs, fs;
	if (ShaderProgramTex == 0)
	{
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	vs =
		"#version 330\n"
		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec3 color;\n"
		"layout(location = 2) in vec2 textCoord;\n"
		"out vec3 VertColor;\n"
		"out vec2 TextCoord;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position, 1.0);\n"
		"VertColor = color;\n"
		"TextCoord = textCoord;\n"
		"}\n";

	fs =
		"#version 330\n"
		"in vec3 VertColor;\n"
		"in vec2 TextCoord;\n"
		"uniform sampler2D tex;\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = texture(tex, TextCoord);\n"
		"}\n";

	AddShader(ShaderProgramTex, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgramTex, fs.c_str(), GL_FRAGMENT_SHADER);
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgramTex);
	glGetProgramiv(ShaderProgramTex, GL_LINK_STATUS, &Success);
	if (Success == 0)
	{
		glGetProgramInfoLog(ShaderProgramTex, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}
	glValidateProgram(ShaderProgramTex);
	glGetProgramiv(ShaderProgramTex, GL_VALIDATE_STATUS, &Success);
	if (!Success)
	{
		glGetProgramInfoLog(ShaderProgramTex, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}
	//glUseProgram(ShaderProgramTex);
}






// ������ɫ������
static void CompileShaders()
{

	// ������ɫ������
	ShaderProgram = glCreateProgram();
	// ����Ƿ񴴽��ɹ�
	if (ShaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	// �洢��ɫ���ı����ַ�������
	string vs, fs;
	vs = " #version 330\n"
		"layout(location = 0) in vec4 Position; \n"
		"uniform mat4 u_mvpMat;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(Position.x+0.02, Position.y, Position.z, 1.0)*u_mvpMat; \n"
		"}\n";

	fs = "#version 330\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"	{\n"
		"FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n"
		"}\n";

	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	// ����shader��ɫ�����򣬲���������ش���
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// �����֤�ڵ�ǰ�Ĺ���״̬�����Ƿ���Ա�ִ��
	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// ���õ�������������ʹ������ɹ�������shader����
	//glUseProgram(ShaderProgram);
}

static void CompileShadersLeft()
{

	// ������ɫ������
	ShaderProgramLeft = glCreateProgram();
	// ����Ƿ񴴽��ɹ�
	if (ShaderProgramLeft == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	// �洢��ɫ���ı����ַ�������
	string vs, fs;
	vs = " #version 330\n"
		"layout(location = 0) in vec4 Position; \n"
		"uniform mat4 u_mvpMatLeft;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(-Position.x-0.02, Position.y, Position.z, 1.0)*u_mvpMatLeft; \n"
		"}\n";

	fs = "#version 330\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"	{\n"
		"FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n"
		"}\n";

	AddShader(ShaderProgramLeft, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgramLeft, fs.c_str(), GL_FRAGMENT_SHADER);

	// ����shader��ɫ�����򣬲���������ش���
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgramLeft);
	glGetProgramiv(ShaderProgramLeft, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgramLeft, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// �����֤�ڵ�ǰ�Ĺ���״̬�����Ƿ���Ա�ִ��
	glValidateProgram(ShaderProgramLeft);
	glGetProgramiv(ShaderProgramLeft, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgramLeft, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// ���õ�������������ʹ������ɹ�������shader����
	//glUseProgram(ShaderProgramLeft);
}

static void CompileShadersLeftRoate()
{

	// ������ɫ������
	ShaderProgramLeftRoate = glCreateProgram();
	// ����Ƿ񴴽��ɹ�
	if (ShaderProgramLeftRoate == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	// �洢��ɫ���ı����ַ�������
	string vs, fs;
	vs = " #version 330\n"
		"layout(location = 0) in vec4 Position; \n"
		"uniform mat4 u_mvpMatLeftRoate;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(-Position.x-0.02, Position.y, Position.z, 1.0)*u_mvpMatLeftRoate; \n"
		"}\n";

	fs = "#version 330\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"	{\n"
		"FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n"
		"}\n";

	AddShader(ShaderProgramLeftRoate, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgramLeftRoate, fs.c_str(), GL_FRAGMENT_SHADER);

	// ����shader��ɫ�����򣬲���������ش���
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgramLeftRoate);
	glGetProgramiv(ShaderProgramLeftRoate, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgramLeftRoate, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// �����֤�ڵ�ǰ�Ĺ���״̬�����Ƿ���Ա�ִ��
	glValidateProgram(ShaderProgramLeftRoate);
	glGetProgramiv(ShaderProgramLeftRoate, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgramLeftRoate, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// ���õ�������������ʹ������ɹ�������shader����
	//glUseProgram(ShaderProgramLeft);
}


static void CompileShadersRightRoate()
{

	// ������ɫ������
	ShaderProgramRightRoate = glCreateProgram();
	// ����Ƿ񴴽��ɹ�
	if (ShaderProgramLeftRoate == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	// �洢��ɫ���ı����ַ�������
	string vs, fs;
	vs = " #version 330\n"
		"layout(location = 0) in vec4 Position; \n"
		"uniform mat4 u_mvpMatRightRoate;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(Position.x+0.02, Position.y, Position.z, 1.0)*u_mvpMatRightRoate; \n"
		"}\n";

	fs = "#version 330\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"	{\n"
		"FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n"
		"}\n";

	AddShader(ShaderProgramRightRoate, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgramRightRoate, fs.c_str(), GL_FRAGMENT_SHADER);

	// ����shader��ɫ�����򣬲���������ش���
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgramRightRoate);
	glGetProgramiv(ShaderProgramRightRoate, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgramRightRoate, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// �����֤�ڵ�ǰ�Ĺ���״̬�����Ƿ���Ա�ִ��
	glValidateProgram(ShaderProgramRightRoate);
	glGetProgramiv(ShaderProgramRightRoate, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgramRightRoate, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// ���õ�������������ʹ������ɹ�������shader����
	//glUseProgram(ShaderProgramLeft);
}


///////////////////////////////////////////////////yellow

// ������ɫ������
static void CompileShadersYellow()
{

	// ������ɫ������
	ShaderProgramYellow = glCreateProgram();
	// ����Ƿ񴴽��ɹ�
	if (ShaderProgramYellow == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	// �洢��ɫ���ı����ַ�������
	string vs, fs;
	vs = " #version 330\n"
		"layout(location = 0) in vec4 Position; \n"
		"uniform mat4 u_mvpMatYellow;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(Position.x+0.02, Position.y, Position.z, 1.0)*u_mvpMatYellow; \n"
		"}\n";

	fs = "#version 330\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"	{\n"
		"FragColor = vec4(1.0, 1.0, 0.0, 1.0); \n"
		"}\n";

	AddShader(ShaderProgramYellow, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgramYellow, fs.c_str(), GL_FRAGMENT_SHADER);

	// ����shader��ɫ�����򣬲���������ش���
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgramYellow);
	glGetProgramiv(ShaderProgramYellow, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgramYellow, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// �����֤�ڵ�ǰ�Ĺ���״̬�����Ƿ���Ա�ִ��
	glValidateProgram(ShaderProgramYellow);
	glGetProgramiv(ShaderProgramYellow, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgramYellow, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// ���õ�������������ʹ������ɹ�������shader����
	//glUseProgram(ShaderProgram);
}

static void CompileShadersLeftYellow()
{

	// ������ɫ������
	ShaderProgramLeftYellow = glCreateProgram();
	// ����Ƿ񴴽��ɹ�
	if (ShaderProgramLeftYellow == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	// �洢��ɫ���ı����ַ�������
	string vs, fs;
	vs = " #version 330\n"
		"layout(location = 0) in vec4 Position; \n"
		"uniform mat4 u_mvpMatLeftYellow;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(-Position.x-0.02, Position.y, Position.z, 1.0)*u_mvpMatLeftYellow; \n"
		"}\n";

	fs = "#version 330\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"	{\n"
		"FragColor = vec4(1.0, 1.0, 0.0, 1.0); \n"
		"}\n";

	AddShader(ShaderProgramLeftYellow, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgramLeftYellow, fs.c_str(), GL_FRAGMENT_SHADER);

	// ����shader��ɫ�����򣬲���������ش���
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgramLeftYellow);
	glGetProgramiv(ShaderProgramLeftYellow, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgramLeftYellow, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// �����֤�ڵ�ǰ�Ĺ���״̬�����Ƿ���Ա�ִ��
	glValidateProgram(ShaderProgramLeftYellow);
	glGetProgramiv(ShaderProgramLeftYellow, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgramLeftYellow, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// ���õ�������������ʹ������ɹ�������shader����
	//glUseProgram(ShaderProgramLeft);
}

static void CompileShadersLeftRoateYellow()
{

	// ������ɫ������
	ShaderProgramLeftRoateYellow = glCreateProgram();
	// ����Ƿ񴴽��ɹ�
	if (ShaderProgramLeftRoateYellow == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	// �洢��ɫ���ı����ַ�������
	string vs, fs;
	vs = " #version 330\n"
		"layout(location = 0) in vec4 Position; \n"
		"uniform mat4 u_mvpMatLeftRoateYellow;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(-Position.x-0.02, Position.y, Position.z, 1.0)*u_mvpMatLeftRoateYellow; \n"
		"}\n";

	fs = "#version 330\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"	{\n"
		"FragColor = vec4(1.0, 1.0, 0.0, 1.0); \n"
		"}\n";

	AddShader(ShaderProgramLeftRoateYellow, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgramLeftRoateYellow, fs.c_str(), GL_FRAGMENT_SHADER);

	// ����shader��ɫ�����򣬲���������ش���
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgramLeftRoateYellow);
	glGetProgramiv(ShaderProgramLeftRoateYellow, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgramLeftRoateYellow, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// �����֤�ڵ�ǰ�Ĺ���״̬�����Ƿ���Ա�ִ��
	glValidateProgram(ShaderProgramLeftRoateYellow);
	glGetProgramiv(ShaderProgramLeftRoate, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgramLeftRoateYellow, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// ���õ�������������ʹ������ɹ�������shader����
	//glUseProgram(ShaderProgramLeft);
}


static void CompileShadersRightRoateYellow()
{

	// ������ɫ������
	ShaderProgramRightRoateYellow = glCreateProgram();
	// ����Ƿ񴴽��ɹ�
	if (ShaderProgramLeftRoateYellow == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	// �洢��ɫ���ı����ַ�������
	string vs, fs;
	vs = " #version 330\n"
		"layout(location = 0) in vec4 Position; \n"
		"uniform mat4 u_mvpMatRightRoateYellow;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(Position.x+0.02, Position.y, Position.z, 1.0)*u_mvpMatRightRoateYellow; \n"
		"}\n";

	fs = "#version 330\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"	{\n"
		"FragColor = vec4(1.0, 1.0, 0.0, 1.0); \n"
		"}\n";

	AddShader(ShaderProgramRightRoateYellow, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgramRightRoateYellow, fs.c_str(), GL_FRAGMENT_SHADER);

	// ����shader��ɫ�����򣬲���������ش���
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgramRightRoateYellow);
	glGetProgramiv(ShaderProgramRightRoateYellow, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgramRightRoateYellow, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// �����֤�ڵ�ǰ�Ĺ���״̬�����Ƿ���Ա�ִ��
	glValidateProgram(ShaderProgramRightRoateYellow);
	glGetProgramiv(ShaderProgramRightRoateYellow, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgramRightRoateYellow, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// ���õ�������������ʹ������ɹ�������shader����
	//glUseProgram(ShaderProgramLeft);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////green
// ������ɫ������
static void CompileShadersGreen()
{

	// ������ɫ������
	ShaderProgramGreen = glCreateProgram();
	// ����Ƿ񴴽��ɹ�
	if (ShaderProgramGreen == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	// �洢��ɫ���ı����ַ�������
	string vs, fs;
	vs = " #version 330\n"
		"layout(location = 0) in vec4 Position; \n"
		"uniform mat4 u_mvpMatGreen;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(Position.x+0.02, Position.y, Position.z, 1.0)*u_mvpMatGreen; \n"
		"}\n";

	fs = "#version 330\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"	{\n"
		"FragColor = vec4(0.0, 1.0, 0.0, 1.0); \n"
		"}\n";

	AddShader(ShaderProgramGreen, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgramGreen, fs.c_str(), GL_FRAGMENT_SHADER);

	// ����shader��ɫ�����򣬲���������ش���
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgramGreen);
	glGetProgramiv(ShaderProgramGreen, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgramGreen, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// �����֤�ڵ�ǰ�Ĺ���״̬�����Ƿ���Ա�ִ��
	glValidateProgram(ShaderProgramGreen);
	glGetProgramiv(ShaderProgramGreen, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgramGreen, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// ���õ�������������ʹ������ɹ�������shader����
	//glUseProgram(ShaderProgram);
}

static void CompileShadersLeftGreen()
{

	// ������ɫ������
	ShaderProgramLeftGreen = glCreateProgram();
	// ����Ƿ񴴽��ɹ�
	if (ShaderProgramLeftGreen == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	// �洢��ɫ���ı����ַ�������
	string vs, fs;
	vs = " #version 330\n"
		"layout(location = 0) in vec4 Position; \n"
		"uniform mat4 u_mvpMatLeftGreen;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(-Position.x-0.02, Position.y, Position.z, 1.0)*u_mvpMatLeftGreen; \n"
		"}\n";

	fs = "#version 330\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"	{\n"
		"FragColor = vec4(0.0, 1.0, 0.0, 1.0); \n"
		"}\n";

	AddShader(ShaderProgramLeftGreen, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgramLeftGreen, fs.c_str(), GL_FRAGMENT_SHADER);

	// ����shader��ɫ�����򣬲���������ش���
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgramLeftGreen);
	glGetProgramiv(ShaderProgramLeftGreen, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgramLeftGreen, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// �����֤�ڵ�ǰ�Ĺ���״̬�����Ƿ���Ա�ִ��
	glValidateProgram(ShaderProgramLeftGreen);
	glGetProgramiv(ShaderProgramLeftGreen, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgramLeftGreen, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// ���õ�������������ʹ������ɹ�������shader����
	//glUseProgram(ShaderProgramLeft);
}

static void CompileShadersLeftRoateGreen()
{

	// ������ɫ������
	ShaderProgramLeftRoateGreen = glCreateProgram();
	// ����Ƿ񴴽��ɹ�
	if (ShaderProgramLeftRoateGreen == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	// �洢��ɫ���ı����ַ�������
	string vs, fs;
	vs = " #version 330\n"
		"layout(location = 0) in vec4 Position; \n"
		"uniform mat4 u_mvpMatLeftRoateGreen;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(-Position.x-0.02, Position.y, Position.z, 1.0)*u_mvpMatLeftRoateGreen; \n"
		"}\n";

	fs = "#version 330\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"	{\n"
		"FragColor = vec4(0.0, 1.0, 0.0, 1.0); \n"
		"}\n";

	AddShader(ShaderProgramLeftRoateGreen, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgramLeftRoateGreen, fs.c_str(), GL_FRAGMENT_SHADER);

	// ����shader��ɫ�����򣬲���������ش���
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgramLeftRoateGreen);
	glGetProgramiv(ShaderProgramLeftRoateGreen, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgramLeftRoateGreen, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// �����֤�ڵ�ǰ�Ĺ���״̬�����Ƿ���Ա�ִ��
	glValidateProgram(ShaderProgramLeftRoateGreen);
	glGetProgramiv(ShaderProgramLeftRoateGreen, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgramLeftRoateGreen, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// ���õ�������������ʹ������ɹ�������shader����
	//glUseProgram(ShaderProgramLeft);
}


static void CompileShadersRightRoateGreen()
{

	// ������ɫ������
	ShaderProgramRightRoateGreen = glCreateProgram();
	// ����Ƿ񴴽��ɹ�
	if (ShaderProgramLeftRoateGreen == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	// �洢��ɫ���ı����ַ�������
	string vs, fs;
	vs = " #version 330\n"
		"layout(location = 0) in vec4 Position; \n"
		"uniform mat4 u_mvpMatRightRoateGreen;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(Position.x+0.02, Position.y, Position.z, 1.0)*u_mvpMatRightRoateGreen; \n"
		"}\n";

	fs = "#version 330\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"	{\n"
		"FragColor = vec4(0.0, 1.0, 0.0, 1.0); \n"
		"}\n";

	AddShader(ShaderProgramRightRoateGreen, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgramRightRoateGreen, fs.c_str(), GL_FRAGMENT_SHADER);

	// ����shader��ɫ�����򣬲���������ش���
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgramRightRoateGreen);
	glGetProgramiv(ShaderProgramRightRoateGreen, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgramRightRoateGreen, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// �����֤�ڵ�ǰ�Ĺ���״̬�����Ƿ���Ա�ִ��
	glValidateProgram(ShaderProgramRightRoateGreen);
	glGetProgramiv(ShaderProgramRightRoateGreen, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgramRightRoateGreen, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// ���õ�������������ʹ������ɹ�������shader����
	//glUseProgram(ShaderProgramLeft);
}













// ������
int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 04");

	InitializeGlutCallbacks();

	// ������glut��ʼ����
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	printf("GL version: %s\n", glGetString(GL_VERSION));

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	initTexture2D();
	setRadar();
	setRadarYellow();
	setRadarGreen();
	// ������ɫ��
	CompileShadersTex();
	CompileShaders();
	CompileShadersLeft();
	CompileShadersLeftRoate();
	CompileShadersRightRoate();

	CompileShadersYellow();
	CompileShadersLeftYellow();
	CompileShadersLeftRoateYellow();
	CompileShadersRightRoateYellow();

	CompileShadersGreen();
	CompileShadersLeftGreen();
	CompileShadersLeftRoateGreen();
	CompileShadersRightRoateGreen();
	
	glutMainLoop();

	return 0;
}
