
#include <iostream>

#include <signal.h>
#include <string.h>
#include <stdlib.h>

#include <errno.h>
#include <string>
#include <fstream>
#include <sys/signal.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
const std::string PID_PATH = "/serverPath/server.pid";
const std::string SOCK_PATH = "/serverPath/socket";
const std::string LOG_PATH = "/serverPath/server.log";
const std::string SAVE_PATH =  "/serverPath/serverSaves/messages.txt";

void fork_handler(int);
void handle_connection(int);
void handle_args(int argc, char *argv[]);
void kill_daemon();
void daemonize();
void stop_server();
void init_socket();

int server_socket;

int main(int argc, char *argv[])
{

        if(argc > 1) {
                handle_args(argc, argv);
        }

        daemonize();

        signal(SIGTERM, stop_server);

        init_socket();

        if(listen(server_socket, 5) == -1)
        {
                perror("Listen failed");
                exit(1);
        }

        sockaddr_in client;
        socklen_t clientSize = sizeof(client);

        while(true) 
        {
                cout << "Waiting for a connection\n";
                
                if((client_socket = accept(server_socket, (sockaddr *)&client, &clientSize)) == -1)
                {
                        perror("Client accept failed");
                        exit(1);
                }

                cout << "Accepted connection\n";
                
                fork_handler(client_socket); 
        }
}

void fork_handler(int client_socket)
{
        switch(fork())
        {
                case -1:
                        perror("Error forking connection handler");
                        break;
                case 0:
                        handle_connection(client_socket);
                        exit(0);
                default:
                        break;
        }
}

void handle_connection(int client_socket)
{
        char buff[4096];
        unsigned int len;

        cout << "Handling connection\n";
        ofstream saveFile = ofstream(SAVE_PATH);

        while(len = recv(client_socket, &buff, 4096, 0), len > 0) 
                saveFile << buff << '\n';

        saveFile.close();
        close(client_socket);
        cout << "Done handling\n";
        
        exit(0);
}


void handle_args(int argc, char *argv[])
{
        std::string command = "kill";
        if(command == strcmp(argv[1])) 
                kill_daemon();
}


void daemonize()
{
        ofstream pidfile;
        pid_t pid, sid;

        switch(pid = fork())
        {
                case 0:

                        freopen("/dev/null", "r", stdin);
                        freopen(LOG_PATH, "w", stdout);
                        freopen(LOG_PATH, "w", stderr);
                        sid = setsid();
                        if (sid < 0) {
                                cout << "Failed creating unique session ID"
                                exit(EXIT_FAILURE);
                        }
                        chdir("/");
                        break;
                case -1:
                        perror("Failed to fork daemon\n");
                        exit(1);
                default: 
                        pidfile = std::ofstream(PID_PATH);
                        pidfile << pid;
                        pidfile.close();
                        exit(0);
        }
}

void stop_server()
{
        unlink(PID_PATH); 
        unlink(SOCK_PATH);
        kill(0, SIGKILL); 
        exit(0);
}

void init_socket()
{

        if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
                perror("Error creating server socket");
                exit(1);
        }

        

        sockaddr_in hint;
        hint.sin_family = AF_INET;
        strcpy(local.sin_path, SOCK_PATH);
        unlink(local.sin_path);
        inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
        if(bind(server_socket, (struct sockaddr *)&hint, sizeof(hint)) == -1)
        {
                perror("Bind failed");
                exit(1);
        }
}

void kill_daemon()
{
        ofstream pidfile;
        pid_t pid;

        if(pidfile = std::ofstream(PID_PATH))
        {
                pidfile >> pid;
                cout << "Killing PID" << pid << '\n';
                kill(pid, SIGTERM);
        }
        else
        {
                printf("Server not running\n"); 
        }
        exit(0);
}
