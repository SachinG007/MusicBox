//Eight vertices in homogenous coordinates
//elongated cuboid , basic arm in the hierarchy;
glm::vec4 positions[8] = {
  glm::vec4(0.0, -0.25, 0.25, 1.0),
  glm::vec4(0.0, 0.25, 0.25, 1.0),
  glm::vec4(2.0, 0.25, 0.25, 1.0),
  glm::vec4(2.0, -0.25, 0.25, 1.0),
  glm::vec4(0.0, -0.25, -0.25, 1.0),
  glm::vec4(0.0, 0.25, -0.25, 1.0),
  glm::vec4(2.0, 0.25, -0.25, 1.0),
  glm::vec4(2.0, -0.25, -0.25, 1.0)
};

//RGBA colors
glm::vec4 colors[8] = {
  glm::vec4(0.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 1.0, 0.0, 1.0),
  glm::vec4(0.0, 1.0, 0.0, 1.0),
  glm::vec4(0.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(0.0, 1.0, 1.0, 1.0)
};

//BOX
glm::vec4 positions_box[8] = {
  glm::vec4(-1.5 - size_var, -0.5 - size_var, 0.5 + size_var, 1.0),
  glm::vec4(-1.5 - size_var, 0.5 + size_var, 0.5 + size_var, 1.0),//
  glm::vec4(-0.5 + size_var, 0.5 + size_var, 0.5 + size_var, 1.0),//
  glm::vec4(-0.5 + size_var, -0.5 - size_var, 0.5 + size_var, 1.0),
  glm::vec4(-1.5 - size_var, -0.5 - size_var, -0.5 - size_var, 1.0),
  glm::vec4(-1.5 - size_var, 0.5 + size_var, -0.5 - size_var, 1.0),//
  glm::vec4(-0.5 + size_var, 0.5 + size_var, -0.5 - size_var, 1.0),//
  glm::vec4(-0.5 + size_var, -0.5 - size_var, -0.5 - size_var, 1.0)
};

//RGBA colors
glm::vec4 colors_box[8] = {
  glm::vec4(0.8, 0.4, 0.0, 1.0),
  glm::vec4(1.0, 0.6, 0.2, 1.0),
  glm::vec4(1.0, 0.6, 0.2, 1.0),
  glm::vec4(0.8, 0.4, 0.0, 1.0),
  glm::vec4(0.8, 0.4, 0.0, 1.0),
  glm::vec4(1.0, 0.6, 0.2, 1.0),
  glm::vec4(1.0, 0.6, 0.2, 1.0),
  glm::vec4(0.8, 0.4, 0.0, 1.0),
};

//-lid of the music box
float top_lid = size_var + .5 ;
glm::vec4 positions_lid[8] = {
  glm::vec4(-1.5 - size_var, 0.0, 0.5 + size_var + top_lid, 1.0),
  glm::vec4(-1.5 - size_var, 0.2, 0.5 + size_var + top_lid, 1.0),//
  glm::vec4(-0.5 + size_var, 0.2, 0.5 + size_var + top_lid, 1.0),//
  glm::vec4(-0.5 + size_var, 0.0, 0.5 + size_var + top_lid, 1.0),
  glm::vec4(-1.5 - size_var, 0.0, -0.5 - size_var + top_lid, 1.0),
  glm::vec4(-1.5 - size_var, 0.2, -0.5 - size_var + top_lid, 1.0),//
  glm::vec4(-0.5 + size_var, 0.2, -0.5 - size_var + top_lid, 1.0),//
  glm::vec4(-0.5 + size_var, 0.0, -0.5 - size_var + top_lid, 1.0)
};

//RGBA colors
glm::vec4 colors_lid[8] = {
  glm::vec4(0.4, 0.2, 0, 1.0),
  glm::vec4(0.4, 0.2, 0, 1.0),
  glm::vec4(0.4, 0.2, 0, 1.0),
  glm::vec4(0.4, 0.2, 0, 1.0),
  glm::vec4(0.4, 0.2, 0, 1.0),
  glm::vec4(0.4, 0.2, 0, 1.0),
  glm::vec4(0.4, 0.2, 0, 1.0),
  glm::vec4(0.4, 0.2, 0, 1.0),
};


//platform 1
glm::vec4 positions_platform1[8] = {
  glm::vec4(-1.5 - size_var + 0.02, 0.0, 0.5 + size_var - 0.02, 1.0),
  glm::vec4(-1.5 - size_var + 0.02, 0.2, 0.5 + size_var - 0.02, 1.0),//
  glm::vec4(-0.5 + size_var - 0.02, 0.2, 0.5 + size_var - 0.02, 1.0),//
  glm::vec4(-0.5 + size_var - 0.02, 0.0, 0.5 + size_var - 0.02, 1.0),
  glm::vec4(-1.5 - size_var + 0.02, 0.0, -0.5 - size_var + 0.02, 1.0),
  glm::vec4(-1.5 - size_var + 0.02, 0.2, -0.5 - size_var + 0.02, 1.0),//
  glm::vec4(-0.5 + size_var - 0.02, 0.2, -0.5 - size_var + 0.02, 1.0),//
  glm::vec4(-0.5 + size_var - 0.02, 0.0, -0.5 - size_var + 0.02, 1.0)
};

//RGBA colors
glm::vec4 colors_paltform1[8] = {
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
};

//platform2
glm::vec4 positions_platform2[8] = {
  glm::vec4(-1 +0.02            , 0.0, 0.5 + size_var - 0.02, 1.0),
  glm::vec4(-1 +0.02            , 0.2, 0.5 + size_var - 0.02, 1.0),//
  glm::vec4(-0.5 + size_var-0.02, 0.2, 0.5 + size_var - 0.02, 1.0),//
  glm::vec4(-0.5 + size_var-0.02, 0.0, 0.5 + size_var - 0.02, 1.0),
  glm::vec4(-1 +0.02            , 0.0, -0.5 - size_var + 0.02, 1.0),
  glm::vec4(-1 +0.02            , 0.2, -0.5 - size_var + 0.02, 1.0),//
  glm::vec4(-0.5 + size_var-0.02, 0.2, -0.5 - size_var + 0.02, 1.0),//
  glm::vec4(-0.5 + size_var-0.02, 0.0, -0.5 - size_var + 0.02, 1.0)
};

//RGBA colors
glm::vec4 colors_paltform2[8] = {
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
};

//platform3 //vertical partition
glm::vec4 positions_platform3[8] = {
  glm::vec4(-1 -0.1            ,  -0.5 - size_var + 0.02, 0.5 + size_var - 0.02, 1.0),
  glm::vec4(-1 -0.1            , 0.5 + size_var - 0.02, 0.5 + size_var - 0.02, 1.0),//
  glm::vec4(-1 +0.1            , 0.5 + size_var - 0.02, 0.5 + size_var - 0.02, 1.0),//
  glm::vec4(-1 +0.1            ,  -0.5 - size_var + 0.02, 0.5 + size_var - 0.02, 1.0),
  glm::vec4(-1 -0.1            ,  -0.5 - size_var + 0.02, -0.5 - size_var + 0.02, 1.0),
  glm::vec4(-1 -0.1            , 0.5 + size_var - 0.02, -0.5 - size_var + 0.02, 1.0),//
  glm::vec4(-1 +0.1            , 0.5 + size_var - 0.02, -0.5 - size_var + 0.02, 1.0),//
  glm::vec4(-1 +0.1            ,  -0.5 - size_var + 0.02, -0.5 - size_var + 0.02, 1.0)
};

//RGBA colors
glm::vec4 colors_paltform3[8] = {
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
  glm::vec4(0.4, 0.2, 0.2, 1.0),
};

glm::vec4 positions_torso[8] = {
  glm::vec4(-torso_width/2, 0           , torso_depth/2, 1.0),
  glm::vec4(-torso_width/2, torso_height, torso_depth/2, 1.0),//
  glm::vec4(torso_width/2 , torso_height, torso_depth/2, 1.0),//
  glm::vec4(torso_width/2 , 0           , torso_depth/2, 1.0),
  glm::vec4(-torso_width/2, 0           , -torso_depth/2, 1.0),
  glm::vec4(-torso_width/2, torso_height, -torso_depth/2, 1.0),//
  glm::vec4(torso_width/2 , torso_height, -torso_depth/2, 1.0),//
  glm::vec4(torso_width/2 , 0           , -torso_depth/2, 1.0)
};

//RGBA colors
glm::vec4 colors_torso[8] = {
  glm::vec4(0, 0.3, 1, 1.0),
  glm::vec4(0, 0.125, 0.5, 1.0),
  glm::vec4(0, 0.125, 0.5, 1.0),
  glm::vec4(0, 0.3, 1, 1.0),
  glm::vec4(0, 0.3, 1, 1.0),
  glm::vec4(0, 0.125, 0.5, 1.0),
  glm::vec4(0, 0.125, 0.5, 1.0),
  glm::vec4(0, 0.3, 1, 1.0),

};

//SHOES
float shoe_width = .3;
float shoe_height = .3;
float shoe_depth = .5;
glm::vec4 positions_shoe[8] = {
  glm::vec4(-shoe_width/2, -shoe_height/2, shoe_depth, 1.0),
  glm::vec4(-shoe_width/2, shoe_height/2, shoe_depth, 1.0),//
  glm::vec4(shoe_width/2 , shoe_height/2, shoe_depth, 1.0),//
  glm::vec4(shoe_width/2 , -shoe_height/2, shoe_depth, 1.0),
  glm::vec4(-shoe_width/2, -shoe_height/2, 0 - thigh_radius/2, 1.0),
  glm::vec4(-shoe_width/2, shoe_height/2, 0- thigh_radius/2, 1.0),//
  glm::vec4(shoe_width/2 , shoe_height/2, 0- thigh_radius/2, 1.0),//
  glm::vec4(shoe_width/2 , -shoe_height/2, 0- thigh_radius/2, 1.0)
};

//RGBA colors
glm::vec4 colors_shoe[8] = {
  glm::vec4(0.5, 0.5, 0.5, 1.0),
  glm::vec4(0.5, 0.5, 0.5, 1.0),
  glm::vec4(0.5, 0.5, 0.5, 1.0),
  glm::vec4(0.5, 0.5, 0.5, 1.0),
  glm::vec4(0.5, 0.5, 0.5, 1.0),
  glm::vec4(0.5, 0.5, 0.5, 1.0),
  glm::vec4(0.5, 0.5, 0.5, 1.0),
  glm::vec4(0.5, 0.5, 0.5, 1.0),
};

//Eyes
glm::vec4 positions_eyes_im[8] = {
  glm::vec4(-eyes_width_im/2, -eyes_height_im/2, eyes_depth_im/2, 1.0),
  glm::vec4(-eyes_width_im/2, eyes_height_im/2, eyes_depth_im/2, 1.0),//
  glm::vec4(eyes_width_im/2 , eyes_height_im/2, eyes_depth_im/2, 1.0),//
  glm::vec4(eyes_width_im/2 , -eyes_height_im/2, eyes_depth_im/2, 1.0),
  glm::vec4(-eyes_width_im/2, -eyes_height_im/2, -eyes_depth_im/2, 1.0),
  glm::vec4(-eyes_width_im/2, eyes_height_im/2, -eyes_depth_im/2, 1.0),//
  glm::vec4(eyes_width_im/2 , eyes_height_im/2, -eyes_depth_im/2, 1.0),//
  glm::vec4(eyes_width_im/2 , -eyes_height_im/2, -eyes_depth_im/2, 1.0)
};

//RGBA colors
glm::vec4 colors_eyes_im[8] = {
  glm::vec4(1, 1, 1, 1.0),
  glm::vec4(1, 1, 1, 1.0),
  glm::vec4(1, 1, 1, 1.0),
  glm::vec4(1, 1, 1, 1.0),
  glm::vec4(1, 1, 1, 1.0),
  glm::vec4(1, 1, 1, 1.0),
  glm::vec4(1, 1, 1, 1.0),
  glm::vec4(1, 1, 1, 1.0),
};

//ROOM
glm::vec4 positions_room[8] = {
  glm::vec4(-room_size_var, -room_size_height, room_size_var, 1.0),
  glm::vec4(-room_size_var, room_size_height, room_size_var, 1.0),//
  glm::vec4(room_size_var, room_size_height, room_size_var, 1.0),//
  glm::vec4(room_size_var, -room_size_height, room_size_var, 1.0),
  glm::vec4(-room_size_var, -room_size_height, -room_size_var, 1.0),
  glm::vec4(-room_size_var, room_size_height, -room_size_var, 1.0),//
  glm::vec4(room_size_var, room_size_height, -room_size_var, 1.0),//
  glm::vec4(room_size_var, -room_size_height, -room_size_var, 1.0)
};

glm::vec4 room_normals[6] = {
  glm::vec4(0, 0, -1.0, 1.0), //front
  glm::vec4(-1.0, 0, 0, 1.0), //right
  glm::vec4(0, 1.0, 0, 1.0),  //bottom
  glm::vec4(0, -1.0, 0, 1.0), //top
  glm::vec4(0, 0, 1.0, 1.0),  //back
  glm::vec4(1.0, 0, 0, 1.0), //left
};

glm::vec4 box_normals[6] = {
  glm::vec4(0, 0, 1.0, 1.0),
  glm::vec4(1.0, 0, 0, 1.0),
  glm::vec4(0, -1.0, 0, 1.0),
  glm::vec4(0, 1.0, 0, 1.0),
  glm::vec4(0, 0, -1.0, 1.0),
  glm::vec4(-1.0, 0, 0, 1.0)
};

glm::vec4 colors_room[8] = {
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0)
};

//RGBA colors
// glm::vec4 colors_room[8] = {
//   glm::vec4(0.94, 0.87, 0.5, 1.0),
//   glm::vec4(0.94, 0.87, 0.5, 1.0),
//   glm::vec4(0.94, 0.87, 0.5, 1.0),
//   glm::vec4(0.94, 0.87, 0.5, 1.0),
//   glm::vec4(0.94, 0.87, 0.5, 1.0),
//   glm::vec4(0.94, 0.87, 0.5, 1.0),
//   glm::vec4(0.94, 0.87, 0.5, 1.0),
//   glm::vec4(0.94, 0.87, 0.5, 1.0),
// };

glm::vec2 t_coords[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 1.0),
  glm::vec2( 1.0, 0.0),
  glm::vec2( 1.0, 1.0),
};

// glm :: vec2 t_coords [4][4] = {
//   { glm :: vec2 ( 0.0 , 0.0) ,
//     glm :: vec2 ( 0.0 , 0.45) ,
//     glm :: vec2 ( 0.45 , 0.0) ,
//     glm :: vec2 ( 0.45 , 0.45) } ,
//   { glm :: vec2 ( 0.55 , 0.0) ,
//     glm :: vec2 ( 0.55 , 0.45) ,
//     glm :: vec2 ( 1.0 , 0.0) ,
//     glm :: vec2 ( 1.0 , 0.45) } ,
//   { glm :: vec2 ( 0.0 , 0.55) ,
//     glm :: vec2 ( 0.0 , 1.0) ,
//     glm :: vec2 ( 0.45 , 0.55) ,
//     glm :: vec2 ( 0.45 , 1.0) } ,
//   { glm :: vec2 ( 0.55 , 0.55) ,
//     glm :: vec2 ( 0.55 , 1.0) ,
//     glm :: vec2 ( 1.0 , 0.55) ,
//     glm :: vec2 ( 1.0 , 1.0) } ,
// };

//TABLE TOP
float x_disp = -room_size_var + table_width;
float y_disp = -room_size_var + table_leg_height + table_depth/2;
float z_disp = - room_size_var + table_depth;
glm::vec4 positions_tabletop[8] = {
  glm::vec4(x_disp - table_width,y_disp - 0.5,z_disp  + table_depth, 1.0),
  glm::vec4(x_disp - table_width,y_disp + 0.5,z_disp  + table_depth, 1.0),//
  glm::vec4(x_disp + table_width,y_disp + 0.5,z_disp  + table_depth, 1.0),//
  glm::vec4(x_disp + table_width,y_disp - 0.5,z_disp  + table_depth, 1.0),
  glm::vec4(x_disp - table_width,y_disp - 0.5,z_disp  - table_depth, 1.0),
  glm::vec4(x_disp - table_width,y_disp + 0.5,z_disp  - table_depth, 1.0),//
  glm::vec4(x_disp + table_width,y_disp + 0.5,z_disp  - table_depth, 1.0),//
  glm::vec4(x_disp + table_width,y_disp - 0.5,z_disp  - table_depth, 1.0)
};

//RGBA colors
glm::vec4 colors_tabletop[8] = {
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
};

//BED

float s_length = .3;  //bed support length
float bed_width = 3;
float bed_length = 4;
float bed_depth = 1;
float x_disp_bed = room_size_var - bed_width;
float y_disp_bed = -room_size_height + bed_depth;
float z_disp_bed = -room_size_var + bed_length + 2*s_length; 
glm::vec4 positions_bed[8] = {
  glm::vec4( x_disp_bed - bed_width, y_disp_bed - bed_depth, z_disp_bed + bed_length , 1.0),
  glm::vec4( x_disp_bed - bed_width, y_disp_bed + bed_depth, z_disp_bed + bed_length , 1.0),//
  glm::vec4( x_disp_bed + bed_width, y_disp_bed + bed_depth, z_disp_bed + bed_length , 1.0),//
  glm::vec4( x_disp_bed + bed_width, y_disp_bed - bed_depth, z_disp_bed + bed_length , 1.0),
  glm::vec4( x_disp_bed - bed_width, y_disp_bed - bed_depth, z_disp_bed - bed_length , 1.0),
  glm::vec4( x_disp_bed - bed_width, y_disp_bed + bed_depth, z_disp_bed - bed_length , 1.0),//
  glm::vec4( x_disp_bed + bed_width, y_disp_bed + bed_depth, z_disp_bed - bed_length , 1.0),//
  glm::vec4( x_disp_bed + bed_width, y_disp_bed - bed_depth, z_disp_bed - bed_length , 1.0)
};

//mattress
float mat_depth = .3;
glm::vec4 positions_mat[8] = {
  glm::vec4( x_disp_bed - bed_width, y_disp_bed - mat_depth + bed_depth + mat_depth, z_disp_bed + bed_length , 1.0),
  glm::vec4( x_disp_bed - bed_width, y_disp_bed + mat_depth + bed_depth + mat_depth, z_disp_bed + bed_length , 1.0),//
  glm::vec4( x_disp_bed + bed_width, y_disp_bed + mat_depth + bed_depth + mat_depth, z_disp_bed + bed_length , 1.0),//
  glm::vec4( x_disp_bed + bed_width, y_disp_bed - mat_depth + bed_depth + mat_depth, z_disp_bed + bed_length , 1.0),
  glm::vec4( x_disp_bed - bed_width, y_disp_bed - mat_depth + bed_depth + mat_depth, z_disp_bed - bed_length , 1.0),
  glm::vec4( x_disp_bed - bed_width, y_disp_bed + mat_depth + bed_depth + mat_depth, z_disp_bed - bed_length , 1.0),//
  glm::vec4( x_disp_bed + bed_width, y_disp_bed + mat_depth + bed_depth + mat_depth, z_disp_bed - bed_length , 1.0),//
  glm::vec4( x_disp_bed + bed_width, y_disp_bed - mat_depth + bed_depth + mat_depth, z_disp_bed - bed_length , 1.0)
};


//bed support
float s_width = bed_width;
float s_depth = 2.5;
float x_disp_s = room_size_var - s_width;
float y_disp_s = -room_size_height + s_depth;
float z_disp_s = -room_size_var + s_length; 
glm::vec4 positions_bed_sprt[8] = {
  glm::vec4( x_disp_s - s_width, y_disp_s - s_depth, z_disp_s + s_length, 1.0),
  glm::vec4( x_disp_s - s_width, y_disp_s + s_depth, z_disp_s + s_length, 1.0),//
  glm::vec4( x_disp_s + s_width, y_disp_s + s_depth, z_disp_s + s_length, 1.0),//
  glm::vec4( x_disp_s + s_width, y_disp_s - s_depth, z_disp_s + s_length, 1.0),
  glm::vec4( x_disp_s - s_width, y_disp_s - s_depth, z_disp_s - s_length, 1.0),
  glm::vec4( x_disp_s - s_width, y_disp_s + s_depth, z_disp_s - s_length, 1.0),//
  glm::vec4( x_disp_s + s_width, y_disp_s + s_depth, z_disp_s - s_length, 1.0),//
  glm::vec4( x_disp_s + s_width, y_disp_s - s_depth, z_disp_s - s_length, 1.0)
};

//RGBA colors
glm::vec4 colors_bed[8] = {
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
};

//RGBA colors
glm::vec4 colors_mat[8] = {
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
};

//RGBA colors
glm::vec4 colors_bed_sprt[8] = {
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
};

//STOOL TOP
glm::vec4 positions_stooltop[8] = {
  glm::vec4(-stool_width, -0.3, stool_depth, 1.0),
  glm::vec4(-stool_width, 0.3, stool_depth, 1.0),//
  glm::vec4(stool_width, 0.3, stool_depth, 1.0),//
  glm::vec4(stool_width, -0.3, stool_depth, 1.0),
  glm::vec4(-stool_width, -0.3, -stool_depth, 1.0),
  glm::vec4(-stool_width, 0.3, -stool_depth, 1.0),//
  glm::vec4(stool_width, 0.3, -stool_depth, 1.0),//
  glm::vec4(stool_width, -0.3, -stool_depth, 1.0)
};

//RGBA colors
glm::vec4 colors_stooltop[8] = {
  red,
  red,
  red,
  red,
  red,
  red,
  red,
  red,
};

//STOOL TOP
glm::vec4 positions_stoolback[8] = {
  glm::vec4(-stoolback_width, -stoolback_height, stoolback_depth, 1.0),
  glm::vec4(-stoolback_width, stoolback_height, stoolback_depth, 1.0),//
  glm::vec4(stoolback_width, stoolback_height, stoolback_depth, 1.0),//
  glm::vec4(stoolback_width, -stoolback_height, stoolback_depth, 1.0),
  glm::vec4(-stoolback_width, -stoolback_height, -stoolback_depth, 1.0),
  glm::vec4(-stoolback_width, stoolback_height, -stoolback_depth, 1.0),//
  glm::vec4(stoolback_width, stoolback_height, -stoolback_depth, 1.0),//
  glm::vec4(stoolback_width, -stoolback_height, -stoolback_depth, 1.0)
};

//RGBA colors
glm::vec4 colors_stoolback[8] = {
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
};

//ROOM
glm::vec4 positions_door[8] = {
  glm::vec4(-door_width/2, -door_height/2, door_depth/2, 1.0),
  glm::vec4(-door_width/2, door_height/2, door_depth/2, 1.0),//
  glm::vec4(door_width/2, door_height/2, door_depth/2, 1.0),//
  glm::vec4(door_width/2, -door_height/2, door_depth/2, 1.0),
  glm::vec4(-door_width/2, -door_height/2, -door_depth/2, 1.0),
  glm::vec4(-door_width/2, door_height/2, -door_depth/2, 1.0),//
  glm::vec4(door_width/2, door_height/2, -door_depth/2, 1.0),//
  glm::vec4(door_width/2, -door_height/2, -door_depth/2, 1.0)
};

//RGBA colors
glm::vec4 colors_door[8] = {
  dark_brown,
  dark_brown,
  dark_brown,
  dark_brown,
  dark_brown,
  dark_brown,
  dark_brown,
  dark_brown,
};

//WINDOW
float x_disp_win = 2;
float y_disp_win = 2;
float z_disp_win = -room_size_var + window_depth; 
glm::vec4 positions_window[8] = {
  glm::vec4(x_disp_win - window_width/2, y_disp_win - window_height/2, z_disp_win + window_depth/2, 1.0),
  glm::vec4(x_disp_win - window_width/2, y_disp_win + window_height/2,  z_disp_win + window_depth/2, 1.0),//
  glm::vec4(x_disp_win + window_width/2, y_disp_win + window_height/2,   z_disp_win + window_depth/2, 1.0),//
  glm::vec4(x_disp_win + window_width/2, y_disp_win - window_height/2,  z_disp_win + window_depth/2, 1.0),
  glm::vec4(x_disp_win - window_width/2, y_disp_win - window_height/2, z_disp_win + -window_depth/2, 1.0),
  glm::vec4(x_disp_win - window_width/2, y_disp_win + window_height/2,  z_disp_win + -window_depth/2, 1.0),//
  glm::vec4(x_disp_win + window_width/2, y_disp_win + window_height/2,   z_disp_win + -window_depth/2, 1.0),//
  glm::vec4(x_disp_win + window_width/2, y_disp_win - window_height/2,  z_disp_win + -window_depth/2, 1.0)
};

//RGBA colors
glm::vec4 colors_window[8] = {
  blue,
  blue,
  blue,
  blue,
  blue,
  blue,
  blue,
  blue,
};

// CUPBOARD
glm::vec4 positions_cupboard[8] = {
  glm::vec4(-cupboard_width/2, -cupboard_height/2, cupboard_depth/2, 1.0),
  glm::vec4(-cupboard_width/2, cupboard_height/2, cupboard_depth/2, 1.0),//
  glm::vec4(cupboard_width/2, cupboard_height/2, cupboard_depth/2, 1.0),//
  glm::vec4(cupboard_width/2, -cupboard_height/2, cupboard_depth/2, 1.0),
  glm::vec4(-cupboard_width/2, -cupboard_height/2, -cupboard_depth/2, 1.0),
  glm::vec4(-cupboard_width/2, cupboard_height/2, -cupboard_depth/2, 1.0),//
  glm::vec4(cupboard_width/2, cupboard_height/2, -cupboard_depth/2, 1.0),//
  glm::vec4(cupboard_width/2, -cupboard_height/2, -cupboard_depth/2, 1.0)
};

glm::vec4 positions_cupboard_front[8] = {
  glm::vec4(-room_size_var + 1.1*cupboard_depth ,  -room_size_height + cupboard_height/2-cupboard_height/2, cupboard_depth/2 - cupboard_width/2 + 4.2, 1.0),
  glm::vec4(-room_size_var + 1.1*cupboard_depth ,  -room_size_height + cupboard_height/2+cupboard_height/2, cupboard_depth/2 - cupboard_width/2 + 4.2, 1.0),//
  glm::vec4(-room_size_var + 1.1*cupboard_depth ,  -room_size_height + cupboard_height/2+cupboard_height/2, cupboard_depth/2 + cupboard_width/2 + 4.2, 1.0),//
  glm::vec4(-room_size_var + 1.1*cupboard_depth ,  -room_size_height + cupboard_height/2-cupboard_height/2, cupboard_depth/2 + cupboard_width/2 + 4.2, 1.0),
  glm::vec4(-room_size_var + cupboard_depth/2 - cupboard_width/2 ,  -room_size_height + cupboard_height/2-cupboard_height/2, -cupboard_depth/2 + 5, 1.0),
  glm::vec4(-room_size_var + cupboard_depth/2 - cupboard_width/2 ,  -room_size_height + cupboard_height/2+cupboard_height/2, -cupboard_depth/2 + 5, 1.0),//
  glm::vec4(-room_size_var + cupboard_depth/2 + cupboard_width/2 ,  -room_size_height + cupboard_height/2+cupboard_height/2, -cupboard_depth/2 + 5, 1.0),//
  glm::vec4(-room_size_var + cupboard_depth/2 + cupboard_width/2 ,  -room_size_height + cupboard_height/2-cupboard_height/2, -cupboard_depth/2 + 5, 1.0)
};


//RGBA colors
glm::vec4 colors_cupboard[8] = {
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
  brown,
};

//WALL LIGHT
glm::vec4 positions_wall_light[8] = {
  glm::vec4(-wall_light_width/2, -wall_light_height/2, wall_light_depth/2, 1.0),
  glm::vec4(-wall_light_width/2, wall_light_height/2, wall_light_depth/2, 1.0),//
  glm::vec4(wall_light_width/2, wall_light_height/2, wall_light_depth/2, 1.0),//
  glm::vec4(wall_light_width/2, -wall_light_height/2, wall_light_depth/2, 1.0),
  glm::vec4(-wall_light_width/2, -wall_light_height/2, -wall_light_depth/2, 1.0),
  glm::vec4(-wall_light_width/2, wall_light_height/2, -wall_light_depth/2, 1.0),//
  glm::vec4(wall_light_width/2, wall_light_height/2, -wall_light_depth/2, 1.0),//
  glm::vec4(wall_light_width/2, -wall_light_height/2, -wall_light_depth/2, 1.0)
};

//RGBA colors
glm::vec4 colors_wall_light[8] = {
  white,
  white,
  white,
  white,
  white,
  white,
  white,
  white,
};