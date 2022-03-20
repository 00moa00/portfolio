#pragma once
#include <GameEngine/GameEngine.h>


class StardewValley : public GameEngine
{
public:
	StardewValley();
	~StardewValley();

	StardewValley(const StardewValley& _Other) = delete;
	StardewValley(StardewValley&& _Other) noexcept = delete;
	StardewValley& operator=(const StardewValley& _Other) = delete;
	StardewValley& operator=(StardewValley&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;

protected:

private:

};

