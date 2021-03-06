#include <shared.h>

Image::Image(sf2d_texture * texture)
{
	this->texture = texture;
}

int Image::getWidth()
{
	return this->texture->width;
}

int Image::getHeight()
{
	return this->texture->height;
}

void Image::render(float x, float y)
{
	if (sf2d_get_current_screen() == getCurrentScreen()) 
	{
		sf2d_draw_texture_blend(this->texture, x, y, getCurrentColor());
	}
}

void Image::render(Quad quad, float x, float y)
{
	if (sf2d_get_current_screen() == getCurrentScreen()) 
	{
		sf2d_draw_texture_part_blend(this->texture, x, y, quad.getX(), quad.getY(), quad.getWidth(), quad.getHeight(), getCurrentColor());
	}
}