#include "pch.h"
#include "Student.h"

Student::Student(const CString& m_name, const CString& m_id, int score1, int score2)
	: m_name(m_name),
	  m_id(m_id),
	  score1(score1),
	  score2(score2) {
}

Student::Student() {
}
