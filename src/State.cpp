#include "../include/State.h"

template <> State * Singleton<State>::instance_ = 0;

bool State::terrainFlatShading_ = true;
bool State::perspective_ = true;
bool State::cursorDisabled_ = true;
bool State::fullScreenMode_ = false;

