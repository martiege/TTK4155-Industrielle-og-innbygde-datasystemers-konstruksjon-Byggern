#include "controller.h"
#include "defines.h"
#include "timer.h"



void controller_init(int16_t ctrl_K_p, int16_t ctrl_K_i, int16_t ctrl_K_d)
{
	ctrl.sumE = 0;
	ctrl.y = 0;
	ctrl.r = 0;
	
	ctrl.K_p = ctrl_K_p;
	ctrl.K_i = ctrl_K_i;
	ctrl.K_d = ctrl_K_d;
	
	ctrl.maxE = MAX_INT / (ctrl.K_p + 1);
	ctrl.maxSumE = MAX_I_TERM / (ctrl.K_i + 1);
	
	timer_init(1, controller_update);
}

void controller_set_ref(int16_t ref)
{
	ctrl.ref = r;
}

void controller_reset_integrator()
{
	ctrl.sumE = 0;
}

void controller_set_sampling_time(uint16_t ms)
{
	timer_set_period(ms, 1);
}

void controller_start()
{
	timer_start(1);
}

void controller_stop()
{
	timer_stop(1);
}

void controller_update()
{
	int16_t error, p, d;
	int32_t i, ret, temp;
	
	int16_t meas = 0; // measure function
	
	error = ctrl.r - meas;
	
	// proportional term
	if (error > ctrl.maxE)
	{
		p = MAX_INT
	}
	else if (error < -ctrl.maxE)
	{
		p = -MAX_INT;
	}
	else
	{
		p = ctrl.K_p * error;
	}
	
	// integral term
	temp = ctrl.sumE + error;
	if (temp > ctrl.maxSumE)
	{
		ctrl.sumE = ctrl.maxSumE;
		i = MAX_I_TERM;
	}
	else if (temp < -ctrl.maxSumE)
	{
		ctrl.sumE = ctrl.maxSumE;
		i = -MAX_I_TERM;
	}
	else
	{
		ctrl.sumE = temp;
		i = ctrl.K_i * ctrl.sumE;
	}
	
	// derivative term
	d = ctrl.K_d * (ctrl.y - meas);
	ctrl.y = meas;
	
	ret = (p + i + d) / SCALING_FACTOR;
	if (ret > MAX_INT)
	{
		ret = MAX_INT;
	}
	else if (ret < -MAX_INT)
	{
		ret = -MAX_INT;
	}
	
	return ((int16_t)ret);
}