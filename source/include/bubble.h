#pragma once

class Bubble
{
	public:
		Bubble(sf2d_texture * texture);
		void render();
		void update(float dt);
		void resetBubble();
		bool shouldRemove();
		int getZOrder();
		
	private:
		Image * graphic;
		float x;
		float y;
		int width;
		int height;
		int currentScreen;
		bool remove;
		int zOrder;
};