#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
using namespace std;

int main(int argc,char* argv[])
{
    char buf[1024]={0};
    //标准输入的文件描述符是0
    ssize_t sret = read(0,buf,sizeof(buf));
    if(sret==-1) perror("read");
    cout<<sret<<" "<<buf<<endl;

    //read标准输入时，程序会产生阻塞，直到输入完成
    return 0;
}