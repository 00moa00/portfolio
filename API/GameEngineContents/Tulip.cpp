#include "Tulip.h"
#include "Inventory.h"

Tulip* Tulip::MainTulip = nullptr;
Font* Tulip::Font_ = nullptr;

Tulip::Tulip() 
{
}

Tulip::~Tulip() 
{
}

void Tulip::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::TULIP));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}

	ItemName_ = "Tulip";

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::TULIP);

	ItemType_ = ITEMTYPE::FARMING;
	SellPrice_ = 35;
}

void Tulip::Update()
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
			Player::MainPlayer->GetInventroy()->NewItem<Tulip>();
		}

		break;
	default:
		break;
	}
}

void Tulip::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainTulip = this;
	Font_ = Font_;
}

void Tulip::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();

}

void Tulip::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Tulip::SubItemCount()
{
	if (ItemCount_ == 1)
	{
		Player::MainPlayer->SetResetPlayerHandItem();
		Inventory::MainInventory->FindAndErasePlayerItemList(this->GetItemNameConstRef());
		Death();
	}
	else
	{
		--ItemCount_;
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}
}

void Tulip::UpdateOff()
{
	this->Off();
	Font_->Off();
}
