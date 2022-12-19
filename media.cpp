#include <iostream>
#include <cmath>

using namespace std;

int main(){
    double soma  = 0;
    double dado[20];
    double media = 0;
    for (int i = 0; i < 20 ; i++){
        cin >> dado[i];
        soma += dado[i]; 
    }

    media = soma/20;

    double desvio = 0;

    for (int i = 0; i < 20; i++) {
        float v = dado[i] - media;
        desvio += v * v;
    }

    desvio = sqrt(desvio / 20);
    
    cout << soma << "(desvio: " << desvio << ")\n";
}