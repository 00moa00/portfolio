#pragma once
#include "Items.h"

// ���� :
class ShippingBox : public Items
{
public:
	// constrcuter destructer
	ShippingBox();
	~ShippingBox();

	// delete Function
	ShippingBox(const ShippingBox& _Other) = delete;
	ShippingBox(ShippingBox&& _Other) noexcept = delete;
	ShippingBox& operator=(const ShippingBox& _Other) = delete;
	ShippingBox& operator=(ShippingBox&& _Other) noexcept = delete;

protected:

private:

};

