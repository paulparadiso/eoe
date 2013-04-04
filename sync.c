#include "sync.h"

char* list_url = "http://localhost:8080/getimgs";
char* img_url = "http://farm9.staticflickr.com/8522/8610102162_02c5b5beaa_m.jpg";
//int data_wait = DATA_WAIT_NONE;

size_t data_recv(void *ptr, size_t size, size_t nmemb, void *data){
	printf("data write.\n");

	size_t real_size = size * nmemb;

	if(real_size == 0){
		return 0;
	} 
	curl_buffer* page = (curl_buffer*)data;
	page->buffer = realloc(page->buffer, page->size + real_size + 1);
	if(page->buffer == NULL){
		return 0;
	} 
	memcpy(&(page->buffer[page->size]), ptr, real_size);
	page->size += real_size;
	page->buffer[page->size] = 0;

	return real_size;

}

size_t header_recv(void *ptr, size_t size, size_t nmemb, void *data){
	size_t real_size = size * nmemb;
	printf("%s", (char*)ptr);
	return real_size;
}

size_t write_data_to_file(char* name, curl_buffer* buf){
	FILE* file = fopen(name, "wb");
	fwrite(buf->buffer, 1, buf->size, file);
	fclose(file);
}

int get_file(CURL* curl, char* url, curl_buffer* buf){
	curl_easy_setopt(curl, CURLOPT_URL, list_url);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)buf);
	int res = curl_easy_perform(curl);
	if(res != CURLE_OK){
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
	} 
	return res;
}

void extract_file_name(char* url, char* name){
	char domain[256];
	char id[256];
	sscanf("http://%s/%s/%s", domain, id, name);
	//free(domain);
	//free(id);
}

int json_to_list(curl_buffer* data, char** out){
	json_object *json_obj = json_tokener_parse(data->buffer);
	//printf("JSON type - %i\n", json_object_get_type(json_obj));
	if(json_object_get_type(json_obj) == json_type_array){
		int len = json_object_array_length(json_obj);
		out = malloc(sizeof(char*) * len);
		int i;
		for(i = 0; i < len; i++){
			json_object* str_obj = json_object_array_get_idx(json_obj, i);
			//printf("writing %s of length %i\n", json_object_get_string(str_obj), json_object_get_string_len(json_obj));
			out[i] = calloc(1, 256);
			//memcpy(out[i], json_object_get_string(str_obj), json_object_get_string_len(json_obj));
			sprintf(out[i], "%s", json_object_get_string(str_obj)); 
			printf("img - %s\n", out[i]);
		}
		return len;
	} else {
		printf("Output is not array.\n");
		return 0;
	}
}

int main(int argc, char** argv){
	CURL* curl;
	curl_buffer files;
	char* header_data;

	files.buffer = malloc(1);
	files.size = 0;

	int res;

	//file = fopen("../test/images/out.jpg", "wb");

	curl = curl_easy_init();

	if(curl){
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, data_recv);
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_recv);
		curl_easy_setopt(curl, CURLOPT_WRITEHEADER, (void*)header_data);
		res = get_file(curl, list_url, &files);
		if(res == CURLE_OK){
			char** img_list;
			int len = json_to_list(&files, img_list);
			if(len > 0){
				int i;
				for(i = 0; i < len; i++){
					curl_buffer tmp_buffer;
					res = get_file(curl, img_list[i], &tmp_buffer);
					if(res == CURLE_OK){
						char file_name[256];
						extract_file_name(img_list[i], file_name);
						printf("extracted file name - %s\n", file_name);
						//char* path = "../images/" + file_name;
						//write_data_to_file(path, tmp_buffer);
						free(tmp_buffer.buffer);
					}
				}
			}
		}
	}
	curl_easy_cleanup(curl);
	return 0;
}

