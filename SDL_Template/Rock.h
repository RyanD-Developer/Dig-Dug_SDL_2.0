#ifndef __ROCK_H
#define __ROCK_H
#include "AnimatedGLTexture.h"
#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"
#include "Scoreboard.h"

using namespace SDLFramework; 

class Rock : public PhysEntity {
private:
	float mTimeSide;
	float mTimeSide1;
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;
	bool mVisible;
	bool mWasHit = false;
	bool Falled = false;
	Vector2 RockPos;
	Texture* mStoneFree;
	AnimatedGLTexture* mDeath13;
	int mTile;
	bool mTileBelow;
	bool mTileAbove;
	bool mTileLeft;
	bool mTileRight;
	bool mAnimating;
	bool DoneFalling;
	bool DeleteRock;
	Vector2 mMoveBounds;
	Vector2 mMoveBoundsy;
public:
	Rock();
	~Rock();
	bool ReturnIsAnimating();
	bool ReturnDeleteRock();
	bool ReturnDoneFalling();
	float ReturnRockPosY();
	void SetTile(int tile);
	void Reset();
	bool ReturnFalled();
	void SetRockPos(Vector2 pos);
	void SurroundTiles(bool left, bool right, bool up, bool down);
	void Update() override;
	void Render() override;
};
#endif