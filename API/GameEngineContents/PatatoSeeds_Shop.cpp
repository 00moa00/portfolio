#include "PatatoSeeds_Shop.h"
#include "Player.h"
#include "Potato_Seeds.h"

PatatoSeeds_Shop::PatatoSeeds_Shop() 
{
}

PatatoSeeds_Shop::~PatatoSeeds_Shop() 
{
}

void PatatoSeeds_Shop::Start()
{
	SetPosition({ 0.f,0.f });

	ShopItemListRenderer_ = CreateRenderer("PatatoSeeds_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("PatatoSeeds_Shop", { 760, 60 });
	ShopItemListCollider_->SetPivot({ 0, +50.f / 2 });


	Index_ = static_cast<int>(SHOP_LIST::PATAPOSEEDS);
	
	BuyPrice_ = 50;

}

void PatatoSeeds_Shop::Update()
{
}

void PatatoSeeds_Shop::InventoryNewItem()
{
	Inventory::MainInventory->NewItem<Potato_Seeds>();
}

bool PatatoSeeds_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}

