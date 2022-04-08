#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "TitleLogo.h"

#include "MenuExit.h"
#include "MenuLoad.h"
#include "MenuNewGame.h"
#include "Mouse.h"

#include "TitleBackGround.h"
enum class ORDER
{
	TitleLogo = 0,
	TitleBackGround,
	MAX,
};

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

private:
	TitleLogo* TitleLogo_;
	MenuNewGame* MenuNewGame_;
	MenuLoad* MenuLoad_;
	MenuExit* MenuExit_;
	Mouse* Mouse_;
	TitleBackGround* TitleBackGround_;

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

