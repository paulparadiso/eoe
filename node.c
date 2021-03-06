#include "node.h"

node3d* node3d_create(){
	node3d* node = malloc(sizeof(node3d));
	node->transform = mat4_create_id();
	node->position.x = 0.0;
	node->position.y = 0.0;
	node->position.z = 0.0;
	node->position.w = 1.0;
	node->mesh = malloc(sizeof(mesh_data));
	node->mesh->b_indexed_draw = 0;
	node->mesh->b_has_vertex_colors = 0;
	node->mesh->b_has_texture = 0;
	return node;
}

void node3d_free(node3d* node){
	free(node->mesh->vertex_data);
	free(node->mesh->mesh_offsets);
	mat4_free(node->transform);
	free(node);
}

void node3d_load(node3d* node, void* data, int data_type){}

void node3d_load_texture(node3d* node, image_buffer* img, int offset){
	glGenTextures(1, &node->mesh->texture);
	glBindTexture(GL_TEXTURE_2D, node->mesh->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->pixels);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	/*
	glGenSamplers(1, &node->mesh->sampler);
	glSamplerParameteri(node->mesh->sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glSamplerParameteri(node->mesh->sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glSamplerParameteri(node->mesh->sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(node->mesh->sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	*/
	node->mesh->b_has_texture = 1;
	node->mesh->texture_index_offset = offset;
}

void node3d_gen_vao(node3d* node){	
	if(node->mesh->b_indexed_draw){
		
		/*
		int i;
		for(i = 0; i < node->mesh->num_vertices; i++){
			printf("vertex[%i] = %f.\n", i, node->mesh->vertex_data[i]);
		}
		*/

		glGenVertexArrays(1, &node->mesh->vao);
		glBindVertexArray(node->mesh->vao);


		glGenBuffers(1, &node->mesh->vertex_buffer_object);
		
		printf("vertex buffer = %i, size = %i\n", node->mesh->vertex_buffer_object, sizeof(node->mesh->vertex_data));

		glBindBuffer(GL_ARRAY_BUFFER, node->mesh->vertex_buffer_object);
		
		/*
		If node->mesh->b_has_vertex_color == 1 buffer size will be double.
		*/
		
		//int buffer_size = node->mesh->num_vertices * sizeof(GLfloat) * (1 + node->mesh->b_has_vertex_colors);

		int buffer_size = sizeof(GLfloat) * 20;

		glBufferData(GL_ARRAY_BUFFER, buffer_size, node->mesh->vertex_data, GL_STATIC_DRAW);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &node->mesh->index_buffer_object);

		printf("index buffer = %i, size = %i\n", node->mesh->index_buffer_object, buffer_size);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, node->mesh->index_buffer_object);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, node->mesh->num_indeces * sizeof(GLushort), node->mesh->index_data, GL_STATIC_DRAW);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		if(node->mesh->b_has_vertex_colors){
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(12 * sizeof(GLfloat)));		
		}

		//if(node->mesh->b_has_texture){

		//}
		//int color_offset = node->mesh->num_vertices / 2 * sizeof(float);

		//glBindBuffer(GL_ARRAY_BUFFER, node->mesh->vertex_buffer_object);
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)color_offset);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, node->mesh->index_buffer_object);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, node->mesh->index_buffer_object);

		glBindVertexArray(0);

		/*
		int i;
		printf("Shape coords:\n");
		for(i = 0; i < node->mesh->num_indeces; i++){
			GLushort vertex_index = node->mesh->index_data[i];
			printf("\t%i %f, %f, %f\n", vertex_index, node->mesh->vertex_data[vertex_index * 3], 
									    vertex_index,node->mesh->vertex_data[vertex_index * 3 + 1], 
									    vertex_index,node->mesh->vertex_data[vertex_index * 3 + 2]);
		}
		*/

	} else {
		glGenBuffers(1, &node->mesh->vertex_buffer_object);
		glBindBuffer(GL_ARRAY_BUFFER, node->mesh->vertex_buffer_object);
		glBufferData(GL_ARRAY_BUFFER, node->mesh->num_vertices * 3, node->mesh->vertex_data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//printf("Node has buffer - %i\n", node->mesh->vertex_buffer_object);

		/*
		glGenVertexArrays(1, &node->mesh->vao);
		glBindBuffer(GL_ARRAY_BUFFER, node->mesh->vertex_buffer_object);
		glEnableVertexAttribArray(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		*/
	}
}

void node3d_gen_vbo(node3d* node, float* vertices, int* indeces, int i_count, int v_depth){
	node->mesh->num_vertices = i_count;
	node->mesh->vertex_data = malloc(node->mesh->num_vertices * v_depth * sizeof(float));
	memset(node->mesh->vertex_data, 0, node->mesh->num_vertices * v_depth * sizeof(float));
	int i, j;
	for(i = 0; i < i_count; i++){
		int mesh_index = i * v_depth;
		printf("writing to address - %i = %f | %i\n", mesh_index, node->mesh->vertex_data[mesh_index], indeces[i]);
		//memcpy(&node->mesh->vertex_data[mesh_index], &vertices[indeces[i]], sizeof(float) * v_depth);
		printf("Cube Coord:\n\t");
		for(j = 0; j < v_depth; j++){
			float val = vertices[indeces[i + j]];
			printf("%f ", val);
			node->mesh->vertex_data[mesh_index + j] = val;
		}
		printf("\n");
	}
	for(i = 0; i < i_count * v_depth; i++){
		printf("point - %i = %f\n", i, node->mesh->vertex_data[i]);
	}
	glGenVertexArrays(1, &node->mesh->vao);
	glBindVertexArray(node->mesh->vao);
	glGenBuffers(1, &node->mesh->vertex_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, node->mesh->vertex_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, node->mesh->num_vertices * 3 * sizeof(float), node->mesh->vertex_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void node3d_draw(node3d* node){
	if(node->mesh->b_indexed_draw){
		glBindVertexArray(node->mesh->vao);
		if(node->mesh->b_has_texture){
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, node->mesh->texture);
			//glBindSampler(0, node->mesh->sampler);
		}
		glDrawElements(GL_TRIANGLES, node->mesh->num_indeces, GL_UNSIGNED_SHORT, NULL);
		if(node->mesh->b_has_texture){
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		glBindVertexArray(0);
	} else {
		glBindVertexArray(node->mesh->vao);
		glDrawArrays(node->mesh->draw_mode, 0, node->mesh->num_vertices);
		glBindVertexArray(0);
	}
}
