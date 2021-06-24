// Transform.cpp: implementation of the Transform class.

#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
    // YOUR CODE FOR HW1 HERE
	mat3 R;
	mat3 I = mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);
	mat3 aa_t = glm::outerProduct(axis, axis);
	mat3 A = mat3(0, axis.z, -axis.y, 
		-axis.z, 0, axis.x, 
		axis.y, -axis.x, 0);

	R = cos(degrees / 180.0f * pi) * I + (1 - cos(degrees / 180.0f * pi)) * aa_t + sin(degrees / 180.0f * pi) * A;
	// Axis-Angle formula: https://learning.edx.org/course/course-v1:UCSanDiegoX+CSE167x+2T2018/block-v1:UCSanDiegoX+CSE167x+2T2018+type@sequential+block@L4/block-v1:UCSanDiegoX+CSE167x+2T2018+type@vertical+block@vertical_c05677f28575
  
    // You will change this return call
    return R;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
	eye = Transform::rotate(degrees, up) * eye;
	up = Transform::rotate(degrees, up) * up;
	printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
    // YOUR CODE FOR HW1 HERE 
	vec3 axis = glm::cross(eye, up);
	axis = glm::normalize(axis);
	up = Transform::rotate(degrees, axis) * up;
	eye = Transform::rotate(degrees, axis) * eye;
	printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(glm::normalize(up), w));
	vec3 v = glm::normalize(glm::cross(w, u));
  /*
	glm::mat4 rotation = glm::mat4(
		u.x, u.y, u.z, 0, 
		v.x, v.y, v.z, 0, 
		w.x, w.y, w.z, 0, 
		0, 0, 0, 1);
	mat4 translation = glm::mat4(
		1, 0, 0, -eye.x, 
		0, 1, 0, -eye.y, 
		0, 0, 1, -eye.z, 
		0, 0, 0, 1);
  */
	// mat4 res = glm::cross(rotation, translation);
	mat4 res = mat4(u.x, u.y, u.z, dot(u, -eye),
		v.x, v.y, v.z, dot(v, -eye),
		w.x, w.y, w.z, dot(w, -eye),
		0, 0, 0, 1);
  // You will change this return call
	return glm::transpose(res); // rotation*translation;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}