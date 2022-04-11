#pragma once
#include "Items.h"
// ���� :
class PlayerHouse : public Items
{
public:
	// constrcuter destructer
	PlayerHouse();
	~PlayerHouse();

	// delete Function
	PlayerHouse(const PlayerHouse& _Other) = delete;
	PlayerHouse(PlayerHouse&& _Other) noexcept = delete;
	PlayerHouse& operator=(const PlayerHouse& _Other) = delete;
	PlayerHouse& operator=(PlayerHouse&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

