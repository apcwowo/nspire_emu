#include "types.h"

static inline u16 BSWAP16(u16 x) { return x << 8 | x >> 8; }
static inline u32 BSWAP32(u32 x) {
	if (__builtin_constant_p(x)) return x << 24 | (x << 8 & 0xFF0000) | (x >> 8 & 0xFF00) | x >> 24;
	asm ("bswap %0" : "=r" (x) : "0" (x)); return x;
}

/* Declarations for emu.c */

extern int cycle_count_delta;

extern int throttle_delay;

extern u32 cpu_events;
#define EVENT_IRQ 1
#define EVENT_FIQ 2
#define EVENT_RESET 4
#define EVENT_DEBUG_STEP 8
#define EVENT_WAITING 16

extern bool exiting;
extern bool do_translate;
extern int product;
extern int asic_user_flags;
#define emulate_casplus (product == 0x0C0)
// 0C-0E (CAS, lab cradle, plain Nspire) use old ASIC
// 0F-12 (CX CAS, CX, CM CAS, CM) use new ASIC
#define emulate_cx (product >= 0x0F0)
extern bool turbo_mode;
extern bool is_halting;
extern bool show_speed;

enum { LOG_CPU, LOG_IO, LOG_FLASH, LOG_INTS, LOG_ICOUNT, LOG_USB, LOG_GDB, MAX_LOG };
#define LOG_TYPE_TBL "CIFQ#UG";
extern int log_enabled[MAX_LOG];
void logprintf(int type, char *str, ...);

void warn(char *fmt, ...);
__attribute__((noreturn)) void error(char *fmt, ...);
void throttle_timer_on();
void throttle_timer_off();
int exec_hack();
typedef void fault_proc(u32 mva, u8 status);
fault_proc prefetch_abort, data_abort;
void add_reset_proc(void (*proc)(void));




