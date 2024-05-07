//
// Created by nino on 24-5-7.
//

#ifndef CPP_SOCKET_TCPCLIENT_H
#define CPP_SOCKET_TCPCLIENT_H

#include "iostream"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "cstring"
#include "string"
#include "unistd.h"
#include "netdb.h"

#define BUFF_SIZE 1024

class TCPClient{
private:
    int client_socket;  //客户端的socket
    struct sockaddr_in serv_addr;   //Server端的网络地址结构
    char buf[BUFF_SIZE]; //客户端读写缓冲区
    int buf_len;    //客户端读写长度

public:
    TCPClient();
    ~TCPClient();

    bool ClientInit();

    /**
     * @brief: 连接服务器
     * @arg : ip_addr Server端的ip地址
     * @arg : port  Server端的端口
     * */
    bool Connect(const std::string& ip_addr, const std::string port);

    /**
     * @brief: 关闭socket连接
     * */
    void CloseClientSock();

    /**
     * @brief: 读取缓冲区数据
     * */
    int Read();

    /**
     *@brief: 写入数据
     * @arg: 数据字符串
     * */
     void Write(const std::string& str);
};

#endif //CPP_SOCKET_TCPCLIENT_H
