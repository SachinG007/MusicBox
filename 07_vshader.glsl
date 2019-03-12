#version 330

in vec4 vPosition;
in vec4 vColor;
in vec4 vNormal;
in vec2 texCoord;

out vec2 tex;
out vec4 fragPosition;
out vec3 fragNormal;
out vec4 fragColor;
out vec4 eye;

uniform int tex_or_color;
uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;

void main (void) 
{

  if(tex_or_color == 0){
    gl_Position = uModelViewMatrix * vPosition;
    fragColor = vColor;
  }
  else{
    gl_Position = uModelViewMatrix * vPosition;
    tex = texCoord;
    fragColor = vColor;
  }

  eye = -gl_Position;
  fragPosition = vPosition;
  fragNormal = vNormal.xyz;
  // fragColor = vColor;

  // gl_Position = uModelViewMatrix * vPosition;
}