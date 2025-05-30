// C++ program to illustrate the client application in the
// socket programming
#include <cstring>
#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>


int sendmess(sockaddr_in serverAddress, int clientSocket){
    if(connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
        printf("\nConnection Failed \n");
        return -1;
    }
    else{
        printf("Connection Success \n");
    };
    
    //std::cout << INADDR_ANY << "\n";

    // sending data
    //const char* message = "Hello, server ahihi!";
    std::string str;  
    std::getline(std::cin, str);  
    const char* message = str.c_str();
    send(clientSocket, message, strlen(message), 0); /**/
   
    while(1){
        std::getline(std::cin, str); message = str.c_str();
        send(clientSocket, message, strlen(message), 0);
        //while (getchar() != '\n');

    }
   // close(clientSocket); printf("Close \n");
    return 0;
}



int main()
{
    // creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    int *clientpt = &clientSocket;

    // specifying address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("192.168.2.250"); 
    sockaddr_in *serverpt = &serverAddress;

    // sending connection request
    //sendmess(serverAddress, clientSocket);
    //sendmess(serverpt, clientpt);


    if(connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
        printf("\nConnection Failed \n");
        return -1;
    }
    else{
        printf("Connection Success \n");
    };
    
    // sending data
    //const char* message = "Hello, server ahihi!";
    std::string str;  
    std::getline(std::cin, str);  
    const char* message = str.c_str();
    send(clientSocket, message, strlen(message), 0); /**/
   
    while(1){
        std::getline(std::cin, str); message = str.c_str();
        send(clientSocket, message, strlen(message), 0);
        //while (getchar() != '\n');

    }


    return 0;
}