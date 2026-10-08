#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// ===================== Hằng số =====================
#define BOARD_SIZE 12 // Kích thước ma trận bàn cờ
#define LEFT 3        // Tọa độ trái màn hình bàn cờ
#define TOP 1         // Tọa độ trên màn hình bàn cờ

// ===================== Khai báo kiểu dữ liệu =====================
struct _POINT { int x, y, c; }; // x: tọa độ cột trên màn hình, y: tọa độ dòng trên màn hình, c: đánh dấu

// ===================== Biến toàn cục =====================
_POINT _A[BOARD_SIZE][BOARD_SIZE]; // Ma trận bàn cờ
bool _TURN;                        // true là lượt người thứ nhất và false là lượt người thứ hai
int _COMMAND;                      // Biến nhận giá trị phím người dùng nhập
int _X, _Y;                        // Tọa độ hiện hành trên màn hình bàn cờ

// ===================== Hàm nhóm View =====================

// Cố định cửa sổ console, không cho phóng to / kéo giãn
void FixConsoleWindow() {
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}

// Di chuyển con trỏ tới vị trí (x, y) trên màn hình console
void GotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Vẽ bàn cờ
void DrawBoard(int pSize) {
    for (int i = 0; i <= pSize; i++) {
        for (int j = 0; j <= pSize; j++) {
            GotoXY(LEFT + 4 * i, TOP + 2 * j);
            printf(".");
        }
    }
}

// Hàm xử lý khi người chơi thắng/thua/hòa
int ProcessFinish(int pWhoWin) {
    GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2); // Nhảy tới vị trí thích hợp để in chuỗi thắng/thua/hòa
    switch (pWhoWin) {
    case -1:
        printf("Nguoi choi %d da thang va nguoi choi %d da thua\n", true, false);
        break;
    case 1:
        printf("Nguoi choi %d da thang va nguoi choi %d da thua\n", false, true);
        break;
    case 0:
        printf("Hai ben hoa nhau\n");
        break;
    case 2:
        _TURN = !_TURN; // Đổi lượt nếu không có gì xảy ra
    }
    GotoXY(_X, _Y); // Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
    return pWhoWin;
}

// Hỏi người dùng có tiếp tục hay không
int AskContinue() {
    GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 4);
    printf("Nhan 'y/n' de tiep tuc/dung: ");
    return toupper(_getch());
}

// ===================== Hàm nhóm Model =====================

// Khởi tạo dữ liệu mặc định ban đầu cho ma trận bàn cờ
void ResetData() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            _A[i][j].x = 4 * j + LEFT + 2; // Trùng với hoành độ màn hình bàn cờ
            _A[i][j].y = 2 * i + TOP + 1;  // Trùng với tung độ màn hình bàn cờ
            _A[i][j].c = 0; // 0 nghĩa là chưa ai đánh dấu, nếu đánh dấu phải theo quy
                            // định như sau: -1 là lượt true đánh, 1 là lượt false đánh
        }
    }
    _TURN = true; _COMMAND = -1; // Gán lượt và phím mặc định
    _X = _A[0][0].x; _Y = _A[0][0].y; // Thiết lập lại tọa độ hiện hành ban đầu
}

// Dọn dẹp tài nguyên
void GabageCollect() {
    // Dọn dẹp tài nguyên nếu có khai báo con trỏ
}

// Kiểm tra xem có người thắng/thua hay hòa
int demNgang( int i, int j, int me){
    int di[1] = {0};
    int dj[1] = {1};
        int cnt = 1;
        for (int dir = -1; dir <= 1; dir += 2){
            int hang = i + dir*di[0]; //giữ nguyên
            int cot = j + dir*dj[0];
            while (hang >= 0 && hang < BOARD_SIZE && cot >= 0 && cot < BOARD_SIZE && _A[hang][cot].c == me){
                cnt++;
                hang = hang + dir*di[0];
                cot = cot + dir*dj[0];
            }
        }
        return cnt;
    }
int demDoc( int i, int j, int me){
    int di[1] = {1};
    int dj[1] = {0};
        int cnt = 1;
        for (int dir = -1; dir <= 1; dir += 2){
            int hang = i + dir*di[0];
            int cot = j + dir*dj[0];
            while (hang >= 0 && hang < BOARD_SIZE && cot >= 0 && cot < BOARD_SIZE && _A[hang][cot].c == me){
                cnt++;
                hang = hang + dir*di[0];
                cot = cot + dir*dj[0];
            }
        }
        return cnt;
    }
int demCheoPhai( int i, int j, int me){
    int di[1] = {1};
    int dj[1] = {1};
        int cnt = 1;
        for (int dir = -1; dir <= 1; dir += 2){
            int hang = i + dir*di[0];
            int cot = j + dir*dj[0];
            while (hang >= 0 && hang < BOARD_SIZE && cot >= 0 && cot < BOARD_SIZE && _A[hang][cot].c == me){
                cnt++;
                hang = hang + dir*di[0];
                cot = cot + dir*dj[0];
            }
        }
        return cnt;
    }
int demCheoTrai( int i, int j, int me){
    int di[1] = {1};
    int dj[1] = {-1};
        int cnt = 1;
        for (int dir = -1; dir <= 1; dir += 2){
            int hang = i + dir*di[0];
            int cot = j + dir*dj[0];
            while (hang >= 0 && hang < BOARD_SIZE && cot >= 0 && cot < BOARD_SIZE && _A[hang][cot].c == me){
                cnt++;
                hang = hang + dir*di[0];
                cot = cot + dir*dj[0];
            }
        }
        return cnt;
    }
// Trả về: 0 = hòa, -1 = lượt 'true' thắng, 1 = lượt 'false' thắng, 2 = chưa ai thắng
int TestBoard() {
    int cnt;
    int i = (_Y - TOP - 1) / 2;   
    int j = (_X - LEFT - 2) / 4;  
    int me = _A[i][j].c; 
    if (demNgang(i,j,me) == 5 || demDoc(i,j,me) == 5 || demCheoPhai(i,j,me) == 5 || demCheoTrai(i,j,me) == 5){
        if (_TURN == true) return -1;
        else return 1;
}

    // Ma trận đầy => hòa (kiểm tra sau khi đã kiểm tra thắng)
    bool daDay = true;
    for (int i = 0; i < BOARD_SIZE && daDay; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (_A[i][j].c == 0) { daDay = false; break; }
    if (daDay) return 0; // Hòa

    return 2; // 2 nghĩa là chưa ai thắng
}

// Đánh dấu vào ma trận bàn cờ khi người chơi nhấn phím 'enter'
int CheckBoard(int pX, int pY) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0) {
                if (_TURN == true) _A[i][j].c = -1; // Nếu lượt hiện hành là true thì c = -1
                else _A[i][j].c = 1;                // Nếu lượt hiện hành là false thì c = 1
                return _A[i][j].c;
            }
        }
    }
    return 0;
}

// ===================== Hàm nhóm Control =====================

// Chuẩn bị trước khi vào trò chơi
void StartGame() {
    system("cls");
    ResetData();            // Khởi tạo dữ liệu gốc
    DrawBoard(BOARD_SIZE);  // Vẽ màn hình game
}

// Thoát game
void ExitGame() {
    system("cls");
    GabageCollect();
    // Có thể lưu game trước khi exit
}

// Các hàm di chuyển trên màn hình bàn cờ
void MoveRight() {
    if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x) {
        _X += 4;
        GotoXY(_X, _Y);
    }
}

void MoveLeft() {
    if (_X > _A[0][0].x) {
        _X -= 4;
        GotoXY(_X, _Y);
    }
}

void MoveDown() {
    if (_Y < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y) {
        _Y += 2;
        GotoXY(_X, _Y);
    }
}

void MoveUp() {
    if (_Y > _A[0][0].y) {
        _Y -= 2;
        GotoXY(_X, _Y);
    }
}



// ===================== Hàm main =====================
int main() {
    FixConsoleWindow();
    StartGame();
    bool validEnter = true;
    while (1) {
        int c = _getch();                    

        if (c == 224 || c == 0) {            
            int c2 = _getch();
            if (_TURN == true) {             
                if (c2 == 75) MoveLeft();
                else if (c2 == 72) MoveUp();
                else if (c2 == 80) MoveDown();
                else if (c2 == 77) MoveRight();
            }
            continue;
        }

        _COMMAND = toupper(c);

        if (_COMMAND == 27) {                
            ExitGame();
            return 0;
        }

        if (_TURN == false) {                
            if (_COMMAND == 'A') MoveLeft();
            else if (_COMMAND == 'W') MoveUp();
            else if (_COMMAND == 'S') MoveDown();
            else if (_COMMAND == 'D') MoveRight();
        }

        if (_COMMAND == 13) {                
            switch (CheckBoard(_X, _Y)) {
            case -1:
                printf("X"); break;
            case 1:
                printf("O"); break;
            case 0:
                validEnter = false;          
            }
            if (validEnter == true) {
                switch (ProcessFinish(TestBoard())) {
                case -1: case 1: case 0:
                    if (AskContinue() != 'Y') {
                        ExitGame();
                        return 0;
                    }
                    else StartGame();
                }
            }
            validEnter = true;
        }
    }
}