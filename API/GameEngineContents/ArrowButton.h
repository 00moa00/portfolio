#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// ���� :
class ArrowButton : public GameEngineActor
{
public:
	// constrcuter destructer
	ArrowButton();
	~ArrowButton();

	// delete Function
	ArrowButton(const ArrowButton& _Other) = delete;
	ArrowButton(ArrowButton&& _Other) noexcept = delete;
	ArrowButton& operator=(const ArrowButton& _Other) = delete;
	ArrowButton& operator=(ArrowButton&& _Other) noexcept = delete;

private:
	void Start()override;
	void Update() override;

private:
	GameEngineRenderer* ArrowRenderer_;
	GameEngineCollision* ArrowCollision_;
	std::vector<GameEngineCollision*> ColList;

public:

	void CreateArrowCollision(std::string _CollName);
	void CreateRightArrow();
	void CreateLeftArrow();

	bool ButtonMouseOverAndLeftClick();

	GameEngineRenderer* GetRenderer()
	{
		return ArrowRenderer_;
	}
};

