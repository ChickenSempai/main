#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

AAAAAA

int client_socket;
void init_socket();

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

        if (send(sock, userInput.c_str(), userInput.size() + 1, 0) == -1)
        {
            cout << "Could not send to server \n";
            continue;
        }

        //		Wait for response
        memset(buf, 0, 4096);
 
        if (recv(client_socket, buf, 4096, 0) == -1)
        {
            cout << "There was an error getting response from server\n";
        }
        else
        {
            cout << "Server answer: " << string(buf, bytesReceived) << "\n";
        }
    } 

    close(client_socket);

    return 0;
}

void init_socket()
{
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        exit(1);
    }

    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    
    if (connect(client_socket, (sockaddr*)&hint, sizeof(hint)) == -1)
    {
        exit(1);
    }

}
