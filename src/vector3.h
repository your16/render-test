#pragma once
#include <cmath>
#include <iostream>

struct vector3
{
	float x;
	float y;
	float z;

	vector3();
	vector3(float x, float y, float z);
	vector3(const vector3& obj);
	vector3(vector3&& obj) = delete;

	vector3& operator = (const vector3& obj);
	//vector3& operator = (vector3&& obj);

	vector3 operator + (const vector3& obj) const;
	vector3 operator - (const vector3& obj) const;
	vector3 operator * (const float value) const;
	vector3 operator / (const float value) const;

	vector3& operator += (const vector3& obj);
	vector3& operator -= (const vector3& obj);
	vector3& operator *= (const float value);
	vector3& operator /= (const float value);

	float magnitude() const;

	void normalize();
	vector3 normalized() const;

	friend std::ostream& operator << (std::ostream& os, const vector3& obj);
};