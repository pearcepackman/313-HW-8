#include <iostream>
#include <vector>

class Matrix {
    public:
        //Attributes, sizex and sizey along with vector with data
        int sizex, sizey;
        std::vector<std::vector<double> > data;
    
        //Constructor, setting up matrix
        Matrix(int x, int y, const std::vector<double>& values) {
            sizex = x;
            sizey = y;
            //If values don't fit, throw an error, just a little extra precaution
            if (values.size() != x * y){
                std::cerr << "ERROR";
                exit(1);
            }
            //Resizing data to fit in the Matrix
            data.resize(x, std::vector<double>(y));
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) { //Double loops very common in this
                    data[i][j] = values[i * y + j];
                }
            }
        }
        //Matrix Addition method, supposed to add two matrices together
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
    //Scalar multiplication
    Matrix scalar_multiply(double scalar) {
        std::vector<double> newValues;
        for (int i = 0; i < sizex; i++) { //Another double loop, multiplying every piece by scalar
            for (int j = 0; j < sizey; j++) {
                newValues.push_back(this->data[i][j] * scalar);
            }
        }//Return matrix with newvalues multiplied with scalar
        return Matrix(sizex, sizey, newValues);
    }
    //Transpose function
    Matrix transpose() {
        std::vector<double> newValues;
        for (int i = 0; i < sizey; i++){
            for (int j = 0; j < sizex; j++){ //Double loop setting rows to columns and vice versa
                newValues.push_back(this->data[j][i]);
            }
        }//Return new matrix with rows and columns switched
        return Matrix(sizey, sizex, newValues);
    }
    // Matrix multiplication, done basically the same as above
    Matrix operator*(const Matrix& other) {
        if (this->sizey != other.sizex) {
            //Will throw if dimensions cannot have multiplication done on them
            std::cerr << "ERROR: Dimensions are not correct";
        }
        //Initializes a matrix with sizes and new vector data
        Matrix result(this->sizex, other.sizey, std::vector<double>(this->sizex * other.sizey, 0));

        for (int i = 0; i < this->sizex; ++i) {
            for (int j = 0; j < other.sizey; ++j) {
                for (int k = 0; k < this->sizey; ++k) {//Loop multiplying all of the data together to fill new matrix
                    result.data[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }
        //Return that new matrix we initialized above
        return result;
    }
   
        //Readout method, basically just displaying size and data foudn within
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
    //Init matrix A here
    Matrix a(2, 2, avalues);
    
    std::vector<double> bvalues;
    bvalues.push_back(1);
    bvalues.push_back(2);
    bvalues.push_back(3);
    bvalues.push_back(4);
    bvalues.push_back(5);
    bvalues.push_back(6);
    //Init matrix B here
    Matrix b(2, 3, bvalues);
    
    std::vector<double> cvalues;
    cvalues.push_back(2);
    cvalues.push_back(4);
    cvalues.push_back(6);
    cvalues.push_back(1);
    cvalues.push_back(3);
    cvalues.push_back(5);
    //Init matrix C here
    Matrix c(2, 3, cvalues);


    //Transpose C
    Matrix ctranspose = c.transpose();
    //Scalar multiply b by 3
    Matrix threeb = b.scalar_multiply(3);
    //Multiply the last two matrices together
    Matrix threebtimesct = threeb * ctranspose;
    //Finally, add them together
    Matrix d = a + threebtimesct;
    std::cout << "\nMatrix D: ";
    d.readout(); //Readout the final matrix


    return 0;
}