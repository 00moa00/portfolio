#include "MainUI.h"
#include "RendererData.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include "Player.h"

#include <GameEngine/GameEngineLevel.h> 

MainUI* MainUI::MainMainUI = nullptr;

Font* MainUI::MoneyFont_ = nullptr;
Font* MainUI::MinuteFont_ = nullptr;
Font* MainUI::HourFont_ = nullptr;
Font* MainUI::DayFont_ = nullptr;


MainUI::MainUI() 
	:
	MinuteTime_(0),
	HourTime_(6),
	Day_(1),
	WeekIndex_(0),
	SecondTime_(0),
	PrevSecondTime_(0),
	AddTIme_(),

	AmPm_(AM_PM::AM),

	MinuteState_(MINUTE_STATE::COUNT),

	MainUIRenderer_(nullptr),
	WeekRenderer_(nullptr),
	AmPmRenderer_(nullptr)
{
}

MainUI::~MainUI() 
{

}

void MainUI::Start()
{
	SetPosition({ GameEngineWindow::GetScale().x - (140.f / 1.5f) - 50.f,  (114.f / 1.5f) + 50.f });

	MainUIRenderer_ = CreateRenderer("UITop.bmp");
	MainUIRenderer_->CameraEffectOff();
	MainUIRenderer_->SetOrder((int)PLAYLEVEL::MAINUI);

	MoneyFont_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONTUI);
	MoneyFont_->ChangeNumMoneyLeftSort(1000, { 1230.f, 192.f });

	//1188 128
	AmPmRenderer_ = CreateRenderer("am.bmp");
	AmPmRenderer_->CameraEffectOff();
	AmPmRenderer_->SetPivot({ 60.f, 12.f });

	//1150 67
	WeekRenderer_ = CreateRenderer("Week_Sheet.bmp");
	WeekRenderer_->CameraEffectOff();
	WeekRenderer_->SetPivot({ 20.f, -60.f });
	WeekRenderer_->SetIndex(static_cast<int>(WEEK::MON));

	//1119 128
	HourFont_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONTUI);
	HourFont_->ChangeNumLeftSort(6, { GetPosition().x - 3.f, GetPosition().y + 1.f});

	//1145 128
	MinuteFont_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONTUI);
	MinuteFont_->ChangeNumStr("00");
	MinuteFont_->ChangeNumLeftSort(10, { GetPosition().x + 32.f, GetPosition().y + 1.f });

	//1145 128
	DayFont_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONTUI);
	DayFont_->ChangeNumRightSort(1);
	DayFont_->SetPositionRightSort({ GetPosition().x + 55.f, GetPosition().y  - 55.f});

	LevelRegist("MainUI");


	//1145
}

void MainUI::Update()
{

	if (true == GameEngineInput::GetInst()->IsPress("TimeAdd"))
	{
		AddTIme_ = 1000;

	}
	
	else
	{
		AddTIme_ = 1;
	}

	SecondTime_ = (GetAccTime()) * AddTIme_;
	SecondTimeInt_ = static_cast<int>(SecondTime_) + 253;



	switch (MinuteState_)
	{
	case MINUTE_STATE::COUNT:



		if (SecondTimeInt_ % 7 == 0)
		{
			MinuteState_ = MINUTE_STATE::ADD;
			break;
		}

		break;

	case MINUTE_STATE::ADD:

		MinuteTime_ += 10;
		PrevSecondTime_ = SecondTimeInt_;

		MinuteState_ = MINUTE_STATE::WAIT;

		break;

	case MINUTE_STATE::WAIT:

		if (PrevSecondTime_ != SecondTimeInt_)
		{
			MinuteState_ = MINUTE_STATE::COUNT;
			break;
		}

		break;
	default:
		break;
	}

	UpdateMinuteFont();
	UpdateHourTime();
	UpdateSetPm();
	UpdateAddDay();
}

void MainUI::Render()
{

}

void MainUI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainMainUI = this;

	MoneyFont_ = MoneyFont_;
	MinuteFont_ = MinuteFont_;
	HourFont_ = HourFont_;
	DayFont_ = DayFont_;
}

void MainUI::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	MoneyFont_->NextLevelOn();
	MinuteFont_->NextLevelOn();
	HourFont_->NextLevelOn();
	DayFont_->NextLevelOn();
}


void MainUI::UpdateMinuteFont()
{
	//10�и��� ��Ʈ ������Ʈ
	if (MinuteTime_ > 0 && MinuteTime_ % 10 == 0)
	{
		MinuteFont_->ChangeNumLeftSort(MinuteTime_, { GetPosition().x + 32.f, GetPosition().y + 1.f });
		return;

	}
}

void MainUI::UpdateHourTime()
{
	//1�ð��� �Ǹ� �� ����, ��Ʈ ������Ʈ
	if (MinuteTime_ > 0 && MinuteTime_ % 60 == 0)
	{
		MinuteTime_ = 0;
		MinuteFont_->ChangeNumStr("00");

		HourTime_ += 1;
		HourFont_->ChangeNumLeftSort(HourTime_, { GetPosition().x - 3.f, GetPosition().y + 1.f });
		return;
	}
}

void MainUI::UpdateSetPm()
{
	//12�ð� �Ǹ� ���ķ� �ٲ�� 1�÷� �ٽ� ī����
	if (HourTime_ == 12 && AmPm_ == AM_PM::AM)
	{
		HourTime_ = 1;
		SetPm();
		AmPm_ = AM_PM::PM;
	}
}

void MainUI::UpdateAddDay()
{
	//���� 12�ð� ������ �Ϸ簡 �ٲ�
	if (HourTime_ == 12 && AmPm_ == AM_PM::PM)
	{
		HourTime_ = 1;
		SetAm();
		AmPm_ = AM_PM::PM;
		AddWeek();
		++Day_;
		DayFont_->ChangeNumRightSort(Day_);
	}

}

void MainUI::SetMainUIMoney(int _Money)
{
	MoneyFont_->ChangeNumMoneyLeftSort(_Money, { 1230.f, 192.f });
}
