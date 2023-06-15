#ifndef __FYGAR_H
#define __FYGAR_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"
#include "Scoreboard.h"
#include <string>

using namespace SDLFramework;

class Fygar : public PhysEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;
	InputManager* mInput;

	bool mAnimating;
	bool mWasHit;
	bool mHarpoonHit;
	bool mFireBreath;
	bool mTileBelow;
	bool mTileAbove;
	bool mTileLeft;
	bool mTileRight;
	bool mTileVis;
	bool HarpoonStriked;
	bool Dead;
	bool Check;
    bool GhostForm = false;
    bool LeaveTunnel = false;
	std::string DirCheck = "Null";
	std::string Previous = "Null";

	int  mTile;
	int mAnimFrame;
	int Ghost;
	int FireTimer;
	std::string mFrame = "Right";
	std::string GoingTowards = "None";
	AnimatedGLTexture* mWalking;
	AnimatedGLTexture* mGhostForm;
	Texture* mDeath2;
	Texture* mFDeath1;
	Texture* mFDeath2;
	Texture* mFDeath3;
	Texture* mFDeath4;
	Texture* mPreFire;
	Texture* mFire;
	Texture* mFire1;
	Texture* mFire2;
	bool InPlace;
	bool LastOne;
	bool Done = false;
	float mTimeSide;
	float mAnimFrame2;
	float mTimeSide1;
    float mFireTimer;
	float mTimerGhost;
	float mMoveSpeed;
	Vector2 mMoveBounds;
	Vector2 mMoveBoundsy;
	Vector2 PlayerPos;
	Vector2 TilePos;
	float mWalkingX;

private:
	void HandleMovement();


public:
	Fygar();
	~Fygar();

	// Inherited from PhysEntity
	bool WasHit();
	bool IgnoreCollisions() override;
	void HandleDirection();
	void SetPlayerPos(Vector2 PPos);
	void Hit(PhysEntity* other) override;
	void HarpoonHit();
	void HarpoonStrike(bool hs);
	bool FireBreath();
	void AnimFrameSet();
	void SurroundTiles(bool left, bool right, bool up, bool down, bool tile);
	void SetTile(int Tile);
	void SetTilePos(Vector2 TP);
	bool GetHPS();
	bool GetDead();
	void Reset();
	void SetDirection(std::string dir);
	int GetFrame();
	void SetDead(bool Dead2);
	void Update() override;
	void SetMS(int Move);
	void SetLO(bool LO);
	bool GetDone();
	void Render() override;
	bool NeedCheck();
	int GetTile();
	std::string GetDirC();
	void CheckIfClear(std::string dir);
};
#endif

