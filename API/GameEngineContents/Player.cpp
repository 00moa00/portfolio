#include "Player.h"

#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h> 
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

#include "PlayerSpriteData.h"
#include "TileData.h"

std::string Player::CurrentLevel_ = "";
std::string Player::PrevLevel_ = "";

Player* Player::MainPlayer = nullptr;
PlayerHandItem* Player::PlayerHandItem_ = nullptr;


Player::Player()
	:
	Money_(1000),

	AnimationFrame_(0.120f),
	Speed_(150.f),
	Energy_(150.f),
	MapSizeX_(0.f),
	MapSizeY_(0.f),

	PlayerRenderer_(nullptr),
	ToolRenderer_(nullptr),
	PlayerCollider_(nullptr),
	MapColImage_(nullptr),
	//Inventory_(nullptr),
	Mouse_(nullptr),
//	Shop_(nullptr),
	
	ObjectColl_(false),
	FarmingArea_(false),
	UsingAxe_(false),
	isShopping_(false),

	MoveDir_(float4::DOWN),

	UseToolState_(USE_TOOL::INIT),
	TileState_(TILE_COLL::INIT),
	PlayerState_(PLAYER_UPDATE::LEVELINIT),
	PlayerShoppingState_(PLAYER_SHOPPING::INT)



{
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::INIT)] = "INIT";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::WALK)] = "WALK";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::WATER)] = "WATER";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::HOE)] = "HOE";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::AXE)] = "HOE";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::PICKAXE)] = "HOE";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::HANDITEM)] = "HANDITEM";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::HANDITEMWALK)] = "HANDITEMWALK";



	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::INIT)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::WALK)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::HANDITEM)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::HANDITEMWALK)] = "INIT";

	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::WATER)] = "WATER";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::HOE)] = "HOE";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::AXE)] = "AXE";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::PICKAXE)] = "PICKAXE";



}


Player::~Player() 
{
	CurrentLevel_ = "";


}

void Player::Start()
{
	//------< ���� ��� >------------------------------------------------------------------

//	Shop_ = GetLevel()->CreateActor<Shop>((int)PLAYLEVEL::SHOP);


	//------< �ʱ�ȭ >------------------------------------------------------------------
	MapColImage_ = GameEngineImageManager::GetInst()->Find("PlayerHouse_Coll.bmp");
	PlayerRenderer_ = CreateRenderer();
	PlayerRenderer_->SetPivotType(RenderPivot::BOT);

	ToolRenderer_ = CreateRenderer();
	ToolRenderer_ ->SetPivotType(RenderPivot::BOT);
	ToolRenderer_->SetOrder(static_cast<int>(PLAYLEVEL::USE_TOOL));

	PlayerCollider_ = CreateCollision("Player", { 40.f, 30 });

	SetScale({ 40.f, 40.f });

	CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();


	//------< �ִϸ��̼� ���� >------------------------------------------------------------------

	//================================
	//     �÷��̾� ���
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_INIT", static_cast<int>(PLAYER::RIGHT_INIT), static_cast<int>(PLAYER::RIGHT_INIT), 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_INIT", static_cast<int>(PLAYER::LEFT_INIT),  static_cast<int>(PLAYER::LEFT_INIT), 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_INIT", static_cast<int>(PLAYER::FRONT_INIT), static_cast<int>(PLAYER::FRONT_INIT), 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_INIT", static_cast<int>(PLAYER::BACK_INIT),  static_cast<int>(PLAYER::BACK_INIT), 0.0f, false);

	//================================
	//     �÷��̾� �̵� 
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_WALK",  static_cast<int>(PLAYER::RIGHT_WALK0),  static_cast<int>(PLAYER::RIGHT_WALK5), AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_WALK",   static_cast<int>(PLAYER::LEFT_WALK0),  static_cast<int>(PLAYER::LEFT_WALK5), AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_WALK",  static_cast<int>(PLAYER::FRONT_WALK0),  static_cast<int>(PLAYER::FRONT_WALK3), AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_WALK",   static_cast<int>(PLAYER::BACK_WALK0),  static_cast<int>(PLAYER::BACK_WALK3), AnimationFrame_, true);


	//================================
	//     �÷��̾� �� ��½! ���
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_HANDITEM",  static_cast<int>(PLAYER::RIGHT_HAND_INIT), static_cast<int>(PLAYER::RIGHT_HAND_INIT), 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_HANDITEM",  static_cast<int>(PLAYER::LEFT_HAND_INIT), static_cast<int>(PLAYER::LEFT_HAND_INIT), 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_HANDITEM", static_cast<int>(PLAYER::FRONT_HAND_INIT), static_cast<int>(PLAYER::FRONT_HAND_INIT), 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_HANDITEM", static_cast<int>(PLAYER::BACK_HAND_INIT), static_cast<int>(PLAYER::BACK_HAND_INIT), 0.0f, false);


	//================================
	//     �÷��̾� �̵� 
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_HANDITEMWALK", static_cast<int>(PLAYER::RIGHT_WALK_HAND0), static_cast<int>(PLAYER::RIGHT_WALK_HAND5), AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_HANDITEMWALK", static_cast<int>(PLAYER::LEFT_WALK_HAND0), static_cast<int>(PLAYER::LEFT_WALK_HAND5), AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_HANDITEMWALK",  static_cast<int>(PLAYER::FRONT_WALK_HAND0), static_cast<int>(PLAYER::FRONT_WALK_HAND3), AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_HANDITEMWALK", static_cast<int>(PLAYER::BACK_WALK_HAND0), static_cast<int>(PLAYER::BACK_WALK_HAND3), AnimationFrame_, true);


	//================================
	//     �÷��̾� ȣ�� ���
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_HOE", static_cast<int>(PLAYER::HOE_FRONT0), static_cast<int>(PLAYER::HOE_FRONT5), AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_HOE", static_cast<int>(PLAYER::HOE_RIGHT0), static_cast<int>(PLAYER::HOE_RIGHT4), AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_HOE", static_cast<int>(PLAYER::HOE_BACK0), static_cast<int>(PLAYER::HOE_BACK2), AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_HOE", static_cast<int>(PLAYER::HOE_LEFT0), static_cast<int>(PLAYER::HOE_LEFT4), AnimationFrame_, true);


	//================================
	//     �÷��̾� ���Ѹ��� ���
	//================================

	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_WATER", static_cast<int>(PLAYER::WATER_FRONT0), static_cast<int>(PLAYER::WATER_FRONT2), 0.200f, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_WATER", static_cast<int>(PLAYER::WATER_RIGHT0), static_cast<int>(PLAYER::WATER_RIGHT2), 0.200f, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_WATER", static_cast<int>(PLAYER::WATER_LEFT0),  static_cast<int>(PLAYER::WATER_LEFT2), 0.200f, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_WATER", static_cast<int>(PLAYER::WATER_BACK0),  static_cast<int>(PLAYER::WATER_BACK2), 0.200f, true);



	//------< �� �ִϸ��̼� >------------------------------------------------------------------

	//================================
	//     �÷��̾� �� ���
	//================================
	ToolRenderer_->CreateAnimation("axe_back.bmp", "LEFT_INIT", static_cast<int>(HOE_BACK::HOE_BACK2), static_cast<int>(HOE_BACK::HOE_BACK2), AnimationFrame_, false);
	ToolRenderer_->CreateAnimation("axe_back.bmp", "RIGHT_INIT", static_cast<int>(HOE_BACK::HOE_BACK2), static_cast<int>(HOE_BACK::HOE_BACK2), AnimationFrame_, false);
	ToolRenderer_->CreateAnimation("axe_back.bmp", "FRONT_INIT", static_cast<int>(HOE_BACK::HOE_BACK2), static_cast<int>(HOE_BACK::HOE_BACK2), AnimationFrame_, false);
	ToolRenderer_->CreateAnimation("axe_back.bmp", "BACK_INIT", static_cast<int>(HOE_BACK::HOE_BACK2), static_cast<int>(HOE_BACK::HOE_BACK2), AnimationFrame_, false);



	//================================
	//     �÷��̾� ȣ�� ���
	//================================
	ToolRenderer_->CreateAnimation("hoe_left.bmp", "LEFT_HOE", static_cast<int>(HOE_LEFT::HOE_LEFT0), static_cast<int>(HOE_LEFT::HOE_LEFT4), AnimationFrame_, false);
	ToolRenderer_->CreateAnimation("hoe_right.bmp", "RIGHT_HOE", static_cast<int>(HOE_RIGHT::HOE_RIGHT0), static_cast<int>(HOE_RIGHT::HOE_RIGHT4), AnimationFrame_, false);
	ToolRenderer_->CreateAnimation("hoe_front.bmp", "FRONT_HOE", static_cast<int>(HOE_FRONT::HOE_FRONT0), static_cast<int>(HOE_FRONT::HOE_FRONT4), AnimationFrame_, false);
	ToolRenderer_->CreateAnimation("hoe_back.bmp", "BACK_HOE", static_cast<int>(HOE_BACK::HOE_BACK0), static_cast<int>(HOE_BACK::HOE_BACK2), AnimationFrame_, false);

	//================================
	//     �÷��̾� ���� ���
	//================================
	ToolRenderer_->CreateAnimation("axe_left.bmp", "LEFT_AXE", static_cast<int>(AXE_LEFT::AXE_LEFT0), static_cast<int>(AXE_LEFT::AXE_LEFT4), AnimationFrame_, false);
	ToolRenderer_->CreateAnimation("axe_right.bmp", "RIGHT_AXE", static_cast<int>(AXE_RIGHT::AXE_RIGHT0), static_cast<int>(AXE_RIGHT::AXE_RIGHT4), AnimationFrame_, false);
	ToolRenderer_->CreateAnimation("axe_front.bmp", "FRONT_AXE", static_cast<int>(AXE_FRONT::AXE_FRONT0), static_cast<int>(AXE_FRONT::AXE_FRONT4), AnimationFrame_, false);
	ToolRenderer_->CreateAnimation("axe_back.bmp", "BACK_AXE", static_cast<int>(AXE_BACK::AXE_BACK0), static_cast<int>(AXE_BACK::AXE_BACK2), AnimationFrame_, false);


	//================================
	//     �÷��̾� ��� ���
	//================================
	ToolRenderer_->CreateAnimation("pickaxe_left.bmp", "LEFT_PICKAXE", static_cast<int>(PICKAXE_LEFT::PICKAXE_LEFT0), static_cast<int>(PICKAXE_LEFT::PICKAXE_LEFT4), AnimationFrame_, false);
	ToolRenderer_->CreateAnimation("pickaxe_right.bmp", "RIGHT_PICKAXE", static_cast<int>(PICKAXE_RIGHT::PICKAXE_RIGHT0), static_cast<int>(PICKAXE_RIGHT::PICKAXE_RIGHT4), AnimationFrame_, false);
	ToolRenderer_->CreateAnimation("pickaxe_front.bmp", "FRONT_PICKAXE", static_cast<int>(PICKAXE_FRONT::PICKAXE_FRONT0), static_cast<int>(PICKAXE_FRONT::PICKAXE_FRONT4), AnimationFrame_, false);
	ToolRenderer_->CreateAnimation("pickaxe_back.bmp", "BACK_PICKAXE", static_cast<int>(PICKAXE_BACK::PICKAXE_BACK0), static_cast<int>(PICKAXE_BACK::PICKAXE_BACK2), AnimationFrame_, false);


	//================================
	//     �÷��̾� ���Ѹ��� ���
	//================================

	ToolRenderer_->CreateAnimation("wateringcan_right.bmp", "RIGHT_WATER", static_cast<int>(WATERINGCAN_RIGHT::WATERINGCAN_RIGHT0), static_cast<int>(WATERINGCAN_RIGHT::WATERINGCAN_RIGHT2), 0.200f, false);
	ToolRenderer_->CreateAnimation("wateringcan_left.bmp", "LEFT_WATER",  static_cast<int>(WATERINGCAN_LEFT::WATERINGCAN_LEFT0), static_cast<int>(WATERINGCAN_LEFT::WATERINGCAN_LEFT2), 0.200f, false);
	ToolRenderer_->CreateAnimation("wateringcan_front.bmp", "FRONT_WATER",  static_cast<int>(WATERINGCAN_FRONT::WATERINGCAN_FRONT0), static_cast<int>(WATERINGCAN_FRONT::WATERINGCAN_FRONT2), 0.200f, false);
	ToolRenderer_->CreateAnimation("wateringcan_back.bmp", "BACK_WATER", static_cast<int>(WATERINGCAN_BACK::WATERINGCAN_BACK0), static_cast<int>(WATERINGCAN_BACK::WATERINGCAN_BACK2), 0.200f, false);


	//------< �ִϸ��̼� �ʱ�ȭ >------------------------------------------------------------------

	PlayerRenderer_->ChangeAnimation("FRONT_INIT");
	ToolRenderer_->ChangeAnimation("LEFT_INIT");
	//PlayerMove_.SetFrontDir(true);
	LevelRegist("MainPlayer");
}



void Player::Update()
{
	PlayerDirCheck();
	SetCamera();
	PlayerUpdate();
	SetPlayerHandItemPos();
	ClearWetDirtTile();
	ChangeLevel();
	NpcCollCheck();

	if (CurrentLevel_ == "ShopLevel")
	{
		PlayerShopping();
	}
	

	if (true == GameEngineInput::GetInst()->IsDown("DebugRendereChange"))
	{
		GetLevel()->IsDebugModeSwitch();
	}

}

void Player::Render()
{

}

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;
	PlayerHandItem_ = PlayerHandItem_;
}

void Player::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
//	Shop_->NextLevelOn();
}




void Player::PlayerUpdate()
{

	switch (PlayerState_)
	{
	case PLAYER_UPDATE::LEVELINIT:

		Mouse_ = GetLevel()->CreateActor<Mouse>((int)PLAYLEVEL::MOUSE);
		Mouse_->Renderer()->CameraEffectOff();

		PlayerHandItem_ = GetLevel()->CreateActor<PlayerHandItem>((int)PLAYLEVEL::ITEM);

		Speed_ = 150.f;
		CurrentLevel_ = GetCurrentLevel();

		CollInit();

		PlayerState_ = PLAYER_UPDATE::INIT;
		break;

	case PLAYER_UPDATE::INIT:

		ChangeHandItem();
		harvestingCrops();

		if (isShopping_ == true)
		{
			PlayerState_ = PLAYER_UPDATE::INIT;

		}

		//�տ� �� �� �ִ� �������̶�� 
		if (Inventory::MainInventory->GetCurrentItem() != nullptr && Inventory::MainInventory->GetCurrentItem()->GetisPossibleHand() == true)
		{
			PlayerState_ = PLAYER_UPDATE::HANDITEM;

		}


		//�κ��丮 �� && ��� ������ �����̶�� �� ��� 
		if (Mouse_->MouseClickInventoryOut() && FarmingArea_ == true)
		{
			CheckTool();//���� �°� ������Ʈ �̵�
		}


		//�̵�Ű�� �����ٸ� �̵�������Ʈ�� ����
		if (isMove())
		{
			PlayerState_ = PLAYER_UPDATE::WALK;
		}


		break;

	case PLAYER_UPDATE::HOE:

		if (PlayerRenderer_->IsEndAnimation())
		{
			CreateDirtTile();
			ChangeDirtTile();
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;

	case PLAYER_UPDATE::WATER:

		if (PlayerRenderer_->IsEndAnimation())
		{
			CreateWaterTile();
			ChangeWetDirtTile();

			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;

	case PLAYER_UPDATE::AXE:

		if (PlayerRenderer_->IsEndAnimation())
		{
			CrushTree();
			CrushWood();
		}

		break;

	case PLAYER_UPDATE::PICKAXE:

		if (PlayerRenderer_->IsEndAnimation())
		{
			CrushStone();
		}

		break;

	case PLAYER_UPDATE::HANDITEM:

		ChangeLevel();
		ChangeHandItem();

		if (Mouse_->MouseClickInventoryOut())
		{
			CreateSeed();
		}

		//�տ� �� �� ���� �������� �����ߴٸ� �⺻ ���·� ���ư���.
		if (Inventory::MainInventory->GetCurrentItem() != nullptr && Inventory::MainInventory->GetCurrentItem()->GetisPossibleHand() == false)
		{
			PlayerState_ = PLAYER_UPDATE::INIT;

		}

		if (isMove()
			&& Inventory::MainInventory->GetCurrentItem()->GetisPossibleHand() == true)
		{
			PlayerState_ = PLAYER_UPDATE::HANDITEMWALK;
		}


		break;


	case PLAYER_UPDATE::WALK:

		PlayerWalk();
		SubEnergy();
		harvestingCrops();


		if (isStop())
		{
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;

	case PLAYER_UPDATE::HANDITEMWALK:

		PlayerWalk();
		SubEnergy();

		if (Mouse_->MouseClickInventoryOut())
		{
			CreateSeed();
		}

		if (isStop())
		{
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;

	default:
		break;
	}

}

