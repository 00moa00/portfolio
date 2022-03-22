#include "StardewValley.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

StardewValley::StardewValley() 
{
}

StardewValley::~StardewValley() 
{
}

void StardewValley::GameInit() 
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, {1280, 720});

	// ���ҽ��� �� �ε����� ���ϴ� ��Ȳ�� �ü��� ����.

	GameEngineImageManager::GetInst()->Load("D:\\portfolio\\APIResource\\sprite\\bmp\\CharacterAPI\\Bouncer.bmp", "Bouncer.bmp");
	//GameEngineImageManager::GetInst()->Load("D:\\Project\\AR40\\API\\Resources\\Image\\HPBAR.Bmp", "HPBAR.Bmp");


	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Play");
}

void StardewValley::GameLoop() 
{

}
void StardewValley::GameEnd() 
{

}