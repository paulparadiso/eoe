#include "model_loader.h"
#include "vec4.h"

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
	scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if(scene == NULL){
		printf("file - %s - failed to load:\n\t%s\n", path, aiGetErrorString());
		return NULL;
	} else {
		printf("file - %s - loaded.\n", path);
	}
	print_scene_data(scene);
	node3d* p_n3d = node3d_create();
	p_n3d->mesh->num_meshes = scene->mNumMeshes;
	//printf("New node has %i meshes.\n", p_n3d->mesh->num_meshes);
	p_n3d->mesh->mesh_offsets = calloc(scene->mNumMeshes, sizeof(unsigned int));
	int i, j;
	int mesh_size = 0;
	for(i = 0; i < scene->mNumMeshes; i++){
		mesh_size += scene->mMeshes[i]->mNumVertices;
	}
	int base = 0;
	//printf("Total num mesh vertices = %i\n", mesh_size);
	p_n3d->mesh->num_vertices = mesh_size * 3;
	p_n3d->mesh->vertex_data = malloc(mesh_size * 3 * sizeof(float));
	memset(p_n3d->mesh->vertex_data, 1.0, mesh_size * 3 * sizeof(float));
	for(i = 0; i < scene->mNumMeshes; i++){
		//printf("loading mesh num %i.\n", i);
		for(j = 0; j < scene->mMeshes[i]->mNumVertices; j++){
			int index = (base + j) * 3;
			vec4d res, ai_base;
			ai_base.x = scene->mMeshes[i]->mVertices[j].x;
			ai_base.y = scene->mMeshes[i]->mVertices[j].y;
			ai_base.z = scene->mMeshes[i]->mVertices[j].z;
			//vec4d_unit(&res, &ai_base);
			p_n3d->mesh->mesh_offsets[i] = base;
			//printf("adding to position - %i: ", index);
			p_n3d->mesh->vertex_data[index] = ai_base.x;
			//printf("vertice.x - %f,", res.x);
			p_n3d->mesh->vertex_data[index + 1] = ai_base.y;
			//printf("vertice.y - %f,", res.y);
			p_n3d->mesh->vertex_data[index + 2] = ai_base.z;
			//printf("vertice.y - %f\n", res.z);
		}
		base += scene->mMeshes[i]->mNumVertices;
		//printf("Base = %i\n", base);
	}
	/*
	for(i = 0; i < p_n3d->mesh->num_vertices; i++){
		printf("V - %f\n", p_n3d->mesh->vertex_data[i]);
	}
	*/
	node3d_gen_vao(p_n3d);
	return p_n3d;
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