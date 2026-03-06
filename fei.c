#include "udf.h"

/* Define your acceleration parameters */
#define ACCELERATION 10  /* Acceleration in m/s^2 (change as needed) */
#define INITIAL_VELOCITY 0.0  /* Initial velocity in m/s */

static real velocity = INITIAL_VELOCITY;
static real current_time = 0.0;

DEFINE_CG_MOTION(gogogo, dt, vel, omega, time, dtime)
{
    /* Reset velocity and time when starting a new simulation */
    if (time < current_time)
    {
        velocity = INITIAL_VELOCITY;
        current_time = 0.0;
    }

    /* Update the current time */
    current_time = time;

    /* Calculate new velocity: v = v0 + a*t */
    velocity = INITIAL_VELOCITY + ACCELERATION * time;

    /* Set angular velocity to zero (no rotation) */
    omega[0] = 0.0;
    omega[1] = 0.0;
    omega[2] = 0.0;

    /* Set linear velocity - only in Z-direction */
    vel[0] = 0.0;  /* x-component */
    vel[1] = 0.0;  /* y-component */
    vel[2] = velocity;  /* z-component */

    /* For debugging - print time and velocity to console */
#if RP_NODE
    printf("Time = %f, Velocity = %f\n", time, velocity);
#endif
}
DEFINE_ON_DEMAND(print_rigid_motion_info)
{
	real time = CURRENT_TIME;        // 获取当前物理时间
}