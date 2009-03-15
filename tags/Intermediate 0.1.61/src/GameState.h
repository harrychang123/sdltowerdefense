//Author: Corey Ruda
//Filename: GameState.h
//This is the game state class
//TODO: Implement Class GameState

class GameState
{
public:
	virtual void handle_events() = 0;
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual void GameState(){};
};
