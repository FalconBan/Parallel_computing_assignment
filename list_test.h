#pragma once

#include <linked_list.h>
#include <linked_list_single_mutex.h>
#include <linked_list_rwlock.h>

#include <iostream>

class list_test
{
public:
	list_test() = default;
	~list_test() = default;

	void normal_list_test();
	void mutex_list_test();
	void rwlock_list_test();
};

inline void list_test::normal_list_test()
{
	linked_list list;
	list.add(0);
	list.add(10);
	list.add(5);
	list.add(44);
	list.add(52);
	list.print_list();

	std::cout << std::endl;

	list.remove(44);
	list.delete_member(2);
	list.print_list();
}

inline void list_test::mutex_list_test()
{
	linked_list list;
	list.add(0);
	list.add(10);
	list.add(5);
	list.add(44);
	list.add(52);
	list.print_list();

	std::cout << std::endl;

	list.remove(44);
	list.delete_member(2);
	list.print_list();
}

inline void list_test::rwlock_list_test()
{
	linked_list list;
	list.add(0);
	list.add(10);
	list.add(5);
	list.add(44);
	list.add(52);
	list.print_list();

	std::cout << std::endl;

	list.remove(44);
	list.delete_member(2);
	list.print_list();
}
