#include<signal.h>
#include<iostream>
#include<sys/types.h>
#include<unistd.h>
using namespace std;

int main()
{
    
    pid_t pid = fork();
    if(pid==0)
    {
        //子进程
        sleep(20);
        kill(getppid(),SIGKILL);
    }
    else if(pid > 0)
    {
        //父进程
        while (1)
        {
            cout<<"parent!"<<endl;
            usleep(100000);
        }
        
    }
    return 0;
}
