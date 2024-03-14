#include "net/EventLoop.h"
#include "net/EventLoopThread.h"
#include "net/EventLoopThreadPool.h"
#include "net/TcpServer.h"
#include "base/Logging.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "BinaryReader.h"

using namespace muduo;
using namespace muduo::net;
using namespace boost::uuids;
using namespace std::placeholders;
using namespace edoyun;

enum {
	msg_type_unknown,
	//�û���Ϣ
	msg_type_heartbeart = 1000,
	msg_type_register,
	msg_type_login,
	msg_type_getofriendlist,
	msg_type_finduser,
	msg_type_operatefriend,
	msg_type_userstatuschange,
	msg_type_updateuserinfo,
	msg_type_modifypassword,
	msg_type_creategroup,
	msg_type_getgroupmembers,
	//������Ϣ
	msg_type_chat = 1100,         //������Ϣ
	msg_type_multichat,             //Ⱥ����Ϣ
};

class TcpSession
{
public:
	TcpSession() = default;
	~TcpSession() = default;
	void Send(const TcpConnectionPtr& conn, BinaryWriter& writer) {
		string out = writer.toString();
		writer.Clear();
		int len = (int)out.size();//��ȡ������
		writer.WriteData(len + 6);
		writer.WriteData(htonl(len));
		writer.WriteData(htons(0));
		out = writer.toString() + out;
		if (conn != NULL) {
			BinaryReader::dump(out);
			conn->send(out.c_str(), out.size());
		}
	}
};

class ClientSession :public TcpSession
{
public:
	ClientSession(const TcpConnectionPtr& conn);
	//Ϊ�˿����������ڣ���ֹ��ǰ���٣���������֮���ظ�����
	ClientSession(const ClientSession&) = delete;
	ClientSession& operator=(const ClientSession&) = delete;
	~ClientSession();

	operator std::string() {
		return m_sessionid;
	}

	void OnRead(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time);

	//ҵ����
	bool Process(const TcpConnectionPtr& conn, string msgbuff);
protected:
	void OnHeartbeatResponse(const TcpConnectionPtr& conn, const string& data);
	void OnRegisterResponse(const TcpConnectionPtr& conn, const string& data);
	void OnLoginResponse(const TcpConnectionPtr& conn, const string& data);
private:
	std::string m_sessionid;
	int m_seq;//�Ự�����
};

typedef std::shared_ptr<ClientSession> ClientSessionPtr;