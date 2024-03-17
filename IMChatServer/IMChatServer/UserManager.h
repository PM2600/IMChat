#pragma once

#include <iostream>

// TODO: 在此处引用程序需要的其他标头。
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
	int32_t 	 userid;//用户id
	string  	 username;//用户名
	string  	 password;//密码
	string  	 nickname;//昵称
	int32_t 	 facetype;//默认头像
	string  	 customface;//自定义头像
	string  	 customfacefmt;//自定义头像的格式
	int32_t 	 gender;//性别
	int32_t		 birthday;//生日
	string		 signature;//签名
	string		 address;//位置
	string		 phonenumber;//手机号
	string		 mail;//邮箱
	int32_t		 ownerid;//用于标记群主信息的
	set<int32_t> friends;//好友的id
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

	//添加用户
	bool AddUser(User& user);
	//从数据库加载用户信息
	bool LoadUsersFromDB();
	bool LoadRelationshipFromDB(int32_t userid, set<int32_t>& friends);
	bool GetUserInfoByUsername(const string& name, User& user);
private:
	mutex m_mutex;
	list<User> m_cachedUsers;
	int32_t m_baseUserID{ 0 };
	int32_t m_baseGrupID{ 0x0FFFFFFF };
};