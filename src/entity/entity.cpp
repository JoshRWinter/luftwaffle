#define _USE_MATH_DEFINES
#include "../luftwaffle.hpp"

bool ent::entity::collide(const ent::entity &entity, float tolerance) const
{
	return x + w - tolerance > entity.x && x + tolerance < entity.x + entity.w &&
	y + h - tolerance > entity.y && y + tolerance < entity.y + entity.h;
}

bool ent::entity::collide(const float xpos, const float ypos) const
{
	return x + w > xpos && x < xpos && y + h > ypos && y < ypos;
}

bool ent::entity::in_range(const ent::entity &other, float range) const
{
	return x + w + range > other.x && x < other.x + other.w + range &&
	y + h + range > other.y && y < other.y + other.h + range;
}

void ent::entity::align(float target_angle, const float step)
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
