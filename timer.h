#include <assert.h>
//#include <CoreServices/CoreServices.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <unistd.h>

typedef struct {
	int      once;
	uint64_t time;
} timer;

static inline void timer_start(timer *t)
{
	t->once = 1;
	t->time = mach_absolute_time();
}

static inline void timer_stop(timer *t)
{
	mach_timebase_info_data_t tbase;
	uint64_t end;

	end = mach_absolute_time();
	t->once = 0;

	mach_timebase_info(&tbase);
	t->time = (end - t->time) * tbase.numer / tbase.denom;
}

#define timer_value(t) ((t)->time)
#define timed(t) for (timer_start(t); (t)->once; timer_stop(t))
