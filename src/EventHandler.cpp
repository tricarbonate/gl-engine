#include "../include/EventHandler.h"

EventHandler::EventHandler(GLFWwindow* window, Camera* camera):
    window_(window),
    camera_(camera),
    releasedJump_(true)
{

}

EventHandler::~EventHandler(){

}

void EventHandler::handleEvents(float deltaTime){
    handleKeys(deltaTime);
    handleMouse();
}


void EventHandler::handleKeys(float deltaTime){
    // Camera movement
    if(pressed(GLFW_KEY_W)){
        camera_->goForward(deltaTime);
    }
    if(pressed(GLFW_KEY_S)){
        camera_->goBackward(deltaTime);
    }
    if(pressed(GLFW_KEY_A)){
        camera_->goLeft(deltaTime);
    }
    if(pressed(GLFW_KEY_D)){
        camera_->goRight(deltaTime);
    }
    if(pressed(GLFW_KEY_Q) && releasedJump_){
        std::cout << "SPACE" << std::endl;
        releasedJump_ = false;
        camera_->jump();
    }
    if(!pressed(GLFW_KEY_Q)){
        releasedJump_ = true;
    }
    if(pressed(GLFW_KEY_LEFT_SHIFT)){
        camera_->goDownward(deltaTime);
    }

    // State changes
    glfwSetKeyCallback(window_, key_callback);
    glfwSetMouseButtonCallback(window_, mouse_button_callback);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){

    //if(key == GLFW_KEE_Q && action == GLFW_PRESS){
        //camera_->goUpward();
    //}
    if(key == GLFW_KEY_M && action == GLFW_PRESS){
        State::terrainFlatShading_ = !State::terrainFlatShading_;
    }

    if(key == GLFW_KEY_F && action == GLFW_PRESS){
        State::fullScreenMode_ = !State::fullScreenMode_;
    }

    if(key == GLFW_KEY_G && action == GLFW_PRESS){
        State::useGammaCorrection_ = !State::useGammaCorrection_;
    }

    if(key == GLFW_KEY_P && action == GLFW_PRESS){
        State::postProcessingEffect_ = static_cast<Effect>(static_cast<int>(State::postProcessingEffect_) + 1);
        if(static_cast<int>(State::postProcessingEffect_) == 5){

            State::postProcessingEffect_ = static_cast<Effect>(static_cast<int>(0));
        }
    }

    if(key == GLFW_KEY_C && action == GLFW_PRESS){
        if(State::cursorDisabled_){
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPos(window, State::screenWidth_ / 2, State::screenHeight_ / 2);
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPos(window, State::screenWidth_ / 2, State::screenHeight_ / 2);
        }
        State::cursorDisabled_ = !State::cursorDisabled_;
    }
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        State::picking_ = !State::picking_;
    }
}


void EventHandler::handleMouse(){
    if(State::cursorDisabled_){
        GLdouble xpos, ypos;
        glfwGetCursorPos(window_, &xpos, &ypos);
        camera_->updateOrientation(xpos, ypos);
    } else {
        camera_->setFirstMouse(true);
    }
}

bool EventHandler::pressed(int key){
    return glfwGetKey(window_, key) == GLFW_PRESS;
}


