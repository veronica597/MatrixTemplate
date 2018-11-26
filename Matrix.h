//
// Created by Veronica Pecchioli on 14/11/18.
//

#ifndef MATRIXTEMPLATE_MATRIX_H
#define MATRIXTEMPLATE_MATRIX_H

#include <utility>
#include <stdexcept>
#include <cstdlib>
using namespace std;

template <typename T>
class Matrix{

private:
    int rows;
    int col;
    T * M;

public:

  Matrix(int row, int col) throw(out_of_range); // costruttore con numero righe e colonne per matrici rettangolari
  explicit Matrix(int size) throw(out_of_range);  // costruttore con size per matrici quadrate
  virtual ~ Matrix();


  Matrix <T> trasponse(); // trasposta
  Matrix <T> select_row(int row) throw(out_of_range); // seleziona una riga
  Matrix <T> select_column (int column) throw(out_of_range); // seleziona una colonna
  Matrix <T> select_diag(int diag=0)throw (out_of_range);
  Matrix <T> product (Matrix <T> m1, Matrix <T> m2); // prodotto
  Matrix <T> sum (Matrix <T> m1, Matrix <T> m2); // somma
  //<T> size(); // std:: pair per ritornare le dimensioni di righe e colonne
  int get_col() const ; // ritorna numero colonne
  int get_rows()const; // ritorna numero colonne
  int rank() const;
  T min() const;
  T max() const;
  T det();
  T getValue(int row, int column) throw (out_of_range); // ritorno un valore in una certa posizione
  void setValue(int row, int column, T value)throw (out_of_range); // setto un valore in una certa posizione

};

template <typename T>
Matrix <T>::Matrix(int row, int col) throw (out_of_range): rows(row), col(col){
    if (row <= 0 || col <= 0)
        throw out_of_range ("Index error"); // lancio eccezione poi nel main avrò il blocco try-catch(out_of_range &e){print ("errore")}

    M = new T [row * col];
    for (int i=0; i<row * col;i++)
        //for (int j=0; j<col; j++)
            M[i]=0;
}

template <typename T>
Matrix<T>::Matrix(int size) throw(out_of_range): rows(size), col(size) {
    if (rows <= 0 || col <= 0)
        throw out_of_range ("Index error");

    M = new T [rows * col];
    for (int i=0; i<rows*col;i++)
        //for (int j = 0; j < col; j++)
            M[i] = 0;
}

template <typename T>
Matrix<T>::~Matrix() {
    delete[] M;
}

template <typename T> // tipo ritornato classe :: nome funzione
Matrix<T> Matrix<T>::select_row(int row) throw(out_of_range) {
    if (row<0 || row >= rows)
        throw out_of_range ("row index error");

    Matrix <T> mr = new Matrix(1,col);
    for (int i= 0; i < col; i++)
       mr.M[i] = M[row*col+i];
    return mr;
}

template<typename T>
Matrix<T> Matrix<T>::select_column(int column) throw(out_of_range){
    if (column<0 || column >= col)
        throw out_of_range ("col index error");

    Matrix <T> mc = new Matrix(rows,1);
    for (int i= 0; i < rows; i++)
        mc.M[i] = M[rows*i];
    return mc;
}

template<typename T>
int Matrix<T>::get_col() const {
    return col;
}

template<typename T>
int Matrix<T>::get_rows() const {
    return rows;
}

template<typename T>
T Matrix<T>::min() const {
T min = this -> M[0];
for( int i=1; i < rows * col; i++)
    if (this -> M[i] < min)
        min = this -> M[i];
return min;
}

template<typename T>
T Matrix<T>::max() const {
    T max = this -> M[0];
    for( int i=1; i < rows * col; i++)
        if (this -> M[i] > max)
            max = this -> M[i];
    return max;
}

template<typename T>
Matrix<T> Matrix<T>::select_diag(int diag) throw (out_of_range){
   if ((diag<0 && abs(diag) >= rows) || (diag >0 && abs(diag) >= col))
       throw out_of_range ("diag not found");

   Matrix <T> md = Matrix(rows,col);
   for (int i=0; i< rows; i++) { // scorro sulle righe per selezionare valori su diag
       int column = i + diag; //seleziono colonna giusta su cui prendere elemento
       if (column< col)
            md.setValue(getValue(i,column),i,column);
   }
    return md;
}

template<typename T>
T Matrix<T>::getValue(int row, int column)throw (out_of_range){
    if (row<0 || row >= rows || col<0 || column >= col)
        throw out_of_range ("index error");
    return M [row * column + col];
}

template<typename T>
void Matrix<T>::setValue(int row, int column, T value)throw (out_of_range){
    if (row<0 || row >= rows || col<0 || column >= col)
        throw out_of_range ("index error");
    M [row * column + col] = value;
}


#endif //MATRIXTEMPLATE_MATRIX_H
