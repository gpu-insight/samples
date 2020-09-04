#version 430 core

uniform usampler2DArray sampler;
flat out uvec4 result;

void main()
{
    uint temp = texture(sampler, vec3(0, 0, 0)).r;
    
    uint red = 0x3fffffffu;

    if (0xffff == temp)
    { 
        result = uvec4(red, 0u, 0u, 0u);
    }
    else
    {
        result = uvec4(0, red, 0u, 0u);
    }

    // uint red = (temp.r << 24) + (temp.g << 16) + (temp.b << 8) + (temp.a << 0);

    switch (gl_VertexID)
    {
    case 0: gl_Position = vec4(-1.0, 1.0, 0.0, 1.0); break;
    case 1: gl_Position = vec4( 1.0, 1.0, 0.0, 1.0); break;
    case 2: gl_Position = vec4(-1.0,-1.0, 0.0, 1.0); break;
    case 3: gl_Position = vec4( 1.0,-1.0, 0.0, 1.0); break;
    }
}

