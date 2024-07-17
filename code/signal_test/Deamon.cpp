#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
using namespace std;

void creat_Daemon(){
    pid_t pid ;

    //创建子进程，让子进程创立一个会话
    pid = fork();
    if(pid<0){
        perror("fork");
        exit(0);
    }
    else if(pid>0){
        //父进程直接退出
        exit(EXIT_SUCCESS);
    }
    
    //子进程创建session
    if(setsid()<0)
    {
        perror("setsid");
        exit(0);
    }
    //改变工作目录，防止多占用挂载点
    if(chdir("/")<0){
        perror("chdir");
        exit(EXIT_FAILURE);
    }
    //关闭标准文件描述符
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    //重定向标准文件描述符到/dev/null
    open("/dev/null",O_RDWR);
    dup(0);
    dup(0);
    //模拟守护进程其他的工作
    while(1)
    {
        sleep(30);
    }
}


int main(int argc,char* argv[])
{
    creat_Daemon();
    return 0;
}
