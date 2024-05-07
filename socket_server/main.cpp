#include <iostream>
#include "TCPServer.h"

int main(int argc, char** argv) {

    if(argc != 2){
        cout << "Usage: " << argv[0] << "<PORT>" << endl;
        return -1;
    }

    TCPServer tcpServer;
    tcpServer.CloseServerSock();
    bool init_res = tcpServer.ServerInit(argv[1]);
    if(!init_res){
        cout << "服务器初始化失败" << endl;
        return -1;
    }
    //接受客户端的连接, 只接受一个客户端
    bool accept_res = tcpServer.Accept();
    if(!accept_res){
        return -2;
    }

    while(1){

        if(tcpServer.Read() == 0){
            cout << "客户端不存在" << endl;
            break;
        }
        tcpServer.Write();
    }

    tcpServer.CloseServerSock();
    tcpServer.CloseClientSock();

    return 0;
}
