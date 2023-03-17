# TCP Server

████████╗░█████╗░██████╗░                          
╚══██╔══╝██╔══██╗██╔══██╗                          
░░░██║░░░██║░░╚═╝██████╔╝                           
░░░██║░░░██║░░██╗██╔═══╝░                         
░░░██║░░░╚█████╔╝██║░░░░░                            
░░░╚═╝░░░░╚════╝░╚═╝░░░░░                           
                                                    
 
 
░██████╗███████╗██████╗░██╗░░░██╗███████╗██████╗░ 
██╔════╝██╔════╝██╔══██╗██║░░░██║██╔════╝██╔══██╗ 
╚█████╗░█████╗░░██████╔╝╚██╗░██╔╝█████╗░░██████╔╝ 
░╚═══██╗██╔══╝░░██╔══██╗░╚████╔╝░██╔══╝░░██╔══██╗ 
██████╔╝███████╗██║░░██║░░╚██╔╝░░███████╗██║░░██║ 
╚═════╝░╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝ 

**Our project is a TCP chat server in which multiple client/users will be able to communicate with each other. The TCP server will run on localhost and will allow user to chat with one another if they are on the same network. The server code will use winsocks2 and W2tpcip header files so that the server can create and maintain sockets on Windows. The Project file also contains code for our client, through which our users can access the server. The server will act as an intermediary between the client to make a bare-bones group chat. As the server use winsocks it will only work on a Windows machine.**


# Directories
/src : contains all the source code for our project

/build : contains all binaries of the project

/.vscode : VS Code configuration file

/testing : contains code to be merged later and future update idea's

# Files

client.cpp : code for our client 

server.cpp : code for bare-bones TCP server (allows only one client)

Multi-Server.cpp : code for our TCP server (allows multiple clients)

Makefile : build instructions for g++ to include ws2_32.lib while building executables and where to place complied binaries 


# Use
Start server before starting the clients

To start client pass user name as argv[1] to client, when starting client 
`Example: client0 rohan`
