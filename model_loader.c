#include "model_loader.h"

const char* model_file;
const struct aiScene* scene = NULL;
struct aiVector3D scene_min, scene_max, scene_center;

void print_scene_data(struct aiScene* scene){
	printf("File data:\n");
	printf("\tNum Meshes = %i\n", scene->mNumMeshes);
	printf("\tNum Materials = %i\n", scene->mNumMaterials);
	printf("\tNum Animations = %i\n", scene->mNumAnimations);
	printf("\tNum Textures = %i\n", scene->mNumTextures);
	printf("\tNum Lights = %i\n", scene->mNumLights);
	printf("\tNum Cameras = %i\n", scene->mNumCameras);

	if(scene->mNumMeshes > 0){
		print_mesh_data(scene->mMeshes, scene->mNumMeshes);
	}
}	

void print_mesh_data(struct aiMesh** meshes, unsigned int num_meshes){
	int i;
	for(i = 0; i < num_meshes; i++){
		printf("Mesh %i data:\n", i);
		printf("\tNum Vertices = %i\n", meshes[i]->mNumVertices);
	}
}

node3d* load_model(char* path){
	struct aiScene* scene;
	printf("Loading file - %s\n", path);
	scene = aiImportFile(model_file, aiProcessPreset_TargetRealtime_MaxQuality);
	if(scene == NULL){
		printf("file - %s - failed to load:\n\t%s\n", path, aiGetErrorString());
		return NULL;
	} else {
		printf("file - %s - loaded.\n", path);
	}
	print_scene_data(scene);
	node3d* new_node = node3d_create();
	new_node->mesh->num_meshes = scene->mNumMeshes;
	//printf("New node has %i meshes.\n", new_node->mesh->num_meshes);
	new_node->mesh->mesh_offsets = calloc(scene->mNumMeshes, sizeof(unsigned int));
	int i, j;
	int mesh_size = 0;
	for(i = 0; i < scene->mNumMeshes; i++){
		mesh_size += scene->mMeshes[i]->mNumVertices;
	}
	int base = 0;
	printf("Total num mesh vertices = %i\n", mesh_size);
	new_node->mesh->num_vertices = mesh_size * 3;
	new_node->mesh->vertex_data = calloc(mesh_size * 3, sizeof(float));
	for(i = 0; i < scene->mNumMeshes; i++){
		printf("loading mesh num %i.\n", i);
		for(j = 0; j < scene->mMeshes[i]->mNumVertices; j++){
			new_node->mesh->mesh_offsets[i] = base;
			new_node->mesh->vertex_data[(base * 3)] = scene->mMeshes[i]->mVertices[j].x;
			new_node->mesh->vertex_data[(base * 3) + 1] = scene->mMeshes[i]->mVertices[j].y;
			new_node->mesh->vertex_data[(base * 3) + 2] = scene->mMeshes[i]->mVertices[j].z;
		}
		base += scene->mMeshes[i]->mNumVertices;
		printf("Base = %i\n", base);
	}
	node3d_gen_vao(new_node);
	return new_node;
}

/*
int main(int argc, char** argv){
	if(argc > 1){
		model_file = argv[1];
	} else {
		model_file = "test.obj";
	}
	//scene = aiImportFile(model_file, aiProcessPreset_TargetRealtime_MaxQuality);
	//print_scene_data(scene);
	node3d* output = load_model(model_file);
	return 1;
}
*/