#include "ClientSession.h"
#include <sstream>
#include "BinaryReader.h"
#include "jsoncpp/json.h"
#include "UserManager.h"
using namespace edoyun;

ClientSession::ClientSession(const TcpConnectionPtr& conn)
{
	m_seq = 0;
	//uuid_generate(m_sessionid);
	//此处就是两个括号，第一个表示构造对象
	//第二个表示()运算符重载
	stringstream ss;
	ss << (void*)conn.get();
	m_sessionid = ss.str();// to_string(random_generator()());
	TcpConnectionPtr* client = const_cast<TcpConnectionPtr*>(&conn);
	//*const_cast<std::string*>(&conn->name()) = m_sessionid;
	(*client)->setMessageCallback(std::bind(&ClientSession::OnRead, this, _1, _2, _3));
}

ClientSession::~ClientSession()
{

}

void ClientSession::OnRead(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
{
	cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	while (buf->readableBytes() >= sizeof(int32_t)) {
		int32_t packagesize = 0;
		BinaryReader::dump(buf->peek(), buf->readableBytes());
		packagesize = *(int32_t*)buf->peek();
		if (buf->readableBytes() < sizeof(int32_t) + packagesize)
			return;
		buf->retrieve(sizeof(int32_t));
		string msgbuff;
		cout << __FILE__ << "(" << __LINE__ << ")" << packagesize << "\r\n";
		msgbuff.assign(buf->peek() + 6, packagesize - 6);
		BinaryReader::dump(msgbuff);
		buf->retrieve(packagesize);
		if (Process(conn, msgbuff) != true) {
			cout << "process error,close connection!\r\n";
			conn->forceClose();
		}
	}
}

bool ClientSession::Process(const TcpConnectionPtr& conn, string msgbuff)
{
	BinaryReader reader(msgbuff);
	int cmd = -1;
	if (reader.ReadData<decltype(cmd)>(cmd) == false)return false;
	if (reader.ReadData<int>(m_seq) == false)return false;
	string data;
	if (reader.ReadData(data) == false)return false;
	cout << __FILE__ << "(" << __LINE__ << ")" << cmd << "\r\n";
	cout << __FILE__ << "(" << __LINE__ << ")" << m_seq << "\r\n";
	cout << __FILE__ << "(" << __LINE__ << ")" << data.size() << "\r\n";
	
	switch (cmd) {
	case msg_type_heartbeart://心跳包
		OnHeartbeatResponse(conn, data);
		break;
	case msg_type_register://注册消息
		OnRegisterResponse(conn, data);
		break;
	case msg_type_login://登录消息
		OnLoginResponse(conn, data);
		break;
	case msg_type_getofriendlist://获取好友列表
		break;
	case msg_type_finduser://查找用户
		break;
	case msg_type_operatefriend://操作好友
		break;
	case msg_type_updateuserinfo://更新用户信息
		break;
	case msg_type_modifypassword://修改密码
		break;
	case msg_type_creategroup://创建群组
		break;
	case msg_type_getgroupmembers://获取群成员
		break;
	case msg_type_chat://聊天消息
		break;
	case msg_type_multichat://群发消息
		break;
	default:
		break;
	}
	return true;
}

void ClientSession::OnHeartbeatResponse(const TcpConnectionPtr& conn, const string&)
{
	//包的长度 4字节 不能压缩的，固定格式
	//命令类型 4字节 不能压缩的，固定格式
	//包的序号 4字节 不能压缩的，固定格式
	//包的数据 包长度（4字节，可以压缩的）+包内容（长度由前面一项来定）
	BinaryWriter writer;
	int cmd = msg_type_heartbeart;
	writer.WriteData(htonl(cmd));
	writer.WriteData(htonl(m_seq));
	string empty;
	writer.WriteData(empty);
	Send(conn, writer);
}

void ClientSession::OnRegisterResponse(const TcpConnectionPtr& conn, const string& data)
{//{"username":"手机号","nickname":"昵称","password":"密码"}
	Json::Reader reader;
	Json::Value root, response;
	BinaryWriter writer;
	string result;
	int cmd = msg_type_register;
	writer.WriteData(htonl(cmd));
	writer.WriteData(htonl(m_seq));
	if (reader.parse(data, root) == false) {
		cout << "error json:" << data << endl;
		response["code"] = 101;
		response["msg"] = "json parse failed!";
		result = response.toStyledString();
		writer.WriteData(result);
		Send(conn, writer);
		return;
	}
	if (!root["username"].isString() ||
		!root["nickname"].isString() ||
		!root["password"].isString())
	{
		cout << "error type:" << data << endl;
		response["code"] = 102;
		response["msg"] = "json data type error!";
		result = response.toStyledString();
		writer.WriteData(result);
		Send(conn, writer);
		return;
	}
	User user;
	user.username = root["username"].asString();
	user.nickname = root["nickname"].asString();
	user.password = root["password"].asString();

	if (!Singleton<UserManager>::instance().AddUser(user))
	{
		cout << "add user failed!\r\n";
		response["code"] = 100;
		response["msg"] = "register failed!";
		result = response.toStyledString();
		writer.WriteData(result);
		Send(conn, writer);
		return;
	}
	else {
		root["code"] = 0;
		root["msg"] = "ok";
		result = root.toStyledString();
		writer.WriteData(result);
		Send(conn, writer);
	}
}

void ClientSession::OnLoginResponse(const TcpConnectionPtr& conn, const string& data)
{//{"username":"用户名","password":"密码","clienttype":1,"status":1}
	BinaryWriter writer;
	string result;
	Json::Value root, response;
	Json::Reader reader;
	int cmd = msg_type_login;
	writer.WriteData(htonl(cmd));
	writer.WriteData(htonl(m_seq));
	if (reader.parse(data, root) == false) {
		cout << __FILE__ << "(" << __LINE__ << ")\r\n";
		response["code"] = 101;
		response["msg"] = "json parse failed!";
		result = response.toStyledString();
		writer.WriteData(result);
		Send(conn, writer);
		return;
	}
	if (!root["username"].isString() ||
		!root["password"].isString() ||
		!root["clienttype"].isInt() ||
		!root["status"].isInt())
	{
		cout << __FILE__ << "(" << __LINE__ << ")\r\n";
		response["code"] = 102;
		response["msg"] = "json data type error!";
		result = response.toStyledString();
		writer.WriteData(result);
		Send(conn, writer);
		return;
	}
	string username = root["username"].asString();
	string password = root["password"].asString();
	User user;
	if (Singleton<UserManager>::instance().GetUserInfoByUsername(username, user) == false)
	{
		cout << __FILE__ << "(" << __LINE__ << ")\r\n";
		response["code"] = 103;
		response["msg"] = "user is not exist or password is incorrect!";
		result = response.toStyledString();
		writer.WriteData(result);
		Send(conn, writer);
		return;
	}

	if (password != user.password) {
		cout << __FILE__ << "(" << __LINE__ << ")\r\n";
		response["code"] = 104;
		response["msg"] = "user is not exist or password is incorrect!";
		result = response.toStyledString();
		writer.WriteData(result);
		Send(conn, writer);
		return;
	}


	//如果成功，返回应答
	response["code"] = 0;
	response["msg"] = "ok";
	response["userid"] = user.userid;
	response["username"] = user.username;
	response["nickname"] = user.nickname;
	response["facetype"] = user.facetype;
	response["customface"] = user.customface;
	response["gender"] = user.gender;
	response["birthday"] = user.birthday;
	response["signature"] = user.signature;
	response["address"] = user.address;
	response["phonenumber"] = user.phonenumber;
	response["mail"] = user.mail;
	result = response.toStyledString();
	writer.WriteData(result);
	cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	Send(conn, writer);
}