#include <iostream>

bool Same(const char *a, const char *b)
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
        {
            return false;
        }
        i++;
    }
    return a[i] == b[i];
}

void Clear(char board[5][10])
{
    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            board[y][x] = ' ';
        }
    }
}

bool Put(char board[5][10], int x, int y, char c)
{
    if (x < 0 || x >= 10 || y < 0 || y >= 5)
    {
        return false;
    }
    board[y][x] = c;
    return true;
}

bool Text(char board[5][10], int x, int y, const char *word)
{
    int len = 0;
    while (word[len])
    {
        len++;
    }
    if (y < 0 || y >= 5)
    {
        return false;
    }
    if (x < 0 || x + len > 10)
    {
        return false;
    }
    for (int i = 0; i < len; i++)
    {
        board[y][x + i] = word[i];
    }
    return true;
}

void Print(char board[5][10])
{
    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            std::cout << board[y][x];
        }
        std::cout << '\n';
    }
}

int main()
{
    char board[5][10];
    Clear(board);
    char cmd[10];
    while (std::cin >> cmd)
    {
        if (Same(cmd, "quit"))
        {
            break;
        }
        else if (Same(cmd, "clear"))
        {
            Clear(board);
        }
        else if (Same(cmd, "print"))
        {
            Print(board);
        }
        else if (Same(cmd, "put"))
        {
            int x, y;
            char c;
            std::cin >> x >> y >> c;
            if (!Put(board, x, y, c))
            {
                std::cout << "error\n";
            }
        }
        else if (Same(cmd, "text"))
        {
            int x, y;
            char word[20];
            std::cin >> x >> y >> word;
            if (!Text(board, x, y, word))
            {
                std::cout << "error\n";
            }
        }
    }
    return 0;
}