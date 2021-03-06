#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>


#include "TitleLogo.h"
#include "RendererData.h"
#include "Mouse.h"
#include "Player.h"
#include "Title.h"
#include "BackGround.h"
#include "Bird.h"
#include "MenuButton.h"

#include "CustomBoard.h"

enum class TITLE_STATE
{
	START,
	POPUP,
	WAIT
};

// 설명 :
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

private:

	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

	bool isPopup_;
	bool KeyFlag_; //업데이트에서 함수를 한번만 사용하기 위한 플러그
	bool ButtonPopUp[3];

	float Timer_;
	float SoundTimer_;

	Title* Title_;

	TitleLogo* TitleLogo_;
	MenuButton* MenuButton_[3];

	Mouse* Mouse_;

	BackGround* TitleBackGround_;
	BackGround* TitleRightFrontMount;
	BackGround* TitleLeftFrontMount;
	BackGround* TitleBackMountBlue;
	BackGround* TitleBackMountGreen;
	BackGround* TitleCloud_[3];

	Bird* Bird_[2];

	CustomBoard* CustomBoard_;

	GameEngineSoundPlayer BgmPlayer;

	TITLE_STATE TitleState_;

private:

	void MoveCloud();
	void MoveFrontMount();
	void MoveBackMount();
	void MoveTitleLogo();
	void MoveLogo();
	void PopUpMenu();
	void MoveBird();

	void SkipTitle();

	//================================
	//     Getter
	//================================


	//================================
	//     Setter
	//================================

};

