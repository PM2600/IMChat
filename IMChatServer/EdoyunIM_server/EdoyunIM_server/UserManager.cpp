#include "UserManager.h"
#include "base/Singleton.h"
#include "MySqlManager.h"
#include <sstream>
using namespace muduo;
bool UserManager::Init()
{
	//�����û���Ϣ�����е��û���
	if (LoadUsersFromDB() == false) {
		cout << "load users from database failed!\r\n";
		return false;
	}
	//�����û���ϵ
	for (auto& iter : m_cachedUsers) {
		if (!LoadRelationshipFromDB(iter.userid, iter.friends))
		{
			cout << "load friend failed!\r\n";
		}
	}
	return true;
}

//����û�
bool UserManager::AddUser(User& user)
{
	stringstream sql;
	m_baseUserID++;
	sql << "INSERT INTO t_user(f_user_id,f_username,f_nickname,f_password,f_register_time)" <<
		"VALUES(" << m_baseUserID << ",'" << user.username << "','" <<
		user.nickname << "','" << user.password << "',NOW())";
	bool result = Singleton<MySqlManager>::instance().Excute(sql.str());
	if (result == false)
		return false;
	user.userid = m_baseUserID;
	user.facetype = 0;
	user.birthday = 20000101;
	user.gender = 0;
	user.ownerid = 0;
	{
		lock_guard<mutex> guard(m_mutex);
		m_cachedUsers.push_back(user);
	}
	return true;
}
//�����ݿ�����û���Ϣ
bool UserManager::LoadUsersFromDB() {
	stringstream sql;
	sql << "SELECT f_user_id, f_username, f_nickname, f_password,  f_facetype, f_customface, f_gender, f_birthday, f_signature, f_address, f_phonenumber, f_mail FROM t_user ORDER BY  f_user_id DESC";
	//��ע����û���idС����ע����û�id��
	//��ע����û����ߵĸ��ʻ�������Խ��н�������
	QueryResultPtr result = Singleton<MySqlManager>::instance().Query(sql.str());
	if (result == NULL)
		return false;
	cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	while (result != NULL) {
		Field* pRow = result->Fetch();
		if (pRow == NULL)break;
		User u;
		u.userid = pRow[0].toInt32();
		u.username = pRow[1].GetString();
		u.nickname = pRow[2].GetString();
		u.password = pRow[3].GetString();
		u.facetype = pRow[4].toInt32();
		u.customface = pRow[5].GetString();
		u.gender = pRow[6].toInt32();
		u.birthday = pRow[7].toInt32();
		u.signature = pRow[8].GetString();
		u.address = pRow[9].GetString();
		u.phonenumber = pRow[10].GetString();
		u.mail = pRow[11].GetString();
		{
			lock_guard<mutex> guard(m_mutex);
			m_cachedUsers.push_back(u);
		}
		if (u.userid > m_baseUserID) {
			m_baseUserID = u.userid;
		}
		if (result->NextRow() == false)break;
	}
	result->EndQuery();
	cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	return true;
}
bool UserManager::LoadRelationshipFromDB(int32_t userid, set<int32_t>& friends) {
	stringstream sql;
	sql << "SELECT f_user_id1, f_user_id2 FROM t_user_relationship WHERE f_user_id1=" << userid << " OR f_user_id2=" << userid << " ;";
	QueryResultPtr result = Singleton<MySqlManager>::instance().Query(sql.str());
	if (result == NULL)
		return false;
	while (result != NULL) {
		Field* pRow = result->Fetch();
		if (pRow == NULL)break;
		int friendid1 = pRow[0].toInt32();
		int friendid2 = pRow[1].toInt32();
		if (friendid1 == userid)friends.insert(friendid2);
		else friends.insert(friendid1);
		if (result->NextRow() == false)break;
	}
	result->EndQuery();
	return true;
}

bool UserManager::GetUserInfoByUsername(const string& name, User& user)
{
	lock_guard<mutex> guard(m_mutex);
	for (const auto& iter : m_cachedUsers)
	{
		if (iter.username == name)
		{
			user = iter;
			return true;
		}
	}
	return false;
}