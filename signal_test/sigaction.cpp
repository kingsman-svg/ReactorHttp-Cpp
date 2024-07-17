#include<signal.h>
#include<iostream>
using namespace std;

void sig_catch(int signum)
{
    cout<<"Caught signal num is:"<<signum<<endl;
}

int main()
{
    struct sigaction act, old_act;
    act.sa_handler = sig_catch;
    sigemptyset(&act.sa_mask); //清空sa_mask屏蔽字
    act.sa_flags = 0;   //本信号自动屏蔽

    if(sigaction(SIGINT,&act,&old_act))
    {
        perror("sigaction");
        exit(1);
    }

    while(1)
    {
        pause();
    }

    return 0;

}