#pragma once

#include <list>

typedef unsigned data_type;

class linked_list
{
public:
	linked_list() = default;
	virtual ~linked_list() = default;

	virtual void add(data_type val);
	virtual const bool member(data_type val);
	virtual void remove(data_type val);
	virtual const data_type get_by_index(int index);
	virtual void delete_member(int index);
	virtual size_t get_node_count() { return m_list.size(); }

	virtual void print_list();

protected:
	std::list<data_type> m_list;
};
