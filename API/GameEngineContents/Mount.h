#pragma once

// ���� :
class Mount
{
public:
	// constrcuter destructer
	Mount();
	~Mount();

	// delete Function
	Mount(const Mount& _Other) = delete;
	Mount(Mount&& _Other) noexcept = delete;
	Mount& operator=(const Mount& _Other) = delete;
	Mount& operator=(Mount&& _Other) noexcept = delete;

protected:

private:

};

