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
	BoxCollision_{ nullptr },
	WildHorseradish_(nullptr),
	InventoryExit_(nullptr),
	Mouse_(nullptr),
	ItemCount_(0),
	UpdateState_(0),

	MiniState_(MINIPOPUP::MINI),
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


	InventoryPosInit();

}

void Inventory::InventoryPosInit()
{

	//��ġ �ʱ�ȭ
	std::map<int, InventroyBox*>::iterator StartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator EndIter = Box_.end();
	int count = 0;

	int BoxMargin = 0;
	int BoxYMargin = 0;
	float BoxXMargin = 0.f;

	for (; StartIter != EndIter; ++StartIter) {

		if (StartIter->first == 12) {
			BoxMargin = 10.f;
			BoxYMargin = 1;
			BoxXMargin = 0.f;
		}
		if (StartIter->first == 24) {
			//BoxYMargin = 20.f;
			BoxYMargin = 2;

			BoxXMargin = 0.f;
		}

		StartIter->second->SetPosition({ (GetPosition().x - 352.f) + (64.f * BoxXMargin), (GetPosition().y - 200.f) + (64.f * BoxYMargin + BoxMargin) });
		StartIter->second->CreateBoxCollision(StartIter->first);
		++BoxXMargin;
	}
}

void Inventory::ItemPosFocusInvenBox()
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

void Inventory::InvenPopUp()
{

	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();


	int BoxXMargin = 0;

	switch (MiniState_)
	{
	case MINIPOPUP::INIT :

		break;

	case MINIPOPUP::MINI:

		InventoryExit_->Off();


		Inventroy_->SetImage("MiniInven.bmp");
		SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y+300.f });


		for (; BoxStartIter != BoxEndIter; ++BoxStartIter) {
			BoxStartIter->second->SetPosition({ (this->GetPosition().x - 352.f) + (64.f * BoxXMargin), (this->GetPosition().y) });
			++BoxXMargin;

			if (BoxStartIter->first > 11){

				BoxStartIter->second->Off();
			}
		}


		for (; ItemStartIter != ItemEndIter; ++ItemStartIter) {

			if (ItemStartIter == ItemEndIter) {
				continue;
			}

			if (ItemStartIter->first > 11)
				ItemStartIter->second->Off();
		}

		MiniState_ = MINIPOPUP::INIT;

		break;

	case MINIPOPUP::MAIN:

		InventoryExit_->On();

		for (; ItemStartIter != ItemEndIter; ++ItemStartIter) {

			if (ItemStartIter == ItemEndIter) {
				continue;
			}

			ItemStartIter->second->On();
		}

		for (; BoxStartIter != BoxEndIter; ++BoxStartIter) {
			InventoryPosInit();
			BoxStartIter->second->On();
		}
		SetPosition(GameEngineWindow::GetScale().Half());
		Inventroy_->SetImage("inventory.bmp");


		InventoryPosInit();

		MiniState_ = MINIPOPUP::INIT;

		break;

	}


}


void Inventory::Update()
{
	//if (Mouse_->isMouseFree()) {
	//	MoveState_ = ITEMMOVE::INIT;
	//}

	//std::map<int, Items*>::iterator PlayerItemListStartIter = PlayerItemList_.begin();
	//std::map<int, Items*>::iterator PlayerItemListEndIter = PlayerItemList_.end();

	//std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	//std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	//Ű�� �����
	std::map<int, Items*>::iterator Finditer;
	std::map<int, InventroyBox*>::iterator FindBoxiter;

	InvenPopUp();

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
		ItemPosFocusInvenBox();

		for (; PlayerItemListStartIter != PlayerItemListEndIter; ++PlayerItemListStartIter) {


			if (PlayerItemListStartIter->second->MouseOver() && Mouse_->isMouseClick()) {
				PlayerItemListStartIter->second->SetInBox(false);
				MoveState_ = ITEMMOVE::HOLD;
				break;
			}

			
			//break;
		}


		if (PlayerItemListStartIter == PlayerItemListEndIter) {
			PlayerItemListStartIter = PlayerItemList_.begin();
		}


		////�������� ���콺�� �浹�߰� Ŭ���ߴٸ� Ȧ��
		//if (PlayerItemListStartIter->second->MouseOver() && Mouse_->isMouseClick()) {

		//
		//}

		//++PlayerItemListStartIter;

		//if (PlayerItemListStartIter == PlayerItemListEndIter) {
		//	PlayerItemListStartIter = PlayerItemList_.begin();
		//}

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


					 if (Finditer->first == PlayerItemListStartIter->first) {

						 MoveState_ = ITEMMOVE::MINE;
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

					PlayerItemListStartIter->second->SetInBox(true);

					//Ű�� ����
					Finditer = PlayerItemListStartIter;
					std::swap(PlayerItemList_[BoxStartIter->first], Finditer->second);

					PlayerItemList_.erase(Finditer);

					MoveState_ = ITEMMOVE::INIT;
			//	}
			}
		}
		break;

	case ITEMMOVE::MINE :
		
		FindBoxiter = Box_.find(PlayerItemListStartIter->first);

		PlayerItemListStartIter->second->SetPosition(FindBoxiter->second->GetPosition());
		MoveState_ = ITEMMOVE::INIT;

	default:

		break;
	}

}

void Inventory::Render()
{
}

