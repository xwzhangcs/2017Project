#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLWidget.h"
#include "util.hpp"
#include "MainWindow.h"

/* Maximum value that can be returned by the rand function. */
#define RAND_MAX 0x7fff

GLWidget::GLWidget(MainWindow* mainWin) : QGLWidget(QGLFormat(QGL::SampleBuffers), (QWidget*)mainWin) {
	shader = 0;
	this->mainWin = mainWin;

	uniXform = 0;
}
GLWidget::~GLWidget() {
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	if (shader) {
		glDeleteProgram(shader); shader = 0; 
	}
}

/**
* This event handler is called when the mouse press events occur.
*/
void GLWidget::mousePressEvent(QMouseEvent *e)
{
	camera.mouseDown(e->x(), e->y());
}

/**
* This event handler is called when the mouse release events occur.
*/
void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{
	//camera.mouseUp();

	//updateGL();
}

/**
* This event handler is called when the mouse move events occur.
*/
void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
	if (e->buttons() & Qt::LeftButton) {
		camera.rotate(e->x(), e->y());
	}
	else if (e->buttons() & Qt::RightButton) {
		camera.zoom(e->x(), e->y());
	}

	updateGL();
}

/**
* This function is called once before the first call to paintGL() or resizeGL().
*/
void GLWidget::initializeGL()
{
	//std::cout << G::getInt("road_type") << std::endl;
	//std::cout << "hello" << std::endl;
	try {
		// Dark blue background
		//glClearColor(0.13f, 0.7f, 0.3f, 0.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//glClearDepth(1.0f);

		//glEnable(GL_DEPTH_TEST);

		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		// Compile and link shader program
		vector<GLuint> shaders;
		shaders.push_back(compileShader(GL_VERTEX_SHADER, "sh_v.glsl"));
		shaders.push_back(compileShader(GL_FRAGMENT_SHADER, "sh_f.glsl"));
		shader = linkProgram(shaders);
		// Release shader sources
		for (auto s = shaders.begin(); s != shaders.end(); ++s)
			glDeleteShader(*s);
		shaders.clear();
		
	}
	catch (const exception& e) {
		cerr << "Fatal error: " << e.what() << endl;
		exit(0);
	}
}

/**
* This function is called whenever the widget has been resized.
*/
void GLWidget::resizeGL(int width, int height)
{
	height = height ? height : 1;

	camera.setWindowSize(width, height);

	glViewport(0, 0, (GLint)width, (GLint)height);
}

/**
* This function is called whenever the widget needs to be painted.
*/
void GLWidget::paintGL()
{
	float whole_size = 0.95f;
	if (!G::getBool("generate")){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLfloat g_vertex_buffer_data[] = {
			-whole_size, whole_size, 0,
			whole_size, whole_size, 0,
			-whole_size, -whole_size, 0,
			whole_size, -whole_size, 0 };
		GLfloat g_color_buffer_data[] = {
			0.75f, 0.75f, 0.75f,
			0.75f, 0.75f, 0.75f,
			0.75f, 0.75f, 0.75f,
			0.75f, 0.75f, 0.75f };
		GLuint indices[] = {
			0, 1, 2,
			1, 2, 3
		};

		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

		glGenBuffers(1, &colorbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

		// Create an Element Array Buffer that will store the indices array:
		glGenBuffers(1, &eab);

		// Transfer the data from indices to eab
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eab);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glUseProgram(shader);
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
			);
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glUseProgram(0);
	}
	if (G::getBool("generate")){
		int draw_mode = G::getInt("road_type") + 1;
		//std::cout << draw_mode << std::endl;
		drawScene(draw_mode);
	}
	else{

	}

}
void GLWidget::drawScene(int drawMode){
	float whole_size = 0.95f;
	// warm up the random numbers
	for (int i = 0; i < 100; ++i) rand();
	//
	int size_r = 0;
	//road vbo
	GLfloat* g_road_buffer_data = NULL;
	//building vbo
	GLfloat* g_builds_buffer_data = NULL;
	//vbo
	GLfloat* g_vertex_buffer_data;
	//
	road_width = G::getFloat("road_width");
	stories = G::getInt("stories");
	x_dim = G::getFloat("x_dim");
	y_dim = G::getFloat("y_dim");
	//std::cout << stories << std::endl;
	//std::cout << x_dim << std::endl;
	//std::cout << y_dim << std::endl;
	float dis_side = 0.0f;
	float dis_rear = 0.0f;
	float block_dim = 0.0f;
	if (drawMode == 1){
		GLfloat tmp_buffer[] = {
			-whole_size, whole_size, 0,
			whole_size, whole_size, 0,
			-whole_size, -whole_size, 0,
			whole_size, -whole_size, 0,
			-road_width, whole_size, 0.0f,
			road_width, whole_size, 0.0f,
			-road_width, -whole_size, 0.0f,
			road_width, -whole_size, 0.0f,
			-whole_size, road_width, 0.0f,
			whole_size, road_width, 0.0f,
			-whole_size, -road_width, 0.0f,
			whole_size, -road_width, 0.0f };

		int size = sizeof(tmp_buffer) / sizeof(tmp_buffer[0]);
		g_road_buffer_data = (GLfloat *)malloc(sizeof(GLfloat)* (size));
		g_road_buffer_data = &tmp_buffer[0];
		size_r = size;
		block_dim = whole_size - road_width;

	}
	else if (drawMode == 2){
		GLfloat tmp_buffer[] = {
			-whole_size, whole_size, 0,
			whole_size, whole_size, 0,
			-whole_size, -whole_size, 0,
			whole_size, -whole_size, 0,

			-road_width, whole_size, 0.0f,
			road_width, whole_size, 0.0f,
			-road_width, -whole_size, 0.0f,
			road_width, -whole_size, 0.0f,

			-whole_size, road_width, 0.0f,
			road_width, road_width, 0.0f,
			-whole_size, -road_width, 0.0f,
			road_width, -road_width, 0.0f };
		int size = sizeof(tmp_buffer) / sizeof(tmp_buffer[0]);
		//std::cout << "size is " << size << std::endl;
		g_road_buffer_data = (GLfloat *)malloc(sizeof(GLfloat) * (size));
		g_road_buffer_data = &tmp_buffer[0];
		size_r = size;
		// configurations
		block_dim = whole_size - road_width;
	}
	else if (drawMode == 3){
		GLfloat tmp_buffer[] = {
			-whole_size, whole_size, 0,
			whole_size, whole_size, 0,
			-whole_size, -whole_size, 0,
			whole_size, -whole_size, 0,

			-road_width, whole_size, 0.0f,
			road_width, whole_size, 0.0f,
			-road_width, -whole_size, 0.0f,
			road_width, -whole_size, 0.0f };

		int size = sizeof(tmp_buffer) / sizeof(tmp_buffer[0]);
		//std::cout << "size is " << size << std::endl;
		g_road_buffer_data = (GLfloat *)malloc(sizeof(GLfloat) * (size));
		g_road_buffer_data = &tmp_buffer[0];
		size_r = size;
	}
	else if (drawMode == 4){
		GLfloat tmp_buffer[] = {
			-whole_size, whole_size, 0,
			whole_size, whole_size, 0,
			-whole_size, -whole_size, 0,
			whole_size, -whole_size, 0,

			-road_width, 0.5 * whole_size, 0.0f,
			road_width, 0.5 * whole_size, 0.0f,
			-road_width, -whole_size, 0.0f,
			road_width, -whole_size, 0.0f };

		int size = sizeof(tmp_buffer) / sizeof(tmp_buffer[0]);
		//std::cout << "size is " << size << std::endl;
		g_road_buffer_data = (GLfloat *)malloc(sizeof(GLfloat) * (size));
		g_road_buffer_data = &tmp_buffer[0];
		size_r = size;
	}
	else{
		//do nothing
		fprintf(stderr, "Wrong road type\n");
	}
	if (!g_road_buffer_data){
		fprintf(stderr, "Wrong road type\n");
	}

	int size_b = 0;
	float side_dim_left = 0.0f;
	float rear_dim_left = 0.0f;
	if (drawMode == 1){
		int size = 4 * stories * 4 * 3;
		int index = 0;
		GLfloat tmp_buffer[1000] = { 0 };
		//4 blocks
		for (int m = 0; m < 2; m++){
			for (int n = 0; n < 2; n++){
				dis_side = 0.0f;
				dis_rear = 0.0f;
				side_dim_left = block_dim - stories * x_dim;
				rear_dim_left = block_dim - y_dim;
				for (int i = 0; i < stories; i++){
					float r_value = genRand(0.1f, 0.5f);
					setback_side = r_value * side_dim_left;
					dis_side += setback_side;
					r_value = genRand(0.2f, 0.8f);
					setback_rear = r_value * rear_dim_left;
					dis_rear = setback_rear;
					//first point
					tmp_buffer[index++] = -whole_size + (whole_size + road_width) * n + dis_side + x_dim * i;
					tmp_buffer[index++] = whole_size - (whole_size + road_width) * m - dis_rear;
					tmp_buffer[index++] = 0;
					//second point
					tmp_buffer[index++] = -whole_size + (whole_size + road_width) * n + dis_side + x_dim * (i + 1);
					tmp_buffer[index++] = whole_size - (whole_size + road_width) * m - dis_rear;
					tmp_buffer[index++] = 0;
					//third point
					tmp_buffer[index++] = -whole_size + (whole_size + road_width) * n + dis_side + x_dim * i;
					tmp_buffer[index++] = whole_size - (whole_size + road_width) * m - dis_rear - y_dim;
					tmp_buffer[index++] = 0;
					//fourth
					tmp_buffer[index++] = -whole_size + (whole_size + road_width) * n + dis_side + x_dim * (i + 1);
					tmp_buffer[index++] = whole_size - (whole_size + road_width) * m - dis_rear - y_dim;
					tmp_buffer[index++] = 0;		

					side_dim_left -= setback_side;
				}
			}
		}
		g_builds_buffer_data = (GLfloat *)malloc(sizeof(GLfloat)* (size));
		g_builds_buffer_data = &tmp_buffer[0];
		size_b = size;
	}
	else if (drawMode == 2){
		int size = 2 * stories * 4 * 3 + 2 * stories * 4 * 3;
		int index = 0;
		GLfloat tmp_buffer[1000] = { 0 };
		//2 small blocks
		for (int m = 0; m < 2; m++){
			for (int n = 0; n < 1; n++){
				dis_side = 0.0f;
				dis_rear = 0.0f;
				side_dim_left = block_dim - stories * x_dim;
				rear_dim_left = block_dim - y_dim;
				for (int i = 0; i < stories; i++){
					float r_value = genRand(0.1f, 0.5f);
					setback_side = r_value * side_dim_left;
					dis_side += setback_side;
					r_value = genRand(0.2f, 0.8f);
					setback_rear = r_value * rear_dim_left;
					dis_rear = setback_rear;
					//first point
					tmp_buffer[index++] = -whole_size + (whole_size + road_width) * n + dis_side + x_dim * i;
					tmp_buffer[index++] = whole_size - (whole_size + road_width) * m - dis_rear;
					tmp_buffer[index++] = 0;
					//second point
					tmp_buffer[index++] = -whole_size + (whole_size + road_width) * n + dis_side + x_dim * (i + 1);
					tmp_buffer[index++] = whole_size - (whole_size + road_width) * m - dis_rear;
					tmp_buffer[index++] = 0;
					//third point
					tmp_buffer[index++] = -whole_size + (whole_size + road_width) * n + dis_side + x_dim * i;
					tmp_buffer[index++] = whole_size - (whole_size + road_width) * m - dis_rear - y_dim;
					tmp_buffer[index++] = 0;
					//fourth
					tmp_buffer[index++] = -whole_size + (whole_size + road_width) * n + dis_side + x_dim * (i + 1);
					tmp_buffer[index++] = whole_size - (whole_size + road_width) * m - dis_rear - y_dim;
					tmp_buffer[index++] = 0;

					side_dim_left -= setback_side;
				}
			}
		}
		// add the big block
		block_dim = 2 * whole_size;
		dis_side = 0.0f;
		dis_rear = 0.0f;
		rear_dim_left = block_dim - 2 * stories * y_dim;
		side_dim_left = whole_size - road_width - x_dim;
		for (int i = 0; i < 2 * stories; i++){
			float r_value = genRand(0.1f, 0.5f);
			setback_rear = r_value * rear_dim_left;
			dis_rear += setback_rear;
			r_value = genRand(0.2f, 0.8f);
			setback_side = r_value * side_dim_left;
			dis_side = setback_side;
			//first point
			tmp_buffer[index++] = road_width + dis_side;
			tmp_buffer[index++] = whole_size - dis_rear - y_dim * i;
			tmp_buffer[index++] = 0;
			//second point
			tmp_buffer[index++] = road_width + dis_side + x_dim;
			tmp_buffer[index++] = whole_size - dis_rear - y_dim * i;
			tmp_buffer[index++] = 0;
			//third point
			tmp_buffer[index++] = road_width + dis_side;
			tmp_buffer[index++] = whole_size - dis_rear - y_dim * (i + 1);
			tmp_buffer[index++] = 0;
			//fourth
			tmp_buffer[index++] = road_width + dis_side + x_dim;
			tmp_buffer[index++] = whole_size - dis_rear - y_dim * (i + 1);
			tmp_buffer[index++] = 0;

			rear_dim_left -= setback_rear;
		}
		g_builds_buffer_data = (GLfloat *)malloc(sizeof(GLfloat) * (size));
		g_builds_buffer_data = &tmp_buffer[0];
		size_b = size;
	}
	else if (drawMode == 3){
		int size = 2 * stories * 4 * 3;
		int index = 0;
		GLfloat tmp_buffer[1000] = { 0 };
		dis_side = 0.0f;
		dis_rear = 0.0f;
		for (int n = 0; n < 2; n++){
			rear_dim_left = 2 * whole_size - stories * y_dim;
			side_dim_left = whole_size - road_width - x_dim;
			dis_side = 0.0f;
			dis_rear = 0.0f;
			for (int i = 0; i < stories; i++){
				float r_value = genRand(0.1f, 0.5f);
				setback_rear = r_value * rear_dim_left;
				dis_rear += setback_rear;
				r_value = genRand(0.2f, 0.8f);
				setback_side = r_value * side_dim_left;
				dis_side = setback_side;
				//first point
				tmp_buffer[index++] = -whole_size + (whole_size + road_width) * n + dis_side;
				tmp_buffer[index++] = whole_size - dis_rear - y_dim * i;
				tmp_buffer[index++] = 0;
				//second point
				tmp_buffer[index++] = -whole_size + (whole_size + road_width) * n + dis_side + x_dim;
				tmp_buffer[index++] = whole_size - dis_rear - y_dim * i;
				tmp_buffer[index++] = 0;
				//third point
				tmp_buffer[index++] = -whole_size + (whole_size + road_width) * n + dis_side;
				tmp_buffer[index++] = whole_size - dis_rear - y_dim * (i + 1);
				tmp_buffer[index++] = 0;
				//fourth
				tmp_buffer[index++] = -whole_size + (whole_size + road_width) * n + dis_side + x_dim;
				tmp_buffer[index++] = whole_size - dis_rear - y_dim * (i + 1);
				tmp_buffer[index++] = 0;

				rear_dim_left -= setback_rear;
			}
		}
	
		g_builds_buffer_data = (GLfloat *)malloc(sizeof(GLfloat) * (size));
		g_builds_buffer_data = &tmp_buffer[0];
		size_b = size;
	}
	else if (drawMode == 4){
		int size = 2 * stories * 4 * 3;
		int index = 0;
		GLfloat tmp_buffer[1000] = { 0 };
		dis_side = 0.0f;
		dis_rear = 0.0f;
		for (int n = 0; n < 2; n++){
			rear_dim_left = 1.5 * whole_size - stories * y_dim;
			side_dim_left = whole_size - road_width - x_dim;
			dis_side = 0.0f;
			dis_rear = 0.0f;
			for (int i = 0; i < stories; i++){
				float r_value = genRand(0.1f, 0.5f);
				setback_rear = r_value * rear_dim_left;
				dis_rear += setback_rear;
				r_value = genRand(0.2f, 0.8f);
				setback_side = r_value * side_dim_left;
				dis_side = setback_side;
				//first point
				tmp_buffer[index++] = -whole_size + (whole_size + road_width) * n + dis_side;
				tmp_buffer[index++] = 0.5 * whole_size - dis_rear - y_dim * i;
				tmp_buffer[index++] = 0;
				//second point
				tmp_buffer[index++] = -whole_size + (whole_size + road_width) * n + dis_side + x_dim;
				tmp_buffer[index++] = 0.5 * whole_size - dis_rear - y_dim * i;
				tmp_buffer[index++] = 0;
				//third point
				tmp_buffer[index++] = -whole_size + (whole_size + road_width) * n + dis_side;
				tmp_buffer[index++] = 0.5 * whole_size - dis_rear - y_dim * (i + 1);
				tmp_buffer[index++] = 0;
				//fourth
				tmp_buffer[index++] = -whole_size + (whole_size + road_width) * n + dis_side + x_dim;
				tmp_buffer[index++] = 0.5 * whole_size - dis_rear - y_dim * (i + 1);
				tmp_buffer[index++] = 0;

				rear_dim_left -= setback_rear;
			}
		}

		g_builds_buffer_data = (GLfloat *)malloc(sizeof(GLfloat) * (size));
		g_builds_buffer_data = &tmp_buffer[0];
		size_b = size;
	}
	else{
		fprintf(stderr, "Wrong road type\n");
	}
	if (!g_builds_buffer_data){
		fprintf(stderr, "Wrong road type\n");
	}

	int total_s = size_b + size_r;
	g_vertex_buffer_data = (GLfloat *)malloc(sizeof(GLfloat)* (total_s));
	int index = 0;
	memcpy(g_vertex_buffer_data, g_road_buffer_data, sizeof(GLfloat)* size_r);
	memcpy(g_vertex_buffer_data + size_r, g_builds_buffer_data, sizeof(GLfloat)* size_b);

	GLfloat g_color_buffer_data[1000] = { 0 };
	index = 0;
	for (int i = 0; i < 4; i++){
		g_color_buffer_data[index++] = 0.13f;
		g_color_buffer_data[index++] = 0.7f;
		g_color_buffer_data[index++] = 0.3f;
	}
	for (int i = 4; i < size_r / 3; i++){
		g_color_buffer_data[index++] = 0.82f;
		g_color_buffer_data[index++] = 0.78f;
		g_color_buffer_data[index++] = 0.235f;
	}
	for (int i = 0; i < size_b / 3; i++){
		g_color_buffer_data[index++] = 0.0f;
		g_color_buffer_data[index++] = 0.0f;
		g_color_buffer_data[index++] = 1.0f;
	}

	GLuint indices[1000] = { 0 };
	total_triangles = (size_r + size_b) / (3 * 2);
	int r_rects = size_r / (3 * 4);
	int b_rects = size_b / (3 * 4);
	index = 0;
	for (int i = 0; i < r_rects; i++){
		//1st triangle
		indices[index++] = i * 4;
		indices[index++] = i * 4 + 1;
		indices[index++] = i * 4 + 2;
		//2nd triangle
		indices[index++] = i * 4 + 1;
		indices[index++] = i * 4 + 2;
		indices[index++] = i * 4 + 3;
	}
	for (int i = r_rects; i < b_rects + r_rects; i++){
		//1st triangle
		indices[index++] = i * 4;
		indices[index++] = i * 4 + 1;
		indices[index++] = i * 4 + 2;
		//2nd triangle
		indices[index++] = i * 4 + 1;
		indices[index++] = i * 4 + 2;
		indices[index++] = i * 4 + 3;
	}

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* (total_s), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	// Create an Element Array Buffer that will store the indices array:
	glGenBuffers(1, &eab);

	// Transfer the data from indices to eab
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eab);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glUseProgram(shader);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);
	glDrawElements(GL_TRIANGLES, total_triangles * 3, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glUseProgram(0);
}

float GLWidget::genRand() {
	return rand() / (float(RAND_MAX) + 1);
}

float GLWidget::genRand(float a, float b) {
	return genRand() * (b - a) + a;
}

int GLWidget::genRand(int a, int b) {
	return (int)round((genRand() * (b - a))) + a;
}