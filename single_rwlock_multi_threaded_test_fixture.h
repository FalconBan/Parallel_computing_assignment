#pragma once

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <atomic>
#include <pthread.h>

#include <linked_list.h>

using namespace std;

namespace rwlock
{
	pthread_rwlock_t m_list_lock;
	linked_list m_list;

	pthread_mutex_t time_measure_lock;
	int time_taken_us = 0;

	void insert()
	{
		pthread_rwlock_wrlock(&m_list_lock);
		m_list.add(1);
		pthread_rwlock_unlock(&m_list_lock);
	}

	void delete_member()
	{
		pthread_rwlock_wrlock(&m_list_lock);
		int index_to_delete = rand()%(m_list.get_node_count());
		m_list.delete_member(index_to_delete);
		pthread_rwlock_unlock(&m_list_lock);
	}

	void get_member()
	{
		pthread_rwlock_rdlock(&m_list_lock);
		int index_to_recall = rand()%(m_list.get_node_count());
		m_list.get_by_index(index_to_recall);
		pthread_rwlock_unlock(&m_list_lock);
	}

	void* thread_function(void* operations_vector)
	{
		auto operations_vec = (vector<int>*)(operations_vector);

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

		return nullptr;
	}

	class rwlock_multi_threaded_test_fixture
	{
	public:

		void perform_operations(int thread_count, int range, int insert, int access, int del)
		{
			time_taken_us = 0;
			pthread_rwlock_init(&m_list_lock, NULL);

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

			chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

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

			chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
			time_taken_us = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

			pthread_rwlock_destroy(&m_list_lock);
		}

	private:
		pthread_t* m_threads;
	};
}
