#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;

int main()
{
    int pid = fork();
    if(pid==0)
    {//子进程不死
        while(1);
    }
    else{
        //父进程
        int status;
        while(1)
        {
            int ret = waitpid(-1,&status,WNOHANG);//WNOHANG可以实现非阻塞wait
            if(ret==0){
                //选定WNOHANG且返回值为0,说明没有子进程终止
                cout<<"no child has been dead!"<<endl;
                sleep(2);
            }
            else{
                //有子进程终止
                if(WIFEXITED(status)) cout<<"child exit normally! exit code is "<<WEXITSTATUS(status)<<endl;
                else if(WIFSIGNALED(status)) cout<<"child exit abnormally! terminal signal is "<<WTERMSIG(status)<<endl;
                break;
            }
        }
    }
    return 0;
}
