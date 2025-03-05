#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>
#include <iostream>
#include <functional>

class ChatServer
{
public:
    ChatServer(muduo::net::EventLoop *loop,               // 事件循环
               const muduo::net::InetAddress &listenAddr, // IP port
               const std::string &nameArg)
        : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        // 注册连接和读写事件回调
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, std::placeholders::_1));
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        // 设置服务端线程数
        _server.setThreadNum(4);
    }

    void start()
    {
        _server.start();
    }

private:
    // 处理连接事件
    void onConnection(const muduo::net::TcpConnectionPtr &conn)
    {
        if (conn->connected())
        {
            std::cout << conn->peerAddress().toIpPort() << " -> "
                      << conn->localAddress().toIpPort() << " state: online" << std::endl;
        }
        else
        {
            std::cout << conn->peerAddress().toIpPort() << " -> "
                      << conn->localAddress().toIpPort() << " state: offline" << std::endl;
            conn->shutdown(); // 关闭连接
        }
    }

    // 处理消息事件
    void onMessage(const muduo::net::TcpConnectionPtr &conn,
                   muduo::net::Buffer *buffer,
                   muduo::Timestamp time)
    {
        std::string buf = buffer->retrieveAllAsString();
        std::cout << "Received data: " << buf << " at " << time.toString() << std::endl;
        conn->send(buf); // 回显数据
    }

    muduo::net::TcpServer _server;
    muduo::net::EventLoop *_loop;
};

int main()
{
    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "ChatServer");

    server.start();
    loop.loop();

    return 0;
}
