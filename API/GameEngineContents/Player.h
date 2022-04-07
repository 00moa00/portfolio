#pragma once

#include "RendererEnum.h"
#include <GameEngine/GameEngineActor.h>
#include "PlayerData.h"
#include "Hoe.h"
#include "Mouse.h"
#include "Inventory.h"

//class PlayerMove;

class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

protected:
	void Start() override;
	void Update() override;
	void Render() override;

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

private:



	void moveX();
	void moveY();

	bool isStop();
	bool isMove();
	void SetDirAnimation();

	//void SetInit();


private:

	float AnimationFrame_;
	float Speed_;
	float Energy_;


	GameEngineRenderer* Player_;

	Mouse* Mouse_;

	Inventory* Inventory_;
	PLAYERSTATE PlayerState_;
	PlayerDir  PlayerMove_;

	//��
	Hoe* Hoe_;

private:
	float GetEnergy() {
		return Energy_;
	}

	void SetPlayerSpeed(float f) {
		Speed_ = f;
	}

	float GetPlayerSpeed() {
		return Speed_;
	}

	void SubEnergy() {
		Energy_ -= 3.0f * GameEngineTime::GetDeltaTime();
	}

	
};

