#pragma once
#include "Items.h"

// ���� :
class MoveShop : public Items
{
public:
	// constrcuter destructer
	MoveShop();
	~MoveShop();

	// delete Function
	MoveShop(const MoveShop& _Other) = delete;
	MoveShop(MoveShop&& _Other) noexcept = delete;
	MoveShop& operator=(const MoveShop& _Other) = delete;
	MoveShop& operator=(MoveShop&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

