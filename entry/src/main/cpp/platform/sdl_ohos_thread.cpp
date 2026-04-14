#include "sdl_ohos.h"
#include <pthread.h>
#include <cstdlib>
#include <cstring>
#include <hilog/log.h>

#undef LOG_DOMAIN
#undef LOG_TAG
#define LOG_DOMAIN 0x0000
#define LOG_TAG "SDL_OHOS"

struct SDL_Thread {
    pthread_t thread;
    SDL_ThreadFunction func;
    void *data;
    char name[16];
    int status;
};

struct SDL_mutex {
    pthread_mutex_t mutex;
};

struct SDL_cond {
    pthread_cond_t cond;
};

struct SDL_sem {
    volatile int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

static void *thread_entry(void *arg)
{
    SDL_Thread *thread = static_cast<SDL_Thread *>(arg);
    thread->status = thread->func(thread->data);
    return nullptr;
}

SDL_Thread *SDL_CreateThread(SDL_ThreadFunction fn, const char *name, void *data)
{
    SDL_Thread *thread = new SDL_Thread();
    thread->func = fn;
    thread->data = data;
    thread->status = 0;
    if (name) {
        strncpy(thread->name, name, sizeof(thread->name) - 1);
        thread->name[sizeof(thread->name) - 1] = '\0';
    } else {
        thread->name[0] = '\0';
    }
    int ret = pthread_create(&thread->thread, nullptr, thread_entry, thread);
    if (ret != 0) {
        delete thread;
        return nullptr;
    }
    return thread;
}

void SDL_WaitThread(SDL_Thread *thread, int *status)
{
    if (thread) {
        pthread_join(thread->thread, nullptr);
        if (status) *status = thread->status;
        delete thread;
    }
}

int SDL_SetThreadPriority(SDL_ThreadPriority priority)
{
    return 0;
}

SDL_mutex *SDL_CreateMutex()
{
    SDL_mutex *mutex = new SDL_mutex();
    pthread_mutex_init(&mutex->mutex, nullptr);
    return mutex;
}

void SDL_DestroyMutex(SDL_mutex *mutex)
{
    if (mutex) {
        pthread_mutex_destroy(&mutex->mutex);
        delete mutex;
    }
}

int SDL_LockMutex(SDL_mutex *mutex)
{
    if (mutex) pthread_mutex_lock(&mutex->mutex);
    return 0;
}

int SDL_TryLockMutex(SDL_mutex *mutex)
{
    if (mutex) return pthread_mutex_trylock(&mutex->mutex) == 0 ? 0 : -1;
    return -1;
}

int SDL_UnlockMutex(SDL_mutex *mutex)
{
    if (mutex) pthread_mutex_unlock(&mutex->mutex);
    return 0;
}

SDL_cond *SDL_CreateCond()
{
    SDL_cond *cond = new SDL_cond();
    pthread_cond_init(&cond->cond, nullptr);
    return cond;
}

void SDL_DestroyCond(SDL_cond *cond)
{
    if (cond) {
        pthread_cond_destroy(&cond->cond);
        delete cond;
    }
}

int SDL_CondSignal(SDL_cond *cond)
{
    if (cond) pthread_cond_signal(&cond->cond);
    return 0;
}

int SDL_CondBroadcast(SDL_cond *cond)
{
    if (cond) pthread_cond_broadcast(&cond->cond);
    return 0;
}

int SDL_CondWait(SDL_cond *cond, SDL_mutex *mutex)
{
    if (cond && mutex) pthread_cond_wait(&cond->cond, &mutex->mutex);
    return 0;
}

int SDL_CondWaitTimeout(SDL_cond *cond, SDL_mutex *mutex, uint32_t ms)
{
    if (!cond || !mutex) return -1;
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += ms / 1000;
    ts.tv_nsec += (ms % 1000) * 1000000;
    if (ts.tv_nsec >= 1000000000) {
        ts.tv_sec++;
        ts.tv_nsec -= 1000000000;
    }
    int ret = pthread_cond_timedwait(&cond->cond, &mutex->mutex, &ts);
    return ret == 0 ? 0 : -1;
}

SDL_sem *SDL_CreateSemaphore(uint32_t initial_value)
{
    SDL_sem *sem = new SDL_sem();
    sem->value = (int)initial_value;
    pthread_mutex_init(&sem->mutex, nullptr);
    pthread_cond_init(&sem->cond, nullptr);
    return sem;
}

void SDL_DestroySemaphore(SDL_sem *sem)
{
    if (sem) {
        pthread_mutex_destroy(&sem->mutex);
        pthread_cond_destroy(&sem->cond);
        delete sem;
    }
}

int SDL_SemWait(SDL_sem *sem)
{
    if (!sem) return -1;
    pthread_mutex_lock(&sem->mutex);
    while (sem->value <= 0) {
        pthread_cond_wait(&sem->cond, &sem->mutex);
    }
    sem->value--;
    pthread_mutex_unlock(&sem->mutex);
    return 0;
}

int SDL_SemTryWait(SDL_sem *sem)
{
    if (!sem) return -1;
    int ret = -1;
    pthread_mutex_lock(&sem->mutex);
    if (sem->value > 0) {
        sem->value--;
        ret = 0;
    }
    pthread_mutex_unlock(&sem->mutex);
    return ret;
}

int SDL_SemPost(SDL_sem *sem)
{
    if (!sem) return -1;
    pthread_mutex_lock(&sem->mutex);
    sem->value++;
    pthread_cond_signal(&sem->cond);
    pthread_mutex_unlock(&sem->mutex);
    return 0;
}

uint32_t SDL_SemValue(SDL_sem *sem)
{
    if (!sem) return 0;
    return (uint32_t)sem->value;
}
