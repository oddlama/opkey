#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <esp32/cache_err_int.h>
#include <esp32/dport_access.h>
#include <freertos/xtensa_timer.h>
#include <esp_log.h>


void main_cpu1();


/* Defined in portasm.h */
extern void _frxt_tick_timer_init(void);

/* Defined in xtensa_context.S */
extern void _xt_coproc_init(void);

extern volatile int port_xSchedulerRunning[2];


void start_cpu1(void) IRAM_ATTR __attribute__((noreturn));
//void __attribute__((weak, alias("start_cpu1_default"))) __attribute__((noreturn)) start_cpu1(void) {
void start_cpu1() {
    // Wait for FreeRTOS initialization to finish on PRO CPU
    while (port_xSchedulerRunning[0] == 0) {
        ;
    }

    esp_cache_err_int_init();
    esp_crosscore_int_init();
    esp_dport_access_int_init();

    ESP_EARLY_LOGI("OpKey", "Starting application on APP CPU.");

	// Interrupts are disabled at this point and stack contains PS with enabled interrupts when task context is restored

	#if XCHAL_CP_NUM > 0
	/* Initialize co-processor management for tasks. Leave CPENABLE alone. */
	_xt_coproc_init();
	#endif

	/* Init the tick divisor value */
	_xt_tick_divisor_init();

	/* Setup the hardware to generate the tick. */
	_frxt_tick_timer_init();

	main_cpu1();

	// Should never get here.
    abort();
}
