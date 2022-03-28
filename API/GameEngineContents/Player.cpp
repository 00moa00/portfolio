#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> // ������ ���ؼ�



Player::Player()
	:	Speed_(100.0f),
		Energy_(0.f),
		PlayerBody_(nullptr),
		PlayerArm_(nullptr)
{
}

Player::~Player() 
{
}


void Player::Start() 
{
	SetPosition(GameEngineWindow::GetScale().Half());
	PlayerBody_ = CreateRenderer("farmer_girl_base_bald.bmp");
	PlayerBody_->SetIndex(0);

	PlayerArm_ = CreateRenderer("farmer_girl_base_bald.bmp");
	PlayerArm_->SetIndex(6);

	if (false == GameEngineInput::GetInst()->IsKey("MoveUp"))
	{
		//GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		//GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
	}

	Energy_ = (42.f * 1.8f);
}

void Player::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		// 1.0F * 0.001101F
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
		Energy_ -= 3.0f* GameEngineTime::GetDeltaTime();
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
		Energy_ -= 3.0f * GameEngineTime::GetDeltaTime();
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
		Energy_ -= 3.0f * GameEngineTime::GetDeltaTime();
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
		Energy_ -= 3.0f * GameEngineTime::GetDeltaTime();

	}

	//if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	//{

	//}

	// ���� Ű�� �����ٸ� ��������.
	//if (0 != GetAsyncKeyState('A'))
	//{
	//	int a = 0;
	//}

}

// �������� �� ���ư��� �������� �˴ϴ�.
void Player::Render() 
{
	//GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");
	//if (nullptr == FindImage)
	//{
	//	MsgBoxAssert("CCCCC!");
	//}
	//GameEngine::BackBufferImage()->BitCopyBot(FindImage, GetPosition());

}