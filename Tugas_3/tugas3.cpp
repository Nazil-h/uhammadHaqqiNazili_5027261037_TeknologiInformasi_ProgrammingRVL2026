#include <iostream>
#include <cmath>
using namespace std;

double endX(double L1, double L2, double theta1, double theta2){
    return L1*cos(theta1) + L2*cos(theta1+theta2);
}

double endY(double L1, double L2, double theta1, double theta2){
    return L1*sin(theta1) + L2*sin(theta1+theta2);
}

int main(){
    double L1 = 10.0, L2 = 5.0;
    double theta1 = 30.0, theta2 = 10.0;

    theta1 = theta1 * M_PI / 180.0;
    theta2 = theta2 * M_PI / 180.0;

    cout << "X = " << endX(L1,L2,theta1,theta2) << endl;
    cout << "Y = " << endY(L1,L2,theta1,theta2) << endl;

    return 0;
}