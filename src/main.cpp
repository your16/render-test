#pragma warning(disable:4996)

#include "serializable_list.h"
#include "vector3.h"

#include <iostream>
#include <sstream>
#include <cstdio>

#include <chrono>
#include <random>

#include <bitset>
#include <vector>
#include <utility>

const unsigned int FACES = 4;
const unsigned int VERTS = 6;
const unsigned int VERTS_PER_FACE = 3;

std::string to_bin(const unsigned int value);
void calc_mesh_normals(vector3* normals, const vector3* verts,
	const unsigned int* faces, unsigned int nverts, unsigned int nfaces);

void task_1(const unsigned int n = 1);
void task_2(const char* file_name, const std::vector<std::string>& list_data,
	const std::vector<std::pair<unsigned int, unsigned int>>& rands);
void task_3(const vector3* verts, const unsigned int* faces, vector3* normals, unsigned int nverts, unsigned int nfaces);

int main()
{
	task_1(3);

	std::vector<std::string> data = { "Hello", ", ", "Kitty", "!" };
	std::vector<std::pair<unsigned int, unsigned int>> rands = { {0, 3}, {1, 2}, {2, 1}, {3, 0} };
	task_2("test.bin", data, rands);

	vector3 normals[VERTS];
	vector3 verticies[VERTS] = { vector3(0.0f, 5.0f, 0.0f), vector3(0.0f, 5.0f, 5.0f),
								 vector3(5.0f, 5.0f, 5.0f), vector3(5.0f, 5.0f, 0.0f),
								 vector3(5.0f, 0.0f, 5.0f), vector3(0.0f, 0.0f, 5.0f) };
	unsigned int faces[FACES * VERTS_PER_FACE] = { 0, 1, 2, 0, 2, 3, 1, 2, 4, 1, 4, 5 };

	task_3(verticies, faces, normals, VERTS, FACES);

	std::cin.get();
}


void task_1(const unsigned int n)
{
	std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
	for (unsigned int i = 0; i < n; i++)
	{
		int test_number = rng();
		std::bitset<sizeof(test_number) * 8> bit(test_number);
		std::cout << "std::bitset: " << test_number << " -> " << bit << std::endl;
		std::cout << "to_bin: " << test_number << " -> " << to_bin(test_number) << std::endl;
	}
	std::cout << std::endl;
}

void task_2(const char* file_name, const std::vector<std::string>& list_data,
	const std::vector<std::pair<unsigned int, unsigned int>>& rands)
{
	FILE* file;
	slist test_list_a;
	slist test_list_b;

	for (unsigned int n = 0; n < list_data.size(); n++)
		test_list_a.push_back(list_data[n]);
	for (unsigned int n = 0; n < rands.size(); n++)
		test_list_a.set_rand(rands[n].first, rands[n].second);

	std::cout << "test_list_a: " << test_list_a << std::endl;

	file = fopen(file_name, "wb");
	if (!file)
		return;
	else
	{
		test_list_a.serialize(file);
		fclose(file);
	}

	file = fopen(file_name, "rb");
	if (!file)
		return;
	else
	{
		test_list_b.deserialize(file);
		fclose(file);
	}

	std::cout << "test_list_b: " << test_list_b << std::endl;
	std::cout << std::endl;
}

void task_3(const vector3* verts, const unsigned int* faces, vector3* normals, unsigned int nverts, unsigned int nfaces)
{
	calc_mesh_normals(normals, verts, faces, nverts, nfaces);
	for (unsigned int n = 0; n < nverts; n++)
		std::cout << "normal " << n + 1 << ": " << normals[n] << std::endl;
	std::cout << std::endl;
}

std::string to_bin(const unsigned int value)
{
	std::stringstream s_stream;
	for (int offset = (sizeof(value) * 8) - 1; offset >= 0; offset--)
		s_stream << (value >> offset & 1);
	return s_stream.str();
}

void calc_mesh_normals(vector3* normals, const vector3* verts,
	const unsigned int* faces, unsigned int nverts, unsigned int nfaces)
{
	for (unsigned int n = 0; n < nfaces; n++)
	{
		unsigned int offset = VERTS_PER_FACE * n;

		vector3 vec_a = verts[faces[1 + offset]] - verts[faces[offset]];
		vector3 vec_b = verts[faces[2 + offset]] - verts[faces[offset]];

		vector3 face_normal;
		face_normal.x = (vec_a.y * vec_b.z) - (vec_a.z * vec_b.y);
		face_normal.y = (vec_a.z * vec_b.x) - (vec_a.x * vec_b.z);
		face_normal.z = (vec_a.x * vec_b.y) - (vec_a.y * vec_b.x);

		normals[faces[offset]] = normals[faces[offset]] + face_normal;
		normals[faces[1 + offset]] = normals[faces[1 + offset]] + face_normal;
		normals[faces[2 + offset]] = normals[faces[2 + offset]] + face_normal;
	}

	for (unsigned int n = 0; n < nverts; n++)
		normals[n].normalize();
}