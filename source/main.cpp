/*
	The MIT License (MIT)

	Copyright (c) 2016 Jeremy 'TurtleP' Postelnek - jeremy.postelnek@gmail.com

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include "shared.h"

bool romfsEnabled = false;
bool channelList[24];
bool hasError = false;
bool forceQuit = false;
bool audioEnabled = false;

void displayError(const char * error)
{
	hasError = true;

	printf("\n\x1b[31mError: %s\x1b[0m\nPress 'Start' to quit.\n", error);
}

int main()
{
	sf2d_init(); // 2D Drawing lib.

	//sftd_init(); // Text Drawing lib.

	cfguInit();

	ptmuInit();

	consoleInit(GFX_BOTTOM, NULL);
	
	sf2d_set_clear_color(RGBA8(61, 142, 185, 0xFF)); // Reset background color.

	Result enableROMFS = romfsInit();

	romfsEnabled = (enableROMFS) ? false : true;

	audioEnabled = !ndspInit();

	printf("%d\n", audioEnabled);

	if (romfsEnabled) chdir("romfs:/");

	if (!audioEnabled) displayError("DSP Failed to initialize. Please dump your DSPFirm!");

	printf("Hello, world!\n");

	OggVorbis * backgroundMusic = new OggVorbis("audio/bgm.ogg");
	backgroundMusic->setLooping(true);
	backgroundMusic->play();

	while (aptMainLoop())
	{
		if (!hasError)
		{
			//Start top screen
			sf2d_start_frame(GFX_TOP, GFX_LEFT);

			sf2d_end_frame();
		
			//Start bottom screen
			/*sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

			sf2d_end_frame();*/

			sf2d_swapbuffers();

			hidScanInput();
			u32 kTempDown = hidKeysDown();
			if (kTempDown & KEY_START) 
			{
				printf("Ayylmao! This is aptMainLoop!\n");
			}
		}
		else
		{
			sf2d_start_frame(GFX_TOP, GFX_LEFT);

			sf2d_end_frame();

			//Start bottom screen
			/*sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

			sf2d_end_frame();*/

			hidScanInput();
			u32 kTempDown = hidKeysDown();
			if (kTempDown & KEY_START) 
			{
				break;
			}

			sf2d_swapbuffers();
		}
	}

	//sftd_fini();

	sf2d_fini();

	cfguExit();

	ptmuExit();

	if (romfsEnabled) romfsExit();

	if (audioEnabled) ndspExit();

	return 0;
}