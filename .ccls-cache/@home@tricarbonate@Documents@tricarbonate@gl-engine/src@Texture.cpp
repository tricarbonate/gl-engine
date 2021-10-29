#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "../include/Texture.h" 

Texture::Texture(const char* textureLoc, GLint internalFormat):
  textureId_(0),
  textureLocation_(textureLoc),
  internalFormat_(internalFormat)
{
  loadTexture();
}

Texture::Texture():
  textureId_(0),
  textureLocation_(""),
  internalFormat_(GL_RGBA)
{}

Texture::Texture(const Texture& texture):
  textureId_(texture.textureId_),
  textureLocation_(texture.textureLocation_),
  internalFormat_(texture.internalFormat_)
{
  loadTexture();
}

int Texture::loadTexture(){

  int width, height, nrChannels;
  unsigned char *data = stbi_load(textureLocation_, &width, &height, &nrChannels, 0);

  if (data)
  {
    glGenTextures(1, &textureId_);
    glBindTexture(GL_TEXTURE_2D, textureId_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat_,
        width, height, 0, internalFormat_, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture at " << textureLocation_ << std::endl;
    return -1;
  }
  stbi_image_free(data);
  return 0;
}

void Texture::bind(){
  glBindTexture(GL_TEXTURE_2D, textureId_);
}

Texture& Texture::operator=(const Texture& texture){
  if(this != &texture){
    textureId_ = texture.textureId_;
    textureLocation_ = texture.textureLocation_;
    internalFormat_ = texture.internalFormat_;
  }
  return *this;
}
