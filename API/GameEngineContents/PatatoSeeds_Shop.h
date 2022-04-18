#pragma once
#include "ShopItem.h"

// ���� :
class PatatoSeeds_Shop : public ShopItem
{
public:
	// constrcuter destructer
	PatatoSeeds_Shop();
	~PatatoSeeds_Shop();

	// delete Function
	PatatoSeeds_Shop(const PatatoSeeds_Shop& _Other) = delete;
	PatatoSeeds_Shop(PatatoSeeds_Shop&& _Other) noexcept = delete;
	PatatoSeeds_Shop& operator=(const PatatoSeeds_Shop& _Other) = delete;
	PatatoSeeds_Shop& operator=(PatatoSeeds_Shop&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

public:
	void InventoryNewItem() override;

protected:

private:

};

