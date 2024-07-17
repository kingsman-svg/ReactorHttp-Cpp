#include<iostream>
#include<sys/wait.h>
#include<unistd.h>
using namespace std;
int main()
{
    int wstatus;
    pid_t wpid = 0;
    pid_t pid = fork();
    if(pid==-1){
        perror("fork");
    }
    else if(pid==0){
        cout<<"child process! pid = "<<getpid()<<endl;
        sleep(20);
        exit(98);
    }
    else{
        wpid=wait(&wstatus); //保存子进程的退出状态
        if(wpid==-1) perror("wait");
        else if(WIFEXITED(wstatus)){
            cout<<"parent process! child exit normally, code = "<<WIFEXITED(wstatus)<<endl;
        }
        else if(WIFSIGNALED(wstatus)){
            cout<<"parent process! child exit abnormally, killed by signal "<<WIFSIGNALED(wstatus)<<endl;
        }
    }

    return 0;
}