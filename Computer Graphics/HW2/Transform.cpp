// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
    mat3 R;
    mat3 I = mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);
    mat3 aa_t = glm::outerProduct(axis, axis);
    mat3 A = mat3(0, axis.z, -axis.y,
        -axis.z, 0, axis.x,
        axis.y, -axis.x, 0);

    R = cos(degrees / 180.0f * pi) * I + (1 - cos(degrees / 180.0f * pi)) * aa_t + sin(degrees / 180.0f * pi) * A;
    return R;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
    eye = Transform::rotate(degrees, up) * eye;
    up = Transform::rotate(degrees, up) * up;    
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE 
    // Likely the same as in HW 1.  
    vec3 axis = glm::cross(eye, up);
    up = glm::normalize(Transform::rotate(degrees, axis) * up);
    eye = Transform::rotate(degrees, axis) * eye;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
    vec3 w = glm::normalize(eye - center);
    vec3 u = glm::normalize(glm::cross(glm::normalize(up), w));
    vec3 v = glm::normalize(glm::cross(w, u));
    mat4 res = mat4(u.x, u.y, u.z, dot(u, -eye),
                    v.x, v.y, v.z, dot(v, -eye),
                    w.x, w.y, w.z, dot(w, -eye),
                    0, 0, 0, 1);
    // You will change this return call
    return glm::transpose(res);
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    // YOUR CODE FOR HW2 HERE
    // New, to implement the perspective transform as well.  

    mat4 ret = mat4(1 / tan(0.5 * fovy * pi / 180.0) / aspect, 0, 0, 0, 
                    0, 1 / tan(0.5 * fovy * pi / 180.0), 0, 0, 
                    0, 0, -(zFar + zNear) / (zFar - zNear), -1, 
                    0, 0, -2 * zFar * zNear / (zFar - zNear), 0);

    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{    // YOUR CODE FOR HW2 HERE
    // Implement scaling 

    mat4 ret = mat4(sx, 0, 0, 0, 
                    0, sy, 0, 0, 
                    0, 0, sz, 0, 
                    0, 0, 0, 1.0f);

    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{    
    // YOUR CODE FOR HW2 HERE
    // Implement translation 

    mat4 ret = mat4(1.0f, 0, 0, 0,
                    0, 1, 0, 0, 
                    0, 0, 1, 0, 
                    tx, ty, tz, 1);

    return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    return glm::normalize(y);
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
