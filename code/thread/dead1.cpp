#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
using namespace std;

pthread_mutex_t mutex;
pthread_t tid;

void* pthread_func(void* arg)
{
    cout<<"Thread started\n";

    //第一次上锁
    pthread_mutex_lock(&mutex);
    cout<<"Thread acquried lock 1\n";

    //第二次尝试上锁
    pthread_mutex_lock(&mutex);
    cout<<"Thread acquried lock 2\n";

    //解锁
    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex);

    cout<<"Thread has finished\n";

    return nullptr;

}


int main()
{
    //初始化锁
    pthread_mutex_init(&mutex,nullptr);

    //创建子线程
    int ret;
    ret = pthread_create(&tid,nullptr,pthread_func,nullptr);
    if(ret!=0){
        cout<<"creat pthread error:"<<strerror(ret)<<endl;
        exit(1);
    }

    //等待线程结束
    pthread_join(tid,NULL);

    //销毁互斥锁
    pthread_mutex_destroy(&mutex);

    return 0;






}