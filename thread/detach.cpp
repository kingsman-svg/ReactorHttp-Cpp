#include<iostream>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

using namespace std;

void* thread_func(void* arg)
{
    int threadnum = *reinterpret_cast<int*> (arg);
    cout<<"threadnum is "<<threadnum<<endl;
    return nullptr;
}

int main()
{
    int ret;

    //创建子线程
    const int thread_num = 3;
    pthread_t threads[thread_num];
    int threads_args[thread_num];
    for(int i=0;i<thread_num;i++)
    {
        threads_args[i]=i;
        ret = pthread_create(&threads[i],nullptr,thread_func,&threads_args[i]);
        if(ret!=0){
            cout<<"pthread_create error:"<<strerror(ret)<<endl;
        }

        //设置线程分离
        ret = pthread_detach(threads[i]);
        if(ret!=0){
            cout<<"pthread_detach error:"<<strerror(ret)<<endl;
        }

        sleep(2);
    }

    //模拟主线程工作
    sleep(5);

    cout<<"Main thread has finished."<<endl;

    return 0;

}