#include "MySqlManager.h"
#include <sstream>


MySqlManager::MySqlManager()
{
	//用户
	sTableInfo info;
	info.sName = "t_user";
	info.mapField["f_id"] = { "f_id","bigint(20) NOT NULL AUTO_INCREMENT COMMENT '自增ID'","bigint(20)" };
	info.mapField["f_user_id"] = { "f_user_id", "bigint(20) NOT NULL COMMENT '用户ID'", "bigint(20)" };
	info.mapField["f_username"] = { "f_username", "varchar(64) NOT NULL COMMENT '用户名'", "varchar(64)" };
	info.mapField["f_nickname"] = { "f_nickname", "varchar(64) NOT NULL COMMENT '用户昵称'", "varchar(64)" };
	info.mapField["f_password"] = { "f_password", "varchar(64) NOT NULL COMMENT '用户密码'", "varchar(64)" };
	info.mapField["f_facetype"] = { "f_facetype", "int(10) DEFAULT 0 COMMENT '用户头像类型'", "int(10)" };
	info.mapField["f_customface"] = { "f_customface", "varchar(32) DEFAULT NULL COMMENT '自定义头像名'", "varchar(32)" };
	info.mapField["f_customfacefmt"] = { "f_customfacefmt", "varchar(6) DEFAULT NULL COMMENT '自定义头像格式'", "varchar(6)" };
	info.mapField["f_gender"] = { "f_gender", "int(2)  DEFAULT 0 COMMENT '性别'", "int(2)" };
	info.mapField["f_birthday"] = { "f_birthday", "bigint(20)  DEFAULT 19900101 COMMENT '生日'", "bigint(20)" };
	info.mapField["f_signature"] = { "f_signature", "varchar(256) DEFAULT NULL COMMENT '地址'", "varchar(256)" };
	info.mapField["f_address"] = { "f_address", "varchar(256) DEFAULT NULL COMMENT '地址'", "varchar(256)" };
	info.mapField["f_phonenumber"] = { "f_phonenumber", "varchar(64) DEFAULT NULL COMMENT '电话'", "varchar(64)" };
	info.mapField["f_mail"] = { "f_mail", "varchar(256) DEFAULT NULL COMMENT '邮箱'", "varchar(256)" };
	info.mapField["f_owner_id"] = { "f_owner_id", "bigint(20) DEFAULT 0 COMMENT '群账号群主userid'", "bigint(20)" };
	info.mapField["f_register_time"] = { "f_register_time", "datetime NOT NULL COMMENT '注册时间'", "datetime" };
	info.mapField["f_remark"] = { "f_remark", "varchar(64) NULL COMMENT '备注'", "varchar(64)" };
	info.mapField["f_update_time"] = { "f_update_time", "timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间'", "timestamp" };
	info.sKey = "PRIMARY KEY (f_user_id), INDEX f_user_id (f_user_id), KEY  f_id  ( f_id )";
	m_mapTable.insert(TablePair(info.sName, info));

	//聊天内容
	info.mapField.clear();
	info.sName = "t_chatmsg";
	info.mapField["f_id"] = { "f_id", "bigint(20) NOT NULL AUTO_INCREMENT COMMENT '自增ID'", "bigint(20)" };
	info.mapField["f_senderid"] = { "f_senderid", "bigint(20) NOT NULL COMMENT '发送者id'", "bigint(20)" };
	info.mapField["f_targetid"] = { "f_targetid", "bigint(20) NOT NULL COMMENT '接收者id'", "bigint(20)" };
	info.mapField["f_msgcontent"] = { "f_msgcontent", "blob NOT NULL COMMENT '聊天内容'", "blob" };
	info.mapField["f_create_time"] = { "f_create_time", "timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间'", "timestamp" };
	info.mapField["f_remark"] = { "f_remark", "varchar(64) NULL COMMENT '备注'", "varchar(64)" };
	info.sKey = "PRIMARY KEY (f_id), INDEX f_id (f_id)";
	m_mapTable.insert(TablePair(info.sName, info));

	//用户关系
	info.mapField.clear();
	info.sName = "t_user_relationship";
	info.mapField["f_id"] = { "f_id", "bigint(20) NOT NULL AUTO_INCREMENT COMMENT '自增ID'", "bigint(20)" };
	info.mapField["f_user_id1"] = { "f_user_id1", "bigint(20) NOT NULL COMMENT '用户ID'", "bigint(20)" };
	info.mapField["f_user_id2"] = { "f_user_id2", "bigint(20) NOT NULL COMMENT '用户ID'", "bigint(20)" };
	info.mapField["f_remark"] = { "f_remark", "varchar(64) NULL COMMENT '备注'", "varchar(64)" };
	info.mapField["f_create_time"] = { "f_create_time", "timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间'", "timestamp" };
	info.sKey = "PRIMARY KEY (f_id), INDEX f_id (f_id)";
	m_mapTable.insert(TablePair(info.sName, info));
}
MySqlManager::~MySqlManager()
{

}
bool MySqlManager::Init(
	const string& host,
	const string user,
	const string passwd,
	const string dbname,
	unsigned port
)
{
	m_mysql.reset(new MySQLTool());
	if (m_mysql->connect(host, user, passwd, dbname, port) == false) {
		cout << "connect mysql failed!\r\n";
		return false;
	}
	if (CheckDatabase() == false) {
		if (CreateDatabase() == false)
			return false;
	}
	cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	TableIter it = m_mapTable.begin();
	for (; it != m_mapTable.end(); it++) {
		cout << __FILE__ << "(" << __LINE__ << ")\r\n";
		if (CheckTable(it->second) == false) {
			cout << __FILE__ << "(" << __LINE__ << ")\r\n";
			if (CreateTable(it->second) == false) {
				cout << __FILE__ << "(" << __LINE__ << ")\r\n";
				return false;
			}
		}
		cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	}
	cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	return true;
}

QueryResultPtr MySqlManager::Query(const string& sql)
{
	if (m_mysql == NULL)return QueryResultPtr();
	return m_mysql->Query(sql);
}

bool MySqlManager::Excute(const string& sql)
{
	if (m_mysql == NULL)return false;
	return m_mysql->Execute(sql);
}


bool MySqlManager::CheckDatabase() {
	if (m_mysql == NULL)return false;
	cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	QueryResultPtr result = m_mysql->Query("show databases;");
	if (NULL == result) {
		cout << "no database found in mysql!\r\n";
		return false;
	}
	cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	Field* pRow = result->Fetch();
	string dbname = m_mysql->GetDBName();
	while (pRow != NULL) {
		string name = pRow[0].GetString();
		if (name == dbname) {
			cout << __FILE__ << "(" << __LINE__ << ")\r\n";
			result->EndQuery();
			return true;
		}
		if (result->NextRow() == false)break;
		pRow = result->Fetch();
	}
	cout << "database not found!\r\n";
	result->EndQuery();
	return false;
}

bool MySqlManager::CreateDatabase() {
	if (m_mysql == NULL)return false;
	stringstream sql;
	sql << "create database " << m_mysql->GetDBName() << ";";
	uint32_t naffect = 0;
	int nErrno = 0;
	if (m_mysql->Execute(sql.str(), naffect, nErrno) == false)return false;
	if (naffect == 1)return true;
	return false;
}

bool MySqlManager::CheckTable(const sTableInfo& info) {
	cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	if (m_mysql == NULL)return false;
	stringstream sql;
	sql << "desc " << info.sName << ";";
	QueryResultPtr result = m_mysql->Query(sql.str());
	cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	if (result == NULL) {
		if (CreateTable(info) == false) {
			return false;
		}
		return true;
	}
	cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	map<string, sFieldInfo> rest;
	rest.insert(info.mapField.begin(), info.mapField.end());
	map<string, sFieldInfo> mapChange;

	Field* pRow = result->Fetch();
	cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	while (pRow != NULL) {
		string name = pRow[0].GetString();
		string type = pRow[1].GetString();
		FieldConstIter iter = info.mapField.find(name);
		cout << __FILE__ << "(" << __LINE__ << "):" << name << " type " << type << "\r\n";
		cout << __FILE__ << "(" << __LINE__ << "):" << iter->second.sDesc << endl;
		if (iter == info.mapField.end()) {
			exit(-1);
		}
		rest.erase(name);
		if (iter->second.sDesc != type) {
			mapChange.insert(FieldPair(name, iter->second));
			break;
		}
		if (result->NextRow() == false)break;
		pRow = result->Fetch();
		cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	}
	cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	result->EndQuery();
	if (rest.size() > 0) {//补全缺掉的列
		FieldIter it = rest.begin();
		for (; it != rest.end(); it++) {
			stringstream ss;
			ss << "alter table " << info.sName <<
				" add column " << it->second.sName <<
				" " << it->second.sType << ";";
			if (m_mysql->Execute(ss.str()) == false) {
				return false;
			}
		}
	}
	if (mapChange.size() > 0) {//修改不匹配的列
		FieldIter iter = mapChange.begin();
		for (; iter != mapChange.end(); iter++) {
			stringstream ss;
			ss << "alter table " << info.sName <<
				" modify column " << iter->second.sName <<
				" " << iter->second.sType << ";";
			if (m_mysql->Execute(ss.str()) == false) {
				return false;
			}
		}
	}
	return true;
}


bool MySqlManager::CreateTable(const sTableInfo& info) {
	if (m_mysql == NULL)return false;
	if (info.mapField.size() == 0)return false;
	stringstream sql;
	sql << "create table if not exists " << info.sName << "(";
	FieldConstIter it = info.mapField.begin();
	for (; it != info.mapField.end(); it++)
	{
		if (it != info.mapField.begin()) {
			sql << ",";
		}
		sFieldInfo field = it->second;
		sql << field.sName << " " << field.sType;
	}
	if (info.sKey.size() > 0) {
		sql << "," << info.sKey;
	}
	sql << ") default charset=utf-8,ENGINE=InnoDB;";
	return m_mysql->Execute(sql.str());
}

bool MySqlManager::UpdateTable(const sTableInfo& info) {
	if (CheckTable(info) == false) {
		return CreateTable(info);
	}
	return true;
}