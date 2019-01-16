#pragma once
#include "gameNode.h"

enum OLAFDIRECTION
{
	OLAF_DIRECTION_RIGHT_STOP,
	OLAF_DIRECTION_LEFT_STOP,
	OLAF_DIRECTION_RIGHT_SHIELD,
	OLAF_DIRECTION_LEFT_SHIELD,
	OLAF_DIRECTION_RIGHT_MOVE,
	OLAF_DIRECTION_LEFT_MOVE,
	OLAF_DIRECTION_RIGHT_SHIELD_UP_MOVE,
	OLAF_DIRECTION_LEFT_SHIELD_UP_MOVE,
	OLAF_DIRECTION_RIGHT_JUMP,
	OLAF_DIRECTION_LEFT_JUMP
};



class olaf : public gameNode
{
private:

	OLAFDIRECTION _olafDirection;

	image* _olafimg;
	float _olaf_x, _olaf_y;
	RECT _olaf_rc;

	string _olafName;
	bool _changeMode;
	int num;
	animation* _olafMotion;

public:

	olaf();
	~olaf();

	HRESULT init();
	HRESULT init(string name);
	void release();
	void update();
	void render();

	OLAFDIRECTION getOlafDirection() { return _olafDirection; }
	void setOlafDirection(OLAFDIRECTION direction) { _olafDirection = direction; }

	animation* getOlafMotion() { return _olafMotion; }
	void setOlafMotion(animation* ani) { _olafMotion = ani; }

	inline int getolafX() { return _olaf_x; }
	void setolafX(int olafx) { _olaf_x = olafx; }

	inline int getolafY() { return _olaf_y; }
	void setolafY(int olafy) { _olaf_y = olafy; }


	void olafMovement();
};

