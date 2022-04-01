#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
class PlayerShirts : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerShirts();
	~PlayerShirts();

	// delete Function
	PlayerShirts(const PlayerShirts& _Other) = delete;
	PlayerShirts(PlayerShirts&& _Other) noexcept = delete;
	PlayerShirts& operator=(const PlayerShirts& _Other) = delete;
	PlayerShirts& operator=(PlayerShirts&& _Other) noexcept = delete;

	GameEngineRenderer* Renderer() {
		return PlayerShirts_;
	}

protected:
	GameEngineRenderer* PlayerShirts_;

private:

	void Start() override;
	void Update() override;
	void Render() override;
};

