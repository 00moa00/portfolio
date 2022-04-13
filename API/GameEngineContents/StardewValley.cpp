#include "StardewValley.h"
#include "MyFarmLevel.h"
#include "TitleLevel.h"
#include "MyHouseLevel.h"

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


	//------< ������ �ʱ�ȭ >------------------------------------------------------------------

	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

	//------< Ű�Է� �ʱ�ȭ >------------------------------------------------------------------

	if (false == GameEngineInput::GetInst()->IsKey("MoveUp"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Enter", VK_RETURN);
		GameEngineInput::GetInst()->CreateKey("LeftClick", MK_LBUTTON);
	}


	{
		//------< �̹��� ���� ���丮 >------------------------------------------------------------------

		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("All");


		//------< �̹��� ���� ã�� >------------------------------------------------------------------

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		//------< �̹��� Cut >------------------------------------------------------------------
	}



	{
		//------< ���� ���� ���丮 >------------------------------------------------------------------

		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sound");


		//------< ���� ���� ã�� >------------------------------------------------------------------
		
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile();

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineSound::LoadRes(AllImageFileList[i].GetFullPath());
		}

	}



	//------< �̹��� Cut >------------------------------------------------------------------

	//================================
	//     Ÿ��Ʋ �޴� 148 116
	//================================
	GameEngineImage* TitleImage = GameEngineImageManager::GetInst()->Find("TitleButtons.ko-KR.bmp");

	for (int j = 0; j < 2; j++) 
	{
		for (int i = 0; i < 4; i++) 
		{
			if (i == 2) continue; // �����÷��� ��ư ��ŵ
			TitleImage->Cut({ 148, 116 }, { 148 * (float)i, 374.f + (116.f * j) });//1 2 3
		}
	}

	//================================
	//     �÷��̾� 48 96
	//================================
	GameEngineImage* PlayerBody = GameEngineImageManager::GetInst()->Find("Player.bmp");
	PlayerBody->Cut({ 48, 96 });


	//================================
	//     �� ������ 48 48
	//================================
	GameEngineImage* SpringObjects = GameEngineImageManager::GetInst()->Find("springobjects.bmp");
	SpringObjects->Cut({ 48, 48 });


	//================================
	//     �÷��̾� �� 48 96
	//================================
	GameEngineImage* PlayerTool = GameEngineImageManager::GetInst()->Find("tools.bmp");
	PlayerTool->Cut({ 48, 96 });


	//================================
	//    ȣ�̷� �� ��
	//================================
	GameEngineImage* HoeDirt = GameEngineImageManager::GetInst()->Find("hoeDirt.bmp");
	HoeDirt->Cut({ 48, 48 });


	//------< ���� ��� >------------------------------------------------------------------

	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<MyHouseLevel>("MyHouseLevel");
	CreateLevel<MyFarmLevel>("MyFarmLevel");


	ChangeLevel("MyFarmLevel");


}

void StardewValley::GameLoop()
{
	
}
void StardewValley::GameEnd()
{
}
