#include <list>

#include "net/EventLoop.h"
#include "net/EventLoopThread.h"
#include "net/EventLoopThreadPool.h"
#include "net/TcpServer.h"
#include "base/Logging.h"
#include "ClientSession.h"
#include <mutex>
#include <iostream>

using namespace muduo;
using namespace muduo::net;
using namespace std;

class IMServer final //final��ʾ���಻������������
{
public:
	IMServer() = default;
	IMServer(const IMServer&) = delete;//��ֹʹ�ô˺���
	~IMServer() = default;
	IMServer& operator=(const IMServer&) = delete;//���ô˺���
	bool Init(const string& ip, short port, EventLoop* loop);
protected:
	void OnConnection(const TcpConnectionPtr& conn);
	void OnClose(const TcpConnectionPtr& conn);
private:
	shared_ptr<TcpServer>  m_server;
	map<string, ClientSessionPtr> m_mapclient;
	//std::list<TcpConnectionPtr> m_lstConn;
	mutex m_sessionlock;//����m_mapclient�Ĳ���
};
typedef pair<string, ClientSessionPtr> ConnPair;
typedef map<string, ClientSessionPtr>::iterator ConnIter;