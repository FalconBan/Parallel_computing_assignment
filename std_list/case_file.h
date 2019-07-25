#pragma once

class case_holder
{
public:
	case_holder(int iterations, int operation_count, double member,
			double insert, double delete_frac) : m_iterations(iterations),
			m_operation_count(operation_count), m_member(member), m_insert(insert),
			m_delete(delete_frac)
		{}

	const int get_iteration_count() { return m_iterations; }
	const int get_total_operations() { return m_operation_count; }
	const int get_member_access_count() { return static_cast<int>(m_member*m_operation_count); }
	const int get_inset_count() { return static_cast<int>(m_insert*m_operation_count); }
	const int get_delete_count() { return static_cast<int>(m_delete*m_operation_count); }

private:
	const int m_iterations;
	const int m_operation_count;
	const double m_member;
	const double m_insert;
	const double m_delete;
};
