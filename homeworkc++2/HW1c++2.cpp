#include <iostream>

void Deposit(int &sum, int k)
{
    if (k <= 0)
    {
        std::cout << "error\n";
        return;
    }
    sum = sum + k;
}

void Withdraw(int &sum, int k)
{
    if (k <= 0)
    {
        std::cout << "error\n";
        return;
    }
    if (sum < k)
    {
        std::cout << "error\n";
        return;
    }
    sum = sum - k;
}

void Balance(int &sum, int k)
{
    std::cout << sum << "\n";
}

void Reset(int &sum, int k)
{
    sum = 0;
}

void DoubleSum(int &sum, int k)
{
    sum = sum * 2;
}

struct Command
{
    const char *name;
    void (*func)(int &, int);
};

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

int main()
{
    Command commands[] = {
        {"Deposit", Deposit},
        {"Withdraw", Withdraw},
        {"Balance", Balance},
        {"Reset", Reset},
        {"double", DoubleSum}};

    int sum = 0;

    while (true)
    {
        char cmd[100];
        std::cin >> cmd;

        if (Same(cmd, "stop"))
        {
            break;
        }

        int k = 0;

        if (Same(cmd, "Deposit") || Same(cmd, "Withdraw"))
        {
            std::cin >> k;
        }

        int count = 5;
        bool found = false;
        for (int i = 0; i < count; i++)
        {
            if (Same(cmd, commands[i].name))
            {
                commands[i].func(sum, k);
                found = true;
                break;
            }
        }

        if (!found)
        {
            std::cout << "error\n";
        }
    }

    return 0;
}