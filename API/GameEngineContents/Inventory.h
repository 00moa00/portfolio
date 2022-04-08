#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>

#include "MenuExit.h"
#include "InventroyBox.h"
#include "WildHorseradish.h"
#include "RendererEnum.h"

#include "Mouse.h"
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
	FREE
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

	void BoxInit();
	void ItemSetPos();
public:

	template<typename Actor>
	Actor* NewItem(float4 _AddPos = {0, 0})
	{
		Actor* Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::ITEM));



		//
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


private:
	
	std::map<int, Items*> PlayerItemList_;
	std::map<int, InventroyBox*> Box_;

	std::map<int, Items*>::iterator PlayerItemListStartIter;
	std::map<int, Items*>::iterator PlayerItemListEndIter;
	//std::map<int, Items*>::iterator ItemHoldIter;

	std::map<int, InventroyBox*>::iterator BoxStartIter;
	std::map<int, InventroyBox*>::iterator BoxEndIter;

	//std::map<int, Items*>::iterator ItemHoldStartIter;
	//std::map<int, Items*>::iterator ItemHoldEndIter;


	GameEngineRenderer* Inventroy_;
	GameEngineCollision* BoxCollision_[INVENTORY_MAX_COUNT];
	

	int ItemCount_;
	Mouse* Mouse_;
	InventoryExit* InventoryExit_;

	WildHorseradish* WildHorseradish_;
	WildHorseradish* WildHorseradish2_;

	int UpdateState_;
	ITEMMOVE MoveState_;


};

