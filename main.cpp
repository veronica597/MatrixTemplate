#include <iostream>
#include "Matrix.h"
using namespace std;




int main() {

    Matrix<float> M1(2, {1, 3, 0, 7});
    Matrix<float> M2(2, {2, 3, 3, 7});
    Matrix<float> A(3, {1, 3, 0, 7, 8, 0, 1, 3, 4});


    cout << "M1 =" << endl;
    for (int i = 0; i < M1.get_rows(); i++) {
        cout << "  ";
        for (int j = 0; j < M1.get_col(); j++) {
            cout << M1.getValue(i, j) << " ";
        }
        cout << endl;
    }

    Matrix<float> C(M2);
    cout << "C =" << endl;
    for (int i = 0; i < C.get_rows(); i++) {
        cout << "  ";
        for (int j = 0; j < C.get_col(); j++) {
            cout << C.getValue(i, j) << " ";
        }
        cout << endl;
    }

    cout << "massimo:" << M1.max() << endl;
    cout << "minimo:" << M2.min() << endl;


    M1.setValue(0, 0, 9);
    cout << "M1 modificata =" << endl;
    for (int i = 0; i < M1.get_rows(); i++) {
        cout << "  ";
        for (int j = 0; j < M1.get_col(); j++) {
            cout << M1.getValue(i, j) << " ";
        }
        cout << endl;
    }

    cout << "numero colonne M2: " << M2.get_col() << endl;
    cout << "numero righe M1: " << M1.get_rows() << endl;

    Matrix<float> M3 = C.Gauss();
    cout << "M3= " << endl;
    for (int i = 0; i < M3.get_rows(); i++) {
        cout << "  ";
        for (int j = 0; j < M3.get_col(); j++) {
            cout << M3.getValue(i, j) << " ";
        }
        cout << endl;
    }

    Matrix<float> M4 = M1.select_column(0);
    cout << "M4= " << endl;
    for (int i = 0; i < M4.get_rows(); i++) {
        cout << "  ";
        for (int j = 0; j < M4.get_col(); j++) {
            cout << M4.getValue(i, j) << " ";
        }
        cout << endl;
    }

    Matrix<float> M5 = M1.select_row(0);
    cout << "M5= " << endl;
    for (int i = 0; i < M5.get_rows(); i++) {
        cout << "  ";
        for (int j = 0; j < M5.get_col(); j++) {
            cout << M5.getValue(i, j) << " ";
        }
        cout << endl;
    }

    Matrix<float> M6= M1+M2;
    cout << "M6 = " << endl;
    for (int i = 0; i < M6.get_rows(); i++) {
        cout << "  ";
        for (int j = 0; j < M6.get_col(); j++) {
            cout << M6.getValue(i, j) << " ";
        }
        cout << endl;
    }

    Matrix<float> M7= M1*M2;
    cout << "M7 = " << endl;
    for (int i = 0; i < M7.get_rows(); i++) {
        cout << "  ";
        for (int j = 0; j < M7.get_col(); j++) {
            cout << M7.getValue(i, j) << " ";
        }
        cout << endl;
    }

    cout << "det M1 = " <<M1.det()<< endl;
    cout << "rango A = " <<A.rank()<< endl;

    Matrix<float> Trasponse = A.trasponse();
    cout << "trasponse = " << endl;
    for (int i = 0; i < Trasponse.get_rows(); i++) {
        cout << "  ";
        for (int j = 0; j < Trasponse.get_col(); j++) {
            cout << Trasponse.getValue(i, j) << " ";
        }
        cout << endl;
    }

}


