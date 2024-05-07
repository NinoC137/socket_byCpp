//
// Created by nino on 24-5-7.
//

#include "TCPServer.h"

TCPServer::TCPServer():server_sock(-1), client_sock(-1) {
    cout << "Create TCP Server" << endl;
}

TCPServer::~TCPServer(){

}

bool TCPServer::ServerInit(const std::string &port) {
    if(server_sock > 0){    //如果服务端已开启, 关闭它, 重新启动
        CloseServerSock();
        server_sock = -1;
    }

    server_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(server_sock == -1){
        cout << "服务器创建监听套接字失败!" << endl;
        return false;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(port.c_str()));
    if(bind(server_sock, (struct sockaddr*)& server_addr, sizeof(server_addr)) == -1){
        cout << "服务器绑定套接字失败!" << endl;
        CloseServerSock();
        return false;
    }

    if(listen(server_sock, 5) == -1) {
        cout << "服务器监听套接字失败" << endl;
        CloseServerSock();
        return false;
    }

    cout << "服务端初始化成功, 开始接受客户端连接" << endl;
    return true;
}

bool TCPServer::Accept() {
    if(server_sock == -1){
        cout << "服务器未开启监听" << endl;
        return false;
    }

    client_addr_len = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)& client_addr, &client_addr_len);

    if(client_sock == -1){
        cout << "服务器无法接受客户端的连接!" << endl;
        return false;
    }
    return true;
}

void TCPServer::CloseServerSock() {
    if(server_sock > 0){
        close(server_sock);
        server_sock = -1;
    }
}

void TCPServer::CloseClientSock() {
    if(client_sock > 0){
        close(client_sock);
        client_sock = -1;
    }
}

int TCPServer::Read() {
    if(client_sock == -1){
        cout << "没有客户端进行连接" << endl;
        return 0;
    }
    buf_len = read(client_sock, buf, BUFF_SIZE);
    if(buf_len == 0){
        CloseClientSock();
        return buf_len;
    }
    buf[buf_len] = 0;
    cout << "[" << client_sock << "]说: " << buf << endl;
    return buf_len;
}

void TCPServer::Write() {
    if(client_sock == -1){
        cout << "没有客户端进行连接, 写入失败" << endl;
    }else{
        write(client_sock, buf, buf_len);
    }
}