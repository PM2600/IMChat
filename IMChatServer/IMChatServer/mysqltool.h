#include <unistd.h>
#include <mysql/mysql.h>
#include <mysql/errmsg.h>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <errno.h>
#include "base/Logging.h"
#include "QueryResult.h"
#include <iostream>//cout cin cerr
using namespace std;

class MySQLTool
{
public:
	MySQLTool();
	~MySQLTool();
	bool connect(const string& host, const string& user, const string& passwd, const string& db, unsigned port = 3306);
	QueryResultPtr Query(const string& sql);
	bool Execute(const string& sql);
	bool Execute(const string& sql, uint32_t& nAffectedCount, int& nErrno);
	const string GetDBName()const { return m_dbname; }
private:
	MYSQL* m_mysql;
	string m_host;
	string m_user;
	string m_passwd;
	string m_dbname;
	unsigned m_port;
};