#include "Inventory.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <sstream>

Inventory::Inventory() 
	:
	BoxCollision_{nullptr},
	isItem{false},
	Weeds_(nullptr),
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


	PlayerItemList.reserve(INVENTORYCOUNT);
	NewItem(Weeds_);
}

void Inventory::NewItem(GameEngineActor* _Item)
{
	//ī����, Ž�� ��
	PlayerItemList.push_back(_Item);

	
	std::map<int, InventroyBox*>::iterator FindIter = Box_.find(PlayerItemList.size()-1);

	float4 Pos = FindIter->second->GetPosition();

	GameEngineActor* Item = _Item;

	_Item = GetLevel()->CreateActor<Weeds>(11);
	_Item->SetPosition({ Pos.x, Pos.y });
	
}

void Inventory::BoxInit()
{
	for (int i = 0; i < INVENTORYCOUNT; i++) {

		Box_.insert(std::make_pair(i, GetLevel()->CreateActor<InventroyBox>(10)));
		std::stringstream CollisionBoxNum;
		CollisionBoxNum << i;
		BoxCollision_[i] = CreateCollision(CollisionBoxNum.str(), {148, 116});

	}


	//��ġ �ʱ�ȭ
	std::map<int, InventroyBox*>::iterator StartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator EndIter = Box_.end();

	for (int y = 0; y < 3; ++y) {

		float BoxMargin = 0.f;

		if (y > 0) {
			BoxMargin = 10.f;
		}

		for (int x = 0; x < 12; ++x)
		{
			StartIter->second->SetPosition({ (GetPosition().x - 352.f) + (64.f * x), (GetPosition().y - 200.f) + (64.f * y + BoxMargin) });
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