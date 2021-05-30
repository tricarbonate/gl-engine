#include "../include/State.h"

template <> State * Singleton<State>::instance_ = 0;

bool State::terrainFlatShading_ = true;
bool State::perspective_ = true;
bool State::cursorDisabled_ = true;
bool State::fullScreenMode_ = false;
unsigned int State::nMaxModels = 10000;
unsigned int State::nMaxLights = 10000;

