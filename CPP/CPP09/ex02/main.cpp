#include "PmergeMe.hpp"


// std::deque fournit un accès direct aux éléments via l'indexation
// std::vector est généralement choisi pour les algorithmes de tri comme Merge Sort en raison de son allocation continue, de son accès direct rapide et de sa performance en termes de gestion de la mémoire. 
int main(int ac, char **av)
{
    PmergeMe pmergeMe;
    size_t length = ac - 1;

    if (ac <= 1)
    {
        std::cerr << "Usage: ./PmergeMe [int1] [int2] [int3] ..." << std::endl;
        return 1;
    }

    pmergeMe.setArrayCapacity(length);
    std::vector<int>& array = pmergeMe.getArray();

    std::cout << "Before: ";
    for (size_t i = 0; i < length; ++i)
    {
        char *endptr;
        long int value = std::strtol(av[i + 1], &endptr, 10);

        if (*endptr != '\0')
        {
            std::cerr << "\nError: Invalid character(s) in: " << av[i + 1] << std::endl;
            return 1;
        }

        if (value < 0 || value > INT_MAX)
        {
            std::cerr << "\nError: The value of an argument is not within the range of a positive int: " << av[i + 1] << std::endl;
            return 1;
        }

        int int_value = static_cast<int>(value);
        array.push_back(int_value);
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    pmergeMe.mergeSort(array, length);

    std::cout << "After: ";
    for (size_t i = 0; i < length; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "*********** Deque ***********" << std::endl;

    std::deque<int>& deque = pmergeMe.getDeque();
    std::cout << "Before: ";
    for (size_t i = 0; i < length; ++i)
    {
        char *endptr;
        long int value = std::strtol(av[i + 1], &endptr, 10);

        if (*endptr != '\0')
        {
            std::cerr << "\nError: Invalid character(s) in: " << av[i + 1] << std::endl;
            return 1;
        }

        if (value < 0 || value > INT_MAX)
        {
            std::cerr << "\nError: The value of an argument is not within the range of a positive int: " << av[i + 1] << std::endl;
            return 1;
        }

        int int_value = static_cast<int>(value);
        deque.push_back(int_value);
        std::cout << deque[i] << " ";
    }
    std::cout << std::endl;

    pmergeMe.mergeSortDeque(deque);

    std::cout << "After: ";
    for (size_t i = 0; i < length; ++i)
    {
        std::cout << deque[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
