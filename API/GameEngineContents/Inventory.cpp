#include "Inventory.h"
#include "Player.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <sstream>

//

Inventory* Inventory::MainInventory = nullptr;

enum class UPDATE {
	POPUPINIT,
	POPUP,
	POPDOWN
};

Inventory::Inventory()
	:
	
	Inventory_(nullptr),
	ExitBotton_(nullptr),
	Mouse_(nullptr),
	CurrentItem_(nullptr),
	Hoe_(nullptr),
	CurrentItemFrame_(nullptr),

	CurrentInvenState_(POPUPSTATE::INIT),
	PopUpState_(POPUPSTATE::MINI),
	MoveState_(ITEMMOVE::INIT),
	UpdateState_(INVEN_UPDATE::INIT)

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

	Inventory_ = CreateRenderer("inventory.bmp");
	Inventory_->CameraEffectOff();

	CurrentItemFrame_ = GetLevel()->CreateActor<InventoryCurrentFrame>(static_cast<int>(PLAYLEVEL::CURRENTITEM));
	Mouse_ = GetLevel()->CreateActor<Mouse>(static_cast<int>(PLAYLEVEL::MOUSE));
	ExitBotton_ = GetLevel()->CreateActor<ExitBotton>(static_cast<int>(PLAYLEVEL::ITEM));

	BoxInit();


	Hoe_ = NewItem<Hoe>();
	NewItem<Watering_Can>();
	NewItem<Axe>();
	NewItem<Pickaxe>();
	NewItem<WildHorseradish>();
	NewItem<Parsnip_Seeds>();
	NewItem<Parsnip_Seeds>();


	
	float4 Position;
	Position.x = Inventory_->GetScale().x  + 250.f;
	Position.y = Inventory_->GetScale().y  + 50.f;
	ExitBotton_->SetPosition({ Position.x ,Position.y });
	
	LevelRegist("MainInventory");
}



void Inventory::Update()
{
	switch (UpdateState_)
	{
	case INVEN_UPDATE::INIT:


		InventoryPosInit();
		ItemPosFocusInvenBox();

		CurrentItem_ = Hoe_;
		CurrentItemFrame_->SetPosition(CurrentItem_->GetPosition());

		UpdateState_ = INVEN_UPDATE::UPDATE;
		break;

	case INVEN_UPDATE::UPDATE:
		//�������� �ڽ��� ��ġ�� ������ ����
		//ItemPosFocusInvenBox();
		InvenPopUp();
		ItemMove();

		break;
	default:
		break;
	}



}

void Inventory::Render()
{

}

void Inventory::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainInventory = this;
	
}

void Inventory::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();

	for (; ItemStartIter != ItemEndIter; ++ItemStartIter)
	{
		ItemStartIter->second->NextLevelOn();
	}

	std::map<int, InventroyBox*>::iterator StartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator EndIter = Box_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		StartIter->second->NextLevelOn();
	}

	CurrentItemFrame_->NextLevelOn();
	Mouse_->NextLevelOn();
	NextLevelOn();

}


void Inventory::BoxInit()
{
	for (int i = 0; i < INVENTORY_MAX_COUNT; i++) 
	{
		Box_.insert(std::make_pair(i, GetLevel()->CreateActor<InventroyBox>(static_cast<int>(PLAYLEVEL::INVENTROYBOX))));
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
	int BoxXMargin = 0;

	for (; StartIter != EndIter; ++StartIter)
	{
		if (StartIter->first == 12) 
		{
			BoxMargin = 10.f;
			BoxYMargin = 1;
			BoxXMargin = 0;
		}

		if (StartIter->first == 24) 
		{
			BoxYMargin = 2;
			BoxXMargin = 0;
		}

		StartIter->second->SetPosition({ (GetPosition().x - 352.f) + (64.f * BoxXMargin), (GetPosition().y - 200.f) + (64.f * BoxYMargin + BoxMargin) });
		
		//�ڽ� �浹ü
		if (StartIter->second->BoxCollision() == nullptr) 
		{
			StartIter->second->CreateBoxCollision(StartIter->first);
		}

		++BoxXMargin;
	}
}

void Inventory::ItemPosFocusInvenBox()
{

	std::map<int, Items*>::iterator IterEndIter = PlayerItemList_.end();

	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	for (; BoxStartIter != BoxEndIter; ++BoxStartIter) 
	{
		std::map<int, Items*>::iterator IterFindIter = PlayerItemList_.find(BoxStartIter->first);

		if (IterFindIter == IterEndIter) 
		{
			continue;
		}

		//���� ��� ����� �ٸ���.
		if (IterFindIter->second->GetItemType() == ITEMTYPE::TOOL) 
		{
			float4 Pos = { BoxStartIter->second->GetPosition().x, BoxStartIter->second->GetPosition().y + 24.f };
			IterFindIter->second->SetPosition(Pos);

		}

		else 
		{
			IterFindIter->second->SetPosition(BoxStartIter->second->GetPosition());

		}
		
	}
}

void Inventory::AllUpdateOff()
{

	this->Off();

	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	for (; BoxStartIter != BoxEndIter; ++BoxStartIter) 
	{
		BoxStartIter->second->Off();
	}


	std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();

	for (; ItemStartIter != ItemEndIter; ++ItemStartIter)
	{
		ItemStartIter->second->Off();
	}

	ExitBotton_->Off();

}


void Inventory::AllUpdateOn()
{
	this->On();

	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	for (; BoxStartIter != BoxEndIter; ++BoxStartIter)
	{
		BoxStartIter->second->On();
	}

	std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();

	for (; ItemStartIter != ItemEndIter; ++ItemStartIter) 
	{
		ItemStartIter->second->On();
	}

	ExitBotton_->On();

}

void Inventory::SetCurrentItemFrame(Items* item_, InventroyBox* box_)
{
	if (item_->GetItemType() == ITEMTYPE::TOOL)
	{
		float4 Pos = { box_->GetPosition().x, box_->GetPosition().y  };
		CurrentItemFrame_->SetPosition(Pos);
	}

	else 
	{
		CurrentItemFrame_->SetPosition({ box_->GetPosition().x,  box_->GetPosition().y });
	}

}

void Inventory::SetCurrentItemFrame(Items* item_)
{

	if (item_->GetItemType() == ITEMTYPE::TOOL)
	{

		float4 Pos = { item_->GetPosition().x, item_->GetPosition().y - 24.f };
		CurrentItemFrame_->SetPosition(Pos);
	}

	else 
	{
		CurrentItemFrame_->SetPosition({ item_->GetPosition().x,  item_->GetPosition().y });
	
	}

}

void Inventory::SetCurrentItemFrameChange(InventroyBox* box_)
{

	if (CurrentItem_ != nullptr) {

		if (CurrentItem_->GetItemType() == ITEMTYPE::TOOL) 
		{

			float4 Pos = { CurrentItemFrame_->GetPosition().x, box_->GetPosition().y};
			CurrentItemFrame_->SetPosition(Pos);
		}

		else 
		{
			CurrentItemFrame_->SetPosition({ CurrentItemFrame_->GetPosition().x,  box_->GetPosition().y });

		}
	}

}

void Inventory::ItemMove()
{
	//Ű�� �����
	std::map<int, Items*>::iterator Finditer;
	std::map<int, InventroyBox*>::iterator FindBoxiter;


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

		ItemPosFocusInvenBox();

		for (; PlayerItemListStartIter != PlayerItemListEndIter; ++PlayerItemListStartIter)
		{

			if (PlayerItemListStartIter->second->MouseOver() && Mouse_->isMouseClick())
			{

				//�����϶� �÷��̾� ���� ���� ����.
				if (Player::MainPlayer->GetPlayerShoppingStateShopping())
				{
					if ((PlayerItemListStartIter->second->GetItemType() == ITEMTYPE::TOOL))
					{
						MoveState_ = ITEMMOVE::INIT;
						break;
					}

					MoveState_ = ITEMMOVE::SHOPPING;
					break;
				}

				//���� ������ ������, ���� ������ ����
				SetCurrentItemFrame(PlayerItemListStartIter->second);
				CurrentItem_ = PlayerItemListStartIter->second;
				//FindCurrentItemIter

				//�̴� ���¿��� ���� �̵��� �� ����.
				if ((CurrentInvenState_ == POPUPSTATE::MINI) &&
					(PlayerItemListStartIter->second->GetItemType() == ITEMTYPE::TOOL))
				{
					PlayerItemListStartIter->second->SetInBox(false);
					MoveState_ = ITEMMOVE::INIT;
					break;
				}


				PlayerItemListStartIter->second->SetInBox(false);
				MoveState_ = ITEMMOVE::HOLD;
				break;
			}

		}

		if (PlayerItemListStartIter == PlayerItemListEndIter)
		{
			PlayerItemListStartIter = PlayerItemList_.begin();
		}


		break;

	case ITEMMOVE::HOLD:

		//�������� ���콺�� ��ġ�� ����
		PlayerItemListStartIter->second->SetPosition({Mouse_->GetPosition().x + 24.f, Mouse_->GetPosition().y + 30.f });
		PlayerItemListStartIter->second->MouseHoldItem();

		//�κ��丮 �ۿ� Ŭ���ߴٸ� 
		if (Mouse_->MouseClickInventoryOut())
		{
			MoveState_ = ITEMMOVE::MINE;
		}

		//���콺�� �ٽ� �ѹ� Ŭ���߰�, ���콺�� �κ��丮 �ڽ� �ȿ� ������ �����ֱ� �õ�
		if (Mouse_->MouseClickAndItemColl())
		{
			BoxStartIter = Box_.begin();
			BoxEndIter = Box_.end();

			for (; BoxStartIter != BoxEndIter; ++BoxStartIter)
			{

				if (BoxStartIter->second->MouseOver())
				{

					//������ġ�� �������� �ش� �ڽ� �ȿ� �ִٸ� �Ѿ�� �ʴ´�.
					Finditer = PlayerItemList_.find(BoxStartIter->first);

					//�ش� ��ġ�� �������� ���ٸ� 
					if (Finditer == PlayerItemListEndIter)
					{
						SetCurrentItemFrame(PlayerItemListStartIter->second, BoxStartIter->second);
						MoveState_ = ITEMMOVE::FREE;
						continue;
					}

					//�������� �ڸ��� �������� �ִٸ�
					if (Finditer->second->GetInBox())
					{
						MoveState_ = ITEMMOVE::HOLD;
					}

					//���� �ڸ��� �״�� �ִ´ٸ�
					if (Finditer->first == PlayerItemListStartIter->first)
					{
						SetCurrentItemFrame(PlayerItemListStartIter->second, BoxStartIter->second);
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
			if (BoxStartIter->second->MouseOver())
			{

				PlayerItemListStartIter->second->SetInBox(true);

				//Ű�� ����
				Finditer = PlayerItemListStartIter;
				std::swap(PlayerItemList_[BoxStartIter->first], Finditer->second);

				PlayerItemList_.erase(Finditer);

				MoveState_ = ITEMMOVE::INIT;
			}
		}
		break;

	case ITEMMOVE::MINE:

		FindBoxiter = Box_.find(PlayerItemListStartIter->first);
		PlayerItemListStartIter->second->SetPosition(FindBoxiter->second->GetPosition());

		MoveState_ = ITEMMOVE::INIT;
		break;


	case ITEMMOVE::SHOPPING:

		Player::MainPlayer->AddMoney(PlayerItemListStartIter->second->GetSellPrice());
		PlayerItemListStartIter->second->SubItemCount();


		MoveState_ = ITEMMOVE::INIT;


	default:

		break;
	}
}

void Inventory::InvenPopUp()
{

	if ((CurrentInvenState_ == POPUPSTATE::MINI)
		&& true == GameEngineInput::GetInst()->IsDown("Enter"))
	{
		PopUpState_ = POPUPSTATE::MAIN;
	}

	if (((CurrentInvenState_ == POPUPSTATE::MAIN) 
		&& true == GameEngineInput::GetInst()->IsDown("Enter")) || (ExitBotton_->MouseClick()))
	{
		PopUpState_ = POPUPSTATE::MINI;
	}

	//Player* MainPlayer = GetLevel()->FindActor<Player>("MainPlayer");

	if (Player::MainPlayer->GetisShopping())
	{
		PopUpState_ = POPUPSTATE::SHOP;
	}


	if (Player::MainPlayer->GetPlayerShoppingState() == PLAYER_SHOPPING::SHOP_OFF)
	{
		PopUpState_ = POPUPSTATE::MINI;
	}



	std::map<int, InventroyBox*>::iterator BoxStartIter = Box_.begin();
	std::map<int, InventroyBox*>::iterator BoxEndIter = Box_.end();

	std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
	std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();


	int BoxXMargin = 0;

	switch (PopUpState_)
	{
	case POPUPSTATE::INIT :

		break;

	case POPUPSTATE::MINI:

		CurrentInvenState_ = POPUPSTATE::MINI;

		ExitBotton_->Off();
		CurrentItemFrame_->On();
		Inventory_->On();

		Inventory_->SetImage("MiniInven.bmp");
		SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y+300.f });
		
		for (; BoxStartIter != BoxEndIter; ++BoxStartIter) 
		{
			BoxStartIter->second->SetPosition({ (this->GetPosition().x - 352.f) + (64.f * BoxXMargin), (this->GetPosition().y) });
			if (BoxStartIter->first == 0) 
			{
				SetCurrentItemFrameChange(BoxStartIter->second);
			}
			
			++BoxXMargin;

			if (BoxStartIter->first > 11)
			{
				BoxStartIter->second->Off();
			}
		}


		for (; ItemStartIter != ItemEndIter; ++ItemStartIter) 
		{
			if (ItemStartIter == ItemEndIter)
			{
				continue;
			}

			if (ItemStartIter->first > 11)
			{
				ItemStartIter->second->Off();
			}
		}

	
		PopUpState_ = POPUPSTATE::INIT;

		break;

	case POPUPSTATE::MAIN:

		CurrentInvenState_ = POPUPSTATE::MAIN;
		ExitBotton_->On();
		CurrentItemFrame_->Off();

		SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y});
		Inventory_->SetImage("inventory.bmp");


		for (; ItemStartIter != ItemEndIter; ++ItemStartIter)
		{
			if (ItemStartIter == ItemEndIter)
			{
				continue;
			}

			ItemStartIter->second->On();
		}

		for (; BoxStartIter != BoxEndIter; ++BoxStartIter)
		{
			BoxStartIter->second->On();
		}


		InventoryPosInit();

		PopUpState_ = POPUPSTATE::INIT;
		break;

	case POPUPSTATE::SHOP:

		CurrentInvenState_ = POPUPSTATE::SHOP;
		ExitBotton_->Off();
		CurrentItemFrame_->Off();
		Inventory_->Off();

		for (; ItemStartIter != ItemEndIter; ++ItemStartIter)
		{
			if (ItemStartIter == ItemEndIter) 
			{
				continue;
			}

			ItemStartIter->second->On();
		}

		for (; BoxStartIter != BoxEndIter; ++BoxStartIter)
		{
			BoxStartIter->second->On();

		}


		std::map<int, InventroyBox*>::iterator StartIter = Box_.begin();
		std::map<int, InventroyBox*>::iterator EndIter = Box_.end();

		int BoxYMargin = 0;
		int BoxXMargin = 0;

		for (; StartIter != EndIter; ++StartIter)
		{
			if (StartIter->first == 12)
			{
				BoxYMargin = 1;
				BoxXMargin = 0;
			}

			if (StartIter->first == 24)
			{
				BoxYMargin = 2;
				BoxXMargin = 0;
			}

			StartIter->second->SetPosition({ (362.f) + (64.f * BoxXMargin), (459.f) + (64.f * BoxYMargin ) });

			++BoxXMargin;
		}

		PopUpState_ = POPUPSTATE::INIT;
		break;

	}


}


