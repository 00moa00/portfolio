#pragma once
#include <filesystem>

// TODO : filesystem
//Fstram : ������ �����͸� �о���� �� �ܿ� ���Ͽ� ���� ���� (���� �̸�, ��ġ ��)�� ����
//�����͸� ������ �� ����.

//fileSysytem : ���Ͽ� ���� ������ ���� ������ �����ֳ�, ���� ��ü�� �д� ���� �������� �ʴ´�.

// �ϵ� ��ũ ��򰡿� �ִ� ������ ã��ʹٸ� filesystem , �а�ʹٸ� fstream ���


class GameEnginePath
{
public:
	// constrcuter destructer
	GameEnginePath();
	GameEnginePath(const std::filesystem::path& _Path);
	~GameEnginePath();

	// delete Function
	GameEnginePath(const GameEnginePath& _Other) = delete;
	GameEnginePath(GameEnginePath&& _Other) noexcept = delete;
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	void SetCurrentPath();

	bool IsExits();

	std::string GetExtension();

	std::string GetFileName();

	std::string GetFullPath();

protected:
	std::filesystem::path Path_;

private:
};

