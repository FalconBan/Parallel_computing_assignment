#include <linked_list.h>
#include <iostream>
#include <malloc.h>

void linked_list::add(data_type val)
{
	if (m_head == nullptr)
	{
		struct node* temp = NULL;
		temp = (node*)(malloc(sizeof(struct node)));
		temp->m_data = val;
		temp->m_next = nullptr;
		m_head = temp;
		m_tail = m_head;
	}
	else
	{
		struct node* temp = NULL;
		temp = (node*)(malloc(sizeof(struct node)));
		temp->m_data = val;
		temp->m_next = nullptr;
		m_tail->m_next = temp;
		m_tail = m_tail->m_next;
	}

	++m_node_count;
}

const node* linked_list::member(data_type val)
{
	if (m_head)
	{
		auto cur_node = m_head;

		while (cur_node)
		{
			if (cur_node->m_data == val)
			{
				return cur_node;
			}
			else
				cur_node = cur_node->m_next;
		}
	}

	return nullptr;
}

void linked_list::remove(data_type val)
{
	if (m_head)
	{
		auto cur_node = m_head;
		node* prev_node = nullptr;

		while (cur_node)
		{
			if (cur_node->m_data == val)
			{
				if (prev_node)
				{
					prev_node->m_next = cur_node->m_next;
				}
				else
				{
					m_head = cur_node->m_next;
				}

				free(cur_node);
				cur_node = nullptr;
				--m_node_count;
			}
			else
			{
				prev_node = cur_node;
				cur_node = cur_node->m_next;
			}
		}
	}
}

void linked_list::print_list()
{
	if (m_head)
	{
		auto cur_node = m_head;

		while (cur_node)
		{
			std::cout << cur_node->m_data << std::endl;
			cur_node = cur_node->m_next;
		}
	}
}

void linked_list::delete_member(int index)
{
	if (index < m_node_count)
	{
		auto cur_node = m_head;
		node* prev_node = nullptr;
		int cur_index = 0;

		while (true)
		{
			if (cur_node == nullptr)
				break;

			if (cur_index == index)
			{
				if (prev_node)
				{
					prev_node->m_next = cur_node->m_next;
				}
				else
				{
					m_head = cur_node->m_next;
				}

				free(cur_node);
				cur_node = nullptr;
				--m_node_count;
			}
			else
			{
				prev_node = cur_node;
				cur_node = cur_node->m_next;
				++cur_index;
			}
		}
	}
}

const node* linked_list::get_by_index(int index)
{
	if (index < m_node_count)
	{
		auto cur_node = m_head;
		int cur_index = 0;

		while (true)
		{
			if (cur_node == nullptr)
				break;

			if (cur_index == index)
			{
				return cur_node;
			}
			else
			{
				cur_node = cur_node->m_next;
				++cur_index;
			}
		}
	}

	return nullptr;
}
