#include <GameEngineBase/GameEngineTime.h>


#include "ShopLevel.h"

#include "GameData.h"

#include "MoveTown.h"
#include "ShopFlag.h"

ShopLevel::ShopLevel()
	:
	Iter(MapObject_.begin())

{

	SetName("ShopLevel");

}

ShopLevel::~ShopLevel()
{

}

void ShopLevel::Loading()
{

}

void ShopLevel::LevelChangeStart()
{

	BackGroundFront_->GetRenderer()->SetImage("ShopFront.bmp");
	BackGroundFront_->GetRenderer()->SetPivot({ SHOP_SIZE_WEIGHT / 2, SHOP_SIZE_HEIGHT / 2 });

	BackGround_->GetRenderer()->SetImage("ShopBack.bmp");
	BackGround_->GetRenderer()->SetPivot({ SHOP_SIZE_WEIGHT / 2, SHOP_SIZE_HEIGHT / 2 });

	BackGround_->DirtTileMap_.TileRangeSetting(SHOP_CHIP_NUM_X, SHOP_CHIP_NUM_Y, { CHIP_SIZE, CHIP_SIZE });
	BackGround_->WetTileMap_.TileRangeSetting(SHOP_CHIP_NUM_X, SHOP_CHIP_NUM_Y, { CHIP_SIZE, CHIP_SIZE });

	LoadMapObject();


	Player_->SetPosition({ 310.f, 1280.f });
	Player_->SetDirtTileMap(&BackGround_->DirtTileMap_);
	Player_->SetWetTileMap(&BackGround_->WetTileMap_);

	//BgmPlayer = GameEngineSound::SoundPlayControl("05 - Spring (It's A Big World Outside).mp3");
	//Time = 5.0f;
}



void ShopLevel::LoadMapObject()
{

	char MapOject[SHOP_CHIP_NUM_Y][SHOP_CHIP_NUM_X] = {
	#include "Map/Shop.txt";

	};


	for (int y = 0; y < SHOP_CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < SHOP_CHIP_NUM_X; x++)
		{
			const char chip = MapOject[y][x];
			if (chip < 0) continue;

			const float4 pos = {
				x * CHIP_SIZE + CHIP_SIZE * 0.5f,
				y * CHIP_SIZE + CHIP_SIZE,
			};

			FARM_TILE TileState_ = static_cast<FARM_TILE>(chip);
			std::map<int, Items*>::iterator ThisIter;


			const float4 IndexPos = {
			  x * CHIP_SIZE ,
			  y * CHIP_SIZE,
			};


			TileIndex Index = { static_cast<int>(IndexPos.x / CHIP_SIZE), static_cast<int>(IndexPos.y / CHIP_SIZE) };
			int ChangeIndex = Index.X + (Index.Y * SHOP_CHIP_NUM_Y);


			switch (TileState_)
			{


			case FARM_TILE::SHOP_FLAG:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<ShopFlag>((int)PLAYLEVEL::OBJECT)));

				break;

			case FARM_TILE::MOVE_TOWN:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveTown>((int)PLAYLEVEL::OBJECT)));

				break;


			default:
				break;

			}
			ThisIter = --MapObject_.end();
			ThisIter->second->SetPosition(pos);


		}
	}

	Player_->CopyList(MapObject_);


}


void ShopLevel::Update()
{

	//float4 NextPos = Player_->GetPosition() + (float4::RIGHT *GameEngineTime::GetDeltaTime() * 150.f);
	//float4 CheckPos = NextPos + float4(0.0f, 20.0f);
	//std::list<Items*>::iterator Iter;

	//Time -= GameEngineTime::GetDeltaTime();



	//if (0 >= Time)
	//{
	//	//	BgmPlayer.Stop();
	//}



}