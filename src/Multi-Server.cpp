#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>

using namespace std;

int main() {
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0) {
        cerr << "Can't Initialize winsock! Quitting!" << endl;
        return 0;
    }

    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        cerr << "Can't create a socket! Quitting!" << endl;
        return 0;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(50000);
    hint.sin_addr.S_un.S_addr = INADDR_ANY; 
    
    bind(listening, (sockaddr*)&hint, sizeof(hint));

    listen(listening, SOMAXCONN);

    fd_set master;
    FD_ZERO(&master);

    FD_SET(listening, &master);

    bool running = true; 

    while (running)  {
        fd_set copy = master;
        int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
        for (int i = 0; i < socketCount; i++) {
            SOCKET sock = copy.fd_array[i];
            if (sock == listening) {
                SOCKET client = accept(listening, nullptr, nullptr);
                FD_SET(client, &master);
                string welcomeMsg = "Welcome to the Chat!\n";
                send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
            }
            else {
                char buf[4096];
                memset(buf,0, 4096);
                int bytesIn = recv(sock, buf, 4096, 0);
                if (bytesIn <= 0) {
                    closesocket(sock);
                    FD_CLR(sock, &master);
                }
                else {
                    if (buf[0] == '\\') {
                        string cmd = string(buf, bytesIn);
                        if (cmd == "\\quit") {
                            running = false;
                            break;
                        }
                        continue;
                    }
                    for (int i = 0; i < master.fd_count; i++) {
                        SOCKET outSock = master.fd_array[i];
                        if (outSock != listening && outSock != sock) {
                            ostringstream ss;
                            ss << buf <<  "\n";
                            string strOut = ss.str();
                            send(outSock, strOut.c_str(), strOut.size() + 1024, 0);
                        }
                    }
                }
            }
        }
    }
    FD_CLR(listening, &master);
    closesocket(listening);
    
    string msg = "Shutting Down\n";

    while (master.fd_count > 0) {
        SOCKET sock = master.fd_array[0];
        send(sock, msg.c_str(), msg.size() + 1, 0);
        FD_CLR(sock, &master);
        closesocket(sock);
    }
    WSACleanup();
    system("pause");
}
