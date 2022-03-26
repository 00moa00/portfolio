#pragma once

class Scene
{
public:
	virtual void init() {}
	virtual void update() = 0;
	virtual void render() = 0;
};