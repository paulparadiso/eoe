#include "../vec4.h"

void test_set_angle(){
	quat* q = quat_create();
	float i;
	for(i = 0.0; i < 1.0; i += 0.08){
		printf("Set angle test - %f\n", i);
		quat_set_angle(q, i);
		quat_print(q);
	}
}

void test_set_axis(){
	quat* q = quat_create();
	float i;
	for(i = 0.0; i < 100.0; i += 0.98){
		float x = i;
		float y = i * 1.03;
		float z = i * 1.23;
		printf("Set axis test - %f, %f, %f\n", x, y, x);
		quat_set_axis(q, x, y, z);
		quat_print(q);
	}
}

void test_rotate_x(){
	quat* q = quat_create();
	float i;
	for(i = 0.0; i < 100.0; i += 0.98){
		quat_rotate_x(q, i);
		quat_print(q);
	}
	quat_free(q);
}

void test_rotate_y(){
	quat* q = quat_create();
	float i;
	for(i = 0.0; i < 100.0; i += 0.98){
		quat_rotate_y(q, i);
		quat_print(q);
	}
	quat_free(q);
}

void test_rotate_z(){
	quat* q = quat_create();
	float i;
	for(i = 0.0; i < 100.0; i += 0.98){
		quat_rotate_z(q, i);
		quat_print(q);
	}
	quat_free(q);
}

void test_rotate_axis(){
	quat* q = quat_create();
	vec4d v = {
		.x = 2.31,
		.y = 1.42,
		.z = 0.44
	};
	float i;
	for(i = 0.0; i < 100.0; i += 0.98){
		quat_rotate_axis(q, i, &v);
		quat_print(q);
	}
	quat_free(q);
}

void test_dot(quat *q, quat* p){
	float d = quat_dot(q,p);
	printf("Dot = %f\n", d);
}

void test_cross(quat* q, quat* p){
	quat* o = quat_create();
	quat_cross(q,p,o);
	quat_print(o);
}

void test_norm(quat* q){}

void test_con(quat* q){}

void test_pow(quat* q){}

void test_slerp(quat* q, quat* p){}

int main(int* argc, char** argv){
	quat* q1 = quat_create();
	quat_set_angle(q1, 23.7);
	quat_set_axis(q1, 2.0, 3.0, 4.0);

	quat* q2 = quat_create();
	quat_set_angle(q2, 109.3);
	quat_set_axis(q2, 0.2, -1.3, 2.5);

	quat_print(q1);

	quat_print(q2);

	//test_set_angle();
	//test_set_axis();
	//test_rotate_x();
	//test_rotate_y();
	//test_rotate_z();
	//test_rotate_axis();
	//test_dot(q1, q2);
	test_cross(q1, q2);
	//test_norm(quat* q);
	//test_con(quat* q);
	//test_pow(quat* q);
	//test_slerp(quat* q, quat* p);

	return 0;
}