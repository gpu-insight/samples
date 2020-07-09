#version 430 core

flat in uint result;
out uint out_color;

void main()
{
    out_color = result;
}

