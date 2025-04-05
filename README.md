# cluster-chat-server
**集群聊天服务器，使用了muduo、mysql、redis、nginx**

## 依赖：

### Mysql数据库

表结构:

![image-20250405225341669](C:\Users\侯照宇\AppData\Roaming\Typora\typora-user-images\image-20250405225341669.png)

### nginx的tcp负载均衡模块

nginx version: nginx/1.26.3
built by gcc 11.4.0 (Ubuntu 11.4.0-1ubuntu1~22.04) 
built with OpenSSL 3.0.2 15 Mar 2022
TLS SNI support enabled
configure arguments: --with-pcre --with-http_ssl_module --with-http_v2_module --with-http_gzip_static_module --with-stream --with-stream_ssl_module

#### nginx配置文件：

```
stream {
    upstream MyServer{
        server 127.0.0.1:6000 weight=1 max_fails=3 fail_timeout=30s;
        server 127.0.0.1:6002 weight=1 max_fails=3 fail_timeout=30s;
    }

    server{
        proxy_connect_timeout 1s;
        #proxy_timeout 3s;
        listen 8000;
        proxy_pass MyServer;
        tcp_nodelay on;
    }
}
```



### muduo库



### redis

版本：Redis server v=6.0.16 sha=00000000:0 malloc=jemalloc-5.2.1 bits=64 build=a3fdef44459b3ad6

### nlohamann json





## 编译方式：

cd ./build
rm -rf *
cmake ..
make

## 运行方式：

- 启动nginx
  - Nginx可执行文件位置：/usr/local/nginx/sbin
  - 修改配置文件：/usr/local/nginx/conf/nginx.conf
  - 启动nginx：./nginx（运行时重新加载配置文件：./nginx -s reload）
  - 查看是否启动成功：sudo netstat -tanp
  - ![image-20250405230837383](C:\Users\侯照宇\AppData\Roaming\Typora\typora-user-images\image-20250405230837383.png)
  - ![image-20250405230859659](C:\Users\侯照宇\AppData\Roaming\Typora\typora-user-images\image-20250405230859659.png)

- 启动redis
  - 安装：sudo apt-get install redis-server  
  - redis安装后会自动启动
  - 查看是否启动：ps -ef | grep redis![image-20250405230717758](C:\Users\侯照宇\AppData\Roaming\Typora\typora-user-images\image-20250405230717758.png)



- 服务器程序：bin/ChatServer
  - ip地址和端口号与nginx配置文件中upstream MyServer的ip和端口号相同：
  - ./ChatServer 127.0.0.1 6000
  - ./ChatServer 127.0.0.1 6002

- 客户端程序：bin/ChatClient
  - 端口号与nginx配置文件中server的端口号相同：
  - ./ChatClient 127.0.0.1 8000

分别在6000和6002端口运行两个服务器程序

客户端连接8000端口，nginx会通过负载均衡算法将客户端连接到其中一个端口

![image-20250405231137935](C:\Users\侯照宇\AppData\Roaming\Typora\typora-user-images\image-20250405231137935.png)