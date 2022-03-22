#pragma once
#include <string>
#include <algorithm>

//std::transform
// first1���� last1 ������ ������ ���ҵ��� unary_op�� �����ϰ�, �� ����� d_first���� ���ʷ� �����Ѵ�
//		 first1, last1 : transform �Լ��� ������ ù ��° ���ҵ��� ����Ű�� ����
//		 first2: transform �Լ��� ������ �� ��° ���ҵ��� ������
//		 d_first : ����� ������ ����. (first1, first2�� �����ص� ��.�� ���, ���� �����͸� ����� ��)
//		 binary_op : ���ҵ��� ��ȯ�� �Լ�. 2 ���� parameter�� ����.
// 

class GameEngineString
{
public:
	static void ToUpper(std::string& _Text) 
	{
		std::transform(_Text.begin(), _Text.end(), _Text.begin(), std::toupper);
	}

	static std::string ToUpperReturn(const std::string& _Text)
	{
		std::string NewText = _Text;
		std::transform(NewText.begin(), NewText.end(), NewText.begin(), std::toupper);
		return NewText;
	}

protected:

private:
	// constrcuter destructer
	GameEngineString();
	~GameEngineString();

	// delete Function
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;


};

