#include "Penny.h"
#include "Player.h"

Penny* Penny::MainPenny = nullptr;
DialogueBox* Penny::MainDialogueBox_ = nullptr;


Penny::Penny() 
{
}

Penny::~Penny() 
{
}

void Penny::Start()
{
	NpcRenderer_ = CreateRenderer("Penny.bmp");
	NpcRenderer_->SetIndex(0);

	NpcCollider_ = CreateCollision("NPC", { 48.f, 60.f });
	NpcCollider_->SetPivot({0, 20.f});

	MainDialogueBox_ = GetLevel()->CreateActor<DialogueBox>(static_cast<int>(PLAYLEVEL::DIALOGUEBOX));
	MainDialogueBox_->DialogueOff();

	NpcRenderer_->CreateAnimation("Penny.bmp", "RIGHT_INIT", static_cast<int>(NPC_INDEX::RIGHT_WALK00), static_cast<int>(NPC_INDEX::RIGHT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Penny.bmp", "LEFT_INIT", static_cast<int>(NPC_INDEX::LEFT_WALK00), static_cast<int>(NPC_INDEX::LEFT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Penny.bmp", "FRONT_INIT", static_cast<int>(NPC_INDEX::FRONT_WALK00), static_cast<int>(NPC_INDEX::FRONT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Penny.bmp", "BACK_INIT", static_cast<int>(NPC_INDEX::BACK_WALK00), static_cast<int>(NPC_INDEX::BACK_WALK00), 0.0f, false);

	NpcRenderer_->CreateAnimation("Penny.bmp", "RIGHT_WALK", static_cast<int>(NPC_INDEX::RIGHT_WALK00), static_cast<int>(NPC_INDEX::RIGHT_WALK03), 0.150f, true);
	NpcRenderer_->CreateAnimation("Penny.bmp", "LEFT_WALK", static_cast<int>(NPC_INDEX::LEFT_WALK00), static_cast<int>(NPC_INDEX::LEFT_WALK03), 0.150f, true);
	NpcRenderer_->CreateAnimation("Penny.bmp", "FRONT_WALK", static_cast<int>(NPC_INDEX::FRONT_WALK00), static_cast<int>(NPC_INDEX::FRONT_WALK03), 0.150f, true);
	NpcRenderer_->CreateAnimation("Penny.bmp", "BACK_WALK", static_cast<int>(NPC_INDEX::BACK_WALK00), static_cast<int>(NPC_INDEX::BACK_WALK03), 0.150f, true);


	NpcRenderer_->ChangeAnimation("FRONT_INIT");
	SetScale({ 48,96 });

	LoadPennyMoveFlag();
}

void Penny::Update()
{

	//��ȭ�߿��� ����
	if (DialogueUpdate_ == false)
	{
		MoveCheck();
	}

	switch (NpcUpdateState_)
	{
	case NPC_STATE::INIT:

		//�÷��̾�� �־����� ���� �������� ����
		if (ForAwayPlayer() == true)
		{
			MoveDir_ = float4::DOWN;
		}

		break;
	case NPC_STATE::WALK:

		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
		
		break;
	case NPC_STATE::WALK_WAIT:

		WaitTimer_ -= GameEngineTime::GetDeltaTime();

		if (WaitTimer_ < 0.f)
		{

			MoveDir_ = PrevDir_;
			NpcUpdateState_ = NPC_STATE::WALK;

		}


		break;
	default:
		break;
	}

	DirAnimationChange();
}

void Penny::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPenny = this;
	MainDialogueBox_ = MainDialogueBox_;
}

void Penny::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	MainDialogueBox_->NextLevelOn();

}

void Penny::OpenDialogue()
{
	DialogueUpdate_ = !DialogueUpdate_;


	if (DialogueUpdate_ == true)
	{
		Inventory::MainInventory->AllUpdateOff();

		MainDialogueBox_->DialogueOn();
		MainDialogueBox_->SetPenny();

		//���� ���� �����ϰ� �÷��̾��� �������� �� ����
		PrevDir_ = MoveDir_; 
		MoveDir_ = -Player::MainPlayer->GetMoveDir();
		NpcUpdateState_ = NPC_STATE::INIT;
	}


	if (DialogueUpdate_ == false)
	{
		Inventory::MainInventory->AllUpdateOn();
		Inventory::MainInventory->SetPopUpStateMini();

		MainDialogueBox_->DialogueOff();
		WaitTimer_ = 2.0f;
		NpcUpdateState_ = NPC_STATE::WALK_WAIT;

	}
}

bool Penny::MoveRight()
{
	return (NpcCollider_->CollisionResult("PennyRight", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Penny::MoveLeft()
{
	return (NpcCollider_->CollisionResult("PennyLeft", ColList, CollisionType::Rect, CollisionType::Rect));

}

bool Penny::MoveDown()
{
	return (NpcCollider_->CollisionResult("PennyDown", ColList, CollisionType::Rect, CollisionType::Rect));

}

bool Penny::MoveUp()
{
	return (NpcCollider_->CollisionResult("PennyUp", ColList, CollisionType::Rect, CollisionType::Rect));

}

bool Penny::MoveWait()
{
	return (NpcCollider_->CollisionResult("PennyWait", ColList, CollisionType::Rect, CollisionType::Rect));
}

void Penny::MoveCheck()
{
	if (MoveDown() == true)
	{
		MoveDir_ = float4::DOWN;
		NpcUpdateState_ = NPC_STATE::WALK;
	}

	if (MoveUp() == true)
	{
		MoveDir_ = float4::UP;
		NpcUpdateState_ = NPC_STATE::WALK;

	}

	if (MoveRight() == true)
	{
		MoveDir_ = float4::RIGHT;
		NpcUpdateState_ = NPC_STATE::WALK;

	}

	if (MoveLeft() == true)
	{
		MoveDir_ = float4::LEFT;
		NpcUpdateState_ = NPC_STATE::WALK;

	}

	if (MoveWait() == true)
	{
		MoveDir_ = float4::DOWN;
		NpcUpdateState_ = NPC_STATE::INIT;

	}

}
