#include "Cauliflower.h"
#include "Inventory.h"

Cauliflower* Cauliflower::MainCauliflower = nullptr;
Font* Cauliflower::Font_ = nullptr;


Cauliflower::Cauliflower() 
{
}

Cauliflower::~Cauliflower() 
{
}

void Cauliflower::Start()
{
	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::CAULIFLOWER));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
		Font_->ChangeWhiteColor();
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}

	ItemName_ = "Cauliflower";

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::CAULIFLOWER);

	SellPrice_ = 35;
}

void Cauliflower::Update()
{
	MoveToPlayer();

	if (isMapItemDeath_ == true)
	{
		Player* MainPlayer = GetLevel()->FindActor<Player>("MainPlayer");
		MainPlayer->GetInventroy()->NewItem<Cauliflower>();
	}

	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		break;
	}
}

void Cauliflower::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainCauliflower = this;
	Font_ = Font_;
}

void Cauliflower::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
}

void Cauliflower::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Cauliflower::SubItemCount()
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

void Cauliflower::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Cauliflower::UpdateOn()
{
	this->On();
	Font_->On();
}
