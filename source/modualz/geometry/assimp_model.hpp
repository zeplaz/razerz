

#include "geometry.hpp"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/material.h>
#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

struct ai_Material
	{
		ai_Material(const glm::vec4& in_specular, const glm::vec4& in_diffuse, const glm::vec4& in_ambient, float in_shinz)
			: specular(in_specular), diffuse(in_diffuse), ambient(in_ambient), shininess{in_shinz}
		{}
		glm::vec4 specular;
		glm::vec4 diffuse;
		glm::vec4 ambient;
    float shininess;
	};

struct ai_drectional_light
{
     glm::vec3 direction;
     ai_Material light_colourz;
     ai_drectional_light(const glm::vec3& in_direction, const ai_Material& in_light_colourz)
			: direction(in_direction), light_colourz(in_light_colourz)
      {}
};

struct ai_vertex{
  glm::vec3 pos;
  float __one;
  glm::vec3 normal;
  float __zero;
  float U;
  float V;
  ai_vertex(const glm::vec3& in_pos, const glm::vec3& in_norm,float u, float v) :
  pos{in_pos},__one(1.f),normal{in_norm},__zero{0.f}, U{u},V{v}
  {}
};

struct ai_Transformz
{
  glm::vec3 pos;
  glm::vec3 scale;
  glm::quat q_rotation;
  const static ai_Transformz identity;


  ai_Transformz();
  ai_Transformz(const glm::vec3& in_pos, const glm::quat rot, const glm::vec3& scale);
  ai_Transformz(const ai_Transformz&)= default;

  ai_Transformz operator *(const ai_Transformz& rhs) const;

  ai_Transformz inverse() const;

  static ai_Transformz get_tranz_from_martix(const glm::mat4& m);

  glm::mat4 get_martix_from_tranform() const;

  ai_Transformz lerp(const ai_Transformz& t1, const ai_Transformz t2, float ratio);

  inline void set_rotatio_via_martix(glm::mat4 in_matrix)
  {
      q_rotation= glm::quat_cast(in_matrix);
  }
  inline glm::mat4 get_matrix_rotation()
  {
    return  glm::mat4_cast(q_rotation);
  }

};

class ai_render_call
{
  public :

  ai_render_call (const std::vector<ai_vertex>& vertices, const std::vector<std::uint32_t>& indices)
  {
    	NumberOfIndices = (uint32_t)indices.size();
  }
  std::uint32_t NumberOfIndices;

};
class ai_model{
  public :
  struct ai_mesh{
    ai_render_call render_call;
    ai_Material material;
    ai_mesh(ai_render_call in_rc,ai_Material in_mat)
    :render_call{in_rc},material{in_mat}
    {}
    };

protected :
      std::vector<ai_mesh> meshez;
      ai_Transformz tranzform;
      GLuint*	textureIds = nullptr;
      render_state_cache render_cache;
public :

      ai_model(const std::vector<ai_mesh>& in_meshz, const ai_Transformz& tranz);

      static std::shared_ptr<ai_model> load_from_file(const pathz& in_path, const ai_Transformz& tranz);
      bool update(float dt);
      bool draw(shader_seprate*shader,glm::mat4& view,glm::mat4& proj);
      ai_model(const ai_model&) = delete;

      inline void draw_via_cache()
      {
        draw(render_cache.shader,render_cache.view,render_cache.proj);
      }
      inline void set_render_cache(shader_seprate* shader,glm::mat4& view,glm::mat4& proj, bool is_elm = false)
      {
        render_cache.shader= shader;
        render_cache.view=view;
        render_cache.proj=proj;
        render_cache.is_elm=is_elm;
      }

  void LoadGLTextures(const aiScene* scene, const std::string& pModelPath)
{
	// Check if scene has textures.
	if(scene->HasTextures())
	{
		textureIds = new GLuint[scene->mNumTextures];
		glGenTextures(scene->mNumTextures, textureIds);// generate GL-textures ID's
		// upload textures
		for(size_t ti = 0; ti < scene->mNumTextures; ti++)
		{
			glBindTexture(GL_TEXTURE_2D, textureIds[ti]);// Binding of texture name
			//
			//redefine standard texture values
			//
			// We will use linear interpolation for magnification filter
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// tiling mode
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (scene->mTextures[ti]->achFormatHint[0] & 0x01) ? GL_REPEAT : GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (scene->mTextures[ti]->achFormatHint[0] & 0x01) ? GL_REPEAT : GL_CLAMP);
			// Texture specification
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, scene->mTextures[ti]->mWidth, scene->mTextures[ti]->mHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE,
							scene->mTextures[ti]->pcData);
		}
	}
}
/*
void get_bounding_box_for_node(const aiNode* nd, aiVector3D* min,  aiVector3D* max, aiMatrix4x4* trafo)
{
aiMatrix4x4 prev;
unsigned int n = 0, t;

	prev = *trafo;
	*trafo = *trafo * nd->mTransformation;
	for(; n < nd->mNumMeshes; ++n)
	{
		const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

		for(t = 0; t < mesh->mNumVertices; ++t)
		{
			aiVector3D tmp = mesh->mVertices[t];

			tmp *= *trafo;

			min->x = aisgl_min(min->x,tmp.x);
			min->y = aisgl_min(min->y,tmp.y);
			min->z = aisgl_min(min->z,tmp.z);

			max->x = aisgl_max(max->x,tmp.x);
			max->y = aisgl_max(max->y,tmp.y);
			max->z = aisgl_max(max->z,tmp.z);
		}
	}

	for(n = 0; n < nd->mNumChildren; ++n)
	{
		get_bounding_box_for_node(nd->mChildren[n],min,max,trafo);
	}

	*trafo = prev;
}

void get_bounding_box(aiVector3D* min, aiVector3D* max)
{
aiMatrix4x4 trafo;

	min->x = min->y = min->z =  1e10f;
	max->x = max->y = max->z = -1e10f;
	get_bounding_box_for_node(scene->mRootNode, min, max, &trafo);
}

*/
    //  assimp_model(const assimp_model&);
};

//  set_obj_type(Sym_Object_Type::MESH_OBJ);
