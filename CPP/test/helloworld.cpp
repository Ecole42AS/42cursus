#include <iostream>
#include <cmath>




class Student
{
    private:
        int temperature = 0;

    public:    
        std::string name;
        int         age;
        int         size;

        Student(int t, std::string a, int b, int c)
        {
            setTemp(t);
            name = a;
            age = b;
            size = c;
        }

        int getTemp()
        {
            std::cout << temperature << std::endl;
            return(temperature);
        }

        void setTemp(int temp)
        {
            temperature = temp;
        }
};

class Grade : public Student {
    public:
        int level;
        Grade(int t, std::string a, int b, int c, int l) : Student(t, a, b, c), level(l){
            level = l;
        }
};

int main()
{
    Student student1(60, "Alex", 12, 25);
    Grade   grade1(60, "Alex", 12, 25, 5);


    grade1.getTemp();
    std::cout << grade1.name << std::endl;
    std::cout << grade1.age << std::endl;
    std::cout << grade1.size << std::endl;
    std::cout << grade1.level << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    student1.getTemp();
    std::cout << student1.name << std::endl;
    std::cout << student1.age << std::endl;
    std::cout << student1.size << std::endl;
}

// template <typename T, typename C>

// C max(T nb1, C nb2)
// {
//     return(nb1 > nb2) ? nb1 : nb2;
// }

// int main ()
// {
//     int nb1 = 22;
//     double nb2 = 28.5;
 
//     std::cout << max(nb1, nb2);
// }


// int main()
// {
//     double a = 4;
//     double b = 3;
//     double c;

//     c = sqrt(pow(a, 2) + pow(b,2));
//     std::cout << c;
// }

// int main()
// {
//     using string = std::string;

//     string name;

//     std::cout << "what's your full name? ";
//     std::getline(std::cin >> std::ws, name);

//     std::cout << "Your name is: " << name;
//     std::cout << "hellooooo";
//     return 0;
// }

// int main()
// {
//     char op;
//     double num1;
//     double num2;
//     double res;

//     std::cout << "choose an operator: '+' or '/' or '-'";
//     std::cin >> op;

//     std::cout << "choose a number?";
//     std::cin >> num1;

//     std::cout << "choose a second number?";
//     std::cin >> num2;

//     switch(op)
//     {
//         case '+':
//             res = num1 + num2;
//             break;
//         case '-':
//             res = num1 - num2;
//             break;
//         case '/':
//             res = num1 / num2;
//             break;
//         default:
//             std::cout << "wrong operator\n+";
//     }
//     std::cout << res;
// }


// double get_total(double *arr, int size);

// int main()
// {   
//     double sum = 0;
//     double arr[] = {2.22, 22.5, 10.05};
//     int size = sizeof(arr) / sizeof(arr[0]);

//     sum = get_total(arr, size);
//     std::cout << "le total est : " << sum;
// }

// double get_total(double arr[], int size)
// {
//     double sum = 0;

//     for (int i = 0; i < size; i++)
//         sum += arr[i];
//     return sum;
// }

// int main()
// {

//     std::string name = "Hello World";
//     std::string *pname = &name;
//     std::string *ptest;
//     std::string first_name = "Alex";



//     std::cout << pname << '\n';
//     std::cout << &name << '\n';
//     std::cout << *pname << '\n';
//     std::cout << ptest;
    
// }

// int main()
// {
//     int size;
//     char *pLetters = NULL;


//     std::cout << "How many letters do you want to enter ?";
//     std::cin >> size;

//     pLetters = new char[size];

//     for (int i = 0; i < size; i++)
//     {
//         std::cout << "Please enter your letter at position " << i + 1 << ": ";
//         std::cin >> pLetters[i];
//     }

//     std::cout << pLetters;
//     delete[] pLetters;
// }


// int factorial(int nb);

// int main()
// {
//     int res;
    
//     res = factorial(10);

//     std::cout << res;
// }

// int factorial(int nb)
// {
//     int res = 1;

//     for(int i = 1; i <= nb; i++)
//         res *= i;
//     return (res);
// }

// int factorial(int nb)
// {
//     if (nb > 1)
//         nb *= factorial(nb - 1);
//     return(nb);
// }

//utiliser #pragma once dans les fichiers .hpp

/*
#pragma once est une directive de préprocesseur utilisée dans les fichiers d'en-tête (header files) en C++ pour éviter les problèmes de double inclusion. Lorsqu'elle est placée au début d'un fichier d'en-tête, elle indique au compilateur de ne l'inclure qu'une seule fois dans un fichier source, même si cet en-tête est inclus plusieurs fois dans le même fichier source ou dans plusieurs fichiers source différents. 
Cela améliore l'efficacité de la compilation en évitant la répétition inutile de code et en évitant les conflits de définitions multiples.*/


// std::endl --> vide le tampon de sortie et ajoute un retour à la ligne.
//std::flush vide le tampon de sortie
/*dans des situations où le contrôle précis du moment où les données sont écrites est crucial,
 vider le tampon de sortie peut être nécessaire.*/