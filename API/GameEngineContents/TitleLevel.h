#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "TitleLogo.h"
#include "RendererData.h"
#include "MenuExit.h"
#include "MenuLoad.h"
#include "MenuNewGame.h"
#include "Mouse.h"
#include "Player.h"
#include "Title.h"
#include "BackGround.h"

//�ڸ� �̹��� �ε�����
enum class MENU
{
	MenuNewGame = 0, //0
	MenuLoad,	//1
	MenuExit,	//2
	ClickMenuNewGame,
	ClickMenuLoad,
	ClickMenuExit,
	MAX,
};


enum class KEYBOARD
{
	Wait = 0,
	MenuNewGame, //1
	MenuLoad,	//2
	MenuExit,	//3
	MAX,

};

// ���� :
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

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;

private:

	Title* Title_;

	TitleLogo* TitleLogo_;

	MenuNewGame* MenuNewGame_;
	MenuLoad* MenuLoad_;
	MenuExit* MenuExit_;

	Mouse* Mouse_;

	BackGround* TitleBackGround_;
	BackGround* TitleRightFrontMount;
	BackGround* TitleLeftFrontMout;
	BackGround* TitleBackMountBlue;
	BackGround* TitleBackMountGreen;

	BackGround* TitleCloud_[2];



	Player* Player_;


	bool isPopup_;
	bool KeyFlag_; //������Ʈ���� �Լ��� �ѹ��� ����ϱ� ���� �÷���
	int Timer_;
	unsigned int MoveMenu_;
	KEYBOARD CurrentMenu_;

	void AddTimer(int i) {
		Timer_ += i;
	}

	int getTimer() {
		return Timer_;
	}
};

