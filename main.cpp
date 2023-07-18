//******************************************
//  SIR model by Belardinelli & Ronchetti
//******************************************

#include "disease.hpp"
using namespace std;
int main() {
    int N, I0, days; //population sample, initial number of infected people, days of development
    double BETA, GAMMA;
    string name;
    
    cout << "Welcome to SIR simulator!" << endl;
    cout << "Please insert the name of the disease: ";
    cin >> name;

    do{
        cout << "Please insert Beta value: ";
        cin >> BETA;
        if (BETA<0 || BETA >1)
            cout << "Error: Beta value must be in the range [0,1]" << endl;
    } while (BETA<0 || BETA >1);

    do{
        cout << "Please insert Gamma value: ";
        cin >> GAMMA;
        if (GAMMA<0 || GAMMA >1)
            cout << "Error: Gamma value must be in the range [0,1]" << endl;
    } while (GAMMA<0 || GAMMA >1);

    do{
        cout << "Please insert the population sample: ";
        cin >> N;
        if (N<=0)
            cout << "Error: N must be greater than 0" << endl;
    } while (N<=0 );

    do{
        cout << "Please insert the initial number of infected people: ";
        cin >> I0;
        if (I0<=0)
            cout << "Error: I0 value must be > 0" << endl;
    } while (I0<=0 );

    do{
        cout << "Please insert the number of days of development of the epidemic: ";
        cin >> days;
        if (days<=0)
            cout << "Error: The number of days must be in the range ]0,2e^9]" << endl;
    } while (days<=0 );

    disease::Disease d(name, N, I0, BETA, GAMMA);
    
    d.evolve(days);
    
    d.f_print();
    cout << "Operation completed: file epidemic.txt is ready!" << endl;
}
