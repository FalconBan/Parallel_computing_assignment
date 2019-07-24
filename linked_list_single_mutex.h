#pragma once

#include <linked_list.h>
#include <pthread.h>

class linked_list_single_mutex : public linked_list
{
public:
	linked_list_single_mutex() = default;
	~linked_list_single_mutex() = default;

	void add(data_type val) override;
	const node* member(data_type val) override;
	void remove(data_type val) override;
	void delete_member(int index) override;
	const node* get_by_index(int index) override;

	void print_list() override;

private:
	pthread_mutex_t m_mutex;
};
