#ifndef PWM_H
#define PWM_H

void pwm_init(int prescaler, int period, int init_duty);

void pwm_set_frequency(float frequency);

void pwm_start_frequency();

void pwm_stop_frequency();

void pwm_set_ticks(int ticks);

#endif
