#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Timer.h"
#include "AudioManager.h"
#include "Scoreboard.h"
#include "Player.h"
#include "Tiles.h"
#include "Pooka.h"
#include "Fygar.h"
#include "Rock.h"
#include <vector>
#include <string>

class PlayScreen : public GameEntity {
private:
	Timer * mTimer;
	AudioManager * mAudio;
	InputManager* mInput;
	GameEntity* mTopBar;
	int RockAmount = 1;
	int PookaAmount = 1;
	int FygarAmount = 1;
	int RFamount = 0;
	int WFamount = 1;
	int HavePookas = 0;
	int HaveFygars = 0;
	int FoodScore = 400;
	Scoreboard* mPlayerOneScore;
	Scoreboard* mPlayerTwoScore;
	Scoreboard* mTopScore;
	Texture* mPlayerOne;
	Texture* mPlayerTwo;
	Texture* mHiScore;
	Texture* mHiScore1;
	Texture* mLive1;
	Texture* mLive2;
	Texture* mBackground;
	Texture* mESC;
	Texture* mFood;
    Texture* mWhiteFlower[10];
    Texture* mRedFlower[10];
	Rock * mRock[5];
	Player * mPlayer;
	Pooka * mPooka[4];
	Fygar * mFygar[4];
	Tiles * mTiles[224];
	int CountTiles = 0;
	bool MusicPlaying = false;
	bool mFoodCollected = false;
	bool mFoodCollect;
	bool PSwitch = true;
	bool GameOver;
    int LastOne = -3;
	char LastType = 'N';
	bool FSwitch = true;
	float MusicTimer = 0.0f;
	int mLevel;
	Vector2 TilePos = Vector2(24.0f, 256.0f);
	int TileCurrent = 0;
	struct TileSurround{
		bool Up;
		bool Down;
		bool Left;
		bool Right;
	};
	TileSurround TileSurr;
public:
	PlayScreen();
	~PlayScreen();

	int GetTile(Vector2(position), int w, int h);
	void LevelSet(int level);
	void HarpoonCollision();
	int GetScore();
	void SetHS(int HS);
	void GetTileSurround(int tile);
	void GameEnding();
	void GameStart();
	void EnemyChase(std::string enemy, int enemy1);
	void Update() override;
	void Render() override;
};
#endif