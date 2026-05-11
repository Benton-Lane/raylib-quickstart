#include "raylib.h"

#include "resource_dir.h"

int main() {
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context, text = window title
	InitWindow(800, 600, "Baby's First Raylib Steps");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Test to create new font
	Font test_font = LoadFontEx("Fonts/Playwrite.ttf", 32, 0, 250);
	Vector2 textPos = { 200, 200 };

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("Sprites/wabbit_alpha.png");

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLUE);

		// draw some text using the default font
		//DrawText("Hey LOSER", 200, 200, 40, ORANGE);

		// draw some text with a new font
		DrawTextEx(test_font, "Hey LOSER", Vector2{ 200, 200 }, test_font.baseSize, 2, ORANGE);

		// draw our texture to the screen
		DrawTexture(wabbit, 400, 200, WHITE);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}