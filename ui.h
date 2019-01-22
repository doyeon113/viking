#pragma once
#include "gameNode.h"

class ui : public gameNode
{
private:
	int _ericCurrentX, _ericCurrentY;				//에릭 프로필 프레임 X,Y
	int _baleogCurrentX, _baleogCurrentY;			//벨로그 프로필 프레임 X, Y
	int _olafCurrentX, _olafCurrentY;				//올라프 프로필 프레임 X, Y
							
	int _choice;
	int _ericLife, _baleogLife, _olafLife;			//바이킹 Life
	int _ericBox_X, _ericBox_Y;						//에릭 박스 커서 X,Y값
	int	_baleogBox_X, _baleogBox_Y;					//벨로그 박스 커서 X,Y값
	int	_olafBox_X, _olafBox_Y;						//올라프 박스 커서 X,Y값

	int _ericItemFrameX[4], _ericItemFrameY[4];
	int _baleogItemFrameX[4], _baleogItemFrameY[4];
	int _olafItemFrameX[4], _olafItemFrameY[4];
	int _deleteItemFrameX;
	int _saveFrameX, _itemMove;

	bool _ericCursor, _baleogCursor, _olafCursor;	//커서 깜빡임
	bool _fKeyMod;

	int _ericItemNumber, _baleogItemNumber, _olafItemNumber;

	int _oldTime;									//커서 깜빡일때 시간

public:
	ui();
	~ui();

	HRESULT init();
	void release();
	void update(int choice, bool uiChange);
	void render();
	void profileUpdate(int choice);					//프로필 이미지 변경할 때
	void keyControl(int choice);
	void uiItemSave(int itemFrameX);
	void uiItemRender();
	void vikingItemNumber(int choice);


	int getEricLife() { return _ericLife; }				// 35씩 뺄때마다 life 하나씩 줄어듬~
	int getBaleogLife() { return _baleogLife; }
	int getOlafLife() { return _olafLife; }

	int getEricItemNumber() { return _ericItemNumber;  }
	int getBaleogItemNumber() { return _baleogItemNumber; }
	int getOlafItemNumber() { return _olafItemNumber; }
};

