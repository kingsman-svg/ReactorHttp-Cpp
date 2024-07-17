#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
using namespace std;
int main(int argc,char* argv[])
{
    //重定向之前要先打印一个换行符
    cout<<endl;
    close(STDOUT_FILENO);
    int fd = open(argv[1],O_RDWR);
    cout<<fd<<endl;
    return 0;
}