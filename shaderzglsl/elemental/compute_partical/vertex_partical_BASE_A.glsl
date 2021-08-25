#version 450 core

        layout(location = 0) in vec4 vert;
        layout(location = 0)  out gl_PerVertex
        {
          vec4 gl_Position;
        };
        layout(location = 1)  out float age_intensity;
        layout(location = 2)  out vec2 pos_intensity;

        layout(set=0,binding = 0) uniform uniform_object
        {
          mat4 mvp[3];
        } ubo;

        void main(void)
        {
            age_intensity = vert.w;
            pos_intensity = vec2(vert.x,vert.y);
            gl_Position = (ubo.mvp[0]*ubo.mvp[1]*ubo.mvp[2])* vec4(vert.xyz, 1.0);
        }
