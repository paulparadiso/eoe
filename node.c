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

		glGenBuffers(1, &node->mesh->vertex_buffer_object);
		
		printf("vertex buffer = %i, size = %i\n", node->mesh->vertex_buffer_object, sizeof(node->mesh->vertex_data));

		glBindBuffer(GL_ARRAY_BUFFER, node->mesh->vertex_buffer_object);
		glBufferData(GL_ARRAY_BUFFER, node->mesh->num_vertices * sizeof(float), node->mesh->vertex_data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &node->mesh->index_buffer_object);

		printf("index buffer = %i, size = %i\n", node->mesh->index_buffer_object, sizeof(node->mesh->index_data));
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, node->mesh->index_buffer_object);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, node->mesh->num_indeces * sizeof(GLushort), node->mesh->index_data, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &node->mesh->vao);
		
		int color_offset = node->mesh->num_vertices / 2 * sizeof(float);

		glBindVertexArray(node->mesh->vao);
		glBindBuffer(GL_ARRAY_BUFFER, node->mesh->vertex_buffer_object);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)color_offset);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, node->mesh->index_buffer_object);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, node->mesh->index_buffer_object);

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

void node3d_draw(node3d* node){
	if(node->mesh->b_indexed_draw){
		glBindVertexArray(node->mesh->vao);
		glDrawElements(GL_TRIANGLES, node->mesh->num_indeces, GL_UNSIGNED_SHORT, NULL);
		glBindVertexArray(0);
	} else {
		int i;
		glBindBuffer(GL_ARRAY_BUFFER, node->mesh->vertex_buffer_object);
		/*
		for(i = 0; i < node->mesh->num_meshes; i++){
			int num_points;
			if(i < node->mesh->num_meshes - 2){
				num_points = node->mesh->mesh_offsets[i + 1] - node->mesh->mesh_offsets[i];
			} else {
				num_points = node->mesh->num_vertices - node->mesh->mesh_offsets[i];
			}
			//glDrawElementsBaseVertex(GL_POINTS, num_points, GL_UNSIGNED_SHORT, 0, node->mesh->mesh_offsets[i]);
			//int b = node->mesh->mesh_offsets[i];
			//int s = node->mesh->mesh_offsets[i] + num_points;
			//printf("drawing from %i to %i\n", b, s);
			glDrawArrays(GL_POINTS, b, s);
		}
		*/
		//glVertexPointer(3, GL_FLOAT, 0, node->mesh->)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_POINTS, 0, node->mesh->num_vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
