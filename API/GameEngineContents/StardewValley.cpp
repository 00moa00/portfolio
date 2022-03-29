#include "StardewValley.h"
#include "MyHouseLevel.h"
#include "TitleLevel.h"
#include "CustomLevel.h"
#include "CustomData.h"

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
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, {1280, 720});

	// ���� ���丮
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("API");
	ResourcesDir.MoveParent("portfolio");
	ResourcesDir.Move("APIResource");
	ResourcesDir.Move("sprite");
	ResourcesDir.Move("bmp");
	ResourcesDir.Move("All");

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
			TitleImage->Cut({ 148, 116 }, { 148 * (float)i, 374.f + (116.f * j)});//1 2 3
		}
	}

	//�÷��̾� �ٵ� 32 64
	GameEngineImage* PlayerBody = GameEngineImageManager::GetInst()->Find("farmer_girl_base_bald.bmp");
	PlayerBody->Cut({ 32, 64 });

	//�÷��̾� ���  32 64
	GameEngineImage* PlayerHair = GameEngineImageManager::GetInst()->Find("hairstyles.bmp");
	PlayerHair->Cut({ 32, 64 });

	//�÷��̾� ����  32 64
	GameEngineImage* PlayerPants = GameEngineImageManager::GetInst()->Find("pants.bmp");
	PlayerPants->Cut({ 32, 64 });

	//�÷��̾� ����  16 16
	GameEngineImage* PlayerShirts = GameEngineImageManager::GetInst()->Find("shirts2.bmp");
	PlayerShirts->Cut({ 16, 16 });



	CreateLevel<TitleLevel>("Title");
	CreateLevel<CustomLevel>("Custom");
	CreateLevel<MyHouseLevel>("Play");

	ChangeLevel("Title");


}

void StardewValley::GameLoop() 
{

}
void StardewValley::GameEnd() 
{
	CustomData::Destroy();
}