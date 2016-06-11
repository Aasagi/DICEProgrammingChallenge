#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#include "GameState.h"
#include "AudioSystem\Stream.h"

class MainMenu : public GameState
{
public:
	MainMenu(void);
	~MainMenu(void);

	void Init() override;
	void Update() override;
	void HandleInput() override;
	void HandleInputWithoutGUI() override;

private:
	Stream myMusic;
};

#endif