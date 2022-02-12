#pragma once

struct COLOR
{
	int r, g, b;
	COLOR() : COLOR(0,0,0) {}
	COLOR(int _r, int _g, int _b) : r(_r), g(_g), b(_b) {}

};

class OBJ2D {

public:
	//TODO : �����Լ��� �ٲٱ�
	float posX;
	float posY;
	float scaleX;
	float sclaeY;

	//TODO : ������ ����, ���ǵ�, ��� �߰��ϱ�

public:
	OBJ2D();

	void init();
	void clear();
	void update();
	void render();
};

class OBJ2DManager
{
public:
	virtual OBJ2D* begin() = 0;
	virtual OBJ2D* end() = 0;

	virtual void init();
	virtual void update();
	virtual void render();
};