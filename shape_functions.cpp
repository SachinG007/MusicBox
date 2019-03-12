#include "hierarchy_node.hpp"
#include <iostream>
#include <fstream> 

extern float sampled_beizer[100][3];
using namespace std;

double PI = 3.14159265;

////code for CYLINDER/////
void cyd(double radius, float height, glm::vec4 col[], glm::vec4 pos[], glm::vec4 normals[], glm::vec4 col_source )
{
  float h;
  float long_inc=.25;
  float h_inc=height/10;

  //bottom circle
  for(float longs = 0.0; longs <= 2.0*PI*3; longs+=long_inc){

    glm::vec4 pt(0, -height/2.0, 0, 1.0);
    col[tri_idx] = col_source; pos[tri_idx] = pt;
    normals[tri_idx] = glm::vec4(0, -1.0, 0, 1.0);
    tri_idx++;

    float x = radius  * cos(longs);
    float z = radius  * sin(longs);    
    pt = glm::vec4(x, -height/2.0, z, 1.0);
    col[tri_idx] = col_source; pos[tri_idx] = pt;
    normals[tri_idx] = glm::vec4(0, -1.0, 0, 1.0);
    tri_idx++;

    longs = longs + long_inc;
    x = radius  * cos(longs);
    z = radius  * sin(longs);    
    pt = glm::vec4(x, -height/2.0, z, 1.0);
    col[tri_idx] = col_source; pos[tri_idx] = pt;
    normals[tri_idx] = glm::vec4(0, -1.0, 0, 1.0);
    tri_idx++;
  }

  //top circle
  for(float longs = 0.0; longs <= 2.0*PI*3; longs+=long_inc){

    glm::vec4 pt(0, height/2.0 , 0, 1.0);
    col[tri_idx] = col_source; pos[tri_idx] = pt;
    normals[tri_idx] = glm::vec4(0, 1.0, 0, 1.0);
    tri_idx++;

    float x = radius  * cos(longs);
    float z = radius  * sin(longs);    
    pt = glm::vec4(x, height/2.0 - h_inc, z, 1.0);
    col[tri_idx] = col_source; pos[tri_idx] = pt;
    normals[tri_idx] = glm::vec4(0, 1.0, 0, 1.0);
    tri_idx++;

    longs = longs + long_inc;
    x = radius  * cos(longs);
    z = radius  * sin(longs);    
    pt = glm::vec4(x, height/2.0 - h_inc, z, 1.0);
    col[tri_idx] = col_source; pos[tri_idx] = pt;
    normals[tri_idx] = glm::vec4(0, 1.0, 0, 1.0);
    tri_idx++;
  }

  for (h = -height/2; h <= height/2 - h_inc; h+=h_inc){

    for(float longs = 0.0; longs <= 2.0*PI; longs+=long_inc){

      ///first triangle
      //1
      float x = radius  * cos(longs);
      float z = radius  * sin(longs);
      glm::vec4 pt(x, h, z, 1.0);
      col[tri_idx] = col_source; pos[tri_idx] = pt;
      normals[tri_idx] = glm::vec4(x, 0, z, 1.0);
      tri_idx++;
      
      //2
      x = radius *  cos(longs);
      z = radius *  sin(longs);
      pt =glm::vec4(x, h+h_inc, z, 1.0);
      col[tri_idx] = col_source; pos[tri_idx] = pt;
      normals[tri_idx] = glm::vec4(x, 0, z, 1.0);
      tri_idx++;

      //3
      longs = longs + long_inc;
      x = radius *  cos(longs);
      z = radius *  sin(longs);
      pt =glm::vec4(x, h, z, 1.0);
      col[tri_idx] = col_source; pos[tri_idx] = pt;
      normals[tri_idx] = glm::vec4(x, 0, z, 1.0);
      tri_idx++;

      //2nd traingle 
      //3
      x = radius *  cos(longs);
      z = radius *  sin(longs);
      pt =glm::vec4(x, h, z, 1.0);
      col[tri_idx] = col_source; pos[tri_idx] = pt;
      normals[tri_idx] = glm::vec4(x, 0, z, 1.0);
      tri_idx++;

      //4
      x = radius *  cos(longs);
      z = radius *  sin(longs);
      pt =glm::vec4(x, h+h_inc, z,1.0);
      col[tri_idx] = col_source; pos[tri_idx] = pt;
      normals[tri_idx] = glm::vec4(x, 0, z, 1.0);
      tri_idx++;

      //2
      longs = longs - long_inc;
      x = radius *  cos(longs);
      z = radius *  sin(longs);
      pt =glm::vec4(x, h+h_inc, z, 1.0);
      col[tri_idx] = col_source; pos[tri_idx] = pt;
      normals[tri_idx] = glm::vec4(x, 0, z, 1.0);
      tri_idx++;
  
    }
  }
}

////code for CYLINDER/////
void cyd_flat(double radius, float height, glm::vec4 col[], glm::vec4 pos[], glm::vec4 normals[], glm::vec4 col_source )
{
  float h;
  float long_inc=.25;
  float h_inc=height/10;

  //bottom circle
  for(float longs = 0.0; longs <= 2.0*PI*10; longs+=long_inc){

    glm::vec4 pt(-height/2.0, 0, 0, 1.0);
    col[tri_idx] = col_source; pos[tri_idx] = pt;
    normals[tri_idx] = glm::vec4(-1.0, 0, 0, 1.0);
    tri_idx++;

    float y = radius  * cos(longs);
    float z = radius  * sin(longs);    
    pt = glm::vec4( -height/2.0, y, z, 1.0);
    col[tri_idx] = col_source; pos[tri_idx] = pt;
    normals[tri_idx] = glm::vec4(-1.0, 0, 0, 1.0);
    tri_idx++;

    longs = longs + long_inc;
    y = radius  * cos(longs);
    z = radius  * sin(longs);    
    pt = glm::vec4( -height/2.0, y, z, 1.0);
    col[tri_idx] = col_source; pos[tri_idx] = pt;
    normals[tri_idx] = glm::vec4(-1.0, 0, 0, 1.0);
    tri_idx++;
  }

  //top circle
  for(float longs = 0.0; longs <= 2.0*PI*3; longs+=long_inc){

    glm::vec4 pt(height/2.0 - h_inc, 0, 0, 1.0);
    col[tri_idx] = col_source; pos[tri_idx] = pt;
    normals[tri_idx] = glm::vec4(1.0, 0, 0, 1.0);
    tri_idx++;

    float y = radius  * cos(longs);
    float z = radius  * sin(longs);    
    pt = glm::vec4(height/2.0 - h_inc, y, z, 1.0);
    col[tri_idx] = col_source; pos[tri_idx] = pt;
    normals[tri_idx] = glm::vec4(1.0, 0, 0, 1.0);
    tri_idx++;

    longs = longs + long_inc;
    y = radius  * cos(longs);
    z = radius  * sin(longs);    
    pt = glm::vec4( height/2.0 - h_inc, y, z, 1.0);
    col[tri_idx] = col_source; pos[tri_idx] = pt;
    normals[tri_idx] = glm::vec4(1.0, 0, 0, 1.0);
    tri_idx++;
  }

  for (h = -height/2; h <= height/2 - h_inc; h+=h_inc){

    for(float longs = 0.0; longs <= 2.0*PI*3; longs+=long_inc){

      ///first triangle
      //1
      float y = radius  * cos(longs);
      float z = radius  * sin(longs);
      glm::vec4 pt( h, y, z, 1.0);
      col[tri_idx] = col_source; pos[tri_idx] = pt;
      normals[tri_idx] = glm::vec4(0, y, z, 1.0);
      tri_idx++;
      
      //2
      y = radius *  cos(longs);
      z = radius *  sin(longs);
      pt =glm::vec4(h+h_inc, y, z, 1.0);
      col[tri_idx] = col_source; pos[tri_idx] = pt;
      normals[tri_idx] = glm::vec4(0, y, z, 1.0);
      tri_idx++;

      //3
      longs = longs + long_inc;
      y = radius *  cos(longs);
      z = radius *  sin(longs);
      pt =glm::vec4( h, y, z, 1.0);
      col[tri_idx] = col_source; pos[tri_idx] = pt;
      normals[tri_idx] = glm::vec4(0, y, z, 1.0);
      tri_idx++;

      //2nd traingle 
      //3
      y = radius *  cos(longs);
      z = radius *  sin(longs);
      pt =glm::vec4( h, y, z, 1.0);
      col[tri_idx] = col_source; pos[tri_idx] = pt;
      normals[tri_idx] = glm::vec4(0, y, z, 1.0);
      tri_idx++;

      //4
      y = radius *  cos(longs);
      z = radius *  sin(longs);
      pt =glm::vec4(h+h_inc, y,  z,1.0);
      col[tri_idx] = col_source; pos[tri_idx] = pt;
      normals[tri_idx] = glm::vec4(0, y, z, 1.0);
      tri_idx++;

      //2
      longs = longs - long_inc;
      y = radius *  cos(longs);
      z = radius *  sin(longs);
      pt =glm::vec4(h+h_inc, y, z, 1.0);
      col[tri_idx] = col_source; pos[tri_idx] = pt;
      normals[tri_idx] = glm::vec4(0, y, z, 1.0);
      tri_idx++;
  
    }
  }
}

////code for sphere/////
void sphere(double radius, int Lats, int Longs, glm::vec4 col[], glm::vec4 pos[], glm::vec4 normals[])
{
  float lats,longs;
  tri_idx = 0;

  float slices=(180/(float(Lats)*10))/2;
  float sectors=(180/(float(Longs)*10))/2;

  float l;

  for (lats = 0.0; lats <= 2*PI*3; lats+=sectors){

    for(longs = 0.0; longs <= 2.0*PI*3; longs+=slices){

      float x = radius * sin(lats) * cos(longs);
      float y = radius * sin(lats) * sin(longs);
      float z = radius * cos(lats);
      glm::vec4 pt(x, y, z, 1.0);

      col[tri_idx] = glm::vec4(1,1,1,1); pos[tri_idx] = pt;
      normals[tri_idx] = pt;
      tri_idx++;
      
      // if(lats+sectors>PI)
      //   l=PI;
      // else
      l=lats+sectors;
      x = radius * sin(l) * cos(longs);
      y = radius * sin(l) * sin(longs);
      z = radius * cos(l);
      pt =glm::vec4(x, y, z, 1.0);
      col[tri_idx] = glm::vec4(1,1,1,1); pos[tri_idx] = pt;
      normals[tri_idx] = pt;
      tri_idx++;
        
    }
  }
}

//code for hemisphere/////
void hemi(double radius, int Lats, int Longs, glm::vec4 col[], glm::vec4 pos[], glm::vec4 normals[])
{
  float lats,longs;
  tri_idx = 0;

  float slices=(180/(float(Lats)*10))/2;
  float sectors=(180/(float(Longs)*10))/2;

  float l;
  //bottom circle
  for(float longs = 0.0; longs <= 2.0*PI*3; longs+=slices){

    glm::vec4 pt(0, 0, 0, 1.0);
    col[tri_idx] = face_col2; pos[tri_idx] = pt;
    normals[tri_idx] = glm::vec4(0, -1.0, 0, 1.0);
    tri_idx++;

    float x = radius  * cos(longs);
    float z = radius  * sin(longs);    
    pt = glm::vec4(x, 0, z, 1.0);
    col[tri_idx] = face_col2; pos[tri_idx] = pt;
    normals[tri_idx] = glm::vec4(0, -1.0, 0, 1.0);
    tri_idx++;

    longs = longs + slices;
    x = radius  * cos(longs);
    z = radius  * sin(longs);    
    pt = glm::vec4(x, 0, z, 1.0);
    col[tri_idx] = face_col2; pos[tri_idx] = pt;
    normals[tri_idx] = glm::vec4(0, -1.0, 0, 1.0);
    tri_idx++;
  }

  for (lats = 0; lats <= PI/2; lats+=sectors){

    for(longs = 0.0; longs <= 2.0*PI*10; longs+=slices){

      float x = radius * sin(lats) * cos(longs);
      float y = radius * cos(lats);
      float z = radius * sin(lats) * sin(longs);
      glm::vec4 pt(x, y, z, 1.0);

      col[tri_idx] = face_col2; pos[tri_idx] = pt;
      normals[tri_idx] = pt;
      tri_idx++;
      
      // if(lats+sectors>PI)
      //   l=PI;
      // else
      l=lats+sectors;
      x = radius * sin(l) * cos(longs);
      y = radius * cos(l);
      z = radius * sin(l) * sin(longs);
      pt =glm::vec4(x, y, z, 1.0);
      col[tri_idx] = face_col2; pos[tri_idx] = pt;
      normals[tri_idx] = pt;
      tri_idx++;
        
    }
  }
}


////code for shield/////
void shield(double radius, int Lats, int Longs, glm::vec4 col[], glm::vec4 pos[], glm::vec4 normals[])
{
  float lats,longs;
  tri_idx = 0;
  float shield_depth = 0.25;
  float curr_radius;
  float z2;

  float slices=(180/(float(Lats)*10))/2;
  float sectors=(180/(float(Longs)*10))/2;

  float l;
  for(int k=0;k<10;k++){

    for (float z = k*shield_depth/100; z<shield_depth; z = z + shield_depth/10){

      for(longs = 0; longs <= 2*PI*3; longs+=slices){

        curr_radius = radius*(1 - z/shield_depth);
        float x = curr_radius * sin(longs);
        float y = curr_radius * cos(longs);
        glm::vec4 pt(x, y, z, 1.0);

        if(z<shield_depth/3){
          col[tri_idx] = shield_col;
        }
        else if(z<2*shield_depth/3){
           col[tri_idx] = lgrey; 
        }
        else{
          col[tri_idx] = blue;  
        }
        pos[tri_idx] = pt;
        normals[tri_idx] = glm::vec4(0, 0, 1.0, 1.0);
        tri_idx++;
        
        // if(lats+sectors>PI)
        //   l=PI;
        // else
        z2 = z + shield_depth/10;
        if(z2>shield_depth){
          z2 = shield_depth;
        }
        curr_radius = radius*(1 - z2/shield_depth);
        x = curr_radius * sin(longs);
        y = curr_radius * cos(longs);
        pt =glm::vec4(x, y, z, 1.0);
        if(z2<shield_depth/3){
          col[tri_idx] = shield_col;
        }
        else if(z2<2*shield_depth/3){
           col[tri_idx] = lgrey; 
        }
        else{
          col[tri_idx] = blue;  
        }
        pos[tri_idx] = pt;
        normals[tri_idx] = glm::vec4(0, 0, 1.0, 1.0);
        tri_idx++;
          
      }
    }
  }
}

////code for lamp/////
void lamp(double radius, int Lats, int Longs, glm::vec4 col[], glm::vec4 pos[], glm::vec4 normals[])
{
  float lats,longs;
  tri_idx = 0;
  float lamp_depth = 1.0;
  float curr_radius;
  float z2;
  float max_rad = 4;

  float slices=(180/(float(Lats)*10))/2;
  float sectors=(180/(float(Longs)*10))/2;

  float l;
  for(int k=0;k<100;k++){

    for (float z = k*lamp_depth/100; z<lamp_depth; z = z + lamp_depth/10){

      for(longs = 0; longs <= 2*PI*3; longs+=slices){

        curr_radius = radius*(1 + max_rad*z/(2*lamp_depth));
        float x = curr_radius * sin(longs);
        float y = curr_radius * cos(longs);
        glm::vec4 pt(x, y, z, 1.0);
        col[tri_idx] = shield_col;

        pos[tri_idx] = pt;
        normals[tri_idx] = glm::vec4(0, 0, 1.0, 1.0);
        tri_idx++;
        
        // if(lats+sectors>PI)
        //   l=PI;
        // else
        z2 = z + lamp_depth/10;
        if(z2>lamp_depth){
          z2 = lamp_depth;
        }
        curr_radius = radius*(1 + max_rad*z2/(2*lamp_depth));
        x = curr_radius * sin(longs);
        y = curr_radius * cos(longs);
        pt =glm::vec4(x, y, z, 1.0);
        col[tri_idx] = shield_col;

        pos[tri_idx] = pt;
        normals[tri_idx] = glm::vec4(0, 0, 1.0, 1.0);
        tri_idx++;

          
      }
    }
  }
}

//beizer visulaization
void beizer_util(int a, int b, int c, int d,int &tri_idx, glm::vec4 positions_beizer[]){

  v_positions_beizer[tri_idx] = positions_beizer[a]; v_colors_beizer[tri_idx] = blue; v_norms_beizer[tri_idx] = positions_beizer[a]; tri_idx++;
  v_positions_beizer[tri_idx] = positions_beizer[b]; v_colors_beizer[tri_idx] = blue; v_norms_beizer[tri_idx] = positions_beizer[b]; tri_idx++;
  v_positions_beizer[tri_idx] = positions_beizer[c]; v_colors_beizer[tri_idx] = blue; v_norms_beizer[tri_idx] = positions_beizer[c]; tri_idx++;
  v_positions_beizer[tri_idx] = positions_beizer[a]; v_colors_beizer[tri_idx] = blue; v_norms_beizer[tri_idx] = positions_beizer[a]; tri_idx++;
  v_positions_beizer[tri_idx] = positions_beizer[c]; v_colors_beizer[tri_idx] = blue; v_norms_beizer[tri_idx] = positions_beizer[c]; tri_idx++;
  v_positions_beizer[tri_idx] = positions_beizer[d]; v_colors_beizer[tri_idx] = blue; v_norms_beizer[tri_idx] = positions_beizer[d]; tri_idx++;
}

void beizer(){

  tri_idx = 0;
  float x = 0,y = 0,z = 0;
  float del_x=0.1,del_y=0.1,del_z=0.1;

  for(int i=0;i<num_beizer_divisions;i++){

    x = sampled_beizer[i][0];
    y = sampled_beizer[i][1];
    z = sampled_beizer[i][2];
    // cout << "sam num "<<i<<" x y z "<< x<<" "<<y<<" "<<z<<endl;
    
    glm::vec4 positions_beizer[8] = {
      glm::vec4(x - del_x, y - del_y, z + del_z, 1.0),
      glm::vec4(x - del_x, y + del_y, z + del_z, 1.0),
      glm::vec4(x + del_x, y + del_y, z + del_z, 1.0),
      glm::vec4(x + del_x, y - del_y, z + del_z, 1.0),
      glm::vec4(x - del_x, y - del_y, z - del_z, 1.0),
      glm::vec4(x - del_x, y + del_y, z - del_z, 1.0),
      glm::vec4(x + del_x, y + del_y, z - del_z, 1.0),
      glm::vec4(x + del_x, y - del_y, z - del_z, 1.0)
    };

    beizer_util(1,0,3,2,tri_idx,positions_beizer);
    // std::cout << "tr "<<tri_idx<<std::endl;
    beizer_util(2,3,7,6,tri_idx,positions_beizer);
    beizer_util(3,0,4,7,tri_idx,positions_beizer);
    beizer_util(6,5,1,2,tri_idx,positions_beizer);
    beizer_util(4,5,6,7,tri_idx,positions_beizer);
    beizer_util(5,4,0,1,tri_idx,positions_beizer);
    
  }
}



