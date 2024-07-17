#include<iostream>
#include<unistd.h>
#include<wait.h>
#include<sys/types.h>
using namespace std;
//使用兄弟进程，而不是父子进程实现命令 ls | ws-l
int main()
{
    int fd[2],i=0;
    pid_t pid;

    pipe(fd);//创建管道

    for(i=0;i<2;i++)
    {
        if((pid=fork())==0){
            break;
        }
    }
    if(i==0){
        //兄进程  ls
        close(fd[0]);//关闭读端
        dup2(fd[1],STDOUT_FILENO);
        execlp("ls","ls",NULL);
    }
    else if(i==1){
        //弟进程  wc -l
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        execlp("wc","wc","-l",NULL);
    }
    else{
        //父进程
        for(i=0;i<2;i++)
        {
            wait(NULL);
        }
    }
    return 0;
}