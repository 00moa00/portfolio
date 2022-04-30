#pragma once
#include "ShopItem.h"

// ���� :
class Pizza_Shop : public ShopItem
{
public:
	// constrcuter destructer
	Pizza_Shop();
	~Pizza_Shop();

	// delete Function
	Pizza_Shop(const Pizza_Shop& _Other) = delete;
	Pizza_Shop(Pizza_Shop&& _Other) noexcept = delete;
	Pizza_Shop& operator=(const Pizza_Shop& _Other) = delete;
	Pizza_Shop& operator=(Pizza_Shop&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

public:
	void InventoryNewItem() override;
	bool MouseInItem() override;

};

