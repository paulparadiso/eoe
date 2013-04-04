#include "sync.h"

char* list_url = "http://localhost:8080/getimgs"
int data_wait = DATA_WAIT_NONE;

size_t data_recv(void *ptr, size_t size, size_t nmemb, void *data){
	printf("data write.\n");

	size_t real_size = size * nmemb;

	if(real_size = 0){
		return 0;
	}

	curl_mem* page = (curl_mem*)data;
	page->mem = realloc(page->mem, page->size + real_size + 1);
	if(page->mem == NULL){
		printf("not enough memory\n");
		return 0;
	} 
	memcpy(&(page->mem[page->size]), ptr, real_size);
	page->size += real_size;
	//page->mem[page->size] = 0;

	//data_loaded(page);

	return real_size;

}

void get_file(CURL* curl, char* url, int file_type, void* mem_cnk){
	if(file_type == DATA_FILE_JSON){

	}
	if(file_type == DATA_FILE_IMG){

	}
}

size_t write_data_to_file(void *ptr, size_t size, size_t nmemb, void *file){
	size_t written = fwrite(ptr, size, nmemb, file);
	return written;
}

void data_loaded(curl_mem* mem){
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, "http://farm9.staticflickr.com/8397/8612674243_5774fe9571_m.jpg");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_to_file);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)file);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n", 
					curl_easy_strerror(res));
		} else {
			//fwrite((void*)chunk.mem, 1, chunk.size, file);
			//process_json(&chunk);
			//data_loaded(&chunk);
		}
		fclose(file);
	}
	if(data_wait == DATA_WAIT_NONE){
		return;
	} 
	if(data_wait == DATA_WAIT_LIST){
		process_json_list(mem);
		return;
	}
	if(data_wait == DATA_WAIT_IMG){
		process_json_img(mem);
		return;
	}
}

void process_json_list(curl_mem* data, char** out){
	json_object *json_obj = json_tokener_parse(data->mem);
	//printf("JSON type - %i\n", json_object_get_type(json_obj));
	if(json_object_get_type(json_obj) == json_type_array){
		int len = json_object_array_length(json_obj);
		
		int i;
		for(i = 0; i < len; i++){
			json_object* str_obj = json_object_array_get_idx(json_obj, i);
			printf("img - %s\n", json_object_get_string(str_obj));
		}
	} else {
		printf("Output is not array.\n");
	}
}

void process_json_img(curl_mem* data){
	json_object *json_obj;
}

int main(int argc, char** argv){
	CURL* curl;

	chunk.mem = malloc(1);
	chunk.size = 0;

	//file = fopen("../test/images/out.jpg", "wb");

	curl = curl_easy_init();

	if(curl){
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		get_file(curl, list_url, FILE_TYPE_JSON, &chunk);

	}


	return 0;
}

