#include "hierarchy_node.hpp"
#include <iostream>

extern GLuint vPosition, vColor, vNormal, normalMatrix, uModelViewMatrix;
extern std::vector<glm::mat4> matrixStack;

namespace csX75
{

	HNode::HNode(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_colours, glm::vec4* a_norms, glm::vec2* a_tex, std::size_t n_size, std::size_t t_size, std::size_t v_size, std::size_t c_size, int r_mode=1){

		free_motion = 1;
		render_mode = r_mode;
		num_vertices = num_v;
		vertex_buffer_size = v_size;
		color_buffer_size = c_size;
		// initialize vao and vbo of the object;//


		//Ask GL for a Vertex Attribute Objects (vao). 
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		if(tex_mode == 0){
			glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size + n_size, NULL, GL_STATIC_DRAW);
			glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
			glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, a_colours );
			glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size, n_size, a_norms );

			//setup the vertex array as per the shader
			glEnableVertexAttribArray( vPosition );
			glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

			glEnableVertexAttribArray( vColor );
			glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

			glEnableVertexAttribArray( vNormal );
			glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size + color_buffer_size));
		}
		else{

		}

		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=0;

		update_matrices();
	}

	void HNode::check_limits(){
		// if (tx > lim_tx_pos)
		// 	tx = lim_tx_pos;
		// if (tx < lim_tx_neg)
		// 	tx = lim_tx_neg;

		// if (ty > lim_ty_pos)
		// 	ty = lim_ty_pos;
		// if (ty < lim_ty_neg)
		// 	ty = lim_ty_neg;

		// if (tz > lim_tz_pos)
		// 	tz = lim_tz_pos;
		// if (tz < lim_tz_neg)
		// 	tz = lim_tz_neg;
		if (!free_motion) {
			if (rx > lim_rx_pos)
				rx = lim_rx_pos;
			if (rx < lim_rx_neg)
				rx = lim_rx_neg;

			if (ry > lim_ry_pos)
				ry = lim_ry_pos;
			if (ry < lim_ry_neg)
				ry = lim_ry_neg;

			if (rz > lim_rz_pos)
				rz = lim_rz_pos;
			if (rz < lim_rz_neg)
				rz = lim_rz_neg;
		}
	}

	void HNode::update_matrices(){
		check_limits();
		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

		translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));


	}

	void HNode::add_child(HNode* a_child){
		children.push_back(a_child);

	}

	void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz){
		tx = atx;
		ty = aty;
		tz = atz;
		rx = arx;
		ry = ary;
		rz = arz;

		update_matrices();
	}

	void HNode::add_rotation_limits(GLfloat alim_rx_neg, GLfloat alim_rx_pos, GLfloat alim_ry_neg, GLfloat alim_ry_pos, GLfloat alim_rz_neg, GLfloat alim_rz_pos){
		free_motion = 0;
		lim_rx_neg = alim_rx_neg;
		lim_rx_pos = alim_rx_pos;
		lim_ry_neg = alim_ry_neg;
		lim_ry_pos = alim_ry_pos;
		lim_rz_neg = alim_rz_neg;
		lim_rz_pos = alim_rz_pos;
	}

	void HNode::render(){

		//matrixStack multiply
		glm::mat4* ms_mult = multiply_stack(matrixStack);

		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));

		glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(*ms_mult)));
  		glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));

		glBindVertexArray (vao);
		if (render_mode == 0){
			glDrawArrays(GL_TRIANGLES, 0, num_vertices);
		} else if (render_mode == 1) {
			glDrawArrays(GL_TRIANGLE_STRIP, 0, num_vertices);
		}

		// for memory 
		delete ms_mult;

	}

	void HNode::render_tree(){
		
		matrixStack.push_back(translation);
		matrixStack.push_back(rotation);

		render();
		for(int i=0;i<children.size();i++){
			children[i]->render_tree();
		}
		matrixStack.pop_back();
		matrixStack.pop_back();

	}

	void HNode::inc_rx(){
		rx += 1;
		update_matrices();
	}


	void HNode::inc_ry(){
		ry += 1;
		update_matrices();
	}

	void HNode::inc_rz(){
		rz += 1;
		update_matrices();
	}

	void HNode::dec_rx(){
		rx -= 1;
		update_matrices();
	}

	void HNode::dec_ry(){
		ry -= 1;
		update_matrices();
	}

	void HNode::dec_rz(){
		rz -= 1;
		update_matrices();
	}

	void HNode::new_tx(GLfloat new_x){
		tx = new_x;
		update_matrices();
	}


	void HNode::new_ty(GLfloat new_y){
		ty = new_y;
		update_matrices();
	}

	void HNode::new_tz(GLfloat new_z){
		tz = new_z;
		update_matrices();
	}

	void HNode::new_rx(GLfloat new_x){
		rx = new_x;
		update_matrices();
	}


	void HNode::new_ry(GLfloat new_y){
		ry = new_y;
		update_matrices();
	}

	void HNode::new_rz(GLfloat new_z){
		rz = new_z;
		update_matrices();
	}

	glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
		glm::mat4* mult;
		mult = new glm::mat4(1.0f);
	
		for(int i=0;i<matStack.size();i++){
			*mult = (*mult) * matStack[i];
		}	

		return mult;
	}

}