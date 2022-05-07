#include "Kale.h"
#include "Inventory.h"

Kale* Kale::MainKale = nullptr;
Font* Kale::Font_ = nullptr;

Kale::Kale() 
{
}

Kale::~Kale() 
{
}

void Kale::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::KALE));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}

	ItemName_ = "Kale";
	ItemType_ = ITEMTYPE::FARMING;

	//�ڵ� �����ۿ�
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::KALE);

	SellPrice_ = 35;
}

void Kale::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		if (isMove_ == true)
		{

			PrePosition_ = this->GetPosition();
			ItemState_ = ITEM_STATE::ANIMATION;
		}

		break;
	case ITEM_STATE::ANIMATION:

		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 700.0f;
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());

		if (this->GetPosition().y > PrePosition_.y)
		{
			ItemState_ = ITEM_STATE::MOVETOPLAYER;

		}

		break;
	case ITEM_STATE::MOVETOPLAYER:

		MoveToPlayer();
		if (isMapItemDeath_ == true)
		{
			Player::MainPlayer->GetInventroy()->NewItem<Kale>();
		}

		break;
	default:
		break;
	}
}

void Kale::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainKale = this;
	Font_ = Font_;
}

void Kale::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();

}

void Kale::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Kale::SubItemCount()
{
	if (ItemCount_ == 1)
	{
		ItemCount_ = 0;
		Player::MainPlayer->SetResetPlayerHandItem();
		Inventory::MainInventory->FindAndErasePlayerItemList(this->GetItemNameConstRef());
		Font_ = nullptr;
		this->Death();
	}
	else
	{
		--ItemCount_;
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}
}

void Kale::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Kale::UpdateOn()
{
	this->On();
	Font_->On();
}
