#include "../luftwaffle.hpp"

#include <math.h>

// physical component
void comp::physical::align(float target_angle, const float step)
{
	const float PI2 = 2.0f * M_PI;

	while(target_angle > PI2)
		target_angle -= PI2;

	while(target_angle < 0.0f)
		target_angle += PI2;

	while(rot > PI2)
		rot -= PI2;

	while(rot < 0.0f)
		rot += PI2;

	if(target_angle > rot)
	{
		if(target_angle - rot > M_PI)
		{
			rot -= step;

			if(rot < 0.0f)
			{
				rot += 2.0f * M_PI;

				if(rot < target_angle)
					rot = target_angle;
			}
		}
		else
		{
			rot += step;

			if(rot > target_angle)
				rot = target_angle;
		}
	}
	else
	{
		if(rot - target_angle > M_PI)
		{
			rot += step;

			if(rot > 2.0f * M_PI)
			{
				rot -= 2.0f * M_PI;

				if(rot > target_angle)
					rot = target_angle;
			}
		}
		else
		{
			rot -= step;

			if(rot < target_angle)
				rot = target_angle;
		}
	}
}
