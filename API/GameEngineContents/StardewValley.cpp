#include "StardewValley.h"
#include "MyHouseLevel.h"
#include "TitleLevel.h"


#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>


#include <vector>


StardewValley::StardewValley()
{
}

StardewValley::~StardewValley()
{
}

void StardewValley::GameInit()
{

	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

	// ���� ���丮
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("API");
	ResourcesDir.Move("Resources");
	ResourcesDir.Move("All");

	//ResourcesDir.MoveParent("portfolio");
	//ResourcesDir.Move("APIResource");
	//ResourcesDir.Move("sprite");
	//ResourcesDir.Move("bmp");
	//ResourcesDir.Move("All");

	// �����ȿ� ��� �̹��� ������ ã�´�.
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	//Ÿ��Ʋ �ΰ�
	GameEngineImage* TitleImage = GameEngineImageManager::GetInst()->Find("TitleButtons.ko-KR.bmp");
	//TitleImage->Cut({ 800, 440 }, { 0,0 }); //0

	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 4; i++) {
			if (i == 2) continue; // �����÷��� ��ư ��ŵ
			TitleImage->Cut({ 148, 116 }, { 148 * (float)i, 374.f + (116.f * j) });//1 2 3
		}
	}

	//�÷��̾� �ٵ� 48, 96
	GameEngineImage* PlayerBody = GameEngineImageManager::GetInst()->Find("Player.bmp");
	PlayerBody->Cut({ 250, 250 });



	CreateLevel<TitleLevel>("Title");
	CreateLevel<MyHouseLevel>("Play");


	ChangeLevel("Play");


}

void StardewValley::GameLoop()
{

}
void StardewValley::GameEnd()
{
}
