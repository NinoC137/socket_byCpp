#include <iostream>
#include "TCPClient.h"

int main(int argc, char** argv) {
    TCPClient tcpClient;
    tcpClient.CloseClientSock();

    bool ope_res = tcpClient.ClientInit();

    if(!ope_res){
        return -1;
    }

    char* argv1 = argv[1];
    char* argv2 = argv[2];

    std::cout << "参数1: " << argv1 << std::endl;
    std::cout << "参数2: " << argv2 << std::endl;

    ope_res = tcpClient.Connect(argv1, argv2);
    if(!ope_res){
        return -2;
    }

    std::cout << "开始发送数据(按Q退出)" << std::endl;
    while(1){
        std::string str;
        std::cin >> str;
        if(strcmp(str.c_str(), "q")){
            break;
        }
        tcpClient.Write(str);
        if(tcpClient.Read() <= 0){
            break;
        }
    }

    tcpClient.CloseClientSock();

    return 0;
}
