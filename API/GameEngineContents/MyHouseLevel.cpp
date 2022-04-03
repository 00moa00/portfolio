#include "MyHouseLevel.h"





MyHouseLevel::MyHouseLevel()
	:

	PlayerEnergyBar_(nullptr),
	PlayerEnergyFrame_(nullptr),
	Player_(nullptr),

	MainUI_(nullptr)

{
}

MyHouseLevel::~MyHouseLevel()
{
}

void MyHouseLevel::Loading()
{
	Player_ = CreateActor<Player>((int)PlayLevel::PLAYER);
	PlayerEnergyFrame_ = CreateActor<PlayerEnergyFrame>((int)PlayLevel::ENERGYFRAME);
	PlayerEnergyBar_ = CreateActor<PlayerEnergyBar>((int)PlayLevel::ENERGYBAR);
	MainUI_ = CreateActor<MainUI>((int)PlayLevel::MAINUI);
	CreateActor<TitleBackGround>((int)PlayLevel::BACKGROUND);


}

void MyHouseLevel::LevelChangeStart()
{


}


void MyHouseLevel::Update()
{
	//�÷��̾ �ൿ �Ҷ����� ���׹̳� ����. �׽�Ʈ��
	//PlayerEnergyBar_->SubEnergyBar(PlayerBody_->GetEnergy());





}
