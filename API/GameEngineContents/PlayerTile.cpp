#include "Player.h"
#include "TreeTop.h"
#include "MainUI.h"
#include "StoneEffect.h"
#include "WoodEffect.h"
#include "WateringCanEffect.h"

//******************************************************************************
//
//
//		Ÿ�� ���� �Լ� ������
//
//
//******************************************************************************

float4 Player::PlayerCollCheckPos()
{
	float4 Length = MoveDir_;

	if (float4::DOWN.CompareInt2D(MoveDir_))
	{
		Length = float4(0.0f, 24.0f);
	}
	if (float4::RIGHT.CompareInt2D(MoveDir_))
	{
		Length = float4(24.0f, 0.0f);
	}
	if (float4::LEFT.CompareInt2D(MoveDir_))
	{
		Length = float4(-24.0f, 0.0f);
	}
	if (float4::UP.CompareInt2D(MoveDir_))
	{
		Length = float4(0.0f, -24.0f);
	}

	float4 Pos = { GetPosition().x + Length.x, GetPosition().y + Length.y };

	return Pos;

}

void Player::CreateDirtTile()
{
	
	float4 Pos = PlayerCollCheckPos();


	TileIndex Index = DirtTileMap_->GetTileIndex({ Pos.x , Pos.y });
	int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

	std::map<int, FarmTile*>::iterator FindIter = DirtList_.find(ChangeIndex);
	std::map<int, FarmTile*>::iterator EndIter = DirtList_.end();

	std::map<int, Items*>::iterator ObjectFindIter = MapObject_.find(ChangeIndex);
	std::map<int, Items*>::iterator ObjectEndIter = MapObject_.end();

	
	// �ش� ���� �̹� �����ִٸ� ���ο� Ÿ�ϸ��� �������� ����

	if (FindIter != EndIter || ObjectFindIter != ObjectEndIter)
	{
			return;
	}

	else {
		FarmTile* Tile = DirtTileMap_->CreateTile<FarmTile>(static_cast<int>(Pos.x / CHIP_SIZE), static_cast<int>(Pos.y / CHIP_SIZE)
			, "hoeDirt.bmp", static_cast<int>(TILE_DIRT::BASIC), (int)PLAYLEVEL::DIRT);
		Tile->TileState_ = TILE_STATE::HOE_DIRT_CREATE;

		//Index = TileMap_->GetTileIndex({ Pos.x , Pos.y });
		//ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

		DirtList_.insert(std::make_pair(ChangeIndex, Tile));
	}
	//delete Tile;
}

void Player::CreateWaterTile()
{

	float4 Pos = PlayerCollCheckPos();

	TileIndex Index = WetTileMap_->GetTileIndex({ Pos.x , Pos.y });
	int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

	std::map<int, FarmTile*>::iterator FindIter = WetDirtList_.find(ChangeIndex);
	std::map<int, FarmTile*>::iterator EndIter = WetDirtList_.end();


	std::map<int, FarmTile*>::iterator FindDirtIter = DirtList_.find(ChangeIndex);
	std::map<int, FarmTile*>::iterator EndDirtIter = DirtList_.end();


	//�ش� ���� �̹� �����ִٸ� + ���� �������� ������ �н�

	if (FindIter != EndIter && FindDirtIter == EndDirtIter)
	{
		return;
	}

	if(FindIter == EndIter && FindDirtIter != EndDirtIter)
	{
	

		FarmTile* Tile = WetTileMap_->CreateTile<FarmTile>(static_cast<int>(Pos.x / CHIP_SIZE), static_cast<int>(Pos.y / CHIP_SIZE)
			, "hoeDirt.bmp",static_cast<int>(TILE_DIRT::BASIC_WET), (int)PLAYLEVEL::WETDIRT);
		Tile->TileState_ = TILE_STATE::HOE_DIRT_WATER;

		WetDirtList_.insert(std::make_pair(ChangeIndex, Tile));


	}


}

void Player::CreateWaterEffet()
{
	float4 Pos = PlayerCollCheckPos();
	float MarginX = 0;

	if (MoveDir_ .CompareInt2D(float4::RIGHT))
	{
		MarginX = 24.f;
	}

	if (MoveDir_.CompareInt2D(float4::LEFT))
	{
		MarginX = -24.f;
	}


	WateringCanEffect* WateringCanEffect_ = GetLevel()->CreateActor<WateringCanEffect>(static_cast<int>(PLAYLEVEL::BOTTOM_EFFECT));
	WateringCanEffect_->SetPosition({ Pos.x + MarginX, Pos.y});

	if (GetCurrentLevel() == "MyHouseLevel")
	{
		WateringCanEffect_->GetRenderer()->CameraEffectOff();
	}

}

void Player::CreateSeed()
{

	float4 Pos = PlayerCollCheckPos();

	TileIndex Index = WetTileMap_->GetTileIndex({ Pos.x , Pos.y });
	int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

	std::map<int, FarmTile*>::iterator FindDirtIter = DirtList_.find(ChangeIndex);
	std::map<int, FarmTile*>::iterator EndDirtIter = DirtList_.end();

	std::map<int, Crops*>::iterator FindSeedIter = SeedList_.find(ChangeIndex);
	std::map<int, Crops*>::iterator EndSeedIter = SeedList_.end();


	//���� ���� ���� ������, �̹� ������ ������
	if (FindDirtIter == EndDirtIter || FindSeedIter != EndSeedIter)
	{
		return;
	}


	//�ش� ���� ���������� ������ �ɴ´�.
	if (FindDirtIter != EndDirtIter)
	{

		//TODO: �ڵ� �������� Ÿ�Կ� ���� �ʱ�ȭ.
		
		GetCurrentItem()->SubItemCount();

		Crops* seed = GetCurrentItem()->CreateCrops();
			
		float4 TileSize_ = { 48.f, 48.f };
		float4 WorldPos = TileSize_;

		WorldPos.x *= static_cast<int>(Pos.x / CHIP_SIZE);
		WorldPos.y *= static_cast<int>(Pos.y / CHIP_SIZE);

		WorldPos += TileSize_.Half();

		//seed->GetRenderer()->SetPivot({ WorldPos.x, WorldPos.y - 24.f });
		seed->SetTileFindIndex(ChangeIndex);
		seed->SetPosition({ WorldPos.x, WorldPos.y - 24.f });

		SeedList_.insert(std::make_pair(ChangeIndex, seed));

	}


}

void Player::harvestingCrops()
{
	float4 Pos = PlayerCollCheckPos();

	TileIndex Index = WetTileMap_->GetTileIndex({ Pos.x , Pos.y });
	int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

	std::map<int, Crops*>::iterator FindSeedIter = SeedList_.find(ChangeIndex);
	std::map<int, Crops*>::iterator EndSeedIter = SeedList_.end();


	//������ ������, ������ ���� ��Ȯ���� ���°� �ƴ϶��
	if (FindSeedIter == EndSeedIter || FindSeedIter->second->GetisHarvest() == false)
	{
		return;
	}

	if (MainMouse_->isMouseClick())
	{
		FindSeedIter->second->DropCropsInMap();

		SeedList_.erase(ChangeIndex);
		//FindSeedIter->second->Death();
	}

}

void Player::CrushWood()
{

	for (Iter = MapObject_.begin(); Iter != MapObject_.end(); ++Iter) {

		if (Iter->second->ItemCheck(PlayerCollCheckPos(), GetScale()) == true)
		{
			if (Iter->second->GetItemType() == ITEMTYPE::WOOD)

			{

				WoodEffect* StoneAnimation_ = GetLevel()->CreateActor<WoodEffect>();
				StoneAnimation_->SetParticlesPosition({ Iter->second->GetPosition().x , Iter->second->GetPosition().y });

				//������ ���
				Iter->second->DropItemInMap();

				//�ش� ������ ����
				Iter->second->Death();
				MapObject_.erase(Iter);

				//������Ʈ �ʱ�ȭ
				TileState_ = TILE_COLL::INIT;
				PlayerState_ = PLAYER_UPDATE::INIT;

				//���ͷ����� �ʱ�ȭ
				Iter = MapObject_.begin();
			}

			else
			{
				return;
			}

			//�������� �ߴٸ� ��� ����
			SubEnergy(2.f);
		}

		else
		{
			PlayerState_ = PLAYER_UPDATE::INIT;
		}


	}
}

void Player::CrushStone()
{

	for (Iter = MapObject_.begin(); Iter != MapObject_.end(); ++Iter) {

		if (Iter->second->ItemCheck(PlayerCollCheckPos(), GetScale()) == true)
		{
			if (Iter->second->GetItemType() == ITEMTYPE::STONE)
			{

				StoneEffect* StoneAnimation_ = GetLevel()->CreateActor<StoneEffect>();
				StoneAnimation_->SetParticlesPosition({ Iter->second->GetPosition().x ,   Iter->second->GetPosition().y });

				//������ ���
				Iter->second->DropItemInMap();

				//�ش� ������ ����
				Iter->second->Death();
				Player::MapObject_.erase(Iter);

				//������Ʈ �ʱ�ȭ
				TileState_ = TILE_COLL::INIT;
				PlayerState_ = PLAYER_UPDATE::INIT;

				//���ͷ����� �ʱ�ȭ
				Iter = Player::MapObject_.begin();
			}

			else
			{
				return;
			}

			//������� �ߴٸ� ü�� ����
			SubEnergy(2.f);

		}

		else
		{
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

	}

}

void Player::CrushTree()
{

	for (Iter = Player::MapObject_.begin(); Iter != Player::MapObject_.end(); ++Iter)
	{

		if (Iter->second->ItemCheck(PlayerCollCheckPos(), GetScale()) == true
			&& Iter->second->GetItemType() == ITEMTYPE::TREE)
		{
			WoodEffect* StoneAnimation_ = GetLevel()->CreateActor<WoodEffect>();
			StoneAnimation_->SetParticlesPosition({ Iter->second->GetPosition().x , Iter->second->GetPosition().y });

			//������ ����ִ�
			if (Iter->second->GetDamage() > 0)
			{
				//�������� �����鼭 �ִϸ��̼� ����
				Iter->second->SubDamage();
				Iter->second->SetCrushAnimation();


				//������ �������� 2�� Top ����(�ش� ������Ʈ �Լ�)�� �������� ���
				if (Iter->second->GetDamage() == 2)
				{
				}

				//������Ʈ �ʱ�ȭ
				TileState_ = TILE_COLL::INIT;
				PlayerState_ = PLAYER_UPDATE::INIT;

				return;
			}

			//������ �������� 0�̸� (�ֵ��̱��� ����)
			else
			{
				//��� ������
				Iter->second->DropItemInMap();

				//�ش� ������ ����
				Iter->second->Death();
				Player::MapObject_.erase(Iter);

				//������Ʈ �ʱ�ȭ
				TileState_ = TILE_COLL::INIT;
				PlayerState_ = PLAYER_UPDATE::INIT;


				//���ͷ����� �ʱ�ȭ
				Iter = Player::MapObject_.begin();

			}
			//�������� �ߴٸ� ��� ����
			SubEnergy(2.f);

		}

		//�� ���� �����ٸ�
		else
		{
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

	}
}

void Player::GetItem()
{

	std::map<int, Items*>::iterator GetItemIter = MapObject_.begin();


	for (; GetItemIter != MapObject_.end(); ++GetItemIter) {

		if (GetItemIter->second->ItemCheck(PlayerCollCheckPos(), GetScale()) == true
			&& GetItemIter->second->GetItemType() == ITEMTYPE::GETITEM
			&& MainMouse_->isMouseClick() == true
			&& GetCurrentItem()->GetItemType() != ITEMTYPE::TOOL)
		{
			//�̺�Ʈ���� �ƴ� �������� �����ϴ� ���� �ִٸ� ���� ���� �ؾ���
			GetItemIter->second->ItemCollPlayer();
			MapObject_.erase(GetItemIter);
			GetItemIter = MapObject_.begin();
		}

		else
		{
			PlayerState_ = PLAYER_UPDATE::INIT;

		}
	}
}

void Player::CheckShippingBox()
{
	std::map<int, Items*>::iterator ShippingIter = MapObject_.begin();

	if (GetCurrentLevel() == "MyFarmLevel")
	{
		for (; ShippingIter != MapObject_.end(); ++ShippingIter) {

			if (ShippingIter->second->ItemCheck(PlayerCollCheckPos(), GetScale()) == true
				&& ShippingIter->second->GetItemType() == ITEMTYPE::SHIPPINGBOX)
			{
				//�̺�Ʈ���� �ƴ� �������� �����ϴ� ���� �ִٸ� ���� ���� �ؾ���
				ShippingIter->second->ItemCollPlayer();
			}

			else
			{
				ShippingIter->second->ItemCollFalsePlayer();
			}
		}
	}
}

void Player::ClearWetDirtTile()
{
	if (WetDirtList_.empty() == false)
	{
		if (MainUI::MainMainUI->DayOver() == true)
		{
			WetTileMap_->DeleteTile();
			WetDirtList_.erase(WetDirtList_.begin(), WetDirtList_.end());
		}
	}
}

void Player::ChangeDirtTile()
{

	std::map<int, FarmTile*>::iterator EndIter = DirtList_.end();



	for (int i = 0; i < FARM_CHIP_NUM_X * FARM_CHIP_NUM_Y; ++i)
	{

		std::map<int, FarmTile*>::iterator FindLeftIter = DirtList_.find(i - 1);
		std::map<int, FarmTile*>::iterator FindThisIter = DirtList_.find(i);
		std::map<int, FarmTile*>::iterator FindRightIter = DirtList_.find(i + 1);
		std::map<int, FarmTile*>::iterator FindTopIter = DirtList_.find(i - FARM_CHIP_NUM_Y);
		std::map<int, FarmTile*>::iterator FindBottomIter = DirtList_.find(i + FARM_CHIP_NUM_Y);


		//���� ã������ Ÿ���� ���� ������ �н�
		if (FindThisIter == EndIter) continue;



		//------< �� �Ʒ� �ƹ��͵� ������ x��, ������ >------------------------------------------------------------------

		if (FindTopIter == EndIter && FindBottomIter == EndIter)
		{
			//===================================================
			//   case 1 ���� Ÿ���� ���µ� ������ Ÿ���� �ִ°��
			//===================================================

			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_LEFT));

			}

			//===================================================
			//   case 2 ����Ÿ���� �ִµ� ������ Ÿ���� ���°��
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_RIGHT) );

			}

			//===================================================
			//   case 3 ���� ������ �� �� �ִ� ���
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_MIDDLE) );

			}


		}

		//------< �� �� �ƹ��͵� ������ y��, ������ >------------------------------------------------------------------

		if (FindLeftIter == EndIter && FindRightIter == EndIter)
		{

			//===================================================
			//   case 1 ���� Ÿ���� ���µ� �Ʒ��� Ÿ���� �ִ°��
			//===================================================

			if (FindTopIter == EndIter && FindBottomIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_TOP) );

			}


			//===================================================
			//   case 2 ����Ÿ���� �ִµ� �Ʒ��� Ÿ���� ���°��
			//===================================================

			if (FindTopIter != EndIter && FindBottomIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_MIDDLE) );

			}


			//===================================================
			//   case 3 ���� �Ʒ��� �� �� �ִ� ���
			//===================================================

			if (FindTopIter != EndIter && FindBottomIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_BOTTOM) );

			}

		}


		//------< �Ʒ��� �ִµ� ���� ������� >------------------------------------------------------------------


		if (FindTopIter == EndIter && FindBottomIter != EndIter)
		{

			//===================================================
			//   case 1 ���� Ÿ���� ���µ� ������ Ÿ���� �ִ°��
			//===================================================
			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_TOP) );

			}


			//===================================================
			//   case 2 ����Ÿ���� �ִµ� ������ Ÿ���� ���°��
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_TOP) );

			}


			//===================================================
			//   case 3 ���� ������ �� �� �ִ� ���
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_TOP) );

			}


		}

		//------< ���� �ִµ� �Ʒ��� ���� ��� >------------------------------------------------------------------

		if (FindTopIter != EndIter && FindBottomIter == EndIter)
		{

			//===================================================
			//   case 1 ���� Ÿ���� ���µ� ������ Ÿ���� �ִ°��
			//===================================================
			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_BOTTOM) );

			}


			//===================================================
			//   case 2 ����Ÿ���� �ִµ� ������ Ÿ���� ���°��
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_BOTTOM) );

			}


			//===================================================
			//   case 3 ���� ������ �� �� �ִ� ���
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_BOTTOM) );

			}

		}


		//------< ���Ʒ� �Ѵ� �ִ� ��� >------------------------------------------------------------------

		if (FindTopIter != EndIter && FindBottomIter != EndIter)
		{

			//===================================================
			//   case 1 ���� Ÿ���� ���µ� ������ Ÿ���� �ִ°��
			//===================================================
			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_MIDDLE) );

			}


			//===================================================
			//   case 2 ����Ÿ���� �ִµ� ������ Ÿ���� ���°��
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_MIDDLE) );

			}


			//===================================================
			//   case 3 ���� ������ �� �� �ִ� ���
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_MIDDLE) );

			}

		}

		//------< ��濡 �ƹ��͵� ���ٸ� >------------------------------------------------------------------

		if (FindLeftIter == EndIter && FindRightIter == EndIter && FindTopIter == EndIter && FindBottomIter == EndIter)
		{
			FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::BASIC) );

		}

		//------< �̸��Ϳ� ������ �ʴ´� >------------------------------------------------------------------

		//if (FindLeftIter == EndIter || FindRightIter == EndIter || FindTopIter == EndIter || FindBottomIter == EndIter)
		//{
		//	return;

		//}

	}


}

void Player::ChangeWetDirtTile()
{

	std::map<int, FarmTile*>::iterator EndIter = WetDirtList_.end();


	for (int i = 0; i < FARM_CHIP_NUM_X * FARM_CHIP_NUM_Y; ++i)
	{

		std::map<int, FarmTile*>::iterator FindLeftIter = WetDirtList_.find(i - 1);
		std::map<int, FarmTile*>::iterator FindThisIter = WetDirtList_.find(i);
		std::map<int, FarmTile*>::iterator FindRightIter = WetDirtList_.find(i + 1);
		std::map<int, FarmTile*>::iterator FindTopIter = WetDirtList_.find(i - FARM_CHIP_NUM_Y);
		std::map<int, FarmTile*>::iterator FindBottomIter = WetDirtList_.find(i + FARM_CHIP_NUM_Y);


		//���� ã������ Ÿ���� ���� ������ �н�
		if (FindThisIter == EndIter) continue;



		//------< �� �Ʒ� �ƹ��͵� ������ x��, ������ >------------------------------------------------------------------

		if (FindTopIter == EndIter && FindBottomIter == EndIter)
		{
			//===================================================
			//   case 1 ���� Ÿ���� ���µ� ������ Ÿ���� �ִ°��
			//===================================================

			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_LEFT_WET));
				
			}

			//===================================================
			//   case 2 ����Ÿ���� �ִµ� ������ Ÿ���� ���°��
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_RIGHT_WET));

			}

			//===================================================
			//   case 3 ���� ������ �� �� �ִ� ���
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_MIDDLE_WET));

			}


		}

		//------< �� �� �ƹ��͵� ������ y��, ������ >------------------------------------------------------------------

		if (FindLeftIter == EndIter && FindRightIter == EndIter)
		{

			//===================================================
			//   case 1 ���� Ÿ���� ���µ� �Ʒ��� Ÿ���� �ִ°��
			//===================================================

			if (FindTopIter == EndIter && FindBottomIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_TOP_WET));

			}


			//===================================================
			//   case 2 ����Ÿ���� �ִµ� �Ʒ��� Ÿ���� ���°��
			//===================================================

			if (FindTopIter != EndIter && FindBottomIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_MIDDLE_WET));

			}


			//===================================================
			//   case 3 ���� �Ʒ��� �� �� �ִ� ���
			//===================================================

			if (FindTopIter != EndIter && FindBottomIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_BOTTOM_WET));

			}

		}


		//------< �Ʒ��� �ִµ� ���� ������� >------------------------------------------------------------------


		if (FindTopIter == EndIter && FindBottomIter != EndIter)
		{

			//===================================================
			//   case 1 ���� Ÿ���� ���µ� ������ Ÿ���� �ִ°��
			//===================================================
			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_TOP_WET));

			}


			//===================================================
			//   case 2 ����Ÿ���� �ִµ� ������ Ÿ���� ���°��
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_TOP_WET));

			}


			//===================================================
			//   case 3 ���� ������ �� �� �ִ� ���
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_TOP_WET));

			}


		}

		//------< ���� �ִµ� �Ʒ��� ���� ��� >------------------------------------------------------------------

		if (FindTopIter != EndIter && FindBottomIter == EndIter)
		{

			//===================================================
			//   case 1 ���� Ÿ���� ���µ� ������ Ÿ���� �ִ°��
			//===================================================
			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_BOTTOM_WET));

			}


			//===================================================
			//   case 2 ����Ÿ���� �ִµ� ������ Ÿ���� ���°��
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_BOTTOM_WET));

			}


			//===================================================
			//   case 3 ���� ������ �� �� �ִ� ���
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_BOTTOM_WET));

			}

		}


		//------< ���Ʒ� �Ѵ� �ִ� ��� >------------------------------------------------------------------

		if (FindTopIter != EndIter && FindBottomIter != EndIter)
		{

			//===================================================
			//   case 1 ���� Ÿ���� ���µ� ������ Ÿ���� �ִ°��
			//===================================================
			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_MIDDLE_WET));

			}


			//===================================================
			//   case 2 ����Ÿ���� �ִµ� ������ Ÿ���� ���°��
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_MIDDLE_WET));

			}


			//===================================================
			//   case 3 ���� ������ �� �� �ִ� ���
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_MIDDLE_WET));

			}

		}

		//------< ��濡 �ƹ��͵� ���ٸ� >------------------------------------------------------------------

		if (FindLeftIter == EndIter && FindRightIter == EndIter && FindTopIter == EndIter && FindBottomIter == EndIter)
		{
			FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::BASIC_WET));

		}

		//------< �̸��Ϳ� ������ �ʴ´� >------------------------------------------------------------------

		//if (FindLeftIter == EndIter || FindRightIter == EndIter || FindTopIter == EndIter || FindBottomIter == EndIter)
		//{
		//	return;

		//}

	}

}