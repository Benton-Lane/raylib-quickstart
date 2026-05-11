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

	// Define the camera to look into our 3d world
	Camera camera = { 0 };
	camera.position = Vector3{ 0.0f, 3.0f, 3.0f };
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	// Load image to create texture for the cube
	Model model = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
	Image img = LoadImage("cubicmap_atlas.png");
	Image crop = ImageFromImage(img, Rectangle{ 0, img.height / 2.0f, img.width / 2.0f, img.height / 2.0f });
	Texture2D texture = LoadTextureFromImage(crop);
	UnloadImage(img);
	UnloadImage(crop);

	model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

	float rotation = 0.0f;

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// Update
		rotation += 1.0f;

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(RAYWHITE);

		BeginMode3D(camera);

		// Draw model defining: position, size, rotation-axis, rotation (degrees), size, and tint-color
		DrawModelEx(model, Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.5f, 1.0f, 0.0f },
			rotation, Vector3{ 1.0f, 1.0f, 1.0f }, WHITE);

		DrawGrid(10, 1.0f);

		EndMode3D();

		// draw some text with a new font
		DrawTextEx(test_font, "Sup nerds", Vector2{ 200, 200 }, test_font.baseSize, 0.5, ORANGE);

		// draw our texture to the screen
		DrawTexture(wabbit, 300, 200, WHITE);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// De-Initialization
	UnloadFont(test_font); // Unload font
	UnloadTexture(wabbit);
	UnloadTexture(texture); // Unload texture
	UnloadModel(model);     // Unload model

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}