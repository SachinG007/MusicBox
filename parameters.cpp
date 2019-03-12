const int num_vertices = 36;
const int num_vertices_walls = 24;
const int num_vertices_floor = 6;
const int num_beizer_divisions = 100;
const int num_vertices_beizer = 36*num_beizer_divisions;
const int num_vertices_box = 30;
const int num_vertices_cyd = 100000;

int tri_idx = 0;

//----the music box 
float size_var = 1; //variable to control the size of the music box
//x range is (-size var - 1.5 to 1.5+size_var)

float character_scale = 0.25;

/****************** CAPTAIN AMERICA ********************/
//TORSO
float torso_width = 1.25 * character_scale;
float torso_height = 3 * character_scale;
float torso_depth = .5 * character_scale;

////variables for FACE
double face_height = 1.5 * character_scale;
double face_radius = .4 * character_scale;

glm::vec4 face_col(1, 0.8, 0.4, 1.0);

////variables for NECK
double neck_extra_hidden = .1 * character_scale;  //fake neck part to hide inside torso
double neck_height = (.5 + neck_extra_hidden) * character_scale;
double neck_radius = .2 * character_scale;

glm::vec4 neck_col(1, 0.5, 0.1, 1.0);

////variables for caplower
double caplow_height = .1 * character_scale;
double caplow_radius = .8 * character_scale;

glm::vec4 caplow_col(0.6, 0.4, 0.2, 1.0);

////variables for capupper
double capup_height = .5 * character_scale;
double capup_radius = .5 * character_scale;

glm::vec4 capup_col(0.7, 0.5, 0.3, 1.0);

////Thighs
double thigh_height = 1.5 * character_scale;
double thigh_radius = .15 * character_scale;
glm::vec4 thigh_col(0, 0.124, 0.5, 1.0);
glm::vec4 leg_col(1, 0, 0, 1.0);

////Torso2
double torso2_height = 1.25 * character_scale;
double torso2_radius = .25 * character_scale;
glm::vec4 torso2_col(0, 0.8, 0.4, 1.0);

////Arm
double arm_height = 1.2 * character_scale;
double arm_radius = .12 * character_scale;
glm::vec4 arm_col(0, 0.124, 0.5, 1.0);

/////////ball joint
int tesselations = 50;
float hip_radius = .25 * character_scale;
float knee_radius = .15 * character_scale;
float hand_radius = .15 * character_scale;
float shield_radius = 1 * character_scale;
float lamp_radius = 1 * character_scale;

////


/****************** IRON MAN *******************/
//variables for FACE
double face_radius_im = 1.35 * character_scale;
glm::vec4 face_col2(.6, 0, 0, 1.0);

//eyes
float eyes_width_im = 0.2 * character_scale;
float eyes_height_im = 0.1 * character_scale;
float eyes_depth_im = 0.2 * character_scale;

//variables for NECK
double neck_height_im = 0.4 * character_scale;

double torso_radius_im = 1.5 * character_scale;
double torso_height_im = 3 * character_scale;
glm::vec4 torso_col_im(0.8, 0.1, 0, 1.0);

//variables for SHOULDER/
double shoulder_radius_im = .2 * character_scale;
double shoulders_width_extra_im = 0.30 * character_scale;
double shoulders_height_offset_im = 0.5 * character_scale;

//variables for ARMS
double arm_height_im = 1.2 * character_scale;
double arm_radius_im = 0.12 * character_scale;
glm::vec4 arm_col_im(0.8, 0, 0, 1.0);

//leg
double leg_height_im = 1.8 * character_scale;

//variable for antenna
double antenna_height_im = .5 * character_scale;
double antenna_radius_im = 0.1 * character_scale;
glm::vec4 antenna_col_im(0.8, 0.2, 0.2, 1.0);

//variable for iron man heart
double heart_height_im = .15 * character_scale;
double heart_radius_im = 0.5 * character_scale;
glm::vec4 heart_col_im(0.2, 0.8, 1, 1.0);

glm::vec4 shield_col(1, 0.2, 0.2, 1.0);
glm::vec4 blue(.2, .2, 1, 1.0);
glm::vec4 lgrey(.85, .85, .85, 1.0);
glm::vec4 brown(1, 0.7, 0.3, 1.0);
glm::vec4 red(1, 0.2, 0, 1.0);

/***************** ROOM ***********************/

float room_size_var = 10;
float room_size_height = 8;

/***************** TABLE ************************/
float table_leg_radius = 0.25;
float table_leg_height = 4;
float table_width = 4;
float table_depth = 3;

/***************** STOOL ************************/
float stool_leg_radius = 0.1;
float stool_leg_height = 2.5;
float stool_width = 1.0;
float stool_depth = 1.0;
float stoolback_width = 1.0;
float stoolback_height = 1.5;
float stoolback_depth = 0.1;

/***************** DOOR **********************/
float door_height = 0.7 * 2 * room_size_height;
float door_width = 4.5;
float door_depth = 0.5;
glm::vec4 dark_brown(0.4, 0.26, 0.13, 1.0);

/***************** WINDOW ******************/
float window_height = 4;
float window_width = 4;
float window_depth = 0.1;

/***************** CUPBOARD ******************/
float cupboard_height = 8;
float cupboard_width = 4;
float cupboard_depth = 1.5;

/***************** CUPBOARD ******************/
float wall_light_height = 0.4;
float wall_light_width = 3;
float wall_light_depth = 0.25;
glm::vec4 white(1.0, 1.0, 1.0, 1.0);

/***************** On Click Sphere **********************/
// int tesselations = 50;	already defined
float onclick_radius = .2;
