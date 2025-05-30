// C++ program to show the example of server application in
// socket programming

#include <iostream>
#include <cstring>
#include <netinet/in.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <net/route.h>

#include <bitset>

using namespace std;


void getIPAddress(char *interface, char *ipAddress) {
    int fd;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, interface, IFNAMSIZ - 1);
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);

    strcpy(ipAddress, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
}



int main()
{// creating socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying the address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr =  inet_addr("0.0.0.0");// INADDR_ANY;

    // binding socket.
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    
    // listening to the assigned socket
    
    printf("Server on\n");

    while(1){
        // accepting connection request
        listen(serverSocket, 5);
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        // recieving data
        char buffer[1024] = { 0 };

    
        while(recv(clientSocket, &buffer, 1, MSG_PEEK | MSG_DONTWAIT)){
            char buffer1[1024] = { 0 };
            recv(clientSocket, buffer1, sizeof(buffer1), 0);
            std::cout << "Message from client: " << buffer1 << endl;
            
        }
            
       
        
        
    }
    // closing the socket.
    close(serverSocket);

    char ipAddress[INET_ADDRSTRLEN];
    //getIPAddress("eth0", ipAddress);
    //printf("IP Address     : %s\n", ipAddress);
    


    return 0;
}