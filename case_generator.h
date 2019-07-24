#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include <single_threaded_test_fixture.h>
#include <single_mutex_multi_threaded_test_fixture.h>
#include <single_rwlock_multi_threaded_test_fixture.h>

class case_generator
{
public:
	explicit case_generator(int thread_count, int data_point_count, std::string filename) : m_thread_count(thread_count),
	m_data_point_count(data_point_count), case_file(filename) {}

	void run_case(int range, int insert_count, int access_count, int del_count)
	{
		ofstream case_results;

		if (check_existence(case_file))
		{
			case_results.open(case_file.c_str(), ios_base::app);
		}
		else
		{
			case_results.open(case_file.c_str(), ios_base::out);

			if (m_thread_count == 1)
				case_results << "single_thread,mutex,rwlock\n";
			else
				case_results << "mutex,rwlock\n";
		}

		for (auto i = 0; i < m_data_point_count; ++i)
		{
			if (m_thread_count == 1)
			{
				single_threaded_test_fixture fixture_1;
				fixture_1.perform_operations(range, insert_count, access_count, del_count);
				case_results << fixture_1.m_duration << ",";
			}

			mutex::single_mutex_multi_threaded_test_fixture fixture_2;
			fixture_2.perform_operations(m_thread_count, range, insert_count, access_count, del_count);
			case_results << mutex::time_taken_us << ",";

			rwlock::rwlock_multi_threaded_test_fixture fixture_3;
			fixture_3.perform_operations(m_thread_count, range, insert_count, access_count, del_count);
			case_results << rwlock::time_taken_us << "\n";
		}

		case_results.close();
	}

private:
	std::string case_file;
	int m_thread_count;
	int m_data_point_count;

	inline bool check_existence(const std::string& name)
	{
	    if (FILE* file = fopen(name.c_str(), "r"))
	    {
	        fclose(file);
	        return true;
	    }
	    else
	    {
	        return false;
	    }
	}
};
