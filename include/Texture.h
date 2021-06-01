#ifndef __TEXTURE_H__
#define __TEXTURE_H__ 

#include <GL/glew.h>

#include <iostream>

#include "State.h"

class Texture{
  public:
    Texture(const char* textureLoc, GLint internalFormat = GL_RGBA);
    Texture();

    // copy construtor
    Texture(const Texture& texture);

    void bind();

    unsigned int getId() { return textureId_; }

    Texture& operator=(const Texture& texture);

  private:
    unsigned int textureId_;
    const char* textureLocation_;
    GLint internalFormat_;

    int loadTexture();
};

#endif // __TEXTURE_H__
