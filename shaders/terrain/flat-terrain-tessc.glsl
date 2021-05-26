#version 400 core

layout(vertices = 6) out;

in vec3 fragColor;
flat in vec3 flatColor;

out vec3 fragColorE;
flat out vec3 flatColorE;

uniform float TessLevelInner;
uniform float TessLevelOuter;

void main()
{
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

    if ( gl_InvocationID == 0 )
    {
        gl_TessLevelInner[0] = TessLevelInner;
        gl_TessLevelOuter[0] = TessLevelOuter;
        gl_TessLevelOuter[1] = TessLevelOuter;
        gl_TessLevelOuter[2] = TessLevelOuter;
    }

    fragColorE = fragColor;
    flatColorE = flatColor;
}

