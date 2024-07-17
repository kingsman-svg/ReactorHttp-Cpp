#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<iostream>
#include<string.h>
using namespace std;
int main(int argc,char* argv[])
{
    int fd_r=open(argv[1],O_RDONLY);
    if(fd_r==-1) perror("open fd_r");
    int fd_w=open(argv[2],O_WRONLY|O_TRUNC|O_CREAT,0666);
    if(fd_w==-1) perror("open fd_w");
    char buf[4096]={0};
    while(1)
    {
        memset(buf,0,sizeof(buf));
        ssize_t sret = read(fd_r,buf,sizeof(buf));
        if(sret==-1) perror("read");
        //读取磁盘文件，如果read返回值为0,则读完
        if(sret==0) break;
        else write(fd_w,buf,sret);//写入文件  
    }
    close(fd_r);
    close(fd_w);
}
//只适合小文件的copy，因为read和write是系统调用，频繁调用会使cpu状态频繁改变，执行效率太低
