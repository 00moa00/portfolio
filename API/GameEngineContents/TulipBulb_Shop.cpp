#include "TulipBulb_Shop.h"
#include "Tulip_Seeds.h"
#include "Player.h"

TulipBulb_Shop::TulipBulb_Shop() 
{
}

TulipBulb_Shop::~TulipBulb_Shop() 
{
}

void TulipBulb_Shop::Start()
{

	SetPosition({ 0.f,0.f });

	ShopItemListRenderer_ = CreateRenderer("TulipBulb_Shop.bmp");
	ShopItemListRenderer_->CameraEffectOff();

	ShopItemListCollider_ = CreateCollision("TulipBulb_Shop", { 760, 60 });
	ShopItemListCollider_->SetPivot({ 0, +50.f / 2 });

	Index_ = static_cast<int>(SHOP_LIST::TULIPBULB);

	BuyPrice_ = 20;

}

void TulipBulb_Shop::Update()
{
}

void TulipBulb_Shop::InventoryNewItem()
{
	Inventory::MainInventory->NewItem<Tulip_Seeds>();
}

bool TulipBulb_Shop::MouseInItem()
{
	return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
}

