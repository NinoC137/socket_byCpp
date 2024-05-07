//
// Created by nino on 24-5-7.
//

#include "TCPClient.h"

in_addr GetHostByName(const std::string& ip_addr){
    struct hostent* host;
    host = gethostbyname(ip_addr.c_str());
    struct in_addr _sin_addr;
    memset(&_sin_addr, 0, sizeof(_sin_addr));
    if(!host){
        return _sin_addr;
    }
    _sin_addr = (*(struct in_addr*)host->h_addr_list[0]);
    return _sin_addr;
}

TCPClient::TCPClient():client_socket(-1), buf_len(0){

}

TCPClient::~TCPClient(){

}

bool TCPClient::ClientInit() {
    if(client_socket != -1){
        CloseClientSock();
    }
    client_socket = socket(PF_INET, SOCK_STREAM, 0);
    if(client_socket == -1){
        std::cout << "client create Socket Fail!" << std::endl;
        return false;
    }
    std::cout << "client create socket success!" << std::endl;
    return true;
}

void TCPClient::CloseClientSock() {
    if(client_socket > 0){
        close(client_socket);
    }
    client_socket = -1;
}

bool TCPClient::Connect(const std::string &ip_addr, const std::string port) {
    if(client_socket == -1){
        std::cout << "client without socket!" << std::endl;
        return false;
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr = GetHostByName(ip_addr);
    serv_addr.sin_port = htons(atoi(port.c_str()));

    if(connect(client_socket, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1){
        CloseClientSock();
        std::cout << "Connect Server fail!" << std::endl;
        return false;
    }
    std::cout << "connect server success!" << std::endl;
    return true;
}

int TCPClient::Read() {
    if(client_socket == -1){
        std::cout << "client without socket!" << std::endl;
        return false;
    }
    buf_len = read(client_socket, buf, BUFF_SIZE);
    if(buf_len == 0){
        std::cout << "cannot read socket from server" << std::endl;
        CloseClientSock();
        return buf_len;
    }
    buf[buf_len] = 0;
    std::cout << "get data from server: " << buf << std::endl;
    return buf_len;
}

void TCPClient::Write(const std::string& str) {
    if(client_socket < 0){
        std::cout << "client without socket!" << std::endl;
    }else{
        write(client_socket, str.c_str(), str.size());
    }
}