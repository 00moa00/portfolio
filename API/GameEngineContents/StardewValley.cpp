#include "StardewValley.h"
#include "MyFarmLevel.h"
#include "TitleLevel.h"
#include "MyHouseLevel.h"
#include "BusStopLevel.h"
#include "TownLevel.h"
#include "ShopLevel.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>

#include <vector>


StardewValley::StardewValley()
{
}

StardewValley::~StardewValley()
{
}

void StardewValley::GameInit()
{


	//------< 윈도우 초기화 >------------------------------------------------------------------

	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

	//------< 키입력 초기화 >------------------------------------------------------------------

	if (false == GameEngineInput::GetInst()->IsKey("MoveUp"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');

		GameEngineInput::GetInst()->CreateKey("Enter", VK_RETURN);

		GameEngineInput::GetInst()->CreateKey("LeftClick", MK_LBUTTON);
		GameEngineInput::GetInst()->CreateKey("RightClick", MK_RBUTTON);

		GameEngineInput::GetInst()->CreateKey("DebugRendereChange", 'R');
		GameEngineInput::GetInst()->CreateKey("TimeAdd", 'T');


		GameEngineInput::GetInst()->CreateKey("KeyLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("KeyRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("KeyUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("KeyDown", VK_DOWN);

	}


	{
		//------< 사운드 현재 디렉토리 >------------------------------------------------------------------

		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sound");


		//------< 사운드 파일 찾기 >------------------------------------------------------------------
		
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile();

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineSound::LoadRes(AllImageFileList[i].GetFullPath());
		}

	}

	//------< 이미지 현재 디렉토리 >------------------------------------------------------------------

	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sprite");
		ResourcesDir.Move("Player");


		//------< 이미지 파일 찾기 >------------------------------------------------------------------

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		//------< 이미지 Cut >------------------------------------------------------------------

		//================================
		//     플레이어 48 96
		//================================
		GameEngineImage* PlayerBody = GameEngineImageManager::GetInst()->Find("Player.bmp");
		PlayerBody->Cut({ 48, 96 });



		//================================
		//     플레이어 호미 250	150
		//================================
		GameEngineImage* PlayerHoeRight = GameEngineImageManager::GetInst()->Find("hoe_right.bmp");
		PlayerHoeRight->Cut({ 250, 150 });

		GameEngineImage* PlayerHoeLeft = GameEngineImageManager::GetInst()->Find("hoe_left.bmp");
		PlayerHoeLeft->Cut({ 250, 150 });


		GameEngineImage* PlayerHoeFront = GameEngineImageManager::GetInst()->Find("hoe_front.bmp");
		PlayerHoeFront->Cut({ 250, 150 });

		GameEngineImage* PlayerHoeBack = GameEngineImageManager::GetInst()->Find("hoe_back.bmp");
		PlayerHoeBack->Cut({ 250, 150 });


		//================================
		//     플레이어 도끼 250	150
		//================================
		GameEngineImage* PlayerAxeRight = GameEngineImageManager::GetInst()->Find("axe_right.bmp");
		PlayerAxeRight->Cut({ 250, 150 });

		GameEngineImage* PlayerAxeLeft = GameEngineImageManager::GetInst()->Find("axe_left.bmp");
		PlayerAxeLeft->Cut({ 250, 150 });

		GameEngineImage* PlayerAxeFront = GameEngineImageManager::GetInst()->Find("axe_front.bmp");
		PlayerAxeFront->Cut({ 250, 150 });

		GameEngineImage* PlayerAxeBack = GameEngineImageManager::GetInst()->Find("axe_back.bmp");
		PlayerAxeBack->Cut({ 250, 150 });



		//================================
		//     플레이어 곡괭이 250	150
		//================================

		GameEngineImage* PlayerPiRight = GameEngineImageManager::GetInst()->Find("pickaxe_front.bmp");
		PlayerPiRight->Cut({ 250, 150 });

		GameEngineImage* PlayerPiLeft = GameEngineImageManager::GetInst()->Find("pickaxe_left.bmp");
		PlayerPiLeft->Cut({ 250, 150 });

		GameEngineImage* PlayerPiFront = GameEngineImageManager::GetInst()->Find("pickaxe_front.bmp");
		PlayerPiFront->Cut({ 250, 150 });

		GameEngineImage* PlayerPiBack = GameEngineImageManager::GetInst()->Find("pickaxe_back.bmp");
		PlayerPiBack->Cut({ 250, 150 });


		//================================
		//     플레이어 물 250	150
		//================================
		GameEngineImage* PlayeWaterRight = GameEngineImageManager::GetInst()->Find("wateringcan_right.bmp");
		PlayeWaterRight->Cut({ 250, 150 });

		GameEngineImage* PlayerWaterLeft = GameEngineImageManager::GetInst()->Find("wateringcan_left.bmp");
		PlayerWaterLeft->Cut({ 250, 150 });

		GameEngineImage* PlayerWaterFront = GameEngineImageManager::GetInst()->Find("wateringcan_front.bmp");
		PlayerWaterFront->Cut({ 250, 150 });

		GameEngineImage* PlayerWaterBack = GameEngineImageManager::GetInst()->Find("wateringcan_back.bmp");
		PlayerWaterBack->Cut({ 250, 150 });


	}


	{
		//------< 이미지 현재 디렉토리 >------------------------------------------------------------------

		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sprite");


		//------< 이미지 파일 찾기 >------------------------------------------------------------------

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		//------< 이미지 Cut >------------------------------------------------------------------


		//================================
		//     타이틀 메뉴 148 116
		//================================
		GameEngineImage* TitleImage = GameEngineImageManager::GetInst()->Find("TitleButtons.ko-KR.bmp");

		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (i == 2) continue; // 협동플레이 버튼 스킵
				TitleImage->Cut({ 148, 116 }, { 148 * (float)i, 374.f + (116.f * j) });//1 2 3
			}
		}


		//================================
		//     봄 아이템 48 48
		//================================
		GameEngineImage* SpringObjects = GameEngineImageManager::GetInst()->Find("springobjects.bmp");
		SpringObjects->Cut({ 48, 48 });


		//================================
		//     플레이어 툴 48 96
		//================================
		GameEngineImage* PlayerTool = GameEngineImageManager::GetInst()->Find("tools.bmp");
		PlayerTool->Cut({ 48, 96 });


		//================================
		//    호미로 판 땅
		//================================
		GameEngineImage* HoeDirt = GameEngineImageManager::GetInst()->Find("hoeDirt.bmp");
		HoeDirt->Cut({ 48, 48 });


		//================================
		//    씨앗
		//================================
		GameEngineImage* crops = GameEngineImageManager::GetInst()->Find("crops.bmp");
		crops->Cut({ 48, 96 });


		//================================
		//		폰트 블랙
		//================================
		GameEngineImage* Font = GameEngineImageManager::GetInst()->Find("font_colored.bmp");
		Font->Cut({ 12, 21 });

		//================================
		//		폰트 화이트
		//================================
		GameEngineImage* WhiteFont = GameEngineImageManager::GetInst()->Find("font_colored_White.bmp");
		WhiteFont->Cut({ 9, 16 });

		//================================
		//		OakTree
		//================================
		GameEngineImage* OakTree = GameEngineImageManager::GetInst()->Find("Oak_Tree_AnimaionSheet.bmp");
		OakTree->Cut({ 152, 240 });

		//================================
		//		MapleTree
		//================================
		GameEngineImage* MapleTree = GameEngineImageManager::GetInst()->Find("Maple_Tree_AnimationSheet.bmp");
		MapleTree->Cut({ 152, 228 });

		//================================
		//		MahoganyTree
		//================================
		GameEngineImage* MahoganyTree = GameEngineImageManager::GetInst()->Find("Mahogany_Tree_AnimaionSheet.bmp");
		MahoganyTree->Cut({ 152, 238 });

		//================================
		//		FineTree
		//================================
		GameEngineImage* FineTree = GameEngineImageManager::GetInst()->Find("Fine_Tree_AnimaionSheet.bmp");
		FineTree->Cut({ 152, 246 });

		//================================
		//		요일
		//================================
		GameEngineImage* Week_Sheet = GameEngineImageManager::GetInst()->Find("Week_Sheet.bmp");
		Week_Sheet->Cut({ 42, 26 });
	}



	//------< 레벨 등록 >------------------------------------------------------------------

	//CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<MyHouseLevel>("MyHouseLevel");
	CreateLevel<MyFarmLevel>("MyFarmLevel");
	CreateLevel<BusStopLevel>("BusStopLevel");
	CreateLevel<TownLevel>("TownLevel");
	CreateLevel<ShopLevel>("ShopLevel");

	ChangeLevel("MyFarmLevel");


}

void StardewValley::GameLoop()
{
}
void StardewValley::GameEnd()
{
}
