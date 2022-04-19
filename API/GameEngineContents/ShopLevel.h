#pragma once
#include"PlayLevel.h"

// ���� :
class ShopLevel : public PlayLevel
{
public:
	// constrcuter destructer
	ShopLevel();
	~ShopLevel();

	// delete Function
	ShopLevel(const ShopLevel& _Other) = delete;
	ShopLevel(ShopLevel&& _Other) noexcept = delete;
	ShopLevel& operator=(const ShopLevel& _Other) = delete;
	ShopLevel& operator=(ShopLevel&& _Other) noexcept = delete;

private:

	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


private:

	float Time;

	Shop* Shop_;

	std::map<int, Items*> MapObject_;
	std::map<int, Items*>::iterator Iter;

private:

	void LoadMapObject();
};

