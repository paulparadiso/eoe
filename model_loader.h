#ifndef __MODEL_LOADER_H__
#define __MODEL_LOADER_H__

#include <stdlib.h>
#include <stdio.h>

#include "node.h"

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/vector3.h"
//#include "assimp/mesh.h"

void print_scene_data(struct aiScene* scene);

void print_mesh_data(struct aiMesh** meshes, unsigned int num_meshes);

float* make_vertex_array(struct aiMesh** meshes, unsigned int num_meshes);

node3d* load_model(char* path);

#endif