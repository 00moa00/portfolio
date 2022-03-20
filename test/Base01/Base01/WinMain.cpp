#include "WinMain.h"
#include "Scene.h"
#include "Scenetitle.h"

//�� ���� Ŭ���� ����
SceneTitle sceneTitle;

//Ŭ���� ����ü
Scene* scene_tbl[] = {
	&sceneTitle,
};

Scene* pScene;
Scene* pNext;

//���� �Լ�

int main() {
	
	setScene(SCENE_TITLE);

	//���� ����
	while (true) {

		//�� ���� ó��
		pScene = pNext;
		pNext = nullptr;
		pScene->init();
	}

	pScene->update();
	pScene->render();
}

void setScene(int _scene) {

	pNext = scene_tbl[_scene];

}