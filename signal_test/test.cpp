#include<iostream>
#include<signal.h>
#include<sys/wait.h>
using namespace std;

void catch_child(int signum)
{
    //父进程收到SIGCHLD函数之后，调用waitpid回收子进程
    pid_t wpid;
    int status;
    while((wpid=waitpid(-1,&status,WNOHANG))>0){
        cout<<"Caught child pid = "<<wpid<<endl;
    }
}
int main()
{
    pid_t pid;
    int i;
    for(i=0;i<5;i++)
    {
        if((pid = fork())==0)
            break;//不让子进程参与后续fork操作
    }

    if(5==i){
        //父进程
        struct sigaction act;

        act.sa_handler = catch_child;
        act.sa_flags=0;
        sigemptyset(&act.sa_mask);

        sigaction(SIGCHLD,&act,NULL);

        while(1){
            pause();
        }
        
    }
    else{
        //子进程
        cout<<"child pid = "<<getpid()<<endl;
        sleep(2);
        return i;
    }

}
