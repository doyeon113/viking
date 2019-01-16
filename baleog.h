#pragma once
#include "gameNode.h"

struct baleogPlayer
{
	float x, y;
	image* baleogImage;
	RECT baleogRc;
	float speed;
};


enum BALEOGSTATE //���α� ����
{
	BALEOG_RIGHT_STOP, //������ �⺻����
	BALEOG_LEFT_STOP, //���� �⺻����
	BALEOG_RIGHT_MOVE, //������ ������
	BALEOG_LEFT_MOVE, //���� ������
	BALEOG_RIGHT_SWORD_ATTACK_ONE, //������ ù��° ���� �˰���
	BALEOG_LEFT_SWORD_ATTACK_ONE, //���� ù��° ���� �˰���
	BALEOG_RIGHT_SWORD_ATTACK_TWO, //������ �ι�° ���� �˰���
	BALEOG_LEFT_SWORD_ATTACK_TWO, //���� �ι�° ���� �˰���
	BALEOG_RIGHT_ARROW_ATTACK, //������ ȭ�����
	BALEOG_LEFT_ARROW_ATTACK, //���� ȭ�����
};

enum BALEOGINFO // ���α� ������
{
	BALEOG_X = WINSIZEX / 2,
	BALEOG_Y = WINSIZEY / 2,
	BALEOG_SPEED = 0,
};

class baleog : public gameNode
{
private:
	BALEOGSTATE _baleogState;
	baleogPlayer _baleogPlayer;

	string _name;
	animation* _baleogMotion; //���α� ��� ����� �� �ִϸ��̼�
public:

	baleog();
	~baleog();

	HRESULT init();
	HRESULT init(string name);
	void release();
	void update();
	void render();

	//�ݹ��Լ� �ҷ��� �Լ�
	static void rightFire(void* obj);
	static void leftFire(void* obj);

	//���α� ���� ������ ������
	BALEOGSTATE getBaleogState() { return _baleogState; }
	void setBaleogState(BALEOGSTATE state) { _baleogState = state; }

	string getName() {return _name;}
	//���α� �ִϸ��̼� ������ ������
	animation* getBaleogMotion() {return _baleogMotion;}
	void setBaleogMotion(animation* motion) {_baleogMotion = motion;}
};
