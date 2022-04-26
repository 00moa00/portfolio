#pragma once
#include "Items.h"
#include"ShippingBoxTop.h"

enum class SHIPPINGBOX_UPDATE
{
	INIT,
	UPDATE,
};

// ���� :
class ShippingBox : public Items
{
public:
	static ShippingBox* MainShippingBox;

	// constrcuter destructer
	ShippingBox();
	~ShippingBox();

	// delete Function
	ShippingBox(const ShippingBox& _Other) = delete;
	ShippingBox(ShippingBox&& _Other) noexcept = delete;
	ShippingBox& operator=(const ShippingBox& _Other) = delete;
	ShippingBox& operator=(ShippingBox&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

public:

	void ItemCollPlayer() override;
	void ItemCollFalsePlayer() override;
private:

	//������ �ִϸ��̼��� ���� ���ϸ��̼� �Ŀ��� ����� �� �ֵ���
	bool isOpenAnimation;

	SHIPPINGBOX_UPDATE ShippingUpdateState_;

	ShippingBoxTop* ShippingBoxTop_;

};

