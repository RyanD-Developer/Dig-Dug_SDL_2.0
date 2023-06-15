#ifndef __PLAYER_H
#define __PLAYER_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"
#include "Scoreboard.h"
#include <string>
using namespace SDLFramework;

class Player : public PhysEntity {
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;
	bool mWasHit;
	bool mTileBelow;
	bool mTileAbove;
	bool mTileLeft;
	bool mTileRight;
	bool mHarpoonShot;
	bool HarpoonStriked;
	bool Dead;

	int mScore;
	int mLives;
	int mTile;
	int mHarpoonW;
	int mHarpoonY;

	std::string mFrame = "Right";
	Texture* mShipR;
	Texture* mShipL;
	Texture* mShipU;
	Texture* mShipD;
	Texture* mDeath1;
	Texture* mHarpoon;
	Texture* mHarpoonThrow;
	Texture* mHarpoonHorizontal;
	AnimatedGLTexture* mDeathAnimation;
    
	float mTimeSide;
	float mMoveSpeed;
	Vector2 mMoveBounds;
	Vector2 mMoveBoundsy;
private:
	void HandleMovement();
	void HandleFiring();

public:
	Player();
	~Player();

	void Visible(bool visible);
	bool IsAnimating();

	int GetHarpoonW();
	int Score();
	int Lives();

	bool GetHPS();
	bool GetDead();
	void GameRestart();

	void AddScore(int change);
	void HarpoonStrike(bool hs);
	// Inherited from PhysEntity
	bool IgnoreCollisions() override;
	void Hit(PhysEntity* other) override;
	void SurroundTiles(bool left, bool right, bool up, bool down);
	void SetTile(int Tile);
	void TakeLife();
	void SetDead(bool dead);
	bool WasHit();
	std::string GetFrame();
	void Reset();
	bool GetHPSH();

	void Update() override;
	void Render() override;
};
#endif