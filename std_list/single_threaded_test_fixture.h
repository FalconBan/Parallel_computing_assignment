#pragma once

#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <iostream>

#include <linked_list.h>

#define MAX_RANDOM 65535

using namespace std;

class single_threaded_test_fixture
{
public:

	virtual void perform_operations(int range, int insert_count, int access_count, int del_count)
	{
		vector<int> all_operations(insert_count + access_count + del_count);
		for (auto i = 0; i < insert_count; ++i)
		{
			all_operations[i] = 0;
		}

		for (auto i = insert_count; i < insert_count + access_count; ++i)
		{
			all_operations[i] = 1;
		}

		for (auto i = insert_count + access_count; i < insert_count + access_count + del_count; ++i)
		{
			all_operations[i] = 2;
		}

		chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
		for (auto operation : all_operations)
		{
			switch (operation)
			{
			case 0:
				insert();
				break;

			case 1:
				get_member();
				break;

			case 2:
				delete_member();
				break;
			}
		}
		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
		m_duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
	}

	int m_duration = 0;

protected:

	void insert()
	{
        int random_value = rand() % MAX_RANDOM;
		m_list.add(random_value);
		++m_cur_index;
	}

	void delete_member()
	{
		if (m_list.get_node_count() != 0)
		{
			int index_to_delete = rand()%(m_list.get_node_count());
			m_list.delete_member(index_to_delete);
		}
	}

	void get_member()
	{
		if (m_list.get_node_count() != 0)
		{
			int index_to_recall = rand()%(m_list.get_node_count());
			m_list.get_by_index(index_to_recall);
		}
	}

	linked_list m_list;

private:
	int m_cur_index = 0;
};
