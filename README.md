# 高并发IM聊天工具
本项目是一款通过通信网络提供实时通讯功能的应用程序。客户端基于SQLite3、MTL皮肤库，服务端基于muduo库、MySQL、线程池等技术，主要实现了用户登录、注册、聊天、群聊、文件发送等功能。

- 客户端：Sqlite3、MTL皮肤库、protobuf、线程池
- 服务端：MySQL、muduo库、Reactor网络模型、epoll
- 编译：cmake

