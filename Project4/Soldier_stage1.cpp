#include "Soldier_stage1.h"



Soldier_stage1::Soldier_stage1()
{
}

Soldier_stage1::Soldier_stage1(string Path, int x, int y, int Width, int Height, int frameNumber, int animDelay, string fileName,
	float rangeXstart, float rangeXend)
	:Enemy(Path, x, y, Width, Height, frameNumber, animDelay, fileName)
{
	_type = SOLDIER_stage1;
	_rangeXstart = rangeXstart;
	_rangeXend = rangeXend;
	_vy = 0;
	_vx = -SOLDIER_STAGE1_SPEED;
	sprite.FlipX = -1;
	_score = 100;
}


void Soldier_stage1::UpdateVelocity()
{
	if (sprite._X > _rangeXend || sprite._X < _rangeXstart)
	{
		_vx *= -1;
		sprite.FlipX *= -1;
	}
}

void Soldier_stage1::UpdatePosition()
{
	sprite._X += _vx;
	
}

void Soldier_stage1::UpdateFrame()
{
	switch ((int)(_countDelay/(sprite._animDelay*1.75)))
	{
	case 0:
	case 2:
		_curSprite = 0;
		break;
	case 1:
		_curSprite = 1;
		break;
	case 3:
		_curSprite = 2;
		break;
	default:
		break;
	}
	_countDelay++;
	if ((int)(_countDelay / (sprite._animDelay*1.75)) >= 4)
		_countDelay = 0;
}

LPEnemy Soldier_stage1::Update(Ryu* ryu)
{
	if (ryu->GetStateType() != ATTACK_state)
		_isAttacked = false;
	if (_HP == 0)
	{
		_HP--;
		_died = 20;
	}
	if (_died != -1)
	{
		Enemy::DiedUpdate();
		return NULL;
	}
	UpdateVelocity();
	UpdatePosition();
	UpdateFrame();
	return NULL;
}

Box Soldier_stage1::ToBox()
{
	return Enemy::ToBox();
}

void Soldier_stage1::Render(Camera camera)
{
	if (_died == -1)
	{
		Enemy::Render(camera);
		return;
	}
	else Enemy::DiedRender(camera);
}

Soldier_stage1::~Soldier_stage1()
{
}