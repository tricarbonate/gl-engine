#ifndef __STATE_H__
#define __STATE_H__

#include "Singleton.h"
#include "glm/common.hpp" 

class State : 
  public Singleton<State>
{
  public:
  
    // State variables
    //
    static bool terrainFlatShading_;
    static bool perspective_; 
    static bool cursorDisabled_;
    static bool fullScreenMode_;
    static unsigned int nMaxModels;
    static unsigned int nMaxLights;
    static bool picking_;

    // Camera Settings
    static float top_;
    static float bottom_;
    static float nearPlane_;
    static float farPlane_;
    static float tanFov_;
    static float fov_;

    // Screen/Window information
    static float screenWidth_;
    static float screenHeight_;

  private:
    State();
    ~State();
    State(const State&);
    State& operator=(const State&);
    friend class Singleton<State>;
};


#endif //__STATE_H__
