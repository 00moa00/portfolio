#include "MainUI.h"
#include "RendererData.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include "Player.h"

#include <GameEngine/GameEngineLevel.h> 

MainUI::MainUI() 
{
}

MainUI::~MainUI() 
{
}

void MainUI::Start()
{

	SetPosition({ GameEngineWindow::GetScale().x - (140.f / 1.5f) - 50.f,  (114.f / 1.5f) + 50.f });

	MainUI_ = CreateRenderer("UITop.bmp");
	MainUI_->CameraEffectOff();

	Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONTUI);
	Font_->ChangeNumUI(1000);
	Font_->SetPositionUI({1085.f, 192.f });
	LevelRegist("MainUI");

}

void MainUI::Update()
{
//	Player* MainPlayer = GetLevel()->FindActor<Player>("MainPlayer");

}

void MainUI::Render()
{
}

void MainUI::SetMainUIMoney(int _Money)
{
	Font_->ChangeNumUI(_Money);
}
