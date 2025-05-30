#include <iostream>
#include <thread>/* w   w w  . d  e    mo   2 s   .   co   m */

#include <cstring>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <netinet/in.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <net/route.h>

// Function that will be executed in a separate thread
void threadFunction() {
    // Perform some operations
    std::cout << "Thread is running!" << std::endl;

    // Simulate some work
    while(1){
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Thread execution complete
    std::cout << "Thread execution complete!" << std::endl;}
}


void threadFunction1() {
    // Perform some operations
    std::cout << "Thread is running 111!" << std::endl;

    // Simulate some work
    while(1){
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Thread execution complete
    std::cout << "Thread execution complete!111" << std::endl;}
}



void serverRun(){
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);


    // specifying the address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr =  inet_addr("0.0.0.0");// INADDR_ANY;

    // binding socket.
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    
    // listening to the assigned socket
    
    printf("Server on\n");

    while(1){
        // accepting connection request
        listen(serverSocket, 5);
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        // recieving data
        char buffer[1024] = { 0 };

    
        while(recv(clientSocket, &buffer, 1, MSG_PEEK | MSG_DONTWAIT)){ //recv(sock, &buf, 1, MSG_PEEK | MSG_DONTWAIT);
            char buffer1[1024] = { 0 };
            recv(clientSocket, buffer1, sizeof(buffer1), 0);
            std::cout << "Message from client: " << buffer1 << std::endl;
        }
    }
    // closing the socket.
    close(serverSocket);
}


int clientRun(){
    // creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    int *clientpt = &clientSocket;

    // specifying address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); //172.28.165.27
    sockaddr_in *serverpt = &serverAddress;

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
    }

    return 0;
}



int main() {
    
    /*
    // Create a thread and execute the threadFunction
    std::thread myThread(threadFunction);
    // Detach the thread
    std::thread myThread1(threadFunction1);
    // Detach the thread
    myThread.join();myThread1.join();
    */

    std::thread myThread(serverRun);
    std::thread myThread1(clientRun);
    myThread.join();myThread1.join();


    // Continue executing the main thread
    std::cout << "Main thread continues..." << std::endl;
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Main thread execution complete
    std::cout << "Main thread execution complete!" << std::endl;


    

    



    return 0;
}