#include <unistd.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <errno.h>
#include <memory>
#include <vector>
#include "base/Logging.h"
#include "Field.h"

using namespace std;

class QueryResult
{
public:
	QueryResult(MYSQL_RES* result, uint32_t rowcount, uint32_t cloumncout);
	~QueryResult();
	bool NextRow();//true表示还有下一行，并且切换成功；false表示没有了
	Field* Fetch() {
		return m_CurrentRow.data();
	}
	const Field& operator[](int index)const {
		return m_CurrentRow[index];
	}
	const Field& operator[](const string& name)const {
		return m_CurrentRow[GetFieldIndexByName(name)];
	}
	uint32_t GetFieldCount()const { return m_cloumncout; }
	uint32_t GetRowCount()const { return m_rowcount; }

	vector<string> const& GetFieldNames() const { return m_vecFieldName; }
	void EndQuery();
	Field::DataTypes toEDYType(enum_field_types mysqltype)const;
protected:
	int GetFieldIndexByName(const string& name) const{
		for (uint32_t i = 0; i < m_vecFieldName.size(); i++) {
			if (m_vecFieldName[i] == name)return i;
		}
		return -1;
	}
private:
	vector<Field> m_CurrentRow;
	vector<string> m_vecFieldName;
	MYSQL_RES* m_result;
	uint32_t m_rowcount;
	uint32_t m_cloumncout;
};

typedef shared_ptr<QueryResult> QueryResultPtr;