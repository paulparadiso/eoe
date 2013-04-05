#include "image.h"

void image_open(const char* file, image_buffer* image){
	struct jpeg_decompress_struct cinfo;
	struct my_error_mgr jerr;

	FILE* in_file;
	JSAMPARRAY buffer;
	int row_stride;
	if((in_file = fopen(file, "rb")) == NULL){
		printf("Could not open image - %s\n", file);
		return;
	}

	cinfo.err = jpeg_std_error(&jerr.pub);
  	jerr.pub.error_exit = my_error_exit;

  	if (setjmp(jerr.setjmp_buffer)) {
    /* If we get here, the JPEG code has signaled an error.
     * We need to clean up the JPEG object, close the input file, and return.
     */
     	jpeg_destroy_decompress(&cinfo);
    	fclose(in_file);
    	return;
  	}

  	jpeg_create_decompress(&cinfo);

  	jpeg_stdio_src(&cinfo, in_file);

  	(void) jpeg_read_header(&cinfo, TRUE);

  	(void) jpeg_start_decompress(&cinfo);

  	row_stride = cinfo.output_width * cinfo.output_components;

  	buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

	image->width = cinfo.output_width;
	image->height = cinfo.output_height;
	image->depth = cinfo.output_components;
	image->pixels = malloc(image->width * image->height * image->depth);

	int counter = 0;

	while (cinfo.output_scanline < cinfo.output_height) {
    	(void) jpeg_read_scanlines(&cinfo, buffer, 1);
		//put_scanline_someplace(buffer[0], row_stride);
		memcpy(image->pixels, buffer[0], row_stride);	
	}

	(void) jpeg_finish_decompress(&cinfo);

	jpeg_destroy_decompress(&cinfo);

	fclose(in_file);	
}
