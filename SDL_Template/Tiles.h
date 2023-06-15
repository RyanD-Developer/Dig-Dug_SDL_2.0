#ifndef __TILES_H
#define __TILES_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"
#include "Scoreboard.h"
using namespace SDLFramework;

class Tiles : public PhysEntity {
private:
	Timer* mTimer;
	bool mVisible;
	bool mWasHit;
	Texture* mTile;

public:
	Tiles();
	~Tiles ();

	void Visible(bool visible);
	bool ReturnVisible();

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;

	void Update() override;
	void Render() override;
};
#endif