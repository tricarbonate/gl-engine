/*
 * Contains all necessary include for main
 * */

#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <cstring> //for strlen();
#include <map>
#include <fstream>

#include "Light.h"
#include "Texture.h"
#include "Mesh.h"
#include "Camera.h"
#include "utils.hpp"
#include "commonValues.hpp"
//#include "Scene.h"
#include "Model.h"
#include "Block.h"
#include "Terrain.h"
#include "State.h"
#include "EventHandler.h"
#include "ShaderManager.h"
#include "Mirror.h"

// texture locations
#define CONTAINER2_TEX_LOC "textures/container2.png" 
#define CONTAINER2_SPEC_LOC "textures/container2_specular.png"
#define GRASS_TEX_LOC "textures/grass.jpg"

// shader programs locations
#define SHADERPROGRAM_VERT_LOC "shaders/models/default-vert.glsl"
#define SHADERPROGRAM_FRAG_LOC "shaders/models/default-frag.glsl"

// shader programs for lights
#define LIGHTINGSHADER_VERT_LOC "shaders/lights/light-vert.glsl"
#define LIGHTINGSHADER_FRAG_LOC "shaders/lights/light-frag.glsl"

// terrain shader programs
#define TERRAIN_FLATSHADER_VERT_LOC "shaders/terrain/flat-terrain-vert.glsl"
#define TERRAIN_FLATSHADER_FRAG_LOC "shaders/terrain/flat-terrain-frag.glsl"
#define TERRAIN_FLATSHADER_TESSC_LOC "shaders/terrain/flat-terrain-tessc.glsl"
#define TERRAIN_FLATSHADER_TESSE_LOC "shaders/terrain/flat-terrain-tesse.glsl"

#endif // __INCLUDES_H__
