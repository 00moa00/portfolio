#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>

#include <map>

#include "ShopItem.h"
#include "ExitBotton.h"
#include "Mouse.h"
#include "Font.h"



enum class SHOP
{
	NONE,
	SEED_SHOP,
	SALOON
};

enum class SHOP_UPDATE
{
	WAIT,
	SET_POS_INDEX,
	HIDE_ITME,
	INIT,
	SCROLL_UP,
	SCROLL_DOWN
};

// 설명 :
class Shop : public GameEngineActor
{
public:
	static Shop* MainShop;
	static ExitBotton* ExitBotton_;
	static Font* Font_;

	// constrcuter destructer
	Shop();
	~Shop();

	// delete Function
	Shop(const Shop& _Other) = delete;
	Shop(Shop&& _Other) noexcept = delete;
	Shop& operator=(const Shop& _Other) = delete;
	Shop& operator=(Shop&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

	int ScrollMax_;

	GameEngineRenderer* ShopRenderer_;
	Mouse* Mouse_;

	SHOP Shop_;
	SHOP_UPDATE ShopUpdateState_;

	std::map<int, ShopItem*> CurrentShopItemList_;

	std::map<int, ShopItem*> SeedShopItemList_;
	std::map<int, ShopItem*> SaloonItemList_;

	std::map<int, float4> ConstItmePos_;



public:

	void ShopOff();
	void ShopOn();
	void SetShopMoney(int _Money);

	template<typename Actor>
	void NewSeedShopItem()
	{
		Actor* Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::SHOP_ITEM_LIST));
		
		//기본 인덱스로 초기화
		int Index = Item->GetIndex();
		SeedShopItemList_.insert(std::make_pair(Index, Item));
	}


	template<typename Actor>
	void NewSaloonItem()
	{
		Actor* Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::SHOP_ITEM_LIST));

		//기본 인덱스로 초기화
		int Index = Item->GetIndex();
		SaloonItemList_.insert(std::make_pair(Index, Item));
	}

};

