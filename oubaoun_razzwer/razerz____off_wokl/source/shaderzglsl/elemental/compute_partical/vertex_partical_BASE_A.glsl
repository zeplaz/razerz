#version 450 core

        layout(location = 0)in vec4 vert;
        uniform mat4 mvp;

        out gl_PerVertex{
            vec4 gl_Position;
            
        };

        out float age_intensity;
        out vec2 pos_intensity;

        void main(void)
        {
            age_intensity = vert.w;
            pos_intensity = vec2(vert.x,vert.y);
            gl_Position = mvp * vec4(vert.xyz, 1.0);

        }
