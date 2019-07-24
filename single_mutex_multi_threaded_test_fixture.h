#pragma once

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <atomic>
#include <pthread.h>

#include <linked_list_single_mutex.h>

using namespace std;

extern vector<unsigned>* g_remainingNumbers;
extern vector<unsigned>* g_chosenNumbers;

namespace mutex
{
	linked_list_single_mutex m_list;
	int m_cur_index = 0;

	pthread_mutex_t time_measure_lock;
	int time_taken_us = 0;

	void insert()
	{
		m_list.add((*g_chosenNumbers)[m_cur_index]);
		++m_cur_index;
	}

	void delete_member()
	{
		int index_to_delete = rand()%(m_list.get_node_count());
		m_list.delete_member(index_to_delete);
	}

	void get_member()
	{
		int index_to_recall = rand()%(m_list.get_node_count());
		m_list.get_by_index(index_to_recall);
	}

	void* thread_function(void* operations_vector)
	{
		auto operations_vec = (vector<int>*)(operations_vector);

		chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
		for (auto operation:*(operations_vec))
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
		int duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

		pthread_mutex_lock(&time_measure_lock);
		time_taken_us = ((time_taken_us > duration) ? time_taken_us : duration);
		pthread_mutex_unlock(&time_measure_lock);

		return nullptr;
	}

	class single_mutex_multi_threaded_test_fixture
	{
	public:

		void perform_operations(int thread_count, int range, int insert, int access, int del)
		{
			time_taken_us = 0;
			generate_unique_random(static_cast<unsigned>(pow(2, 16)), range);

			int total_operations = insert + access + del;
			int operations_per_thread = total_operations/thread_count;
			vector<int>* thread_operation_vectors[thread_count];

			for (auto i = 0; i < thread_count; ++i)
			{
				thread_operation_vectors[i] = new vector<int>(operations_per_thread);

				auto inserts_per_thread = insert/thread_count;
				for (auto ins = 0; ins < inserts_per_thread; ++ins)
				{
					(*thread_operation_vectors[i])[ins] = 0;
				}

				auto access_per_thread = access/thread_count;
				for (auto acc = inserts_per_thread; acc < inserts_per_thread + access_per_thread; ++acc)
				{
					(*thread_operation_vectors[i])[acc] = 1;
				}

				auto del_per_thread = del/thread_count;
				for (auto dels = inserts_per_thread + access_per_thread;
						dels < inserts_per_thread + access_per_thread + del_per_thread; ++dels)
				{
					(*thread_operation_vectors[i])[dels] = 2;
				}
			}

			//Create the pthreads
			m_threads = new pthread_t[thread_count];

			for (auto i = 0; i < thread_count; ++i)
			{
				pthread_create(&m_threads[i], NULL, &thread_function, (void*)(thread_operation_vectors[i]));
			}

			for (auto i = 0; i < thread_count; ++i)
			{
				pthread_join(m_threads[i], NULL);
			}

			delete g_chosenNumbers;
			delete g_remainingNumbers;
		}

		void generate_unique_random(const unsigned int range, const unsigned int  numberToSelect)
		{
			g_remainingNumbers = new vector<unsigned>(range);
			g_chosenNumbers = new vector<unsigned>(numberToSelect);

			/* Initialise the list of possible choices */
			for(unsigned i = 0; i < range; i++) (*g_remainingNumbers)[i] = i;

			/* Now chose however many you want, without repeats */
			for(unsigned i = 0; i < numberToSelect; i++){
			   /* Generate a random number to select */
			   int selectedElement = rand()%(range - i);

			   /* Put it in the chosenNumbers vector */
			   (*g_chosenNumbers)[i] = (*g_remainingNumbers)[selectedElement];

			   /* Now erase this number from the possible numbers, so that it can't be chosen again */
			   for(unsigned j = selectedElement; j < range - i - 1; j++)
				  (*g_remainingNumbers)[j] = (*g_remainingNumbers)[j + 1];
			}
		}

	private:
		pthread_t* m_threads;
	};
}
