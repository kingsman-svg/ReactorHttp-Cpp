#include<iostream>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
using namespace std;

int main()
{   
    //1、创建通信的套接字
    int cfd = socket(AF_INET,SOCK_STREAM,0);
    if(cfd==-1)
    {
        perror("socket");
        exit(0);
    }

    //2、连接服务器
    struct sockaddr_in addr; 
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8989);
    inet_pton(AF_INET,"192.168.235.130",(char*)&addr.sin_addr.s_addr);
    int ret = connect(cfd,(sockaddr*)&addr,sizeof(addr));
    if(ret == -1)
    {
        perror("connect");
        exit(0);
    }

    //3、通信
    int num = 0;
    while(1)
    {
        //发送数据
        char buf[1024];
        sprintf(buf,"hello,world,%d,...",num++);    
        send(cfd,buf,strlen(buf)+1,0);

        //接受数据
        memset(buf,0,sizeof(buf));
        int len = recv(cfd,buf,sizeof(buf),0);//返回值是接受到的数据长度
        if(len == 0)
        {
            cout<<"服务器已经断开连接...\n";
            break;
        }
        else if(len>0)
        {
            cout<<"recv buf:"<<buf<<endl;
        }
        else
        {
            perror("recv");
            break;
        }

        sleep(2);//客户端不阻塞，因此要限制发送速率
    }

    //6、断开连接
    close(cfd);

    return 0;
}