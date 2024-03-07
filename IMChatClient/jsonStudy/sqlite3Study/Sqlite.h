#pragma once
#include "sqlite3.h"
#include <string>
#include <vector>
#include <list>
#pragma comment(lib, "sqlite3.lib")
#ifdef _UNICODE
typedef std::wstring tstring;
#define SqliteOpen sqlite3_open16
#else
typedef std::string tstring;
#define SqliteOpen sqlite3_open
#endif

class Sqlite
{
public:
	Sqlite(const tstring& dbPath);
	~Sqlite();

	int Query(const std::string& sql, std::vector<std::vector<std::string>>& results, std::vector<std::string>& cloumns, std::string& strMsg);	
	
	int QueryContainBlob(
		const std::string& sql, 
		std::vector<std::vector<std::string>>& results, 
		std::vector<std::string>& cloumns, 
		std::string& strMsg);

	int Exec(const std::string& sql, std::string& strMsg);

protected:
	static int SelectCallbackEntry(void* thiz, int argc, char* argv[], char* names[]);
	int SelectCallback(int argc, char* argv[], char* names[]);
	void ClearResult();
private:
	Sqlite(const Sqlite& db) = delete;
	Sqlite operator=(const Sqlite& db) = delete;
private:
	sqlite3_stmt* m_stmt;
	sqlite3* m_db;
	std::list<std::vector<std::string>*> m_result;
	std::vector<std::string> m_cloumn;
};

