

#include "RedBlackTree.h"

int main()
{
    int wybor;
    std::string input;
    bool is_number = true;
    
    RedBlackTree rb;
    do
    {
        system("CLS");
        rb.print();

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
            rb.add(std::stoi(input));
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
            rb.remove(std::stoi(input));
            break;
        case 3:
            rb.clear(rb.getRoot());
            break;
        case 4:
            exit(1);
            break;

        default:
            std::cout << "POMYLKA!";
            Sleep(2000);
            break;
        }

    } while (wybor != 5);

    return 0;
}
