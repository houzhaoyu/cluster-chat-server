#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include "usermodel.hpp"
#include "offlinemsgmodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
#include "redis.hpp"

#include <unordered_map>
#include <functional>
#include <mutex>

#include <muduo/net/TcpConnection.h>
#include "json.hpp"
using json = nlohmann::json;

// 处理消息的回调函数
using MsgHandler = std::function<void(const muduo::net::TcpConnectionPtr &, json &, muduo::Timestamp)>;
// 聊天服务器处理业务的类
class ChatService
{
public:
    // 获取单例对象的接口函数
    static ChatService *instance();
    // 处理登录业务
    void login(const muduo::net::TcpConnectionPtr &conn, json &js, muduo::Timestamp time);
    // 处理注册业务
    void reg(const muduo::net::TcpConnectionPtr &conn, json &js, muduo::Timestamp time);
    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);

    // 处理客户端异常退出
    void clientCloseExcption(const muduo::net::TcpConnectionPtr &conn);
    // 客户端正常退出
    void logout(const muduo::net::TcpConnectionPtr &conn, json &js, muduo::Timestamp time);
    // 一对一聊天
    void oneChat(const muduo::net::TcpConnectionPtr &conn, json &js, muduo::Timestamp time);
    // 重置用户状态
    void reset();
    // 添加好友
    void addFriend(const muduo::net::TcpConnectionPtr &conn, json &js, muduo::Timestamp time);
    // 创建群组业务
    void createGroup(const muduo::net::TcpConnectionPtr &conn, json &js, muduo::Timestamp time);
    // 加入群组业务
    void addGroup(const muduo::net::TcpConnectionPtr &conn, json &js, muduo::Timestamp time);
    // 群聊业务
    void groupChat(const muduo::net::TcpConnectionPtr &conn, json &js, muduo::Timestamp time);
    //从redis消息队列中获取订阅的消息
    void handleRedisSubscribeMessage(int userid, std::string msg);
private:
    ChatService();

    // 存储消息id和其对应的业务处理方法
    std::unordered_map<int, MsgHandler> _msgHandlerMap;

    // 存储在线用户的通信连接
    // 有线程安全问题
    std::unordered_map<int, muduo::net::TcpConnectionPtr> _userConnMap;

    // 定义互斥锁
    std::mutex _connMutex;

    // 数据操作类对象
    UserModel _userModel;
    // 离线消息类对象
    OfflineMsgModel _offlineMsgModel;
    // 好友信息
    FriendModel _friendModel;
    // 处理群组
    GroupModel _groupModel;

    //redis操作对象
    Redis _redis;
};

#endif