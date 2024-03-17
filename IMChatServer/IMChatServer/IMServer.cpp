#include "IMServer.h"
#include <sstream>

using namespace std::placeholders;

bool IMServer::Init(const std::string& ip, short port, EventLoop* loop)
{
	InetAddress addr(ip, port);
	m_server.reset(new TcpServer(loop, addr, "chatserver", TcpServer::kReusePort));
	m_server->setConnectionCallback(
		std::bind(&IMServer::OnConnection, this, _1)
	);
	m_server->start();
	return true;
}

void IMServer::OnConnection(const TcpConnectionPtr& conn)
{
	if (conn->connected()) {
		ClientSessionPtr client(new ClientSession(conn));

		{
			std::lock_guard<std::mutex> guard(m_sessionlock);
			m_mapclient.insert(ConnPair((std::string) * client, client));
			//m_lstConn.push_back(client);
		}
	}
	else {
		OnClose(conn);
	}
}

void IMServer::OnClose(const TcpConnectionPtr& conn)
{
	//TODO:�����������,�ҵ�������ӣ�Ȼ����йر�
	stringstream ss;
	ss << (void*)conn.get();
	ConnIter iter = m_mapclient.find(ss.str());
	if (iter != m_mapclient.end()) {
		//TODO:�ر����ӵĲ���
		m_mapclient.erase(iter);
	}
	else {
		//TODO:�����������
		cout << conn->name() << std::endl;
	}
}