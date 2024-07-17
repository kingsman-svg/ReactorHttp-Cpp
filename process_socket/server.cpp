#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<iostream>
#include<arpa/inet.h>
#include<signal.h>
using namespace std;

//子进程和客户端通信的函数
void working(int fd)
{
    while(1)
    {
        //接收客户端数据
        char buf[1024];
        memset(buf,0,sizeof(buf));

        //recv是阻塞函数，如果客户端不发数据就阻塞
        int len = recv(fd,buf,sizeof(buf),0);
        if(len==0){
            cout<<"客户端断开连接..."<<endl;
            break;
        }
        else if (len==-1){
            perror("recv");
            break;
        }
        else{
            cout<<"客户端say:"<<buf<<endl;
            //回复数据
            send(fd,buf,strlen(buf),0);
        }
    }

    close(fd);
}

void recycle(int num)
{
    while (1)
    {
        pid_t pid = waitpid(-1,nullptr,WNOHANG);
        if(pid>0)
        {
            cout<<"子进程被回收了,pid:"<<pid<<endl;
        }
        else{
            break;
        }
    }
    
}

int main()
{
    //1、创建监听的文件描述符
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    if(lfd==-1)
    {
        perror("socket");
        exit(0);
    }

    //2、绑定
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8989);
    addr.sin_addr.s_addr = INADDR_ANY;
    int len = sizeof(addr);
    int ret = bind(lfd,(sockaddr*)&addr,(socklen_t)len);
    if(ret==-1)
    {
        perror("bind");
        exit(0);
    }

    //3、监听
    ret = listen(lfd,128);
    if(ret==-1)
    {
        perror("listen");
        exit(0);
    }
    
    //注册信号捕捉
    struct sigaction act;
    act.sa_handler = recycle;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD,&act,nullptr);



    //4、接受连接
    struct sockaddr_in c_addr;
    int c_len = sizeof(c_addr);
    while(1)
    {
        int cfd = accept(lfd,(sockaddr*)&c_addr,(socklen_t*)&c_len);
        if(cfd==-1)
        {
            perror("建立连接失败！正在重新尝试连接...\n");
            continue;
        }
        char ip[24];
        cout<<"客户端的IP:"<<inet_ntop(AF_INET,&c_addr.sin_addr.s_addr,ip,sizeof(ip))<<endl;
        cout<<"客户端的端口:"<<ntohs(c_addr.sin_port)<<endl;


        //连接建立成功，创建子进程，在子进程中进行通信
        pid_t pid = fork();
        if(pid==0)
        {
            //当前进程是子进程
            //和客户端通信
            close(lfd);
            working(cfd);//传入需要通信的fd
            exit(0);
        }
        else{
            //父进程
            close(cfd);
        }
    }

}