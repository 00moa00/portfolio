#include "Parsnip_Crops.h"
#include "Items.h"
#include "Pasnip.h"

Parsnip_Crops::Parsnip_Crops() 
{
}

Parsnip_Crops::~Parsnip_Crops() 
{
}

void Parsnip_Crops::Start()
{
	CropRenderer_ = CreateRenderer("crops.bmp");
	CropRenderer_->SetIndex(static_cast<size_t>(CROPS::PARSNIP_SEED));
	CropRenderer_->CameraEffectOn();

}

void Parsnip_Crops::Update()
{
	GrowingCropsTime();

	//�ٲ� �������� �ε����� ��ü 
	if ( GetGrowingDay() == 1 && CropsUpdateState_ == CROPS_UPDATE::ADD_GROWING_DAY)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::PARSNIP_GROW0));
	}
	
	if (GetGrowingDay() == 2 && CropsUpdateState_ == CROPS_UPDATE::ADD_GROWING_DAY)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::PARSNIP_GROW1));

	}

	if (GetGrowingDay() == 3 && CropsUpdateState_ == CROPS_UPDATE::ADD_GROWING_DAY)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::PARSNIP_GROW2));

	}

	if (GetGrowingDay() == 4 && CropsUpdateState_ == CROPS_UPDATE::ADD_GROWING_DAY)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::PARSNIP_GROW3));

	}

	if (GetGrowingDay() == 5 && CropsUpdateState_ == CROPS_UPDATE::ADD_GROWING_DAY)
	{
		CropRenderer_->SetIndex(static_cast<size_t>(CROPS::PARSNIP_GROW4));
		isHarvest_ = true;

	}
}

void Parsnip_Crops::CropsDeath()
{
	int Count = RandomItemCount.RandomInt(1, 5);
	Items* DropItem;
	for (int i = 0; i < Count; ++i)
	{
		DropItem = CreateDropItemActor<Pasnip>();

		float4 Pos;
		Pos.x = RandomItemPosX.RandomFloat(-60.f, 60.f);
		Pos.y = RamdomItemPosY.RandomFloat(-60.f, 60.f);

		DropItem->SetPosition({ this->GetPosition().x + Pos.x, this->GetPosition().y + Pos.y});
		DropItem->SetMoveFlag(true);

	}

}
