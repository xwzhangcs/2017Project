#pragma once

#include "gl_core_3_3.h"
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include "Camera.h"
#include "mesh.hpp"
#include <QVector3D>
#include <vector>
#include <memory>
#include <math.h> 

using namespace std;
class MainWindow;

class GLWidget : public QGLWidget
{
public:
	GLWidget(MainWindow* parent);
	~GLWidget();
	void drawScene(int drawMode);
	float genRand();
	float genRand(float a, float b);
	int genRand(int a, int b);

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);

private:

	GLuint shader;		// Shader program
	GLuint uniXform;	// Location of transformation matrix in shader
	Camera camera;
	std::unique_ptr<Mesh> mesh;

public:
	MainWindow* mainWin;
	int road_mode;
	float road_width;
	int stories;
	float x_dim;
	float y_dim;
	float setback_front;
	float setback_rear;
	float setback_side;
	int total_triangles;
	//VAO
	GLuint VertexArrayID;
	//vertrx buffer
	GLuint vertexbuffer;
	//color buffer
	GLuint colorbuffer;
	//element buffer
	GLuint eab;
};

