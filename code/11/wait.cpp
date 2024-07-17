#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>
using namespace std;
int main(int argc,char* argv[])
{
    int pid = fork();
    if(pid==-1) perror("fork");
    else if(pid==0)
    {//子进程
        cout<<"child is running..."<<endl;
        return 500;
    }
    else{
        //父进程
        int status;
        wait(&status);
        if(WIFEXITED(status)){
            cout<<"child exit normally! exit code is "<<WEXITSTATUS(status)<<endl;
        }
        else if(WIFSIGNALED(status)){
            cout<<"child exit abnormally! terminal signal is "<<WTERMSIG(status)<<endl;
        }
        cout<<"father exit!"<<endl;

    }
    return 0;
}
