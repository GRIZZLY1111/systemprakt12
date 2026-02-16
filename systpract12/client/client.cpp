// client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>

int main() {
    setlocale(0, "rus");

    while (true) {
        system("cls");
        HANDLE printerMutex = OpenMutex(SYNCHRONIZE, FALSE, L"SharedPrinterLock");

        if (!printerMutex) {
            std::cout << "Принтер не запущен.\n";
            _getch();
            break;
        }

        std::cout << "Выберите действие:\n"
            << "1 — отправить задание\n"
            << "2 — фоновый приоритет\n"
            << "3 — нормальный приоритет\n"
            << "4 — высокий приоритет\n"
            << "5 — завершить работу\n"
            << "> ";

        char userChoice = _getch();
        std::cout << "\n";

        if (userChoice == '1') {
            if (WaitForSingleObject(printerMutex, 0) == WAIT_TIMEOUT) {
                system("cls");
                std::cout << "Мьютекс занят. Повторите позже.\n";
            }
            else {
                system("cls");
                std::cout << "Задание отправлено на печать.\n";
                Sleep(1000);
                ReleaseMutex(printerMutex);
                Sleep(1000);

                WaitForSingleObject(printerMutex, INFINITE);
                system("cls");
                std::cout << "Печать завершена.\n";
                ReleaseMutex(printerMutex);
            }
        }
        else if (userChoice == '2') {
            SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
            std::cout << "Фоновый приоритет установлен.\n";
        }
        else if (userChoice == '3') {
            SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
            std::cout << "Нормальный приоритет установлен.\n";
        }
        else if (userChoice == '4') {
            SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
            std::cout << "Высокий приоритет установлен.\n";
        }
        else if (userChoice == '5') {
            std::cout << "Завершение работы клиента.\n";
            CloseHandle(printerMutex);
            Sleep(3000);
            break;
        }
        else {
            std::cout << "Неизвестная команда.\n";
        }

        Sleep(2500);
        CloseHandle(printerMutex);
    }
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
