#ifndef __STATE_H__
#define __STATE_H__

#include "Singleton.h"
#include "glm/common.hpp" 

enum Effect {
  NO_EFFECT = 0,
  HDR = 1,
  COLOR_INVERSION = 2,
  GRAY_SCALE = 3,
  KERNEL_EFFECT = 4
};

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

    // OpenGL render options
    static bool useHDR_;
    static bool useGammaCorrection_;
    static Effect postProcessingEffect_;

  private:
    State();
    ~State();
    State(const State&);
    State& operator=(const State&);
    friend class Singleton<State>;
};


#endif //__STATE_H__
