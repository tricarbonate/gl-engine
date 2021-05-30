#ifndef __STATE_H__
#define __STATE_H__

#include "Singleton.h"

class State : 
  public Singleton<State>
{
  public:
  
    // State variables
    //
    static bool terrainFlatShading_;
    static bool perspective_; 
    static bool fov_; 
    static bool cursorDisabled_;
    static bool fullScreenMode_;
    static unsigned int nMaxModels;
    static unsigned int nMaxLights;

  private:
    State();
    ~State();
    State(const State&);
    State& operator=(const State&);
    friend class Singleton<State>;
};


#endif //__STATE_H__
