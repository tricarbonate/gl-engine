/* This file contains useful functions to the whole program */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"

int failed(std::string message);

float getDeltaTime(float &lastFrame);

void printMSperFrame(double deltaTime);

GLFWwindow* initializeWindow(const unsigned int windowHeight, const unsigned int windowWidth);

int initializeGlew(GLFWwindow *window);

int initializeGlfw();

#endif // UTILS_HPP
