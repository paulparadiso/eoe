#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <json/json.h>

#define IMG_URL_STR_LEN 256

typedef struct curl_buffer{
	size_t size;
	char* name;
	char* buffer;
} curl_buffer;

enum{
	DATA_WAIT_NONE,
	DATA_WAIT_LIST,
	DATA_WAIT_IMG,
};

enum{
	FILE_TYPE_JSON,
	FILE_TYPE_IMG,
};

/*
Retrieve file from the given url and store the results in buf. 
*/

int get_file(CURL* curl, char* url, curl_buffer* buf);

/*
Extract the name of the file from the url and store it in name.  
*/

void extract_file_name(char* url, char* name);

/*
Take a json response and build a list of urls.
*/

int json_to_strings(curl_buffer* data, char** url_list);