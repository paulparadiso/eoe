/*
Vertex attribute types.
*/

enum{
	VERTEX_ATTRIB_COORD,
	VERTEX_ATTRIB_COLOR,
	VERTEX_ATTRIB_TEX_COORD
}

/*
Vertex primitive can be any of the enum for pos, color, tex, etc.
*/

typedef struct vertex_primitive{
	int type;
	int size;
	float* data;
} vertex_primitive;

/*
List of vertex primitives comprising a single vertex.
*/

typedef struct vertex{
	vertex_primitive* vp;
	vertex_primitive* next;
} vertex;

/*
Individual element is a vertex list.
*/

typedef struct vertex_list_element{
	vertex* v;
	vertex* next;
} vertex_list_element;

/*
Vertex list to keep track of new vertices before they are compiled into
a vertex buffer;
*/

typedef struct vertex_list{
	vertex_list_element* head;
	vertex_list_element* current;
	vertex_list_element* tail;
} vertex_list;

/*
Buffer elements describe the elements in the buffer in order to 
set up vertex array and attribute pointers.
*/

typedef struct buffer_element{
	int type;
	int size;
} buffer_element;

/*
Vertex buffer that can be used to set up a vertex array object.
*/

typedef struct vertex_buffer{
	int num_elements;
	buffer_element* elements;
	float* buffer;
} vertex_buffer;

/*

*/

vertex_list* vertex_list_create();

/*
Add an empty element to the list and set the current pointer to it.
*/

void vertex_list_exp();

/*
Add a new element and start it with a primitive.
*/

void vertex_list_exp_with_primitive(vertex_list* vl, int type; int size; void* data);

/*
Add a primitive to the list element currently pointed to.
*/

void vertex_list_add_primitive(vertex_list* vl, int type; int size; void* data);

/*
Return to the beginning of the list.
*/

void vertex_list_reset(vertex_list *vl);

/*
Advance a list. Will return 0 if at end of list.
*/

int vertex_list_advance(vertex_list *vl);



