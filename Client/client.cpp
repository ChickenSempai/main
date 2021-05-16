#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string>
#include <fstream>
#include <sys/signal.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>

int client_socket;
void init_socket();

using namespace std;

int main()
{
    init_socket();
    //	While loop:
    char buf[4096];
    string userInput;


    while(true) {
        //		Enter lines of text
        cout << "> ";
        getline(cin, userInput);

        //		Send to server

        if (send(client_socket, userInput.c_str(), userInput.size() + 1, 0) == -1)
        {
            cout << "Could not send to server \n";
            continue;
        }

        //		Wait for response
        memset(buf, 0, 4096);
        int received = recv(client_socket, buf, 4096, 0);
        if (received  == -1)
        {
            cout << "There was an error getting response from server\n";
        }
        else
        {
            cout << "Server answer: " << string(buf, received) << "\n";
        }
    } 

    close(client_socket);

    return 0;
}

void init_socket()
{   
    if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error creating client socket");
        exit(1);
    }


    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    
    if (connect(client_socket, (sockaddr*)&hint, sizeof(hint)) == -1)
    {
        perror("Error connecting");
        exit(1);
    }

}
