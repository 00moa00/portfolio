#pragma once
#include "Npc.h"

// ���� :
class Pierre : public Npc
{
public:
	static Pierre* MainPierre;
	static 	DialogueBox* MainDialogueBox_;

	// constrcuter destructer
	Pierre();
	~Pierre();

	// delete Function
	Pierre(const Pierre& _Other) = delete;
	Pierre(Pierre&& _Other) noexcept = delete;
	Pierre& operator=(const Pierre& _Other) = delete;
	Pierre& operator=(Pierre&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	void OpenDialogue() override;
};

