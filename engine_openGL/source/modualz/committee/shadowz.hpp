

const unsigned int SHADOW_TX_WIDTH = 1024, SHADOW_TX_HEIGHT = 1024;

class shadow_omnidirectional_map
{
  //unsigned int depth_cube_map;
  GLuint fbo;
//GLuint m_shadowMap;
  GLuint depth_cube_map;
  std::vector<glm::mat4> shadowTransforms;
  bool high_prz = false;
  void init()
  {
    // traditional 24 bit unsigned int z-bufferGLint
    if(!high_prz){
      internal_format =  GL_DEPTH_COMPONENT24;
      GLenum data_type = GL_UNSIGNED_INT;
    }
    else
    {
      GLint internal_format =  GL_DEPTH_COMPONENT32F;
      GLenum data_type = GL_FLOAT;
    }

    // float z-buffer (if more precision is needed)



    glGenFramebuffers(1, &fbo);

    glGenTextures(1, &depth_cube_map);
    glBindTexture(GL_TEXTURE_CUBE_MAP,depth_cube_map);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for(unsigned int i =0 ; i<6; ++i)
    {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
                    SHADOW_TX_WIDTH, SHADOW_TX_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }


     glBindFramebuffer(GL_FRAMEBUFFER, fbo);
       glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_cube_map, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
    //glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,)
  }

void gen_light_space_tranz()
{

  float aspect = (float)SHADOW_TX_WIDTH/(float)SHADOW_TX_HEIGHT;
  float near =1.0f;
  float far =25.0f;
  glm::mat4 shadow_projection = glm::perspective(glm::radians(90.0f),aspect,near,far);

  shadowTransforms.push_back(shadow_projection *
                   glm::lookAt(lightPos, lightPos +
                  glm::vec3( 1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0));
  shadowTransforms.push_back(shadow_projection *
                   glm::lookAt(lightPos, lightPos +
                   glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0));
  shadowTransforms.push_back(shadow_projection *
                   glm::lookAt(lightPos, lightPos +
                  glm::vec3( 0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
  shadowTransforms.push_back(shadow_projection *
                   glm::lookAt(lightPos, lightPos +
                   glm::vec3( 0.0,-1.0, 0.0), glm::vec3(0.0, 0.0,-1.0));
  shadowTransforms.push_back(shadow_projection *
                   glm::lookAt(lightPos, lightPos +
                   glm::vec3( 0.0, 0.0, 1.0), glm::vec3(0.0,-1.0, 0.0));
  shadowTransforms.push_back(shadow_projection *
                   glm::lookAt(lightPos, lightPos +
                   glm::vec3( 0.0, 0.0,-1.0), glm::vec3(0.0,-1.0, 0.0));
}


};

void bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void render()
{
  glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
glClear(GL_DEPTH_BUFFER_BIT);
ConfigureShaderAndMatrices();
RenderScene();
glBindFramebuffer(GL_FRAMEBUFFER, 0);
// 2. then render scene as normal with shadow mapping (using depth cubemap)
glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
ConfigureShaderAndMatrices();
glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
RenderScene();
}



struct light_space_tranform
{


}
