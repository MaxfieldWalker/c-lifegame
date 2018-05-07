#include <stdio.h>
#include <stdlib.h>

/**
 * 盤面をコンソールに出力する関数
 */
void display(int col, int row, int board[])
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            char c = board[i * col + j] ? '*' : '-';
            printf("%c ", c);
        }
        printf("\n");
    }
}

/**
 * セルの状態をトグルする
 * 生ならば死へ
 * 死ならば生へ
 */
void toggle_cell_state(int x, int y, int w, int h, int board[])
{
    if (board[y * w + x] == 1)
    {
        board[y * w + x] = 0;
    }
    else
    {
        board[y * w + x] = 1;
    }
}

int get_cell_state(int x, int y, int w, int h, int board[])
{
    return board[y * w + x];
}

int count_alive_cell(int x, int y, int w, int h, int board[])
{
    int a[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

    int count = 0;
    for (int i = 0; i < 8; i++)
    {
        int dx = a[i][0];
        int dy = a[i][1];
        int x_temp = x + dx;
        int y_temp = y + dy;
        printf("(%d, %d)\n", x_temp, y_temp);
        if (
            (x_temp < 0) || (x_temp >= w) || (y_temp < 0) || (y_temp >= h))
        {
        }
        else
        {
            if (get_cell_state(x_temp, y_temp, w, h, board) > 0)
            {
                count++;
                // printf("count up: (%d, %d) => %d\n", x, y, count);
            }
        }
        // int actual_x = x_temp < 0 ? 0 : x_temp >= w ? w - 1 : x_temp;
        // int actual_y = y_temp < 0 ? 0 : y_temp >= h ? h - 1 : y_temp;
        // if (board[actual_y * h + actual_x])
        // {
        //     count++;
        // }
    }
    return count;
}

void update_board(int w, int h, int board[])
{
    int accept[100] = {0};
    int count = 0;
    // すべてのセルについて
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            // 周りの生きているセルを数える
            int n = count_alive_cell(x, y, w, h, board);

            if (get_cell_state(x, y, w, h, board) > 0)
            {
                if (!(n == 2 || n == 3))
                {
                    // toggle_cell_state(x, y, w, h, board);
                    accept[count++] = x * 10 + y;
                }
            }
            else
            {
                // 現在死亡の場合
                if (n == 3)
                {
                    // printf("Change");
                    accept[count++] = x * 10 + y;
                    // toggle_cell_state(x, y, w, h, board);
                }
            }
        }
    }

    for (int i = 0; i < count; i++)
    {
        int x = accept[i] / 10;
        int y = accept[i] % 10;
        toggle_cell_state(x, y, w, h, board);
    }
}

void lifegame(const int w, const int h, int input[], int input_length)
{
    // 盤面を作成
    int *b = calloc(w * h, sizeof(int));

    // 入力をもとに、盤面の状態を初期化する
    for (int i = 0; i < input_length; i++)
    {
        int n = input[i];
        int x = n / 10;
        int y = n % 10;
        toggle_cell_state(x, y, w, h, b);
    }

    display(w, h, b);
    printf("\n");

    // 12世代進める
    for (int i = 0; i < 12; i++)
    {
        update_board(w, h, b);
        display(w, h, b);
        printf("\n");
    }

    free(b);
}

int main()
{
    /// 入力として与えるもの
    /// 盤面の横幅 (col)
    /// 盤面の縦幅 (row)
    /// 盤面の初期状態
    ///   -> ライフが存在するセルの番地を表す数値の配列
    ///   -> 番地の表し方 (2, 3) => 23, (0, 2) => 2
    const int w = 10;
    const int h = 10;
    int input[] = {11, 22, 3, 13, 23};
    int input_length = 5;

    /// lifegame関数を作成し、この位置で呼び出すこと。
    lifegame(w, h, input, input_length);

    return 0;
}
