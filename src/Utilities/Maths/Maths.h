#pragma once
#include <iostream>
#include <cmath>

#define PI 3.14159

//Vectors
struct vec3 {
	float x;
	float y;
	float z;
	vec3() : x(0.0f), y(0.0f), z(0.0f) {}
	vec3(float x_val, float y_val, float z_val) : x(x_val), y(y_val), z(z_val) {}

	float magnitude() const
	{
		return std::sqrt((x * x) + (y * y) + (z * z));
	}

	float sqMagnitude() const
	{
		return (x * x) + (y * y);
	}

	float length() const
	{
		return magnitude();
	}

	vec3 operator-(vec3 other) const
	{
		return vec3(x - other.x, y - other.y, z - other.z);
	}

	vec3 operator+(vec3 other) const
	{
		return vec3(x + other.x, y + other.y, z + other.z);
	}

	vec3& operator-=(const vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	vec3 operator*(float scalar) const {
		return vec3(x * scalar, y * scalar, z * scalar);
	}

	vec3 operator/(float scalar) const {
		return vec3(x / scalar, y / scalar, z / scalar);
	}

	vec3& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	vec3 operator*(const vec3& other) const {
		return vec3(x * other.x, y * other.y, z * other.z);
	}

	vec3& operator*=(const vec3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	vec3& operator+=(const vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec3& operator+(const vec3& other) {
		return vec3(x + other.x, y + other.y, z + other.z);
	}

	bool operator==(const vec3& other)
	{
		return (x == other.x && y == other.y && z == other.z);
	}
	
	bool operator!=(const vec3& other)
	{
		return (x != other.x || y != other.y || z != other.z);
	}

	bool operator<(const vec3 & other)
	{
		return magnitude() < other.magnitude();
	}

	bool operator>(const vec3& other)
	{
		return magnitude() > other.magnitude();
	}
};

struct vec4 {
	float x, y, z, w;
	vec4(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f, float w_ = 0.0f) : x(x_), y(y_), z(z_), w(w_) {}
	

	vec3 toVec3() const { return vec3(x, y, z); }
};

//Matrices
struct mat4 {
	float elements[16];
	mat4()
	{
		for (int i = 0; i < 16; i++)
		{
			elements[i] = 0;
		}
	};

	//mat4 * vec4
	vec4 operator*(const vec4& v) const {
		vec4 result;
		result.x = elements[0] * v.x + elements[4] * v.y + elements[8] * v.z + elements[12] * v.w;
		result.y = elements[1] * v.x + elements[5] * v.y + elements[9] * v.z + elements[13] * v.w;
		result.z = elements[2] * v.x + elements[6] * v.y + elements[10] * v.z + elements[14] * v.w;
		result.w = elements[3] * v.x + elements[7] * v.y + elements[11] * v.z + elements[15] * v.w;
		return result;
	}

	//mat4 * mat4
	mat4 operator*(const mat4& other) const {
		mat4 result;
		for (int row = 0; row < 4; ++row) {
			for (int col = 0; col < 4; ++col) {
				float sum = 0.0f;
				for (int i = 0; i < 4; ++i) {
					sum += this->elements[i * 4 + row] * other.elements[col * 4 + i];
				}
				result.elements[col * 4 + row] = sum;
			}
		}
		return result;
	}
};

//Matrix Utilities
inline vec3 cross(vec3 a, vec3 b)
{
	vec3 c;
	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return c;
}

inline float dot(vec3 a, vec3 b)
{
	vec3 c;
	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
	return c.x + c.y + c.z;
}

inline vec3 normalize(vec3 a)
{
	float dist = (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
	dist = sqrtf(dist);

	if (dist == 0.0f) return { 0.0f , 0.0f , 0.0f};
	a.x = a.x / dist;
	a.y = a.y / dist;
	a.z = a.z / dist;
	return a;
}

//Transformations matrix
inline mat4 createTranformationMatrix(vec3 translation, float theta)
{
	theta = theta * PI / 180.0f;
	float cosTheta = cosf(theta);
	float sinTheta = sinf(theta);

	mat4 transformation;
	transformation.elements[0] = cosTheta;
	transformation.elements[1] = sinTheta;
	transformation.elements[2] = 0.0f;
	transformation.elements[3] = 0.0f;
						 
	transformation.elements[4] = -sinTheta;
	transformation.elements[5] = cosTheta;
	transformation.elements[6] = 0.0f;
	transformation.elements[7] = 0.0f;
						 
	transformation.elements[8] = 0.0f;
	transformation.elements[9] = 0.0f;
	transformation.elements[10] = 1.0f;
	transformation.elements[11] = 0.0f;
						 
	transformation.elements[12] = translation.x;
	transformation.elements[13] = translation.y;
	transformation.elements[14] = translation.z;
	transformation.elements[15] = 1.0f;

	return transformation;
}

inline mat4 lookAt(vec3 from, vec3 to)
{
	vec3 global_up = { 0.0f, 1.0f, 0.0f };
	vec3 forward = {
		to.x - from.x,
		to.y - from.y,
		to.z - from.z
	};
	forward = normalize(forward);

	vec3 right = cross(forward, global_up);
	right = normalize(right);

	vec3 up = cross(right, forward);

	mat4 view;
	view.elements[0] = right.x;
	view.elements[1] = up.x;
	view.elements[2] = -forward.x;
	view.elements[3] = 0.0f;

	view.elements[4] = right.y;
	view.elements[5] = up.y;
	view.elements[6] = -forward.y;
	view.elements[7] = 0.0f;

	view.elements[8] = right.z;
	view.elements[9] = up.z;
	view.elements[10] = -forward.z;
	view.elements[11] = 0.0f;

	view.elements[12] = -dot(right , from);
	view.elements[13] = -dot(up, from);
	view.elements[14] = dot(forward, from);
	view.elements[15] = 1.0f;

	return view;
}

inline mat4 projectionOrtho(float l, float r, float b, float t, float n , float f)
{
	mat4 projection;
	projection.elements[0] = 2.0f / (r - l);
	projection.elements[1] = 0.0f;
	projection.elements[2] = 0.0f;
	projection.elements[3] = 0.0f;
	
	projection.elements[4] = 0.0f;
	projection.elements[5] = 2.0f / (t - b);
	projection.elements[6] = 0.0f;
	projection.elements[7] = 0.0f;
	
	projection.elements[8] = 0.0f;
	projection.elements[9] = 0.0f;
	projection.elements[10] = -2.0 / (f - n);
	projection.elements[11] = 0.0f;
	
	projection.elements[12] = -(r + l) / (r - l);
	projection.elements[13] = -(t + b) / (t - b);
	projection.elements[14] = -(f + n) / (f - n);
	projection.elements[15] = 1.0f;

	return projection;
}