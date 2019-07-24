#include <linked_list_single_mutex.h>

void linked_list_single_mutex::add(data_type val)
{
	pthread_mutex_lock(&m_mutex);
	linked_list::add(val);
	pthread_mutex_unlock(&m_mutex);
}

const node* linked_list_single_mutex::member(data_type val)
{
	pthread_mutex_lock(&m_mutex);
	const auto member = linked_list::member(val);
	pthread_mutex_unlock(&m_mutex);

	return member;
}

void linked_list_single_mutex::remove(data_type val)
{
	pthread_mutex_lock(&m_mutex);
	linked_list::remove(val);
	pthread_mutex_unlock(&m_mutex);
}

void linked_list_single_mutex::print_list()
{
	//To avoid inconsistencies
	pthread_mutex_lock(&m_mutex);
	linked_list::print_list();
	pthread_mutex_unlock(&m_mutex);
}

void linked_list_single_mutex::delete_member(int index)
{
	pthread_mutex_lock(&m_mutex);
	linked_list::delete_member(index);
	pthread_mutex_unlock(&m_mutex);
}

const node* linked_list_single_mutex::get_by_index(int index)
{
	pthread_mutex_lock(&m_mutex);
	const auto member = linked_list::get_by_index(index);
	pthread_mutex_unlock(&m_mutex);

	return member;
}
