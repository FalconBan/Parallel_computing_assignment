#pragma once

#include <pthread.h>
#include <iostream>

void* test_thread_function(void* count)
{
	std::cout << "Thread id : " << reinterpret_cast<long>(count) << std::endl;
	return NULL;
}

class thread_creator
{
public:

	void create_threads(int thread_count)
	{
		pthread_t* threads = new pthread_t[thread_count];

		for (long i=0; i < thread_count; ++i)
		{
			pthread_create(&threads[i], NULL, &test_thread_function, (void*)i);
		}

		for (auto i=0; i < thread_count; ++i)
		{
			pthread_join(threads[i], NULL);
		}
	}
};
