#include "stdafx.h"
#include "eric.h"


eric::eric()
{
}


eric::~eric()
{
}

HRESULT eric::init()
{
	_ericImage = IMAGEMANAGER->addFrameImage("eric", "image/eric.bmp", 0, 0, 1761, 2240, 11, 14, true, RGB(255, 0, 255));

	_eric_X = WINSIZEX / 2;
	_eric_Y = WINSIZEY / 2;

	_ericState = ERIC_RIGHT_STOP;

	_eric_rc = RectMakeCenter(_eric_X, _eric_Y, _ericImage->getFrameWidth(), _ericImage->getFrameHeight());

	int rightStop[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "rightStop", "eric", rightStop, 2, 4, true);

	int leftStop[] ={2,3};
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "leftStop", "eric", leftStop, 2, 4, true);

	int rightMove[] = { 11,12,13,14,15,16,17,18 };
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "rightMove", "eric", rightMove, 8, 10, true);

	int leftMove[] = { 29,28,27,26,25,24,23,22 };
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "leftMove", "eric", leftMove, 8, 10, true);

	int rightDashArr[] = { 33, 34, 35, 36, 37, 38, 39, 40, 39, 38, 39, 40};
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "rightDash", "eric", rightDashArr, 12, 10, false, rightDash, this);

	int leftDashArr[] = { 51, 50, 49, 48, 47, 46, 45, 44, 45, 46, 45, 44 };
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "leftDash", "eric", leftDashArr, 12, 10, false, leftDash, this);

	int rightJumpArr[] = {77, 78, 79, 80};
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "rightJump", "eric", rightJumpArr, 4, 5, false, rightJump, this);

	int leftJumpArr[] = {84, 83, 82, 81};
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "leftJump", "eric", leftJumpArr, 4, 5, false, leftJump, this);

	int upMove[] = {88, 89, 90, 91};
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "upMove", "eric", upMove, 4, 8, true);

	int downMove[] = {91, 90, 89, 88};
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "downMove", "eric", downMove, 4, 8, true);

	_ericMotion = KEYANIMANAGER->findAnimation("ericName", "rightStop");

	_speed = 0;
	_acceleration = 0;
	_isLadderCollision = false;
	_isJump = false;

	_motionTime = 1.0f;
	_motionWorldTime = TIMEMANAGER->getWorldTime();
	return S_OK;
}

void eric::release()
{

}

void eric::update(float viewX, float viewY, float* x, float* y)
{
	_eric_X = viewX;
	_eric_Y = viewY;

	keySetting();
	dashKeySetting();
	//jumpKeySetting();
	//if (_isJump == false)
	//{
	//	if (_ericState != ERIC_RIGHT_MOVE && (_ericState == ERIC_RIGHT_STOP || _ericState == ERIC_RIGHT_JUMP))
	//	{
	//		if (_motionTime + _motionWorldTime <= TIMEMANAGER->getWorldTime())
	//		{
	//			_ericMotion = KEYANIMANAGER->findAnimation("ericName", "rightStop");
	//			_motionWorldTime = TIMEMANAGER->getWorldTime();
	//		}
	//	}
	//	if (_ericState != ERIC_LEFT_MOVE && (_ericState == ERIC_LEFT_STOP || _ericState == ERIC_LEFT_JUMP))
	//	{
	//		if (_motionTime + _motionWorldTime <= TIMEMANAGER->getWorldTime())
	//		{
	//			_ericMotion = KEYANIMANAGER->findAnimation("ericName", "leftStop");
	//			_motionWorldTime = TIMEMANAGER->getWorldTime();
	//		}
	//	}
	//}

	//가속도 주기위함
	if (_ericState == ERIC_RIGHT_MOVE)
	{
		if (_speed < 5)
		{
			_acceleration = 0.05f;
			*x += _speed;
			_speed += _acceleration;
		}
		else if (_speed >= 5)
		{
			_speed = 7;
		}
	}
	//가속도 주기위함
	else if (_ericState == ERIC_LEFT_MOVE)
	{
		if (_speed < 5)
		{
			_acceleration = 0.05f;
			*x -= _speed;
			_speed += _acceleration;
		}
		else if (_speed >= 5)
		{
			_speed = 7;
		}
	}

	switch (_ericState)
	{
	case ERIC_UP_MOVE:
		*y -= 7;
		break;
	case ERIC_DOWN_MOVE:
		*y += 7;
	}

	//대쉬나 점프할때 오른쪽이나 왼쪽 꾹눌러도 무브상태로 하기위함.
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && (_ericState == ERIC_RIGHT_STOP || _ericState == ERIC_LEFT_STOP))
	{
		_ericState = ERIC_RIGHT_MOVE;
		_ericMotion = KEYANIMANAGER->findAnimation("ericName", "rightMove");
		_ericMotion->start();
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT) && (_ericState == ERIC_LEFT_STOP || _ericState == ERIC_RIGHT_STOP))
	{
		_ericState = ERIC_LEFT_MOVE;
		_ericMotion = KEYANIMANAGER->findAnimation("ericName", "leftMove");
		_ericMotion->start();
	}

	KEYANIMANAGER->update();
}

void eric::render(float viewX, float viewY)
{
	char str[128];
	sprintf_s(str, "_motionTime : %f ", _motionTime);
	TextOut(getMemDC(), 200, 100, str, strlen(str));

	sprintf_s(str, "_motionWorldTime : %f ", _motionWorldTime);
	TextOut(getMemDC(), 200, 120, str, strlen(str));


	//sprintf_s(str, "에릭 상태 : %d ", _ericState);
	//TextOut(getMemDC(), 200, 590, str, strlen(str));

	//sprintf_s(str, "에릭 가속도 : %f ", _acceleration);
	//TextOut(getMemDC(), 200, 610, str, strlen(str));

	//sprintf_s(str, "에릭 속도 : %f ", _speed);
	//TextOut(getMemDC(), 200, 630, str, strlen(str));

	_ericImage->aniRender(getMemDC(), viewX, viewY, _ericMotion);
}
void eric::keySetting()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _ericState != ERIC_RIGHT_DASH && _ericState != ERIC_LEFT_DASH)
	{
		_speed = 0;
		_ericState = ERIC_RIGHT_MOVE;
		_ericMotion = KEYANIMANAGER->findAnimation("ericName", "rightMove");
		_ericMotion->start();
		//점프상태에서 오른쪽키 눌러도 점프모션 나오기 위함.
		if (_isJump == true && _ericState == ERIC_RIGHT_MOVE)
		{
			_ericMotion = KEYANIMANAGER->findAnimation("ericName", "rightJump");
			_ericMotion->start();
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && _ericState != ERIC_LEFT_MOVE && _ericState != ERIC_LEFT_DASH && _ericState != ERIC_RIGHT_DASH && _ericState != ERIC_UP_MOVE && _ericState != ERIC_DOWN_MOVE && _ericState != ERIC_RIGHT_JUMP && _ericState != ERIC_LEFT_JUMP)
	{
		_speed = 0;
		_ericState = ERIC_RIGHT_STOP;
		_ericMotion = KEYANIMANAGER->findAnimation("ericName", "rightStop");
		_ericMotion->start();
		//점프상태에서 오른쪽키를 떼도 점프모션 나오기 위함.
		if (_isJump == true)
		{
			_ericMotion = KEYANIMANAGER->findAnimation("ericName", "rightJump");
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && _ericState != ERIC_LEFT_DASH && _ericState != ERIC_RIGHT_DASH)
	{
		_speed = 0;
		_ericState = ERIC_LEFT_MOVE;
		_ericMotion = KEYANIMANAGER->findAnimation("ericName", "leftMove");
		_ericMotion->start();

		//점프상태에서 왼쪽키 눌러도 점프모션 나오기 위함.
		if (_isJump == true && _ericState == ERIC_LEFT_MOVE)
		{
			_ericMotion = KEYANIMANAGER->findAnimation("ericName", "leftJump");
			_ericMotion->start();
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && _ericState != ERIC_RIGHT_MOVE && _ericState != ERIC_RIGHT_DASH && _ericState != ERIC_LEFT_DASH && _ericState != ERIC_UP_MOVE && _ericState != ERIC_DOWN_MOVE && _ericState != ERIC_RIGHT_JUMP && _ericState != ERIC_LEFT_JUMP)
	{
		_speed = 0;
		_ericState = ERIC_LEFT_STOP;
		_ericMotion = KEYANIMANAGER->findAnimation("ericName", "leftStop");
		_ericMotion->start();
		//점프상태에서 왼쪽키를 떼도 점프모션 나오기 위함.
		if (_isJump == true)
		{
			_ericMotion = KEYANIMANAGER->findAnimation("ericName", "leftJump");
		}
	}

	//사다리 충돌했을경우만 위아래 움직이게함.
	if (_isLadderCollision == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_ericState = ERIC_UP_MOVE;
			_ericMotion = KEYANIMANAGER->findAnimation("ericName", "upMove");
			_ericMotion->start();
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_UP) && _ericState != ERIC_RIGHT_MOVE && _ericState != ERIC_LEFT_MOVE)
		{
			_ericMotion->pause();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_ericState = ERIC_DOWN_MOVE;
			_ericMotion = KEYANIMANAGER->findAnimation("ericName", "downMove");
			_ericMotion->start();
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_DOWN) && _ericState != ERIC_RIGHT_MOVE && _ericState != ERIC_LEFT_MOVE)
		{
			_ericMotion->pause();
		}
	}
}
void eric::jumpKeySetting()
{
	if (!(_ericState == ERIC_RIGHT_DASH) && !(_ericState == ERIC_LEFT_DASH))
	{
		SOUNDMANAGER->play("eric_Jump");
		_isJump = true;
		_motionTime = 0.7f;

		if (_ericState == ERIC_RIGHT_STOP || _ericState == ERIC_RIGHT_MOVE)
		{
			_ericState = ERIC_RIGHT_JUMP;
			_ericMotion = KEYANIMANAGER->findAnimation("ericName", "rightJump");
			_ericMotion->start();
		}
		else if (_ericState == ERIC_LEFT_STOP || _ericState == ERIC_LEFT_MOVE)
		{
			_ericState = ERIC_LEFT_JUMP;
			_ericMotion = KEYANIMANAGER->findAnimation("ericName", "leftJump");
			_ericMotion->start();
		}
	}
}
void eric::dashKeySetting()
{
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (_speed >= 7)
		{
			if (_ericState == ERIC_RIGHT_STOP || _ericState == ERIC_RIGHT_MOVE)
			{
				_ericState = ERIC_RIGHT_DASH;
				_ericMotion = KEYANIMANAGER->findAnimation("ericName", "rightDash");
				_ericMotion->start();
			}

			else if (_ericState == ERIC_LEFT_STOP || _ericState == ERIC_LEFT_MOVE)
			{
				_ericState = ERIC_LEFT_DASH;
				_ericMotion = KEYANIMANAGER->findAnimation("ericName", "leftDash");
				_ericMotion->start();
			}
		}
	}

}
void eric::rightDash(void* obj)
{
	eric* e = (eric*)obj;
	e->setEricState(ERIC_RIGHT_STOP);
	e->setEricMotion(KEYANIMANAGER->findAnimation("ericName", "rightStop"));
	e->getEricMotion()->start();
}

void eric::leftDash(void* obj)
{
	eric* e = (eric*)obj;
	e->setEricState(ERIC_LEFT_STOP);
	e->setEricMotion(KEYANIMANAGER->findAnimation("ericName", "leftStop"));
	e->getEricMotion()->start();
}

void eric::rightJump(void* obj)
{
	eric* e = (eric*)obj;
	e->setEricState(ERIC_RIGHT_STOP);
	e->setEricMotion(KEYANIMANAGER->findAnimation("ericName", "rightStop"));
	e->getEricMotion()->start();
}

void eric::leftJump(void* obj)
{
	eric* e = (eric*)obj;
	e->setEricState(ERIC_LEFT_STOP);
	e->setEricMotion(KEYANIMANAGER->findAnimation("ericName", "leftStop"));
	e->getEricMotion()->start();
}
