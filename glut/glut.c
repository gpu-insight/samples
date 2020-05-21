/* =================================================================
 * Copyright (c) 2020 Botson Corp 
 * 
 * This program is proprietary and confidential information of Botson.
 * And may not be used unless duly authorized. 
 * 
 * Revision: 
 * Date: 2020-04-16
 * Author: 
 * Descriptions: 
 * 
 */
// =================================================================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "GL/glut.h"
#include <GL/gl.h>

#include "shader.h"

#define WIDTH	480
#define HEIGHT	320

GLuint VAOs, Buffers;
GLuint program;
GLfloat red = 1.0;
GLfloat green = 1.0;
GLfloat blue = 1.0;

GLfloat x_off = 0.0;
GLfloat y_off = 0.0;
GLfloat z_off = 0.0;

GLuint start = 0;

ShaderInfo shaders[] = {
       {GL_VERTEX_SHADER, "triangles.vert"},
       {GL_FRAGMENT_SHADER,"triangles.frag"},
       {GL_NONE, NULL},
};
 
void init ()
{
	GLint r_location;
	GLint g_location;
	GLint b_location;

	GLint x_location;
	GLint y_location;
	GLint z_location;

	GLfloat vertices[] = {
             -0.90f, -0.90f,
              0.85f, -0.90f,
             -0.90f,  0.85f,
              0.90f, -0.85f,
              0.90f,  0.90f,
             -0.85f,  0.90f,
     	};

     	glGenVertexArrays(1, &VAOs);
     	glBindVertexArray(VAOs);

	glGenBuffers(1, &Buffers);
     	glBindBuffer(GL_ARRAY_BUFFER, Buffers);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

     	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
     	glEnableVertexAttribArray(0);

     	glClearColor(1.0, 1.0, 1.0, 0.0);

     	program = LoadShaders(shaders);
     	glUseProgram(program);
 
	r_location = glGetUniformLocation(program, "red");
	g_location = glGetUniformLocation(program, "green");
	b_location = glGetUniformLocation(program, "blue");
	glUniform1f(r_location, 1.0);
	glUniform1f(g_location, 0.0);
	glUniform1f(b_location, 1.0);

	x_location = glGetUniformLocation(program, "x_offset");
	y_location = glGetUniformLocation(program, "y_offset");
	z_location = glGetUniformLocation(program, "z_offset");
	glUniform1f(x_location, x_off);
	glUniform1f(y_location, y_off);
	glUniform1f(z_location, z_off);
}

void display_callback()
{
	//void *data = NULL;

//	data = malloc(WIDTH * HEIGHT * 4 );
	fprintf(stdout, "%s_%d\n", __func__, __LINE__);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
//	glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, data);
//	free(data);
//	fprintf(stdout, "%s_%d\n", __func__, __LINE__);
}

void idle_callback()
{
	//fprintf(stdout, "%s_%d\n", __func__, __LINE__);
	//display_callback();
}

void reshape_callback(int width, int height) 
{
	fprintf(stdout, "%s_%d\n", __func__, __LINE__);
	glViewport(0, 0, width, height);
}

#if 0
void position_callback(int x, int y)
{
	fprintf(stdout, "%s_%d\n", __func__, __LINE__);

}
#endif
void close_callback()
{
	fprintf(stdout, "%s_%d\n", __func__, __LINE__);
	removeShader(program, shaders);
	glDeleteBuffers(1, &Buffers);
     	glDeleteVertexArrays(1, &VAOs);
}

void keyboard_callback(unsigned char key, int x, int y)
{
	fprintf(stdout, "%s_%d\n", __func__, __LINE__);
	fprintf(stdout, "key:%c\n", key);
	switch(key) {
		case 'b':
		case 'B':
			{
				GLint b_location;

				b_location = glGetUniformLocation(program, "blue");
				if (blue > 0) {
					blue -= 0.1;
				}
				fprintf(stdout, "blue:%f\n", blue);
				glUniform1f(b_location, blue);
				glutPostRedisplay();
			}
			break;
		case 'c':
		case 'C':
			start = (start + 3)%6;
			glClear(GL_COLOR_BUFFER_BIT);
			glBindVertexArray(VAOs);
			glDrawArrays(GL_TRIANGLES, start, 3);
			glutSwapBuffers();
			break;
		case 'g':
		case 'G':
			{
				GLint g_location;

				g_location = glGetUniformLocation(program, "green");
				if (green > 0) {
					green -= 0.1;
				}
				fprintf(stdout, "green:%f\n", green);
				glUniform1f(g_location, green);
				glutPostRedisplay();
			}
			break;
		case 'r':
		case 'R':
			{
				GLint r_location;

				r_location = glGetUniformLocation(program, "red");
				if (red > 0) {
					red -= 0.1;
				}
				fprintf(stdout, "red:%f\n", red);
				glUniform1f(r_location, red);
				glutPostRedisplay();
			}
			break;
		default:
			break;
	}
}

void keyboard_up_callback(unsigned char key, int x, int y)
{
	fprintf(stdout, "%s_%d\n", __func__, __LINE__);

}

#if 0
void motion_callback(int x, int y)
{
	fprintf(stdout, "%s_%d\n", __func__, __LINE__);

}
#endif
void mouse_callback(int button, int state, int x, int y)
{
	fprintf(stdout, "%s_%d\n", __func__, __LINE__);
	switch(button) {
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_UP) {
				GLint x_location;

				x_location = glGetUniformLocation(program, "x_offset");
				x_off += 0.1;
				glUniform1f(x_location, x_off);
//				display_callback();
				glutPostRedisplay();
				fprintf(stdout, "x_off:%f\n", x_off);
			}
			
			break;
		case GLUT_MIDDLE_BUTTON:
			fprintf(stdout, "%s_%d\n", __func__, __LINE__);
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_UP) {
				GLint y_location;

				y_location = glGetUniformLocation(program, "y_offset");
				y_off += 0.2;
				glUniform1f(y_location, y_off);
				glutPostRedisplay();
				fprintf(stdout, "y_off:%f\n", y_off);
			
			}
			break;
	}
}
#if 0
void mouse_wheel_callback(int buttion, int state, int x, int y)
{
	fprintf(stdout, "%s_%d\n", __func__, __LINE__);

}
#endif
void entry_callback(int state) 
{
	fprintf(stdout, "%s_%d\n", __func__, __LINE__);
}

void visibility_callback(int state)
{
	fprintf(stdout, "%s_%d\n", __func__, __LINE__);
}

int main(int argc, char **argv)
{
	int win1, win2;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);

	win1 = glutCreateWindow("test");
#if 10
	glutIdleFunc(idle_callback);
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
//	glutPositionFunc(position_callback);
	glutCloseFunc(close_callback);
	glutKeyboardFunc(keyboard_callback);
	glutKeyboardUpFunc(keyboard_up_callback);
//	glutMotionFunc(motion_callback);
	glutMouseFunc(mouse_callback);
//	glutMouseWheelFunc(mouse_wheel_callback);
	glutEntryFunc(entry_callback);
	glutVisibilityFunc(visibility_callback);
#endif
	init();
	glutMainLoop();

	fprintf(stdout, "%s_%d\n", __func__, __LINE__);
	return 0;
}
