#pragma once


enum class PLAYER_UPDATE
{
	//INVENTROY_MINI_INIT,
	LEVELINIT,
	INIT,
	HOE,
	WATER,
	AXE,
	PICKAXE,
	HANDITEM,
	WALK,
	HANDITEMWALK,
	/*INVENTROY_POPUP_INIT,
	INVENTROY_POPUP,*/
	MAX
};

enum class PLAYER_SHOPPING
{
	INT,
	SHOPPING,
	SHOP_ON,
	SHOP_OFF
};


enum class USE_TOOL
{
	INIT,
	COLL,
	
};


enum class MINUTE_STATE
{
	COUNT,
	ADD,
	WAIT,
};