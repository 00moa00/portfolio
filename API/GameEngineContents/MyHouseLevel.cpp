#include "MyHouseLevel.h"
#include "GameData.h"

#include "Block.h"
#include "BadBottom.h"
#include "BadTop.h"
#include "Chair.h"
#include "Table.h"
#include "Tv.h"
#include "Hitter.h"
#include "MoveFarm.h"

#include <GameEngineBase/GameEngineTime.h>


MyHouseLevel::MyHouseLevel()
	:
	Iter(MapObject_.begin())
{
	SetName("MyHouseLevel");

}

MyHouseLevel::~MyHouseLevel()
{
}

void MyHouseLevel::Loading()
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

void MyHouseLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{

//	BackGroundFront_->GetRenderer()->SetImage("FarmFront.bmp");
//	BackGroundFront_->GetRenderer()->SetPivot({ FARM_SIZE_WEIGHT / 2, FARM_SIZE_HEIGHT / 2 });


	BackGround_->GetRenderer()->SetImage("PlayerHouse.bmp");
	BackGround_->GetRenderer()->CameraEffectOff();
	BackGround_->GetRenderer()->SetPivot({ GameEngineWindow::GetScale().Half().x,  GameEngineWindow::GetScale().Half().y });

	LoadMapObject();

	Player::MainPlayer->SetPosition({ HOUSE_SIZE_WEIGHT / 2, (HOUSE_SIZE_HEIGHT / 2) + 100.f });
	Player::MainPlayer->Renderer()->CameraEffectOff();


}

void MyHouseLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		Inventory::MainInventory->NextLevelOn();

	}
}


void MyHouseLevel::LoadMapObject()
{

    char MapOject[MYHOUSE_CHIP_NUM_Y][MYHOUSE_CHIP_NUM_X] = {
    #include "Map/FarmerHouse.txt";

    };
	 

    for (int y = 0; y < MYHOUSE_CHIP_NUM_Y; y++)
    {
        for (int x = 0; x < MYHOUSE_CHIP_NUM_X; x++)
        {
            const char chip = MapOject[y][x];
            if (chip < 0) continue;

            const float4 pos = {
                x * CHIP_SIZE + CHIP_SIZE * 0.5f,
                y * CHIP_SIZE + CHIP_SIZE,
            };

			MYHOUSE_TILE TileState_ = static_cast<MYHOUSE_TILE>(chip);
			std::map<int, Items*>::iterator ThisIter;

			const float4 IndexPos = {
			  x * CHIP_SIZE ,
			  y * CHIP_SIZE,
			};

			TileIndex Index = { static_cast<int>(IndexPos.x / CHIP_SIZE), static_cast<int>(IndexPos.y / CHIP_SIZE) };
			int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);


			switch (TileState_)
			{
			case MYHOUSE_TILE::BAD_BOTTOM:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<BadBottom>((int)PLAYLEVEL::TOP_OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition({ pos.x, pos.y });

				break;
		

			case MYHOUSE_TILE::MOVE_FARM:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFarm>((int)PLAYLEVEL::TOP_OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->GetRenderer()->CameraEffectOff();

				break;
			default:
				break;
			}

			ThisIter = --MapObject_.end();
			ThisIter->second->SetPosition(pos);

     
        }
    }

	Player::MainPlayer->CopyList(MapObject_);

}


void MyHouseLevel::Update()
{

}



	//플레이어가 행동 할때마다 스테미너 감소. 테스트용
	////PlayerEnergyBar_->SubEnergyBar(PlayerBody_->GetEnergy());
	//		if (GetAsyncKeyState(MK_LBUTTON))
	//{
	//	GameEngine::GetInst().ChangeLevel("Title");
	//}

