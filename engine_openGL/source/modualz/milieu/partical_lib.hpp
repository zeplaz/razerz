#pragma once
#include<time.h>
#include<chrono>

#include "../../basez/gl_lib_z.hpp"
#include "../../MCP_cmd/shader_pipeline_CMD.hpp"
#include "../../basez/lenz.hpp"


/*
REMBER YOU MUST SET THE SHADER PROGRAMS LENZ AND ORGIAN BEFORE CALLING INIT!
ORGIN USES PIXEL SPACE! KINDA>
*/

constexpr int  VERTEX_BINDER = 0;
constexpr int  PARTCL_UNI_BIDN_INDX = 3;
constexpr int  PARTCL_U_VELOC_INDEX =4;
constexpr int  PARTCL_U_POS_INDEX =5;
constexpr int  PARTCL_U_ORGIN_INDEX =6;

constexpr int  MAX_ATTRACTORS = 24;

constexpr int  PARTC_ENV_BUFFZ = 2;

constexpr int  PARTICLE_GROUP_SIZE     = 512;
constexpr int  PARTICLE_GROUP_COUNT   = 4096;
constexpr int  PARTICLE_COUNT          = (PARTICLE_GROUP_SIZE * PARTICLE_GROUP_COUNT);


static inline  long tick_current_return()
  {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

    auto ap_now_epo = now_ms.time_since_epoch();
    long now_duration = ap_now_epo.count();

    std::chrono::milliseconds dur(now_duration);
    std::chrono::time_point<std::chrono::system_clock> dt_tic(dur);
    std::cout << "\n->#LONG TICCK RETURN::"<< now_duration <<'\n';
    return now_duration;
  }

  static inline float random_float()
  {
    float res;
    unsigned int tmp;
    static unsigned int seed = 0xFFFF0C59;

    seed *= 16807;

    tmp = seed ^ (seed >> 4) ^ (seed << 15);

    *((unsigned int *) &res) = (tmp >> 9) | 0x3F800000;

    //std::cout << "\nres::"<<res << " rez-1.0f" << res - 1.0f <<'\n';
    return (res - 1.0f);
   }

  static glm::vec3 random_vector(float minmag = 0.0f, float maxmag = 1.0f)
  {
      glm::vec3 randomvec(random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f);
      randomvec = glm::normalize(randomvec);
      randomvec *= (random_float() * (maxmag - minmag) + minmag);

    //  std::cout <<"\nradvec::" << 'x'<< randomvec.x <<'\n'
    //  <<'y' <<randomvec.y << '\n'
    //  <<'z' << randomvec.y << '\n';
      return randomvec;
  }
