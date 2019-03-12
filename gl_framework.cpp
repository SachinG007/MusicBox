#include "gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xpos, c_ypos, c_zpos, c_xrot,c_yrot,c_zrot;
#include <vector>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "hierarchy_node.hpp"

#include <iostream>
#include <cmath>
#include <sstream>
#include <string>


// #include "07_hierarchical_modelling.cpp"

double beizer_points[50][3];
int num_beizer_points = 0;
glm::vec3 c_lookat_b = glm::vec3(0, 0, -1);

extern GLfloat c_xpos, c_ypos, c_zpos, c_xrot,c_yrot,c_zrot, click, beizer_done, animate, start_char_animation;
extern float light1_on_var, light2_on_var;
extern glm::mat4 modelview_matrix;
extern glm::mat4 inv_modview;
extern glm::mat4 view_matrix;
extern float sampled_beizer[100][3];
extern float sampled_beizer_rotation[100][3];

extern int num_read_frames;
extern std::vector<double> read_keyframes[500];
extern std::vector<double> interpolated_frames[5000];

extern bool enable_perspective;
extern csX75::HNode *curr_node, *node_room, *node_box, *node_lid ,*node_platform1, *node_hip_left,*node_hip_right, *node_knee_left,*node_knee_right, *node_neck, *node_torso, *node_shoulder_left, *node_shoulder_right, *node_elbow_left, *node_elbow_right, *node_torso2, *node_torso_im, *node_face_im, *node_shoulder_left_im,       *node_shoulder_right_im, *node_hip_left_im, *node_hip_right_im, *node_onclick,    *present_node;

extern std::vector<csX75::HNode*> vec_nodes;
// string nodes[20] = {"node_torso2"}; 


namespace csX75
{

  void init_vec_nodes(){

    std::cout << "vec initliazid"<<std::endl;

    vec_nodes.push_back(node_lid);vec_nodes.push_back(node_platform1);vec_nodes.push_back(node_torso2);vec_nodes.push_back(node_torso);vec_nodes.push_back(node_neck);vec_nodes.push_back(node_shoulder_left);vec_nodes.push_back(node_elbow_left);vec_nodes.push_back(node_shoulder_right);vec_nodes.push_back(node_elbow_right);vec_nodes.push_back(node_hip_left);vec_nodes.push_back(node_knee_left);vec_nodes.push_back(node_hip_right);vec_nodes.push_back(node_knee_right);vec_nodes.push_back(node_torso_im);vec_nodes.push_back(node_face_im);vec_nodes.push_back(node_shoulder_left_im);vec_nodes.push_back(node_shoulder_right_im);vec_nodes.push_back(node_hip_left_im);vec_nodes.push_back(node_hip_right_im);

  }



  //Storing Keyframes
  void storeKeyFrame() {
    std::ofstream keyframe;
    keyframe.open("keyframes.txt", std::ios_base::app | std::ios_base::out);
    int num_nodes = vec_nodes.size();
    // std::cout << num_nodes << std::endl;
    if(num_nodes == 0){
      init_vec_nodes();
    }
    num_nodes = vec_nodes.size();
    // int i = 1;
    for(int i=0;i<num_nodes;i++){
      keyframe << (vec_nodes[i]->get_tx())<< " "<< (vec_nodes[i]->get_ty())<< " "<< (vec_nodes[i]->get_tz())<< " "<< (vec_nodes[i]->get_rx())<< " "<< (vec_nodes[i]->get_ry())<< " "<< (vec_nodes[i]->get_rz()) << " " ;
    }
    keyframe << light1_on_var << " "<< light2_on_var<<" ";


    keyframe << "\n";
    keyframe.close();
  }

  void readKeyFrame() {

    std::string keyframe_inp;
    num_read_frames = 0;

    std::ifstream keyframe("keyframes.txt");

    if(keyframe.is_open()) {
      std::cout<< "entered keyframe.txt"<<std::endl;

      while(getline(keyframe, keyframe_inp)) {

        std::stringstream iss( keyframe_inp);
        double number;
        while ( iss >> number ){
          read_keyframes[num_read_frames].push_back( number );
        }

        num_read_frames++;
      }

      keyframe.close();
      std::cout <<"number of keyframes "<<num_read_frames<<" entries in 1 frame"<< read_keyframes[0].size()<<std::endl;

    }

  }

  void vector_util(std::vector<double> &vec, double n){
    int sz = vec.size();
    for(int k=0;k<sz;k++){
      vec[k] = vec[k] * n;
    }
  }

  void interpolate_frames(){

    int len_of_one_frame = read_keyframes[0].size();
    for(int i=0;i<num_read_frames-1;i++){

      //take difference of 2 consecutive keyframes
      std::vector<double> diff_frames = read_keyframes[i];
      std::transform(read_keyframes[i+1].begin(), read_keyframes[i+1].end(), read_keyframes[i].begin(), diff_frames.begin(), std::minus<double>());

      //multiply the diffrecen by 0.1
      vector_util(diff_frames,0.1);

      for(int j=0;j<10;j++){
        // std::cout << i <<" "<<j << std::endl;
        if(i==0 && j==0){
          interpolated_frames[i*10 + j] = read_keyframes[i];          
        }
        else{
          int pframe = i*10 + j;
          //just for sake of variable initialization
          interpolated_frames[pframe] = interpolated_frames[pframe-1];//for initilization, else seg fault
          //add the diff value ot the previous interpolated frame
          std::transform(interpolated_frames[pframe - 1].begin(), interpolated_frames[pframe - 1].end(), diff_frames.begin(), interpolated_frames[pframe].begin(), std::plus<double>());
        }
      }
    }

    for(int i=0;i<40;i++){
      std::cout<<"debug"<<interpolated_frames[i][108]<<" " << interpolated_frames[i][109] <<std::endl;
    }

  }

  //! Initialize GL State.  
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  


  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    //Music Box controls
    // else if (key == GLFW_KEY_1)
    //   curr_node = node_room;  
    else if (key == GLFW_KEY_1){
      // curr_node = node_lid; 
      node_lid->dec_rx();
      node_platform1->new_ty(node_platform1->get_ty() + 0.03);
    }
    else if (key == GLFW_KEY_2){
      // curr_node = node_lid; 
      node_lid->inc_rx();
      node_platform1->new_ty(node_platform1->get_ty() - 0.03);
    }

    //Captain America Controls
    else if (key == GLFW_KEY_3 )
      curr_node = node_torso2; 
    else if (key == GLFW_KEY_4 )
      curr_node = node_torso; 
    // else if (key == GLFW_KEY_U )
    //   curr_node = node_neck; 
    else if (key == GLFW_KEY_5 )
      curr_node = node_shoulder_left; 
    // else if (key == GLFW_KEY_6 )
    //   curr_node = node_elbow_left; 
    else if (key == GLFW_KEY_6 )
      curr_node = node_shoulder_right; 
    // else if (key == GLFW_KEY_8 )
    //   curr_node = node_elbow_right; 
    else if (key == GLFW_KEY_7 )
      curr_node = node_hip_left;
    // else if (key == GLFW_KEY_0 )
    //   curr_node = node_knee_left;
    else if (key == GLFW_KEY_8 )
      curr_node = node_hip_right;
    // else if (key == GLFW_KEY_EQUAL )
    //   curr_node = node_knee_right; 

    else if (key == GLFW_KEY_Z )
      node_torso2->new_tx(node_torso2->get_tx()+.03);
    // else if (key == GLFW_KEY_8 )
    //   curr_node = node_elbow_right; 
    else if (key == GLFW_KEY_X )
      node_torso2->new_tx(node_torso2->get_tx()-.03);

    //Iron Man Controls
    else if (key == GLFW_KEY_9)
      curr_node = node_torso_im; 
    else if (key == GLFW_KEY_0 )
      curr_node = node_face_im; 
    else if (key == GLFW_KEY_MINUS )
      curr_node = node_shoulder_left_im; 
    else if (key == GLFW_KEY_EQUAL )
      curr_node = node_shoulder_right_im; 
    else if (key == GLFW_KEY_LEFT_BRACKET )
        curr_node = node_hip_left_im; 
    else if (key == GLFW_KEY_RIGHT_BRACKET )
      curr_node = node_hip_right_im; 

    else if (key == GLFW_KEY_C )
      node_torso_im->new_tx(node_torso_im->get_tx()+.03); 
    // else if (key == GLFW_KEY_8 )
    //   curr_node = node_elbow_right; 
    else if (key == GLFW_KEY_F )
      node_torso_im->new_tx(node_torso_im->get_tx()-.03);


    //Rotation Paramter Controls    
    else if (key == GLFW_KEY_LEFT )
      curr_node->dec_ry();
      // c_xpos -= 0.2;
    else if (key == GLFW_KEY_RIGHT )
      curr_node->inc_ry();
      // c_xpos += 0.2;
    else if (key == GLFW_KEY_UP )
      curr_node->dec_rx();
      // c_zpos -= 0.2;
    else if (key == GLFW_KEY_DOWN )
      curr_node->inc_rx();
      // c_zpos += 0.2;
    else if (key == GLFW_KEY_PAGE_UP )
      curr_node->dec_rz();
      // c_ypos -= 0.2;
    else if (key == GLFW_KEY_PAGE_DOWN )
      curr_node->inc_rz();
      // c_ypos += 0.2;

    //Camera Controls
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;   
    else if (key == GLFW_KEY_A  )
      c_yrot -= 1.0;
    else if (key == GLFW_KEY_D  )
      c_yrot += 1.0;
    else if (key == GLFW_KEY_W)
      c_xrot -= 1.0;
    else if (key == GLFW_KEY_S  )
      c_xrot += 1.0;        
    else if (key == GLFW_KEY_Q )
      c_zrot -= 1.0;
    else if (key == GLFW_KEY_E  ){
      c_zrot += 1.0;
      std::cout << "c_zrot " <<c_zrot << std::endl;   
    }

    //Camera Translation.  
    else if (key == GLFW_KEY_R  ){
      c_xpos += .25;
      std::cout << "c_xpos " <<c_xpos << std::endl; 
      std::cout << "num of pts clicked"<<num_beizer_points<<std::endl;  
    }
    else if (key == GLFW_KEY_T  ){
      c_xpos -= .25;
      std::cout << "c_xpos " <<c_xpos << std::endl;   
    }
    else if (key == GLFW_KEY_Y  ){
      c_ypos += .25;
      std::cout << "c_ypos " <<c_ypos << std::endl;   
    }
    else if (key == GLFW_KEY_U  ){
      c_ypos -= .25;
      std::cout << "c_ypos " <<c_ypos << std::endl;   
    }
    else if (key == GLFW_KEY_G  ){
      c_zpos += .25;
      std::cout << "c_zpos " <<c_zpos << std::endl;   
    }
    else if (key == GLFW_KEY_H  ){
      c_zpos -= .25;
      // cout << "debug"<<sizeof(modelview_matrix)<<endl;
      std::cout << "c_zpos " <<c_zpos << std::endl;   
    }

    //IMPORTANT ANIMATION KEYS
    else if (key == GLFW_KEY_I ){
      fill_beizer();
      beizer_done = 1;
      click = 0;
    }
    else if (key == GLFW_KEY_O ){
      animate = 1;
    }
    else if (key == GLFW_KEY_L && action == GLFW_PRESS){
      storeKeyFrame();
      std::cout << "frame stored" << std::endl;
    }
    else if (key == GLFW_KEY_M && action == GLFW_PRESS){
      readKeyFrame();
      interpolate_frames();
      start_char_animation = 1;
      // std::cout << "frame stored" << std::endl;
    }
    else if (key == GLFW_KEY_N && action == GLFW_PRESS){
      // dump_frames();
    }

    // LIGHT CONTROLS
    else if (key == GLFW_KEY_V && action == GLFW_PRESS){
      if (light1_on_var < 0.5) {
        light1_on_var = 1.0;
      }
      else {
        light1_on_var = 0.0;
      }
    }
    else if (key == GLFW_KEY_B && action == GLFW_PRESS){
      if (light2_on_var < 0.5) {
        light2_on_var = 1.0; 
      }
      else {
        light2_on_var = 0.0;
      }
    }



  }

  // !GLFW mouse callback
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  {

    switch(button)
    {
      case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS)
        {
          // if storing the current camera position
          click = 1;
          curr_node = node_onclick;
          std::cout<<"a point was clicked"<<std::endl;
          std::cout << "c_xpos " << c_xpos << " c_ypos " << c_ypos << " c_zpos " << c_zpos << std::endl;  
          std::cout << "c_xrot " << c_xrot << " c_yrot " << c_yrot << " c_zrot " << c_zrot << std::endl; 
          curr_node->new_tx(c_xpos + c_lookat_b[0]);
          curr_node->new_ty(c_ypos + c_lookat_b[1]);
          curr_node->new_tz(c_zpos + c_lookat_b[2]);

          //division by arr 3 just for a check , not compulsory
          beizer_points[2*num_beizer_points][0] = c_xpos;
          beizer_points[2*num_beizer_points][1] = c_ypos;
          beizer_points[2*num_beizer_points][2] = c_zpos-1;
          beizer_points[2*num_beizer_points+1][0] = c_xrot;
          beizer_points[2*num_beizer_points+1][1] = c_yrot;
          beizer_points[2*num_beizer_points+1][2] = c_zrot;
          num_beizer_points = num_beizer_points + 1;

        }
    }
  }

  double nci(int n, int i){

    double ans = 1;

    for(int j=0;j<i;j++){
      ans = ans * (n-j)/(i-j);
    }

    std::cout<<"nci "<< ans<< std::endl;
    return ans;
  }


  void fill_beizer(){
    int samp_num = 0;
    std::cout<<"num_beizer_points "<< num_beizer_points<< std::endl;

    for(double t=0.0;t<=1;t=t+0.01){
      
      double sum[6]={0};
      for(int k=0;k<num_beizer_points;k++){
    
        double fact = nci(num_beizer_points - 1, k);
        if(k==0 && t==0){
          fact = 1;
        }
        if(k==num_beizer_points-1 && t==1){
          fact = 1;
        }
        else{
          fact = fact*pow(t,k)*pow(1-t,num_beizer_points - 1 - k);
        }
        sum[0] = sum[0] + beizer_points[2*k][0] * fact;
        sum[1] = sum[1] + beizer_points[2*k][1] * fact;
        sum[2] = sum[2] + beizer_points[2*k][2] * fact;
        sum[3] = sum[3] + beizer_points[2*k+1][0] * fact;
        sum[4] = sum[4] + beizer_points[2*k+1][1] * fact;
        sum[5] = sum[5] + beizer_points[2*k+1][2] * fact;
      }

      sampled_beizer[samp_num][0] = sum[0];
      sampled_beizer[samp_num][1] = sum[1];
      sampled_beizer[samp_num][2] = sum[2];
      sampled_beizer_rotation[samp_num][0] = sum[0];
      sampled_beizer_rotation[samp_num][1] = sum[1];
      sampled_beizer_rotation[samp_num][2] = sum[2];
      samp_num++;

    }
  }



};  
  


