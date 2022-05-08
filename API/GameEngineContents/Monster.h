#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineSound.h>

#include "SubHPFont.h"

#include "RendererData.h"
#include "MonsterData.h"


enum class MONSTER_STATE
{
	WAIT,			//���
	REVIVAL,		//�һ�

	CHECK,			//��� �浹 üũ
	RE_CHECK,		//��� �浹 üũ
	WALK,			//���� �ȱ�
	MOVE_TO_PLAYER,

	MOVE_UP,		//BUG - �� �̵�
	MOVE_DOWN,		//BUG - �Ʒ� �̵�

	BACK,			//���� ������ �ڷ� �̵�

	COLL,			//�� ������Ʈ�� ���Ͱ� ������
	DEATH,

	MAX
};

enum class MONSTER_TYPE
{
	OTHER,
	BUG,
	BAT,
	CRAB,
	GOLEM
};

// ���� :
class Monster : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	
public:
	virtual std::string GetDirString();

	virtual bool CheckMapObject();		//���� ���⿡ ������Ʈ�� �ִ�.

	virtual bool CheckRightObject();
	virtual bool CheckLeftObject();
	virtual bool CheckUpObject();
	virtual bool CheckDownObject();
	virtual void BackMove();
	virtual void SetMonsterStateBack();
	//virtual bool CheckPlayer();

protected:

	int Damage_;
	int HP_;
	int RamdomDirResult_;		//���� �� �����

	float Speed_;				//�̵� ���ǵ�
	float Timer_;				//���� ���� Ÿ�̸�

	bool isDeath_;				//�׾����� üũ
	bool isHit_;				//ũ���� �÷���
	bool invincibility_;

	float4 PrevPos_;
	float4 MoveDir_;			// �ȴ� ����

	GameEngineRandom RandomDir_;	//���� ��������
	GameEngineRandom RandomTimer_;	//���� �������� Ÿ�̸�

	MONSTER_STATE MonsterState_;
	MONSTER_TYPE MonsterType_;

	GameEngineRenderer* MonsterRenderer_;
	GameEngineCollision* MonsterCollider_;		

	std::vector<GameEngineCollision*> ColList;

	const char* ArrAnimationName[static_cast<int>(MONSTER_STATE::MAX)];

public:
	bool MonsterCheck(const float4 pos, const float4 scale);


	//================================
	//     Getter
	//================================
	GameEngineCollision* GetCollision()
	{
		return MonsterCollider_;
	}

	GameEngineRenderer* GetRenderer()
	{
		return MonsterRenderer_;
	}

	bool GetisHit()
	{
		return isHit_;
	}

	int GetDamage()
	{
		return Damage_;
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

	bool MonsterVSPlayer()
	{
		return	MonsterCollider_->CollisionResult("Player", ColList, CollisionType::Rect, CollisionType::Rect);
	}


	MONSTER_TYPE GetMonsterType()
	{
		return MonsterType_;
	}

	//================================
	//    Setter
	//================================

	void SetIsHit(bool _Flag)
	{
		isHit_ = _Flag;
	}

	void SubHP(int _Damage)
	{
		if (invincibility_ == false )
		{
			SubHPFont* SubHPFont_;
			SubHPFont_ = GetLevel()->CreateActor<SubHPFont>();


			if (MonsterType_ == MONSTER_TYPE::BUG)
			{
				SubHPFont_->SetPosAndNumGray(this->GetPosition(), 0);
				HP_ -= 0;

			}
			else
			{
				SubHPFont_->SetPosAndNumGray(this->GetPosition(), _Damage);
				HP_ -= _Damage;
			}

			if (HP_ <= 0)
			{			
				isDeath_ = true;
			}
		}
	}

	float4 GetMoveDir()
	{
		return MoveDir_;
	}

	//------< ���콺, �浹 ���� >------------------------------------------------------------------

};

