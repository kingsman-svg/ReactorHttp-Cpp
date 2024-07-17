#include<sys/types.h>
#include<unistd.h>
#include<iostream>
using namespace std;
//返回进程的身份（使用者身份，不是拥有者身份），用于观察操作权限
int main()
{
    cout<<"uid="<<getuid()<<endl;
    cout<<"euid="<<geteuid()<<endl;
    return 0;
}