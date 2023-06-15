#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

void Player::HandleMovement() {
	if (mInput->KeyPressed(SDL_SCANCODE_RIGHT) && !mHarpoonShot) {
		//Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
		Translate(Vector2(48.0f,0.0f), World);
		mFrame = "Right";
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_LEFT) && !mHarpoonShot) {
		//Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
		Translate(Vector2(-48.0f, 0.0f), World);
		mFrame = "Left";
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_UP) && !mHarpoonShot) {
		//Translate(-Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
		Translate(Vector2(0.0f, -48.0f), World);
		mFrame = "Up";
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_DOWN) && !mHarpoonShot) {
		//Translate(Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
		Translate(Vector2(0.0f, 48.0f), World);
		mFrame = "Down";
	}

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
}

void Player::HandleFiring() {
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE) && !mHarpoonShot) {
		mHarpoonShot = true;
		delete mHarpoon;
		mHarpoon = new GLTexture("Harpoon.png", 0, 0, mHarpoonW, 16);
	}else if (mHarpoonShot) {
		delete mHarpoon;
		mHarpoon = new GLTexture("Harpoon.png", 0, 0, mHarpoonW, 16);
		mHarpoon->Parent(this);
		mHarpoon->Position(0.0f, 0.0f);
		if (mFrame == "Right") {
			mHarpoon->Scale(Vector2(-1.0f, 1.0f));
			mHarpoon->Position(45.0f, 0.0f);
			if (mHarpoonW <= 90) {
				mHarpoonW += 5;
			}
		}
		else if (mFrame == "Left") {
			mHarpoon->Position(-45.0f, 0.0f);
			if (mHarpoonW <= 90) {
				mHarpoonW += 5;
			}
		}
		else if (mFrame == "Up") {
			mHarpoon->Scale(Vector2(1.0f, -1.0f));
			mHarpoon->Position(0.0f, -42.0f);
			mHarpoon->Rotate(90.0f);
			if (mHarpoonW <= 90) {
				mHarpoonW += 5;
			}
		}
		else if (mFrame == "Down") {
			mHarpoon->Position(0.0f, 42.0f);
			mHarpoon->Rotate(270.0f);
			if (mHarpoonW <= 90) {
				mHarpoonW += 5;
			}
		}
		if (mHarpoonW >= 90 && !HarpoonStriked) {
			mHarpoonShot = false;
			mHarpoonW = 0;
		}
	}
}

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mWasHit = false;

	mScore = 0;
	mLives = 3;

	mHarpoonW = 0;
	mShipL = new AnimatedGLTexture("PlayerLeft.png", 0, 0, 45, 42, 2, 0.25f, Animation::Layouts::Horizontal);
	mShipR = new AnimatedGLTexture("PlayerRight.png", 0, 0, 45, 42, 2, 0.25f, Animation::Layouts::Horizontal);
	mShipR->Parent(this);
	mShipL->Position(Vec2_Zero);
	mShipL->Parent(this);
	mShipR->Position(Vec2_Zero);
	mHarpoonThrow = new GLTexture("HarpoonThrow.png", 0, 0, 48, 39);
	mHarpoonHorizontal = new AnimatedGLTexture("HarpoonHorizontal.png", 0, 0, 51, 42, 2, 0.25f, Animation::Layouts::Horizontal);
	mHarpoonThrow->Parent(this);
	mHarpoonThrow->Position(0.0f, 0.0f);
	mHarpoonHorizontal->Parent(this);
	mHarpoonHorizontal->Position(0.0f, 0.0f);
	mDeath1 = new GLTexture("Death1.png", 0, 0, 43, 22);
	mDeath1->Parent(this);
	mDeath1->Position(Vector2(0.0f, 10.0f));
	mShipU = new AnimatedGLTexture("PlayerUp.png", 0, 0, 45, 42, 2, 0.25f, Animation::Layouts::Horizontal);
	mShipD = new AnimatedGLTexture("PlayerDown.png", 0, 0, 45, 42, 2, 0.25f, Animation::Layouts::Horizontal);
	mShipD->Parent(this);
	mShipU->Position(Vec2_Zero);
	mShipU->Parent(this);
	mShipD->Position(Vec2_Zero);
	mMoveSpeed = 300.0f;
	mMoveBounds = Vector2(27.0f, 652.0f);
	mMoveBoundsy = Vector2(259.0f, 931.0f);
	mDeathAnimation = new AnimatedGLTexture("DigDugDeathAnimation1.png",0,0,53,50,5,1.0f,Animation::Layouts::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(Animation::WrapModes::Once);

	AddCollider(new BoxCollider(Vector2(35.0f, 30.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	Visible(true);
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	
	delete mShipR;
	mShipR = nullptr;
	delete mShipL;
    mShipL= nullptr;
	delete mShipU;
	mShipU = nullptr;
	delete mShipD;
	mShipD = nullptr;
	delete mDeath1;
	mDeath1 = nullptr;
	delete mHarpoon;
    mHarpoon = nullptr;
	delete mHarpoonThrow;
	mHarpoonThrow = nullptr;
	delete mHarpoonHorizontal;
	mHarpoonHorizontal = nullptr;
	delete mDeathAnimation;
	mDeathAnimation = nullptr;
}

void Player::Visible(bool visible) {
	mVisible = visible;
}

std::string Player::GetFrame() {
	return mFrame;
}

bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mLives;
}

int Player::GetHarpoonW() {
	return mHarpoonW;
}


void Player::AddScore(int change) {
	mScore += change;
}

bool Player::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void Player::Hit(PhysEntity* other) {
	//Death anim for pooka fygar and fire
	mDeathAnimation->ResetAnimation();
	//mAudio->PlaySFX("SFX/PlayerExplosion.wav");
	mWasHit = true;
    WasHit();
}

bool Player::WasHit() {
	HarpoonStriked = false;
    mLives -= 1;
    mDeathAnimation->ResetAnimation();
    mAnimating = true;
    //mAudio->PlaySFX
    return mWasHit;
}


void Player::Update() {
	if (mAnimating) {
        
		if (mWasHit) {
			mDeathAnimation->Update();
		    mAnimating = mDeathAnimation->IsAnimating();
		}
		else if (!mWasHit) {
			mTimeSide += 0.026;
			if (mTimeSide >= 3) {
				mAnimating = false;
				Dead = true;
		    }
		}
	}
	else if (!HarpoonStriked) {
		if (Active()) {
			mWasHit = false;
			HandleMovement();
			HandleFiring();
			mShipR->Update();
			mShipL->Update();
			mShipU->Update();
			mShipD->Update();
		}
	}
	else {
		mHarpoonHorizontal->Update();
	}
}

void Player::Render() {
	
	if (mVisible) {
		if (mAnimating && !HarpoonStriked) {
			if (mWasHit) {
				Dead = true;
                mDeathAnimation->Render();
			}
			else if (!mWasHit) {
			mDeath1->Render();
			}
		}
		else if (!HarpoonStriked){
			if (mHarpoonShot) {
                mHarpoon->Render();
				if (mFrame == "Right") {
					mHarpoonThrow->Scale(Vector2(-1.0f, 1.0f));
					mHarpoonThrow->Render();
					mHarpoonThrow->Rotation(0.0f);
				}
				else if (mFrame == "Left") {
					mHarpoonThrow->Scale(Vector2(1.0f, 1.0f));
					mHarpoonThrow->Render();
					mHarpoonThrow->Rotation(0.0f);
				}
				else if (mFrame == "Up") {
					mHarpoonThrow->Scale(Vector2(1.0f, -1.0f));
					mHarpoonThrow->Render();
					mHarpoonThrow->Rotation(90.0f);
				}
				else if (mFrame == "Down") {
					mHarpoonThrow->Scale(Vector2(1.0f, 1.0f));
					mHarpoonThrow->Render();
					mHarpoonThrow->Rotation(270.0f);
				}
			}
			else {
                if (mFrame == "Right") {
				    mShipR->Render();
			    }
			    else if(mFrame == "Left") {
                    mShipL->Render();
			    }
			    else if (mFrame == "Up") {
			    	mShipU->Render();
			    }
			    else if (mFrame == "Down") {
			     	mShipD->Render();
			    }
			}
			
		}
		else {
			mHarpoon->Render();
			if (mFrame == "Right") {
				mHarpoonHorizontal->Scale(Vector2(-1.0f, 1.0f));
				mHarpoonHorizontal->Render();
				mHarpoonHorizontal->Rotation(0.0f);
			}
			else if (mFrame == "Left") {
				mHarpoonHorizontal->Scale(Vector2(1.0f, 1.0f));
				mHarpoonHorizontal->Render();
				mHarpoonHorizontal->Rotation(0.0f);
			}
			else if (mFrame == "Up") {
				mHarpoonHorizontal->Scale(Vector2(1.0f, -1.0f));
				mHarpoonHorizontal->Render();
				mHarpoonHorizontal->Rotation(90.0f);
			}
			else if (mFrame == "Down") {
				mHarpoonHorizontal->Scale(Vector2(1.0f, 1.0f));
				mHarpoonHorizontal->Render();
				mHarpoonHorizontal->Rotation(270.0f);
			}
		}
	}

	PhysEntity::Render();
}
/* bool CanYouSee = false
for (int i = leftsidetile; i < rightsidetile + 1; i++) {
	if (!Tiles[i]->ReturnVisibility()) {
		CanYouSee = false;
		break;
		break;
	}
	else {
		CanYouSee = true
	}
}
return CanYouSee*/

void Player::SetTile(int Tile) {
	mTile = Tile;
}
void Player::SurroundTiles(bool left, bool right, bool up, bool down) {
	mTileLeft = left;
	mTileRight = right;
	mTileAbove = up;
	mTileBelow = down;
}
void Player::HarpoonStrike(bool hs) {
	HarpoonStriked = hs;
}

bool Player::GetHPS() {
	return HarpoonStriked;
}
void Player::SetDead(bool dead) {
	Dead = dead;
}
bool Player::GetDead() {
	return Dead;
}
void Player::Reset()
{
	mAnimating = false;
	mWasHit = false;
	mHarpoonW = 0;
}
bool Player::GetHPSH() {
	return mHarpoonShot;
}
void Player::TakeLife() {
	mLives -= 1;
}

void Player::GameRestart() {
	Reset();
	mLives = 3;
	mScore = 0;
}