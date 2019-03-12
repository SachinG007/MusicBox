/*
  A program which opens a window and draws three arms in a hierarchy

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Written by - 
               Harshavardhan Kode
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include <vector>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
// #include "parameters.cpp"
#include "hierarchy_node.hpp"

/*// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;*/
// Camera position and rotation Parameters
GLfloat c_xpos = 0.0, c_ypos = 0.0, c_zpos = 8.0, click=0, beizer_done=0, animate = 0, start_char_animation=0;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;

glm::vec3 c_lookat = glm::vec3(-10,  0, -10);
int char_anim_frame_num=0;

float sampled_beizer[100][3];
float sampled_beizer_rotation[100][3];
double timer = 1.0/30.0;
double timer2 = 1.0/30.0;
int num_frames=0;
int num_read_frames = 0;
std::vector<double> read_keyframes[500];
std::vector<double> interpolated_frames[5000];

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=false;
//Shader program attribs
GLuint vPosition, vColor, vNormal, texCoord, tex_or_color, light1_on, light2_on;
float light1_on_var = 1.0, light2_on_var = 0.0;
glm::mat4 modelview_matrix;
glm::mat4 inv_modview;
glm::mat4 view_matrix;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;

csX75::HNode* root_node;
csX75::HNode* curr_node;
csX75::HNode* node1;
csX75::HNode* node2;
csX75::HNode* node3;
csX75::HNode* node_box;
csX75::HNode* node_lid;
csX75::HNode* node_face;
csX75::HNode* node_neck;
csX75::HNode* node_torso;
csX75::HNode* node_hip_left;
csX75::HNode* node_hip_right;
csX75::HNode* node_thigh_left;
csX75::HNode* node_thigh_right;
csX75::HNode* node_knee_left;
csX75::HNode* node_knee_right;
csX75::HNode* node_leg_left;
csX75::HNode* node_leg_right;
csX75::HNode* node_shoulder_left;
csX75::HNode* node_shoulder_right;
csX75::HNode* node_uarm_left;
csX75::HNode* node_uarm_right;
csX75::HNode* node_elbow_left;
csX75::HNode* node_elbow_right;
csX75::HNode* node_larm_left;
csX75::HNode* node_larm_right;
csX75::HNode* node_caplow;
csX75::HNode* node_capup;
csX75::HNode* node_hand_left;
csX75::HNode* node_hand_right;
csX75::HNode* node_shoe_left;
csX75::HNode* node_shoe_right;
csX75::HNode* node_torso2;
csX75::HNode* node_shield;
csX75::HNode* node_face_im;
csX75::HNode* node_torso_im;
csX75::HNode* node_shoulder_left_im;
csX75::HNode* node_shoulder_right_im;
csX75::HNode* node_arm_left_im;
csX75::HNode* node_arm_right_im;
csX75::HNode* node_antenna1_im;
csX75::HNode* node_antenna2_im;
csX75::HNode* node_heart_im;
csX75::HNode* node_eye_im;
csX75::HNode* node_hip_left_im;
csX75::HNode* node_hip_right_im;
csX75::HNode* node_leg_left_im;
csX75::HNode* node_leg_right_im;
csX75::HNode* node_leyes_im;
csX75::HNode* node_reyes_im;
csX75::HNode* node_platform1;
csX75::HNode* node_platform2;
csX75::HNode* node_platform3;

csX75::HNode* node_room;

csX75::HNode* node_tabletop;
csX75::HNode* node_tableleg_bl;
csX75::HNode* node_tableleg_br;
csX75::HNode* node_tableleg_fl;
csX75::HNode* node_tableleg_fr;

csX75::HNode* node_stooltop;
csX75::HNode* node_stoolback;
csX75::HNode* node_stoolleg_bl;
csX75::HNode* node_stoolleg_br;
csX75::HNode* node_stoolleg_fl;
csX75::HNode* node_stoolleg_fr;

csX75::HNode* node_door;
csX75::HNode* node_window;
csX75::HNode* node_cupboard;
csX75::HNode* node_wall_light;

csX75::HNode* node_onclick;
csX75::HNode* node_beizer;
csX75::HNode* node_lamp;
csX75::HNode* node_lamp_sprt;
csX75::HNode* node_lamp_sprt2;
// csX75::HNode* nodes[2];
std::vector<csX75::HNode*> vec_nodes;
// vec_nodes.push_back(node_torso2);

//-------------------------------------------------------------------------

#endif
