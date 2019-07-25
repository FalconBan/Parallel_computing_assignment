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

#define MAX_RANDOM 65535

namespace rwlock
{
	pthread_rwlock_t list_rwlock;
	linked_list* m_list;

	pthread_mutex_t time_measure_lock;
	int time_taken_us = 0;

	void insert()
	{
        int random_value = rand() % MAX_RANDOM;
		pthread_rwlock_wrlock(&list_rwlock);
		m_list->add(random_value);
		pthread_rwlock_unlock(&list_rwlock);
	}

	void delete_member()
	{
		pthread_rwlock_wrlock(&list_rwlock);
		auto node_count = m_list->get_node_count();

		if (node_count != 0)
		{
			int index_to_delete = rand()%(node_count);
			m_list->delete_member(index_to_delete);
		}
		pthread_rwlock_unlock(&list_rwlock);
	}

	void get_member()
	{
		pthread_rwlock_rdlock(&list_rwlock);
		auto node_count = m_list->get_node_count();

		if (node_count != 0)
		{
			int index_to_recall = rand()%(node_count);
			m_list->get_by_index(index_to_recall);
		}
		pthread_rwlock_unlock(&list_rwlock);
	}

	void* thread_function(void* operations_vector)
	{
		chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
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

		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
		int time_taken = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

		pthread_mutex_lock(&time_measure_lock);
		time_taken_us = (time_taken > time_taken_us) ? time_taken : time_taken_us;
		pthread_mutex_unlock(&time_measure_lock);

		return nullptr;
	}

	class rwlock_multi_threaded_test_fixture
	{
	public:

		void perform_operations(int thread_count, int range, int insert, int access, int del)
		{
			time_taken_us = 0;
			pthread_rwlock_init(&list_rwlock, NULL);
			pthread_mutex_init(&time_measure_lock, NULL);
			m_list = new linked_list;

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

			std::cout << "####---- Rwlock test ----####" << std::endl;
			for (auto i = 0; i < thread_count; ++i)
			{
				std::cout << "Elements per thread: " << (*thread_operation_vectors[i]).size() << std::endl;
			}
			std::cout << "############################" << std::endl;

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

			pthread_rwlock_destroy(&list_rwlock);
			pthread_mutex_destroy(&time_measure_lock);
			delete m_list;
		}

	private:
		pthread_t* m_threads;
	};
}
