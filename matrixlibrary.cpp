#include <iostream>
#include <vector>

class Matrix {
    public:
        //Attributes
        int sizex, sizey;
        std::vector<std::vector<double> > data;
    
        //Constructor
        Matrix(int x, int y, const std::vector<double>& values) {
            sizex = x;
            sizey = y;
            //If values don't fit, throw an error
            if (values.size() != x * y){
                std::cerr << "ERROR";
                exit(1);
            }
            //Resizing data to fit in the Matrix
            data.resize(x, std::vector<double>(y));
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                    data[i][j] = values[i * y + j];
                }
            }
        }
        //Matrix Addition method
        Matrix operator+(const Matrix& other) {
            //If the sizes are not compatible, cannot do math
            if (this->sizex != other.sizex || this->sizey != other.sizey){
                std::cerr << "ERROR: Dimensons don't match";
                exit(1);
                //Stops program if incompatable
            }
        //Creating vector of new values to fill in the new matrix
        std::vector<double> newValues;
            for (int i = 0; i < sizex; ++i) {
                for (int j = 0; j < sizey; ++j) {
                    //Pushing values back to fill the new vector
                    newValues.push_back(this->data[i][j] + other.data[i][j]);
                }
            }
        //Return a new matrix with the new values
        return Matrix(sizex, sizey, newValues);
    }

    // Matrix multiplication, done basically the same as above
    Matrix operator*(const Matrix& other) {
        if (this->sizey != other.sizex) {
            //Will throw if dimensions cannot have multiplication done on them
            std::cerr << "ERROR: Dimensions are not correct";
        }

        Matrix result(this->sizex, other.sizey, std::vector<double>(this->sizex * other.sizey, 0));

        for (int i = 0; i < this->sizex; ++i) {
            for (int j = 0; j < other.sizey; ++j) {
                for (int k = 0; k < this->sizey; ++k) {
                    result.data[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }
   
        //Method
        void readout() {
            std::cout<< "Matrix is " << sizex << " rows by " << sizey << " columns\n";
            for(int i = 0; i < data.size(); i++) {
                for (int j = 0; j < data[i].size(); j++) {
                    std::cout << data[i][j] << " ";
                }
                std::cout << "\n";
            }
        }

};

int main() {
    //Was having issues declaring vectors so I had to push them back individually
    std::vector<double> avalues;
    avalues.push_back(6);
    avalues.push_back(4);
    avalues.push_back(8);
    avalues.push_back(3);
    
    Matrix a(2, 2, avalues);
    a.readout();

    std::vector<double> bvalues;
    bvalues.push_back(1);
    bvalues.push_back(2);
    bvalues.push_back(3);
    bvalues.push_back(4);
    bvalues.push_back(5);
    bvalues.push_back(6);

    Matrix b(2, 3, bvalues);
    b.readout();

    std::vector<double> cvalues;
    cvalues.push_back(2);
    cvalues.push_back(4);
    cvalues.push_back(6);
    cvalues.push_back(1);
    cvalues.push_back(3);
    cvalues.push_back(5);

    Matrix c(2, 3, cvalues);
    c.readout();

    Matrix sum = b + c;
    Matrix mult = a * b;
    sum.readout();
    mult.readout();
    return 0;
}