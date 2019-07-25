#pragma once

#include <linked_list.h>
#include <pthread.h>

class linked_list_rwlock : public linked_list
{
public:
	linked_list_rwlock() = default;
	~linked_list_rwlock() = default;

	void add(data_type val) override;
	const bool member(data_type val) override;
	void remove(data_type val) override;
	void delete_member(int index) override;
	const data_type get_by_index(int index) override;
	size_t get_node_count() override;

	void print_list() override;

private:
	pthread_rwlock_t m_rwlock;
};
