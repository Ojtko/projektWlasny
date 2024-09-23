#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <time.h>
#include <sstream>
// Identyfikator kontrolki dla okna gry
#define IDC_GAME_WINDOW 1001
// Wymiary planszy
const int rows = 10;
const int cols = 10;
const int totalMines = 5;
// Kody pól planszy
const int emptyCode = 0;
const int mineCode = 9;
int board[rows][cols] = { 0 };
bool revealed[rows][cols] = { false };
bool flagged[rows][cols] = { false };
int remainingCells = rows * cols - totalMines;
bool gameWon = false;

void PlaceMines() {
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < totalMines; ++i) {
        int row, col;
        do {
            row = rand() % rows;
            col = rand() % cols;
        } while (board[row][col] == mineCode);
        board[row][col] = mineCode;
    }
}

void CalculateNumbers() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board[i][j] != mineCode) {
                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        int newRow = i + x;
                        int newCol = j + y;
                        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && board[newRow][newCol] == mineCode) {
                            ++board[i][j];
                        }
                    }
                }
            }
        }
    }
}

void DrawGameBoard(HWND hwnd, HDC hdc) {
    COLORREF defaultBkColor = GetSysColor(COLOR_BTNFACE);
    COLORREF revealedBkColor = RGB(255, 255, 255);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            RECT rect = { j * 40, i * 40, (j + 1) * 40, (i + 1) * 40 };
            if (revealed[i][j]) {
                std::wstringstream wss;
                wss << board[i][j];
                std::wstring text = wss.str();
                SetBkColor(hdc, revealedBkColor);
                FillRect(hdc, &rect, CreateSolidBrush(revealedBkColor));
                DrawEdge(hdc, &rect, EDGE_RAISED, BF_RECT);
                SetTextColor(hdc, RGB(0, 0, 0)); // Ustawienie koloru tekstu na czarny
                DrawText(hdc, text.c_str(), text.length(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            }
            else if (flagged[i][j]) {
                // Rysowanie flagi
                FillRect(hdc, &rect, CreateSolidBrush(defaultBkColor));
                DrawEdge(hdc, &rect, EDGE_RAISED, BF_RECT);
                SetTextColor(hdc, RGB(255, 0, 0)); // Ustawienie koloru tekstu na czarny
                DrawText(hdc, L"F", 1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            }
            else {
                // Rysowanie zakrytego pola (kwadrat z obramowaniem)
                FillRect(hdc, &rect, CreateSolidBrush(defaultBkColor));
                DrawEdge(hdc, &rect, EDGE_SUNKEN, BF_RECT);
            }

            DeleteObject(CreateSolidBrush(revealedBkColor));
        
        }
    }
}

void RevealZero(HWND hwnd, int row, int col) {
    if (row >= 0 && row < rows && col >= 0 && col < cols && !revealed[row][col]) {
        revealed[row][col] = true;
        remainingCells--;
        if (board[row][col] == 0) {
            // Jeśli odsłonięta komórka zawiera 0, rekurencyjnie odsłoń wszystkie sąsiednie zera
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int newRow = row + i;
                    int newCol = col + j;
                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                        RevealZero(hwnd, newRow, newCol);
                    }
                }
            }
        }
        RECT rect = { col * 40, row * 40, (col + 1) * 40, (row + 1) * 40 };
        InvalidateRect(hwnd, &rect, TRUE);
    }

}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        PlaceMines();
        CalculateNumbers();
        break;

    case WM_LBUTTONDOWN: {
        int mouseX = LOWORD(lParam) / 40;
        int mouseY = HIWORD(lParam) / 40;

        if (board[mouseY][mouseX] == mineCode) {
            MessageBox(hwnd, _T("Przegrana!"), _T("Koniec gry"), MB_OK | MB_ICONERROR);
            SendMessage(hwnd, WM_DESTROY, 0, 0);
        }
        else if (board[mouseY][mouseX] == 0) {
            RevealZero(hwnd, mouseY, mouseX);
        }
        else {
            revealed[mouseY][mouseX] = true;
            InvalidateRect(hwnd, NULL, TRUE);
            remainingCells--;
        }
        if (remainingCells == 0 && !gameWon) {
            MessageBox(hwnd, _T("Wygrana!"), _T("Koniec gry"), MB_OK);
            SendMessage(hwnd, WM_DESTROY, 0, 0);
            //StartWinAnimation(hwnd);
            gameWon = true;
        }
       
        break;
    }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        DrawGameBoard(hwnd, hdc);
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        PostQuitMessage(0);
        break;
    
    case WM_RBUTTONDOWN: {
        int mouseX = LOWORD(lParam) / 40;
        int mouseY = HIWORD(lParam) / 40;
        if (!revealed[mouseY][mouseX]) {
            flagged[mouseY][mouseX] = !flagged[mouseY][mouseX];
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);

    }
    return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
   WNDCLASS wc = {0};
   wc.lpfnWndProc = WindowProc;
   wc.hInstance = hInstance;
   wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND +1);
   wc.lpszClassName = _T("SaperWindowClass");
   RegisterClass(&wc);

   int screenWidth = GetSystemMetrics(SM_CXSCREEN);
   int screenHeight = GetSystemMetrics(SM_CYSCREEN);

   // Rozmiary i pozycja okna
   int windowWidth = 420;
   int windowHeight = 440;
   int windowX = (screenWidth - windowWidth) / 2;
   int windowY = (screenHeight - windowHeight) / 2;
   HWND hwnd = CreateWindowEx(0, _T("SaperWindowClass"), _T("Saper"),
       WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, windowX, windowY,
                              windowWidth,windowHeight, NULL, NULL, hInstance, NULL);
   if (hwnd == NULL) {
       return 0;
   }
   ShowWindow(hwnd, nCmdShow);
   MSG msg;
   while (GetMessage(&msg, NULL, 0, 0)) {
       TranslateMessage(&msg);
       DispatchMessage(&msg);
   }
   return msg.wParam;
}