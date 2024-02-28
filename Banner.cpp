#include "Banner.h"
#include<assert.h>
Banner::Banner(GameObject* scene):GameObject(scene)
{
	hImage = LoadGraph("Assets/font.png");
	assert(hImage > 0);
}

Banner::~Banner()
{
	if (hImage > 0)
		DeleteGraph(hImage);
}

void Banner::Update()
{
}

void Banner::Draw()
{
	if (view == ViewID::V_Start) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawRectGraph(200, 400, 0, 0, 256, 64, hImage, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	else if (view == ViewID::V_Clear) {
		DrawRectGraph(200, 400, 0, 64, 256, 64, hImage, TRUE);
	}
	else if (view == ViewID::V_GameOver) {
		DrawRectGraph(200, 400, 0, 128, 256, 128, hImage, TRUE);
	}

}

void Banner::View(ViewID id)
{
	view = id;
	if (id == ViewID::V_GameOver) {

	}
}
