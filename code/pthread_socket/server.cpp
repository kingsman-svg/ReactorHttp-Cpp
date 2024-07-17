#include<unistd.h>
#include<string.h>
#include<iostream>
#include<pthread.h>
#include<arpa/inet.h>
using namespace std;

//存储文件描述符的数组
struct SockInfo
{
    int fd;
    struct sockaddr_in addr;
};
struct SockInfo fds[1024];

//线程回调函数
void* pthread_func(void* arg)
{
    struct SockInfo* info = (struct SockInfo*) arg;
    
    //和连接成功的服务器通信
     while(1)
    {
        //接收客户端数据
        char buf[1024];
        memset(buf,0,sizeof(buf));

        //recv是阻塞函数，如果客户端不发数据就阻塞
        int len = recv(info->fd,buf,sizeof(buf),0);
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
            send(info->fd,buf,strlen(buf),0);
        }
    }

    close(info->fd);
    info->fd = -1;
    return nullptr;
}



int main()
{
    //1、创建监听的套接字
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
    int ret = bind(lfd,(sockaddr*)&addr,sizeof(addr));
    if(ret==-1)
    {
        perror("bind");
        exit(0);
    }

    //3、设置监听
    ret = listen(lfd,128);
    if(ret==-1)
    {
        perror("liseten");
        exit(0);
    }

    //4、创建子线程进行通信
    struct sockaddr_in c_addr;
    int c_len = sizeof(c_addr);

    //初始化文件描述符数组
    int len = sizeof(fds)/sizeof(struct SockInfo);
    for(int i=0;i<len;i++)
    {
        fds[i].fd=-1;
    }

    while(1)
    {
        //主线程
        int cfd = accept(lfd,(sockaddr*)&c_addr,(socklen_t*)&c_len);
        if(cfd==-1)
        {
            perror("accept");
            continue;
        }

            //建立连接成功,打印客户端信息
        char ip[24];
        cout<<"客户端ip:"<<inet_ntop(AF_INET,&c_addr.sin_addr.s_addr,ip,sizeof(ip))<<endl;
        cout<<"客户端port:"<<ntohs(c_addr.sin_port)<<endl;

        //找到一个数组中的位置存储文件描述符
        struct SockInfo* ptr = nullptr;
        for(int i=0;i<len;++i)
        {
            if(fds[i].fd==-1)
            {
                //找到了可用元素
                fds[i].fd=cfd; //存储用于通信的文件描述符
                ptr = &fds[i]; //防止线程内存冲突
            }
        }

        pthread_t tid;
        ret = pthread_create(&tid,nullptr,pthread_func,ptr);
        //设置线程分离
        pthread_detach(tid);

    }

    return 0;
}

