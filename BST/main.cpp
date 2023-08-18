#include "BST.h"
#include <iostream>
#include <string>
#include <Windows.h>

int main()
{
    int wybor;
    std::string input;
    bool is_number = true;

    BST bst;
    do
    {
        system("CLS");
        bst.print();

        std::cout << "---------------------------" << std::endl;
        std::cout << "1 - dodaj element" << std::endl;
        std::cout << "2 - usun element" << std::endl;
        std::cout << "3 - wyczysc drzewo" << std::endl;
        std::cout << "4 - opusc program" << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "Wybor: ";
        std::cin >> wybor;

        switch (wybor)
        {
        case 1:
            do
            {
                std::cout << "Podaj Liczbe do dodania: ";
                std::cin >> input;

                is_number = true;
                for (char c : input) {
                    if (!isdigit(c)) {
                        is_number = false;
                    }
                }


            } while (!is_number);
            bst.add(std::stoi(input));
            break;
        case 2:

            do
            {
                std::cout << "Podaj Liczbe do usuniecia: ";
                std::cin >> input;

                is_number = true;
                for (char c : input) {
                    if (!isdigit(c)) {
                        is_number = false;
                    }
                }


            } while (!is_number);
            bst.remove(std::stoi(input));
            break;
        case 3:
            bst.clear(bst.getRoot());
            break;
        case 4:
            exit(1);
            break;

        default:
            std::cout << "POMYLKA!";
            Sleep(2000);
            break;
        }

    } while (wybor != 4);

    return 0;
}

