//
// Created by Veronica Pecchioli on 14/11/18.
//

#ifndef MATRIXTEMPLATE_MATRIX_H
#define MATRIXTEMPLATE_MATRIX_H

#include <iostream>
#include <utility>
#include <vector>
#include <stdexcept>
#include <cstdlib>
using namespace std;

template <typename T>
class Matrix{

private:
    int rows;
    int col;
    T *M;

public:
  Matrix(int row,int col) throw(invalid_argument); // costruttore per matrici rettangolari
  explicit Matrix(int size) throw(invalid_argument);  // costruttore per quadrate
  Matrix (int rows, int col, const vector<T>& v)throw(invalid_argument); // costruttore con vettore di valori da inserire nella matrice
  Matrix (int size, const vector <T>& v) throw(invalid_argument);
  Matrix(const Matrix<T>& Matrix); // costruttore di copia
  virtual ~ Matrix();

  int get_col() const ; // n colonne
  int get_rows()const; // n righe
  T getValue(int row,int column) throw (out_of_range);
  void setValue(int row,int column,const T value)throw (out_of_range);
  Matrix<T>& trasponse();
  Matrix<T> Gauss() const throw (invalid_argument);
  int rank() const;
  T min() const;
  T max() const;
  T det() const throw(invalid_argument);
  Matrix <T> select_row(int row) throw(out_of_range); // seleziona una riga
  Matrix <T> select_column (int column) throw(out_of_range); // seleziona una colonna
  Matrix <T> operator *(Matrix <T> &m1) throw (invalid_argument); // prodotto.

  Matrix <T> operator *(const T value); // prodotto per scalare
  Matrix <T>& operator =(const Matrix<T> &m1); // assegnamento
  bool operator ==(const Matrix<T> &m1) const; // uguaglianza
  bool operator !=(const Matrix<T>& m1) const; // diversità
  Matrix <T> operator +(const Matrix <T>& m1)throw (invalid_argument); // somma

};




template <typename T>
Matrix <T>::Matrix(int row, int col) throw (invalid_argument): rows(row), col(col){
    if (row <= 0 || col <= 0)
        throw invalid_argument ("Index error");

    M = new T [row * col];
    for (int i=0; i<row * col;i++)
            M[i]=0;
}

template <typename T>
Matrix<T>::Matrix(int size) throw(invalid_argument): rows(size), col(size) {
    if (rows <= 0 || col <= 0)
        throw invalid_argument ("Index error");

    M = new T [rows * col];
    for (int i=0; i<rows*col;i++)
            M[i] = 0;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &Matrix): rows(Matrix.rows), col(Matrix.col), M(new T[rows*col]) {
    for (int i=0; i<rows*col; i++)
        M[i]=Matrix.M[i];
}


template <typename T>
Matrix<T>::~Matrix() {
    delete[] M;
}

template <typename T>
Matrix<T> Matrix<T>::select_row(int row) throw(out_of_range) {
    if (row<0 || row >= rows)
        throw out_of_range ("row index error");

    Matrix <T> mr (1,col);
    for (int i= 0; i < col; i++)
       mr.M[i] = M[row*col+i];
    return mr;
}

template<typename T>
Matrix<T> &Matrix<T>::trasponse() {
    T* traspose = new T[rows*col];
    for (int i =0; i< rows; i++) {
        for (int j = 0; j < col; j++)
            traspose[j * rows + i] = M[i * col + j];
    }
    delete[] M;
    M = traspose;
    // aggiorno il numero di righe e di colonne dopo l'operazione di trasposizione. Faccio uno swap attraverso una variabile temporanea.
    int n_rows= rows;
    rows=col;
    col=n_rows;
    return *this;


}

template<typename T>
Matrix<T> Matrix<T>::select_column(int column) throw(out_of_range){
    if (column<0 || column >= col)
        throw out_of_range ("col index error");

    Matrix <T> mc(rows,1);
    for (int i= 0; i < rows; i++)
        mc.M[i] = M[i*rows+column];
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
T Matrix<T>::getValue(int row, int column)throw(out_of_range){
    if (row<0 || row >= rows || col<0 || column >= col)
        throw out_of_range ("index error");
    return M [row * col + column];
}

template<typename T>
void Matrix<T>::setValue(int row, int column, T value)throw (out_of_range){
    if (row<0 || row >= rows || col<0 || column >= col)
        throw out_of_range ("index error");
    M [row * col + column] = value;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &m1)throw(invalid_argument){
    if (this->rows != m1.rows || this->col != m1.col)
        throw invalid_argument ("size error");

    Matrix <T> sum(rows,col);
    for (int i=0; i< rows * col; i++)
        sum.M[i]= this->M[i]+ m1.M[i];

    return sum;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> &m1) throw (invalid_argument){ // implemento prodotto riga per colonna
    if (col != m1.rows)
        throw invalid_argument ("size error for product");

    Matrix <T> prod(rows,m1.col);
    for(int i=0; i<rows; i++)
        for (int j=0; j<m1.col; j++)
            for (int k=0; k< col; ++k)
                prod.M[i* m1.col+j] += M[i*col+k] * m1.M[k* m1.col+j];
    return prod;
}

template<typename T>
Matrix<T> Matrix<T>::Gauss() const throw (invalid_argument){ // implementazione algoritmo gauss senza pivoting per
    //ridurre la matrice in una triangolare superiore.

    if (rows !=col)
        throw invalid_argument("matrix must be square"); // la matrice triangolare è una matrice quadrata.

    Matrix<T> reduced(*this);
    float m=0;

    for (int k=0; k<rows-1; k++) {
        if (reduced.M[k * col + k] == 0)
            throw invalid_argument("value is zero");

        for (int i = k + 1; i < rows; i++) {
            m = reduced.M[i * col + k] / reduced.M[k * col + k];
            for (int j = k + 1; j < rows; j++)
                reduced.M[i * col + j] = reduced.M[i * col + j] - m * reduced.M[k * col + j];

            reduced.M[i * col + k] = 0;
        }
    }
    return reduced;
}

template<typename T>
Matrix<T>::Matrix(int rows,int col, const vector<T>& v) throw(invalid_argument): rows(rows), col(col){
    if (rows <= 0 || col <=0)
        throw invalid_argument("invalid rows and cols");
    M = new T [rows * col];

    if (v.size() != rows*col)
        throw invalid_argument(" Matrix size is different to vector size");

    for (int i =0; i<rows*col; i++)
        M[i]= v[i];
}

template<typename T>
Matrix<T>::Matrix(int size, const vector<T> &v) throw(invalid_argument): rows(size), col(size){
    if (rows <= 0 || col <=0)
        throw invalid_argument("invalid size of rows and cols");
    M = new T[rows*col];

    if (v.size() != rows * col)
        throw invalid_argument(" Matrix size is different to vector size");

    for (int i = 0; i<rows*col; i++)
            M[i] = v[i];
    }


template<typename T>
int Matrix<T>::rank() const {

    int rank = col; // variabile per memorizzare il rango. Inizializzo al numero totale delle colonne
    Matrix<T> M_rank(*this);
    float m=0;

    for (int k=0; k< rank;k++){
        if (M_rank.M[k*col+k] !=0){
            for (int i=k+1;i<rows; i++){
                m = M_rank.M[i*col+k]/ M_rank.M [k*col+k]; // calcolo coefficiente m
                for (int j=k+1; j<rows; j++)
                    M_rank.M[i*col+j]=M_rank.M[i*col+j] - m * M_rank.M[k*col+j];
                M_rank.M[i*col+k]=0; // metto a 0 l'elemento sotto il primo pivot
            }
        }
        else{ // if ()==0. Se l'elemento 00 è 0 allora scambio la prima riga con quella sotto.
            bool reduced = true; // variabile che mi indica se posso ridurre oppure no
            for (int i=k+1;i<rows;i++){ //Ciclo per scambiare le righe
                if (M_rank.M[i*col+k]!=0){
                    for(int j=0; j<rank;j++){ // scambio tutti i valori della riga con quelli della riga sotto.
                        T temp= M_rank.M[k*col+j];
                        M_rank.M[k*col+j]= M_rank.M[i*col+j];
                        M_rank.M[i*col+j]=temp;
                    }
                    reduced = false; // non è stata ridotta. Ho solo scambiato le righe
                }
            }
            if(reduced){
                rank--;
                for (int i=0; i<rows; i++)
                    M_rank.M[i*col+k]=M_rank.M[i*col+rank];
            }
            k--;
        }
    }
    return rank;
}

template<typename T>
T Matrix<T>::det() const throw(invalid_argument) {
   if (rows!=col)
       throw invalid_argument ("Matrix must be square");
   Matrix <T> m = Gauss();
   T det = 1; //varabile per mem il det inizializzato a 1.
    for (int i=0; i<rows; i++){
        det *= m.getValue(i,i);
    }
    return det;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T value) {
    Matrix <T> prod(rows,col);
    for(int i=0; i<rows*col; i++)
            prod.M[i] = M[i] * value;
    return prod;

}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> &m1) const {
    if (this->rows != m1.rows || this->col != m1.col)
        return false;
    for (int i = 0; i < rows*col ; i++)
        if (this->M[i] != m1.M[i])
            return false;

    return true;
    }

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &m1) {

    this ->rows = m1.rows;
    this ->col  = m1.col;

    delete[] M;
    M = new T[rows*col];
    for (int i = 0; i < rows; i++)
        M[i] = m1.M[i];

    return *this;
}

template<typename T>
bool Matrix<T>::operator !=(const Matrix<T> &m1) const {
    if (this->rows != m1.rows || this->col != m1.col)
        return true;
    for (int i = 0; i < rows*col ; i++)
        if (this->M[i] != m1.M[i])
            return true;

    return false;
}


#endif //MATRIXTEMPLATE_MATRIX_H
