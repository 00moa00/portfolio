#include <Windows.h>

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContents/StardewValley.h>


#include <cstdlib>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif
int __stdcall WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ char*    lpCmdLine,
    _In_ int       nCmdShow)
{
    // 1. �ƹ� �������� ������ ����
    //    ���� => ������
    //    �ڽ��� ������ ���� ����� �ڱⰡ ģ �ڵ带 �����ϱ� �Ȱų� �𸥴�
    //    ���� �װ� �� ���ؾ�
    //    �������� �տ����� ���鼭 ��Ե� �����Ϸ��� �߾��ϸ鼭
    //    �������� ���������� �� �����ϰ� �亯�� �ؾ��ϴµ�.
    //    �������� �� �ڵ带 §����̾�. �߿��� �κе��� �����ϴ°ǵ�.
    //    ����°� ������ ����°� �ƴմϴ�.
    //    �������鿡�� ���� �ڵ������� �޾�����
    //    ���� § �ڵ�ϱ� �� ������ �˰� �� �ڵ忡�� ���� ���� �ٽ����� �κе��� �˾�.
    //    �׷��� �װ� ������ �������� ���ڵ尡 �� �̷��� ����������
    //    ���� �ٽ����� �κ��̱� ������ �����е鿡�� ����ϴ�.
    //    �ű⿡ ���ؼ� �׳��̶�� �Ѵ�.
    //    
   
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  //  int *a= new int(0);

   // _CrtSetBreakAlloc(22389);
    GameEngine::Start<StardewValley>();

}