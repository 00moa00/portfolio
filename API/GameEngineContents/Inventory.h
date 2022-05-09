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
#include "PlayerPreview.h"
#include "PlayerCustomClothes.h"


//�⺻ ������
#include "Hoe.h"
#include "EmptyItem.h"
#include "Axe.h"
#include "Pickaxe.h"
#include "Watering_Can.h"
#include "Parsnip_Seeds.h"
#include "Swoard.h"

#include "FarmTotem.h"
#include "MineTotem.h"



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
	MINE,
	SWAP,
	SHOPPING
};

enum class POPUPSTATE 
{
	INIT,
	MINI,
	MAIN,
	SHOP,
	OFF
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

	static Inventory* MainInventory;
	static ExitBotton* MainExitBotton;

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
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


private:

	void ItemMove();
	void InvenPopUp();
	void BoxInit();
	void InventoryPosInit();
	void ItemPosFocusInvenBox();
	void CurrentItemFrameFocusBox();

public:

	std::map<int, Items*> PlayerItemList_;
	std::map<int, InventroyBox*> Box_;
	

private:

	Mouse* Mouse_;								//�浹�� ���콺
	PlayerPreview* PlayerPreview_;				//���� Ŀ���� ����
	PlayerCustomClothes* PlayerCustomClothes_;	//���� Ŀ���� �ǻ�

	GameEngineRenderer* Inventory_;				//�κ��丮 ����(�޴� ����)

	InventoryCurrentFrame* CurrentItemFrame_;	//���� �������� ����Ű�� ������
	Items* CurrentItem_;						//���� �����ϰ� �ִ� ������



	Hoe* Hoe_;					//�ʱ� ���� ������ ��Ͽ�
	EmptyItem* EmptyItem_;		//�� ������

	ITEMMOVE MoveState_;			//���� ���¿��� �����̴� 
	POPUPSTATE PopUpState_;			//���ۿ� ���� �˾� ����
	POPUPSTATE CurrentInvenState_;	//���� �˾� ����, �ٱ� üũ��. ���� ������ idle�̱⶧���� Ȯ���ϱ� ��ƴ�.
	INVEN_UPDATE UpdateState_;		//���� ������Ʈ ����

	std::map<int, Items*>::iterator PlayerItemListStartIter;
	std::map<int, Items*>::iterator PlayerItemListEndIter;

	std::map<int, Items*>::iterator FindCurrentItemIter;

	std::map<int, InventroyBox*>::iterator BoxStartIter;
	std::map<int, InventroyBox*>::iterator BoxEndIter;

private:

	void SetCurrentItemFrame(Items* item_, InventroyBox* box_);
	void SetCurrentItemFrame(Items* item_);
	void SetCurrentItemFrame(InventroyBox* box_);

public:

	void AllUpdateOff();
	void AllUpdateOn();


	//================================
	//     Getter
	//================================

	std::map<int, Items*>::iterator FindPlayerListByValue(std::string ItemName)
	{
		std::map<int, Items*>::iterator StartIter = PlayerItemList_.begin();
		std::map<int, Items*>::iterator EndIter = PlayerItemList_.end();
		
		for (; StartIter != EndIter; ++StartIter)
		{
			if (StartIter->second->GetItemNameConstRef() == ItemName)
			{
				return StartIter;
			}
		}

		if (StartIter == EndIter)
		{
			return EndIter;
		}
	}

	Items* GetCurrentItem()
	{
		if (CurrentItem_ != nullptr)
		{
			return CurrentItem_;
		}

		else
		{
			return nullptr;
		}
	}

	Mouse* GetMouse()
	{
		return Mouse_;
	}

	bool GetCurrentItemEmpty()
	{
		return CurrentItem_ == EmptyItem_ && CurrentItem_ != nullptr;
	}

	bool GetPopUpStateShop()
	{
		return CurrentInvenState_ == POPUPSTATE::SHOP;
	}


	bool GetPopUpStateMini()
	{
		return CurrentInvenState_ == POPUPSTATE::MINI;
	}

	bool GetPopUpStateMain()
	{
		return CurrentInvenState_ == POPUPSTATE::MAIN;
	}

	bool ExitBottonMouseClick()
	{
		return MainExitBotton->MouseClick();
	}

	//================================
	//    Setter
	//================================

	void SetCurrentItem(Items* _SetItem)
	{
		CurrentItem_ = _SetItem;
	}

	void SetCurrentItemEmpty()
	{
		CurrentItem_ = EmptyItem_;
	}


	void SetCurrentItemParsnipSeed()
	{
		std::map<int, Items*>::iterator StartIter;
		std::map<int, Items*>::iterator EndIter;

		for (; StartIter != EndIter; ++StartIter)
		{
			if (StartIter->second->GetItemNameConstRef() == "Parsnip_Seeds")
			{
				CurrentItem_ = StartIter->second;

			}
		}

	}

	void SetPopUpStateMini()
	{
		PopUpState_ = POPUPSTATE::MINI;
	}

	void SetInventoryMoveStateInit()
	{
		MoveState_ = ITEMMOVE::INIT;
	}


	void FindAndErasePlayerItemList(std::string ItemName)
	{
		SetInventoryMoveStateInit();

		std::map<int, Items*>::iterator StartIter = PlayerItemList_.begin();
		std::map<int, Items*>::iterator EndIter = PlayerItemList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (StartIter->second->GetItemNameConstRef() == ItemName)
			{
				PlayerItemList_.erase(StartIter->first);
				return;
			}
		}

		if (StartIter == EndIter)
		{
			return;
		}

		CurrentItem_ = EmptyItem_;

	}

	
	void SetMiniInven(POPUPSTATE b)
	{
		PopUpState_ = b;
	}


	template<typename Actor>
	Actor* NewItem(float4 _AddPos = { 0, 0 })
	{
		Actor* Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::ITEM));


		//������ �ִ� �������̶�� ī�����Ѵ�.

		std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
		std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();

		for (; ItemStartIter != ItemEndIter; ++ItemStartIter) 
		{
			if (ItemStartIter->second->GetItemNameConstRef() == Item->GetItemNameConstRef())
			{
				ItemStartIter->second->AddItemCount();
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
		Item->GetRenderer()->CameraEffectOff();

		//++ItemCount_;
		return Item;
	}


	template<typename Actor>
	Actor* NewItem(int _Count)
	{
		Actor* Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::ITEM));

		//������ �ִ� �������̶�� ī�����Ѵ�.

		std::map<int, Items*>::iterator ItemStartIter = PlayerItemList_.begin();
		std::map<int, Items*>::iterator ItemEndIter = PlayerItemList_.end();

		for (; ItemStartIter != ItemEndIter; ++ItemStartIter)
		{
			if (ItemStartIter->second->GetItemNameConstRef() == Item->GetItemNameConstRef())
			{
				Item->SetItemCount(_Count);
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

		Item->SetPosition({ Pos});
		Item->GetRenderer()->CameraEffectOff();
		Item->SetItemCount(_Count);
		return Item;
	}
};

