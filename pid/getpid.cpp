#include<unistd.h>
#include<sys/types.h>
#include<iostream>
using namespace std;

//获取进程的id
int main()
{
    cout<<"pid=" << getpid()<<endl;
    cout<<"ppid=" <<getppid()<<endl;
    return 0;
}