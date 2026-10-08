#include <stdio.h>

#define SIZE 15

// Khởi tạo bàn cờ trống
void khoiTaoBanCo(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '.';
        }
    }
}

// In bàn cờ ra màn hình Console
void inBanCo(char board[SIZE][SIZE]) {
    printf("    ");
    for (int i = 0; i < SIZE; i++) printf("%2d ", i); // in so cot
    printf("\n\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%2d  ", i); // in so hang
        for (int j = 0; j < SIZE; j++) {
            printf("%2c ", board[i][j]);
        }
        printf("\n");
    }
}

// Thuật toán kiểm tra chiến thắng tại nước đi (row, col) của người chơi ký tự ký hiệu (quanQuan)
int kiemTraThang(char board[SIZE][SIZE], int row, int col, char quanQuan) {
    int dem;
    int dr[] = { 0, 1, 1, 1 }; // 4 hướng: Ngang, Dọc, Chéo chính, Chéo phụ
    int dc[] = { 1, 0, 1, -1 };

    for (int i = 0; i < 4; i++) {
        dem = 1; // Tính chính quân vừa đánh

        // Kiểm tra chiều thuận
        int r = row + dr[i], c = col + dc[i];
        while (r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == quanQuan) {
            dem++;
            r += dr[i];  // Từ ô đang check -> check tiếp các ô lân cận
            c += dc[i];
        }

        // Kiểm tra chiều ngược lại
        r = row - dr[i];
        c = col - dc[i];
        while (r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == quanQuan) {
            dem++;
            r -= dr[i];
            c -= dc[i];
        }

        // Nếu đủ 5 quân liên tiếp (chưa tính luật chặn đầu)
        if (dem >= 5) return 1;
    }
    return 0;
}

int main() {
    char board[SIZE][SIZE];
    int row, col;
    int luot = 0; // 0: Người chơi X, 1: Người chơi O
    int soNuocDi = 0;

    khoiTaoBanCo(board);

    while (soNuocDi < SIZE * SIZE) {
        inBanCo(board);
        char quanHienTai = (luot == 0) ? 'X' : 'O';
        printf("\nNguoi choi [%c] nhap toa do (hang cot): ", quanHienTai);

        // Dùng scanf_s hoặc scanf tùy môi trường Visual Studio của bạn
        if (scanf_s("%d %d", &row, &col) != 2) {
            printf("Dinh dang khong hop le!\n");
            continue;
        }

        // Kiểm tra tính hợp lệ của ô nước đi
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != '.') {
            printf("Nuoc đi khong hop le! Vui long chon o khac.\n");
            continue;
        }

        // Đánh quân
        board[row][col] = quanHienTai;
        soNuocDi++;

        // Kiểm tra thắng thua
        if (kiemTraThang(board, row, col, quanHienTai)) {
            inBanCo(board);
            printf("\nCHUC MUNG! Nguoi choi [%c] da CHIEN THANG!\n", quanHienTai);
            break;
        }

        // Đổi lượt
        luot = 1 - luot;
    }

    return 0;
} 