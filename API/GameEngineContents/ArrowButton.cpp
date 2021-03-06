#include "ArrowButton.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>

ArrowButton::ArrowButton()
	:

	ArrowRenderer_(nullptr),
	ArrowCollision_(nullptr)
{
}

ArrowButton::~ArrowButton() 
{
}

void ArrowButton::Start()
{
	ArrowRenderer_ = CreateRenderer();
}

void ArrowButton::Update()
{
}

void ArrowButton::CreateArrowCollision(std::string _CollName)
{
	ArrowCollision_ = CreateCollision(_CollName, { 44, 44 });
}

void ArrowButton::CreateRightArrow()
{
	ArrowRenderer_->SetImage("RightArrow.bmp");
}

void ArrowButton::CreateLeftArrow()
{
	ArrowRenderer_->SetImage("LeftArrow.bmp");

}

bool ArrowButton::ButtonMouseOverAndLeftClick()
{
	return (ArrowCollision_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect))
		&& (true == GameEngineInput::GetInst()->IsDown("LeftClick"));
}

