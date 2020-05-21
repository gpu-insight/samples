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
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <unistd.h>
#include "loadShaders.h"

#if 0
enum VAO_IDS {Triangles, NumVAOs};
enum Buffer_IDs {ArrayBuffer, NumBuffers};
enum Attrib_IDs {vPosition = 0};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 6;

void init ()
{
	static const GLfloat vertices[NumVertexs][2] = {
		{ -0.9, -0.9 },
		{ 0.85, -0.9 },
		{ -0.9, 0.85 },
		{ 0.9, -0.85 },
		{ 0.9, 0.9 },
		{ -0.85, 0.9 },
	};
	glCreatreBuffers(NumBuffers, Buffers);
	glNameBufferStorages(Buffers[ArrayBuffer], sizeof(Vertices), vertices, 0 );

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "triangles.vert"},
		{GL_FRAGMENT_SHADER, "triangles.frag"},
		{GL_NONE, NULL}
	};

	GLuint program = 
}

const float vertices[] = {
    -0.4f, -0.4f, 0.0f, 1.0,
    -0.4f,  0.0f, 0.0f, 1.0,
    -0.4f,  0.4f, 0.0f, 1.0,
     0.0f, -0.4f, 0.0f, 1.0,
     0.0f,  0.0f, 0.0f, 1.0,
     0.0f,  0.4f, 0.0f, 1.0,
     0.4f, -0.4f, 0.0f, 1.0,
     0.4f,  0.0f, 0.0f, 1.0,
     0.4f,  0.4f, 0.0f, 1.0,
};


GLfloat color[] = {
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0
};

#endif

GLuint VAOs, Buffers;





void init ()
{
 
#if 0
    char *vertShader ={	"#version 430 core\n"
			"layout(location = 0) in vec4 vPosition;\n"
			"void main()\n"
			"{\n"
			"gl_Position = vPosition;\n"
			"}\n"
			};

    char *fragShader = {"#version 430 core\n"
			"out vec4 fColor;\n"
                        "void main()\n"
                        "{\n"
			"fColor = vec4(1.0, 0.0, 1.0, 1.0);\n"
                        "}\n"};
#endif
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

     ShaderInfo shaders[] = {
             {GL_VERTEX_SHADER, "triangles.vert"},
             {GL_FRAGMENT_SHADER,"triangles.frag"},
             {GL_NONE, NULL},
     };
 
     GLuint program = LoadShaders(shaders);
     glUseProgram(program);
 
     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
     glEnableVertexAttribArray(0);


#if 0
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(color), NULL, GL_DYNAMIC_DRAW);
//     	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  //   	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(color), color);

     	glEnableVertexAttribArray(0);
     	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
     	glEnableVertexAttribArray(1);
     	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, sizeof(vertices));
     	glClearColor(1.0, 1.0, 1.0, 1.0);
     	glViewport(0, 0, 480, 320);
 #endif
 
}

#if 10
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(VAOs);
	glDrawArrays(GL_TRIANGLES, 0, 3);
#if 0
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(-0.8, -0.6, 0);
		glColor3f(0, 0.9, 0);
		glVertex3f(0.8, -0.6, 0);
		glColor3f(0, 0, 1.0);
		glVertex3f(0, 0.6, 0);
	glEnd();
#endif
	glFlush();
}
#endif
int main()
{
	Display *dpy;
	Window win, root;
	XSetWindowAttributes attr;
	XVisualInfo *visinfo;
	XEvent event;
	int scrnum;
	int attrib_rgba[] = { 	GLX_RENDER_TYPE, GLX_RGBA_BIT,
			      	//GLX_RED_SIZE, 1,
		  	      	//GLX_GREEN_SIZE, 1,
			     	//GLX_BLUE_SIZE, 1,
			    	GLX_DOUBLEBUFFER, True,
			  	//GLX_DEPTH_SIZE, 1,
			  	None};
	int attrib_index[] = { 	GLX_RENDER_TYPE, GLX_COLOR_INDEX_BIT,
			      	GLX_RED_SIZE, 1,
		  	      	GLX_GREEN_SIZE, 1,
			     	GLX_BLUE_SIZE, 1,
			    	GLX_DOUBLEBUFFER, True,
			  	GLX_DEPTH_SIZE, 1,
			  	None};
	GLXContext ctx = NULL, ctx_share = NULL;
	GLXFBConfig *configs;
	
	int nconfigs = 0;
	unsigned long mask;
	Bool open_display = False;
	Bool create_context = False;
	Bool create_share_context = False;
	Bool choose_configs = False;
	Bool choose_visual = False;
	Bool draw_frame = False;

	dpy = XOpenDisplay(NULL);
	if(!dpy) {
		fprintf(stderr, "Error:couldn't open display!'n");
		return -1;
	}
	open_display = True;
	scrnum = DefaultScreen(dpy);

	configs = glXChooseFBConfig(dpy, scrnum, attrib_rgba, &nconfigs);
//	configs = glXChooseFBConfig(dpy, scrnum, attrib_index, &nconfigs);
	if (configs == NULL) {
		fprintf(stderr, "Error: glXChooseFBConfig fail\n");
		goto finish;
	}
	choose_configs = True;
//	ctx_share = glXCreateNewContext(dpy, configs[0], GLX_RGBA_TYPE, NULL, True );
//	if (ctx_share == NULL) {
//		goto finish;
//	}
//	create_share_context = True;
	ctx = glXCreateNewContext(dpy, configs[0], GLX_RGBA_TYPE, NULL, True );
//	ctx = glXCreateNewContext(dpy, configs[0], GLX_RGBA_TYPE, ctx_share, True );
#if 10
//	ctx = glXCreateNewContext(NULL, configs[0], GLX_RGBA_TYPE, NULL, True );
//	ctx = glXCreateNewContext(dpy, NULL, GLX_RGBA_TYPE, NULL, True );
//	ctx = glXCreateNewContext(dpy, configs[0], GLX_RGBA_TYPE, NULL, False);
//	ctx = glXCreateNewContext(dpy, configs[0], GLX_COLOR_INDEX_TYPE, NULL, True );
#endif
	if (ctx == NULL) {
		fprintf(stderr, "create context fail!\n");
		goto finish;
	}
	create_context = True;


	//create window
	visinfo = glXChooseVisual(dpy, scrnum, attrib_rgba);
	if (visinfo == NULL) {
		fprintf(stderr, "Error:cloudn't get an visual!\n");
		goto finish;
	}
	choose_visual = True;

	root = RootWindow(dpy, scrnum);

	attr.background_pixel = 0;
	attr.border_pixel = 0;
	attr.colormap = XCreateColormap(dpy, root, visinfo->visual, AllocNone);
	attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask;
	mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect;
	win = XCreateWindow( dpy, root, 100, 100, 480, 320, 0, visinfo->depth, InputOutput, visinfo->visual, mask, &attr );

	XMapWindow(dpy, win);
//	XSetWMColormapWindows(dpy, win, &win, 1);
	glXMakeCurrent(dpy, win, ctx);
	init();
	while (1) {
		XNextEvent(dpy, &event);
		switch(event.type) {
			case Expose:
				draw();
				glXSwapBuffers(dpy,win);
				draw_frame = True;
				break;
			default:
				break;
		}
	//	if (draw_frame)
	//		break;
	}

	sleep(10);
	XDestroyWindow(dpy, win);
	
finish:
	if (choose_visual) {
		XFree(visinfo);
	}
	if (create_context) {
		glXDestroyContext(dpy, ctx);
	} 
	if (create_share_context) {
		glXDestroyContext(dpy, ctx_share);
	}
	if (choose_configs) {
		XFree(configs);
	}
	if (open_display) {
		XCloseDisplay(dpy);
	}
	return 0;
}
