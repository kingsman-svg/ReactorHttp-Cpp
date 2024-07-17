#include<iostream>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
using namespace std;

void* pthread_func(void* arg)
{
    cout<<"pthread create!"<<endl;
    sleep(2);
    return (void*)74;
}

int main()
{
    pthread_t tid;

    //创建子线程
    int ret = pthread_create(&tid,nullptr,pthread_func,nullptr);
    if(ret!=0){
        cout<<"create pthread error:"<<strerror(ret)<<endl;
    }

    // //设置线程分离
    // ret = pthread_detach(tid);
    // if(ret!=0){
    //     cout<<"pthread detach error:"<<strerror(ret)<<endl;
    // }

    //回收子线程的退出值
    void* retval;
    int ret2=pthread_join(tid,(void**)retval);
    if(retval!=0){
        cout<<"join error:"<<strerror(ret2)<<endl;
    }
    cout<<"pthread exit with:"<<retval<<endl;

    //退出主线程
    pthread_exit((void*)0);
    return 0;
}