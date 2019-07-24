#pragma once

typedef unsigned data_type;

struct node
{
	node(data_type val) { m_data = val; }
	node* m_next = nullptr;
	data_type m_data;
};

class linked_list
{
public:
	linked_list() = default;
	virtual ~linked_list() = default;

	virtual void add(data_type val);
	virtual const node* member(data_type val);
	virtual void remove(data_type val);
	virtual const node* get_by_index(int index);
	virtual void delete_member(int index);
	int get_node_count() { return m_node_count; }

	virtual void print_list();

protected:
	node* m_head = nullptr;
	node* m_tail = nullptr;
	int m_node_count = 0;
};
