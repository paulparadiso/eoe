#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jpeglib.h"
#include <setjmp.h>

typedef struct image_buffer{
	int width;
	int height;
	int depth;
	unsigned char* pixels;
} image_buffer;

struct my_error_mgr {
  struct jpeg_error_mgr pub;
  jmp_buf setjmp_buffer;
};

typedef struct my_error_mgr * my_error_ptr;

void image_save(const char* file);

void image_open(const char* file, image_buffer* image);

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}

#endif