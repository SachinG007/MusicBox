#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

GLuint LoadTexture( const char * filename, int width, int height );
void FreeTexture( GLuint texture );
#endif 
