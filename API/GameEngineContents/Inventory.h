#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>

#include "MenuExit.h"
#include "InventroyBox.h"
#include "WildHorseradish.h"
#include "RendererData.h"
#include "InventoryCurrentFrame.h"
#include "Mouse.h"
#include "Player.h"
#include "ExitBotton.h"
#include "Items.h"


//�⺻ ������
#include "Hoe.h"
#include "Axe.h"
#include "Pickaxe.h"
#include "Watering_Can.h"
#include "Parsnip_Seeds.h"


#include  <vector>
#include <map>
#include <memory>

enum class ITEMMOVE 
{
	INIT,
	NOTACT,
	ADDITER,
	HOLD,
	FREE,
	MINE
};

enum class POPUPSTATE 
{
	INIT,
	MINI,
	MAIN,
	SHOP
};

enum class INVEN_UPDATE
{
	INIT,
	UPDATE,
};

//#pragma warning(disable : 4267)
#define INVENTORY_MAX_COUNT 36

// ���� :
class Inventory : public GameEngineActor
{

public:

	//static Inventory* MainInventory;
	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	//Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;
	void Render() override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:

	void ItemMove();
	void InvenPopUp();
	void BoxInit();
	void InventoryPosInit();
	void ItemPosFocusInvenBox();

public:

	//Inventory& operator= (const Inventory& other)
	//{

	//	if (0 < other.PlayerItemList_.size())
	//	{
	//		PlayerItemList_.insert(other.PlayerItemList_.begin(), other.PlayerItemList_.end());
	//	}

	//	if (0 < other.Box_.size())
	//	{
	//		Box_.insert(other.Box_.begin(), other.Box_.end());
	//	}

	//	//CurrentItemFrame_ = other.CurrentItemFrame_;
	//	//CurrentItem_ = other.CurrentItem_;

	//	UpdateState_ = INVEN_UPDATE::INIT;
	//	MoveState_ = ITEMMOVE::INIT;
	//	PopUpState_ = POPUPSTATE::MINI;
	//	CurrentInvenState_ = POPUPSTATE::INIT;


	//	return *this;
	//}


	template<typename Actor>
	Actor* NewItem(float4 _AddPos = {0, 0})
	{
		Actor* Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::ITEM));


		//������ �ִ� �������̶�� �����ϰ� ī�����Ѵ�.

		std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();

		std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();

		for (; ItemStartIter != ItemEndIter; ++ItemStartIter) {
			if (ItemStartIter->second->GetItemNameConstRef() == Item->GetItemNameConstRef())
			{
				ItemStartIter->second->SetItemStateAddItem();
				Item->Death();
				return nullptr;
			}
		}


		//������ ����

		std::map<int, InventroyBox*>::iterator StartIter = Box_.begin();
		std::map<int, InventroyBox*>::iterator EndIter = Box_.end();

		//�տ������� Ž���ؼ� �ڽ��� �������� ������ �� �ڸ��� �ֱ�

		int index_ = 0;

		for (int i = 0; StartIter != EndIter; ++i) {

			std::map<int, Items*>::iterator ItemFindIter = PlayerItemList_.find(i);
			if (ItemFindIter == PlayerItemList_.end())
			{
				index_ = StartIter->first;
				break;
			}
			else
			{
				++StartIter;
			}

		}

		//�÷��̾� �����۸���Ʈ�� �߰�
		PlayerItemList_.insert(std::make_pair(index_, Item));

		//�ڽ��� ��ġ�� ã�Ƽ� ���
		std::map<int, InventroyBox*>::iterator FindIter = Box_.find(static_cast<const int>(index_));
		float4 Pos = FindIter->second->GetPosition();

		Item->SetPosition({ Pos + _AddPos });
		Item -> GetRenderer()->CameraEffectOff();

		//++ItemCount_;
		return Item;
	}


	void AllUpdateOff();

	void AllUpdateOn();

	bool ExitBottonMouseClick() {
		return ExitBotton_->MouseClick();
	}

	void SetMiniInven(POPUPSTATE b) {
		PopUpState_ = b;
	}


	void SetCurrentItemFrame(Items* item_, InventroyBox* box_);
	void SetCurrentItemFrame(Items* item_);

	void SetCurrentItemFrameChange(InventroyBox* box_);

	Items* CurrentItem() {
		return CurrentItem_;
	}

	Items& CurrentItemLef() {
		return *CurrentItem_;
	}

	//bool GetisMiniInven() {
	//	return isMiniInven_;
	//}


private:
	
	std::map<int, Items*> PlayerItemList_;
	std::map<int, InventroyBox*> Box_;



	std::map<int, Items*>::iterator PlayerItemListStartIter;
	std::map<int, Items*>::iterator PlayerItemListEndIter;

	std::map<int, InventroyBox*>::iterator BoxStartIter;
	std::map<int, InventroyBox*>::iterator BoxEndIter;


	InventoryCurrentFrame* CurrentItemFrame_;

	GameEngineRenderer* Inventory_;
	// GameEngineCollision* BoxCollision_[INVENTORY_MAX_COUNT];
	Items* CurrentItem_;

	//bool isMiniInven_;


	//int ItemCount_;
	Mouse* Mouse_;
	ExitBotton* ExitBotton_;

	Hoe* Hoe_;
	Watering_Can* Watering_Can_;
	Axe* Axe_;
	Pickaxe* Pickaxe_;

	WildHorseradish* WildHorseradish_;
	Parsnip_Seeds* Parsnip_Seeds_;

	ITEMMOVE MoveState_;
	POPUPSTATE PopUpState_;
	POPUPSTATE CurrentInvenState_;
	INVEN_UPDATE UpdateState_;
};

