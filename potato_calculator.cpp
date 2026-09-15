#include <windows.h>
#include <commctrl.h>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdio>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")

// ---- Potato color palette ----
#define POTATO_BG      RGB(210, 180, 140)  // tan skin
#define POTATO_DARK    RGB(101, 67, 33)    // dirt brown
#define POTATO_SCREEN  RGB(245, 222, 179)  // wheat / potato flesh
#define POTATO_BTN     RGB(139, 98, 55)    // button brown
#define POTATO_OP      RGB(85, 60, 30)     // darker operator buttons
#define POTATO_ACCENT  RGB(60, 130, 60)    // sprout green

// ---- Global calculator state ----
static double accumulator = 0.0;
static char   pendingOp   = 0;
static bool   startNewEntry = true;
static char   buffer[64]  = "0";

static HWND   hDisplay;
static HBRUSH bgBrush, btnBrush, opBrush, eqBrush, screenBrush;
static HFONT  fontTitle, fontDisplay, fontBtn;

// Button IDs
enum {
    ID_0 = 100, ID_1, ID_2, ID_3, ID_4, ID_5, ID_6, ID_7, ID_8, ID_9,
    ID_ADD, ID_SUB, ID_MUL, ID_DIV, ID_MOD,
    ID_DOT, ID_EQ, ID_CLR, ID_BACK
};

void refreshDisplay() {
    SetWindowTextA(hDisplay, buffer);
}

void handleDigit(char d) {
    if (startNewEntry) {
        buffer[0] = d; buffer[1] = '\0';
        startNewEntry = false;
    } else if (strcmp(buffer, "0") == 0) {
        buffer[0] = d; buffer[1] = '\0';
    } else {
        size_t len = strlen(buffer);
        if (len < sizeof(buffer) - 1) { buffer[len] = d; buffer[len + 1] = '\0'; }
    }
    refreshDisplay();
}

void handleDot() {
    if (startNewEntry) { strcpy(buffer, "0."); startNewEntry = false; }
    else if (!strchr(buffer, '.')) strcat(buffer, ".");
    refreshDisplay();
}

void applyPendingOp() {
    double current = atof(buffer);
    if (pendingOp == 0) {
        accumulator = current;
    } else {
        switch (pendingOp) {
            case '+': accumulator += current; break;
            case '-': accumulator -= current; break;
            case '*': accumulator *= current; break;
            case '/': accumulator = (current != 0.0) ? accumulator / current : 0.0; break;
            case '%': accumulator = (current != 0.0) ? fmod(accumulator, current) : 0.0; break;
        }
    }
}

void formatAccumulator(char* out, size_t outSize) {
    if (accumulator == (long long)accumulator)
        snprintf(out, outSize, "%lld", (long long)accumulator);
    else
        snprintf(out, outSize, "%g", accumulator);
}

void handleOperator(char op) {
    applyPendingOp();
    pendingOp = op;
    startNewEntry = true;
    formatAccumulator(buffer, sizeof(buffer));
    refreshDisplay();
}

void handleEquals() {
    applyPendingOp();
    pendingOp = 0;
    startNewEntry = true;
    formatAccumulator(buffer, sizeof(buffer));
    refreshDisplay();
}

void handleClear() {
    accumulator = 0.0;
    pendingOp = 0;
    startNewEntry = true;
    strcpy(buffer, "0");
    refreshDisplay();
}

void handleBackspace() {
    size_t len = strlen(buffer);
    if (len > 1) buffer[len - 1] = '\0';
    else { strcpy(buffer, "0"); startNewEntry = true; }
    refreshDisplay();
}

// Subclass procedure so buttons paint with potato colors
WNDPROC origButtonProc;
LRESULT CALLBACK ButtonSubclassProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_ERASEBKGND) return 1; // avoid flicker, we paint in WM_PAINT via owner-draw alt (kept simple: skip)
    return CallWindowProc(origButtonProc, hwnd, msg, wp, lp);
}

HWND makeButton(HWND parent, const char* label, int id, int x, int y, int w, int h) {
    HWND btn = CreateWindowA("BUTTON", label, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                              x, y, w, h, parent, (HMENU)(INT_PTR)id, GetModuleHandle(NULL), NULL);
    SendMessage(btn, WM_SETFONT, (WPARAM)fontBtn, TRUE);
    return btn;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE: {
            fontTitle   = CreateFontA(22, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                       OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                       DEFAULT_PITCH, "Segoe UI");
            fontDisplay = CreateFontA(26, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                       OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                       DEFAULT_PITCH, "Consolas");
            fontBtn     = CreateFontA(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                       OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                       DEFAULT_PITCH, "Segoe UI");

            bgBrush     = CreateSolidBrush(POTATO_BG);
            btnBrush    = CreateSolidBrush(POTATO_BTN);
            opBrush     = CreateSolidBrush(POTATO_OP);
            eqBrush     = CreateSolidBrush(POTATO_ACCENT);
            screenBrush = CreateSolidBrush(POTATO_SCREEN);

            HWND title = CreateWindowA("STATIC", "Potato Calculator",
                                        WS_CHILD | WS_VISIBLE | SS_CENTER,
                                        10, 8, 280, 28, hwnd, NULL, GetModuleHandle(NULL), NULL);
            SendMessage(title, WM_SETFONT, (WPARAM)fontTitle, TRUE);

            hDisplay = CreateWindowA("EDIT", "0",
                                      WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_READONLY | WS_BORDER,
                                      15, 45, 270, 45, hwnd, NULL, GetModuleHandle(NULL), NULL);
            SendMessage(hDisplay, WM_SETFONT, (WPARAM)fontDisplay, TRUE);

            int startY = 100, btnW = 65, btnH = 60, gap = 8;
            int col0 = 15, col1 = col0 + btnW + gap, col2 = col1 + btnW + gap, col3 = col2 + btnW + gap;

            makeButton(hwnd, "C",  ID_CLR,  col0, startY,               btnW, btnH);
            makeButton(hwnd, "<-", ID_BACK, col1, startY,               btnW, btnH);
            makeButton(hwnd, "%",  ID_MOD,  col2, startY,               btnW, btnH);
            makeButton(hwnd, "/",  ID_DIV,  col3, startY,               btnW, btnH);

            makeButton(hwnd, "7", ID_7, col0, startY + (btnH+gap),      btnW, btnH);
            makeButton(hwnd, "8", ID_8, col1, startY + (btnH+gap),      btnW, btnH);
            makeButton(hwnd, "9", ID_9, col2, startY + (btnH+gap),      btnW, btnH);
            makeButton(hwnd, "*", ID_MUL, col3, startY + (btnH+gap),    btnW, btnH);

            makeButton(hwnd, "4", ID_4, col0, startY + 2*(btnH+gap),    btnW, btnH);
            makeButton(hwnd, "5", ID_5, col1, startY + 2*(btnH+gap),    btnW, btnH);
            makeButton(hwnd, "6", ID_6, col2, startY + 2*(btnH+gap),    btnW, btnH);
            makeButton(hwnd, "-", ID_SUB, col3, startY + 2*(btnH+gap),  btnW, btnH);

            makeButton(hwnd, "1", ID_1, col0, startY + 3*(btnH+gap),    btnW, btnH);
            makeButton(hwnd, "2", ID_2, col1, startY + 3*(btnH+gap),    btnW, btnH);
            makeButton(hwnd, "3", ID_3, col2, startY + 3*(btnH+gap),    btnW, btnH);
            makeButton(hwnd, "+", ID_ADD, col3, startY + 3*(btnH+gap),  btnW, btnH);

            makeButton(hwnd, "0", ID_0, col0, startY + 4*(btnH+gap),    btnW*2 + gap, btnH);
            makeButton(hwnd, ".", ID_DOT, col2, startY + 4*(btnH+gap),  btnW, btnH);
            makeButton(hwnd, "=", ID_EQ, col3, startY + 4*(btnH+gap),   btnW, btnH);
            break;
        }

        case WM_CTLCOLORSTATIC: {
            HDC hdc = (HDC)wp;
            SetTextColor(hdc, POTATO_DARK);
            SetBkColor(hdc, POTATO_BG);
            return (LRESULT)bgBrush;
        }

        case WM_CTLCOLOREDIT: {
            HDC hdc = (HDC)wp;
            SetTextColor(hdc, POTATO_DARK);
            SetBkColor(hdc, POTATO_SCREEN);
            return (LRESULT)screenBrush;
        }

        case WM_CTLCOLORBTN: {
            HDC hdc = (HDC)wp;
            SetTextColor(hdc, RGB(255,255,255));
            SetBkColor(hdc, POTATO_BTN);
            return (LRESULT)btnBrush;
        }

        case WM_ERASEBKGND: {
            HDC hdc = (HDC)wp;
            RECT rc; GetClientRect(hwnd, &rc);
            FillRect(hdc, &rc, bgBrush);
            return 1;
        }

        case WM_COMMAND: {
            int id = LOWORD(wp);
            switch (id) {
                case ID_0: handleDigit('0'); break;
                case ID_1: handleDigit('1'); break;
                case ID_2: handleDigit('2'); break;
                case ID_3: handleDigit('3'); break;
                case ID_4: handleDigit('4'); break;
                case ID_5: handleDigit('5'); break;
                case ID_6: handleDigit('6'); break;
                case ID_7: handleDigit('7'); break;
                case ID_8: handleDigit('8'); break;
                case ID_9: handleDigit('9'); break;
                case ID_DOT: handleDot(); break;
                case ID_ADD: handleOperator('+'); break;
                case ID_SUB: handleOperator('-'); break;
                case ID_MUL: handleOperator('*'); break;
                case ID_DIV: handleOperator('/'); break;
                case ID_MOD: handleOperator('%'); break;
                case ID_EQ:  handleEquals(); break;
                case ID_CLR: handleClear(); break;
                case ID_BACK: handleBackspace(); break;
            }
            break;
        }

        case WM_DESTROY:
            DeleteObject(bgBrush); DeleteObject(btnBrush);
            DeleteObject(opBrush); DeleteObject(eqBrush); DeleteObject(screenBrush);
            DeleteObject(fontTitle); DeleteObject(fontDisplay); DeleteObject(fontBtn);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {
    const char* CLASS_NAME = "PotatoCalculatorClass";

    WNDCLASSA wc = {};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInst;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(POTATO_BG);
    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(0, CLASS_NAME, "Potato Calculator",
                                 WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
                                 CW_USEDEFAULT, CW_USEDEFAULT, 320, 480,
                                 NULL, NULL, hInst, NULL);
    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}