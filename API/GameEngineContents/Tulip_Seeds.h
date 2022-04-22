#pragma once
#include "Items.h"

// ���� :
class Tulip_Seeds : public Items
{
public:

	static Tulip_Seeds* MainTulipSeeds;
	static Font* Font_;

	// constrcuter destructer
	Tulip_Seeds();
	~Tulip_Seeds();

	// delete Function
	Tulip_Seeds(const Tulip_Seeds& _Other) = delete;
	Tulip_Seeds(Tulip_Seeds&& _Other) noexcept = delete;
	Tulip_Seeds& operator=(const Tulip_Seeds& _Other) = delete;
	Tulip_Seeds& operator=(Tulip_Seeds&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


	void AddItemCount() override;
	void SubItemCount() override;

};
