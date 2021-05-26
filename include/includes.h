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
#define SHADERPROGRAM_VERT_LOC "shaders/vertexShader.txt"
#define SHADERPROGRAM_FRAG_LOC "shaders/fragmentShader.txt"
#define LIGHTINGSHADER_VERT_LOC "shaders/lightVert.txt"
#define LIGHTINGSHADER_FRAG_LOC "shaders/lightFrag.txt"
#define CUBESHADER_VERT_LOC "shaders/cubeShaderVert.txt"
#define CUBESHADER_FRAG_LOC "shaders/cubeShaderFrag.txt"
#define INSTANCED_VERT_LOC "shaders/instancedVert.txt"
#define INSTANCED_FRAG_LOC "shaders/instancedFrag.txt"

// terrain shader programs
#define TERRAIN_FLATSHADER_VERT_LOC "shaders/terrainFlatShaderVert.txt"
#define TERRAIN_FLATSHADER_FRAG_LOC "shaders/terrainFlatShaderFrag.txt"
#define TERRAIN_FLATSHADER_TESSC_LOC "shaders/terrainFlatShaderTessC.txt"
#define TERRAIN_FLATSHADER_TESSE_LOC "shaders/terrainFlatShaderTessE.txt"


// bounding volumes shaders
#define AABB_BASESHADER_VERT_LOC "shaders/aabbBaseShaderVert.txt"
#define AABB_BASESHADER_FRAG_LOC "shaders/aabbBaseShaderFrag.txt"

#endif // __INCLUDES_H__
