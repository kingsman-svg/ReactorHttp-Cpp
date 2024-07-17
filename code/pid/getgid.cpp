#include<sys/types.h>
#include<unistd.h>
#include<iostream>

using namespace std;

//返回用户的组id
int main()
{
    cout<<"gid="<<getgid()<<endl;
    cout<<"egid="<<getegid()<<endl;
    return 0;
}