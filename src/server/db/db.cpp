#include "db.hpp"
#include <muduo/base/Logging.h>

// 数据库配置信息
static std::string server = "127.0.0.1";
static std::string user = "rarabura";
static std::string password = "111111";
static std::string dbname = "chat";

// 初始化数据库连接
MySQL::MySQL()
{
    _conn = mysql_init(nullptr);
}

// 释放数据库连接资源这里用UserModel示例，通过UserModel如何对业务层封装底层数据库的操作。代码示例如下：
MySQL::~MySQL()
{
    if (_conn != nullptr)
        mysql_close(_conn);
}

// 连接数据库
bool MySQL::connect()
{
    MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(),
                                  password.c_str(), dbname.c_str(), 3306, nullptr, 0);
    if (p != nullptr)
    {
        // 防止中文乱码
        mysql_query(_conn, "set names gbk");
    }
    else
    {
        LOG_INFO << "connect mysql error!";
    }
    return p;
}

// 更新操作
bool MySQL::update(std::string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "更新失败!";
        return false;
    }
    return true;
}

// 查询操作
MYSQL_RES *MySQL::query(std::string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "查询失败!";
        return nullptr;
    }
    return mysql_use_result(_conn);
}

//获取连接
MYSQL * MySQL::getConnection()
{
    return _conn;
}