#ifndef _HNODE_HPP_
#define _HNODE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "gl_framework.hpp"


namespace csX75	 { 

	// A simple class that represents a node in the hierarchy tree
	class HNode {
		//glm::vec4 * vertices;
		//glm::vec4 * colors;
		GLfloat tx,ty,tz,rx,ry,rz;
		int free_motion;
		int tex_mode = 0;
		GLfloat lim_tx_pos, lim_tx_neg;
		GLfloat lim_ty_pos, lim_ty_neg;
		GLfloat lim_tz_pos, lim_tz_neg;
		GLfloat lim_rx_pos, lim_rx_neg;
		GLfloat lim_ry_pos, lim_ry_neg;
		GLfloat lim_rz_pos, lim_rz_neg;

		std::size_t vertex_buffer_size;
		std::size_t color_buffer_size;

		GLuint num_vertices;
		GLuint vao,vbo;

		glm::mat4 rotation;
		glm::mat4 translation;
		
		std::vector<HNode*> children;
		HNode* parent;

		//0 = GL_TRIANGLES (for everything else)
		//1 = GL_TRIANGLE_STRIP (for hemisphere and spheres)
		int render_mode;

		void check_limits();
		void update_matrices();

	  public:
		HNode(HNode*, GLuint, glm::vec4*,  glm::vec4*, glm::vec4*, glm::vec2*, std::size_t, std::size_t, std::size_t, std::size_t, int);
		//HNode (HNode* , glm::vec4*,  glm::vec4*,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);

		void add_child(HNode*);
		void render();
		void change_parameters(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
		void add_rotation_limits(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
		void render_tree();
		void inc_rx();
		void inc_ry();
		void inc_rz();
		void dec_rx();
		void dec_ry();
		void dec_rz();
		void new_tx(GLfloat new_x);
		void new_ty(GLfloat new_y);
		void new_tz(GLfloat new_z);
		void new_rx(GLfloat new_x);
		void new_ry(GLfloat new_y);
		void new_rz(GLfloat new_z);

		float get_tx(){
			return tx;
		}
		float get_ty(){
			return ty;
		}	
		float get_tz(){
			return tz;
		}
		float get_rx(){
			return rx;
		}
		float get_ry(){
			return ry;
		}	
		float get_rz(){
			return rz;
		}

	};

	glm::mat4* multiply_stack(std::vector <glm::mat4> );
};	

#endif