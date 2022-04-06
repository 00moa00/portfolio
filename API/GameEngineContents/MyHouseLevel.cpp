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
	Player_ = CreateActor<Player>((int)PLAYLEVEL::PLAYER);
	PlayerEnergyFrame_ = CreateActor<PlayerEnergyFrame>((int)PLAYLEVEL::ENERGYFRAME);
	PlayerEnergyBar_ = CreateActor<PlayerEnergyBar>((int)PLAYLEVEL::ENERGYBAR);
	MainUI_ = CreateActor<MainUI>((int)PLAYLEVEL::MAINUI);
	CreateActor<TitleBackGround>((int)PLAYLEVEL::BACKGROUND);

	//Inventory_->AllUpdateOff();
}

void MyHouseLevel::LevelChangeStart()
{


}


void MyHouseLevel::Update()
{

	//�÷��̾ �ൿ �Ҷ����� ���׹̳� ����. �׽�Ʈ��
	////PlayerEnergyBar_->SubEnergyBar(PlayerBody_->GetEnergy());
	//		if (GetAsyncKeyState(MK_LBUTTON))
	//{
	//	GameEngine::GetInst().ChangeLevel("Title");
	//}
}
