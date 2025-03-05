# cluster-chat-server
**集群聊天服务器，使用了muduo、mysql、redis、nginx**

## 依赖：

### nginx的tcp负载均衡模块

nginx version: nginx/1.26.3
built by gcc 11.4.0 (Ubuntu 11.4.0-1ubuntu1~22.04) 
built with OpenSSL 3.0.2 15 Mar 2022
TLS SNI support enabled
configure arguments: --with-pcre --with-http_ssl_module --with-http_v2_module --with-http_gzip_static_module --with-stream --with-stream_ssl_module

### muduo库



### redis

版本：Redis server v=6.0.16 sha=00000000:0 malloc=jemalloc-5.2.1 bits=64 build=a3fdef44459b3ad6

### nlohamann json





## 编译方式：

cd ./build
rm -rf *
cmake ..
make



## nginx配置文件：

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

## 运行方式：
服务器程序：bin/ChatServer
ip地址和端口号与nginx配置文件中upstream MyServer的ip和端口号相同：
./ChatServer 127.0.0.1 6000

客户端程序：bin/ChatClient
端口号与nginx配置文件中server的端口号相同：
./ChatClient 127.0.0.1 8000