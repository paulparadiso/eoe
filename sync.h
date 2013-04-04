#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <json/json.h>

#define IMG_URL_STR_LEN 256

typedef struct curl_mem{
	char* mem;
	size_t size;
} curl_mem;

enum{
	DATA_WAIT_NONE,
	DATA_WAIT_LIST,
	DATA_WAIT_IMG,
};

enum{
	FILE_TYPE_JSON,
	FILE_TYPE_IMG,
};

void get_file(CURL* curl, char* url, int file_type);