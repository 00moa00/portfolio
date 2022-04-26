#pragma once
#include"PlayLevel.h"

// ���� :
class ShopLevel : public GameEngineLevel
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
	Shop* Shop_;

	BackGround* BackGround_;
	BackGround* BackGroundFront_;

	std::vector<Npc*> NpcList_;
	std::map<int, Items*> MapObject_;

private:
	void LoadMapObject();
};

