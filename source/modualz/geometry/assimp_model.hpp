
#ifndef RZ_ASSIMP_MODEL_HPP
#define RZ_ASSIMP_MODEL_HPP


#include "geometry.hpp"
#include <assimp/material.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include "../../basez/io_utilityz.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)


struct ai_Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

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
  glm::vec2 uv;

  glm::vec3 Tangent;
// bitangent
  glm::vec3 Bitangent;
  ai_vertex(const glm::vec3& in_pos, const glm::vec3& in_norm, glm::vec2 in_UV, glm::vec3 in_tan, glm::vec3 in_bitan):
  pos{in_pos},__one(1.f),normal{in_norm},__zero{0.f},uv{in_UV},Tangent{in_tan},Bitangent{in_bitan}
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
   unsigned int VAO;
   unsigned int VBO, EBO;

  ai_render_call (std::vector<ai_vertex>& vertices, std::vector<unsigned int>& indices)
  {
    	NumberOfIndices = (uint32_t)indices.size();
      vertices=vertices;
      indices=indices;
  }
  std::uint32_t NumberOfIndices;
  std::vector<ai_vertex> vertices;
  std::vector<unsigned int> indices;

void  draw(){
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
  }

  void setup()
  {
      glGenVertexArrays(1, &VAO);
       glGenBuffers(1, &VBO);
       glGenBuffers(1, &EBO);

       glBindVertexArray(VAO);
        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(ai_vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ai_vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ai_vertex), (void*)offsetof(ai_vertex, normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ai_vertex), (void*)offsetof(ai_vertex, uv));
        // vertex tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(ai_vertex), (void*)offsetof(ai_vertex, Tangent));
        // vertex bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(ai_vertex), (void*)offsetof(ai_vertex, Bitangent));

        glBindVertexArray(0);

  }
};


// should use move symantics with both pointer static func anddddd init!!!

//static unsigned int ai_TextureFromFile(const char *path, const std::string &directory, bool gamma = false);


class ai_model{
  public :
  struct ai_mesh{
    ai_render_call render_call;
    ai_Material material;
		std::vector<ai_texture> textures;

    ai_mesh(ai_render_call in_rc,ai_Material in_mat,std::vector<ai_texture> in_text)
    :render_call{in_rc},material{in_mat},textures{in_text}
    {}
    };
    inline void set_location(glm::mat4 in_cu_loc)
    {
      current_location_matrix = in_cu_loc;
    }
    inline void update_motion_matrix(glm::mat4 in_mat)
    {
      current_location_matrix*= in_mat;
    }
    void draw()
    {
      //handle unformz
      glm::mat4 proj_view(1.f);
      glm::mat3 normal_matrix(1.f);
      //model drawing
      //if(cal_lightz == true)
      glm::mat4 model= tranzform.get_martix_from_tranform();

      glm::mat4 model_view = render_cache.view*model;
        //glm::mat3 normal_matrix = glm::transpose(glm::inverse(model_view.xyz));
        normal_matrix = glm::inverse(glm::mat3(model_view));
        proj_view = render_cache.proj*render_cache.view;
        glm::mat4  m_v_p = proj_view*current_location_matrix;
        glUniformMatrix4fv(glGetUniformLocation(render_cache.shader->gl_shaderprgm_ID,"model"),1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix3fv(glGetUniformLocation(render_cache.shader->gl_shaderprgm_ID,"normal_matrix"),1,GL_TRUE,glm::value_ptr(normal_matrix));
        //glUniformMatrix4fv(glGetUniformLocation(shader->gl_shaderprgm_ID,"model_view"),1,GL_FALSE,glm::value_ptr(model_view));
        glUniformMatrix4fv(glGetUniformLocation(render_cache.shader->gl_shaderprgm_ID,"model_proj_View"),1,GL_FALSE,glm::value_ptr(m_v_p));

      for(size_t j = 0; j< meshez.size(); j++)
      {
        unsigned int diffuseNr  = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr   = 1;
        unsigned int heightNr   = 1;
        for(unsigned int i = 0; i < meshez[j].textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = meshez[j].textures[i].type;
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to stream
            else if(name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to stream
             else if(name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to stream

            // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(render_cache.shader->gl_shaderprgm_ID, (name + number).c_str()), i);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, meshez[j].textures[i].id);
        }
        meshez[j].render_call.draw();
      }

    }

protected :
			pathz model_path;
			std::vector<ai_texture>textures_loaded;
      std::vector<ai_mesh> meshez;
    //  ai_Transformz tranzform;
    glm::mat4 current_location_matrix;
    //  GLuint*	textureIds = nullptr;
      render_state_cache render_cache;


public :
  std::vector<ai_texture> ai_loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, const pathz& in_path);
  //bool update(float dt);
//  bool draw(shader_seprate*shader,glm::mat4& view,glm::mat4& proj);
  ai_model(const ai_model&) = delete;
  ai_model() = default;
  inline void init(std::vector<ai_mesh>& in_meshz)
  {
    meshez=in_meshz;
    //current_location_matrix =tranzform.get_martix_from_tranform();
  }

  /*inline void draw_via_cache()
  {
    draw(render_cache.shader,render_cache.view,render_cache.proj);
  }*/

  inline void update_view_cache(glm::mat4& view)
  {
    render_cache.view=view;
  }

  inline void update_proj_cache(glm::mat4& proj)
  {
    render_cache.proj=proj;
  }
  inline void set_render_cache(shader_seprate* shader,glm::mat4& view,glm::mat4& proj, bool is_elm = false)
  {
    render_cache.shader= shader;
    render_cache.view=view;
    render_cache.proj=proj;
    render_cache.is_elm=is_elm;
  }

  static std::shared_ptr<ai_model> load_from_file(const pathz& in_path)
        //  static ai_model* load_from_file(const pathz& in_path,  ai_Transformz& in_tranz)
				{
			  //model_path= in_path;
			  std::shared_ptr<ai_model> model_to_re= std::make_shared<ai_model>();
        //ai_model* model_to_re= new ai_model();
        model_to_re->model_path=in_path;
				const aiScene* scene = aiImportFile(in_path.full_path, aiProcessPreset_TargetRealtime_MaxQuality);
				//const std::vector<pathz> texture_paths;

#ifdef DEBUG_01
          std::cout << "DRECTORY OF MODEL::" <<in_path.drectory_path <<'\n';
#endif

        if(!scene)
			  {
			    std::cerr <<"failed ai loadfilez::"<< in_path.file_name <<'\n';
			    return nullptr;
			  }
			  std::vector<ai_mesh> new_meshz;
			  new_meshz.reserve(scene->mNumMeshes);
			  for(uint32_t meshIdx = 0u; meshIdx<scene->mNumMeshes; meshIdx++)
			  {
			    aiMesh* mesh = scene->mMeshes[meshIdx];
			    std::vector<ai_vertex> vertx;
			    vertx.reserve(mesh->mNumVertices);
			    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			    aiColor4D specularColor;
			    aiColor4D diffuseColor;
			    aiColor4D ambientColor;
			    float   shininess;

			    aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor);
					aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);
					aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColor);
					aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);

			    ai_Material mesh_material(
			      glm::vec4(specularColor.r,specularColor.g,specularColor.b,specularColor.a),
			      glm::vec4(diffuseColor.r,diffuseColor.g,diffuseColor.b,diffuseColor.a),
			      glm::vec4(ambientColor.r,ambientColor.g,ambientColor.b,ambientColor.a),shininess
			    );
          #ifdef DEBUG_01
          std::cout << "SHINEness...::"<<shininess <<'\n';
          #endif

			    for(uint32_t vertxIdx = 0u; vertxIdx< mesh->mNumVertices; vertxIdx++)
			    {
			      aiVector3D  vert = mesh->mVertices[vertxIdx];
						aiVector3D  norm = mesh->mNormals[vertxIdx];
			      aiVector3D  uv   = mesh->mTextureCoords[0][vertxIdx];
            aiVector3D  tang = mesh->mTangents[vertxIdx];
            aiVector3D  bitang = mesh->mBitangents[vertxIdx];
			      vertx.push_back
			      (
			          ai_vertex(glm::vec3(vert.x,vert.y,vert.z),
			                    glm::vec3(norm.x,norm.y,norm.z),
			                    glm::vec2 (uv.x, uv.y),
                          glm::vec3(tang.x,tang.y,tang.z),
                          glm::vec3(bitang.x,bitang.y,bitang.z)
			                    )
			      );
			    }

			    std::vector<uint32_t> indices;
			    indices.reserve(mesh->mNumFaces*3u);
			    for(uint32_t faceIdx= 0u; faceIdx<mesh->mNumFaces; faceIdx++)
			    {
			      indices.push_back(mesh->mFaces[faceIdx].mIndices[0u]);
						indices.push_back(mesh->mFaces[faceIdx].mIndices[1u]);
						indices.push_back(mesh->mFaces[faceIdx].mIndices[2u]);
			    }
			      std::vector<ai_texture> textures;

			         std::vector<ai_texture> diffuseMaps = model_to_re->ai_loadMaterialTextures(material, aiTextureType_DIFFUSE,"texture_diffuse",in_path);
               #ifdef DEBUG_01
                         std::cout << "diffusemapz of MODEL::size vec" << diffuseMaps.size() << '\n';
               #endif
              textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			        // 2. specular maps
			        std::vector<ai_texture> specularMaps = model_to_re->ai_loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular",in_path);
			        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
              #ifdef DEBUG_01
                        std::cout << "specularMaps of MODEL::size vec" << specularMaps.size() << '\n';
              #endif
			        // 3. normal maps
			        std::vector<ai_texture> normalMaps = model_to_re->ai_loadMaterialTextures(material, aiTextureType_HEIGHT,"texture_normal" ,in_path);
			        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
              #ifdef DEBUG_01
                        std::cout << "normalMaps of MODEL::size vec" << normalMaps.size() << '\n';
              #endif
			        // 4. height maps
			        std::vector<ai_texture> heightMaps = model_to_re->ai_loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height",in_path);
			        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
              #ifdef DEBUG_01
                        std::cout << "heightMaps of MODEL::size vec" << heightMaps.size() << '\n';
              #endif

			    //the call set_
			    ai_render_call rcall(vertx,indices);

			    //verts, indices
			    new_meshz.push_back(ai_mesh(rcall,mesh_material,textures));
			  }


			  model_to_re->init(new_meshz);
        #ifdef DEBUG_01
                  std::cout << "model to re_init()etc\n";
        #endif
			  return model_to_re;
			  }

};
#endif
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


//  set_obj_type(Sym_Object_Type::MESH_OBJ);
