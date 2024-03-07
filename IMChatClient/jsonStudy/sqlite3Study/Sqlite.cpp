#include "Sqlite.h"

Sqlite::Sqlite(const tstring& dbPath)
{
	m_stmt = NULL;
	int ret = SqliteOpen(dbPath.c_str(), &m_db);
	if (ret != 0) {
		throw ret;
	}
}

Sqlite::~Sqlite()
{
	ClearResult();
	sqlite3* db = m_db;
	m_db = NULL;
	sqlite3_close(db);
}

int Sqlite::Query(const std::string & sql, std::vector<std::vector<std::string>>& results, std::vector<std::string>& cloumns, std::string& strMsg)
{
	ClearResult();
	char* errmsg = NULL;
	int ret = sqlite3_exec(m_db, sql.c_str(), &Sqlite::SelectCallbackEntry, this, &errmsg);
	if (ret != SQLITE_OK) {
		strMsg = errmsg;
		sqlite3_free(errmsg);
		return ret;
	}
	results.resize(m_result.size());
	if (m_result.size() > 0) {
		std::list<std::vector<std::string>*>::iterator it = m_result.begin();
		for (size_t i = 0; i < m_result.size() && it != m_result.end(); i++, it++) {
			results[i].resize((*it)->size());
			for (size_t j = 0; j < (*it)->size(); j++) {
				results[i][j] = (**it)[j];
			}
		}
	}
	cloumns.resize(m_cloumn.size());
	for (size_t i = 0; i < cloumns.size(); i++) {
		cloumns[i] = m_cloumn[i];
	}
	return 0;
}

int Sqlite::QueryContainBlob(const std::string& sql, std::vector<std::vector<std::string>>& results, std::vector<std::string>& cloumns, std::string& strMsg)
{
	cloumns.clear();
	ClearResult();
	int ret = sqlite3_prepare(m_db, sql.c_str(), sql.size(), &m_stmt, NULL);

	if (ret != SQLITE_OK) {
		strMsg = sqlite3_errmsg(m_db);
		return ret;
	}
	while (sqlite3_step(m_stmt) == SQLITE_ROW) {
		int count = sqlite3_column_count(m_stmt);
		if (count > 0 && cloumns.size() <= 0) {
			cloumns.resize(count);
			for (int i = 0; i < count; i++) {
				sqlite3_column_name(m_stmt, i);
			}
		}
		if (count > 0) {
			std::vector<std::string>* presult = new std::vector<std::string>();
			presult->resize(count);
			for (int i = 0; i < count; i++) {
				int type = sqlite3_column_type(m_stmt, i);
				if (type == SQLITE_BLOB) {
					(*presult)[i].resize(sqlite3_column_bytes(m_stmt, i));
					memcpy((char*)(*presult)[i].c_str(), sqlite3_column_blob(m_stmt, i), (*presult)[i].size());
				}
				else {
					switch (type) {
					case SQLITE_INTEGER:
						(*presult)[i] = std::to_string(sqlite3_column_int(m_stmt, i));
						break;
					case SQLITE_FLOAT:
						(*presult)[i] = std::to_string(sqlite3_column_double(m_stmt, i));
						break;
					case SQLITE_NULL:
						(*presult)[i] = "NULL";
						break;
					case SQLITE_TEXT:
						(*presult)[i] = (char*)sqlite3_column_text(m_stmt, i);
						break;
					}
				}
			}
			m_result.push_back(presult);
		}
	}
	results.resize(m_result.size());
	if (m_result.size() > 0) {
		std::list<std::vector<std::string>*>::iterator it = m_result.begin();
		for (size_t i = 0; i < m_result.size() && it != m_result.end(); i++, it++) {
			results[i].resize((*it)->size());
			for (size_t j = 0; j < (*it)->size(); j++) {
				results[i][j] = (**it)[j];
			}
		}
	}
	sqlite3_finalize(m_stmt);
	m_stmt = NULL;
	return 0;
}

int Sqlite::Exec(const std::string& sql, std::string& strMsg)
{
	char* errmsg = NULL;
	int ret = sqlite3_exec(m_db, sql.c_str(), NULL, this, &errmsg);
	if (ret != SQLITE_OK) {
		strMsg = errmsg;
		sqlite3_free(errmsg);
		return ret;
	}
	return ret;
}

int Sqlite::SelectCallbackEntry(void* thiz, int argc, char* argv[], char* names[])
{
	((Sqlite*)thiz)->SelectCallback(argc, argv, names);
	return 0;
}

int Sqlite::SelectCallback(int argc, char* argv[], char* names[])
{
	if (m_cloumn.size() == 0 && argc > 0) {
		m_cloumn.resize(argc);
		for (int i = 0; i < argc; i++) {
			m_cloumn[i] = names[i];
		}
	}
	if (argc > 0) {
		std::vector<std::string>* presult = new std::vector<std::string>();
		presult->resize(argc);
		for (int i = 0; i < argc; i++) {
			(*presult)[i] = argv[i];
		}
		m_result.push_back(presult);
	}
	return 0;
}

void Sqlite::ClearResult()
{
	while (m_result.size() > 0) {
		std::vector<std::string>* presult = m_result.front();
		m_result.pop_front();
		if (presult) {
			presult->clear();
			delete presult;
		} 
	}
	m_cloumn.clear();
}
