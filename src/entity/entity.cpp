#include "../luftwaffle.hpp"

bool ent::entity::collide(const ent::entity &entity, float tolerance) const
{
	return x + w - tolerance > entity.x && x + tolerance < entity.x + entity.w &&
	y + h - tolerance > entity.y && y + tolerance < entity.y + entity.h;
}
