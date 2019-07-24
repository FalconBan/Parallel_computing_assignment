#pragma once

#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <iostream>

#include <linked_list.h>

using namespace std;

extern vector<unsigned>* g_remainingNumbers;
extern vector<unsigned>* g_chosenNumbers;

class single_threaded_test_fixture
{
public:
	void perform_operations(int range, int insert_count, int access_count, int del_count)
	{
		generate_unique_random(static_cast<unsigned>(pow(2, 16)), range);

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

		//Randomize the vector
		//std::random_shuffle(all_operations.begin(), all_operations.end());

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

		delete g_chosenNumbers;
		delete g_remainingNumbers;
	}

	int m_duration = 0;

protected:

	void insert()
	{
		m_list.add((*g_chosenNumbers)[m_cur_index]);
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

	void generate_unique_random(const unsigned int range, const unsigned int  numberToSelect)
	{
	    g_remainingNumbers = new vector<unsigned>(range);
	    g_chosenNumbers = new vector<unsigned>(numberToSelect);

	    //Initialise the list of possible choices
	    for(unsigned i = 0; i < range; i++) (*g_remainingNumbers)[i] = i;

	    //Now chose however many you want, without repeats
	    for(unsigned i = 0; i < numberToSelect; i++){
	       //Generate a random number to select
	       int selectedElement = rand()%(range - i);

	       //Put it in the chosenNumbers vector
	       (*g_chosenNumbers)[i] = (*g_remainingNumbers)[selectedElement];

	       //Now erase this number from the possible numbers, so that it can't be chosen again
	       for(unsigned j = selectedElement; j < range - i - 1; j++)
	          (*g_remainingNumbers)[j] = (*g_remainingNumbers)[j + 1];
	    }
	}

private:
	linked_list m_list;
	int m_cur_index = 0;
};
