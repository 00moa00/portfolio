#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

#include <vector>


// ���� :
class Font : public GameEngineActor
{
	//static Font* MainFont;

public:
	// constrcuter destructer
	Font();
	~Font();

	// delete Function
	Font(const Font& _Other) = delete;
	Font(Font&& _Other) noexcept = delete;
	Font& operator=(const Font& _Other) = delete;
	Font& operator=(Font&& _Other) noexcept = delete;


private:

	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:

	std::vector<GameEngineRenderer*> NumberRenderer;
	std::vector<GameEngineRenderer*> FontRenderer;

	int Num_;
	std::string StrNum_;

public:
	//�ִ� 300��, �������� �ʱ�ȭ
	void InitFont();

	// ��Ʈ������ ������
	void ChangeNumStr(std::string _Num);

	//�⺻ ������, ���� ����
	void ChangeNumRightSort(int _Num);
	void ChangeNumLeftSort(int _Num, float4 _Pos);

	//������, �������϶� ���� ������ �ٸ���
	void ChangeNumItemLeftSort(int _Num, float4 _Pos);
	void ChangeNumMoneyLeftSort(int _Num, float4 _Pos);

	void ChangeWhiteColor();

	//����
	void ChangeFont(std::string _Font, float4 _Pos); //��ü��
	void CreateFontInit(std::string _Font, float4 _Pos); //������

	//================================
	//    Setter
	//================================

	void SetPositionRightSort(float4 _Pos);
	void SetPositionItem(float4 _Pos);
};

enum class FONT
{
	Question,
	DecimalPoint=2,
	_ = 3,
	Astrerrisk = 6,
	Square_Bracket_Right,
	Square_Bracket_Left,
	Small_Question_Mark,
	Big_Question_Mark = 14,
	Exclamaion_Mark,
	z,
	y,
	x,
	w,
	v,
	u,
	t,
	s,
	r,
	q,
	p,
	o,
	n,
	m,
	l,
	k,
	j,
	i,
	h,
	g,
	f,
	e,
	d,
	c,
	b,
	a,
	Z,
	Y,
	X,
	W,
	V,
	U,
	T,
	S,
	R,
	Q,
	P,
	O,
	N,
	M,
	L,
	K,
	J,
	I,
	H,
	G,
	F,
	E,
	D,
	C,
	B,
	A,
	EMPTY,

};



enum class FONT_VER2
{
	EMPTY,
	Exclamaion_Mark, //����ǥ
	Big_Question_Mark,  // "
	Small_Question_Mark = 7, //'
	Square_Bracket_Left = 8,
	Square_Bracket_Right,
	Astrerrisk , //*
	Period =12, // ,
	_ , // -
	DecimalPoint ,
	Zero = 16,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,

	Question=31, // 
	A =33,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I, 
	J,
	K,
	L,
	M,
	N,
	O, 
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	a = 65,
	b, 
	c,
	d,
	e,
	f,
	g,
	h,
	i,
	j,
	k,
	l,
	m,
	n,
	o,
	p,
	q,
	r,
	s,
	t,
	u,
	v,
	w,
	x,
	y,
	z,


};
