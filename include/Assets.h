#ifndef __ASSETS_H__
#define __ASSETS_H__

#include "Mesh.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Singleton.h"

#include <unordered_map>
#include <string>

#define N_TEX_MAX 100
#define N_MAT_MAX 100
#define N_MESH_MAX 100 

/* All publicly available game assets
 * like textures, materials, meshes and shader programs
 * More can then be created AT runtime
 *
 */
class Assets : public Singleton<Assets>
{
  public:
    static inline std::unordered_map<std::string, Texture> textures;
    static inline std::unordered_map<std::string, Material> materials;
    static inline std::unordered_map<std::string, Mesh> meshes;

  private:
    Assets();
    ~Assets();
    Assets(const Assets&);
    Assets& operator=(const Assets&);
    friend class Singleton<Assets>;
};

#endif //__ASSETS_H__

