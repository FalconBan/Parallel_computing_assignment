#pragma once

#include <case_generator.h>

void run_case_2_scenarios(int data_point_count)
{
	std::string case_2_1_file = "case_2_1_results.csv";
	case_generator generator_for_case_1(1, data_point_count, case_2_1_file);
	generator_for_case_1.run_case(1000, 500, 9000, 500);

	std::string case_2_2_file = "case_2_2_results.csv";
	case_generator generator_for_case_2(2, data_point_count, case_2_2_file);
	generator_for_case_2.run_case(1000, 500, 9000, 500);

	std::string case_2_4_file = "case_2_4_results.csv";
	case_generator generator_for_case_3(4, data_point_count, case_2_4_file);
	generator_for_case_3.run_case(1000, 500, 9000, 500);

	std::string case_2_8_file = "case_2_8_results.csv";
	case_generator generator_for_case_4(8, data_point_count, case_2_8_file);
	generator_for_case_4.run_case(1000, 500, 9000, 500);
}
