
#include "assimp_model.hpp"



//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>
/// Build a quaternion from euler angles (pitch, yaw, roll), in radians.
 //GLM_FUNC_DECL GLM_EXPLICIT tquat(tvec3<T, P> const & eulerAngles);
  ai_Transformz::ai_Transformz():
  pos{glm::vec3(0.f,0.f,0.f)},
  q_rotation{glm::quat(0.f,0.f,0.f,1.f)},
  scale{glm::vec3(1.f,1.f,1.f)}
  {}

  ai_Transformz::ai_Transformz(const glm::vec3& in_pos, const glm::quat rot, const glm::vec3& in_scale):
  pos{in_pos},
  q_rotation{rot},
  scale{in_scale}
  {}

  ai_Transformz ai_Transformz::operator * (const ai_Transformz& rhs) const
  {

    return ai_Transformz(
    glm::vec3(pos+(glm::vec3(q_rotation*rhs.pos)*scale)),
    q_rotation*rhs.q_rotation,
    glm::vec3(scale*rhs.scale));
  }

ai_Transformz   ai_Transformz::inverse() const
  {
    glm::quat inrot ;//= ;
    return ai_Transformz({-pos,glm::inverse(q_rotation),glm::vec3(1.f/scale.x,1.f/scale.y,1.f/scale.z)});
  }

  glm::mat4 ai_Transformz::get_martix_from_tranform() const
  {
    glm::mat4 m;

    m[0][0]=scale.x*(1.f-2.f*q_rotation.y*q_rotation.y-2.f*q_rotation.z*q_rotation.z);
    m[0][1]=scale.y*(2.f * q_rotation.x * q_rotation.y - 2.f * q_rotation.z * q_rotation.w);
    m[0][2]=scale.z*(2.f * q_rotation.x * q_rotation.z + 2.f * q_rotation.y * q_rotation.w);
    m[0][3]=pos.x;

    m[1][0]=scale.x*(2.f * q_rotation.x * q_rotation.y + 2.f * q_rotation.z * q_rotation.w);
    m[1][1]=scale.y*(1.f - 2.f * q_rotation.x * q_rotation.x - 2.f * q_rotation.z * q_rotation.z);
    m[1][2]=scale.z*(2.f * q_rotation.y * q_rotation.z - 2.f * q_rotation.x * q_rotation.w);
    m[1][3]=pos.y;

    m[2][0]=scale.x*(2.f * q_rotation.x * q_rotation.z - 2.f * q_rotation.y * q_rotation.w);
    m[2][1]=scale.y*(2.f * q_rotation.y * q_rotation.z + 2.f * q_rotation.x * q_rotation.w);
    m[2][2]=scale.z*(1.f - 2.f * q_rotation.x * q_rotation.x - 2.f * q_rotation.y * q_rotation.y);
    m[2][3]=pos.z;

    m[3][0]=0.f;
    m[3][1]=0.f;
    m[3][2]=0.f;
    m[3][3]=0.f;
    return m;
  }

  ai_Transformz ai_Transformz::lerp (const ai_Transformz& t1, const ai_Transformz t2, float ratio)
  {
    return ai_Transformz(
      t1.pos*(1.f-ratio)+t2.pos*ratio,
      glm::quat(
        t1.q_rotation.w*(1.f-ratio)+t2.q_rotation.w*ratio,
        t1.q_rotation.x*(1.f-ratio)+t2.q_rotation.x*ratio,
        t1.q_rotation.y*(1.f-ratio)+t2.q_rotation.y*ratio,
        t1.q_rotation.z*(1.f-ratio)+t2.q_rotation.z*ratio
      ),t1.scale*(1.f-ratio)+t2.scale*ratio);
  }

ai_Transformz   ai_Transformz::get_tranz_from_martix(const glm::mat4& m)
  {
    float sx  = glm::length(glm::vec3(m[0][0],m[1][0],m[2][0]));
    float sy  = glm::length(glm::vec3(m[0][1],m[1][1],m[2][1]));
    float sz  = glm::length(glm::vec3(m[0][2],m[1][2],m[2][2]));

    glm::vec3 out_pos = glm::vec3(m[0][3],m[1][3],m[2][3]);
    glm::quat out_rot = glm::quat_cast(m);
    glm::vec3 out_scale = glm::vec3(sx,sy,sz);

    return ai_Transformz(out_pos,out_rot,out_scale);
  }

  //std::shared_ptr<ai_model> ai_model::load_from_file(const pathz& in_path, const ai_Transformz& in_tranz)


//  std::vector<ai_Texture> ai_model::ai_loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)


std::vector<ai_texture> ai_model::ai_loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, const pathz& in_path)
  {
      std::vector<ai_texture> textures;
      for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
      {
          aiString str;
          mat->GetTexture(type, i, &str);
          // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
          bool skip = false;
          for(unsigned int j = 0; j < textures_loaded.size(); j++)
          {
              if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
              {
                  textures.push_back(textures_loaded[j]);
                  skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                  break;
              }
          }
          if(!skip)
          {   // if texture hasn't been loaded already, load it
              ai_texture texture;
              const char* tex_path = str.C_Str();

              #ifdef DEBUG_01
              std::cout << "texturePath from mtl:...<<::" << tex_path <<'\n';
              #endif
            //  const std::string text_str_path= in_path.drectory_path+ tex_path;
              //const char* text_dr_path =

              #ifdef DEBUG_01
            //  std::cout << "texturePath from mtl:...<<" << text_str_path <<'\n';
              #endif
            //  const char* drectory= ;
              texture.id = ai_texture::ai_TextureFromFile(tex_path,in_path.drectory_path);
              texture.type = typeName;
              texture.path = str.C_Str();
              textures.push_back(texture);
              textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
          }
      }
      return textures;
  }

/*
assimp_model(const std::vector<assimp_mesh> am_meshez, const Transform& tranz);

  static std::shared_ptr<assimp_model> ai_Transformz::load_from_file(const pathz& in_path);

assimp_model(const assimp_model&)

load_from_file()
{
}
*/
