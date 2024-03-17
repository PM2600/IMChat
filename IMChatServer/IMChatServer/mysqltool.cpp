#include "mysqltool.h"
extern void mysql_close(MYSQL* sock);

MySQLTool::MySQLTool()
{
	m_mysql = NULL;
	m_port = 3306;
}

MySQLTool::~MySQLTool()
{
	if (m_mysql != NULL) {
		MYSQL* tmp = m_mysql;
		m_mysql = NULL;
		mysql_close(tmp);
	}
}

bool MySQLTool::connect(const string& host, const string& user, const string& passwd, const string& db, unsigned port)
{
	if (m_mysql != NULL) {
		MYSQL* tmp = m_mysql;
		m_mysql = NULL;
		mysql_close(tmp);
	}

	m_mysql = mysql_init(m_mysql);
	//mysql Ĭ����3306
	m_mysql = mysql_real_connect(m_mysql, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, NULL, 0);
	cout << host << std::endl << user << std::endl << passwd << std::endl << db << std::endl;

	if (m_mysql != NULL) {
		m_host = host;
		m_user = user;
		m_passwd = passwd;
		m_dbname = db;
		mysql_query(m_mysql, "set names utf8;");
		cout << "connect mysql success!\r\n";
		return true;
	}

	cout << "connect mysql failed!\r\n";
	return false;
}
QueryResultPtr MySQLTool::Query(const string& sql)
{
	if (m_mysql == NULL) {
		if (connect(m_host, m_user, m_passwd, m_dbname) == false) {
			return QueryResultPtr();
		}
	}
	//blob real_query ����\0��������Ϊ���ַ���������
	int ret = mysql_real_query(m_mysql, sql.c_str(), sql.size());
	if (ret) {
		uint32_t nErrno = mysql_errno(m_mysql);
		cout << "mysql_real_query call failed! code is :" << nErrno << std::endl;
		if (CR_SERVER_GONE_ERROR == nErrno) {
			if (connect(m_host, m_user, m_passwd, m_dbname) == false) {
				return QueryResultPtr();
			}
			ret = mysql_real_query(m_mysql, sql.c_str(), sql.size());
			if (ret) {
				nErrno = mysql_errno(m_mysql);
				cout << "mysql_real_query call failed again! code is :" << nErrno << std::endl;
				return QueryResultPtr();
			}
		}
		else {
			return QueryResultPtr();
		}

	}
	MYSQL_RES* result = mysql_store_result(m_mysql);
	uint32_t rowcount = mysql_affected_rows(m_mysql);
	uint32_t cloumncount = mysql_field_count(m_mysql);
	return QueryResultPtr(new QueryResult(result, rowcount, cloumncount));
}

bool MySQLTool::Execute(const string& sql)
{
	uint32_t nAffectedCount;
	int nErrno;
	return Execute(sql, nAffectedCount, nErrno);
}

bool MySQLTool::Execute(const string& sql, uint32_t& nAffectedCount, int& nErrno)
{
	if (m_mysql == NULL) {
		if (connect(m_host, m_user, m_passwd, m_dbname) == false) {
			return false;
		}
	}
	int ret = mysql_query(m_mysql, sql.c_str());
	if (ret) {
		uint32_t nErrno = mysql_errno(m_mysql);
		cout << "mysql_query call failed! code is :" << nErrno << std::endl;
		cout << "mysql_query call failed! msg :" << mysql_error(m_mysql) << std::endl;
		if (CR_SERVER_GONE_ERROR == nErrno) {
			if (connect(m_host, m_user, m_passwd, m_dbname) == false) {
				return false;
			}
			ret = mysql_query(m_mysql, sql.c_str());
			if (ret) {
				nErrno = mysql_errno(m_mysql);
				cout << "mysql_query call failed again! code is :" << nErrno << std::endl;
				return false;
			}
		}
		else {
			return false;
		}
		nErrno = 0;
		nAffectedCount = mysql_affected_rows(m_mysql);
	}
	return false;
}