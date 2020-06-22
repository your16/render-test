#include "vector3.h"

vector3::vector3() :
	x(0.0f), y(0.0f), z(0.0f) {}
vector3::vector3(float x, float y, float z) :
	x(x), y(y), z(z) {}
vector3::vector3(const vector3& obj) :
	x(obj.x), y(obj.y), z(obj.z) {}

vector3& vector3::operator = (const vector3& obj) { x = obj.x; y = obj.y; z = obj.z; return *this; }

vector3 vector3::operator + (const vector3& obj) const { return vector3(x + obj.x, y + obj.y, z + obj.z); }
vector3 vector3::operator - (const vector3& obj) const { return vector3(x - obj.x, y - obj.y, z - obj.z); }
vector3 vector3::operator * (const float value) const { return vector3(x * value, y * value, z * value); }
vector3 vector3::operator / (const float value) const { return vector3(x * value, y * value, z * value); }

vector3& vector3::operator += (const vector3& obj) { x += obj.x;  y += obj.y; z += obj.z; return *this; }
vector3& vector3::operator -= (const vector3& obj) { x -= obj.x; y -= obj.y; z -= obj.z; return *this; }
vector3& vector3::operator *= (const float value) { x *= value; y *= value; z *= value; return *this; }
vector3& vector3::operator /= (const float value) { x /= value; y /= value; z /= value; return *this; }

float vector3::magnitude() const { return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2)); }

void vector3::normalize() { x /= magnitude(); y /= magnitude(); z /= magnitude(); }
vector3 vector3::normalized() const { return vector3(x / magnitude(), y / magnitude(), z / magnitude()); }

std::ostream& operator << (std::ostream& os, const vector3& obj)
{
	os << "[" << obj.x << ", " << obj.y << ", " << obj.z << "]";
	return os;
}