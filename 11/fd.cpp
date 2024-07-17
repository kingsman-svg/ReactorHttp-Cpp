#include<iostream>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
using namespace std;

//若在fork()之前打开文件描述符,则fork()创建的进程对于文件对象是共享的,这包括共享文件指针
int main(int argc,char* argv[])
{
    int fd = open(argv[1],O_RDWR);
    if(fork()==0)
    {
        //int fd = open(argv[1],O_RDWR);
        write(fd,"hello",5);
    }
    else{
        //int fd = open(argv[1],O_RDWR);
        sleep(2);
        write(fd,"world",5);
    }
    close(fd);
    return 0;
}