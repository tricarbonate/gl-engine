#ifndef __ASSETS_H__
#define __ASSETS_H__

#include "Mesh.h"
#include "Texture.h"
#include "Singleton.h"
#include "DataStructures.h"
#include "includes.h"
#include "commonValues.hpp"
#include "DataFormat.h"

#include <unordered_map>
#include <string>


class ShaderProgram;

/* All publicly available game assets
 * like textures, materials, meshes and shader programs
 * can be created using Assets class
 *
 * More assets can added be created AT runtime
 *
 */
class Assets : public Singleton<Assets>
{
  public:
    static std::unordered_map<std::string, Texture> textures;
    static std::unordered_map<std::string, Material> materials;
    static std::unordered_map<std::string, Mesh> meshes;
    static std::unordered_map<std::string, ShaderProgram*> shaderPrograms;

    //Assets only create a ShaderSchema list that the shader manager uses
    static std::vector<ShaderSchema> shaders;

    static void defineAssets();

  private:
    Assets();
    ~Assets();
    Assets(const Assets&);
    Assets& operator=(const Assets&);
    friend class Singleton<Assets>;
};

#endif //__ASSETS_H__

