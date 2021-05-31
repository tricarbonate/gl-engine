/* This file contains useful functions to the whole program */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>

#include "State.h"

int failed(std::string message);

float getDeltaTime(float &lastFrame);

void printStateReport(double deltaTime, int nFrame);

GLFWwindow* initializeWindow(const unsigned int windowHeight, const unsigned int windowWidth);

int initializeGlew(GLFWwindow *window);

int initializeGlfw();

// function that generates a random vec3 with values in between min and max
glm::vec3 randomVec3(double min, double max);

#endif // UTILS_HPP
