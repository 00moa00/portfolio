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
//Inventory* Player::MainInventory = nullptr;



//PLAYER_UPDATE Player::PlayerState_ = PLAYER_UPDATE::INIT;
//GameEngineRenderer* Player::PlayerRenderer_ = nullptr;
//GameEngineCollision* Player::PlayerCollider_ = nullptr;
//Inventory* Player::Inventory_ = nullptr;
//Mouse* Player::Mouse_ = nullptr;
//FixedPlayerColl* Player::FixedPlayerColl_ = nullptr;

Player::Player()
	:
	Money_(1000),

	AnimationFrame_(0.120f),
	Speed_(150.f),
	Energy_(150.f),
	MapSizeX_(0.f),
	MapSizeY_(0.f),

	RandomItemCount(),
	RandomItemPosX(),
	RamdomItemPosY(),

	PlayerRenderer_(nullptr),
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

}


Player::~Player() 
{
	CurrentLevel_ = "";

	std::map<int, FarmTile*>::iterator StartDirtIter = DirtList_.begin();
	std::map<int, FarmTile*>::iterator EndDirtIter = DirtList_.end();


	for (; StartDirtIter != EndDirtIter; ++StartDirtIter)
	{
		delete StartDirtIter->second->GetTile();
	}

	std::map<int, FarmTile*>::iterator StartWetIter = WetDirtList_.begin();
	std::map<int, FarmTile*>::iterator EndWetIter = WetDirtList_.end();


	for (; StartWetIter != EndWetIter; ++StartWetIter)
	{
		delete StartWetIter->second->GetTile();
	}
}

void Player::Start()
{
	//------< ���� ��� >------------------------------------------------------------------

//	Shop_ = GetLevel()->CreateActor<Shop>((int)PLAYLEVEL::SHOP);


	//------< �ʱ�ȭ >------------------------------------------------------------------
	MapColImage_ = GameEngineImageManager::GetInst()->Find("PlayerHouse_Coll.bmp");
	PlayerRenderer_ = CreateRenderer();
	PlayerRenderer_->SetPivotType(RenderPivot::BOT);
	PlayerCollider_ = CreateCollision("Player", { 30, 30 });

	SetScale({ 40, 20 });

	CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();


	//------< �ִϸ��̼� ���� >------------------------------------------------------------------

	//================================
	//     �÷��̾� ���
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_INIT", PLAYER::FRONT_INIT, PLAYER::FRONT_INIT, 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_INIT", PLAYER::RIGHT_INIT, PLAYER::RIGHT_INIT, 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_INIT", PLAYER::LEFT_INIT, PLAYER::LEFT_INIT, 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_INIT", PLAYER::BACK_INIT, PLAYER::BACK_INIT, 0.0f, false);

	//================================
	//     �÷��̾� �̵� 
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_WALK", PLAYER::FRONT_WALK0, PLAYER::FRONT_WALK3, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_WALK", PLAYER::RIGHT_WALK0, PLAYER::RIGHT_WALK5, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_WALK", PLAYER::LEFT_WALK0, PLAYER::LEFT_WALK5, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_WALK", PLAYER::BACK_WALK0, PLAYER::BACK_WALK3, AnimationFrame_, true);


	//================================
	//     �÷��̾� �� ��½! ���
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_HANDITEM", PLAYER::FRONT_HAND_INIT, PLAYER::FRONT_HAND_INIT, 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_HANDITEM", PLAYER::RIGHT_HAND_INIT, PLAYER::RIGHT_HAND_INIT, 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_HANDITEM", PLAYER::LEFT_HAND_INIT, PLAYER::LEFT_HAND_INIT, 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_HANDITEM", PLAYER::BACK_HAND_INIT, PLAYER::BACK_HAND_INIT, 0.0f, false);


	//================================
	//     �÷��̾� �̵� 
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_HANDITEMWALK", PLAYER::FRONT_WALK_HAND0, PLAYER::FRONT_WALK_HAND3, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_HANDITEMWALK", PLAYER::RIGHT_WALK_HAND0, PLAYER::RIGHT_WALK_HAND5, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_HANDITEMWALK", PLAYER::LEFT_WALK_HAND0, PLAYER::LEFT_WALK_HAND5, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_HANDITEMWALK", PLAYER::BACK_WALK_HAND0, PLAYER::BACK_WALK_HAND3, AnimationFrame_, true);


	//================================
	//     �÷��̾� ȣ�� ���
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_HOE", PLAYER::HOE_FRONT0, PLAYER::HOE_FRONT5, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_HOE", PLAYER::HOE_RIGHT0, PLAYER::HOE_RIGHT4, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_HOE", PLAYER::HOE_LEFT0, PLAYER::HOE_LEFT4, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_HOE", PLAYER::HOE_BACK0, PLAYER::HOE_BACK2, AnimationFrame_, true);


	//================================
	//     �÷��̾� ���Ѹ��� ���
	//================================

	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_WATER", PLAYER::WATER_FRONT0, PLAYER::WATER_FRONT2, 0.200f, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_WATER", PLAYER::WATER_RIGHT0, PLAYER::WATER_RIGHT2, 0.200f, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_WATER", PLAYER::WATER_LEFT0, PLAYER::WATER_LEFT2, 0.200f, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_WATER", PLAYER::WATER_BACK0, PLAYER::WATER_BACK2, 0.200f, true);

	//------< �ִϸ��̼� �ʱ�ȭ >------------------------------------------------------------------

	PlayerRenderer_->ChangeAnimation("FRONT_INIT");
	//PlayerMove_.SetFrontDir(true);
	LevelRegist("MainPlayer");
}



void Player::Update()
{
	PlayerDirCheck();
	//ObjectTileColl();
	SetCamera();
	PlayerUpdate();
	SetPlayerHandItemPos();
	ChangeLevel();

	if (CurrentLevel_ == "ShopLevel")
	{
		PlayerShopping();
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

