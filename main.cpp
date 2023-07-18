//******************************************
//  SIR model by Belardinelli & Ronchetti
//******************************************

#include "disease.hpp"

int main() {
    int N, I0, days; //population sample, initial number of infected people, days of development
    double BETA, GAMMA;
    std::string name;
    
    std::cout << "Welcome to SIR simulator!" << '\n';
    std::cout << "Please insert the name of the disease: ";
    std::cin >> name;

    do{
        std::cout << "Please insert Beta value: ";
        std::cin >> BETA;
        if (BETA<0 || BETA >1)
            std::cout << "Error: Beta value must be in the range [0,1]" << '\n';
    } while (BETA<0 || BETA >1);

    do{
        std::cout << "Please insert Gamma value: ";
        std::cin >> GAMMA;
        if (GAMMA<0 || GAMMA >1)
            std::cout << "Error: Gamma value must be in the range [0,1]" << '\n';
    } while (GAMMA<0 || GAMMA >1);

    do{
        std::cout << "Please insert the population sample: ";
        std::cin >> N;
        if (N<=0)
            std::cout << "Error: N must be greater than 0" << '\n';
    } while (N<=0 );

    do{
        std::cout << "Please insert the initial number of infected people: ";
        std::cin >> I0;
        if (I0<=0)
            std::cout << "Error: I0 value must be > 0" << '\n';
    } while (I0<=0 );

    do{
        std::cout << "Please insert the number of days of development of the epidemic: ";
        std::cin >> days;
        if (days<=0)
            std::cout << "Error: The number of days must be in the range ]0,2e^9]" << '\n';
    } while (days<=0 );

    disease::Disease d(name, N, I0, BETA, GAMMA);
    
    d.evolve(days);
    
    d.f_print();
    std::cout << "Operation completed: file epidemic.txt is ready!" << '\n';
}
