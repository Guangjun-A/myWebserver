// 线程同步机制包装
#ifndef LOCKER_H
#define LOCKER_H

#include <exception> // 异常处理库
#include <pthread.h>
#include <semaphore.h> // 信号

// 封装信号类，实现PV操作
class sem {
private: 
    sem_t m_sem; // 声明一个信号量
public:
    // 析构函数，创建并初始化信号类
    sem(int num) { // num 表示资源数量
    // 第二个参数 pshared 控制信号量的类型，值为 0 代表该信号量用于多线程间的同步，值如果大于 0 表示可以共享，用于多个相关进程间的同步
        if (sem_init(&m_sem, 0, num) != 0) { 
            // __nonnull__ 指定非空指针属性
            throw std::exception(); // 创建成功应该返回0
        }
    }
    virtual ~sem() {sem_destroy(&m_sem);} // 对信号量进行释放资源，成功返回0
    bool wait() { // 申请资源，等待信号量
        return sem_wait(&m_sem) == 0; // 若 sem value > 0，则该信号量值减去 1 并立即返回。
    }
    bool post() { // 释放资源，增加信号量
        return sem_post(&m_sem) == 0; // 指定的信号量 sem 的值加 1，唤醒正在等待该信号量的任意线程
    }
};

// 封装互斥锁
class locker {
private:
    pthread_mutex_t m_lock; // 创建锁,或者说创建互斥量

public:
    // 初始化锁
    locker() {
        // 第一个参数锁指针，第二个参数锁属性
        if (pthread_mutex_init(&m_lock, NULL) != 0) {
            throw std::exception();
        }
    }
    // 释放锁资源
    virtual ~locker() { 
        pthread_mutex_destroy(&m_lock);
    };

    // 获取锁并加锁,成功时pthread_mutex_lock返回0
    bool lock() {
        return pthread_mutex_lock(&m_lock) == 0;
    }

    // 解锁， 成功时pthread_mutex_unlock返回0
    bool unlock() {
        return pthread_mutex_unlock(&m_lock);
    }

    // 获取锁
    pthread_mutex_t* get() {
        return &m_lock; 
    }
};

// 条件变量类
class cond {
private:
    pthread_cond_t m_cond; // 定义一个条件变量

public:
    // 初始化条件变量
    cond() { 
        if (pthread_cond_init(&m_cond, NULL) != 0) {
            throw std::exception();
        }
    }

    // 释放条件变量占用的内存
    virtual ~cond() {
        pthread_cond_destroy(&m_cond);
    }

    // 将线程放入条件变量的等待队列中
    void waitCond(pthread_mutex_t* mutex) {
        pthread_cond_wait(&m_cond, mutex);
    }

    // 按照一定的时间进行返回,pthread_cond_timedwait成功运行返回0,失败返回1
    bool timeWaitCont(pthread_mutex_t* mutex, timespec* waitTime) {
        int ret = pthread_cond_timedwait(&m_cond, mutex, waitTime);
        return ret == 0;
    }

    // 释放条件变量信号，唤醒条件变量等待队列中的一个进程
    bool signal() {
        return pthread_cond_signal(&m_cond) == 0;
    }

    // 释放条件变量信号，唤醒等待队列里所有的进程
    bool broadcast() {
        return pthread_cond_broadcast(&m_cond) == 0;
    }
};


#endif









