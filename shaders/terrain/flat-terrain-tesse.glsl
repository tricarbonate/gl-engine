#version 400 core

layout(isolines) in;

in vec3 fragColorE;
flat in vec3 flatColorE;

out vec3 fragColor;
flat out vec3 flatColor;

void main()
{
    float t = gl_TessCoord.x;
    // absolument pas efficace d'utiliser pow(), mais ça permet de bien voir les coefficients et les Nij(t)
    gl_Position = (  1. * pow((1.-t),5) * pow(t,0) * gl_in[0].gl_Position +
                     5. * pow((1.-t),4) * pow(t,1) * gl_in[1].gl_Position +
                     10. * pow((1.-t),3) * pow(t,2) * gl_in[2].gl_Position +
                     10. * pow((1.-t),2) * pow(t,3) * gl_in[3].gl_Position +
                     5. * pow((1.-t),1) * pow(t,4) * gl_in[4].gl_Position +
                     1. * pow((1.-t),0) * pow(t,5) * gl_in[5].gl_Position );

    fragColor = fragColorE;
    flatColor = flatColorE;
}

