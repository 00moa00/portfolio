#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>

#include "DialogueBox.h"
#include "RendererData.h"
#include "NpcMove.h"

enum class NPC_STATE
{
	WAIT,				//�⺻ ���ִ� ����
	WALK,				//�Ȱ�����
	DIALOGUE_IDLE,		//��ȭ��
	DIALOGUE_WAIT,		//��ȭ ���� �� 3�� ���
	WAIT_COUNT,			//Waitī���ÿ�
	MAX
};

// ���� :
class Npc : public GameEngineActor
{
public:
	// constrcuter destructer
	Npc();
	~Npc();

	// delete Function
	Npc(const Npc& _Other) = delete;
	Npc(Npc&& _Other) noexcept = delete;
	Npc& operator=(const Npc& _Other) = delete;
	Npc& operator=(Npc&& _Other) noexcept = delete;


private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


public:

	virtual void OpenDialogue();
	virtual void DirAnimationChange();
	virtual bool ForAwayPlayer();
	virtual void LoadPennyMoveFlag();
	virtual void LoadLewisMoveFlag();

	virtual void MoveCheck();
	virtual bool MoveRight();
	virtual bool MoveLeft();
	virtual bool MoveDown();
	virtual bool MoveUp();
	virtual bool MoveWait();
	virtual void MoveUpdate();

	virtual void CheckTalkingLimit();

	virtual std::string GetDirString();

private:

protected:

	bool TalkingLimit_;		//�Ϸ翡 �� ���� ��ȭ�� �� �� �ִ�.

	int WaitCount_;			//��� ���° ���������� ���� �ൿ�� �ٸ���

	float Speed_;
	float WaitTimer_;		//�÷��̾�� ��ȭ ������ �ൿ�� �ٽ� ���� ������ �ð�

	float4 MoveDir_;		// �ȴ� ����
	float4 PrevDir_;		// �÷��̾ ��ȭ�� �ɰ��� �ٲ� �����ϱ� ���� ����

	bool DialogueUpdate_;
	bool isWalking_;

	const char* ArrAnimationName[static_cast<int>(NPC_STATE::MAX)];

	NPC_STATE NpcUpdateState_;

	std::vector<GameEngineCollision*> ColList;
	std::vector<NpcMove*> MoveFlagList_;

	GameEngineRenderer* NpcRenderer_;
	GameEngineCollision* NpcCollider_;		//�浹üũ��
	GameEngineCollision* PersonalCollider_;	//���� �ݶ��̴�. ������� ���� ����


private:

public:
	bool NPCCheck(const float4 pos, const float4 scale);

	//================================
	//     Getter
	//================================

	GameEngineCollision* GetCollision()
	{
		return NpcCollider_;
	}

	GameEngineRenderer* GetRenderer()
	{
		return NpcRenderer_;
	}

	bool GetTalkingLimit()
	{
		return TalkingLimit_;
	}

	int GetLeft()
	{
		return GetPosition().ix() - GetScale().hix();
	}

	int GetRight()
	{
		return GetPosition().ix() + GetScale().hix();
	}

	int GetTop()
	{
		return GetPosition().iy() - GetScale().hiy();
	}

	int GetBottom()
	{
		return GetPosition().iy() + GetScale().hiy();
	}

	bool GetDialogueUpdate()
	{
		return DialogueUpdate_;
	}

	//================================
	//    Setter
	//================================

	void SetDialogueUpdate(bool _Flag)
	{
		DialogueUpdate_ = _Flag;
	}


	//------< ���콺, �浹 ���� >------------------------------------------------------------------


	//bool MouseOver()
	//{
	//	return (PersonalCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
	//}


};

