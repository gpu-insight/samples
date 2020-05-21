//
// Created by zac.qi on 8/1/18.
//

#ifndef REDBOOK_LOADSHADERS_H
#define REDBOOK_LOADSHADERS_H

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>


typedef struct ShaderInfo {
       GLenum type;
        const char *filename;
        GLuint shader;
} ShaderInfo;

GLuint LoadShaders(ShaderInfo *shaders);

const GLchar *ReadShader(const char *filename);

void GetVersionInfo(void);

#endif //REDBOOK_LOADSHADERS_H
