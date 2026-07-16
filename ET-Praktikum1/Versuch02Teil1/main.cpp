//////////////////////////////////////////////////////////////////////////////
// Praktikum Informatik 1
//
// Datei:  main.cpp
// Inhalt: Hauptprogramm
//////////////////////////////////////////////////////////////////////////////

#include <iostream>

int fibonacci(int n)
{
    if (n <= 1)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{

    for (int n = 0; n <= 25; ++n)
    {
        std::cout << "Fibonacci(" << n << ") = " << fibonacci(n) << std::endl;
    }
    return 0;
}
