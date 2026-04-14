#include "sdl_ohos.h"
#include <time.h>
#include <unistd.h>
#include <hilog/log.h>

#undef LOG_DOMAIN
#undef LOG_TAG
#define LOG_DOMAIN 0x0000
#define LOG_TAG "SDL_OHOS"

static uint64_t g_start_time_ns = 0;
static const uint64_t NANOSECONDS_PER_MILLISECOND = 1000000;

static void ensure_start_time()
{
    if (g_start_time_ns == 0) {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        g_start_time_ns = (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
    }
}

uint32_t SDL_GetTicks()
{
    ensure_start_time();
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    uint64_t now_ns = (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
    return (uint32_t)((now_ns - g_start_time_ns) / NANOSECONDS_PER_MILLISECOND);
}

uint64_t SDL_GetPerformanceCounter()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}

uint64_t SDL_GetPerformanceFrequency()
{
    return 1000000000ULL;
}

void SDL_Delay(uint32_t ms)
{
    if (ms > 0) {
        usleep(ms * 1000);
    }
}
