
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

  std::shared_ptr<ai_model> ai_model::load_from_file(const pathz& in_path, const ai_Transformz& in_tranz)
  {

	const aiScene* scene = aiImportFile(in_path.full_path, aiProcessPreset_TargetRealtime_MaxQuality);
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
    for(uint32_t vertxIdx = 0u; vertxIdx< mesh->mNumVertices; vertxIdx++)
    {
      aiVector3D vert = mesh->mVertices[vertxIdx];
			aiVector3D norm = mesh->mNormals[vertxIdx];
      aiVector3D uv = mesh->mTextureCoords[0][vertxIdx];
      vertx.push_back
      (
          ai_vertex(glm::vec3(vert.x,vert.y,vert.z),
                    glm::vec3(norm.x,norm.y,norm.z),
                    uv.x, uv.y
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
    //the call set_
    ai_render_call rcall(vertx,indices);

    //verts, indices
    new_meshz.push_back(ai_mesh(rcall,mesh_material));
  }
  return std::make_shared<ai_model>(new_meshz,in_tranz);
  }


/*
assimp_model(const std::vector<assimp_mesh> am_meshez, const Transform& tranz);

  static std::shared_ptr<assimp_model> ai_Transformz::load_from_file(const pathz& in_path);

assimp_model(const assimp_model&)

load_from_file()
{
}
*/
