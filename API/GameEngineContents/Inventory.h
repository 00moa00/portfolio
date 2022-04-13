#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>

#include "MenuExit.h"
#include "InventroyBox.h"
#include "WildHorseradish.h"
#include "RendererEnum.h"
#include "InventoryCurrentFrame.h"
#include "Mouse.h"
#include "Player.h"
#include "InventoryExit.h"
#include "Items.h"
#include  <vector>
#include <map>
#include <memory>

enum class ITEMMOVE {
	INIT,
	NOTACT,
	ADDITER,
	HOLD,
	FREE,
	MINE
};

enum class MINIPOPUP {
	INIT,
	MINI,
	MAIN
};

//#pragma warning(disable : 4267)
#define INVENTORY_MAX_COUNT 36

// ���� :
class Inventory : public GameEngineActor
{

public:

	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:

	void InvenPopUp();
	void BoxInit();
	void InventoryPosInit();
	void ItemPosFocusInvenBox();
public:

	template<typename Actor>
	Actor* NewItem(float4 _AddPos = {0, 0})
	{
		Actor* Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::ITEM));

		std::map<int, InventroyBox*>::iterator StartIter = Box_.begin();
		std::map<int, InventroyBox*>::iterator EndIter = Box_.end();

		//�տ������� Ž���ؼ� �������� ������ �� �ڸ��� �ֱ�
		int index_ = 0;

		for (; StartIter != EndIter; ) {
			if (!StartIter->second->IteminBox()) {
				index_ = StartIter->first;
				StartIter = EndIter;
			}
			if (StartIter != EndIter) { ++StartIter; }
		}

		//�÷��̾� �����۸���Ʈ�� �߰�
		PlayerItemList_.insert(std::make_pair(index_, Item));

		//�ڽ��� ��ġ�� ã�Ƽ� ���
		std::map<int, InventroyBox*>::iterator FindIter = Box_.find(static_cast<const int>(index_));
		float4 Pos = FindIter->second->GetPosition();

		Item->SetPosition({ Pos + _AddPos });
		++ItemCount_;
		return Item;
	}


	void AllUpdateOff();

	void AllUpdateOn();

	bool InventoryExitMouseClick() {
		return InventoryExit_->MouseClick();
	}



	void SetMiniInven(MINIPOPUP b) {
		MiniState_ = b;
	}


	void SetCurrentItemFrame(Items* item_, InventroyBox* box_);
	void SetCurrentItemFrame(Items* item_);

	void SetCurrentItemFrameChange(InventroyBox* box_);

	Items* CurrentItem() {
		return CurrentItem_;
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

	GameEngineRenderer* Inventroy_;
	// GameEngineCollision* BoxCollision_[INVENTORY_MAX_COUNT];
	Items* CurrentItem_;

	bool isMiniInven_;


	int ItemCount_;
	Mouse* Mouse_;
	InventoryExit* InventoryExit_;

	WildHorseradish* WildHorseradish_;
	WildHorseradish* WildHorseradish2_;

	int UpdateState_;
	ITEMMOVE MoveState_;
	MINIPOPUP MiniState_;
	MINIPOPUP CurrentInvenState_;

};

