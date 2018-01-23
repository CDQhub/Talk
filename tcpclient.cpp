#pragma execution_character_set("utf-8") 
#include<iostream> 
#include<errno.h> 
#include<sys/socket.h> 
#include<memory> 
#include<cstdlib>
#include"tcpclient.h" 
using namespace std;  

Tcpclient::Tcpclient(char *ip, int port) 
{ 	
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); 	
        if(sockfd == -1) 	
        { 		
            cerr << "socket fail; errno:" << errno << endl; 	
        }  	

        _sockfd = sockfd; 	
        struct sockaddr_in saddr; 	
        memset(&(saddr), 0, sizeof(saddr)); 	
        saddr.sin_family = AF_INET; 	
        saddr.sin_port = htons(port); 	
        saddr.sin_addr.s_addr = inet_addr(ip); 	
        int res = connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)); 	
        if(res == -1) 	
        { 		
            cerr << "connect fail! errno:" << errno << endl; 		
            exit(1); 	
        } 
}  

Tcpclient::~Tcpclient() { }  

void Tcpclient::run() 
{ 	char cmd[1024];
    while(1) 	
    { 		
        memset(cmd, 0, strlen(cmd)); 		
        cin >> cmd;
        
        if(strcmp(cmd, "login"))
        {
            cout<<"Input your name:";
            char buff[1024] = {0};
            cin>>buff;
            Json::Value val;
            val["name"] = buff;
            cout<<"Input your password:";
            memset(buff, 0, strlen(buff));
            cin>>buff;
            val["pw"] = buff; 
            
            send(sockfd, val.toStyledString().c_str(), strlen(val.toStyledString().c_str()), 0);
        }
    } 
}
