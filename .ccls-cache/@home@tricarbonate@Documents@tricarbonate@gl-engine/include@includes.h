/*
 * Contains defined values for file paths
 * */

#ifndef __INCLUDES_H__
#define __INCLUDES_H__

// texture locations
#define CONTAINER2_TEX_LOC "textures/container2.png" 
#define CONTAINER2_SPEC_LOC "textures/container2_specular.png"
#define GRASS_TEX_LOC "textures/grass.jpg"

// shader programs locations
#define SHADERPROGRAM_VERT_LOC "shaders/models/default-vert.glsl"
#define SHADERPROGRAM_FRAG_LOC "shaders/models/default-frag.glsl"
#define SCREEN_SHADER_VERT_LOC "shaders/models/framebuffer-vert.glsl"
#define SCREEN_SHADER_FRAG_LOC "shaders/models/framebuffer-frag.glsl"

// shader programs for lights
#define LIGHTINGSHADER_VERT_LOC "shaders/lights/light-vert.glsl"
#define LIGHTINGSHADER_FRAG_LOC "shaders/lights/light-frag.glsl"

// terrain shader programs
#define TERRAIN_FLATSHADER_VERT_LOC "shaders/terrain/flat-terrain-vert.glsl"
#define TERRAIN_FLATSHADER_FRAG_LOC "shaders/terrain/flat-terrain-frag.glsl"
#define TERRAIN_FLATSHADER_TESSC_LOC "shaders/terrain/flat-terrain-tessc.glsl"
#define TERRAIN_FLATSHADER_TESSE_LOC "shaders/terrain/flat-terrain-tesse.glsl"


#endif // __INCLUDES_H__
