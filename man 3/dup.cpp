#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
using namespace std;
//oldfd和newfd指向的是一个文件对象，但是他们的fd数值不同，但是对pos是继承的，即共享偏移量
//引用计数机制
int main(int argc,char* argv[])
{
    int oldfd = open(argv[1],O_RDWR);
    cout<<"oldfd="<<oldfd<<endl;
    int newfd = dup(oldfd);
    cout<<"newfd="<<newfd;
    return 0;
}