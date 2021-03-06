#include "DialogueBox.h"
#include "RendererData.h"

DialogueBox::DialogueBox() 

	:
		DialogueBoxRenderer_(nullptr),
		PortraitRenderer_(nullptr),
		DialogueRandom_()

{

	PierreDialogue[0] = "*sigh* ... I`ve got those /behind-the-counter- blues...";
	PierreDialogue[1] = "Is it just me or is there /a cold draft in here?";
	PierreDialogue[2] = "If I didn't have this shop /to run I would be outside /right now. /It would be fun to throw a /snowball.";
	PierreDialogue[3] = "Sometimes I get new items /in stock, so make sure to stop /by every so often. It`s a /lot of work to run a shop.";


	LewiseDialogue[0] = "If you plant a certain kind /of flower near your beehouse, /it will produce a different /honey type.";
	LewiseDialogue[1] = "I hope the river doesn`t /overflow...";
	LewiseDialogue[2] = "Gardening is a hobby of mine, /so I'm excited for this warm /weather.";
	LewiseDialogue[3] = "Hi! How're you doing today? /If you see Marnie, tell /her I said 'hi'";


	PennyDialogue[0] = "The raindrops on the roof of /our trailer are really /loud... But it`s soothing!";
	PennyDialogue[1] = "I want her to be happy, /but I can`t stay here /forever... you know?";
	PennyDialogue[2] = "Hi. Ummm... The weather`s /interesting today, don't you /think? Sorry...";
	PennyDialogue[3] = "This town's safe, but I /always walk the children /home anyway.";

	GusDialogue[0] = "Yeah, I know a lot about /the people living here.";
	GusDialogue[1] = "That's one of the benefits /of being a bartender.";
	GusDialogue[2] = "Sometimes I hear too much...";
	GusDialogue[3] = "Business has been pretty /steady thanks to my regular /customers.";

	AbigailDialogue[0] = "Oh, hey. Taking a break /from work?";
	AbigailDialogue[1] = "Oh, hi! Do you ever hang /out at the cemetery? /It's a peaceful place to /spend some time alone";
	AbigailDialogue[2] = "I'm not in a good mood /right now. I said I'm not /in a good mood... /what do you want?";
	AbigailDialogue[3] = "...*sigh*... I know my /parents mean well, /but sometimes they just /cannot understand my point /of view. Weren't they ever /young?";

}

DialogueBox::~DialogueBox() 
{
}

void DialogueBox::Start()
{
	SetPosition({ GameEngineWindow::GetScale().Half().x, 520.f });

	DialogueBoxRenderer_ = CreateRenderer("DialogueBox.bmp");
	DialogueBoxRenderer_->CameraEffectOff();

	PortraitRenderer_ = CreateRenderer("Pierre_Portrait.bmp");
	PortraitRenderer_->SetIndex(0);
	PortraitRenderer_->SetPivot({756.f - 478.5f, -26.f});
	PortraitRenderer_->CameraEffectOff();


	DialogueName_ = CreateRenderer("Name_Sheet.bmp");
	DialogueName_->SetIndex(0);
	DialogueName_->SetPivot({ 755.f - 478.5f, 110.f });
	DialogueName_->CameraEffectOff();

	Dialoue_ = GetLevel()->CreateActor<Font>(static_cast<int>(PLAYLEVEL::DIALOGUEFONT));
	Dialoue_->ChangeFont(" ",{0,0});


}

void DialogueBox::Update()
{
}

void DialogueBox::Render()
{
}

void DialogueBox::SetDialogue(std::string _Text)
{
}

void DialogueBox::SetPierre()
{
	PortraitRenderer_->SetImage("Pierre_Portrait.bmp");
	PortraitRenderer_->SetIndex(0);
	Dialoue_->ChangeFont(PierreDialogue[DialogueRandom_.RandomInt(0, 3)], {this->GetPosition().x -430.f, this->GetPosition().y - 110.f});
	DialogueName_->SetIndex(static_cast<int>(NPC::PIERRE));
}

void DialogueBox::SetLewis()
{
	PortraitRenderer_->SetImage("Lewis_Portrait.bmp");
	PortraitRenderer_->SetIndex(0);

	Dialoue_->ChangeFont(LewiseDialogue[DialogueRandom_.RandomInt(0, 3)], { this->GetPosition().x - 430.f, this->GetPosition().y - 110.f });
	DialogueName_->SetIndex(static_cast<int>(NPC::LEWIS));
}

void DialogueBox::SetPenny()
{
	PortraitRenderer_->SetImage("Penny__Portrait.bmp");
	PortraitRenderer_->SetIndex(0);

	Dialoue_->ChangeFont(PennyDialogue[DialogueRandom_.RandomInt(0, 3)], { this->GetPosition().x - 430.f, this->GetPosition().y - 110.f });
	DialogueName_->SetIndex(static_cast<int>(NPC::PENNY));
}

void DialogueBox::SetAbigail()
{
	PortraitRenderer_->SetImage("Abigail_Portrait.bmp");
	PortraitRenderer_->SetIndex(0);

	Dialoue_->ChangeFont(AbigailDialogue[DialogueRandom_.RandomInt(0, 3)], { this->GetPosition().x - 430.f, this->GetPosition().y - 110.f });
	DialogueName_->SetIndex(static_cast<int>(NPC::PENNY));
}

void DialogueBox::SetGus()
{
	PortraitRenderer_->SetImage("Gus_Portrait.bmp");
	PortraitRenderer_->SetIndex(0);
	Dialoue_->ChangeFont(GusDialogue[DialogueRandom_.RandomInt(0, 3)], { this->GetPosition().x - 430.f, this->GetPosition().y - 110.f });
	DialogueName_->SetIndex(static_cast<int>(NPC::PIERRE));
}

void DialogueBox::DialogueOn()
{
	DialogueBoxRenderer_->On();
	PortraitRenderer_->On();
	DialogueName_->On();
	Dialoue_->On();
}

void DialogueBox::DialogueOff()
{
	DialogueBoxRenderer_->Off();
	PortraitRenderer_->Off();
	DialogueName_->Off();
	Dialoue_->Off();
}

