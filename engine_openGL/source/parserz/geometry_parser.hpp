#pragma once

#include "parserlib.hpp"

 struct mesh_vertex
{
  glm::vec3 v_position;
  glm::vec3 v_normal;
  glm::vec2 v_textcord;
  glm::vec4 v_tangent;

  bool operator<(const mesh_vertex that) const{
		return memcmp((void*)this, (void*)&that, sizeof(mesh_vertex))>0;}

  friend std::ostream & operator << (std::ostream &out, const mesh_vertex &c);

};

typedef struct parsed_paket_type
{
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> uvs;

  parsed_paket_type(std::vector<glm::vec3> in_vertices,
              std::vector<glm::vec3> in_normals,
              std::vector<glm::vec2> in_uvs)
  {
    std::vector<glm::vec3> vertices =in_vertices;
    std::vector<glm::vec3> normals  =in_normals;
    std::vector<glm::vec2> uvs      =in_uvs;
  }

}parsed_paket;


class wavefornt_parser2
{
  private :

  std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

  public :
  void cleanup_paket(parsed_paket* in_pak)
  {
    in_pak->vertices.clear();
    in_pak->uvs.clear();
    in_pak->normals.clear();
    delete in_pak;
  }
  parsed_paket* gen_parse_parket(std::vector < glm::vec3 > & in_vertices,
                                  std::vector < glm::vec3 > & in_normals,
                                  std::vector < glm::vec2 > & in_uvs)
    {
      parsed_paket* temp_pak = new parsed_paket(in_vertices,in_normals,in_uvs);
      return temp_pak;
    }


  std::pair<std::shared_ptr<std::vector<mesh_vertex>>,std::shared_ptr<std::vector<unsigned int>>> read_file(std::string path)
  {
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;
    std::shared_ptr<std::vector<mesh_vertex>> mesh_v_prt = std::make_shared<std::vector<mesh_vertex>>();

    FILE* file = fopen(path.c_str(),"r");
    if(file == NULL)
    {
      printf("failto openfile \n");
      fclose(file);
      return std::make_pair(nullptr,nullptr);
    }
    else
    {

    while(1)
    {
      char line_header[255];
      int res = fscanf(file,"%s",line_header);
      if(res == EOF)
      break;
      if(strcmp(line_header, "v") ==0)
      {
        glm::vec3 vertex;
        fscanf(file,"%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
        temp_vertices.push_back(vertex);
      }
      else if( strcmp( line_header, "vt" ) == 0 )
      {
        glm::vec2 uv;
        fscanf(file, "%f %f\n", &uv.x, &uv.y );
        temp_uvs.push_back(uv);
      }
      else if ( strcmp( line_header, "vn" ) == 0 )
      {
        glm::vec3 normal;
        fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
        temp_normals.push_back(normal);
      }
      else if ( strcmp( line_header, "f" ) == 0 )
      {
        std::string vertex1, vertex2, vertex3;
        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
        if (matches != 9)
        {
            printf("File can't be read by our simple parser : ( Try exporting with other options\n");
            return  std::make_pair(nullptr,nullptr);
        }
        vertexIndices.push_back(vertexIndex[0]);
        vertexIndices.push_back(vertexIndex[1]);
        vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
        normalIndices.push_back(normalIndex[0]);
        normalIndices.push_back(normalIndex[1]);
        normalIndices.push_back(normalIndex[2]);
    }
  }
  fclose(file);

  for(unsigned int i=0; i< vertexIndices.size();i++)
  {
    mesh_vertex t_mv;
    unsigned int vertexIndex_current = vertexIndices[i];
    unsigned int IndicesIndex_current = uvIndices[i];
    unsigned int normalIndex_current = normalIndices[i];
    glm::vec3 vertex = temp_vertices[ vertexIndex_current-1 ];
    glm::vec3 normz = temp_normals[normalIndex_current-1];
    glm::vec2 uvz = temp_uvs[IndicesIndex_current-1];
    t_mv.v_position =vertex;
    t_mv.v_normal   =normz;
    t_mv.v_textcord = uvz;
    mesh_v_prt->push_back(t_mv);
  }
}

  std::shared_ptr<std::vector<unsigned int>> mesh_v_indices = std::make_shared<std::vector<unsigned int>>(vertexIndices);
  std::pair<std::shared_ptr<std::vector<mesh_vertex>>,std::shared_ptr<std::vector<unsigned int>>> vertex_pair_data = make_pair(mesh_v_prt,mesh_v_indices);

  return vertex_pair_data;
}
};
