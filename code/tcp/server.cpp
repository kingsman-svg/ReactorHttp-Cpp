#include<iostream>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
using namespace std;

int main()
{   
    //1、创建监听的套接字
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    if(lfd==-1)
    {
        perror("socket");
        exit(0);
    }

    //设置端口复用
    int optval = 1;
    setsockopt(lfd,SOL_SOCKET,SO_REUSEPORT,&optval,sizeof(optval));


    //2、绑定
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;//指定协议
    addr.sin_port = htons(8989);//指定端口
    addr.sin_addr.s_addr = INADDR_ANY;//指定ip地址

    int ret = bind(lfd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret==-1)
    {
        perror("bind");
        exit(0);
    }

    //3、设置监听
    ret = listen(lfd,128);
    if(ret == -1)
    {
        perror("listen");
        exit(0);
    }

    //4、等待并接受客户端连接
    struct sockaddr_in c_addr;
    int c_len = sizeof(c_addr);

    int cfd = accept(lfd,(struct sockaddr*)&c_addr,(socklen_t*)&c_len);
    if(cfd == -1)
    {
        perror("accept");
        exit(0);
    }

    //5、通信
    while(1)
    {
        //接受数据
        char buf[1024];
        memset(buf,0,sizeof(buf));
        int len = recv(cfd,buf,sizeof(buf),0);//返回值是接受到的数据长度
        if(len == 0)
        {
            cout<<"客户端已经断开连接...\n";
            break;
        }
        else if(len>0)
        {
            cout<<"recv buf:"<<buf<<endl;
            //回复数据
            send(cfd,buf,strlen(buf)+1,0); //回复数据+'\0'
        }
        else
        {
            perror("recv");
            break;
        }
    }

    //6、断开连接
    close(lfd);
    close(cfd);

    return 0;
}