#include<iostream>
#include<unistd.h>
#include<sys/types.h>
using namespace std;
//根据fork的返回值，调用父子进程执行不同的函数
int main()
{
    pid_t pid = fork();
    //fork()的返回值有两个：0为刚刚创建的子进程，>0为父进程，-1为创建失败
    if(pid>0){
        cout<< "parent hello!"<<" my pid = "<<getpid()<<" my ppid = "<<getppid()<<endl;
    }
    else if(pid == 0){ 
        cout<<"child hello!"<<" my pid = "<<getpid()<<" my ppid = "<<getppid()<<endl;
    }
    else perror("fork");
    return 0;
}
