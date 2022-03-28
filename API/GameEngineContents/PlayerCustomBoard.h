#pragma once
#include <GameEngine/GameEngineActor.h>

// �����͸� ���� �̱��� ����ϱ�? ������ �ٸ� ������ ���.?

class PlayerCustomBoard : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerCustomBoard();
	~PlayerCustomBoard();

	// delete Function
	PlayerCustomBoard(const PlayerCustomBoard& _Other) = delete;
	PlayerCustomBoard(PlayerCustomBoard&& _Other) noexcept = delete;
	PlayerCustomBoard& operator=(const PlayerCustomBoard& _Other) = delete;
	PlayerCustomBoard& operator=(PlayerCustomBoard&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* PlayerCustomBoard_;

	void Start() override;
	void Update() override;
	void Render() override;
};


