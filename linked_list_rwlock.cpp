#include <linked_list_rwlock.h>

void linked_list_rwlock::add(data_type val)
{
	pthread_rwlock_wrlock(&m_rwlock);
	linked_list::add(val);
	pthread_rwlock_unlock(&m_rwlock);
}

const bool linked_list_rwlock::member(data_type val)
{
	pthread_rwlock_rdlock(&m_rwlock);
	const auto member = linked_list::member(val);
	pthread_rwlock_unlock(&m_rwlock);

	return member;
}

void linked_list_rwlock::remove(data_type val)
{
	pthread_rwlock_wrlock(&m_rwlock);
	linked_list::remove(val);
	pthread_rwlock_unlock(&m_rwlock);
}

void linked_list_rwlock::delete_member(int index)
{
	pthread_rwlock_wrlock(&m_rwlock);
	linked_list::delete_member(index);
	pthread_rwlock_unlock(&m_rwlock);
}

const data_type linked_list_rwlock::get_by_index(int index)
{
	pthread_rwlock_rdlock(&m_rwlock);
	const auto member = linked_list::get_by_index(index);
	pthread_rwlock_unlock(&m_rwlock);

	return member;
}

void linked_list_rwlock::print_list()
{
	//To avoid inconsistencies
	pthread_rwlock_rdlock(&m_rwlock);
	linked_list::print_list();
	pthread_rwlock_unlock(&m_rwlock);
}

size_t linked_list_rwlock::get_node_count()
{
	pthread_rwlock_rdlock(&m_rwlock);
	auto size = linked_list::get_node_count();
	pthread_rwlock_unlock(&m_rwlock);

	return size;
}
