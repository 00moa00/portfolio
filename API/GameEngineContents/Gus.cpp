#include "Gus.h"
#include "Player.h"

Gus::Gus() 
	:
	MainDialogueBox_(nullptr)
{
}

Gus::~Gus() 
{
}

void Gus::Start()
{
	NpcRenderer_ = CreateRenderer("Gus.bmp");
	NpcRenderer_->SetIndex(0);

	NpcCollider_ = CreateCollision("NPC", { 48.f, 20.f });
	NpcCollider_->SetPivot({ 0, 20.f });

	MainDialogueBox_ = GetLevel()->CreateActor<DialogueBox>(static_cast<int>(PLAYLEVEL::DIALOGUEBOX));
	MainDialogueBox_->DialogueOff();

	NpcRenderer_->CreateAnimation("Gus.bmp", "RIGHT_INIT", static_cast<int>(NPC_INDEX::RIGHT_WALK00), static_cast<int>(NPC_INDEX::RIGHT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Gus.bmp", "LEFT_INIT", static_cast<int>(NPC_INDEX::LEFT_WALK00), static_cast<int>(NPC_INDEX::LEFT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Gus.bmp", "FRONT_INIT", static_cast<int>(NPC_INDEX::FRONT_WALK00), static_cast<int>(NPC_INDEX::FRONT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Gus.bmp", "BACK_INIT", static_cast<int>(NPC_INDEX::BACK_WALK00), static_cast<int>(NPC_INDEX::BACK_WALK00), 0.0f, false);

	NpcRenderer_->ChangeAnimation("FRONT_INIT");
	SetScale({ 70,100 });
}

void Gus::Update()
{
	MoveUpdate();
	NPCDayOver();
}

void Gus::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void Gus::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void Gus::OpenDialogue()
{
	if (TalkingLimit_ == false)
	{
		DialogueUpdate_ = !DialogueUpdate_;

		if (DialogueUpdate_ == true)
		{
			Inventory::MainInventory->AllUpdateOff();

			MainDialogueBox_->DialogueOn();
			MainDialogueBox_->SetGus();

			//���� ���� �����ϰ� �÷��̾��� �������� �� ����
			PrevDir_ = MoveDir_;
			MoveDir_ = -Player::MainPlayer->GetMoveDir();
			NpcUpdateState_ = NPC_STATE::DIALOGUE_IDLE;
		}


		if (DialogueUpdate_ == false)
		{
			Inventory::MainInventory->AllUpdateOn();
			Inventory::MainInventory->SetPopUpStateMini();

			MainDialogueBox_->DialogueOff();
			WaitTimer_ = 2.0f;
			TalkingLimit_ = true;
			NpcUpdateState_ = NPC_STATE::DIALOGUE_WAIT;
		}
	}
}
