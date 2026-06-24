#include "DxLib.h"
#include "SFINAE.h"
#include "CONCEPTS.h"
#include <memory>

namespace {
    constexpr auto WINDOW_TITLE = _T("C++20 Concepts");
    constexpr auto SCREEN_WIDTH = 1280;
    constexpr auto SCREEN_HEIGHT = 720;
    constexpr auto SCREEN_DEPTH = 32;
}

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    auto window_mode = FALSE;

#ifdef _DEBUG
    window_mode = TRUE;
#endif

    SetMainWindowText(WINDOW_TITLE);

    ChangeWindowMode(window_mode);

    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH);

    if (DxLib_Init() == -1) {
        return -1;
    }

    // コピーの実装の方が呼ばれるを期待
    int a = 10;
    SFINAE::DummyCopy(a);
    CONCEPTS::DummyCopy(a);

    // ムーブの実装の方が呼ばれるを期待
    SFINAE::DummyCopy(std::make_unique<int>(10));
    CONCEPTS::DummyCopy(std::make_unique<int>(10));

    // concept を使った Template
    int b = 20;
    CONCEPTS::Add2(a, b);
    CONCEPTS::Add2Concept(a, b);

    while (ProcessMessage() != -1) {
        if (1 == CheckHitKey(KEY_INPUT_ESCAPE)) {
            break;
        }

        ClearDrawScreen();
        ScreenFlip();
    }

    DxLib_End();

    return 0;
}
