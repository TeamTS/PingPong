#include "pch.h"
#include "framework.h"
#include "PingPong.h"
#include "NetworkManager.h"
#include "GameScene.h"
#include "LobbyScene.h"
#include "Button.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HDC gHDC = NULL;
HWND gHWND = NULL;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

std::shared_ptr<Scene> currentScene;
NetworkManager* gNetworkManager = nullptr;

std::shared_ptr<GameScene> gameScene;
std::shared_ptr<LobbyScene> lobbyScene;

std::shared_ptr<Button> button;

void Initialize(void)
{
    currentScene = lobbyScene;
    lobbyScene->button = button;
    currentScene->Initialize();
}

void Update(double deltaTime)
{
    gNetworkManager->Update();
    currentScene->Update(deltaTime);
}

void Render(void)
{
    currentScene->Render(gHWND, gHDC);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PINGPONG, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PINGPONG));

    MSG msg{};
    msg.message = WM_NULL;
    gHDC = GetDC(gHWND);

    gameScene = std::make_shared<GameScene>();
    lobbyScene = std::make_shared<LobbyScene>();
    button = std::make_shared<Button>();

    Initialize();
    // 기본 메시지 루프입니다:
    LARGE_INTEGER curFrame;
    LARGE_INTEGER lastFrame;
    LARGE_INTEGER cpuTick;

    QueryPerformanceCounter(&curFrame);
    QueryPerformanceCounter(&lastFrame);

    QueryPerformanceFrequency(&cpuTick); // 진동수? 였는듯

    Singleton::Register<NetworkManager>(); // 싱글톤 등록
    
    gNetworkManager = Singleton::Get<NetworkManager>();
    gNetworkManager->Initialize();

    // 시간 누적
    double accTime = 0.0;

    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        QueryPerformanceCounter(&curFrame);

        // (현재 시간 - 이전 시간) / cpuTick
        accTime += (curFrame.QuadPart - lastFrame.QuadPart) / static_cast<double>(cpuTick.QuadPart);
        lastFrame = curFrame;

        // 프레임 제한
        if (1.0 / 60.0 <= accTime)
        {
            Update(accTime);
            Render();

            accTime = 0;
        }
    }
    ReleaseDC(gHWND, gHDC);
    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PINGPONG));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT screenSize{ 0, 0, WINCX, WINCY };
   AdjustWindowRect(&screenSize, WS_THICKFRAME, NULL);

   gHWND = CreateWindowW(szWindowClass, szTitle, WS_THICKFRAME,
      CW_USEDEFAULT, 0, screenSize.right - screenSize.left, 
       screenSize.bottom - screenSize.top, nullptr, nullptr, hInstance, nullptr);

   if (!gHWND)
   {
      return FALSE;
   }

   ShowWindow(gHWND, nCmdShow);
   UpdateWindow(gHWND);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_LBUTTONDOWN:
        if (button->IsClicked(gHWND))
        {
            // 동작 시작
            std::string ipFinal(lobbyScene->ipInput.begin(), lobbyScene->ipInput.end());
            Singleton::Get<NetworkManager>()->Connect(SessionType::GameServer, ipFinal.c_str(), lobbyScene->portValue);
        }
        break;
    case WM_LBUTTONUP:
        break;
    case WM_CHAR:
        switch (lobbyScene->inputStage)
        {
        case LobbyInputStage::IP:
            lobbyScene->ipInput += wParam;
            break;
        case LobbyInputStage::PORT:
            if(iswdigit(wParam))
                lobbyScene->portInput += wParam;
            break;
        }
        break;
    case WM_KEYDOWN:
        if (wParam == VK_RETURN)
        {
            switch (lobbyScene->inputStage)
            {
            case LobbyInputStage::IP:
                lobbyScene->inputStage = LobbyInputStage::PORT;
                break;
            case LobbyInputStage::PORT:
                lobbyScene->inputStage = LobbyInputStage::END;
                break;
            }
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
