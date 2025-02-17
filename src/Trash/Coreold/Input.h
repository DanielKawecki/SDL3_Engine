
#ifndef INPUT_H
#define INPUT_H

class Input {

private:
	bool _keyDown[232];
	bool _keyPressed[232];
	bool _keyDownLastFrame[232];

	bool _forceCloseWindow;

public:

	Input();
	~Input();

	void Update();
	bool IsKeyDown(int sdlScancode) const;
	bool IsKeyPressed(int sdlScancode) const;
	bool ForceCloseWindow() const;
};

#endif // !INPUT_H

