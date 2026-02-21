// systpract12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <conio.h>
#include <Windows.h>

DWORD WINAPI Print(LPVOID) {
    std::cout << "Печать...\n";
    srand(GetTickCount64());
    Sleep(5000 + rand() % 10001);
    return 0;
}

int main() {
    setlocale(0, "rus");

    HANDLE printerMutex = CreateMutex(NULL, FALSE, L"SharedPrinterLock");
    if (!printerMutex) {
        std::cout << "Ошибка создания мьютекса принтера.\n";
        return 1;
    }

    std::cout << "Принтер запущен. Ожидание заданий...\n";

    int idleSeconds = 0;
    const int MAX_IDLE_SECONDS = 600;

    while (idleSeconds <= MAX_IDLE_SECONDS) {
        std::cout << "Ожидание...\n";

        if (WaitForSingleObject(printerMutex, 0) == WAIT_TIMEOUT) {
            idleSeconds = 0;
            system("cls");

            WaitForSingleObject(printerMutex, INFINITE);

            DWORD threadId;
            HANDLE printThread = CreateThread(NULL, 0, Print, NULL, 0, &threadId);
            if (!printThread) {
                std::cout << "Ошибка создания потока печати.\n";
                break;
            }

            if (WaitForSingleObject(printThread, 10000) == WAIT_OBJECT_0) {
                system("cls");
                std::cout << "Готово\n";
            }
            else {
                system("cls");
                std::cout << "Ошибка печати\n";
            }

            CloseHandle(printThread);
        }
        else {
            idleSeconds++;
        }

        ReleaseMutex(printerMutex);
        Sleep(1000);
        system("cls");
    }

    CloseHandle(printerMutex);
    std::cout << "Принтер отключился из-за бездействия.\n";
    Sleep(2500);
    return 0;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
