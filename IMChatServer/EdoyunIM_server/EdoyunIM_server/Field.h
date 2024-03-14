#include <unistd.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <errno.h>
#include <memory>
#include "base/Logging.h"

using namespace std;

class Field
{
public:
	typedef enum {
		EDY_TYPE_NONE = 0,
		EDY_TYPE_STRING,
		EDY_TYPE_INTEGER,
		EDY_TYPE_FLOAT,
		EDY_TYPE_BOOL,
		EDY_TYPE_NULL
	}DataTypes;
public:
	Field();
	~Field() = default;
	void SetType(DataTypes tp) { m_type = tp; }
	DataTypes GetType() const { return m_type; }
	void SetName(const string& name) { m_name = name; }
	const string& GetName() const { return m_name; }
	void SetValue(const char* value, size_t nLen);
	const string& GetValue() const { return m_value; }
	bool isNull()const { return m_isnull; }
	bool toBool()const { return atoi(m_value.c_str()) != 0; }
	int8_t toInt8()const { return static_cast<int8_t>(atoi(m_value.c_str())); }
	uint8_t toUint8()const { return static_cast<uint8_t>(atoi(m_value.c_str())); }
	int32_t toInt32()const { return atoi(m_value.c_str()); }
	uint32_t toUint32()const { return (uint32_t)atoi(m_value.c_str()); }
	int64_t toInt64()const { return atoll(m_value.c_str()); }
	uint64_t toUint64()const { return (uint64_t)atoll(m_value.c_str()); }
	double toFloat()const { return atof(m_value.c_str()); }
	const string& GetString() const { return m_value; }
private:
	string m_value;
	string m_name;
	DataTypes m_type;
	bool m_isnull;
};