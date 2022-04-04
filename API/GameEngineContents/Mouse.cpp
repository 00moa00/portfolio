#include "Mouse.h"


#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineLevel.h> 

Mouse::Mouse() :
	CursorPos_({}),
	MousePoint_(nullptr)
{
}

Mouse::~Mouse() 
{
}

void Mouse::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("Enter"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftClick", MK_LBUTTON);

		// VK_LBUTTON;
	}

	CursorPos_ = GameEngineWindow::GetScale().Half();
	MousePoint_ = CreateRenderer("MouseCursor.bmp");
	//MousePoint_->SetScale({ 600, 330 }); 	//800, 440  �ΰ� ���� ũ��

	MouseCollision_ = CreateCollision("MouseCursor", { 24, 30 });

}

void Mouse::Update()
{
	ShowCursor(FALSE);
	GetCursorPos(&pt);	
	ScreenToClient(GameEngineWindow::GetHWND(), &pt);
	CursorPos_.x = static_cast<float>(pt.x);
	CursorPos_.y = static_cast<float>(pt.y);

	MousePoint_->GetActor()->SetPosition(CursorPos_);

}

void Mouse::Render()
{
}
