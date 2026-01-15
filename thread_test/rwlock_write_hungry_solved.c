#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t rwlock;
int shared_data = 0;

void* lock_read(void* arg)
{
    pthread_rwlock_rdlock(&rwlock);
    printf("读线程%s尝试加读锁\n", (char*)arg);
    printf("当前线程为%s, shared_data = %d\n", (char*)arg, shared_data);
    sleep(1);
    pthread_rwlock_unlock(&rwlock);
    printf("读线程%s释放读锁\n", (char*)arg);
}

void* lock_writer(void* arg)
{
    pthread_rwlock_wrlock(&rwlock); // 加写锁
    printf("写线程%s尝试加写锁\n", (char*)arg);
    int tmp = shared_data + 1;
    shared_data = tmp;
    printf("当前线程为%s, shared_data = %d\n", (char*)arg, shared_data);
    pthread_rwlock_unlock(&rwlock); // 释放写锁
    printf("写线程%s释放写锁\n", (char*)arg);
}

int main(int argc, char const *argv[])
{
    // 初始化读写锁
    pthread_rwlockattr_t attr;
    pthread_rwlockattr_init(&attr);
    pthread_rwlockattr_setkind_np(&attr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
    pthread_rwlock_init(&rwlock, &attr);

    pthread_t reader1, reader2, reader3, reader4, reader5, reader6;
    pthread_t writer1, writer2;

    pthread_create(&writer1, NULL, lock_writer, "writer1");

    pthread_create(&reader1, NULL, lock_read, "reader1");
    pthread_create(&reader2, NULL, lock_read, "reader2");
    pthread_create(&reader3, NULL, lock_read, "reader3");

    pthread_create(&writer2, NULL, lock_writer, "writer2");

    pthread_create(&reader4, NULL, lock_read, "reader4");
    pthread_create(&reader5, NULL, lock_read, "reader5");
    pthread_create(&reader6, NULL, lock_read, "reader6");

    // 主线程等待创建的子线程运行完成
    pthread_join(writer1, NULL);
    pthread_join(writer2, NULL);
    pthread_join(reader1, NULL);
    pthread_join(reader2, NULL);
    pthread_join(reader3, NULL);
    pthread_join(reader4, NULL);
    pthread_join(reader5, NULL);
    pthread_join(reader6, NULL);

    // 销毁读写锁
    pthread_rwlock_destroy(&rwlock);
    
    return 0;
}
