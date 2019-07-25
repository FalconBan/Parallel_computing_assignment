#include <linked_list.h>
#include <iostream>
#include <malloc.h>

void linked_list::add(data_type val)
{
	m_list.push_back(val);
}

const bool linked_list::member(data_type val)
{
	for (auto entry : m_list)
	{
		if (entry == val)
			return true;
	}

	return false;
}

void linked_list::remove(data_type val)
{
	m_list.remove(val);
}

void linked_list::print_list()
{
	for (auto itr = m_list.begin(); itr != m_list.end(); ++itr)
	{
		std::cout << *itr << std::endl;
	}
}

void linked_list::delete_member(int index)
{
	if (index < m_list.size())
	{
		int cur_index = 0;
		for (auto itr = m_list.begin(); itr != m_list.end(); ++itr)
		{
			if (cur_index == index)
			{
				m_list.remove(*itr);
				break;
			}
			++cur_index;
		}
	}
}

const data_type linked_list::get_by_index(int index)
{
	if (index < m_list.size())
	{
		int cur_index = 0;
		for (auto itr = m_list.begin(); itr != m_list.end(); ++itr)
		{
			if (cur_index == index)
			{
				return *itr;
			}
			++cur_index;
		}
	}

	return 0;
}
