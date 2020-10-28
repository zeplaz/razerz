#include "partical_env.hpp"

long comput_partic_sim::frame_count =0;

void compute_partic_attracto::init()
{
  glGenVertexArrays(1, &render_vao);
  glBindVertexArray(render_vao);

    set_uniform_loc();

    //
    //glGenBuffers(1, &orgin_ID);
    //glBindBuffer(GL_UNIFORM_BUFFER, orgin_ID);
    //glBufferData(GL_UNIFORM_BUFFER,sizeof(glm::vec4), glm::value_ptr(orgin), GL_STATIC_COPY);
    //glBindBufferBase(GL_UNIFORM_BUFFER, PARTCL_UNI_BIDN_INDX, orgin_ID);
  
  // YOOO  
    
  glGenBuffers(2,p_buffz);
  glBindBuffer(GL_ARRAY_BUFFER,position_buffer);
  glBufferData(GL_ARRAY_BUFFER, PARTICLE_COUNT * sizeof(glm::vec4), NULL, GL_DYNAMIC_COPY);



  glm::vec4* positions = (glm::vec4*)glMapBufferRange(GL_ARRAY_BUFFER,
                                                      0,
                                                      PARTICLE_COUNT * sizeof(glm::vec4),
                                                      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

for(int i = 0; i<PARTICLE_COUNT; i++)
{
  positions[i] = orgin+ glm::vec4(random_vector(-10.0f, 10.0f), random_float());
}
glUnmapBuffer(GL_ARRAY_BUFFER);

glVertexAttribPointer(VERTEX_BINDER, 4, GL_FLOAT, GL_FALSE, 0, NULL);
glEnableVertexAttribArray(VERTEX_BINDER);

glBindBuffer(GL_ARRAY_BUFFER, velocity_buffer);
glBufferData(GL_ARRAY_BUFFER, PARTICLE_COUNT * sizeof(glm::vec4), NULL, GL_DYNAMIC_COPY);

glm::vec4 * velocities = (glm::vec4 *)glMapBufferRange(GL_ARRAY_BUFFER,
                                                             0,
                                                             PARTICLE_COUNT * sizeof(glm::vec4),
                                                             GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

  for (int i = 0; i < PARTICLE_COUNT; i++)
  {
      velocities[i] = glm::vec4(random_vector(-0.1f, 0.1f), 0.0f);
  }
  glUnmapBuffer(GL_ARRAY_BUFFER);

  glGenTextures(2, tbos);
  for (int i = 0; i < 2; i++)
   {
       glBindTexture(GL_TEXTURE_BUFFER, tbos[i]);
       glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, p_buffz[i]);
   }

    glGenBuffers(1, &attractor_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, attractor_buffer);
    glBufferData(GL_UNIFORM_BUFFER, MAX_ATTRACTORS * sizeof(glm::vec4), NULL, GL_DYNAMIC_COPY);

  for (int i = 0; i < MAX_ATTRACTORS; i++)
 {
     attractor_masses[i] = 0.5f + random_float() * 1.5f;
 }

 glBindBufferBase(GL_UNIFORM_BUFFER, PARTCL_UNI_BIDN_INDX, attractor_buffer);

}



void compute_partic_attracto::partical_dispaly()
{

  start_ticks  =  static_cast<GLuint>(tick_current_return())-100000;
  current_time = static_cast<GLuint>(tick_current_return());

time = ((start_ticks - current_time) & 0xFFFFF) / float(0xFFFFF);
delta_time = (float)(current_time - last_ticks) * 0.075;

  std::cout<<"\n TIMEDISPLAYZVALZ" << "start:" <<start_ticks << "  current:" <<current_time << "  last:" <<last_ticks <<'\n'
  << "time::"<<time << "  delta_time::" << delta_time << '\n';

  if (delta_time < 0.01f)
 {
     return;
 }
//glBindBuffer(GL_UNIFORM_BUFFER, attractor_buffer);
  glm::vec4 * attractors = (glm::vec4 *)glMapBufferRange(GL_UNIFORM_BUFFER,
                                                         0,
                                                         MAX_ATTRACTORS * sizeof(glm::vec4),
                                                         GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

for(int i = 0; i<MAX_ATTRACTORS;i++)
{
  attractors[i] = glm::vec4(sinf(time * (float)(i + 4) * 7.5f * 20.0f) * 50.0f,
                                    cosf(time * (float)(i + 7) * 3.9f * 20.0f) * 50.0f,
                                    sinf(time * (float)(i + 3) * 5.3f * 20.0f) * cosf(time * (float)(i + 5) * 9.1f) * 100.0f,
                                    attractor_masses[i]);

    /*std::cout << "\n attractornum:" << i << "\n mass:"<< attractor_masses[i] << '\n'
    << attractors[i].x  << '\n'
    << attractors[i].y << '\n'
    << attractors[i].z << '\n'
    << attractors[i].w << '\n' ;*/

  /*attractors[i] = glm::vec4(sinf(time * (float)(i + 2) * 4.5f * 10.0f) * 30.0f,
                                  cosf(time * (float)(i + 2) * 3.9f * 10.0f) * 30.0f,
                                  sinf(time * (float)(i + 3) * 4.3f * 10.0f) * cosf(time * (float)(i + 4) * 6.1f) * 70.0f,
                                  attractor_masses[i]);*/
}


glUnmapBuffer(GL_UNIFORM_BUFFER);
if (delta_time >= 2.0f)
{
  delta_time = 2.0f;
}

std::cout << "deltatime:" << delta_time <<'\n';
glUseProgram(comput_prog_ID);
glBindImageTexture(PARTCL_U_VELOC_INDEX, velocity_tbo, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
glBindImageTexture(PARTCL_U_POS_INDEX,   position_tbo, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
// Set delta time
glUniform1f(dt_location, delta_time);
glUniform4fv(orgin_loc, 1,glm::value_ptr(orgin));
// Dispatch
glDispatchCompute(PARTICLE_GROUP_COUNT, 1, 1);

glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

   glm::mat4 mvp =   glm::perspective(45.0f, active_lenz->aspect_ratio_cal(), 0.1f, 1000.0f) *
                     glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, -160.0f)) *
                     glm::rotate(glm::mat4(1.f),time * 1000.0f, glm::vec3(0.0f, 1.0f, 0.0f));


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    glUseProgram(render_prog_ID);
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mvp));
    glBindVertexArray(render_vao);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);
    last_ticks = current_time;
}
