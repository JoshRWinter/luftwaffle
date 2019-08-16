#include <time.h>

#include "../luftwaffle.hpp"

game::renderer::renderer(win::display &display, win::roll &roll)
	: screen(-8.0f, 8.0f, -4.5f, 4.5f)
	, quad(roll, screen)
	, glow(display, roll, screen)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.45f, 1.0f, 1.0f);

	font_renderer = display.make_font_renderer(display.width(), display.height(), screen.left, screen.right, screen.bottom, screen.top);
	font.small = font_renderer.make_font(roll["asset/font/arial.ttf"], 0.275f);
	font.med = font_renderer.make_font(roll["asset/font/arial.ttf"], 0.325f);
	font.big = font_renderer.make_font(roll["asset/font/Germania.otf"], 0.825f);
}

void game::renderer::frame(const game::world &world)
{
	// everything is centered around the player
	const ent::entity &player_entity = (*world.objectdb.player.begin()).entity;
	const comp::physical &player = player_entity.component<comp::physical>();

	quad.set_center(player.x, player.y);
	glow.set_center(player.x, player.y);

	for(const auto &renderable : world.objectdb.atlas_renderable_lasergun)
		quad.add(renderable);

	for(const auto &renderable : world.objectdb.atlas_renderable_waffle)
		quad.add(renderable);

	for(const auto &renderable : world.objectdb.atlas_renderable_goring)
		quad.add(renderable);

	for(const auto &renderable : world.objectdb.atlas_renderable_hitler)
		quad.add(renderable);

	for(const auto &renderable : world.objectdb.atlas_renderable_toaster)
		quad.add(renderable);

	for(const auto &renderable : world.objectdb.atlas_renderable_player)
		quad.add(renderable);

	for(const auto &renderable : world.objectdb.atlas_renderable_bomb)
		quad.add(renderable);

	for(const auto &renderable : world.objectdb.atlas_renderable_laser)
		quad.add(renderable);

	for(const auto &renderable : world.objectdb.atlas_renderable_particle_smoke)
		quad.add(renderable);

	for(const auto &renderable : world.objectdb.atlas_renderable_particle_laser)
		quad.add(renderable);

	for(const auto &renderable : world.objectdb.atlas_renderable_missile)
		quad.add(renderable);

	for(const auto &renderable : world.objectdb.atlas_renderable_explosion_cloud)
		quad.add(renderable);

	for(const auto &renderable : world.objectdb.atlas_renderable_particle_smoke)
		quad.add(renderable);

	for(const auto &renderable : world.objectdb.atlas_renderable_explosion_particle)
		quad.add(renderable);

	glBindTexture(GL_TEXTURE_2D, world.asset.atlas.texture());
	quad.send();

	for(const auto &renderable : world.objectdb.glow_renderable)
		glow.add(renderable);

	glow.send();

	drawhud(world, quad);
	drawfps();

	if(world.win)
		font_renderer.draw(font.big, "Victory", 0.0f, 0.0f, win::color(0.0f, 0.0f, 0.0f, 1.0f), win::font_renderer::CENTERED);
}

void game::renderer::drawhud(const game::world &world, game::quad &quad)
{
	const auto &player = *world.objectdb.player.begin();
	const auto &player_physical = player.entity.component<comp::physical>();
	const auto &health = player.entity.component<comp::health>();

	// health and ammo
	char healthtext[15];
	snprintf(healthtext, sizeof(healthtext), "Health: %d", health.hitpoints);
	font_renderer.draw(font.med, healthtext, screen.left + 1.0f, screen.bottom + 0.5f, win::color(1.0f, 1.0f, 1.0f));

	char ammotext[30];
	snprintf(ammotext, sizeof(ammotext), "Lasers: %d Rockets: %d", player.laser_count, player.rocket_count);
	font_renderer.draw(font.med, ammotext, 0.0f, screen.bottom + 0.5f, win::color(1.0f, 1.0f, 1.0f, 1.0f));

	if(world.objectdb.toaster.count() < 1 || world.objectdb.hitler.count() > 0 || world.objectdb.goring.count() > 0)
		return;
	const auto &toaster = *world.objectdb.toaster.begin();
	const auto &toaster_physical = toaster.entity.component<comp::physical>();
	// draw toaster arrow
	if(player_physical.distance(toaster_physical) > 10.0f)
	{
		const float angle = atan2f((toaster_physical.y + (game::TOASTER_HEIGHT / 2.0f)) - (player_physical.y + (game::PLAYER_HEIGHT / 2.0f)), (toaster_physical.x + (game::TOASTER_WIDTH / 2.0f)) - (player_physical.x + (game::PLAYER_WIDTH / 2.0f)));

		const float dist = 3.0f;
		const float xpos = cosf(angle) * dist;
		const float ypos = sinf(angle) * dist;

		quad.add_raw(xpos, ypos, 0.7f, 0.6f, angle, world.asset.atlas.coords(game::asset::aid::ARROW));
	}
}

void game::renderer::drawfps()
{
	// draw fps
	static int accumulate = 0;
	static int fps = 0;
	const int now = time(NULL);
	static int lasttime = 0;

	++accumulate;
	if(now != lasttime)
	{
		lasttime = now;
		fps = accumulate;
		accumulate = 0;
	}

	static char fpsbuffer[30];
	snprintf(fpsbuffer, sizeof(fpsbuffer), "fps: %d", fps);

	font_renderer.draw(font.small, fpsbuffer, screen.left + 0.1f, screen.top - font.small.size(), win::color(1.0f, 1.0f, 0.0f));
}
