#include "Monster.h"
#include "Player.h"

Monster::Monster() 
	:
	Damage_(0),
	HP_(0),
	RamdomDirResult_(0),

	Speed_(0.f),
	Timer_(0.f),

	isDeath_(false),
	invincibility_(false),
	isHit_(false),

	MoveDir_(float4::DOWN),

	RandomDir_(),
	RandomTimer_(),

	MonsterState_(MONSTER_STATE::WALK),
	MonsterType_(MONSTER_TYPE::OTHER),

	MonsterRenderer_(nullptr),
	MonsterCollider_(nullptr)
{
	ArrAnimationName;
}

Monster::~Monster() 
{
}

void Monster::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void Monster::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

std::string Monster::GetDirString()
{
	if (MoveDir_.CompareInt2D(float4::DOWN))
	{
		return "FRONT_";
	}

	else if (MoveDir_.CompareInt2D(float4::UP))
	{
		return "BACK_";
	}

	else if (MoveDir_.CompareInt2D(float4::LEFT))
	{
		return "LEFT_";
	}

	else if (MoveDir_.CompareInt2D(float4::RIGHT))
	{
		return "RIGHT_";
	}



	return "";
}

bool Monster::CheckMapObject()
{

	if (MonsterCollider_->NextPostCollisionCheck("MapObject", MoveDir_ * GameEngineTime::GetDeltaTime() * 100.f, CollisionType::Rect, CollisionType::Rect) == true)
	{
		return true;

	}
	else
	{
		return false;
	}
}

bool Monster::CheckRightObject()
{
	float4 Move = float4::ZERO;

	Move.Normal2D();
	Move += float4::RIGHT;

	if (MonsterCollider_->NextPostCollisionCheck("MapObject", Move * GameEngineTime::GetDeltaTime() * Speed_, CollisionType::Rect, CollisionType::Rect) == true)
	{
		//MoveDir_ = float4::ZERO;
		return true;

	}
	else
	{
		return false;
	}
}

bool Monster::CheckLeftObject()
{
	float4 Move = float4::ZERO;

	Move.Normal2D();
	Move += float4::LEFT;

	if (MonsterCollider_->NextPostCollisionCheck("MapObject", Move * GameEngineTime::GetDeltaTime() * Speed_, CollisionType::Rect, CollisionType::Rect) == true)
	{
	//	MoveDir_ = float4::ZERO;
		return true;

	}
	else
	{
		return false;
	}
}

bool Monster::CheckUpObject()
{
	float4 Move = float4::ZERO;

	Move.Normal2D();
	Move += float4::UP;

	if (MonsterCollider_->NextPostCollisionCheck("MapObject", Move * GameEngineTime::GetDeltaTime() * Speed_, CollisionType::Rect, CollisionType::Rect) == true)
	{
		//MoveDir_ = float4::ZERO;
		return true;

	}
	else
	{
		return false;
	}
}

bool Monster::CheckDownObject()
{
	float4 Move = float4::ZERO;

	Move.Normal2D();
	Move += float4::DOWN;

	if (MonsterCollider_->NextPostCollisionCheck("MapObject", Move * GameEngineTime::GetDeltaTime() * Speed_, CollisionType::Rect, CollisionType::Rect) == true)
	{
		//MoveDir_ = float4::DOWN;
		return true;

	}
	else
	{
		return false;
	}
}

void Monster::BackMove()
{

	float4 BackMove = -MoveDir_;
	MoveDir_ = -Player::MainPlayer->GetMoveDir();


	static float BackTimer_ = 0;
	BackTimer_ += GameEngineTime::GetDeltaTime();

	if (BackTimer_ > 0.1f)
	{
		BackTimer_ = 0.f;
		MonsterState_ = MONSTER_STATE::WALK;
	}

	//if (MonsterCollider_->NextPostCollisionCheck("MapObject", BackMove * GameEngineTime::GetDeltaTime() * Speed_, CollisionType::Rect, CollisionType::Rect) == true)
	//{
	//	MonsterState_ = MONSTER_STATE::WALK;
	//	return;
	//}

	SetMove(BackMove * GameEngineTime::GetDeltaTime() * (Speed_ * 1.5f));

}

void Monster::SetMonsterStateBack()
{
	MonsterState_ = MONSTER_STATE::BACK;
}
//
//bool Monster::CheckPlayer()
//{
//
//}

bool Monster::MonsterCheck(const float4 pos, const float4 scale)
{
	int OtherLeft = pos.ix() - scale.hix() - 10 ;
	int OtherRight = pos.ix() + scale.hix() + 10 ;
	int OtherTop = pos.iy() - scale.hiy() -50;
	int OtherBottom = pos.iy() + scale.hiy() -20;

	//	GameEngineRect DebugRect;


	if (GetRight() < OtherLeft)
	{
		return false;
	}

	if (OtherRight < GetLeft())
	{
		return false;
	}

	if (GetBottom() < OtherTop)
	{
		return false;
	}

	if (OtherBottom < GetTop())
	{
		return false;
	}

	return true;
}

