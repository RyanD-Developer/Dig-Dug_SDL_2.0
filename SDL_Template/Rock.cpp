#include "Rock.h"

Rock::Rock() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAnimating = false;
	DoneFalling = false;
	mWasHit = false;
	DeleteRock = false;
	mStoneFree = new GLTexture("Rock.png", 0, 0, 50, 45);
	mStoneFree->Position(Vec2_Zero);
	mStoneFree->Parent(this);
	mDeath13 = new AnimatedGLTexture("RockAnim.png", 0, 0, 50, 45, 3, 2.0f, Animation::Layouts::Horizontal);
	mDeath13->Parent(this);
	mDeath13->Position(Vec2_Zero);
	mMoveBounds = Vector2(27.0f, 652.0f);
	mMoveBoundsy = Vector2(259.0f, 931.0f);

	mVisible = true;
}

Rock::~Rock() {
	delete mStoneFree;
	mStoneFree = nullptr;
	delete mDeath13;
	mDeath13 = nullptr;
}
void Rock::Update() {
	if (!DeleteRock) {
		Vector2 pos = Position(Local);
		if (pos.x < mMoveBounds.x) {
			pos.x = mMoveBounds.x;
		}
		else if (pos.x > mMoveBounds.y) {
			pos.x = mMoveBounds.y;
		}
		if (pos.y < mMoveBoundsy.x) {
			pos.y = mMoveBoundsy.x;
		}
		else if (pos.y > mMoveBoundsy.y) {
			pos.y = mMoveBoundsy.y;
		}

		Position(pos);

		if (mAnimating) {
			mTimeSide += 0.026;
			mWasHit = true;
			mAnimating = mDeath13->IsAnimating();
			mDeath13->Update();
			DoneFalling = false;
		}
		else {
			if (Active()) {
				if (mTileBelow) {
					if (mTimeSide1 < 2) {
						mTimeSide1 += 0.026;
						if (mStoneFree->Rotation(Local) <= 10.0f) {
							if (mStoneFree->Rotation(Local) >= 10.0f) {
								mStoneFree->Rotation(0.0f);
							}
							mStoneFree->Rotate(1.0f);
						}
						else if (mStoneFree->Rotation(Local) >= 10.0f) {
							if (mStoneFree->Rotation(Local) >= 349.0f) {
								mStoneFree->Rotation(0.0f);
							}
							mStoneFree->Rotate(-1.0f);
						}
					}
					if (mTimeSide1 >= 2) {
						Translate(Vec2_Up * 200 * mTimer->DeltaTime(), World);
						Falled = true;
					}
				}
				else if (Falled && pos.y <= (RockPos.y)) {
					Translate(Vec2_Up * 200 * mTimer->DeltaTime(), World);
					DoneFalling = true;
				}
				else if (DoneFalling && pos.y > (RockPos.y)) {
					mDeath13->ResetAnimation();
					mAnimating = true;
				}
			}
		}
		if (mTimeSide >= 3) {
			DeleteRock = true;
			SDL_RemoveTimer(mTimeSide);
		}
	}
}

void Rock::Render() {
	if (!DeleteRock) {
		if (mVisible) {
			if (mAnimating) {
				mDeath13->Render();
			}
			else {
				mStoneFree->Render();
			}
		}
	}
}

void Rock::SetTile(int Tile) {
	mTile = Tile;
}
void Rock::SetRockPos(Vector2 Pos) {
	RockPos = Pos;
}
void Rock::SurroundTiles(bool left, bool right, bool up, bool down) {
	mTileLeft = left;
	mTileRight = right;
	mTileAbove = up;
	mTileBelow = down;
}
bool Rock::ReturnDeleteRock() {
	return DeleteRock;
}
bool Rock::ReturnIsAnimating() {
	return mAnimating;
}
bool Rock::ReturnDoneFalling() {
	return DoneFalling;
}
bool Rock::ReturnFalled() {
	return !Falled;
}
float Rock::ReturnRockPosY() {
	return RockPos.y;
}

void Rock::Reset() {
	mAnimating = false;
	DoneFalling = false;
	mWasHit = false;
	DeleteRock = false;
}