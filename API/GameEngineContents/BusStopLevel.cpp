#include "BusStopLevel.h"

#include "MoveFlag.h"
#include "GameData.h"
#include "TileData.h"
#include "Block.h"
#include <GameEngineBase/GameEngineTime.h>

BusStopLevel::BusStopLevel() 
	:
	FlowingFlower_(nullptr)
{

	SetName("BusStopLevel");
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
}

void BusStopLevel::Loading()
{
	//if (nullptr == Player::MainPlayer)
	//{
	//	Player::MainPlayer = CreateActor<Player>((int)PLAYLEVEL::PLAYER);
	//}

	//if (nullptr == Inventory::MainInventory)
	//{
	//	Inventory::MainInventory = CreateActor<Inventory>((int)PLAYLEVEL::INVENTORY);
	//}

	//if (nullptr == Inventory::MainInventory)
	//{
	//	MainUI::MainMainUI = CreateActor<MainUI>((int)PLAYLEVEL::MAINUI);
	//}


}

void BusStopLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	if (MapObject_.empty() == true)
	{
		LoadMapObject();
	}


	BackGroundFront_->GetRenderer()->SetImage("BusStop_Front.bmp");
	BackGroundFront_->GetRenderer()->SetPivot({ BUSSTOP_SIZE_WEIGHT / 2, BUSSTOP_SIZE_HEIGHT / 2 });

	BackGround_->GetRenderer()->SetImage("BusStop_Back.bmp");
	BackGround_->GetRenderer()->SetPivot({ BUSSTOP_SIZE_WEIGHT / 2,  BUSSTOP_SIZE_HEIGHT / 2 });

	FlowingFlower_ = CreateActor<FlowingFlower>(static_cast<int>(PLAYLEVEL::EFFECT));
	//FlowingFlower_->SetMax({ BUSSTOP_SIZE_WEIGHT, BUSSTOP_SIZE_HEIGHT });
	FlowingFlower_->SetMaxFocusPlayer(true);

//	Player::MainPlayer->SetDirtTileMap(&BackGround_->DirtTileMap_);

	FadeInOut* FadeInOut_ = CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
	FadeInOut_->SetFadeIn();

}

void BusStopLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		Inventory::MainInventory->NextLevelOn();
		MainUI::MainMainUI->NextLevelOn();
		PlayerEnergyFrame::MainPlayerEnergyFrame->NextLevelOn();
		PlayerHPFrame::MainPlayerHPFrame->NextLevelOn();

	}

}

BusStopLevel::~BusStopLevel() 
{
}



void BusStopLevel::Update()
{

}



void BusStopLevel::LoadMapObject()
{


	char MapOject[BUSSTOP_CHIP_NUM_Y][BUSSTOP_CHIP_NUM_X] = {
		#include "Map/BusStop.txt"

	};


	for (int y = 0; y < BUSSTOP_CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < BUSSTOP_CHIP_NUM_X; x++)
		{
			const char chip = MapOject[y][x];
			if (chip < 0) continue;

			const float4 pos = {
				x * CHIP_SIZE + CHIP_SIZE * 0.5f,
				y * CHIP_SIZE + CHIP_SIZE * 0.5f,
			};

			TILE_LIST TileState_ = static_cast<TILE_LIST>(chip);
			std::map<int, Items*>::iterator ThisIter;


			const float4 IndexPos = {
			  x * CHIP_SIZE ,
			  y * CHIP_SIZE,
			};


			TileIndex Index = { static_cast<int>(IndexPos.x / CHIP_SIZE), static_cast<int>(IndexPos.y / CHIP_SIZE) };
			int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);


			switch (TileState_)
			{
		
			case TILE_LIST::MOVE_TOWN:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFlag>((int)PLAYLEVEL::OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);
				ThisIter->second->CreateMoveFlag("MoveTown");

				break;
		
			case TILE_LIST::MOVE_FARM:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFlag>((int)PLAYLEVEL::OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);
				ThisIter->second->CreateMoveFlag("MoveFarm");

				break;

			case TILE_LIST::BLOCK:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<Block>((int)PLAYLEVEL::OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);

				break;

			default:
				break;

			}



		}
	}
	//Player_->CopyList(MapObject_);

}
