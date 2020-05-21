//
// Created by zac.qi on 8/1/18.
//

#include <stdlib.h>
#include <stdio.h>
#include "shader.h"

const GLchar* ReadShader(const char *filename)
{
    FILE *infile = fopen(filename, "rb");
    if (!infile) {
        fprintf(stderr, "Unable to open file: %s\n" , filename);
        return NULL;
    }

    fseek(infile, 0, SEEK_END);
    int len = (int)ftell(infile);
    fseek(infile, 0, SEEK_SET);

    GLchar *source = (GLchar *)malloc(sizeof(GLchar) * (len + 1));

    fread(source, 1, len, infile);
    // printf("%s\n", source);
    fclose(infile);

    source[len] = 0;

    return source;
}

GLuint LoadShaders(ShaderInfo *shaders)
{
    if (shaders == NULL) {
        return 0;
    }

    GLuint program = glCreateProgram();

    ShaderInfo *entry = shaders;
    while (entry->type != GL_NONE) {
        GLuint shader = glCreateShader(entry->type);
        entry->shader = shader;

        const GLchar * source = ReadShader(entry->filename);
        if (source == NULL) {
            for (entry = shaders; entry->type != GL_NONE; ++entry) {
                glDeleteShader(entry->shader);
                entry->shader = 0;
            }

            return 0;
        }

        glShaderSource(shader, 1, &source, NULL);
        free((void *)source);

        glCompileShader(shader);

        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLsizei len;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

            GLchar *log = (GLchar *)malloc(len + 1);

            glGetShaderInfoLog(shader, len, &len, log);
            fprintf( stderr, "shader compilation failed:%s\n", log);
	    free(log);

            return 0;
        }

        glAttachShader(program, shader);
        ++ entry;
    }

    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLsizei len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

        GLchar *log =(GLchar *) malloc(len + 1);
        glGetProgramInfoLog(program, len, &len, log);
        fprintf(stderr, "Shader linking failed:%s\n",log);
        free(log);

        for (entry = shaders; entry->type != GL_NONE; ++ entry) {
            glDeleteShader(entry->shader);
            entry->shader = 0;
        }

        return 0;
    }

    return program;
}

void removeShader(GLuint program, ShaderInfo *shaders)
{
	ShaderInfo *entry = shaders;

	while (entry->type != GL_NONE) {
		if (glIsShader(entry->shader)) {
			glDeleteShader(entry->shader);
			entry->shader = 0;
		}
		entry++;
	}
	glUseProgram(0);
	if (glIsProgram(program))
		glDeleteProgram(program);
}

void GetVersionInfo()
{
    char *buf;
    buf = (char *)glGetString(GL_VENDOR);
    fprintf( stdout, "GPU Vendor: %s\n", buf);
    buf = (char *)glGetString(GL_VERSION);
    fprintf(stdout, "OpenGL Version: %s\n" ,buf);
    buf = (char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
    fprintf(stdout, "GLSL version:%s\n ", buf);
}
