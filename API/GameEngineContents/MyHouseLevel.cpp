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

	TileState_(TILE_COLL::INIT),
	MainUI_(nullptr),
	Player_(nullptr),
	Iter(MapObject_.begin())

{
}

MyHouseLevel::~MyHouseLevel()
{
}

void MyHouseLevel::Loading()
{

	
	Player_ = CreateActor<Player>((int)PLAYLEVEL::PLAYER);
	Player_->SetPosition({ GameEngineWindow::GetScale().Half().x,  GameEngineWindow::GetScale().Half().y + 100.f });
	Player_->Renderer()->CameraEffectOff();

	MainUI_ = CreateActor<MainUI>((int)PLAYLEVEL::MAINUI);


	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);

	BackGround_->GetRenderer()->SetImage("PlayerHouse.bmp");
	BackGround_->GetRenderer()->CameraEffectOff();
	BackGround_->GetRenderer()->SetPivot({ GameEngineWindow::GetScale().Half().x,  GameEngineWindow::GetScale().Half().y});



	BgmPlayer = GameEngineSound::SoundPlayControl("05 - Spring (It's A Big World Outside).mp3");
	Time = 5.0f;


	LoadMapObject();
	//Inventory_->AllUpdateOff();
}

void MyHouseLevel::LevelChangeStart()
{

	BgmPlayer.Stop();


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
                x * CHIP_SIZE_F + CHIP_SIZE_F * 0.5f,
                y * CHIP_SIZE_F + CHIP_SIZE_F,
            };

			MYHOUSE_OBJECT_TILE TileState_ = static_cast<MYHOUSE_OBJECT_TILE>(chip);
			std::list<Items*>::iterator ThisIter;

			switch (TileState_)
			{
			case MYHOUSE_OBJECT_TILE::BAD_BOTTOM:

				MapObject_.push_back(CreateActor<BadBottom>((int)PLAYLEVEL::TOPOBJECT));
				ThisIter = --MapObject_.end();
				(*ThisIter)->SetPosition({ pos.x, pos.y });

				break;
		

			//	break;
			default:
				break;
			}

			ThisIter = --MapObject_.end();
			(*ThisIter)->SetPosition({ pos.x, pos.y });
			
     
        }
    }

}


void MyHouseLevel::Update()
{
	

	Time -= GameEngineTime::GetDeltaTime();



	if (0 >= Time)
	{
		BgmPlayer.Stop();
	}

	switch (TileState_)
	{
	case TILE_COLL::INIT :
		Iter = MapObject_.begin();
		TileState_ = TILE_COLL::NOTACT;

	break;

	case TILE_COLL::NOTACT :
	

		for (; Iter != MapObject_.end(); ++Iter) {

			if ((*Iter)->IsWall(Player_->GetPosition(), Player_->GetScale(), Player_->CurrentDir()) == true) {
				
				Player_->SetBreakMove(true);
				//TileState_ = TILE_COLL::COll;
				break;
			}

			else {

				Player_->SetBreakMove(false);
			}

		}


		if (Iter == MapObject_.end()) {
			Iter = MapObject_.begin();
		}
		break;

	case TILE_COLL::COll:


		if ((*Iter)->IsWall(Player_->GetPosition(), Player_->GetScale(), Player_->CurrentDir())==false) {
			Player_->SetSpeed(150.f);
			Player_->SetBreakMove(false);

			Iter = MapObject_.begin();
			TileState_ = TILE_COLL::NOTACT;
		}

		break;


	}



	//플레이어가 행동 할때마다 스테미너 감소. 테스트용
	////PlayerEnergyBar_->SubEnergyBar(PlayerBody_->GetEnergy());
	//		if (GetAsyncKeyState(MK_LBUTTON))
	//{
	//	GameEngine::GetInst().ChangeLevel("Title");
	//}
}
