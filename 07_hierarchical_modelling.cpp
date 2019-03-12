/*
  CSX75 Tutorial 3

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Modified from An Introduction to OpenGL Programming, 
  Ed Angel and Dave Shreiner, SIGGRAPH 2013//.  

  Written by - 
               Harshavardhan Kode
*/
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_TGA
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.hpp"

#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
#include <iostream>

#include "texture.hpp"
#include "07_hierarchical_modelling.hpp"
#include "05_gouraud.hpp"
#include "parameters.cpp"
#include "arrays.cpp"
#include "cuboid_definitions.cpp"
#include "shape_functions.cpp"
#include <iostream>
using namespace std;

GLuint shaderProgram;

GLuint tex;
GLuint floor_tex, cupboard_tex,tabletop_tex, bed_tex,mat_tex,bed_sprt_tex, window_tex;

GLuint vao[10], vbo[10];

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::vec3 lookat_point(-10,0,-10);

glm::mat4 model_matrix;
// glm::mat4 view_matrix;

// glm::mat4 modelview_matrix;
// glm::mat4 inv_modview;
glm::mat3 normal_matrix;

GLuint cameraPosition;
GLuint uModelViewMatrix;
GLuint viewMatrix;
GLuint normalMatrix;

// quad generates two triangles for each face and assigns colors to the vertices
// void quad(int a, int b, int c, int d, int face_num, glm::vec4 col[], glm::vec4 pos[], glm::vec4 norms[], glm::vec4 col_source[],  glm::vec4 pos_source[], glm::vec4 norms_source[])
// {
//   col[tri_idx] = col_source[a]; pos[tri_idx] = pos_source[a]; norms[tri_idx] = norms_source[face_num]; tri_idx++;
//   col[tri_idx] = col_source[b]; pos[tri_idx] = pos_source[b]; norms[tri_idx] = norms_source[face_num]; tri_idx++;
//   col[tri_idx] = col_source[c]; pos[tri_idx] = pos_source[c]; norms[tri_idx] = norms_source[face_num]; tri_idx++;
//   col[tri_idx] = col_source[a]; pos[tri_idx] = pos_source[a]; norms[tri_idx] = norms_source[face_num]; tri_idx++;
//   col[tri_idx] = col_source[c]; pos[tri_idx] = pos_source[c]; norms[tri_idx] = norms_source[face_num]; tri_idx++;
//   col[tri_idx] = col_source[d]; pos[tri_idx] = pos_source[d]; norms[tri_idx] = norms_source[face_num]; tri_idx++;
//  }


  void character_animation(int char_animation_frame_num){
    // cout << "received frame num" << char_animation_frame_num << endl;
    // cout << "new val" << interpolated_frames[char_animation_frame_num][3] << endl;

    int num_nodes = vec_nodes.size();
    for(int i=0;i<num_nodes;i++){
      vec_nodes[i]->new_tx(interpolated_frames[char_animation_frame_num][i*6 + 0]);
      vec_nodes[i]->new_ty(interpolated_frames[char_animation_frame_num][i*6 + 1]);
      vec_nodes[i]->new_tz(interpolated_frames[char_animation_frame_num][i*6 + 2]);
      vec_nodes[i]->new_rx(interpolated_frames[char_animation_frame_num][i*6 + 3]);
      vec_nodes[i]->new_ry(interpolated_frames[char_animation_frame_num][i*6 + 4]);
      vec_nodes[i]->new_rz(interpolated_frames[char_animation_frame_num][i*6 + 5]);      
    }
    light1_on_var = interpolated_frames[char_anim_frame_num][114];
    light2_on_var = interpolated_frames[char_anim_frame_num][115];
  }

int dump_frames(int image_num)
  {
    int num_bytes_written = 0;
    const int width = 512;
    const int height = 512;

    std::string filename = "output/SavedFrames";
    filename += std::to_string(image_num);
    filename += ".bmp";
    
    std::cout << filename << std::endl;
    // unsigned char store[width*height*4];
    unsigned char* store = new unsigned char[width*height*4];
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, store);
    
    unsigned char* ustore = new unsigned char[width*height*4];
    unsigned int uindex=0;

    for(int x=511; x>=0; x--){
      // std::cout<< "val x"<< x <<std::endl;
      for(int y=0;y<512; y++)
      { 
        // std::cout<< "val x "<< x <<" "<<y<<std::endl;
        ustore[uindex] = (unsigned char)(store[(x*width*4 + y*4 + 0)]);
        ustore[uindex+1]=(unsigned char)(store[(x*width*4 + y*4 + 1)]);
        ustore[uindex+2]=(unsigned char)(store[(x*width*4 + y*4 + 2)]);
        ustore[uindex+3]=(unsigned char)(store[(x*width*4 + y*4 + 3)]);
        uindex = uindex+4;
      }
    }
  
    num_bytes_written = stbi_write_bmp( filename.c_str(), width, height, 4, (void*)ustore );
    std::cout<< "done writing"<<std::endl;
    delete[] ustore;
    
    return num_bytes_written;
  }

void quad(int a, int b, int c, int d, int face_num, glm::vec4 col[], glm::vec4 pos[], glm::vec4 norms[], glm::vec4 col_source[],  glm::vec4 pos_source[], glm::vec4 norms_source[])
{
  col[tri_idx] = col_source[a]; pos[tri_idx] = pos_source[a]; norms[tri_idx] = norms_source[face_num]; tri_idx++;
  col[tri_idx] = col_source[b]; pos[tri_idx] = pos_source[b]; norms[tri_idx] = norms_source[face_num]; tri_idx++;
  col[tri_idx] = col_source[c]; pos[tri_idx] = pos_source[c]; norms[tri_idx] = norms_source[face_num]; tri_idx++;
  col[tri_idx] = col_source[a]; pos[tri_idx] = pos_source[a]; norms[tri_idx] = norms_source[face_num]; tri_idx++;
  col[tri_idx] = col_source[c]; pos[tri_idx] = pos_source[c]; norms[tri_idx] = norms_source[face_num]; tri_idx++;
  col[tri_idx] = col_source[d]; pos[tri_idx] = pos_source[d]; norms[tri_idx] = norms_source[face_num]; tri_idx++;
 }


void textured_quad(int a, int b, int c, int d, int face_num, glm::vec4 col[], glm::vec4 pos[], glm::vec4 norms[], glm::vec2 tex[], glm::vec4 col_source[],  glm::vec4 pos_source[], glm::vec4 norms_source[], glm::vec2 tex_source[] )
{
  // cout <<"hey"<<endl;
  // tex_face_num = tex_face_num%4;
  col[tri_idx] = col_source[a]; pos[tri_idx] = pos_source[a];
  norms[tri_idx] = norms_source[face_num];
  tex[tri_idx] = tex_source[1];
  tri_idx++;

  col[tri_idx] = col_source[b]; pos[tri_idx] = pos_source[b];
  norms[tri_idx] = norms_source[face_num];
  tex[tri_idx] = tex_source[0];
  tri_idx++;

  col[tri_idx] = col_source[c]; pos[tri_idx] = pos_source[c];
  norms[tri_idx] = norms_source[face_num];
  tex[tri_idx] = tex_source[2];
  tri_idx++;

  col[tri_idx] = col_source[a]; pos[tri_idx] = pos_source[a];
  norms[tri_idx] = norms_source[face_num];
  tex[tri_idx] = tex_source[1];
  tri_idx++;

  col[tri_idx] = col_source[c]; pos[tri_idx] = pos_source[c];
  norms[tri_idx] = norms_source[face_num];
  tex[tri_idx] = tex_source[2];
  tri_idx++;

  col[tri_idx] = col_source[d]; pos[tri_idx] = pos_source[d];
  norms[tri_idx] = norms_source[face_num];
  tex[tri_idx] = tex_source[3];
  tri_idx++;
  cout << tri_idx << endl;
 }


// generate 12 triangles: 36 vertices and 36 colors
void draw_cubes(void)
{
    quad( 1, 0, 3, 2, 0, v_colors, v_positions, v_norms, colors, positions, box_normals);
    quad( 2, 3, 7, 6, 1, v_colors, v_positions, v_norms, colors, positions, box_normals);
    quad( 3, 0, 4, 7, 2, v_colors, v_positions, v_norms, colors, positions, box_normals);
    quad( 6, 5, 1, 2, 3, v_colors, v_positions, v_norms, colors, positions, box_normals);
    quad( 4, 5, 6, 7, 4, v_colors, v_positions, v_norms, colors, positions, box_normals);
    quad( 5, 4, 0, 1, 5, v_colors, v_positions, v_norms, colors, positions, box_normals);
    tri_idx = 0;
    //the upper surface of the box will be created separately as it has to open and close
    quad( 2, 3, 7, 6, 1, v_colors_box, v_positions_box, v_norms_box, colors_box, positions_box, box_normals);
    quad( 3, 0, 4, 7, 2, v_colors_box, v_positions_box, v_norms_box, colors_box, positions_box, box_normals);
    quad( 2, 3, 0, 1, 3, v_colors_box, v_positions_box, v_norms_box, colors_box, positions_box, box_normals);
    quad( 4, 5, 6, 7, 4, v_colors_box, v_positions_box, v_norms_box, colors_box, positions_box, box_normals);
    quad( 5, 4, 0, 1, 5, v_colors_box, v_positions_box, v_norms_box, colors_box, positions_box, box_normals);
    tri_idx = 0;
    //lid , a thin cuboid
    quad( 1, 0, 3, 2, 0, v_colors_lid, v_positions_lid, v_norms_lid, colors_lid, positions_lid, box_normals);
    quad( 2, 3, 7, 6, 1, v_colors_lid, v_positions_lid, v_norms_lid, colors_lid, positions_lid, box_normals);
    quad( 3, 0, 4, 7, 2, v_colors_lid, v_positions_lid, v_norms_lid, colors_lid, positions_lid, box_normals);
    quad( 6, 5, 1, 2, 3, v_colors_lid, v_positions_lid, v_norms_lid, colors_lid, positions_lid, box_normals);
    quad( 4, 5, 6, 7, 4, v_colors_lid, v_positions_lid, v_norms_lid, colors_lid, positions_lid, box_normals);
    quad( 5, 4, 0, 1, 5, v_colors_lid, v_positions_lid, v_norms_lid, colors_lid, positions_lid, box_normals);

    tri_idx = 0;
    //platform 1
    quad( 1, 0, 3, 2, 0, v_colors_platform1, v_positions_platform1, v_norms_platform1, colors_paltform1, positions_platform1, box_normals);
    quad( 2, 3, 7, 6, 1, v_colors_platform1, v_positions_platform1, v_norms_platform1, colors_paltform1, positions_platform1, box_normals);
    quad( 3, 0, 4, 7, 2, v_colors_platform1, v_positions_platform1, v_norms_platform1, colors_paltform1, positions_platform1, box_normals);
    quad( 6, 5, 1, 2, 3, v_colors_platform1, v_positions_platform1, v_norms_platform1, colors_paltform1, positions_platform1, box_normals);
    quad( 4, 5, 6, 7, 4, v_colors_platform1, v_positions_platform1, v_norms_platform1, colors_paltform1, positions_platform1, box_normals);
    quad( 5, 4, 0, 1, 5, v_colors_platform1, v_positions_platform1, v_norms_platform1, colors_paltform1, positions_platform1, box_normals);

    tri_idx = 0;
    //platform 2
    quad( 1, 0, 3, 2, 0, v_colors_platform2, v_positions_platform2, v_norms_platform2, colors_paltform2, positions_platform2, box_normals);
    quad( 2, 3, 7, 6, 1, v_colors_platform2, v_positions_platform2, v_norms_platform2, colors_paltform2, positions_platform2, box_normals);
    quad( 3, 0, 4, 7, 2, v_colors_platform2, v_positions_platform2, v_norms_platform2, colors_paltform2, positions_platform2, box_normals);
    quad( 6, 5, 1, 2, 3, v_colors_platform2, v_positions_platform2, v_norms_platform2, colors_paltform2, positions_platform2, box_normals);
    quad( 4, 5, 6, 7, 4, v_colors_platform2, v_positions_platform2, v_norms_platform2, colors_paltform2, positions_platform2, box_normals);
    quad( 5, 4, 0, 1, 5, v_colors_platform2, v_positions_platform2, v_norms_platform2, colors_paltform2, positions_platform2, box_normals);

    tri_idx = 0;
    //platform 3
    quad( 1, 0, 3, 2, 0, v_colors_platform3, v_positions_platform3, v_norms_platform3, colors_paltform3, positions_platform3, box_normals);
    quad( 2, 3, 7, 6, 1, v_colors_platform3, v_positions_platform3, v_norms_platform3, colors_paltform3, positions_platform3, box_normals);
    quad( 3, 0, 4, 7, 2, v_colors_platform3, v_positions_platform3, v_norms_platform3, colors_paltform3, positions_platform3, box_normals);
    quad( 6, 5, 1, 2, 3, v_colors_platform3, v_positions_platform3, v_norms_platform3, colors_paltform3, positions_platform3, box_normals);
    quad( 4, 5, 6, 7, 4, v_colors_platform3, v_positions_platform3, v_norms_platform3, colors_paltform3, positions_platform3, box_normals);
    quad( 5, 4, 0, 1, 5, v_colors_platform3, v_positions_platform3, v_norms_platform3, colors_paltform3, positions_platform2, box_normals);

    tri_idx = 0;
    //draw the torso
    quad( 1, 0, 3, 2, 0, v_colors_torso, v_positions_torso, v_norms_torso, colors_torso, positions_torso, box_normals);
    quad( 2, 3, 7, 6, 1, v_colors_torso, v_positions_torso, v_norms_torso, colors_torso, positions_torso, box_normals);
    quad( 3, 0, 4, 7, 2, v_colors_torso, v_positions_torso, v_norms_torso, colors_torso, positions_torso, box_normals);
    quad( 6, 5, 1, 2, 3, v_colors_torso, v_positions_torso, v_norms_torso, colors_torso, positions_torso, box_normals);
    quad( 4, 5, 6, 7, 4, v_colors_torso, v_positions_torso, v_norms_torso, colors_torso, positions_torso, box_normals);
    quad( 5, 4, 0, 1, 5, v_colors_torso, v_positions_torso, v_norms_torso, colors_torso, positions_torso, box_normals);

    tri_idx = 0;
    //draw the shoe
    quad( 1, 0, 3, 2, 0, v_colors_shoe, v_positions_shoe, v_norms_shoe, colors_shoe, positions_shoe, box_normals);
    quad( 2, 3, 7, 6, 1, v_colors_shoe, v_positions_shoe, v_norms_shoe, colors_shoe, positions_shoe, box_normals);
    quad( 3, 0, 4, 7, 2, v_colors_shoe, v_positions_shoe, v_norms_shoe, colors_shoe, positions_shoe, box_normals);
    quad( 6, 5, 1, 2, 3, v_colors_shoe, v_positions_shoe, v_norms_shoe, colors_shoe, positions_shoe, box_normals);
    quad( 4, 5, 6, 7, 4, v_colors_shoe, v_positions_shoe, v_norms_shoe, colors_shoe, positions_shoe, box_normals);
    quad( 5, 4, 0, 1, 5, v_colors_shoe, v_positions_shoe, v_norms_shoe, colors_shoe, positions_shoe, box_normals);

    //eyes ss
    tri_idx = 0;
    quad( 1, 0, 3, 2, 0, v_colors_eyes_im, v_positions_eyes_im, v_norms_eyes_im, colors_eyes_im, positions_eyes_im, box_normals);
    quad( 2, 3, 7, 6, 1, v_colors_eyes_im, v_positions_eyes_im, v_norms_eyes_im, colors_eyes_im, positions_eyes_im, box_normals);
    quad( 3, 0, 4, 7, 2, v_colors_eyes_im, v_positions_eyes_im, v_norms_eyes_im, colors_eyes_im, positions_eyes_im, box_normals);
    quad( 6, 5, 1, 2, 3, v_colors_eyes_im, v_positions_eyes_im, v_norms_eyes_im, colors_eyes_im, positions_eyes_im, box_normals);
    quad( 4, 5, 6, 7, 4, v_colors_eyes_im, v_positions_eyes_im, v_norms_eyes_im, colors_eyes_im, positions_eyes_im, box_normals);
    quad( 5, 4, 0, 1, 5, v_colors_eyes_im, v_positions_eyes_im, v_norms_eyes_im, colors_eyes_im, positions_eyes_im, box_normals);

    //room
    tri_idx = 0;
    //draw the room 
    //with the new quad functiom
    textured_quad( 1, 0, 3, 2, 0, v_colors_walls, v_positions_walls, v_norms_walls,v_tex_walls, colors_room, positions_room, room_normals, t_coords);
    textured_quad( 2, 3, 7, 6, 1, v_colors_walls, v_positions_walls, v_norms_walls,v_tex_walls, colors_room, positions_room, room_normals, t_coords);
    textured_quad( 4, 5, 6, 7, 4, v_colors_walls, v_positions_walls, v_norms_walls,v_tex_walls, colors_room, positions_room, room_normals, t_coords);
    textured_quad( 5, 4, 0, 1, 5, v_colors_walls, v_positions_walls, v_norms_walls,v_tex_walls, colors_room, positions_room, room_normals, t_coords);

    // //room
    // tri_idx = 0;
    // //draw the room 
    // //with the new quad functiom
    // textured_quad( 1, 0, 3, 2, 0, v_colors_room, v_positions_room, v_norms_room,v_tex_room, colors_room, positions_room, room_normals, t_coords);
    // textured_quad( 2, 3, 7, 6, 1, v_colors_room, v_positions_room, v_norms_room,v_tex_room, colors_room, positions_room, room_normals, t_coords);
    // textured_quad( 3, 0, 4, 7, 4, v_colors_room, v_positions_room, v_norms_room,v_tex_room, colors_room, positions_room, room_normals, t_coords);
    // textured_quad( 6, 5, 1, 2, 5, v_colors_room, v_positions_room, v_norms_room,v_tex_room, colors_room, positions_room, room_normals, t_coords);
    // textured_quad( 4, 5, 6, 7, 4, v_colors_room, v_positions_room, v_norms_room,v_tex_room, colors_room, positions_room, room_normals, t_coords);
    // textured_quad( 5, 4, 0, 1, 5, v_colors_room, v_positions_room, v_norms_room,v_tex_room, colors_room, positions_room, room_normals, t_coords);

    //tabletop
    tri_idx = 0;
    //draw the tabletop
    //table top rendered via tex method
    textured_quad( 1, 0, 3, 2, 0, v_colors_tabletop2, v_positions_tabletop2, v_norms_tabletop2, v_tex_tabletop2, colors_tabletop, positions_tabletop, box_normals, t_coords);
    textured_quad( 2, 3, 7, 6, 1, v_colors_tabletop2, v_positions_tabletop2, v_norms_tabletop2, v_tex_tabletop2, colors_tabletop, positions_tabletop, box_normals, t_coords);
    textured_quad( 3, 0, 4, 7, 2, v_colors_tabletop2, v_positions_tabletop2, v_norms_tabletop2, v_tex_tabletop2, colors_tabletop, positions_tabletop, box_normals, t_coords);
    textured_quad( 6, 5, 1, 2, 3, v_colors_tabletop2, v_positions_tabletop2, v_norms_tabletop2, v_tex_tabletop2, colors_tabletop, positions_tabletop, box_normals, t_coords);
    textured_quad( 4, 5, 6, 7, 4, v_colors_tabletop2, v_positions_tabletop2, v_norms_tabletop2, v_tex_tabletop2, colors_tabletop, positions_tabletop, box_normals, t_coords);
    textured_quad( 5, 4, 0, 1, 5, v_colors_tabletop2, v_positions_tabletop2, v_norms_tabletop2, v_tex_tabletop2, colors_tabletop, positions_tabletop, box_normals, t_coords);

    //bed
    tri_idx = 0;
    //draw the bed
    textured_quad( 1, 0, 3, 2, 0, v_colors_bed, v_positions_bed, v_norms_bed, v_tex_bed, colors_bed, positions_bed, box_normals, t_coords);
    textured_quad( 2, 3, 7, 6, 1, v_colors_bed, v_positions_bed, v_norms_bed, v_tex_bed, colors_bed, positions_bed, box_normals, t_coords);
    textured_quad( 3, 0, 4, 7, 2, v_colors_bed, v_positions_bed, v_norms_bed, v_tex_bed, colors_bed, positions_bed, box_normals, t_coords);
    textured_quad( 6, 5, 1, 2, 3, v_colors_bed, v_positions_bed, v_norms_bed, v_tex_bed, colors_bed, positions_bed, box_normals, t_coords);
    textured_quad( 4, 5, 6, 7, 4, v_colors_bed, v_positions_bed, v_norms_bed, v_tex_bed, colors_bed, positions_bed, box_normals, t_coords);
    textured_quad( 5, 4, 0, 1, 5, v_colors_bed, v_positions_bed, v_norms_bed, v_tex_bed, colors_bed, positions_bed, box_normals, t_coords);

    //matress
    tri_idx = 0;
    //draw the matress
    textured_quad( 1, 0, 3, 2, 0, v_colors_mat, v_positions_mat, v_norms_bed, v_tex_mat, colors_mat, positions_mat, box_normals, t_coords);
    textured_quad( 2, 3, 7, 6, 1, v_colors_mat, v_positions_mat, v_norms_bed, v_tex_mat, colors_mat, positions_mat, box_normals, t_coords);
    textured_quad( 3, 0, 4, 7, 2, v_colors_mat, v_positions_mat, v_norms_bed, v_tex_mat, colors_mat, positions_mat, box_normals, t_coords);
    textured_quad( 6, 5, 1, 2, 3, v_colors_mat, v_positions_mat, v_norms_bed, v_tex_mat, colors_mat, positions_mat, box_normals, t_coords);
    textured_quad( 4, 5, 6, 7, 4, v_colors_mat, v_positions_mat, v_norms_bed, v_tex_mat, colors_mat, positions_mat, box_normals, t_coords);
    textured_quad( 5, 4, 0, 1, 5, v_colors_mat, v_positions_mat, v_norms_bed, v_tex_mat, colors_mat, positions_mat, box_normals, t_coords);

    //bed_support
    tri_idx = 0;
    //draw the bed
    textured_quad( 1, 0, 3, 2, 0, v_colors_bed_sprt, v_positions_bed_sprt, v_norms_bed_sprt, v_tex_bed_sprt, colors_bed_sprt, positions_bed_sprt, box_normals, t_coords);
    textured_quad( 2, 3, 7, 6, 1, v_colors_bed_sprt, v_positions_bed_sprt, v_norms_bed_sprt, v_tex_bed_sprt, colors_bed_sprt, positions_bed_sprt, box_normals, t_coords);
    textured_quad( 3, 0, 4, 7, 2, v_colors_bed_sprt, v_positions_bed_sprt, v_norms_bed_sprt, v_tex_bed_sprt, colors_bed_sprt, positions_bed_sprt, box_normals, t_coords);
    textured_quad( 6, 5, 1, 2, 3, v_colors_bed_sprt, v_positions_bed_sprt, v_norms_bed_sprt, v_tex_bed_sprt, colors_bed_sprt, positions_bed_sprt, box_normals, t_coords);
    textured_quad( 4, 5, 6, 7, 4, v_colors_bed_sprt, v_positions_bed_sprt, v_norms_bed_sprt, v_tex_bed_sprt, colors_bed_sprt, positions_bed_sprt, box_normals, t_coords);
    textured_quad( 5, 4, 0, 1, 5, v_colors_bed_sprt, v_positions_bed_sprt, v_norms_bed_sprt, v_tex_bed_sprt, colors_bed_sprt, positions_bed_sprt, box_normals, t_coords);

    //window
    tri_idx = 0;
    //draw the bed
    textured_quad( 1, 0, 3, 2, 0, v_colors_window, v_positions_window, v_norms_window, v_tex_window, colors_window, positions_window, box_normals, t_coords);
    textured_quad( 2, 3, 7, 6, 1, v_colors_window, v_positions_window, v_norms_window, v_tex_window, colors_window, positions_window, box_normals, t_coords);
    textured_quad( 3, 0, 4, 7, 2, v_colors_window, v_positions_window, v_norms_window, v_tex_window, colors_window, positions_window, box_normals, t_coords);
    textured_quad( 6, 5, 1, 2, 3, v_colors_window, v_positions_window, v_norms_window, v_tex_window, colors_window, positions_window, box_normals, t_coords);
    textured_quad( 4, 5, 6, 7, 4, v_colors_window, v_positions_window, v_norms_window, v_tex_window, colors_window, positions_window, box_normals, t_coords);
    textured_quad( 5, 4, 0, 1, 5, v_colors_window, v_positions_window, v_norms_window, v_tex_window, colors_window, positions_window, box_normals, t_coords);

    //stool top
    tri_idx = 0;
    //draw the stooltop
    quad( 1, 0, 3, 2, 0, v_colors_stooltop, v_positions_stooltop, v_norms_stooltop, colors_stooltop, positions_stooltop, box_normals);
    quad( 2, 3, 7, 6, 1, v_colors_stooltop, v_positions_stooltop, v_norms_stooltop, colors_stooltop, positions_stooltop, box_normals);
    quad( 3, 0, 4, 7, 2, v_colors_stooltop, v_positions_stooltop, v_norms_stooltop, colors_stooltop, positions_stooltop, box_normals);
    quad( 6, 5, 1, 2, 3, v_colors_stooltop, v_positions_stooltop, v_norms_stooltop, colors_stooltop, positions_stooltop, box_normals);
    quad( 4, 5, 6, 7, 4, v_colors_stooltop, v_positions_stooltop, v_norms_stooltop, colors_stooltop, positions_stooltop, box_normals);
    quad( 5, 4, 0, 1, 5, v_colors_stooltop, v_positions_stooltop, v_norms_stooltop, colors_stooltop, positions_stooltop, box_normals);

    //stool back
    tri_idx = 0;
    //draw the stooltop
    quad( 1, 0, 3, 2, 0, v_colors_stoolback, v_positions_stoolback, v_norms_stoolback, colors_stoolback, positions_stoolback, box_normals);
    quad( 2, 3, 7, 6, 1, v_colors_stoolback, v_positions_stoolback, v_norms_stoolback, colors_stoolback, positions_stoolback, box_normals);
    quad( 3, 0, 4, 7, 2, v_colors_stoolback, v_positions_stoolback, v_norms_stoolback, colors_stoolback, positions_stoolback, box_normals);
    quad( 6, 5, 1, 2, 3, v_colors_stoolback, v_positions_stoolback, v_norms_stoolback, colors_stoolback, positions_stoolback, box_normals);
    quad( 4, 5, 6, 7, 4, v_colors_stoolback, v_positions_stoolback, v_norms_stoolback, colors_stoolback, positions_stoolback, box_normals);
    quad( 5, 4, 0, 1, 5, v_colors_stoolback, v_positions_stoolback, v_norms_stoolback, colors_stoolback, positions_stoolback, box_normals);

    //door
    tri_idx = 0;
    //draw the door
    quad( 1, 0, 3, 2, 0, v_colors_door, v_positions_door, v_norms_door, colors_door, positions_door, box_normals);
    quad( 2, 3, 7, 6, 1, v_colors_door, v_positions_door, v_norms_door, colors_door, positions_door, box_normals);
    quad( 3, 0, 4, 7, 2, v_colors_door, v_positions_door, v_norms_door, colors_door, positions_door, box_normals);
    quad( 6, 5, 1, 2, 3, v_colors_door, v_positions_door, v_norms_door, colors_door, positions_door, box_normals);
    quad( 4, 5, 6, 7, 4, v_colors_door, v_positions_door, v_norms_door, colors_door, positions_door, box_normals);
    quad( 5, 4, 0, 1, 5, v_colors_door, v_positions_door, v_norms_door, colors_door, positions_door, box_normals);

    //cupboard
    tri_idx = 0;
    quad( 2, 3, 7, 6, 1, v_colors_cupboard, v_positions_cupboard, v_norms_cupboard, colors_cupboard, positions_cupboard, box_normals);
    quad( 3, 0, 4, 7, 2, v_colors_cupboard, v_positions_cupboard, v_norms_cupboard, colors_cupboard, positions_cupboard, box_normals);
    quad( 6, 5, 1, 2, 3, v_colors_cupboard, v_positions_cupboard, v_norms_cupboard, colors_cupboard, positions_cupboard, box_normals);
    quad( 4, 5, 6, 7, 4, v_colors_cupboard, v_positions_cupboard, v_norms_cupboard, colors_cupboard, positions_cupboard, box_normals);
    quad( 5, 4, 0, 1, 5, v_colors_cupboard, v_positions_cupboard, v_norms_cupboard, colors_cupboard, positions_cupboard, box_normals);

    // wall light
    tri_idx = 0;
    quad( 1, 0, 3, 2, 0, v_colors_wall_light, v_positions_wall_light, v_norms_wall_light, colors_wall_light, positions_wall_light, box_normals);
    quad( 2, 3, 7, 6, 1, v_colors_wall_light, v_positions_wall_light, v_norms_wall_light, colors_wall_light, positions_wall_light, box_normals);
    quad( 3, 0, 4, 7, 2, v_colors_wall_light, v_positions_wall_light, v_norms_wall_light, colors_wall_light, positions_wall_light, box_normals);
    quad( 6, 5, 1, 2, 3, v_colors_wall_light, v_positions_wall_light, v_norms_wall_light, colors_wall_light, positions_wall_light, box_normals);
    quad( 4, 5, 6, 7, 4, v_colors_wall_light, v_positions_wall_light, v_norms_wall_light, colors_wall_light, positions_wall_light, box_normals);
    quad( 5, 4, 0, 1, 5, v_colors_wall_light, v_positions_wall_light, v_norms_wall_light, colors_wall_light, positions_wall_light, box_normals);
}

//-----------------------------------------------------------------

void setBuffers(glm::vec4 v_positions[], glm::vec4 v_colors[], glm::vec2 v_tex[], glm::vec4 v_norms[], std::size_t v_size, std::size_t c_size, std::size_t tex_size, std::size_t norm_size)
{  
  glBufferData (GL_ARRAY_BUFFER, v_size + tex_size + norm_size, NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, v_size, v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, v_size, tex_size, v_tex);
  glBufferSubData( GL_ARRAY_BUFFER, v_size + tex_size, norm_size, v_norms );
  // set up vertex array
  //Position
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  //Textures

  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(v_size) );

  //Normal
  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(v_size + tex_size) );
}

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("07_vshader.glsl");
  std::string fragment_shader_file("07_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" );
  vNormal = glGetAttribLocation( shaderProgram, "vNormal" );
  cameraPosition = glGetAttribLocation(shaderProgram, "cameraPosition");
  texCoord = glGetAttribLocation( shaderProgram, "texCoord" );
  tex_or_color = glGetUniformLocation( shaderProgram, "tex_or_color" );
  light1_on = glGetUniformLocation( shaderProgram, "light1_on" );
  light2_on = glGetUniformLocation( shaderProgram, "light2_on" );

  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
  normalMatrix =  glGetUniformLocation( shaderProgram, "normalMatrix");
  viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");

  //Load texture
  // GLuint tex=LoadTexture("images/all1.bmp", 256, 256);
  // glBindTexture(GL_TEXTURE_2D, tex);

  glGenVertexArrays (10, vao);
  glGenBuffers (10, vbo);

  //wallls of the room
  glBindVertexArray (vao[0]);
  glBindBuffer (GL_ARRAY_BUFFER, vbo[0]);
  tri_idx = 0;
  draw_cubes();
  std::size_t room_v_size = sizeof(v_positions_walls);
  std::size_t room_c_size = sizeof(v_colors_walls);
  std::size_t room_tex_size = sizeof(v_tex_walls);
  std::size_t room_norm_size = sizeof(v_norms_walls);
  setBuffers(v_positions_walls, v_colors_walls, v_tex_walls, v_norms_walls, room_v_size, room_c_size, room_tex_size, room_norm_size);

  //floor of the room 
  glBindVertexArray (vao[1]);
  glBindBuffer (GL_ARRAY_BUFFER, vbo[1]);
  tri_idx = 0;
  textured_quad( 3, 0, 4, 7, 2, v_colors_floor, v_positions_floor, v_norms_floor,v_tex_floor, colors_room, positions_room, room_normals, t_coords);
  room_v_size = sizeof(v_positions_floor);
  room_c_size = sizeof(v_colors_floor);
  room_tex_size = sizeof(v_tex_floor);
  room_norm_size = sizeof(v_norms_floor);
  setBuffers(v_positions_floor, v_colors_floor, v_tex_floor, v_norms_floor, room_v_size, room_c_size, room_tex_size, room_norm_size);

  //ceil of the room 
  glBindVertexArray (vao[2]);
  glBindBuffer (GL_ARRAY_BUFFER, vbo[2]);
  tri_idx = 0;
  textured_quad( 6, 5, 1, 2, 2, v_colors_ceil, v_positions_ceil, v_norms_ceil,v_tex_ceil, colors_room, positions_room, room_normals, t_coords);
  room_v_size = sizeof(v_positions_ceil);
  room_c_size = sizeof(v_colors_ceil);
  room_tex_size = sizeof(v_tex_ceil);
  room_norm_size = sizeof(v_norms_ceil);
  setBuffers(v_positions_ceil, v_colors_ceil, v_tex_ceil, v_norms_ceil, room_v_size, room_c_size, room_tex_size, room_norm_size);

  //front of cupboard of the room 
  glBindVertexArray (vao[3]);
  glBindBuffer (GL_ARRAY_BUFFER, vbo[3]);
  tri_idx = 0;
  textured_quad( 1, 0, 3, 2, 0, v_colors_cupboard_front, v_positions_cupboard_front, v_norms_cupboard_front, v_tex_cupboard_front, colors_cupboard, positions_cupboard_front, box_normals, t_coords);
  room_v_size = sizeof(v_positions_cupboard_front);
  room_c_size = sizeof(v_colors_cupboard_front);
  room_tex_size = sizeof(v_tex_cupboard_front);
  room_norm_size = sizeof(v_norms_cupboard_front);
  setBuffers(v_positions_cupboard_front, v_colors_cupboard_front, v_tex_cupboard_front, v_norms_cupboard_front, room_v_size, room_c_size, room_tex_size, room_norm_size);

  //tabletop
  glBindVertexArray (vao[4]);
  glBindBuffer (GL_ARRAY_BUFFER, vbo[4]);
  tri_idx = 0;
  room_v_size = sizeof(v_positions_tabletop2);
  room_c_size = sizeof(v_colors_tabletop2);
  room_tex_size = sizeof(v_tex_tabletop2);
  room_norm_size = sizeof(v_norms_walls);
  setBuffers(v_positions_tabletop2, v_colors_tabletop2, v_tex_tabletop2, v_norms_tabletop2, room_v_size, room_c_size, room_tex_size, room_norm_size);

  //bed
  glBindVertexArray (vao[5]);
  glBindBuffer (GL_ARRAY_BUFFER, vbo[5]);
  tri_idx = 0;
  room_v_size = sizeof(v_positions_bed);
  room_c_size = sizeof(v_colors_bed);
  room_tex_size = sizeof(v_tex_bed);
  room_norm_size = sizeof(v_norms_bed);
  setBuffers(v_positions_bed, v_colors_bed, v_tex_bed, v_norms_bed, room_v_size, room_c_size, room_tex_size, room_norm_size);

  //mat
  glBindVertexArray (vao[6]);
  glBindBuffer (GL_ARRAY_BUFFER, vbo[6]);
  tri_idx = 0;
  room_v_size = sizeof(v_positions_mat);
  room_c_size = sizeof(v_colors_mat);
  room_tex_size = sizeof(v_tex_mat);
  room_norm_size = sizeof(v_norms_mat);
  setBuffers(v_positions_mat, v_colors_mat, v_tex_mat, v_norms_mat, room_v_size, room_c_size, room_tex_size, room_norm_size);

  //bed support
  glBindVertexArray (vao[7]);
  glBindBuffer (GL_ARRAY_BUFFER, vbo[7]);
  tri_idx = 0;
  room_v_size = sizeof(v_positions_bed_sprt);
  room_c_size = sizeof(v_colors_bed_sprt);
  room_tex_size = sizeof(v_tex_bed_sprt);
  room_norm_size = sizeof(v_norms_bed_sprt);
  setBuffers(v_positions_bed_sprt, v_colors_bed_sprt, v_tex_bed_sprt, v_norms_bed_sprt, room_v_size, room_c_size, room_tex_size, room_norm_size);

  //window
  glBindVertexArray (vao[8]);
  glBindBuffer (GL_ARRAY_BUFFER, vbo[8]);
  tri_idx = 0;
  room_v_size = sizeof(v_positions_window);
  room_c_size = sizeof(v_colors_window);
  room_tex_size = sizeof(v_tex_window);
  room_norm_size = sizeof(v_norms_window);
  setBuffers(v_positions_window, v_colors_window, v_tex_window, v_norms_window, room_v_size, room_c_size, room_tex_size, room_norm_size);
  // Creating the hierarchy:
  // We are using the original colorcube function to generate the vertices of the cuboid
  tri_idx = 0;
  cyd(face_radius, face_height, v_colors_face, v_positions_face, v_norms_face, face_col);
  tri_idx = 0;
  cyd(neck_radius, neck_height, v_colors_neck, v_positions_neck, v_norms_neck, neck_col);
  tri_idx = 0;
  sphere(hip_radius, tesselations, tesselations, v_colors_hip, v_positions_hip, v_norms_hip);
  tri_idx = 0;
  cyd(thigh_radius, thigh_height, v_colors_thigh, v_positions_thigh, v_norms_thigh, thigh_col);
  tri_idx = 0;  
  cyd(thigh_radius, thigh_height, v_colors_leg, v_positions_leg, v_norms_leg, leg_col);
  tri_idx = 0;  
  sphere(knee_radius, tesselations, tesselations, v_colors_knee, v_positions_knee, v_norms_knee);
  tri_idx = 0;
  cyd(arm_radius, arm_height, v_colors_arm, v_positions_arm, v_norms_arm, arm_col);
  tri_idx = 0;
  cyd(arm_radius, arm_height, v_colors_larm, v_positions_larm, v_norms_larm, red);
  tri_idx = 0;
  cyd(caplow_radius, caplow_height, v_colors_caplow, v_positions_caplow, v_norms_caplow, caplow_col);
  tri_idx = 0;
  cyd(capup_radius, capup_height, v_colors_capup, v_positions_capup, v_norms_capup, capup_col);
  tri_idx = 0;  
  sphere(hand_radius, tesselations, tesselations, v_colors_hand, v_positions_hand, v_norms_hand);
  tri_idx = 0;  
  cyd_flat(torso2_radius, torso2_height, v_colors_torso2, v_positions_torso2, v_norms_torso2, brown);
  tri_idx = 0;  
  shield(shield_radius, tesselations, tesselations, v_colors_shield, v_positions_shield, v_norms_shield);

  //Iron Man Renderring
  tri_idx = 0;
  cyd(torso_radius_im, torso_height_im, v_colors_torso_im, v_positions_torso_im, v_norms_torso_im, torso_col_im);
  tri_idx = 0;  
  hemi(face_radius_im, tesselations, tesselations, v_colors_face_im, v_positions_face_im, v_norms_face_im);
  tri_idx = 0;
  sphere(shoulder_radius_im, tesselations, tesselations, v_colors_shoulders_im, v_positions_shoulders_im, v_norms_shoulders_im);
  tri_idx = 0;
  cyd(arm_radius_im, arm_height_im, v_colors_arm_im, v_positions_arm_im, v_norms_arm_im, arm_col_im);
  tri_idx = 0;
  cyd(antenna_radius_im, antenna_height_im, v_colors_antenna_im, v_positions_antenna_im, v_norms_antenna_im, antenna_col_im);
  tri_idx = 0;
  cyd(heart_radius_im, heart_height_im, v_colors_heart_im, v_positions_heart_im, v_norms_heart_im, heart_col_im);
  tri_idx = 0;
  cyd(arm_radius_im, leg_height_im, v_colors_leg_im, v_positions_leg_im, v_norms_arm_im, arm_col_im);

  //Table
  tri_idx = 0;
  cyd(table_leg_radius, table_leg_height, v_colors_tableleg_bl, v_positions_tableleg_bl, v_norms_tableleg_bl, brown);
  tri_idx = 0;
  cyd(table_leg_radius, table_leg_height, v_colors_tableleg_br, v_positions_tableleg_br, v_norms_tableleg_br, brown);
  tri_idx = 0;
  cyd(table_leg_radius, table_leg_height, v_colors_tableleg_fl, v_positions_tableleg_fl, v_norms_tableleg_fl, brown);
  tri_idx = 0;
  cyd(table_leg_radius, table_leg_height, v_colors_tableleg_fr, v_positions_tableleg_fr, v_norms_tableleg_fr, brown);

  // Stool
  tri_idx = 0;
  cyd(stool_leg_radius, stool_leg_height, v_colors_stoolleg_bl, v_positions_stoolleg_bl, v_norms_stoolleg_bl, brown);
  tri_idx = 0;
  cyd(stool_leg_radius, stool_leg_height, v_colors_stoolleg_br, v_positions_stoolleg_br, v_norms_stoolleg_br, brown);
  tri_idx = 0;
  cyd(stool_leg_radius, stool_leg_height, v_colors_stoolleg_fl, v_positions_stoolleg_fl, v_norms_stoolleg_fl, brown);
  tri_idx = 0;
  cyd(stool_leg_radius, stool_leg_height, v_colors_stoolleg_fr, v_positions_stoolleg_fr, v_norms_stoolleg_fr, brown);
  
  //lamp  
  tri_idx = 0;
  cyd(table_leg_radius*.5, table_leg_height*.8, v_colors_lamp_sprt2, v_positions_lamp_sprt2, v_norms_lamp_sprt2, brown);
  tri_idx = 0;  
  sphere(lamp_radius*1.4, tesselations, tesselations, v_colors_lamp_sprt, v_positions_lamp_sprt, v_norms_lamp_sprt);
  tri_idx = 0;  
  lamp(lamp_radius, tesselations, tesselations, v_colors_lamp, v_positions_lamp, v_norms_lamp);

  //onclick sphere
  tri_idx = 0;
  sphere(onclick_radius, tesselations, tesselations, v_colors_onclick, v_positions_onclick, v_norms_onclick);

  //onclick sphere
  node_onclick = new csX75::HNode(NULL,num_vertices_cyd,v_positions_onclick,v_colors_onclick, v_norms_onclick, v_tex_room, sizeof(v_norms_onclick),sizeof(v_tex_room),sizeof(v_positions_onclick),sizeof(v_colors_onclick), 0);
  node_onclick->change_parameters(c_xpos + lookat_point[0] , c_ypos + lookat_point[1],c_zpos + lookat_point[2],0.0,0,0.0);

  //beizer clicks cubes

  // ROOM
  float room_z = 2.0;
  // node_room = new csX75::HNode(NULL,num_vertices,v_positions_room,v_colors_room, v_norms_room, v_tex_room, sizeof(v_norms_room),sizeof(v_tex_room), sizeof(v_positions_room),sizeof(v_colors_room), 0);
  // curr_node = node_room;
  // node_room->change_parameters(0, 0.0, 0.0, 0, 0, 0);

  node_door = new csX75::HNode(NULL,num_vertices,v_positions_door,v_colors_door,v_norms_room, v_tex_room, sizeof(v_norms_room),sizeof(v_tex_room),sizeof(v_positions_door),sizeof(v_colors_door), 0);
  node_door->change_parameters(room_size_var, -room_size_height + door_height/2, room_z, 0, 90, 0);

  // node_window = new csX75::HNode(NULL,num_vertices,v_positions_window,v_colors_window,v_norms_room, v_tex_room, sizeof(v_norms_room),sizeof(v_tex_room),sizeof(v_positions_window),sizeof(v_colors_window), 0);
  // node_window->change_parameters(-room_size_var + window_depth/2, 1.0, -2.0, 0, -90, 0);

  node_cupboard = new csX75::HNode(NULL,num_vertices,v_positions_cupboard,v_colors_cupboard,v_norms_room, v_tex_room, sizeof(v_norms_room),sizeof(v_tex_room),sizeof(v_positions_cupboard),sizeof(v_colors_cupboard), 0);
  node_cupboard->change_parameters(-room_size_var + cupboard_depth/2, -room_size_height + cupboard_height/2, 5.0, 0, -90, 0);

  node_wall_light = new csX75::HNode(NULL,num_vertices,v_positions_wall_light,v_colors_wall_light,v_norms_room, v_tex_room, sizeof(v_norms_room),sizeof(v_tex_room),sizeof(v_positions_wall_light),sizeof(v_colors_wall_light), 0);
  node_wall_light->change_parameters(0, 7, -10, 0, 0, 0);

  // TABLE
  node_tabletop = new csX75::HNode(NULL,num_vertices,v_positions_tabletop,v_colors_tabletop,v_norms_tabletop, v_tex_room, sizeof(v_norms_tabletop),sizeof(v_tex_room),sizeof(v_positions_tabletop),sizeof(v_colors_tabletop), 0);
  node_tabletop->change_parameters(-room_size_var + table_width, -room_size_height + table_leg_height, - room_size_var + table_depth, 0, 0, 0);
  node_tableleg_bl = new csX75::HNode(node_tabletop,num_vertices_cyd,v_positions_tableleg_bl,v_colors_tableleg_bl,v_norms_tableleg_bl, v_tex_room, sizeof(v_norms_tableleg_bl),sizeof(v_tex_room),sizeof(v_positions_tableleg_bl),sizeof(v_colors_tableleg_bl), 0);
  node_tableleg_bl->change_parameters(-table_width + table_leg_radius, -table_leg_height/2, -table_depth + table_leg_radius, 0, 0, 0);
  node_tableleg_br = new csX75::HNode(node_tabletop,num_vertices_cyd,v_positions_tableleg_br,v_colors_tableleg_br,v_norms_tableleg_br, v_tex_room, sizeof(v_norms_tableleg_br),sizeof(v_tex_room),sizeof(v_positions_tableleg_br),sizeof(v_colors_tableleg_br), 0);
  node_tableleg_br->change_parameters(table_width - table_leg_radius, -table_leg_height/2, -table_depth + table_leg_radius, 0, 0, 0);
  node_tableleg_fl = new csX75::HNode(node_tabletop,num_vertices_cyd,v_positions_tableleg_fl,v_colors_tableleg_fl,v_norms_tableleg_fl, v_tex_room, sizeof(v_norms_tableleg_fl),sizeof(v_tex_room),sizeof(v_positions_tableleg_fl),sizeof(v_colors_tableleg_fl), 0);
  node_tableleg_fl->change_parameters(-table_width + table_leg_radius, -table_leg_height/2, table_depth - table_leg_radius, 0, 0, 0);
  node_tableleg_fr = new csX75::HNode(node_tabletop,num_vertices_cyd,v_positions_tableleg_fr,v_colors_tableleg_fr,v_norms_tableleg_fr, v_tex_room, sizeof(v_norms_tableleg_fr),sizeof(v_tex_room),sizeof(v_positions_tableleg_fr),sizeof(v_colors_tableleg_fr), 0);
  node_tableleg_fr->change_parameters(table_width - table_leg_radius, -table_leg_height/2, table_depth - table_leg_radius, 0, 0, 0);

  //STOOL
  node_stooltop = new csX75::HNode(NULL,num_vertices,v_positions_stooltop,v_colors_stooltop,v_norms_stooltop, v_tex_room, sizeof(v_norms_stooltop),sizeof(v_tex_room),sizeof(v_positions_stooltop),sizeof(v_colors_stooltop), 0);
  node_stooltop->change_parameters(-7, -room_size_height + stool_leg_height, -2, 0, -45, 0);
  node_stoolleg_bl = new csX75::HNode(node_stooltop,num_vertices_cyd,v_positions_stoolleg_bl,v_colors_stoolleg_bl,v_norms_stoolleg_bl, v_tex_room, sizeof(v_norms_stoolleg_bl),sizeof(v_tex_room),sizeof(v_positions_stoolleg_bl),sizeof(v_colors_stoolleg_bl), 0);
  node_stoolleg_bl->change_parameters(-stool_width + stool_leg_radius, -stool_leg_height/2, -stool_depth + stool_leg_radius, 0, 0, 0);
  node_stoolleg_br = new csX75::HNode(node_stooltop,num_vertices_cyd,v_positions_stoolleg_br,v_colors_stoolleg_br,v_norms_stoolleg_br, v_tex_room, sizeof(v_norms_stoolleg_br),sizeof(v_tex_room),sizeof(v_positions_stoolleg_br),sizeof(v_colors_stoolleg_br), 0);
  node_stoolleg_br->change_parameters(stool_width - stool_leg_radius, -stool_leg_height/2, -stool_depth + stool_leg_radius, 0, 0, 0);
  node_stoolleg_fl = new csX75::HNode(node_stooltop,num_vertices_cyd,v_positions_stoolleg_fl,v_colors_stoolleg_fl,v_norms_stoolleg_fl, v_tex_room, sizeof(v_norms_stoolleg_fl),sizeof(v_tex_room),sizeof(v_positions_stoolleg_fl),sizeof(v_colors_stoolleg_fl), 0);
  node_stoolleg_fl->change_parameters(-stool_width + stool_leg_radius, -stool_leg_height/2, stool_depth - stool_leg_radius, 0, 0, 0);
  node_stoolleg_fr = new csX75::HNode(node_stooltop,num_vertices_cyd,v_positions_stoolleg_fr,v_colors_stoolleg_fr,v_norms_stoolleg_fr, v_tex_room, sizeof(v_norms_stoolleg_fr),sizeof(v_tex_room),sizeof(v_positions_stoolleg_fr),sizeof(v_colors_stoolleg_fr), 0);
  node_stoolleg_fr->change_parameters(stool_width - stool_leg_radius, -stool_leg_height/2, stool_depth - stool_leg_radius, 0, 0, 0);
  node_stoolback = new csX75::HNode(node_stooltop,num_vertices,v_positions_stoolback,v_colors_stoolback,v_norms_stoolback, v_tex_room, sizeof(v_norms_stoolback),sizeof(v_tex_room),sizeof(v_positions_stoolback),sizeof(v_colors_stoolback), 0);
  node_stoolback->change_parameters(0, stoolback_height/2 + 0.5, stool_depth, 0, 0, 0);
  //note that the buffers are initialized in the respective constructors
 
  
  node_lamp_sprt2 = new csX75::HNode(node_tabletop,num_vertices_cyd,v_positions_lamp_sprt2,v_colors_lamp_sprt2,v_norms_lamp_sprt2, v_tex_room, sizeof(v_norms_lamp_sprt2),sizeof(v_tex_room),sizeof(v_positions_lamp_sprt2),sizeof(v_colors_lamp_sprt2), 0);
  node_lamp_sprt2->change_parameters(3,2,-1,0.0,-90,0.0);
  node_lamp_sprt = new csX75::HNode(node_lamp_sprt2,num_vertices_cyd,v_positions_lamp_sprt,v_colors_lamp_sprt,v_norms_lamp_sprt, v_tex_room, sizeof(v_norms_lamp_sprt),sizeof(v_tex_room),sizeof(v_positions_lamp_sprt),sizeof(v_colors_lamp_sprt), 0);
  node_lamp_sprt->change_parameters(0,table_leg_height*.4,0.0,0.0,0,0.0);
  node_lamp = new csX75::HNode(node_lamp_sprt,num_vertices_cyd,v_positions_lamp,v_colors_lamp, v_norms_lamp, v_tex_room, sizeof(v_norms_lamp),sizeof(v_tex_room),sizeof(v_positions_lamp),sizeof(v_colors_lamp), 1);
  node_lamp->change_parameters(shield_radius/2,0,0.0,45.0,45,10.0);

  node_box = new csX75::HNode(node_tabletop,num_vertices_box,v_positions_box,v_colors_box,v_norms_box, v_tex_room, sizeof(v_norms_box),sizeof(v_tex_room),sizeof(v_positions_box),sizeof(v_colors_box), 0);
  node_box->change_parameters(0, (size_var+2)/2.0,0,0.0,0.0,0);
  node_lid = new csX75::HNode(node_box,num_vertices,v_positions_lid,v_colors_lid, v_norms_lid, v_tex_room, sizeof(v_norms_lid),sizeof(v_tex_room),sizeof(v_positions_lid),sizeof(v_colors_lid), 0);
  node_lid->change_parameters(0.0,top_lid,-top_lid,0.0,0.0,0);
  node_lid->add_rotation_limits(-120.0, 0, 0, 0, 0, 0);
  node_platform1 = new csX75::HNode(node_box,num_vertices,v_positions_platform1,v_colors_platform1, v_norms_platform1, v_tex_room, sizeof(v_norms_platform1),sizeof(v_tex_room),sizeof(v_positions_platform1),sizeof(v_colors_platform1), 0);
  node_platform1->change_parameters(0.0,-0.8,0,0.0,0.0,0);
  // node_platform2 = new csX75::HNode(node_box,num_vertices,v_positions_platform2,v_colors_platform2,v_norms_platform2, v_tex_room, sizeof(v_norms_platform2),sizeof(v_tex_room),sizeof(v_positions_platform2),sizeof(v_colors_platform2), 0);
  // node_platform2->change_parameters(0.0,0,0,0.0,0.0,0);
  // node_platform3 = new csX75::HNode(node_box,num_vertices,v_positions_platform3,v_colors_platform3, v_norms_platform3, v_tex_room, sizeof(v_norms_platform3),sizeof(v_tex_room),sizeof(v_positions_platform3),sizeof(v_colors_platform3), 0);
  // node_platform3->change_parameters(0.0,0,0,0.0,0.0,0);


  //HUMAN CAPTAIN AMERICA
  //FOR BENDING
  node_torso2 = new csX75::HNode(node_platform1,num_vertices_cyd,v_positions_torso2,v_colors_torso2,v_norms_torso2, v_tex_room, sizeof(v_norms_torso2),sizeof(v_tex_room),sizeof(v_positions_torso2),sizeof(v_colors_torso2), 0);
  // node_torso2->change_parameters(-0.5,torso2_height + 2*thigh_height,0,0,0,0.0);
  node_torso2->change_parameters(0.0,torso2_height + 2*thigh_height,0.0,0,0,0.0);
  root_node = curr_node = node_torso2;
  
  float torso2_overlap_ratio = 0.3;

  node_torso = new csX75::HNode(node_torso2,num_vertices,v_positions_torso,v_colors_torso, v_norms_torso, v_tex_room, sizeof(v_norms_torso),sizeof(v_tex_room),sizeof(v_positions_torso),sizeof(v_colors_torso), 1);
  node_torso->change_parameters(0, torso2_overlap_ratio * torso2_radius ,0.0,0.0,0,0.0);
  node_torso->add_rotation_limits(-20.0, 90.0, 0, 0, 0.0, 0.0);

  

  node_neck = new csX75::HNode(node_torso,num_vertices_cyd,v_positions_neck,v_colors_neck, v_norms_neck, v_tex_room, sizeof(v_norms_room),sizeof(v_tex_room),sizeof(v_positions_neck),sizeof(v_colors_neck), 0);
  node_neck->change_parameters(0, torso_height + neck_height/2 - neck_extra_hidden,0.0,0.0,0,0.0);
  node_neck->add_rotation_limits(-30.0, 45.0, -30, 30, -30.0, 30.0);

  node_face = new csX75::HNode(node_neck,num_vertices_cyd,v_positions_face,v_colors_face,v_norms_face, v_tex_room, sizeof(v_norms_face),sizeof(v_tex_room),sizeof(v_positions_face),sizeof(v_colors_face), 0);
  node_face->change_parameters(0,neck_height/2 + face_height/2,0.0,0.0,0,0.0);
  node_caplow = new csX75::HNode(node_face,num_vertices_cyd,v_positions_caplow,v_colors_caplow,v_norms_caplow, v_tex_room, sizeof(v_norms_caplow),sizeof(v_tex_room),sizeof(v_positions_caplow),sizeof(v_colors_caplow), 0);
  node_caplow->change_parameters(0, face_height/2 + caplow_height/2,0.0,0.0,0,0.0);
  node_capup = new csX75::HNode(node_caplow,num_vertices_cyd,v_positions_capup,v_colors_capup, v_norms_capup, v_tex_room, sizeof(v_norms_capup),sizeof(v_tex_room),sizeof(v_positions_capup),sizeof(v_colors_capup), 0);
  node_capup->change_parameters(0, caplow_height/2 + capup_height/2,0.0,0.0,0,0.0);
   
  float hip_overlap_ratio = 0.1;
  float knee_overlap_ratio = 0.5, elbow_overlap_ratio = 0.5, hand_overlap_ratio = 0.3;
  node_hip_left = new csX75::HNode(node_torso2,num_vertices_cyd,v_positions_hip,v_colors_hip, v_norms_hip, v_tex_room, sizeof(v_norms_hip),sizeof(v_tex_room),sizeof(v_positions_hip),sizeof(v_colors_hip), 0);
  node_hip_left->change_parameters(-torso_width*0.3 , -hip_overlap_ratio*hip_radius - torso2_radius,0.0,0.0,0,0.0);
  node_hip_left->add_rotation_limits(-90.0, 45.0, -180, 180, -45.0, 30.0);
  node_hip_right = new csX75::HNode(node_torso2,num_vertices_cyd,v_positions_hip,v_colors_hip, v_norms_hip, v_tex_room, sizeof(v_norms_hip),sizeof(v_tex_room),sizeof(v_positions_hip),sizeof(v_colors_hip), 0);
  node_hip_right->change_parameters( torso_width*0.30 , -hip_overlap_ratio*hip_radius - torso2_radius,0.0,0.0,0,0.0); 
  node_hip_right->add_rotation_limits(-90.0, 45.0, -180, 180, -30, 45.0);

  node_thigh_left = new csX75::HNode(node_hip_left,num_vertices_cyd,v_positions_thigh,v_colors_thigh, v_norms_thigh, v_tex_room, sizeof(v_norms_thigh),sizeof(v_tex_room),sizeof(v_positions_thigh),sizeof(v_colors_thigh), 0);
  node_thigh_left->change_parameters(0, - .5*hip_radius - thigh_height/2 ,0.0,0.0,0,0.0);
  node_thigh_right = new csX75::HNode(node_hip_right,num_vertices_cyd,v_positions_thigh,v_colors_thigh, v_norms_thigh, v_tex_room, sizeof(v_norms_thigh),sizeof(v_tex_room),sizeof(v_positions_thigh),sizeof(v_colors_thigh), 0);
  node_thigh_right->change_parameters(0, - .5*hip_radius - thigh_height/2 ,0.0,0.0,0,0.0);

  node_knee_left = new csX75::HNode(node_thigh_left,num_vertices_cyd,v_positions_knee,v_colors_knee, v_norms_knee, v_tex_room, sizeof(v_norms_knee),sizeof(v_tex_room),sizeof(v_positions_knee),sizeof(v_colors_knee), 0);
  node_knee_left->change_parameters(0,-thigh_height/2 - knee_overlap_ratio*knee_radius ,0.0,0.0,0,0.0);
  node_knee_left->add_rotation_limits(0.0, 135.0, 0, 0, 0.0, 0.0);
  node_knee_right = new csX75::HNode(node_thigh_right,num_vertices_cyd,v_positions_knee,v_colors_knee, v_norms_knee, v_tex_room, sizeof(v_norms_knee),sizeof(v_tex_room),sizeof(v_positions_knee),sizeof(v_colors_knee), 0);
  node_knee_right->change_parameters(0,-thigh_height/2 - knee_overlap_ratio*knee_radius ,0.0,0.0,0,0.0);
  node_knee_right->add_rotation_limits(0.0, 135.0, 0, 0, 0.0, 0.0);

  node_leg_left = new csX75::HNode(node_knee_left,num_vertices_cyd,v_positions_leg,v_colors_leg, v_norms_leg, v_tex_room, sizeof(v_norms_leg),sizeof(v_tex_room),sizeof(v_positions_leg),sizeof(v_colors_leg), 0);
  node_leg_left->change_parameters(0, - knee_overlap_ratio*knee_radius - thigh_height/2 ,0.0,0.0,0,0.0);
  node_leg_right = new csX75::HNode(node_knee_right,num_vertices_cyd,v_positions_leg,v_colors_leg, v_norms_leg, v_tex_room, sizeof(v_norms_leg),sizeof(v_tex_room),sizeof(v_positions_leg),sizeof(v_colors_leg), 0);
  node_leg_right->change_parameters(0, - knee_overlap_ratio*knee_radius - thigh_height/2,0.0,0.0,0,0.0);

  // node_shoe_left = new csX75::HNode(node_leg_left,num_vertices,v_positions_shoe,v_colors_shoe, v_norms_shoe, v_tex_room, sizeof(v_norms_shoe),sizeof(v_tex_room),sizeof(v_positions_shoe),sizeof(v_colors_shoe), 0);
  // node_shoe_left->change_parameters(0,-thigh_height/2 -shoe_height/2 ,0.0,0.0,0,0.0);
  // node_shoe_right = new csX75::HNode(node_leg_right,num_vertices,v_positions_shoe,v_colors_shoe, v_norms_shoe, v_tex_room, sizeof(v_norms_shoe),sizeof(v_tex_room),sizeof(v_positions_shoe),sizeof(v_colors_shoe), 0);
  // node_shoe_right->change_parameters(0,-thigh_height/2 -shoe_height/2 ,0.0,0.0,0,0.0);
 

  node_shoulder_left = new csX75::HNode(node_torso,num_vertices_cyd,v_positions_hip,v_colors_hip, v_norms_hip, v_tex_room, sizeof(v_norms_hip),sizeof(v_tex_room),sizeof(v_positions_hip),sizeof(v_colors_hip), 0);
  node_shoulder_left->change_parameters(-torso_width/2 - .6*hip_radius, torso_height - hip_radius ,0.0,-30.0,0.0,-10.0);
  node_shoulder_left->add_rotation_limits(-180.0, 30.0, -180, 180, -180, 180.0);
  node_shoulder_right = new csX75::HNode(node_torso,num_vertices_cyd,v_positions_hip,v_colors_hip,v_norms_hip, v_tex_room, sizeof(v_norms_hip),sizeof(v_tex_room),sizeof(v_positions_hip),sizeof(v_colors_hip), 0);
  node_shoulder_right->change_parameters(torso_width/2 + .6*hip_radius, torso_height - hip_radius,0.0,0.0,0,0.0);
  node_shoulder_right->add_rotation_limits(-180.0, 30.0, -180, 180, -180, 180.0);
  
  node_uarm_left = new csX75::HNode(node_shoulder_left,num_vertices_cyd,v_positions_arm,v_colors_arm,v_norms_arm, v_tex_room, sizeof(v_norms_arm),sizeof(v_tex_room),sizeof(v_positions_arm),sizeof(v_colors_arm), 0);
  node_uarm_left->change_parameters(0, - .9*hip_radius - arm_height/2 ,0.0,0.0,0,0.0);
  node_uarm_right = new csX75::HNode(node_shoulder_right,num_vertices_cyd,v_positions_arm,v_colors_arm, v_norms_arm, v_tex_room, sizeof(v_norms_arm),sizeof(v_tex_room),sizeof(v_positions_arm),sizeof(v_colors_arm), 0);
  node_uarm_right->change_parameters(0, - .9*hip_radius - arm_height/2 ,0.0,0.0,0,0.0);

  node_elbow_left = new csX75::HNode(node_uarm_left,num_vertices_cyd,v_positions_knee,v_colors_knee, v_norms_knee, v_tex_room, sizeof(v_norms_knee),sizeof(v_tex_room),sizeof(v_positions_knee),sizeof(v_colors_knee), 0);
  node_elbow_left->change_parameters(0,-arm_height/2 - elbow_overlap_ratio*knee_radius ,0.0,0.0,0,0.0);
  node_elbow_left->add_rotation_limits(-150.0, 0, 0, 0, 0, 0);
  node_elbow_right = new csX75::HNode(node_uarm_right,num_vertices_cyd,v_positions_knee,v_colors_knee, v_norms_knee, v_tex_room, sizeof(v_norms_knee),sizeof(v_tex_room),sizeof(v_positions_knee),sizeof(v_colors_knee), 0);
  node_elbow_right->change_parameters(0,-arm_height/2 - elbow_overlap_ratio*knee_radius ,0.0,0.0,0,0.0);
  node_elbow_right->add_rotation_limits(-150.0, 0, 0, 0, 0, 0);

  node_larm_left = new csX75::HNode(node_elbow_left,num_vertices_cyd,v_positions_larm,v_colors_larm, v_norms_larm, v_tex_room, sizeof(v_norms_larm),sizeof(v_tex_room),sizeof(v_positions_larm),sizeof(v_colors_larm), 0);
  node_larm_left->change_parameters(0, - elbow_overlap_ratio*knee_radius - arm_height/2 ,0.0,0.0,0,0.0);
  node_larm_right = new csX75::HNode(node_elbow_right,num_vertices_cyd,v_positions_larm,v_colors_larm, v_norms_larm, v_tex_room, sizeof(v_norms_larm),sizeof(v_tex_room),sizeof(v_positions_larm),sizeof(v_colors_larm), 0);
  node_larm_right->change_parameters(0, - elbow_overlap_ratio*knee_radius - arm_height/2,0.0,0.0,0,0.0);


  node_hand_left = new csX75::HNode(node_larm_left,num_vertices_cyd,v_positions_hand,v_colors_hand, v_norms_hand, v_tex_room, sizeof(v_norms_hand),sizeof(v_tex_room),sizeof(v_positions_hand),sizeof(v_colors_hand), 0);
  node_hand_left->change_parameters(0,-arm_height/2 - hand_overlap_ratio*hand_radius ,0.0,0.0,0,0.0);
  node_hand_right = new csX75::HNode(node_larm_right,num_vertices_cyd,v_positions_hand,v_colors_hand,v_norms_hand, v_tex_room, sizeof(v_norms_hand),sizeof(v_tex_room),sizeof(v_positions_hand),sizeof(v_colors_hand), 0);
  node_hand_right->change_parameters(0,-arm_height/2 - hand_overlap_ratio*hand_radius ,0.0,0.0,0,0.0);

  node_shield = new csX75::HNode(node_hand_left,num_vertices_cyd,v_positions_shield,v_colors_shield, v_norms_shield, v_tex_room, sizeof(v_norms_shield),sizeof(v_tex_room),sizeof(v_positions_shield),sizeof(v_colors_shield), 1);
  node_shield->change_parameters(0,0,0.0,90.0,0,0.0);


  // IRONMAN
  node_torso_im = new csX75::HNode(node_platform1, num_vertices_cyd, v_positions_torso_im, v_colors_torso_im, v_norms_torso_im, v_tex_room, sizeof(v_norms_torso_im),sizeof(v_tex_room), sizeof(v_positions_torso_im), sizeof(v_colors_torso_im), 0);
  node_torso_im->change_parameters(-1.5, torso_height_im + leg_height_im, 0, 0, 0, 0);

  node_heart_im = new csX75::HNode(node_torso_im,num_vertices_cyd,v_positions_heart_im,v_colors_heart_im, v_norms_heart_im, v_tex_room, sizeof(v_norms_heart_im),sizeof(v_tex_room),sizeof(v_positions_heart_im),sizeof(v_colors_heart_im), 0);
  node_heart_im->change_parameters(0 , .5 * torso_height_im/2 ,torso_radius_im + heart_height_im/2,-90.0,0,0.0);

  node_face_im = new csX75::HNode(node_torso_im,num_vertices_cyd,v_positions_face_im,v_colors_face_im, v_norms_face_im, v_tex_room, sizeof(v_norms_face_im),sizeof(v_tex_room),sizeof(v_positions_face_im),sizeof(v_colors_face_im), 0);
  node_face_im->change_parameters(0,torso_height_im/2 + neck_height_im,0.0,0.0,0.0,0.0);
  node_face_im->add_rotation_limits(0.0, 0.0, -180, 180, 0, 0);

  node_leyes_im = new csX75::HNode(node_face_im, num_vertices, v_positions_eyes_im, v_colors_eyes_im, v_norms_eyes_im, v_tex_room, sizeof(v_norms_eyes_im),sizeof(v_tex_room),sizeof(v_positions_eyes_im), sizeof(v_colors_eyes_im), 0);
  node_leyes_im->change_parameters(- .3 * face_radius_im , .55* face_radius_im , .75*face_radius_im, 0, 0, 0);
  node_reyes_im = new csX75::HNode(node_face_im, num_vertices, v_positions_eyes_im, v_colors_eyes_im, v_norms_eyes_im, v_tex_room, sizeof(v_norms_eyes_im),sizeof(v_tex_room), sizeof(v_positions_eyes_im), sizeof(v_colors_eyes_im), 0);
  node_reyes_im->change_parameters( .3 * face_radius_im , .55* face_radius_im , .75*face_radius_im, 0, 0, 0);

  node_antenna1_im = new csX75::HNode(node_face_im,num_vertices_cyd,v_positions_antenna_im,v_colors_antenna_im, v_norms_antenna_im, v_tex_room, sizeof(v_norms_antenna_im),sizeof(v_tex_room),sizeof(v_positions_antenna_im),sizeof(v_colors_antenna_im), 0);
  node_antenna1_im->change_parameters(face_radius_im * cos(PI/4) + antenna_height_im/3, face_radius_im * cos(PI/4) + antenna_height_im/3,0.0,0.0,0,-45.0);
  node_antenna2_im = new csX75::HNode(node_face_im,num_vertices_cyd,v_positions_antenna_im,v_colors_antenna_im,v_norms_antenna_im, v_tex_room, sizeof(v_norms_antenna_im),sizeof(v_tex_room),sizeof(v_positions_antenna_im),sizeof(v_colors_antenna_im), 0);
  node_antenna2_im->change_parameters(- face_radius_im * cos(PI/4) - antenna_height_im/3, face_radius_im * cos(PI/4) + antenna_height_im/3,0.0,0.0,0,45.0);

  node_shoulder_left_im = new csX75::HNode(node_torso_im,num_vertices_cyd,v_positions_shoulders_im,v_colors_shoulders_im, v_norms_shoulders_im, v_tex_room, sizeof(v_norms_shoulders_im),sizeof(v_tex_room),sizeof(v_positions_shoulders_im),sizeof(v_colors_shoulders_im), 0);
  node_shoulder_left_im->change_parameters(-torso_radius_im - shoulders_width_extra_im, torso_height_im/4 + shoulders_height_offset_im,0.0,0.0,0,0.0);
  node_shoulder_left_im->add_rotation_limits(-180.0, 180.0, 0, 0, -45.0, 30.0);
  node_shoulder_right_im = new csX75::HNode(node_torso_im,num_vertices_cyd,v_positions_shoulders_im,v_colors_shoulders_im, v_norms_shoulders_im, v_tex_room, sizeof(v_norms_shoulders_im),sizeof(v_tex_room),sizeof(v_positions_shoulders_im),sizeof(v_colors_shoulders_im), 0);
  node_shoulder_right_im->change_parameters( torso_radius_im + shoulders_width_extra_im, torso_height_im/4 + shoulders_height_offset_im,0.0,0.0,0,0.0); 
  node_shoulder_right_im->add_rotation_limits(-180.0, 180.0, 0, 0, -30, 45.0);

  node_arm_left_im = new csX75::HNode(node_shoulder_left_im,num_vertices_cyd,v_positions_arm_im,v_colors_arm_im, v_norms_arm_im, v_tex_room, sizeof(v_norms_arm_im),sizeof(v_tex_room),sizeof(v_positions_arm_im),sizeof(v_colors_arm_im), 0);
  node_arm_left_im->change_parameters(0, - .9*shoulder_radius_im - arm_height_im/2 ,0.0,0.0,0,0.0);
  node_arm_right_im = new csX75::HNode(node_shoulder_right_im,num_vertices_cyd,v_positions_arm_im,v_colors_arm_im, v_norms_arm_im, v_tex_room, sizeof(v_norms_arm_im),sizeof(v_tex_room),sizeof(v_positions_arm_im),sizeof(v_colors_arm_im), 0);
  node_arm_right_im->change_parameters(0, - .9*shoulder_radius_im - arm_height_im/2 ,0.0,0.0,0,0.0);

  node_hip_left_im = new csX75::HNode(node_torso_im,num_vertices_cyd,v_positions_shoulders_im,v_colors_shoulders_im, v_norms_shoulders_im, v_tex_room, sizeof(v_norms_shoulders_im),sizeof(v_tex_room),sizeof(v_positions_shoulders_im),sizeof(v_colors_shoulders_im), 0);
  node_hip_left_im->change_parameters(- 0.5 * torso_radius_im , -torso_height_im/2 + shoulder_radius_im ,0.0,0.0,0,0.0);
  node_hip_left_im->add_rotation_limits(-90.0, 45.0, 0, 0, -45.0, 30.0);
  node_hip_right_im = new csX75::HNode(node_torso_im,num_vertices_cyd,v_positions_shoulders_im,v_colors_shoulders_im, v_norms_shoulders_im, v_tex_room, sizeof(v_norms_shoulders_im),sizeof(v_tex_room),sizeof(v_positions_shoulders_im),sizeof(v_colors_shoulders_im), 0);
  node_hip_right_im->change_parameters( 0.5 * torso_radius_im , -torso_height_im/2 + shoulder_radius_im ,0.0,0.0,0,0.0);
  node_hip_right_im->add_rotation_limits(-90.0, 45.0, 0, 0, -45.0, 30.0);

  node_leg_left_im = new csX75::HNode(node_hip_left_im,num_vertices_cyd,v_positions_leg_im,v_colors_leg_im, v_norms_leg_im, v_tex_room, sizeof(v_norms_leg_im),sizeof(v_tex_room),sizeof(v_positions_leg_im),sizeof(v_colors_leg_im), 0);
  node_leg_left_im->change_parameters(0, - .9*shoulder_radius_im - arm_height_im/2 ,0.0,0.0,0,0.0);
  node_leg_right_im = new csX75::HNode(node_hip_right_im,num_vertices_cyd,v_positions_leg_im,v_colors_leg_im, v_norms_leg_im, v_tex_room, sizeof(v_norms_leg_im),sizeof(v_tex_room),sizeof(v_positions_leg_im),sizeof(v_colors_leg_im), 0);
  node_leg_right_im->change_parameters(0, - .9*shoulder_radius_im - arm_height_im/2 ,0.0,0.0,0,0.0);
}

void renderGL(void)
{ 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
    c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
    c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
    c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

    // int frame_num = num_frames%num_beizer_divisions;
    // c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(sampled_beizer[frame_num][0]), glm::vec3(1.0f,0.0f,0.0f));
    // c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(sampled_beizer[frame_num][1]), glm::vec3(0.0f,1.0f,0.0f));
    // c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(sampled_beizer[frame_num][2]), glm::vec3(0.0f,0.0f,1.0f));    
  
  glm::vec4 cameraPos = glm::vec4(c_xpos, c_ypos, c_zpos, 1.0);  
  if(animate == 1){
    int frame_num = num_frames%num_beizer_divisions;
    cameraPos = glm::vec4(sampled_beizer[frame_num][0], sampled_beizer[frame_num][1], sampled_beizer[frame_num][2], 1.0);
    c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(sampled_beizer_rotation[frame_num][0]), glm::vec3(1.0f,0.0f,0.0f));
    c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(sampled_beizer_rotation[frame_num][1]), glm::vec3(0.0f,1.0f,0.0f));
    c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(sampled_beizer_rotation[frame_num][2]), glm::vec3(0.0f,0.0f,1.0f));    
  }

  glm::vec4 c_pos = cameraPos * c_rotation_matrix;
  glUniform4fv(cameraPosition, 1, glm::value_ptr(cameraPos));
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),lookat_point,glm::vec3(c_up));

  //creating the projection matrix. 
  if(enable_perspective)
    projection_matrix = glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 50.0);
    //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);

  view_matrix = projection_matrix*lookat_matrix;
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
  matrixStack.push_back(view_matrix);

  if(start_char_animation == 1){
    character_animation(char_anim_frame_num % ((num_read_frames-1)*10) ) ;
  }

  glUniform1i(tex_or_color, 0);
  node_door->render_tree();
  node_tabletop->render_tree();

  if (light1_on_var < 0.5) {
    glUniform1i(light1_on, 0);  
  } else {
    glUniform1i(light1_on, 1);
  }
  if (light2_on_var < 0.5) {
    glUniform1i(light2_on, 0);  
  } else {
    glUniform1i(light2_on, 1);
  }

  if(click == 1){
   node_onclick->render_tree();
  }

  if(beizer_done == 1){
    beizer();
    node_beizer = new csX75::HNode(NULL,num_vertices_beizer,v_positions_beizer,v_colors_beizer,v_norms_beizer, v_tex_room, sizeof(v_norms_beizer),sizeof(v_tex_room),sizeof(v_positions_beizer),sizeof(v_colors_beizer), 0);
    node_beizer->change_parameters(0, 0, 0, 0, 0, 0);  
    node_beizer->render_tree();
  }

  // node1->render_tree();  
  // node_room->render_tree();
  // node_box->render_tree();
  // node_torso2->render_tree();
  // node_torso_im->render_tree();
  node_door->render_tree();
  // node_window->render_tree();
  node_cupboard->render_tree();
  node_wall_light->render_tree();
  node_tabletop->render_tree();
  node_stooltop->render_tree();
  // node_lamp_sprt2->render_tree();

  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  // Draw the room
  glUniform1i(tex_or_color, 1);
  modelview_matrix = view_matrix*model_matrix;
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  normal_matrix = glm::transpose (glm::inverse(glm::mat3(modelview_matrix)));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  tex =LoadTexture("images/brick.bmp", 512, 512);
  glBindVertexArray (vao[0]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices_walls);

  floor_tex =LoadTexture("images/sandstone_tiles.bmp", 256, 256);
  glBindVertexArray (vao[1]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices_floor);


  floor_tex =LoadTexture("images/ceiling.bmp", 256, 256);
  glBindVertexArray (vao[2]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices_floor);

  cupboard_tex =LoadTexture("images/doors.bmp", 200, 260);
  glBindVertexArray (vao[3]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices_floor);

  tabletop_tex =LoadTexture("images/tabletop.bmp", 96, 96);
  glBindVertexArray (vao[4]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  bed_tex =LoadTexture("images/tabletop.bmp", 96, 96);
  glBindVertexArray (vao[5]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  mat_tex =LoadTexture("images/mattress.bmp", 600, 600);
  glBindVertexArray (vao[6]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  bed_sprt_tex =LoadTexture("images/sandstone_tiles.bmp", 256, 256);
  glBindVertexArray (vao[7]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  window_tex =LoadTexture("images/window.bmp", 599, 416);
  glBindVertexArray (vao[8]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

}


int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(512, 512, "Music Box", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // cout << c_zpos << " rot " << modelview_matrix.shape() << endl;

  glfwSetMouseButtonCallback(window, csX75::mouse_button_callback);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
      
      if(animate==1){
        cout << "trying animate "<<endl;
        if(glfwGetTime() > num_frames*timer2){
          dump_frames(num_frames);
          num_frames++;
        }
        if(num_frames>num_beizer_divisions){
          animate=0;
        }
      }
      // if(animate == 1){
      //   dump_frames(1);
      // }

      if(start_char_animation==1){
        // cout << "trying character animate "<<endl;
        if(glfwGetTime() > char_anim_frame_num*timer){
          if(char_anim_frame_num <  (num_read_frames-1)*10){
            dump_frames(num_beizer_divisions + char_anim_frame_num);//(num_read_frames-1)*10
          }
          char_anim_frame_num++;
        }
      }

      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------

