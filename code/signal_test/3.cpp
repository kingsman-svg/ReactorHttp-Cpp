#include<unistd.h>
#include<signal.h>
#include<iostream>
using namespace std;

void print_pedset(sigset_t *set)
{
    for(int i=0;i<32;i++)
    {
        if(sigismember(set,i)){
            cout<<'1';
        }
        else{
            cout<<'0';
        }
    }
}



int main()
{
    //定义自定义信号集
    sigset_t set;

    //清空自定义信号集
    sigemptyset(&set);

    //将SIGINT信号添加到自定义信号集
    sigaddset(&set,SIGINT);

    //借助自定义信号集，设置pcb中阻塞信号集中的2号信号为屏蔽
    sigset_t oldset;
    int ret = sigprocmask(SIG_BLOCK,&set,&oldset);
    if(ret==-1)
    {
        perror("sigprocmask");
        exit(1);
    }

    sigset_t pedset;    
    //获取当前的未决信号集
    ret = sigpending(&pedset);
    if(ret==-1)
    {
       perror("sigpending");
        exit(1);
    }
    //打印未决信号集
    sleep(2);
    print_pedset(&pedset);
    cout<<endl;


    return 0;

}