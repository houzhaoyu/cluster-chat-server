#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H

#include "user.hpp"

#include <vector>

//维护好友信息的操作接口方法
class FriendModel
{
    public:
    //添加好有关系
    void insert(int userid, int friendid);

    //获取好友列表
    //包括好友id、名字、在线状态
    std::vector<User> query(int userid);
};

#endif