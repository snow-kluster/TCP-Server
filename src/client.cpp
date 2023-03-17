#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>

#define BUF_SIZE 4096

void send_msg(int);
void recv_msg(int);

using namespace std;
string msg;
string name = "DEFAULT";
int main(int argc,const char **argv){
    
    string ipaddress = "127.0.0.1";
    int port = 50000;
    name = "["+std::string(argv[1])+"]:";

    WSADATA data;
    WORD ver = MAKEWORD(2,2);

    int wsResult = WSAStartup(ver,&data);

    if(wsResult != 0){
        cerr << "---can't start quitting---" << wsResult << endl;
        return 0;
    }

    SOCKET rsocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(rsocket == INVALID_SOCKET){
        cerr <<"--- can't create socket quitting---"<< WSAGetLastError <<endl;
        return 0;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET,ipaddress.c_str(),&hint.sin_addr);

    int connresult = connect(rsocket,(sockaddr*)&hint,sizeof(hint));
    if(connresult == SOCKET_ERROR){
        cerr << "cant connect to server" << WSAGetLastError() << endl;
        closesocket(rsocket);
        WSACleanup();
        return 0;
    }

    string my_name = "new client:" + std::string(argv[1]);
    send(rsocket, my_name.c_str(), my_name.length() + 1, 0);

    thread snd(send_msg, rsocket);
    thread rcv(recv_msg, rsocket);
    
    snd.join();
    rcv.join();

    closesocket(rsocket);
    WSACleanup();
}

void send_msg(int rsocket){
    while(1){
        getline(cin, msg);
        if (msg == "Quit"|| msg == "quit"){
            closesocket(rsocket);
            exit(0);
        }
        string name_msg = name + " " + msg;
        send(rsocket, name_msg.c_str(), name_msg.length() + 1, 0);
    }
}

void recv_msg(int rsocket){
    char name_msg[BUF_SIZE + name.length() + 1];
    while (1){
        int str_len = recv(rsocket, name_msg, BUF_SIZE + name.length(), 0);
        if (str_len == -1){
            exit(-1);
        }
        cout<<string(name_msg)<<endl;
    }
}
