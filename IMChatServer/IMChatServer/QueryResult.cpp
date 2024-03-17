#include "QueryResult.h"
#include <iostream>

using namespace std;

QueryResult::QueryResult(MYSQL_RES* result, uint32_t rowcount, uint32_t cloumncout)
	:m_result(result), m_rowcount(rowcount), m_cloumncout(cloumncout)
{
	m_CurrentRow.resize(m_cloumncout);
	m_vecFieldName.resize(m_cloumncout);
	MYSQL_FIELD* fields = mysql_fetch_fields(m_result);
	MYSQL_ROW row = mysql_fetch_row(m_result);
	if (row == NULL) {
		EndQuery();
		return;
	}
	unsigned long* pFieldLength = mysql_fetch_lengths(m_result);
	for (uint32_t i = 0; i < m_cloumncout; i++)
	{
		m_vecFieldName[i] = fields[i].name;
		m_CurrentRow[i].SetType(toEDYType(fields[i].type));
		m_CurrentRow[i].SetName(m_vecFieldName[i]);
		if (row[i] == NULL)
		{
			m_CurrentRow[i].SetValue(NULL, 0);
		}
		else {
			m_CurrentRow[i].SetValue(row[i], pFieldLength[i]);
		}
	}
}

QueryResult::~QueryResult() {}
bool QueryResult::NextRow()
{
	if (m_result == NULL)return false;
	MYSQL_ROW row = mysql_fetch_row(m_result);
	if (row == NULL) {
		EndQuery();
		return false;
	}
	unsigned long* pFieldLength = mysql_fetch_lengths(m_result);
	for (uint32_t i = 0; i < m_cloumncout; i++)
	{
		if (row[i] == NULL)
		{
			m_CurrentRow[i].SetValue(NULL, 0);
		}
		else {
			m_CurrentRow[i].SetValue(row[i], pFieldLength[i]);
		}
	}
	return true;
}

void QueryResult::EndQuery()
{
	m_CurrentRow.clear();
	m_vecFieldName.clear();
	if (m_result) {
		mysql_free_result(m_result);
		m_result = NULL;
	}
	m_rowcount = 0;
	m_cloumncout = 0;
}

Field::DataTypes QueryResult::toEDYType(enum_field_types mysqltype)const
{
	switch (mysqltype)
	{
	case FIELD_TYPE_TIMESTAMP:
	case FIELD_TYPE_DATE:
	case FIELD_TYPE_TIME:
	case FIELD_TYPE_DATETIME:
	case FIELD_TYPE_YEAR:
	case FIELD_TYPE_STRING:
	case FIELD_TYPE_VAR_STRING:
	case FIELD_TYPE_BLOB:
	case FIELD_TYPE_SET:
		return Field::EDY_TYPE_STRING;
	case FIELD_TYPE_NULL:
		return Field::EDY_TYPE_NULL;
	case FIELD_TYPE_TINY:
	case FIELD_TYPE_SHORT:
	case FIELD_TYPE_LONG:
	case FIELD_TYPE_LONGLONG:
	case FIELD_TYPE_INT24:
	case FIELD_TYPE_ENUM:
		return Field::EDY_TYPE_INTEGER;
	case FIELD_TYPE_DECIMAL:
	case FIELD_TYPE_FLOAT:
	case FIELD_TYPE_DOUBLE:
		return Field::EDY_TYPE_FLOAT;
	default:
		return Field::EDY_TYPE_NONE;
	}
	return Field::EDY_TYPE_NONE;
}