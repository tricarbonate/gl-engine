#include "../include/State.h"

template <> State * Singleton<State>::instance_ = 0;

bool State::terrainFlatShading_ = true;
bool State::perspective_ = true;
bool State::cursorDisabled_ = true;
bool State::fullScreenMode_ = false;
unsigned int State::nMaxModels = 10000;
unsigned int State::nMaxLights = 10000;
bool State::picking_ = false;

float State::top_ = 1.0f;
float State::bottom_ = -1.0f;
float State::nearPlane_ = 1.0f;
float State::farPlane_ = 1000.0f;
float State::fov_ = 45.0f;
float State::tanFov_ = tan(0.5 * fov_);

float State::screenWidth_ = 1600;
float State::screenHeight_ = 1200;

bool State::useHDR_ = true;
bool State::useGammaCorrection_ = false;
