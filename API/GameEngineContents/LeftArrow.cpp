#include "LeftArrow.h"


#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> // ������ ���ؼ�

LeftArrow::LeftArrow() 
	:
	LeftArrow_(nullptr)
{
}

LeftArrow::~LeftArrow() 
{
}

void LeftArrow::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	LeftArrow_ = CreateRenderer("LeftArrow.bmp");
}

void LeftArrow::Update()
{
}

void LeftArrow::Render()
{
}
