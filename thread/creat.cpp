#include<string.h>
#include<iostream>
#include<unistd.h>
#include<pthread.h>
using namespace std;

//子线程主体函数
void* tfn(void* arg)
{
    cout<<"thread id is "<<pthread_self()<<endl;
    return NULL;
}


int main()
{
    cout<<"process id is "<<getpid()<<endl;

    //创建子线程
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,tfn,NULL);
    if(ret != 0)
    {
        cout<<"error:"<<strerror(ret)<<endl;
    }

    //sleep(2);//给子线程执行空间
    //return 0;//释放进程空间

    pthread_exit((void*)0); //退出主线程

}