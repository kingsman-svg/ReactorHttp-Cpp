#include<iostream>
#include<unistd.h>
#include<wait.h>
using namespace std;

int main()
{
    //fd[0]读，fd[1]写
    int fd[2];
    int ret = pipe(fd);
    if(ret==-1){
        perror("pipe");
    } 

    pid_t pid = fork();
    if(pid==0){
        //子进程
        sleep(2);
        char buf[4096] = {0};
        read(fd[0],buf,4096);
        cout<<"child read:"<<buf<<endl;
    }
    else if(pid>0){
        //父进程
        write(fd[1],"hello\n",6);
        cout<<"write OK!"<<endl;
        wait(NULL);
        cout<<"Dad close!"<<endl;    
    }
    return 0;
}