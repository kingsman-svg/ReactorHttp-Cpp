#include<iostream>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
using namespace std;

struct msg{
    struct msg* next;
    int num;
};
struct msg *head;

pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void* consumer(void* arg)
{
    struct msg *mp;
    while(1)
    {
        pthread_mutex_lock(&lock);
        while(head==nullptr)
        {
            //如果共享区没有数据
            pthread_cond_wait(&has_product,&lock);
            //线程阻塞，wait等待siganl
        }
    }

    //模拟消耗一个产品
    mp=head;
    head = mp->next;
    pthread_mutex_unlock(&lock);

    cout<<"------consumer------"<<endl;
    delete mp;
    sleep(2);
    return nullptr;
    
}


void* producer(void* arg)
{
    struct msg *mp;
    while(1)
    {
        mp = new msg;
        mp->num = rand()%1000 + 1;//模拟生产一个产品
        cout<<"----------Producer-----------"<<endl;
        cout<<mp->num<<endl;

        //加锁保护
        pthread_mutex_lock(&lock);

        //写入公共区
        mp->next = head;
        head = mp;
        pthread_mutex_unlock(&lock);

        pthread_cond_signal(&has_product);//生产完毕，唤醒等待在cond条件变量上的一个线程
        sleep(2);
    }  
    return nullptr;
}


int main()
{
    pthread_t pid,cid;
    srand(time(NULL));

    pthread_create(&pid,nullptr,producer,nullptr);
    pthread_create(&cid,nullptr,consumer,nullptr);

    pthread_join(pid,nullptr);
    pthread_join(cid,nullptr);

    return 0;
}