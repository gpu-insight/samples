#version 430 core

flat in uvec4 result;
out uvec4 out_color;
// layout(location=0, component=0) uint out_color;

void main()
{
    out_color = result;
    // out_color = 0x3f800000;
    // out_color = 0x00010000u;
    // out_color = uvec4(0x3fffffffu, 0u, 0u, 0u);
}

