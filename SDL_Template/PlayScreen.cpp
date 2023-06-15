#include "PlayScreen.h"



PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mBackground = new GLTexture("Level1.png", 12, 8, 563, 653);
	mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 80.0f);
	mPlayerOne = new GLTexture("1UP", "emulogic.ttf", 32, { 200, 0, 0 });
	mPlayerTwo = new GLTexture("2UP", "emulogic.ttf", 32, { 200, 0, 0 });
	mHiScore = new GLTexture("HI-", "emulogic.ttf", 32, { 200, 0, 0 });
	mHiScore1 = new GLTexture("SCORE", "emulogic.ttf", 32, { 200, 0, 0 });
	mESC = new GLTexture("Hit Esc. To Retry", "emulogic.ttf", 32, { 230, 230, 230 });
	mESC->Parent(this);
	mESC->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	mPlayerOneScore = new Scoreboard();
	mPlayerTwoScore = new Scoreboard();
	mTopScore = new Scoreboard();
	MusicPlaying = false;
	mBackground->Scale(Vector2(1.1936058f, 1.2496171516f));
	mPlayerOne->Parent(this);
	mPlayerTwo->Parent(this);
	mHiScore->Parent(this);
	mPlayerOneScore->Parent(this);
	PookaAmount = 1;
	mPlayerTwoScore->Parent(this);
	mTopScore->Parent(this);
	for (int i = 0; i < 224; i += 1) {
		mTiles[i] = new Tiles();
		mTiles[i]->Position(Vector2(TilePos));
		TilePos.x = TilePos.x + 48.0f;
		if (TilePos.x ==696.0f) {
			TilePos.x = 24.0f;
			TilePos.y += 48.0f;
		}
		mTiles[i]->Parent(this);
		mTiles[i]->Active(true);
	}
	GameOver = false;
	mFoodCollect = false;
	mFoodCollected = false;
	mFood = new GLTexture("Stuff.png", 3, 147, 42, 42);
	mFood->Position(Vector2(500000.0f, 500000.0f));
	mFood->Scale(Vector2(3.0, 3.0));
	for (int i = 0; i < 10; i++) {
	mWhiteFlower[i] = new GLTexture("Stuff.png",120, 8, 16, 16);
	mWhiteFlower[i]->Position(Vector2( 500000, 500000));
	mWhiteFlower[i]->Scale(Vector2(3.0, 3.0));
	}
	for (int i = 0; i < 10; i++) {
		mRedFlower[i] = new GLTexture("Stuff.png",94, 0, 16, 24);
		mRedFlower[i]->Position(Vector2( 500000, 500000));
		mRedFlower[i]->Scale(Vector2(3.0, 3.0 ));
	}
	mPlayerOne->Position(Vector2(725.0f, 544.0f));
	mPlayerTwo->Position(Vector2(725.0f, 700.0f));
	mHiScore->Position(Vector2(725.0f, 400.0f));
	mHiScore1->Position(Vector2(757.0f, 440.0f));
	mPlayerOneScore->Position(Vector2(865.0f, 584.0f)); 
	mPlayerTwoScore->Position(Vector2(865.0f, 740.0f));
	mTopScore->Position(Vector2(865.0f, 480.0f));
	mTopScore->Score(10000);
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(315.0f, 548.0f);
	mPlayer->Active(true);
	for (int i = 0; i < 5; i++) {
		delete mRock[i];
		mRock[i] = new Rock();
		mRock[i]->Parent(this);
		mRock[i]->Position(Vector2(5000.0f, 5000.0f));
		mRock[i]->Active(true);
	}
	for (int i = 0; i < 4; i++) {
		mPooka[i] = new Pooka();
		mPooka[i]->SetDead(true);
		mPooka[i]->Parent(this);
		mPooka[i]->Active(true);
		mPooka[i]->Position(Vector2(5000.0f, 5000.0f));
		mPooka[i]->SetDirection("Left");
	}
	for (int i = 0; i < 4; i++) {
		mFygar[i] = new Fygar();
		mFygar[i]->SetDead(true);
		mFygar[i]->Parent(this);
		mFygar[i]->Active(true);
		mFygar[i]->Position(Vector2(5000.0f, 5000.0f));
		mFygar[i]->SetDirection("Left");
	}
	mLive1 = new GLTexture("ExtraLife.png", 0, 0, 42, 42);
	mLive2 = new GLTexture("ExtraLife.png", 0, 0, 42, 42);
	mLive1->Position(Vector2(703.0f, 800.0f));
	mLive2->Position(Vector2(753.0f, 800.0f));
	mBackground->Position(336.0f, Graphics::SCREEN_HEIGHT * 0.5f);
	for (int i = 0; i < 14; i++) {
		mTiles[i]->Visible(true);
	}
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;
	delete mTopBar;
	mTopBar = nullptr;
	delete mPlayerOne;
	mPlayerOne = nullptr;
	delete mPlayerTwo;
	mPlayerTwo = nullptr;
	delete mHiScore;
	mHiScore = nullptr;
	delete mHiScore1;
	mHiScore1 = nullptr;
	delete mPlayerOneScore;
	mPlayerOneScore = nullptr;
	delete mPlayerTwoScore;
	mPlayerTwoScore = nullptr;
	delete mTopScore;
	mTopScore = nullptr;
	delete mESC;
	mESC = nullptr;
	delete mFood;
	mFood = nullptr;
	for (int i = 0; i < 10; i++) {
		mWhiteFlower[i] = nullptr;
		delete mWhiteFlower[i];
	}
	for (int i = 0; i < 10; i++) {
		mRedFlower[i] = nullptr;
		delete mRedFlower[i];
	}
	delete mBackground;
	mBackground = nullptr;
	delete mLive1;
	mLive1 = nullptr;
	delete mLive2;
	mLive2 = nullptr;
	delete mPlayer;
	mPlayer = nullptr;
	for (int i = 0; i < 4; i++) {
		delete mPooka[i];
		mPooka[i] = nullptr;
	}
	for (int i = 0; i < 4; i++) {
		delete mFygar[i];
		mFygar[i] = nullptr;
	}
	for (int i = 0; i < 5; i++) {
		delete mRock[i];
		mRock[i] = nullptr;
	}
	for (int i = 0; i < 224; i++) {
		delete mTiles[i];
		mTiles[i] = nullptr;
	}
}

void PlayScreen::Update() {
	if (mPlayer->Lives() > 0) {
		mPlayerOneScore->Score(mPlayer->Score());
		if (mPlayer->Score() > 10000) {
			mTopScore->Score(mPlayer->Score());
		}
		if (!MusicPlaying && MusicTimer > 8.5f) {
			PSwitch = false;
			FSwitch = false;
			mAudio->PlayMusic("Walking.mp3", 100);
			mAudio->ResumeMusic();
			MusicPlaying = true;
		}
		else {
			MusicTimer += 0.026;
		}
		for (int i = 0; i < 10; i++) {
			if (i > (WFamount - 1)) {
				mWhiteFlower[i]->Position(50000.0f, 50000.0f);
			}
		}
		for (int i = 0; i < 10; i++) {
			if (i > (RFamount - 1)) {
				mRedFlower[i]->Position(50000.0f, 50000.0f);
			}
		}
		for (int i = 0; i < 224; i++) {
			if ((mPlayer->Position().x + 42) >= mTiles[i]->Position().x &&
				mPlayer->Position().x <= (mTiles[i]->Position().x + 48) &&
				(mPlayer->Position().y + 42) >= mTiles[i]->Position().y &&
				mPlayer->Position().y <= (mTiles[i]->Position().y + 48) &&
				!mPlayer->IsAnimating()) {
				mTiles[i]->Visible(true);
			}
		}
		for (int i = 0; i < PookaAmount; i++) {
			if (mPooka[i]->GetDead()) {
				mPooka[i]->Position(Vector2(5000.0f, 5000.0f));
			}
			else {
				mPooka[i]->SetPlayerPos(mPlayer->Position());
				GetTile(mPooka[i]->Position(), 45, 42);
				if (TileCurrent > 0) {
					mPooka[i]->SetTile(TileCurrent);
					mPooka[i]->SetTilePos(mTiles[TileCurrent]->Position());
					GetTileSurround(GetTile(mPooka[i]->Position(), 42, 42));
					mPooka[i]->SurroundTiles(TileSurr.Left, TileSurr.Right, TileSurr.Up, TileSurr.Down, mTiles[TileCurrent]->ReturnVisible());
				}
				mPooka[i]->Update();
				if (mPooka[i]->NeedCheck()) {
					EnemyChase("Pooka", i);
				}
				GetTile(mPlayer->Position(), 45, 42);
				if (TileCurrent > 0) {
					mPlayer->SetTile(TileCurrent);
					GetTileSurround(GetTile(mPlayer->Position(), 42, 42));
					mPlayer->SurroundTiles(TileSurr.Left, TileSurr.Right, TileSurr.Up, TileSurr.Down);
				}
			}
		}

		for (int i = 0; i < FygarAmount; i++) {
			if (mFygar[i]->GetDead()) {
				mFygar[i]->Position(Vector2(5000.0f, 5000.0f));
			}
			else {
				mFygar[i]->SetPlayerPos(mPlayer->Position());
				GetTile(mFygar[i]->Position(), 45, 42);
				if (TileCurrent > 0) {
					mFygar[i]->SetTile(TileCurrent);
					mFygar[i]->SetTilePos(mTiles[TileCurrent]->Position());
					GetTileSurround(GetTile(mFygar[i]->Position(), 42, 42));
					mFygar[i]->SurroundTiles(TileSurr.Left, TileSurr.Right, TileSurr.Up, TileSurr.Down, mTiles[TileCurrent]->ReturnVisible());
				}
				mFygar[i]->Update();
				if (mFygar[i]->NeedCheck()) {
					EnemyChase("Fygar", i);
				}
			}
		}
		mPlayer->Update();
		for (int i = 0; i < RockAmount; i++) {
			GetTile(mRock[i]->Position(), 50, 45);
			if (TileCurrent > 0) {
				mRock[i]->SetTile(TileCurrent);
				mRock[i]->SetRockPos(mTiles[TileCurrent]->Position());
				GetTileSurround(GetTile(mRock[i]->Position(), 42, 42));
				mRock[i]->SurroundTiles(TileSurr.Left, TileSurr.Right, TileSurr.Up, TileSurr.Down);
			}
			mRock[i]->Update();
			if ((mPlayer->Position().x + 42) >= mRock[i]->Position().x &&
				mPlayer->Position().x <= (mRock[i]->Position().x + 48) &&
				(mPlayer->Position().y + 42) >= mRock[i]->Position().y &&
				mPlayer->Position().y <= (mRock[i]->Position().y + 45) &&
				!mRock[i]->ReturnDeleteRock() &&
				!mRock[i]->ReturnIsAnimating() &&
				!mPlayer->IgnoreCollisions() &&
				mRock[i]->Position().y <= mRock[i]->ReturnRockPosY()) {
				mPlayer->WasHit();
			}
			if ((mPlayer->Position().x + 42) >= mRock[i]->Position().x &&
				mPlayer->Position().x <= (mRock[i]->Position().x + 48) &&
				(mPlayer->Position().y + 42) >= mRock[i]->Position().y &&
				mPlayer->Position().y <= (mRock[i]->Position().y + 45) &&
				!mRock[i]->ReturnDeleteRock() &&
				mRock[i]->Position().y <= mRock[i]->ReturnRockPosY()) {
				mPlayer->Position(Vector2(mRock[i]->Position().x, mRock[i]->Position().y));
			}
			for (int x = 0; x < PookaAmount; x++) {
				if (mPooka[x]->GetDead()) {

				}
				else {
					if ((mPooka[x]->Position().x + 38) >= mRock[i]->Position().x &&
						mPooka[x]->Position().x <= (mRock[i]->Position().x + 48) &&
						(mPooka[x]->Position().y + 35) >= mRock[i]->Position().y &&
						mPooka[x]->Position().y <= (mRock[i]->Position().y + 45) &&
						!mRock[i]->ReturnDeleteRock() &&
						!mRock[i]->ReturnIsAnimating() &&
						!mPooka[x]->IgnoreCollisions() &&
						mRock[i]->Position().y <= mRock[i]->ReturnRockPosY()) {
						mPooka[x]->WasHit();
						mPlayer->AddScore(1000);
					}
					if ((mPooka[x]->Position().x + 38) >= mRock[i]->Position().x &&
						mPooka[x]->Position().x <= (mRock[i]->Position().x + 48) &&
						(mPooka[x]->Position().y + 35) >= mRock[i]->Position().y &&
						mPooka[x]->Position().y <= (mRock[i]->Position().y + 45) &&
						!mRock[i]->ReturnDeleteRock() &&
						mRock[i]->Position().y <= mRock[i]->ReturnRockPosY()) {
						mPooka[x]->Position(Vector2(mRock[i]->Position().x, mRock[i]->Position().y));
					}
				}
			}
			for (int y = 0; y < FygarAmount; y++) {
				if (mFygar[y]->GetDead()) {

				}
				else {
					if ((mFygar[y]->Position().x + 42) >= mRock[i]->Position().x &&
						mFygar[y]->Position().x <= (mRock[i]->Position().x + 48) &&
						(mFygar[y]->Position().y + 42) >= mRock[i]->Position().y &&
						mFygar[y]->Position().y <= (mRock[i]->Position().y + 45) &&
						!mRock[i]->ReturnDeleteRock() &&
						!mRock[i]->ReturnIsAnimating() &&
						!mFygar[y]->IgnoreCollisions() &&
						mRock[i]->Position().y <= mRock[i]->ReturnRockPosY()) {
						mFygar[y]->WasHit();
						mPlayer->AddScore(1000);
					}
					if ((mFygar[y]->Position().x + 42) >= mRock[i]->Position().x &&
						mFygar[y]->Position().x <= (mRock[i]->Position().x + 48) &&
						(mFygar[y]->Position().y + 42) >= mRock[i]->Position().y &&
						mFygar[y]->Position().y <= (mRock[i]->Position().y + 45) &&
						!mRock[i]->ReturnDeleteRock() &&
						mRock[i]->Position().y <= mRock[i]->ReturnRockPosY()) {
						mFygar[y]->Position(Vector2(mRock[i]->Position()));
					}
				}
			}
		}
		HarpoonCollision();
		if (mPlayer->GetDead() && !mPlayer->IsAnimating()) {
			PSwitch = false;
			FSwitch = false;
			LevelSet(mLevel);
			mPlayer->HarpoonStrike(false);
			mPlayer->Reset();
			for (int i = 0; i < PookaAmount; i++) {
				mPooka[i]->SetDead(mPooka[i]->GetDead());
			}
			for (int i = 0; i < FygarAmount; i++) {
				mFygar[i]->SetDead(mFygar[i]->GetDead());
			}
		}
		int numberOfRocksBroken = 0;
		for (int i = 0; i < RockAmount; i++) {
			if (i == 0) {
				numberOfRocksBroken = 0;
			}
			if (mRock[i]->ReturnDeleteRock()) {
				numberOfRocksBroken += 1;
			}
			if (mFoodCollect == false && numberOfRocksBroken >= 2 && mFoodCollected == false) {
				mFoodCollect = true;
				mFood->Position(Vector2(315.0f, 547.0f));
			}
		}
		/*
		Problem is here
		Only works if its the first in the array
		*/
		int numberdead = 0;
		for (int i = 0; i < PookaAmount; i++) {
			if (i == 0) {
				numberdead = 0;
			}
			if (mPooka[i]->GetDead()) {
				numberdead += 1;
			}
			if (numberdead == (PookaAmount - 1) && FSwitch) {
				mPooka[i]->SetLO(true);
			}
			if (numberdead == (PookaAmount)) {
				PSwitch = true;
			}
			else {
				PSwitch = false;
			}
			if (mPooka[i]->GetDone()) {
				mPlayer->TakeLife();
				PSwitch = true;
			}
		}
		numberdead = 0;
		for (int i = 0; i < FygarAmount; i++) {
			if (mFygar[i]->GetDead()) {
				numberdead += 1;
			}
			if (numberdead == (FygarAmount - 1) && PSwitch) {
				mFygar[i]->SetLO(true);
			}
			else {
				std::cout << numberdead << " , " << FygarAmount - 1 << " , " << PSwitch << std::endl;
			}
			if (numberdead == (FygarAmount)) {
				FSwitch = true;
			}
			else {
				FSwitch = false;
			}
			if (mFygar[i]->GetDone()) {
				mPlayer->TakeLife();
				FSwitch = true;
			}
		}
		if (PSwitch && FSwitch) {
			mAudio->PauseMusic();
			MusicPlaying = false;
			MusicTimer = 0;
			mLevel += 1;
			for (int i = 14; i < 224; i++) {
				mTiles[i]->Visible(false);
			}
			LevelSet(mLevel);
			PSwitch = false;
			FSwitch = false;
		}
		if ((mPlayer->Position().x + 42) >= mFood->Position().x &&
			mPlayer->Position().x <= (mFood->Position().x + 16) &&
			(mPlayer->Position().y + 42) >= mFood->Position().y &&
			mPlayer->Position().y <= (mFood->Position().y + 16) &&
			!mPlayer->IsAnimating() &&
			mFoodCollect &&
			!mFoodCollected) {
			mPlayer->AddScore(FoodScore);
			mFoodCollect = false;
			mFoodCollected = true;
			mAudio->PlaySFX("BonusSound.mp3");
		}
	}
	else {
		GameEnding();
	}
}

void PlayScreen::Render() {
	if (mPlayer->Lives() > 0) {
		mBackground->Render();
		mPlayerOne->Render();
		mPlayerTwo->Render();
		mHiScore->Render();
		mHiScore1->Render();
		mPlayerOneScore->Render();
		mPlayerTwoScore->Render();
		mTopScore->Render();
		for (int i = 0; i < 224; i++) {
			mTiles[i]->Render();
		}
		for (int i = 0; i < RFamount; i++) {
			mRedFlower[i]->Render();

		}
		for (int i = 0; i < WFamount; i++) {
			mWhiteFlower[i]->Render();
		}
		if (mFoodCollect) {
			mFood->Render();
		}
		for (int i = 0; i < RockAmount; i++) {
			mRock[i]->Render();
		}
		for (int i = 0; i < PookaAmount; i++) {
			if (mPooka[i]->GetDead()) {

			}
			else {
				mPooka[i]->Render();
			}
		}
		for (int i = 0; i < FygarAmount; i++) {
			if (mFygar[i]->GetDead()) {

			}
			else {
				mFygar[i]->Render();
			}
		}
		mPlayer->Render();
		if (mPlayer->Lives() == 3) {
			mLive1->Render();
			mLive2->Render();
		}
		else if (mPlayer->Lives() == 2) {
			mLive1->Render();
		}
		else { ; }
	} else if (GameOver) {
		mESC->Render();
	}
}

int PlayScreen::GetTile(Vector2(position), int w, int h) {
	TileCurrent = 0;
	for (int i = 0; i < 224; i++) {
		if ((position.x + 42) >= mTiles[i]->Position().x &&
			position.x <= (mTiles[i]->Position().x + 48) &&
			(position.y + 42) >= mTiles[i]->Position().y &&
			position.y <= (mTiles[i]->Position().y + 48)) {
			TileCurrent = i;
		}
	}
	return TileCurrent;
}

void PlayScreen::GetTileSurround(int tile) {
	if (mTiles[tile - 1]->ReturnVisible()) {
		TileSurr.Left = true;
	}
	else {
		TileSurr.Left = false;
	}
	if (mTiles[tile + 1]->ReturnVisible()) {
		TileSurr.Right = true;
	}
	else {
		TileSurr.Right = false;
	}
	if (mTiles[tile - 14]->ReturnVisible()) {
		TileSurr.Up = true;
	}
	else {
		TileSurr.Up = false;
	}
	if (mTiles[tile + 14]->ReturnVisible()) {
		TileSurr.Down = true;
	}
	else {
		TileSurr.Down = false;
	}
}

void PlayScreen::HarpoonCollision() {
	if (mPlayer->GetHPSH()) {
		for (int i = 0; i < PookaAmount; i++) {
			if (mPooka[i]->GetDead() && mPooka[i]->GetHPS()) {
				mPlayer->HarpoonStrike(false);
				mPooka[i]->HarpoonStrike(false);
				mPlayer->AddScore(350);
			} 
			if (mPlayer->GetFrame() == "Right") {
				if ((mPlayer->Position().x + (mPlayer->GetHarpoonW() + 16)) >= mPooka[i]->Position().x &&
					(mPlayer->Position().x + mPlayer->GetHarpoonW()) <= (mPooka[i]->Position().x + 44) &&
					(mPlayer->Position().y + 42) >= mPooka[i]->Position().y &&
					(mPlayer->Position().y) <= (mPooka[i]->Position().y + 42) &&
					!mPlayer->IsAnimating()) {
					mPooka[i]->SetDirection("None");
					if (mPlayer->GetHPS() && mPooka[i]->GetHPS()) {
						if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
							mPooka[i]->AnimFrameSet();
							mAudio->PlaySFX("Pumping.mp3");
						}
					}
					else if (mPlayer->GetHPS() && !mPooka[i]->GetHPS()) {
						break;
						break;
					}
					else {
						mPlayer->HarpoonStrike(true);
						mPooka[i]->HarpoonStrike(true);
						mPooka[i]->HarpoonHit();
						if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
							mPooka[i]->AnimFrameSet();
						}
					}

				}
			}
			else if (mPlayer->GetFrame() == "Left") {
				if ((mPlayer->Position().x - (mPlayer->GetHarpoonW())) >= mPooka[i]->Position().x &&
					(mPlayer->Position().x - (mPlayer->GetHarpoonW() + 16)) <= (mPooka[i]->Position().x + 44) &&
					(mPlayer->Position().y + 42) >= mPooka[i]->Position().y &&
					(mPlayer->Position().y) <= (mPooka[i]->Position().y + 42) &&
					!mPlayer->IsAnimating()) {
					mPooka[i]->SetDirection("None");
					if (mPlayer->GetHPS() && mPooka[i]->GetHPS()) {
						if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
							mPooka[i]->AnimFrameSet();
							mAudio->PlaySFX("Pumping.mp3");
						}
					}
					else if (mPlayer->GetHPS() && !mPooka[i]->GetHPS()) {
						break;
						break;
					}
					else {
						mPlayer->HarpoonStrike(true);
						mPooka[i]->HarpoonStrike(true);
						mPooka[i]->HarpoonHit();
						if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
							mPooka[i]->AnimFrameSet();
						}

					}

				}
			}
			else if (mPlayer->GetFrame() == "Up") {
				if ((mPlayer->Position().x + 42) >= mPooka[i]->Position().x &&
					(mPlayer->Position().x) <= (mPooka[i]->Position().x + 44) &&
					(mPlayer->Position().y - (mPlayer->GetHarpoonW() + 20)) >= mPooka[i]->Position().y &&
					(mPlayer->Position().y - mPlayer->GetHarpoonW()) <= (mPooka[i]->Position().y + 44) &&
					!mPlayer->IsAnimating()) {
					mPooka[i]->SetDirection("None");
					if (mPlayer->GetHPS() && mPooka[i]->GetHPS()) {
						if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
							mPooka[i]->AnimFrameSet();
							mAudio->PlaySFX("Pumping.mp3");
						}
					}
					else if (mPlayer->GetHPS() && !mPooka[i]->GetHPS()) {
						break;
						break;
					}
					else {
						mPlayer->HarpoonStrike(true);
						mPooka[i]->HarpoonStrike(true);
						mPooka[i]->HarpoonHit();
						if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
							mPooka[i]->AnimFrameSet();
						}
					}
				}
			}
			else if (mPlayer->GetFrame() == "Down") {
				if ((mPlayer->Position().x + 42) >= mPooka[i]->Position().x &&
					(mPlayer->Position().x) <= (mPooka[i]->Position().x + 42) &&
					(mPlayer->Position().y + (mPlayer->GetHarpoonW() + 20)) >= mPooka[i]->Position().y &&
					(mPlayer->Position().y + mPlayer->GetHarpoonW()) <= (mPooka[i]->Position().y + 42) &&
					!mPlayer->IsAnimating()) {
					mPooka[i]->SetDirection("None");
					if (mPlayer->GetHPS() && mPooka[i]->GetHPS()) {
						if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
							mPooka[i]->AnimFrameSet();
							mAudio->PlaySFX("Pumping.mp3");
						}
					}
					else if (mPlayer->GetHPS() && !mPooka[i]->GetHPS()) {
						break;
						break;
					}
					else {
						mPlayer->HarpoonStrike(true);
						mPooka[i]->HarpoonStrike(true);
						mPooka[i]->HarpoonHit();
						if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
							mPooka[i]->AnimFrameSet();
						}
					}

				}
			}
		}
		for (int i = 0; i < FygarAmount; i++) {
			if (mFygar[i]->GetDead() && mFygar[i]->GetHPS()) {
				mPlayer->HarpoonStrike(false);
				mFygar[i]->HarpoonStrike(false);
				mPlayer->AddScore(350);
				if (mPlayer->Position().y - 2 <= std::roundf(mFygar[i]->Position().y) && std::roundf(mFygar[i]->Position().y) <= mPlayer->Position().y + 2) {
					mPlayer->AddScore(700);
				}
			}
			if (mPlayer->GetFrame() == "Right") {
				if ((mPlayer->Position().x + (mPlayer->GetHarpoonW())) >= mFygar[i]->Position().x &&
					mPlayer->Position().x <= (mFygar[i]->Position().x + 42) &&
					(mPlayer->Position().y + 16) >= mFygar[i]->Position().y &&
					mPlayer->Position().y <= (mFygar[i]->Position().y + 42) &&
					!mPlayer->IsAnimating()) {
					mFygar[i]->SetDirection("None");
					if (mPlayer->GetHPS() && mFygar[i]->GetHPS()) {
						if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
							mFygar[i]->AnimFrameSet();
							mAudio->PlaySFX("Pumping.mp3");
						}
					}
					else if (mPlayer->GetHPS()) {

					}
					else {
						mPlayer->HarpoonStrike(true);
						mFygar[i]->HarpoonStrike(true);
						mFygar[i]->HarpoonHit();
						if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
							mFygar[i]->AnimFrameSet();
						}
					}

				}
			}
			else if (mPlayer->GetFrame() == "Left") {
				if ((mPlayer->Position().x) >= mFygar[i]->Position().x &&
					(mPlayer->Position().x - mPlayer->GetHarpoonW()) <= (mFygar[i]->Position().x + 42) &&
					(mPlayer->Position().y + 16) >= mFygar[i]->Position().y &&
					mPlayer->Position().y <= (mFygar[i]->Position().y + 42) &&
					!mPlayer->IsAnimating()) {
					mFygar[i]->SetDirection("None");
					if (mPlayer->GetHPS() && mFygar[i]->GetHPS()) {
						if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
							mFygar[i]->AnimFrameSet();
							mAudio->PlaySFX("Pumping.mp3");
						}
					}
					else if (mPlayer->GetHPS()) {

					}
					else {
						mPlayer->HarpoonStrike(true);
						mFygar[i]->HarpoonStrike(true);
						mFygar[i]->HarpoonHit();
						if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
							mFygar[i]->AnimFrameSet();
						}
					}

				}
			}
			else if (mPlayer->GetFrame() == "Up") {
				if ((mPlayer->Position().x + 30) >= mFygar[i]->Position().x &&
					(mPlayer->Position().x + 10) <= (mFygar[i]->Position().x + 42) &&
					(mPlayer->Position().y - mPlayer->GetHarpoonW()) >= mFygar[i]->Position().y &&
					(mPlayer->Position().y - (mPlayer->GetHarpoonW() + 16)) <= (mFygar[i]->Position().y + 42) &&
					!mPlayer->IsAnimating()) {
					mFygar[i]->SetDirection("None");
					if (mPlayer->GetHPS() && mFygar[i]->GetHPS()) {
						if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
							mFygar[i]->AnimFrameSet();
							mAudio->PlaySFX("Pumping.mp3");
						}
					}
					else if (mPlayer->GetHPS()) {

					}
					else {
						mPlayer->HarpoonStrike(true);
						mFygar[i]->HarpoonStrike(true);
						mFygar[i]->HarpoonHit();
						if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
							mFygar[i]->AnimFrameSet();
						}
					}
				}
			}
			else if (mPlayer->GetFrame() == "Down") {
				if ((mPlayer->Position().x + 30) >= mFygar[i]->Position().x &&
					(mPlayer->Position().x + 10) <= (mFygar[i]->Position().x + 42) &&
					(mPlayer->Position().y + mPlayer->GetHarpoonW()) >= mFygar[i]->Position().y &&
					(mPlayer->Position().y + (mPlayer->GetHarpoonW() + 16)) <= (mFygar[i]->Position().y + 42) &&
					!mPlayer->IsAnimating()) {
					mFygar[i]->SetDirection("None");
					if (mPlayer->GetHPS() && mFygar[i]->GetHPS()) {
						if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
							mFygar[i]->AnimFrameSet();
							mAudio->PlaySFX("Pumping.mp3");
						}
					}
					else if (mPlayer->GetHPS()) {

					}
					else {
						mPlayer->HarpoonStrike(true);
						mFygar[i]->HarpoonStrike(true);
						mFygar[i]->HarpoonHit();
						if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
							mFygar[i]->AnimFrameSet();
						}
					}

				}
			}
		}
	}
	else {
	}
}
void PlayScreen::EnemyChase(std::string enemy, int enemy1) {
	if (enemy == "Pooka") {
		if (mPooka[enemy1]->GetDirC() == "R") {
			for (int i = mPooka[enemy1]->GetTile(); i < GetTile(mPlayer->Position(), 45, 42); i++) {
				if (!mTiles[i]->ReturnVisible()) {
					mPooka[enemy1]->CheckIfClear("Null");
					break;
					break;
				}
				if (i == GetTile(mPlayer->Position(), 45, 42) - 1) {
					mPooka[enemy1]->SetDirection("Right");
				}
			}
		} else if (mPooka[enemy1]->GetDirC() == "L") {
			for (int i = mPooka[enemy1]->GetTile(); i > GetTile(mPlayer->Position(), 45, 42); i -=1 ) {
				if (!mTiles[i]->ReturnVisible()) {
					mPooka[enemy1]->CheckIfClear("Null");
					break;
					break;
				}
				if (i == GetTile(mPlayer->Position(), 45, 42) + 1) {
					mPooka[enemy1]->SetDirection("Left");
				}
			}
		}
		else if (mPooka[enemy1]->GetDirC() == "U") {
			for (int i = mPooka[enemy1]->GetTile(); i > GetTile(mPlayer->Position(), 45, 42); i -= 14) {
				if (!mTiles[i]->ReturnVisible()) {
					mPooka[enemy1]->CheckIfClear("Null");
					break;
					break;
				}
				if (i == GetTile(mPlayer->Position(), 45, 42) + 14) {
					mPooka[enemy1]->SetDirection("Up");
				}
			}
		}
		else if (mPooka[enemy1]->GetDirC() == "D") {
			for (int i = mPooka[enemy1]->GetTile(); i < GetTile(mPlayer->Position(), 45, 42); i += 14) {
				if (!mTiles[i]->ReturnVisible()) {
					mPooka[enemy1]->CheckIfClear("Null");
					break;
					break;
				}
				if (i == GetTile(mPlayer->Position(), 45, 42) - 14) {
					mPooka[enemy1]->SetDirection("Down");
				}
			}
		}
	}
	else if (enemy == "Fygar") {
		if (mFygar[enemy1]->GetDirC() == "R") {
			for (int i = mFygar[enemy1]->GetTile(); i < GetTile(mPlayer->Position(), 45, 42); i++) {
				if (!mTiles[i]->ReturnVisible()) {
					mFygar[enemy1]->CheckIfClear("Null");
					break;
					break;
				}
				if (i == GetTile(mPlayer->Position(), 45, 42) - 1) {
					mFygar[enemy1]->SetDirection("Right");
				}
			}
		}
		else if (mFygar[enemy1]->GetDirC() == "L") {
			for (int i = mFygar[enemy1]->GetTile(); i > GetTile(mPlayer->Position(), 45, 42); i -= 1) {
				if (!mTiles[i]->ReturnVisible()) {
					mFygar[enemy1]->CheckIfClear("Null");
					break;
					break;
				}
				if (i == GetTile(mPlayer->Position(), 45, 42) + 1) {
					mFygar[enemy1]->SetDirection("Left");
				}
			}
		}
		else if (mFygar[enemy1]->GetDirC() == "U") {
			for (int i = mFygar[enemy1]->GetTile(); i > GetTile(mPlayer->Position(), 45, 42); i -= 14) {
				if (!mTiles[i]->ReturnVisible()) {
					mFygar[enemy1]->CheckIfClear("Null");
					break;
					break;
				}
				if (i == GetTile(mPlayer->Position(), 45, 42) + 14) {
					mFygar[enemy1]->SetDirection("Up");
				}
			}
		}
		else if (mFygar[enemy1]->GetDirC() == "D") {
			for (int i = mFygar[enemy1]->GetTile(); i < GetTile(mPlayer->Position(), 45, 42); i += 14) {
				if (!mTiles[i]->ReturnVisible()) {
					mFygar[enemy1]->CheckIfClear("Null");
					break;
					break;
				}
				if (i == GetTile(mPlayer->Position(), 45, 42) - 14) {
					mFygar[enemy1]->SetDirection("Down");
				}
			}
		}
	}
}
int PlayScreen::GetScore() {
	if (mPlayer->Score() < 10000) {
		return 10000;
	}
	else {
		return mPlayer->Score();
	}
}
void PlayScreen::SetHS(int HS) {
	mTopScore->Score(HS);
}
void PlayScreen::GameEnding() {
	for (int i = 0; i < FygarAmount; i++) {
		mFygar[i]->SetDead(true);
	}
	for (int i = 0; i < PookaAmount; i++) {
		mPooka[i]->SetDead(true);
	}
	mPlayer->Reset();
	mPlayer->HarpoonStrike(false);
	GameOver = true;
}
void PlayScreen::GameStart() {
	for (int i = 0; i < FygarAmount; i++) {
		mFygar[i]->SetDead(false);
	}
	for (int i = 0; i < PookaAmount; i++) {
		mPooka[i]->SetDead(false);
	}
	mPlayer->GameRestart();
	mPlayer->HarpoonStrike(false);
	MusicTimer = 0;
	for (int i = 14; i < 224; i++) {
		mTiles[i]->Visible(false);
	}
	GameOver = false;
    PSwitch = true;
	FSwitch = true;
}






















/*
DO NOT LOOK PAST HERE DENNIS
DO NOT ENTER THE CODE FOR THE LEVELS
IT IS NOT A SAFE PLACE FOR ANY GAME DEV
TURN BACK WHILE YOU CAN
THIS DID INFACT 100% DEFINITELY NEEDED TO BE 1101 LINES LONG
*/



































void PlayScreen::LevelSet(int level) {
	mLevel = level;
	RFamount = level / 10;
	WFamount = level - (10 * RFamount);
	do {
		if (level > 12) {
			for (int i = 0; i < PookaAmount; i++) {
				mPooka[i]->SetMS(100 * (level / 13));
			}
			for (int i = 0; i < FygarAmount; i++) {
				mFygar[i]->SetMS(100 * (level / 13));
			}
			level = (level - 12);
		}
	} while (level > 12);
	if (level > 12) {
		float fposx = 700;
		for (int i = 0; i < RFamount; i++) {
			fposx -= 50;
			mRedFlower[i]->Position(fposx, 305 - 60);
		}
		for (int i = 0; i < WFamount; i++) {
			fposx -= 50;
			mWhiteFlower[i]->Position(fposx, 305 - 48);
		}
	}
	if (level == 1) {
		for (int i = 0; i < 14; i++) {
			mTiles[i]->Visible(true);
		}
		mTiles[0]->Visible(true);
		mTiles[1]->Visible(true);
		mTiles[2]->Visible(true);
		mTiles[3]->Visible(true);
		PookaAmount = 3;
		FygarAmount = 1;
		RockAmount = 3;
		for (int i = 29; i < 86; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 36; i < 41; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 107; i < 164; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 128; i < 132; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 0; i < PookaAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mPooka[i]->SetDead(false);}
			if (i == 0) {
				mPooka[i]->Position(Vector2(74.0f, 451.0f));
				mPooka[i]->SetDirection("Up");
			}
			if (i == 1) {
				mPooka[i]->Position(Vector2(507.0f, 355.0f));
				mPooka[i]->SetDirection("Right");
			}
			if (i == 2) {
				mPooka[i]->Position(Vector2(458.0f, 691.0f));
				mPooka[i]->SetDirection("Down");
			}

			if (!mPlayer->GetDead()) { mPooka[i]->SetDead(false); }
		}
		for (int i = 0; i < FygarAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mFygar[i]->SetDead(false);}
			if (i == 0) {
				mFygar[i]->Position(Vector2(171.0f, 691.0f));
				mFygar[i]->SetDirection("Right");
			}
		}
		for (int i = 0; i < RockAmount; i++) {
			if (mRock[i]->ReturnFalled()) {
				if (i == 0) {
					mRock[i]->Position(Vector2(169.0f, 403.0f));
				}
				if (i == 1) {
					mRock[i]->Position(Vector2(505.0f, 643.0f));
				}
				if (i == 2) {
					mRock[i]->Position(Vector2(121.0f, 787.0f));
				}
			}
		}
		delete mBackground;
		mBackground = new GLTexture("Level1.png", 12, 8, 563, 653);
		mBackground->Scale(Vector2(1.1936058f, 1.2496171516f));
		mBackground->Position(336.0f, Graphics::SCREEN_HEIGHT * 0.5f);
		mFoodCollect = false;
		mFoodCollected = false;
		FoodScore = 400;
		mFood = new GLTexture("Stuff.png", 3, 147, 42, 42);
		if (!mPlayer->GetDead()) {
			mAudio->PlaySFX("StageClear.mp3");
			mPlayer->Reset();
		}
		else {
			mPlayer->Position(315.0f, 547.0f);
			mPlayer->SetDead(false);
		}
	} 
	else if (level == 2) {
		for (int i = 0; i < 14; i++) {
			mTiles[i]->Visible(true);
		}
		mTiles[0]->Visible(true);
		mTiles[1]->Visible(true);
		mTiles[2]->Visible(true);
		mTiles[3]->Visible(true);
		PookaAmount = 3;
		FygarAmount = 2;
		RockAmount = 4;
		for (int i = 114; i < 157; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 51; i < 54; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 177; i < 180; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 85; i < 89; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 118; i < 121; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 0; i < PookaAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mPooka[i]->SetDead(false);}
			if (i == 0) {
				mPooka[i]->Position(Vector2(219.0f, 547.0f));
				mPooka[i]->SetDirection("Left");
			}
			if (i == 1) {
				mPooka[i]->Position(Vector2(123.0f, 787.0f));
				mPooka[i]->SetDirection("Up");
			}
			if (i == 2) {
				mPooka[i]->Position(Vector2(411.0f, 643.0f));
				mPooka[i]->SetDirection("Left");
			}
		}
		for (int i = 0; i < FygarAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mFygar[i]->SetDead(false);}
			if (i == 0) {
				mFygar[i]->Position(Vector2(459.0f, 835.0f));
				mFygar[i]->SetDirection("Right");
			}
			if (i == 1) {
				mFygar[i]->Position(Vector2(459.0f, 403.0f));
				mFygar[i]->SetDirection("Right");
			}
		}
		for (int i = 0; i < RockAmount; i++) {
			if (mRock[i]->ReturnFalled()) {
				if (i == 0) {
					mRock[i]->Position(Vector2(169.0f, 355.0f));
				}
				if (i == 1) {
					mRock[i]->Position(Vector2(217.0f, 787.0f));
				}
				if (i == 2) {
					mRock[i]->Position(Vector2(409.0f, 403.0f));
				}
				if (i == 3) {
					mRock[i]->Position(Vector2(553.0f, 595.0f));
				}
			}
		}
		delete mBackground;
		mBackground = new GLTexture("Level1.png", 12, 8, 563, 653);
		mBackground->Scale(Vector2(1.1936058f, 1.2496171516f));
		mBackground->Position(336.0f, Graphics::SCREEN_HEIGHT * 0.5f);
		mFoodCollect = false;
		mFoodCollected = false;
		FoodScore = 600;
		mFood = new GLTexture("Stuff.png", 54, 49, 14, 14);
		if (!mPlayer->GetDead()) {
			mAudio->PlaySFX("StageClear.mp3");
		    mPlayer->Reset();
		}
		else {
			mPlayer->Position(315.0f, 547.0f);
			mPlayer->SetDead(false);
		}
	}
	else if (level == 3) {
		for (int i = 0; i < 14; i++) {
			mTiles[i]->Visible(true);
		}
		mTiles[0]->Visible(true);
		mTiles[1]->Visible(true);
		mTiles[2]->Visible(true);
		mTiles[3]->Visible(true);
		PookaAmount = 3;
		FygarAmount = 2;
		RockAmount = 4;
		for (int i = 50; i < 79; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 38; i < 41; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 71; i < 74; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 163; i < 166; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 131; i < 160; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 0; i < PookaAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mPooka[i]->SetDead(false);}
			if (i == 0) {
				mPooka[i]->Position(Vector2(411.0f, 451.0f));
				mPooka[i]->SetDirection("Up");
			}
			if (i == 1) {
				mPooka[i]->Position(Vector2(123.0f, 499.0f));
				mPooka[i]->SetDirection("Right");
			}
			if (i == 2) {
				mPooka[i]->Position(Vector2(267.0f, 739.0f));
				mPooka[i]->SetDirection("Up");
			}
		}
		for (int i = 0; i < FygarAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mFygar[i]->SetDead(false);}
			if (i == 0) {
				mFygar[i]->Position(Vector2(555.0f, 355.0f));
				mFygar[i]->SetDirection("Left");
			}
			if (i == 1) {
				mFygar[i]->Position(Vector2(507.0f, 787.0f));
				mFygar[i]->SetDirection("Left");
			}
		}
		for (int i = 0; i < RockAmount; i++) {
			if (mRock[i]->ReturnFalled()) {
				if (i == 0) {
					mRock[i]->Position(Vector2(121.0f, 403.0f));
				}
				if (i == 1) {
					mRock[i]->Position(Vector2(265.0f, 643.0f));
				}
				if (i == 2) {
					mRock[i]->Position(Vector2(601.0f, 739.0f));
				}
				if (i == 3) {
					mRock[i]->Position(Vector2(553.0f, 499.0f));
				}
			}
		}
		delete mBackground;
		mBackground = new GLTexture("Level1.png", 12, 8, 563, 653);
		mBackground->Scale(Vector2(1.1936058f, 1.2496171516f));
		mBackground->Position(336.0f, Graphics::SCREEN_HEIGHT * 0.5f);
		mFoodCollect = false;
		mFoodCollected = false;
		FoodScore = 800;
		mFood = new GLTexture("Stuff.png", 105, 49, 14, 14);
		if (!mPlayer->GetDead()) {
			mAudio->PlaySFX("StageClear.mp3");
		    mPlayer->Reset();
		}
		else {
			mPlayer->Position(315.0f, 547.0f);
			mPlayer->SetDead(false);
		}
	}
	else if (level == 4) {
		for (int i = 0; i < 14; i++) {
			mTiles[i]->Visible(true);
		}
		mTiles[0]->Visible(true);
		mTiles[1]->Visible(true);
		mTiles[2]->Visible(true);
		mTiles[3]->Visible(true);
		PookaAmount = 3;
		FygarAmount = 2;
		RockAmount = 5;
		for (int i = 36; i < 65; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 30; i < 33; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 143; i < 146; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 162; i < 165; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 95; i < 124; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 0; i < PookaAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mPooka[i]->SetDead(false);}
			if (i == 0) {
				mPooka[i]->Position(Vector2(171.0f, 355.0f));
				mPooka[i]->SetDirection("Right");
			}
			if (i == 1) {
				mPooka[i]->Position(Vector2(411.0f, 403.0f));
				mPooka[i]->SetDirection("Up");
			}
			if (i == 2) {
				mPooka[i]->Position(Vector2(507.0f, 787.0f));
				mPooka[i]->SetDirection("Left");
			}
		}
		for (int i = 0; i < FygarAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mFygar[i]->SetDead(false);}
			if (i == 0) {
				mFygar[i]->Position(Vector2(219.0f, 739.0f));
				mFygar[i]->SetDirection("Right");
			}
			if (i == 1) {
				mFygar[i]->Position(Vector2(555.0f, 595.0f));
				mFygar[i]->SetDirection("Up");
			}
		}
		for (int i = 0; i < RockAmount; i++) {
			if (mRock[i]->ReturnFalled()) {
				if (i == 0) {
					mRock[i]->Position(Vector2(601.0f, 691.0f));
				}
				if (i == 1) {
					mRock[i]->Position(Vector2(553.0f, 403.0f));
				}
				if (i == 2) {
					mRock[i]->Position(Vector2(505.0f, 307.0f));
				}
				if (i == 3) {
					mRock[i]->Position(Vector2(169.0f, 595.0f));
				}
				if (i == 4) {
					mRock[i]->Position(Vector2(73.0f, 451.0f));
				}
			}
		}
		delete mBackground;
		mBackground = new GLTexture("Level1.png", 12, 8, 563, 653);
		mBackground->Scale(Vector2(1.1936058f, 1.2496171516f));
		mBackground->Position(336.0f, Graphics::SCREEN_HEIGHT * 0.5f);
		mFoodCollect = false;
		mFoodCollected = false;
		FoodScore = 1000;
		mFood = new GLTexture("Stuff.png", 156, 49, 14, 14);
		if (!mPlayer->GetDead()) {
			mAudio->PlaySFX("StageClear.mp3");
		    mPlayer->Reset();
		}
		else {
			mPlayer->Position(315.0f, 547.0f);
			mPlayer->SetDead(false);
		}
	}
	else if (level == 5) {
		for (int i = 0; i < 14; i++) {
			mTiles[i]->Visible(true);
		}
		mTiles[0]->Visible(true);
		mTiles[1]->Visible(true);
		mTiles[2]->Visible(true);
		mTiles[3]->Visible(true);
		PookaAmount = 3;
		FygarAmount = 3;
		RockAmount = 5;
		for (int i = 46; i < 75; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 42; i < 45; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 142; i < 145; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 164; i < 167; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 36; i < 65; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 79; i < 108; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 0; i < PookaAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mPooka[i]->SetDead(false);}
			if (i == 0) {
				mPooka[i]->Position(Vector2(411.0f, 355.0f));
				mPooka[i]->SetDirection("Down");
			}
			if (i == 1) {
				mPooka[i]->Position(Vector2(219.0f, 451.0f));
				mPooka[i]->SetDirection("Up");
			}
			if (i == 2) {
				mPooka[i]->Position(Vector2(75.0f, 403.0f));
				mPooka[i]->SetDirection("Right");
			}
		}
		for (int i = 0; i < FygarAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mFygar[i]->SetDead(false);}
			if (i == 0) {
				mFygar[i]->Position(Vector2(459.0f, 547.0f));
				mFygar[i]->SetDirection("Up");
			}
			if (i == 1) {
				mFygar[i]->Position(Vector2(171.0f, 739.0f));
				mFygar[i]->SetDirection("Right");
			}
			if (i == 2) {
				mFygar[i]->Position(Vector2(555.0f, 787.0f));
				mFygar[i]->SetDirection("Left");
			}
		}
		for (int i = 0; i < RockAmount; i++) {
			if (mRock[i]->ReturnFalled()) {
				if (i == 0) {
					mRock[i]->Position(Vector2(361.0f, 355.0f));
				}
				if (i == 1) {
					mRock[i]->Position(Vector2(73.0f, 499.0f));
				}
				if (i == 2) {
					mRock[i]->Position(Vector2(553.0f, 403.0f));
				}
				if (i == 3) {
					mRock[i]->Position(Vector2(265.0f, 787.0f));
				}
				if (i == 4) {
					mRock[i]->Position(Vector2(505.0f, 835.0f));
				}
			}
		}
		delete mBackground;
		mBackground = new GLTexture("Level2.png", 12, 6, 563, 653);
		mBackground->Scale(Vector2(1.1936058f, 1.2496171516f));
		mBackground->Position(336.0f, Graphics::SCREEN_HEIGHT * 0.5f);
		mFoodCollect = false;
		mFoodCollected = false;
		mFood = new GLTexture("Stuff.png", 207, 49, 14, 14);
		FoodScore = 2000;
		if (!mPlayer->GetDead()) {
			mAudio->PlaySFX("StageClear.mp3");
		    mPlayer->Reset();
		}
		else {
			mPlayer->Position(315.0f, 547.0f);
			mPlayer->SetDead(false);
		}
	}
	else if (level == 6) {
		for (int i = 0; i < 14; i++) {
			mTiles[i]->Visible(true);
		}
		mTiles[0]->Visible(true);
		mTiles[1]->Visible(true);
		mTiles[2]->Visible(true);
		mTiles[3]->Visible(true);
		PookaAmount = 2;
		FygarAmount = 4;
		RockAmount = 4;
		for (int i = 30; i < 33; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 108; i < 111; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 173; i < 176; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 127; i < 130; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 72; i < 101; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 0; i < PookaAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mPooka[i]->SetDead(false);}
			if (i == 0) {
				mPooka[i]->Position(Vector2(171.0f, 355.0f));
				mPooka[i]->SetDirection("Right");
			}
			if (i == 1) {
				mPooka[i]->Position(Vector2(171.0f, 355.0f));
				mPooka[i]->SetDirection("Right");
			}
		}
		for (int i = 0; i < FygarAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mFygar[i]->SetDead(false);}
			if (i == 0) {
				mFygar[i]->Position(Vector2(123.0f, 547.0f));
				mFygar[i]->SetDirection("Up");
			}
			if (i == 1) {
				mFygar[i]->Position(Vector2(315.0f, 835.0f));
				mFygar[i]->SetDirection("Right");
			}
			if (i == 2) {
				mFygar[i]->Position(Vector2(555.0f, 595.0f));
				mFygar[i]->SetDirection("Left");
			}
			if (i == 3) {
				mFygar[i]->Position(Vector2(123.0f, 691.0f));
				mFygar[i]->SetDirection("Right");
			}
		}
		for (int i = 0; i < RockAmount; i++) {
			if (mRock[i]->ReturnFalled()) {
				if (i == 0) {
					mRock[i]->Position(Vector2(313.0f, 691.0f));
				}
				if (i == 1) {
					mRock[i]->Position(Vector2(409.0f, 355.0f));
				}
				if (i == 2) {
					mRock[i]->Position(Vector2(553.0f, 499.0f));
				}
				if (i == 3) {
					mRock[i]->Position(Vector2(169.0f, 835.0f));
				}
			}
		}
		delete mBackground;
		mBackground = new GLTexture("Level2.png", 12, 6, 563, 653);
		mBackground->Scale(Vector2(1.1936058f, 1.2496171516f));
		mBackground->Position(336.0f, Graphics::SCREEN_HEIGHT * 0.5f);
		mFoodCollect = false;
		mFoodCollected = false;
		mFood = new GLTexture("Stuff.png", 258, 49, 14, 14);
		FoodScore = 3000;
		if (!mPlayer->GetDead()) {
			mAudio->PlaySFX("StageClear.mp3");
		    mPlayer->Reset();
		}
		else {
			mPlayer->Position(315.0f, 547.0f);
			mPlayer->SetDead(false);
		}
	}
	else if (level == 7) {
		for (int i = 0; i < 14; i++) {
			mTiles[i]->Visible(true);
		}
		mTiles[0]->Visible(true);
		mTiles[1]->Visible(true);
		mTiles[2]->Visible(true);
		mTiles[3]->Visible(true);
		PookaAmount = 4;
		FygarAmount = 3;
		RockAmount = 4;
		for (int i = 51; i < 54; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 128; i < 131; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 147; i < 150; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 32; i < 61; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 0; i < PookaAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mPooka[i]->SetDead(false);}
			if (i == 0) {
				mPooka[i]->Position(Vector2(507.0f, 403.0f));
				mPooka[i]->SetDirection("Left");
			}
			if (i == 1) {
				mPooka[i]->Position(Vector2(219.0f, 355.0f));
				mPooka[i]->SetDirection("Down");
			}
			if (i == 2) {
				mPooka[i]->Position(Vector2(219.0f, 451.0f));
				mPooka[i]->SetDirection("Up");
			}
			if (i == 3) {
				mPooka[i]->Position(Vector2(123.0f, 691.0f));
				mPooka[i]->SetDirection("Right");
			}
		}
		for (int i = 0; i < FygarAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mFygar[i]->SetDead(false);}
			if (i == 0) {
				mFygar[i]->Position(Vector2(555.0f, 403.0f));
				mFygar[i]->SetDirection("Left");
			}
			if (i == 1) {
				mFygar[i]->Position(Vector2(219.0f, 691.0f));
				mFygar[i]->SetDirection("Left");
			}
			if (i == 2) {
				mFygar[i]->Position(Vector2(411.0f, 739.0f));
				mFygar[i]->SetDirection("Left");
			}
		}
		for (int i = 0; i < RockAmount; i++) {
			if (mRock[i]->ReturnFalled()) {
				if (i == 0) {
					mRock[i]->Position(Vector2(409.0f, 355.0f));
				}
				if (i == 1) {
					mRock[i]->Position(Vector2(553.0f, 499.0f));
				}
				if (i == 2) {
					mRock[i]->Position(Vector2(505.0f, 691.0f));
				}
				if (i == 3) {
					mRock[i]->Position(Vector2(121.0f, 451.0f));
				}
			}
		}
		delete mBackground;
		mBackground = new GLTexture("Level2.png", 12, 6, 563, 653);
		mBackground->Scale(Vector2(1.1936058f, 1.2496171516f));
		mBackground->Position(336.0f, Graphics::SCREEN_HEIGHT * 0.5f);
		mFoodCollect = false;
		mFoodCollected = false;
		mFood = new GLTexture("Stuff.png", 309, 49, 14, 14);
		FoodScore = 4000;
		if (!mPlayer->GetDead()) {
			mAudio->PlaySFX("StageClear.mp3");
		    mPlayer->Reset();
		}
		else {
			mPlayer->Position(315.0f, 547.0f);
			mPlayer->SetDead(false);
		}
	}
	else if (level == 8) {
		for (int i = 0; i < 14; i++) {
			mTiles[i]->Visible(true);
		}
		mTiles[0]->Visible(true);
		mTiles[1]->Visible(true);
		mTiles[2]->Visible(true);
		mTiles[3]->Visible(true);
		PookaAmount = 4;
		FygarAmount = 3;
		RockAmount = 4;
		for (int i = 42; i < 45; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 65; i < 68; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 135; i < 138; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 143; i < 146; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 46; i < 75; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 100; i < 129; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 0; i < PookaAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mPooka[i]->SetDead(false);}
			if (i == 0) {
				mPooka[i]->Position(Vector2(219.0f, 451.0f));
				mPooka[i]->SetDirection("Down");
			}
			if (i == 1) {
				mPooka[i]->Position(Vector2(219.0f, 403.0f));
				mPooka[i]->SetDirection("Down");
			}
			if (i == 2) {
				mPooka[i]->Position(Vector2(507.0f, 451.0f));
				mPooka[i]->SetDirection("Left");
			}
			if (i == 3) {
				mPooka[i]->Position(Vector2(267.0f, 739.0f));
				mPooka[i]->SetDirection("Left");
			}
		}
		for (int i = 0; i < FygarAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mFygar[i]->SetDead(false);}
			if (i == 0) {
				mFygar[i]->Position(Vector2(75.0f, 403.0f));
				mFygar[i]->SetDirection("Right");
			}
			if (i == 1) {
				mFygar[i]->Position(Vector2(123.0f, 643.0f));
				mFygar[i]->SetDirection("Up");
			}
			if (i == 2) {
				mFygar[i]->Position(Vector2(507.0f, 691.0f));
				mFygar[i]->SetDirection("Left");
			}
		}
		for (int i = 0; i < RockAmount; i++) {
			if (mRock[i]->ReturnFalled()) {
				if (i == 0) {
					mRock[i]->Position(Vector2(313.0f, 691.0f));
				}
				if (i == 1) {
					mRock[i]->Position(Vector2(265.0f, 595.0f));
				}
				if (i == 2) {
					mRock[i]->Position(Vector2(601.0f, 499.0f));
				}
				if (i == 3) {
					mRock[i]->Position(Vector2(73.0f, 451.0f));
				}
			}
		}
		delete mBackground;
		mBackground = new GLTexture("Level2.png", 12, 6, 563, 653);
		mBackground->Scale(Vector2(1.1936058f, 1.2496171516f));
		mBackground->Position(336.0f, Graphics::SCREEN_HEIGHT * 0.5f);
		mFoodCollect = false;
		mFoodCollected = false;
		mFood = new GLTexture("Stuff.png", 360, 49, 14, 14);
		FoodScore = 5000;
		if (!mPlayer->GetDead()) {
			mAudio->PlaySFX("StageClear.mp3");
		    mPlayer->Reset();
		}
		else {
			mPlayer->Position(315.0f, 547.0f);
			mPlayer->SetDead(false);
		}
	}
	else if (level == 9) {
		for (int i = 0; i < 14; i++) {
			mTiles[i]->Visible(true);
		}
		mTiles[0]->Visible(true);
		mTiles[1]->Visible(true);
		mTiles[2]->Visible(true);
		mTiles[3]->Visible(true);
		PookaAmount = 4;
		FygarAmount = 4;
		RockAmount = 5;
		for (int i = 128; i < 131; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 117; i < 120; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 64; i < 67; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 135; i < 138; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 46; i < 75; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 81; i < 110; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 0; i < PookaAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mPooka[i]->SetDead(false);}
			if (i == 0) {
				mPooka[i]->Position(Vector2(219.0f, 403.0f));
				mPooka[i]->SetDirection("Down");
			}
			if (i == 1) {
				mPooka[i]->Position(Vector2(459.0f, 451.0f));
				mPooka[i]->SetDirection("Left");
			}
			if (i == 2) {
				mPooka[i]->Position(Vector2(459.0f, 451.0f));
				mPooka[i]->SetDirection("Left");
			}
			if (i == 3) {
				mPooka[i]->Position(Vector2(555.0f, 547.0f));
				mPooka[i]->SetDirection("Down");
			}
		}
		for (int i = 0; i < FygarAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mFygar[i]->SetDead(false);}
			if (i == 0) {
				mFygar[i]->Position(Vector2(171.0f, 691.0f));
				mFygar[i]->SetDirection("Right");
			}
			if (i == 1) {
				mFygar[i]->Position(Vector2(171.0f, 691.0f));
				mFygar[i]->SetDirection("Right");
			}
			if (i == 2) {
				mFygar[i]->Position(Vector2(315.0f, 643.0f));
				mFygar[i]->SetDirection("Right");
			}
			if (i == 3) {
				mFygar[i]->Position(Vector2(507.0f, 691.0f));
				mFygar[i]->SetDirection("Left");
			}
		}
		for (int i = 0; i < RockAmount; i++) {
			if (mRock[i]->ReturnFalled()) {
				if (i == 0) {
					mRock[i]->Position(Vector2(457.0f, 595.0f));
				}
				if (i == 1) {
					mRock[i]->Position(Vector2(265.0f, 691.0f));
				}
				if (i == 2) {
					mRock[i]->Position(Vector2(553.0f, 403.0f));
				}
				if (i == 3) {
					mRock[i]->Position(Vector2(361.0f, 355.0f));
				}
				if (i == 4) {
					mRock[i]->Position(Vector2(73.0f, 547.0f));
				}
			}
		}
		delete mBackground;
		mBackground = new GLTexture("Level3.png", 12, 8, 563, 653);
		mBackground->Scale(Vector2(1.1936058f, 1.2496171516f));
		mBackground->Position(336.0f, Graphics::SCREEN_HEIGHT * 0.5f);
		mFoodCollect = false;
		mFoodCollected = false;
		mFood = new GLTexture("Stuff.png", 411, 49, 14, 14);
		FoodScore = 6000;
		if (!mPlayer->GetDead()) {
			mAudio->PlaySFX("StageClear.mp3");
		    mPlayer->Reset();
		}
		else {
			mPlayer->Position(315.0f, 547.0f);
			mPlayer->SetDead(false);
		}
	}
    else if (level == 10) {
		for (int i = 0; i < 14; i++) {
			mTiles[i]->Visible(true);
		}
		PookaAmount = 4;
		FygarAmount = 4;
		RockAmount = 4;
		for (int i = 143; i < 146; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 149; i < 152; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 64; i < 67; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 40; i < 69; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 58; i < 87; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 93; i < 122; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 0; i < PookaAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mPooka[i]->SetDead(false);}
			if (i == 0) {
				mPooka[i]->Position(Vector2(459.0f, 451.0f));
				mPooka[i]->SetDirection("Left");
			}
			if (i == 1) {
				mPooka[i]->Position(Vector2(603.0f, 355.0f));
				mPooka[i]->SetDirection("Down");
			}
			if (i == 2) {
				mPooka[i]->Position(Vector2(603.0f, 403.0f));
				mPooka[i]->SetDirection("Down");
			}
			if (i == 3) {
				mPooka[i]->Position(Vector2(507.0f, 739.0f));
				mPooka[i]->SetDirection("Left");
			}
		}
		for (int i = 0; i < FygarAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mFygar[i]->SetDead(false);}
			if (i == 0) {
				mFygar[i]->Position(Vector2(459.0f, 451.0f));
				mFygar[i]->SetDirection("Left");
			}
			if (i == 1) {
				mFygar[i]->Position(Vector2(459.0f, 595.0f));
				mFygar[i]->SetDirection("Up");
			}
			if (i == 2) {
				mFygar[i]->Position(Vector2(219.0f, 739.0f));
				mFygar[i]->SetDirection("Right");
			}
			if (i == 3) {
				mFygar[i]->Position(Vector2(123.0f, 499.0f));
				mFygar[i]->SetDirection("Up");
			}
		}
		for (int i = 0; i < RockAmount; i++) {
			if (mRock[i]->ReturnFalled()) {
				if (i == 0) {
					mRock[i]->Position(Vector2(363.0f, 787.0f));
				}
				if (i == 2) {
					mRock[i]->Position(Vector2(553.0f, 595.0f));
				}
				if (i == 3) {
					mRock[i]->Position(Vector2(121.0f, 355.0f));
				}
				if (i == 1) {
					mRock[i]->Position(Vector2(73.0f, 499.0f));
				}
			}
		}
		delete mBackground;
		mBackground = new GLTexture("Level3.png", 12, 8, 563, 653);
		mBackground->Scale(Vector2(1.1936058f, 1.2496171516f));
		mBackground->Position(336.0f, Graphics::SCREEN_HEIGHT * 0.5f);
		mFoodCollect = false;
		mFoodCollected = false;
		mFood = new GLTexture("Stuff.png", 462, 49, 14, 14);
		FoodScore = 7000;
		if (!mPlayer->GetDead()) {
			mAudio->PlaySFX("StageClear.mp3");
		    mPlayer->Reset();
		}
		else {
			mPlayer->Position(315.0f, 547.0f);
			mPlayer->SetDead(false);
		}
	}
    else if (level == 11) {
		for (int i = 0; i < 14; i++) {
			mTiles[i]->Visible(true);
		}
		PookaAmount = 3;
		FygarAmount = 4;
		RockAmount = 4;
		for (int i = 72; i < 75; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 43; i < 46; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 95; i < 124; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 51; i < 80; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 100; i < 129; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 0; i < PookaAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mPooka[i]->SetDead(false);}
			if (i == 0) {
				mPooka[i]->Position(Vector2(171.0f, 499.0f));
				mPooka[i]->SetDirection("Right");
			}
			if (i == 1) {
				mPooka[i]->Position(Vector2(75.0f, 403.0f));
				mPooka[i]->SetDirection("Right");
			}
			if (i == 2) {
				mPooka[i]->Position(Vector2(459.0f, 451.0f));
				mPooka[i]->SetDirection("Down");
			}
		}
		for (int i = 0; i < FygarAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mFygar[i]->SetDead(false);}
			if (i == 0) {
				mFygar[i]->Position(Vector2(123.0f, 403.0f));
				mFygar[i]->SetDirection("Right");
			}
			if (i == 1) {
				mFygar[i]->Position(Vector2(123.0f, 595.0f));
				mFygar[i]->SetDirection("Down");
			}
			if (i == 2) {
				mFygar[i]->Position(Vector2(459.0f, 451.0f));
				mFygar[i]->SetDirection("Down");
			}
			if (i == 3) {
				mFygar[i]->Position(Vector2(555.0f, 547.0f));
				mFygar[i]->SetDirection("Down");
			}
		}
		for (int i = 0; i < RockAmount; i++) {
			if (mRock[i]->ReturnFalled()) {
				if (i == 0) {
					mRock[i]->Position(Vector2(265.0f, 643.0f));
				}
				if (i == 2) {
					mRock[i]->Position(Vector2(505.0f, 355.0f));
				}
				if (i == 3) {
					mRock[i]->Position(Vector2(25.0f, 355.0f));
				}
				if (i == 1) {
					mRock[i]->Position(Vector2(553.0f, 691.0f));
				}
			}
		}
		delete mBackground;
		mBackground = new GLTexture("Level3.png", 12, 8, 563, 653);
		mBackground->Scale(Vector2(1.1936058f, 1.2496171516f));
		mBackground->Position(336.0f, Graphics::SCREEN_HEIGHT * 0.5f);
		mFoodCollect = false;
		mFoodCollected = false;
		mFood = new GLTexture("Stuff.png", 513, 49, 14, 14);
		FoodScore = 8000;
		if (!mPlayer->GetDead()) {
			mAudio->PlaySFX("StageClear.mp3");
		    mPlayer->Reset();
		}
		else {
			mPlayer->Position(315.0f, 547.0f);
			mPlayer->SetDead(false);
		}
	}
    else if (level == 12) {
		for (int i = 0; i < 14; i++) {
			mTiles[i]->Visible(true);
		}
		PookaAmount = 4;
		FygarAmount = 4;
		RockAmount = 4;
		for (int i = 64; i < 67; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 44; i < 47; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 171; i < 174; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 163; i < 166; i++) {
			mTiles[i]->Visible(true);
		}
		for (int i = 54; i < 83; i += 14) {
			mTiles[i]->Visible(true);
		}
		for (int i = 0; i < PookaAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mPooka[i]->SetDead(false);}
			if (i == 0) {
				mPooka[i]->Position(Vector2(459.0f, 451.0f));
				mPooka[i]->SetDirection("Left");
			}
			if (i == 1) {
				mPooka[i]->Position(Vector2(123.0f, 403.0f));
				mPooka[i]->SetDirection("Right");
			}
			if (i == 2) {
				mPooka[i]->Position(Vector2(603.0f, 499.0f));
				mPooka[i]->SetDirection("Up");
			}
			if (i == 3) {
				mPooka[i]->Position(Vector2(459.0f, 451.0f));
				mPooka[i]->SetDirection("Left");
			}
		}
		for (int i = 0; i < FygarAmount; i++) {
			if(!FSwitch && !PSwitch){;}else{mFygar[i]->SetDead(false);}
			if (i == 0) {
				mFygar[i]->Position(Vector2(171.0f, 403.0f));
				mFygar[i]->SetDirection("Right");
			}
			if (i == 1) {
				mFygar[i]->Position(Vector2(219.0f, 835.0f));
				mFygar[i]->SetDirection("Right");
			}
			if (i == 2) {
				mFygar[i]->Position(Vector2(459.0f, 787.0f));
				mFygar[i]->SetDirection("Right");
			}
			if (i == 3) {
				mFygar[i]->Position(Vector2(555.0f, 787.0f));
				mFygar[i]->SetDirection("Right");
			}
		}
		for (int i = 0; i < RockAmount; i++) {
			if (mRock[i]->ReturnFalled()) {
				if (i == 0) {
					mRock[i]->Position(Vector2(457.0f, 355.0f));
				}
				if (i == 2) {
					mRock[i]->Position(Vector2(505.0f, 547.0f));
				}
				if (i == 3) {
					mRock[i]->Position(Vector2(73.0f, 595.0f));
				}
				if (i == 1) {
					mRock[i]->Position(Vector2(553.0f, 691.0f));
				}
			}
		}
		delete mBackground;
		mBackground = new GLTexture("Level3.png", 12, 8, 563, 653);
		mBackground->Scale(Vector2(1.1936058f, 1.2496171516f));
		mBackground->Position(336.0f, Graphics::SCREEN_HEIGHT * 0.5f);
		mFoodCollect = false;
		mFoodCollected = false;
		mFood = new GLTexture("Stuff.png", 513, 49, 14, 14);
		FoodScore = 8000;
		if (!mPlayer->GetDead()) {
			mAudio->PlaySFX("StageClear.mp3");
		    mPlayer->Reset();
		}
		else {
			mPlayer->Position(315.0f, 547.0f);
			mPlayer->SetDead(false);
		}
	}
	if (level < 13) {
		float fposx = 700;
		for (int i = 0; i < RFamount; i++) {
			fposx -= 50;
			mRedFlower[i]->Position(fposx, 305 - 60);
		}
		for (int i = 0; i < WFamount; i++) {
			fposx -= 50;
			mWhiteFlower[i]->Position(fposx, 305 - 48);
		}
	}
	mPlayer->Position(315.0f, 548.0f);
}