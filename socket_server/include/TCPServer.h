//
// Created by nino on 24-5-7.
//

#ifndef SOCKET_SERVER_TCPSERVER_H
#define SOCKET_SERVER_TCPSERVER_H

#include <iostream>
#include "sys/socket.h"
#include "arpa/inet.h"
#include "string"
#include "cstring"
#include "unistd.h"

#define BUFF_SIZE 1024

using std::cout;
using std::endl;
using std::cin;
using std::string;

class TCPServer{
private:
    struct sockaddr_in server_addr; //服务器中的服务端网络地址结构
    struct sockaddr_in client_addr; //服务端中客户端的网络地址结构
    socklen_t client_addr_len;  //服务器中客户端的网络地址结构长度
    char buf[BUFF_SIZE];    //读写缓冲区
    int buf_len;    //读取的字节长度
public:
    int server_sock;    //服务器中服务端的socket描述符
    int client_sock;    //服务器中客户端的socket描述符

    TCPServer();
    ~TCPServer();

    /**
     * @brief: 初始化服务器
     * @arg: port: 服务器的端口号
     * */
    bool ServerInit(const string& port);

    /**
     * @brief: 阻塞接受客户端的连接
     * */
    bool Accept();

    /**
     * @brief:关闭服务器中服务端的套接字
     * */
    void CloseServerSock();

    /**
     * @brief: 关闭服务器中客户端的套接字
     * */
     void CloseClientSock();

     /**
      * @brief:读取客户端的数据
      * */
      int Read();

      /**
       * @brief: 回写客户端的时局
       * */
       void Write();
};

#endif //SOCKET_SERVER_TCPSERVER_H
