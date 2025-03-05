#ifndef PUBLIC_H
#define PUBLIC_H

// server client 公共文件

enum EnMsgType
{
    LOGIN_MSG = 1,
    LOGIN_MSG_ACK = 2,
    REG_MSG = 3,
    REG_MSG_ACK = 4,
    ONE_CHAT_MSG = 5, // 一对一聊天
    ADD_FRIEND_MSG = 6,

    CREATE_GROUP_MSG = 7, // 创建群组
    ADD_GROUP_MSG = 8,    // 加入群组
    GROUP_CHAT_MSG = 9,    // 群聊天

    LOGINOUT_MSG = 10
};

#endif