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
	return node;
}

void node3d_free(node3d* node){
	free(node->mesh->vertex_data);
	free(node->mesh->mesh_offsets);
	mat4_free(node->transform);
	free(node);
}

void node3d_load(node3d* node, void* data, int data_type){}

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
		glBufferData(GL_ARRAY_BUFFER, node->mesh->num_vertices * sizeof(float), node->mesh->vertex_data, GL_STATIC_DRAW);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &node->mesh->index_buffer_object);

		printf("index buffer = %i, size = %i\n", node->mesh->index_buffer_object, sizeof(node->mesh->index_data));
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, node->mesh->index_buffer_object);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, node->mesh->num_indeces * sizeof(GLushort), node->mesh->index_data, GL_STATIC_DRAW);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

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
		glDrawElements(GL_TRIANGLES, node->mesh->num_indeces, GL_UNSIGNED_SHORT, NULL);
		glBindVertexArray(0);
	} else {
		glBindVertexArray(node->mesh->vao);
		glDrawArrays(node->mesh->draw_mode, 0, node->mesh->num_vertices);
		glBindVertexArray(0);
	}
}
