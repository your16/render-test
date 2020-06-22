#include "serializable_list.h"

slist_node::slist_node() :
	prev(nullptr), next(nullptr), rand(nullptr), data("") {}

slist_node::slist_node(const std::string& data) :
	prev(nullptr), next(nullptr), rand(nullptr), data(data) {}

slist::slist()
	: _begin(nullptr), _end(nullptr), _size(0) {}

slist::~slist()
{
	while (_end)
	{
		_end = _begin->next;
		delete _begin;
		_begin = _end;
	}
}

void slist::push_back(const std::string& data)
{
	slist_node* temp = new slist_node(data);
	if (!_begin)
		_begin = temp;
	else
	{
		temp->prev = _end;
		_end->next = temp;
	}
	_end = temp;
	_size++;
}

void slist::push_front(const std::string& data)
{
	slist_node* temp = new slist_node(data);
	if (!_begin)
		_end = temp;
	else
	{
		temp->next = _begin;
		_begin->prev = temp;
	}
	_begin = temp;
	_size++;
}

void slist::set_rand(const unsigned int node_index, const unsigned int point_to_index)
{
	if (_begin &&
		(node_index >= 0 && node_index < _size) &&
		(point_to_index >= 0 && point_to_index < _size))
	{
		slist_node* node = nullptr;
		slist_node* point_to = nullptr;
		slist_node* temp = _begin;

		for (unsigned int n = 0; n < _size; n++)
		{
			if (n == node_index)
				node = temp;
			if (n == point_to_index)
				point_to = temp;
			if (node && point_to)
			{
				node->rand = point_to;
				break;
			}
			temp = temp->next;
		}
	}
	else
		return;
}

void slist::serialize(FILE* file)
{
	if (!_begin)
		return;
	else
	{
		slist_node* temp = _begin;

		unsigned int idx = 1;
		std::unordered_map<slist_node*, unsigned int> ptr_to_idx;
		ptr_to_idx.reserve(_size);

		fwrite(&_size, sizeof(_size), 1, file);
		while (temp)
		{
			size_t buffer_size = temp->data.size();
			fwrite(&buffer_size, sizeof(buffer_size), 1, file);

			const char* buffer = temp->data.data();
			fwrite(buffer, sizeof(char) * buffer_size, 1, file);

			ptr_to_idx[temp] = idx++;
			temp = temp->next;
		}

		temp = _begin;
		while (temp)
		{
			idx = (temp->rand) ? ptr_to_idx[temp->rand] : 0;
			fwrite(&idx, sizeof(idx), 1, file);
			temp = temp->next;
		}
	}
}

void slist::deserialize(FILE* file)
{
	if (_begin)
		return;
	else
	{
		size_t list_size;
		fread(&list_size, sizeof(list_size), 1, file);

		std::unordered_map<unsigned int, slist_node*> idx_to_ptr;
		idx_to_ptr.reserve(list_size);

		for (unsigned int n = 0; n < list_size; n++)
		{
			size_t buffer_size;
			fread(&buffer_size, sizeof(buffer_size), 1, file);

			char* buffer = new char[buffer_size + 1];
			buffer[buffer_size] = 0;
			fread(buffer, sizeof(char) * buffer_size, 1, file);

			push_back(buffer);
			delete[] buffer;

			idx_to_ptr[n + 1] = _end;
		}

		slist_node* temp = _begin;
		while (temp)
		{
			unsigned int idx;
			fread(&idx, sizeof(idx), 1, file);
			temp->rand = (idx > 0) ? idx_to_ptr[idx] : nullptr;
			temp = temp->next;
		}
	}
}

std::ostream& operator << (std::ostream& os, const slist& obj)
{
	slist_node* temp = obj._begin;
	while (temp)
	{
		os << temp->data;
		temp = temp->next;
	}
	return os;
}