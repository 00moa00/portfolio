#pragma once
#include "Items.h"
// ���� :
class ShopFlag : public Items
{
public:
	// constrcuter destructer
	ShopFlag();
	~ShopFlag();

	// delete Function
	ShopFlag(const ShopFlag& _Other) = delete;
	ShopFlag(ShopFlag&& _Other) noexcept = delete;
	ShopFlag& operator=(const ShopFlag& _Other) = delete;
	ShopFlag& operator=(ShopFlag&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

