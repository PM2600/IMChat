#include "Field.h"

Field::Field() :m_type(EDY_TYPE_NONE), m_isnull(true) {}

//Field::~Field() {}

void Field::SetValue(const char* value, size_t nLen) {
	if (value == NULL || (nLen == 0)) {
		m_isnull = true;
		m_value.clear();
		return;
	}
	//m_value.resize(nLen);
	//memcpy((char*)m_value.c_str(), value, nLen);
	m_value.assign(value, nLen);//�滻����ָ�������ݣ��滻ԭ�е�����
	m_isnull = false;
}