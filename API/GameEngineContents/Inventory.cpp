#include "Inventory.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <sstream>

Inventory::Inventory() 
	:
	BoxCollision_{nullptr},
	isItem{false},
	WildHorseradish_(nullptr),
	ItemCount_(0)
{
}

Inventory::~Inventory() 
{
}

void Inventory::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	Inventroy_ = CreateRenderer("inventory.bmp");
	BoxInit();


	PlayerItemList.reserve(INVENTORY_MAX_COUNT);

	WildHorseradish_ = NewItem<WildHorseradish>();
}


void Inventory::BoxInit()
{

	for (int i = 0; i < INVENTORY_MAX_COUNT; i++) {

		Box_.insert(std::make_pair(i, GetLevel()->CreateActor<InventroyBox>(10)));

		//
		//std::stringstream CollisionBoxNum;
		//CollisionBoxNum << i;
		//BoxCollision_[i] = CreateCollision(CollisionBoxNum.str(), {148, 116});

	}


	//��ġ �ʱ�ȭ
	std::map<int, InventroyBox*>::iterator StartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator EndIter = Box_.end();
	int count = 0;

	for (int y = 0; y < 3; ++y) {

		float BoxMargin = 0.f;

		if (y > 0) {
			BoxMargin = 10.f;
		}

		for (int x = 0; x < 12; ++x)
		{
			StartIter->second->SetPosition({ (GetPosition().x - 352.f) + (64.f * x), (GetPosition().y - 200.f) + (64.f * y + BoxMargin) });
			StartIter->second->CreateBoxCollision(count);
			count++;
			StartIter++;
		}

	}
}



void Inventory::Update()
{

	//if (Weeds_->isPlayerHas()) {
	//	Weeds_ = GetLevel()->CreateActor<Weeds>();
	//	PlayerItemList.push_back(Weeds_);
	//}

}

void Inventory::Render()
{
}



//�������� ���´ٸ�
//�տ������� ä���
//������ ���� �˾Ƽ�
//��� ������ ������

//����������

//�̱���

//�̸��� �޾Ƽ� ���͸� �������

//�������� ������ ���ͷ� ������ΰ�?