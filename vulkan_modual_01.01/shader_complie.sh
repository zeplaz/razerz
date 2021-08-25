#!/bin/bash

SHADER_ROOT=../shaderzglsl/
COMPUTE_A_DIR=elemental/compute_partical/
GLYPHS_A_DIR=text/glyphs_base_A/

PRECOMP_DIR=${SHADER_ROOT}/precomplied/
#SCOMPUTE_A_FILES= "glslangValidator -V -S comp ${SHADER_ROOT}${COMPUTE_A_DIR}compute_expanse_BASE_A.glsl -o comp1.svp"

#echo ${COMPUTE_A_FILES}
glslangValidator --target-env vulkan1.2 -V -S comp ${SHADER_ROOT}${COMPUTE_A_DIR}compute_expanse_BASE_A.glsl -o ${PRECOMP_DIR}comp_computepartical_A.spv
glslangValidator --target-env vulkan1.2 -V -S vert ${SHADER_ROOT}${COMPUTE_A_DIR}vertex_partical_BASE_A.glsl -o ${PRECOMP_DIR}vert_computepartical_A.spv
glslangValidator --target-env vulkan1.2 -V -S frag ${SHADER_ROOT}${COMPUTE_A_DIR}frag_partical_BASE_A.glsl -o ${PRECOMP_DIR}frag_computepartical_A.spv

glslangValidator --target-env vulkan1.2 -V -S vert ${SHADER_ROOT}${GLYPHS_A_DIR}vertex_glyph_shaderbase_A.glsl -o ${PRECOMP_DIR}vert_glyph_A.spv
glslangValidator --target-env vulkan1.2 -V -S frag ${SHADER_ROOT}${GLYPHS_A_DIR}frag_glyph_shaderbase_A.glsl -o ${PRECOMP_DIR}frag_glyph_A.spv