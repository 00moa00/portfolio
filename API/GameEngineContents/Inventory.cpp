#include "Inventory.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <sstream>


enum class UPDATE {
	POPUPINIT,
	POPUP,
	POPDOWN
};

Inventory::Inventory() 
	:
	BoxCollision_{nullptr},
	WildHorseradish_(nullptr),
	InventoryExit_(nullptr),
	Mouse_(nullptr),
	ItemCount_(0),
	UpdateState_(0),
	PlayerItemListStartIter(PlayerItemList_.begin()),
	PlayerItemListEndIter(PlayerItemList_.end()),
	BoxStartIter(Box_.begin()),
	BoxEndIter(Box_.end()),

	MoveState_(ITEMMOVE::INIT)
{
}


Inventory::~Inventory() 
{
	Box_.clear();
	PlayerItemList_.clear();
}

void Inventory::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	Inventroy_ = CreateRenderer("inventory.bmp");
	Mouse_ = GetLevel()->CreateActor<Mouse>(static_cast<int>(PLAYLEVEL::MOUSE));
	InventoryExit_ = GetLevel()->CreateActor<InventoryExit>(static_cast<int>(PLAYLEVEL::ITEM));
	BoxInit();

	float4 Position;
	Position.x = this->GetPosition().x + (Inventroy_->GetScale().x / 2) + 25.f;
	Position.y = this->GetPosition().y + (Inventroy_->GetScale().y / 2) - 25.f;
	InventoryExit_->SetPosition({ Position.x ,Position.y });
	
	WildHorseradish2_ = NewItem<WildHorseradish>();

	WildHorseradish_ = NewItem<WildHorseradish>();
}


void Inventory::BoxInit()
{
	for (int i = 0; i < INVENTORY_MAX_COUNT; i++) {

		Box_.insert(std::make_pair(i,
			GetLevel()->CreateActor<InventroyBox>(static_cast<int>(PLAYLEVEL::INVENTROYBOX))));
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

			//TODO : ī��Ʈ �ʿ���� �����ϱ�.
			StartIter->second->CreateBoxCollision(count);
			count++;
			StartIter++;
		}

	}
}

void Inventory::ItemSetPos()
{

	std::map<int, Items*>::iterator IterEndIter = PlayerItemList_.end();

	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	for (; BoxStartIter != BoxEndIter; ++BoxStartIter) {
		std::map<int, Items*>::iterator IterFindIter = PlayerItemList_.find(BoxStartIter->first);

		if (IterFindIter == IterEndIter) {
			continue;
		}

		//���� ��� ����� �ٸ���.
		if (IterFindIter->second->GetItemType() == ITEMTYPE::TOOL) {

			float4 Pos = { BoxStartIter->second->GetPosition().x, BoxStartIter->second->GetPosition().y + 24.f };
			IterFindIter->second->SetPosition(Pos);

		}

		else {

			IterFindIter->second->SetPosition(BoxStartIter->second->GetPosition());

		}

	}
}

void Inventory::AllUpdateOff()
{
	this->Off();

	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	for (; BoxStartIter != BoxEndIter; ++BoxStartIter) {
		BoxStartIter->second->Off();
	}


	std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();

	for (; ItemStartIter != ItemEndIter; ++ItemStartIter) {
		ItemStartIter->second->Off();
	}

	InventoryExit_->Off();

}


void Inventory::AllUpdateOn()
{
	this->On();

	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	for (; BoxStartIter != BoxEndIter; ++BoxStartIter) {
		BoxStartIter->second->On();
	}

	std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();

	for (; ItemStartIter != ItemEndIter; ++ItemStartIter) {
		ItemStartIter->second->On();
	}

	InventoryExit_->On();

}


void Inventory::Update()
{


	//Ű�� �����
	std::map<int, Items*>::iterator Finditer;


	//TODO: ����Ǵ� ������, �÷��� ���߿� �������� ������� ����Ʈ�� ����Ǹ鼭 ���ͷ����͵� �ٲ��?

	switch (MoveState_)
	{
	case ITEMMOVE::INIT:

		PlayerItemListStartIter = PlayerItemList_.begin();
		PlayerItemListEndIter = PlayerItemList_.end();

		BoxStartIter = Box_.begin();
		BoxEndIter = Box_.end();


		MoveState_ = ITEMMOVE::NOTACT;

		break;

	case ITEMMOVE::NOTACT:

		//�������� �ڽ��� ��ġ�� ������ ����
		ItemSetPos();


		//�������� ���콺�� �浹�߰� Ŭ���ߴٸ� Ȧ��
		if (PlayerItemListStartIter->second->MouseOver() && Mouse_->isMouseClick()) {

			PlayerItemListStartIter->second->SetInBox(true);

			MoveState_ = ITEMMOVE::HOLD;
			break;
		}

		++PlayerItemListStartIter;

		if (PlayerItemListStartIter == PlayerItemListEndIter) {
			PlayerItemListStartIter = PlayerItemList_.begin();
		}

		break;

	case ITEMMOVE::HOLD:

		//�������� ���콺�� ��ġ�� ����
		PlayerItemListStartIter->second->SetPosition(Mouse_->GetPosition());
		PlayerItemListStartIter->second->MouseHoldItem();


		//���콺�� �ٽ� �ѹ� Ŭ���߰�, ���콺�� �κ��丮 �ڽ� �ȿ� ������ �����ֱ� �õ�
		//TODO : �ڽ� �ۿ��� �����ַ������� ���� �ڸ��� ���ư��� �ϱ�.
		//TODO : �������� �ִ� ��ġ���� ����ִ� ������ �����ϱ�

		if ((Mouse_->isMouseClick() && Mouse_->MouseInBox()))
		{

			BoxStartIter = Box_.begin();
			BoxEndIter = Box_.end();

			for (; BoxStartIter != BoxEndIter; ++BoxStartIter)
			{

				if (BoxStartIter->second->MouseOver()) {

					//������ġ�� �������� �ش� �ڽ� �ȿ� �ִٸ� �Ѿ�� �ʴ´�.

					Finditer = PlayerItemList_.find(BoxStartIter->first);

					//�ش� ��ġ�� �������� ���ٸ� 
					if (Finditer == PlayerItemListEndIter) {

						MoveState_ = ITEMMOVE::FREE;
						continue;
					}

					 if (Finditer->second->GetInBox()) {

						MoveState_ = ITEMMOVE::HOLD;
					}

				}
			}
		}

		break;


	case ITEMMOVE::FREE:

		BoxStartIter = Box_.begin();
		BoxEndIter = Box_.end();

		for (; BoxStartIter != BoxEndIter; ++BoxStartIter)
		{

			//���콺�� �浹�� �κ��丮 �ڽ��� ã�Ƽ� �� �ڽ��� ��ġ�� �������� �ִ´�.
			if (BoxStartIter->second->MouseOver()) {

					PlayerItemListStartIter->second->SetInBox(false);

					//Ű�� ����
					Finditer = PlayerItemListStartIter;
					std::swap(PlayerItemList_[BoxStartIter->first], Finditer->second);

					PlayerItemList_.erase(Finditer);

					MoveState_ = ITEMMOVE::INIT;
			//	}
			}
		}
		break;


	default:

		break;
	}

}

void Inventory::Render()
{
}

