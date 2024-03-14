# CMakeList.txt: EdoyumIMServer 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
# //
cmake_minimum_required (VERSION 3.8)

project(EdoyunServer)

#这个宏，会影响编译参数
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g -Wall -O0 -Wno-unused-variable -pthread")

#设置库目录
link_directories(# 针对64位的
	${PROJECT_SOURCE_DIR}/lib
	/usr/lib64/mysql/
)

find_library(MYSQL_LIB libmysqlclient.so /usr/lib64/mysql/)
if (NOT MYSQL_LIB)#NOT 只能用大写
	message(FATAL_ERROR "not found mysqlclient.so at /usr/lib64/mysql/")
endif(NOT MYSQL_LIB)#必须进行匹配，否则会报错

include_directories(. ./base ./net)

set(muduo_srcs
base/Timestamp.cc
base/TimeZone.cc
base/Date.cc
base/CountDownLatch.cc
base/FileUtil.cc
base/Logging.cc
base/LogFile.cc
base/LogStream.cc
base/AsyncLogging.cc
base/Thread.cc
base/CurrentThread.cc
base/ProcessInfo.cc
"base/Condition.cc"

net/Acceptor.cc
net/Buffer.cc
net/Channel.cc
net/Connector.cc
net/Poller.cc
net/poller/DefaultPoller.cc
net/poller/EPollPoller.cc
net/poller/PollPoller.cc
net/InetAddress.cc
net/Socket.cc
net/SocketsOps.cc
net/TcpClient.cc
net/TcpConnection.cc
net/TcpServer.cc
net/EventLoop.cc
net/EventLoopThread.cc
net/EventLoopThreadPool.cc
net/Timer.cc
net/TimerQueue.cc
)

set(mysql_srcs
mysqltool.cpp
Field.cpp
QueryResult.cpp
MySqlManager.cpp
)

set(chat_srcs 
EdoyumIMServer.cpp
IMServer.cpp
ClientSession.cpp
UserManager.cpp
BinaryReader.cpp
)

set(file_srcs
EdoyumIMTestClient.cpp)

set(json_srcs
jsoncpp/json_reader.cpp
jsoncpp/json_writer.cpp
jsoncpp/json_value.cpp)

# 将源代码添加到此项目的可执行文件。
add_executable (imchatserver ${chat_srcs} ${muduo_srcs} ${json_srcs} ${mysql_srcs})
#只是确认库存在或者设置库目录，是没有用的，需要链接进来才能起效果
target_link_libraries(imchatserver mysqlclient)

# 将源代码添加到此项目的可执行文件。
add_executable (imfileserver ${file_srcs} ${muduo_srcs})
#只是确认库存在或者设置库目录，是没有用的，需要链接进来才能起效果
target_link_libraries(imfileserver)
# TODO: 如有需要，请添加测试并安装目标。
