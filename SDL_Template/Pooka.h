#ifndef __POOKA_H
#define __POOKA_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"
#include "Scoreboard.h"
#include <string>

using namespace SDLFramework;

class Pooka : public PhysEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;

	bool mAnimating;
	bool mWasHit;
	bool mHarpoonHit;
	bool mTileBelow;
	bool mTileAbove;
	bool mTileLeft;
	bool mTileRight;
	bool mTileVis;
	bool HarpoonStriked;
	bool Dead;
	bool InPlace;
	bool Check;
	bool GhostForm = false;
	bool LeaveTunnel = false;
	std::string DirCheck = "Null";

	int  mTile;
	int mAnimFrame;
	int Ghost;
	std::string mFrame = "Right";
	std::string GoingTowards = "None";
	AnimatedGLTexture* mWalking;
	AnimatedGLTexture* mGhostForm;
	Texture* mDeath1;
	Texture* mPDeath1;
	Texture* mPDeath2;
	Texture* mPDeath3;
	Texture* mPDeath4;

	float mTimeSide;
	float mTimeSide1;
	float mTimerGhost;
	float mMoveSpeed;
	bool LastOne;
	bool Done = false;
	Vector2 mMoveBounds;
	Vector2 mMoveBoundsy;
	Vector2 PlayerPos;
	Vector2 TilePos;

	float mWalkingX;

private:
	void HandleMovement();


public:
	Pooka();
	~Pooka();

	// Inherited from PhysEntity
	bool WasHit();
	bool IgnoreCollisions() override;
	void Hit(PhysEntity* other) override;
	void HarpoonHit();

	void HarpoonStrike(bool hs);
	void AnimFrameSet();
	void HandleDirection();
	void SetPlayerPos(Vector2 PPos);
	void SurroundTiles(bool left, bool right, bool up, bool down, bool tile);
	void SetTile(int Tile);
	bool GetHPS();
	bool GetDead();
	void SetDead(bool Dead);
	void SetTilePos(Vector2 TP);
	void Reset();
	void SetDirection(std::string dir);
	int GetFrame();
	bool NeedCheck();
	void SetMS(int Move);
	int GetTile();
	void SetLO(bool LO);
	bool GetDone();
	std::string GetDirC();
	void CheckIfClear(std::string dir);

	void Update() override;
	void Render() override;
};
#endif
