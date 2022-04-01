#include "MyHouseLevel.h"



enum class ORDER
{
	//BACKGROUND,
	PLAYER,

	ENERGYFRAME,
	ENERGYBAR,
	MAINUI
};

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
	Player_ = CreateActor<Player>((int)ORDER::PLAYER);
	PlayerEnergyFrame_ = CreateActor<PlayerEnergyFrame>((int)ORDER::ENERGYFRAME);
	PlayerEnergyBar_ = CreateActor<PlayerEnergyBar>((int)ORDER::ENERGYBAR);
	MainUI_ = CreateActor<MainUI>((int)ORDER::MAINUI);

}

void MyHouseLevel::LevelChangeStart()
{


}


void MyHouseLevel::Update()
{
	//�÷��̾ �ൿ �Ҷ����� ���׹̳� ����. �׽�Ʈ��
	//PlayerEnergyBar_->SubEnergyBar(PlayerBody_->GetEnergy());





}
