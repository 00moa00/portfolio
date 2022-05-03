#include "Golem.h"
#include "Player.h"

Golem::Golem() 
	:
	CheckTimer_(0.f)
{
	ArrAnimationName[static_cast<int>(MONSTER_STATE::WALK)] = "WALK";

	ArrAnimationName[static_cast<int>(MONSTER_STATE::WAIT)] = "WAIT";
	ArrAnimationName[static_cast<int>(MONSTER_STATE::RE_CHECK)] = "WAIT";
	ArrAnimationName[static_cast<int>(MONSTER_STATE::CHECK)] = "WAIT";

}

Golem::~Golem() 
{
}

void Golem::Start()
{
	MonsterRenderer_ = CreateRenderer("StoneGolem.bmp");
	MonsterRenderer_->SetIndex(0);

	MonsterCollider_ = CreateCollision("Monster", { 48.f, 36.f });
	MonsterCollider_->SetPivot({ 0, 18.f });

	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "RIGHT_WALK", static_cast<int>(STONE_GOLEM::RIGHT_WALK00), static_cast<int>(STONE_GOLEM::RIGHT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "LEFT_WALK", static_cast<int>(STONE_GOLEM::LEFT_WALK00), static_cast<int>(STONE_GOLEM::LEFT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "FRONT_WALK", static_cast<int>(STONE_GOLEM::FRONT_WALK00), static_cast<int>(STONE_GOLEM::FRONT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "BACK_WALK", static_cast<int>(STONE_GOLEM::BACK_WALK00), static_cast<int>(STONE_GOLEM::BACK_WALK03), 0.120f, true);

	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "REVIVAL", static_cast<int>(STONE_GOLEM::REVIVAL00), static_cast<int>(STONE_GOLEM::REVIVAL_K07), 0.120f, false);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "DEATH", static_cast<int>(STONE_GOLEM::DEATH), static_cast<int>(STONE_GOLEM::DEATH), 0.0f, false);

	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "RIGHT_WAIT", static_cast<int>(STONE_GOLEM::RIGHT_WALK00), static_cast<int>(STONE_GOLEM::RIGHT_WALK00), 0.120f, false);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "LEFT_WAIT", static_cast<int>(STONE_GOLEM::LEFT_WALK00), static_cast<int>(STONE_GOLEM::LEFT_WALK00), 0.120f, false);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "FRONT_WAIT", static_cast<int>(STONE_GOLEM::FRONT_WALK00), static_cast<int>(STONE_GOLEM::FRONT_WALK00), 0.120f, false);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "BACK_WAIT", static_cast<int>(STONE_GOLEM::BACK_WALK00), static_cast<int>(STONE_GOLEM::BACK_WALK00), 0.120f, false);

	MonsterRenderer_->ChangeAnimation("FRONT_WALK");

	Damage_ = 2;
	HP_ = 10;
	Speed_ = 60.f;


	SetScale({ 48, 96 });
}

void Golem::Update()
{
	DirAnimation(); 

	switch (MonsterState_)
	{
	case MONSTER_STATE::WAIT:
		break;
	case MONSTER_STATE::CHECK:

		RamdomDirResult_ = RandomDir_.RandomInt(0,3);
	
		switch (RamdomDirResult_)
		{
		case 0: 
			if (CheckRightObject() == true)
			{
				MonsterState_ = MONSTER_STATE::RE_CHECK;
			}
			else
			{
				MoveDir_ = float4::RIGHT;
				MonsterState_ = MONSTER_STATE::WALK;
			}

			break;
		case 1:

			if (CheckLeftObject() == true)
			{
				MonsterState_ = MONSTER_STATE::RE_CHECK;
			}
			else
			{
				MoveDir_ = float4::LEFT;
				MonsterState_ = MONSTER_STATE::WALK;
			}

			break;
		case 2:

			if (CheckUpObject() == true)
			{
				MonsterState_ = MONSTER_STATE::RE_CHECK;
			}
			else
			{
				MoveDir_ = float4::UP;
				MonsterState_ = MONSTER_STATE::WALK;
			}

			break;
		case 3:

			if (CheckDownObject() == true)
			{
				MonsterState_ = MONSTER_STATE::RE_CHECK;
			}
			else
			{
				MoveDir_ = float4::DOWN;
				MonsterState_ = MONSTER_STATE::WALK;
			}

			break;
		default:
			break;
		}

		break;

	case MONSTER_STATE::RE_CHECK:

		//������ ������ ���ϰ� ���� �ִٸ� �ٽ� ���ƿ´�
		MonsterState_ = MONSTER_STATE::CHECK;

		break;
	case MONSTER_STATE::WALK:

		//�÷��̾�� ���ϴ� ���� üũ
		Dir = Player::MainPlayer->GetPosition() - this->GetPosition();

		//���� üũ
		Check = Dir.Len2D();

		//���ٰ� ���� �ð��� ������ ������ ư��.
		Timer_ += GameEngineTime::GetDeltaTime();
		if (Timer_ > 3.0f && Check > 150)
		{
			Timer_ = 0.f;
			MonsterState_ = MONSTER_STATE::CHECK;
		}		

		Dir.Normal2D();

		if (Check <= 150 && CheckTime_ == true)
		{
			//�÷��̾ ������, �Ʒ��� �ִ�
			if (Dir.x > 0 && Dir.y > 0)
			{
				MoveDir_ = float4::ZERO;
				MoveDir_ = float4::RIGHT;
			}

			//�÷��̾ ������, ���� �ִ�
			if (Dir.x > 0 && Dir.y < 0)
			{
				MoveDir_ = float4::ZERO;
				MoveDir_ = float4::RIGHT;
			}

			//�÷��̾ ����, ���� �ִ�
			if (Dir.x < 0 && Dir.y < 0)
			{
				MoveDir_ = float4::ZERO;
				MoveDir_ = float4::LEFT;
			}

			//�÷��̾ ����, �Ʒ��� �ִ�
			if (Dir.x < 0 && Dir.y > 0)
			{
				MoveDir_ = float4::ZERO;
				MoveDir_ = float4::LEFT;
			}

			//x�� ���� üũ�ϰ� ������ yüũ
			if (Player::MainPlayer->GetPosition().ix() == this->GetPosition().ix())
			{			
				if (Dir.y > 0)
				{
					MoveDir_ = float4::ZERO;
					MoveDir_ = float4::DOWN;
				}

				
				if (Dir.y < 0)
				{
					MoveDir_ = float4::ZERO;
					MoveDir_ = float4::UP;
				}
				
			}

		}

		//�÷��̾�� �������� ���� ������ ������ �������� �Ӹ��� ư��.
		if (CheckMapObject() == true)
		{
			MonsterState_ = MONSTER_STATE::CHECK;
			break;
		}

		//�÷��̾� üũ ����. ������ 0.5�ʵ��� üũ���� �ʴ´�.

		if (Player::MainPlayer->GetPosition().CompareInt2D(this->GetPosition())== true && CheckTime_ == true)
		{
			CheckTime_ = false;
		}

		if (CheckTime_ == false)
		{
			CheckTimer_ += GameEngineTime::GetDeltaTime();
			if (CheckTimer_ > 0.5f)
			{
				CheckTime_ = true;
				CheckTimer_ = 0.f;
			}
		}

		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);


		break;
	default:
		break;
	}



}

void Golem::DirAnimation()
{

	MonsterRenderer_->ChangeAnimation(GetDirString() + ArrAnimationName[static_cast<int>(MonsterState_)]);

}

