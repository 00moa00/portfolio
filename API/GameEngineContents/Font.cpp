#include "Font.h"
#include <sstream>

//Font* Font::MainFont = nullptr;

Font::Font() 
	:
	Num_(0)
{
}

Font::~Font() 
{
}

void Font::Start()
{
	FontRenderer.reserve(10);

	for (int i = 0; i < 11; ++i)
	{
		FontRenderer.push_back(CreateRenderer("font_colored.bmp"));
		std::vector<GameEngineRenderer*>::iterator This = --FontRenderer.end();
		(*This)->SetIndex(10);
		(*This)->CameraEffectOff();
	}


}

void Font::Update()
{


}

void Font::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//MainFont = nullptr;
}

void Font::ChangeNumUI(int _Num)
{
	int Count_ = 0 ;
	Num_ = _Num;

	//0 �̶��
	if (Num_ == 0)
	{
		std::vector<GameEngineRenderer*>::iterator Iter = FontRenderer.begin();
		for (; Iter != FontRenderer.end(); ++Iter) {

			(*Iter)->SetIndex(10);

		}
		return;

	}


	std::stringstream IntToString;
	IntToString << Num_;
	StrNum_ = IntToString.str();

	for (Count_ = 0; Count_ < StrNum_.size(); ++Count_)
	{
		//������ �տ������� ����
		char String = StrNum_.at(Count_);

		//int�� ��ȯ
		int Index = String - '0';

		//�ε����� �ٲ�
		FontRenderer.at(Count_)->SetIndex(Index);
	}


	//�� ���� ���ڴ� �������� ��
	for (; Count_ < 11; ++Count_)
	{
		FontRenderer.at(Count_)->SetIndex(10);
	}
}

void Font::ChangeNumItem(int _Num)
{
	int Count_ = 0;

	Num_ = _Num;
	//1���� ǥ�� ����
	if (Num_ == 1)
	{
		std::vector<GameEngineRenderer*>::iterator Iter = FontRenderer.begin();
		for (; Iter != FontRenderer.end(); ++Iter) {

			(*Iter)->SetIndex(10);

		}

		return;
	}


	std::stringstream IntToString;
	IntToString << Num_;
	StrNum_ = IntToString.str();

	for (Count_ = 0; Count_ < StrNum_.size(); ++Count_)
	{
		//������ �տ������� ����
		char String = StrNum_.at(Count_);

		//int�� ��ȯ
		int Index = String - '0';

		//�ε����� �ٲ�
		FontRenderer.at(Count_)->SetIndex(Index);
	}


	//�� ���� ���ڴ� �������� ��
	for (; Count_ < 11; ++Count_)
	{
		FontRenderer.at(Count_)->SetIndex(10);
	}

}

void Font::SetPositionUI(float4 _Pos)
{
	std::vector<GameEngineRenderer*>::iterator Iter = FontRenderer.begin();
	for (int i = 0; Iter != FontRenderer.end(); ++Iter)
	{

		(*Iter)->SetPivot({ _Pos.x + (18 * i), _Pos.y });
		++i;

	}
}

void Font::SetPositionItem(float4 _Pos)
{

	std::vector<GameEngineRenderer*>::iterator ItemPosIter = FontRenderer.begin();
	for (int i = 0; ItemPosIter != FontRenderer.end(); ++ItemPosIter) 
	{

		(*ItemPosIter)->SetPivot({ _Pos.x + (20.f) + (8.f * i), _Pos.y+(22.f)});
		++i;

	}

}

void Font::ChangeWhiteColor()
{

	std::vector<GameEngineRenderer*>::iterator Iter = FontRenderer.begin();
	for (; Iter != FontRenderer.end(); ++Iter) {

		(*Iter)->SetImage("font_colored_White.bmp");

	}
}

