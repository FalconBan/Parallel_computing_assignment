/*
 * Main.cpp
 *
 *  Created on: Jan 12, 2019
 *      Author: User
 */

#include <multi_threaded.h>
#include <case_1_runner.h>
#include <case_2_runner.h>
#include <case_3_runner.h>

#include <cstdlib>
#include <pthread.h>
#include <sched.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(int c, char** v)
{
	int data_point_count = 100;

	run_case_1_scenarios(data_point_count);
	run_case_2_scenarios(data_point_count);
	run_case_3_scenarios(data_point_count);

	return 0;
}
