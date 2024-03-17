#pragma once

#include <iostream>

// TODO: �ڴ˴����ó�����Ҫ��������ͷ��
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include "base/Logging.h"
#include "base/Singleton.h"
#include <set>
#include <list>
#include <mutex>
using namespace std;
class User
{
public:
	int32_t 	 userid;//�û�id
	string  	 username;//�û���
	string  	 password;//����
	string  	 nickname;//�ǳ�
	int32_t 	 facetype;//Ĭ��ͷ��
	string  	 customface;//�Զ���ͷ��
	string  	 customfacefmt;//�Զ���ͷ��ĸ�ʽ
	int32_t 	 gender;//�Ա�
	int32_t		 birthday;//����
	string		 signature;//ǩ��
	string		 address;//λ��
	string		 phonenumber;//�ֻ���
	string		 mail;//����
	int32_t		 ownerid;//���ڱ��Ⱥ����Ϣ��
	set<int32_t> friends;//���ѵ�id
	User()
		:userid(-1), facetype(-1), gender(-1),
		birthday(-1), ownerid(-1) {}
	~User() = default;
};

class UserManager final
{
public:
	UserManager() = default;
	~UserManager() = default;
	bool Init();
	UserManager(const UserManager&) = delete;
	UserManager& operator=(const UserManager&) = delete;

	//����û�
	bool AddUser(User& user);
	//�����ݿ�����û���Ϣ
	bool LoadUsersFromDB();
	bool LoadRelationshipFromDB(int32_t userid, set<int32_t>& friends);
	bool GetUserInfoByUsername(const string& name, User& user);
private:
	mutex m_mutex;
	list<User> m_cachedUsers;
	int32_t m_baseUserID{ 0 };
	int32_t m_baseGrupID{ 0x0FFFFFFF };
};