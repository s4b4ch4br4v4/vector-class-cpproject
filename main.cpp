#include <iostream>
#include <cassert>
#include <cmath>
#include <fstream>
#include <cstring>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class Vector{
    private:
        unsigned int Dimension;
        double* myvector;

    public:
        // CONSTRUCTOR:

        Vector(unsigned int Dimension = 1){
            SetD(Dimension);
            myvector = new double[Dimension];
        }

        // SETTERS:

        void SetD(unsigned int Dimension = 1){
            assert(Dimension != 0);
            this->Dimension = Dimension;
        }

        void SetElement(unsigned int i, double value){
            myvector[i] = value;
        }

        // GETTERS:

        unsigned int GetD(){return Dimension;}
        double* GetV(){return myvector;}

        // OPERATOR OVERLOADING:

        Vector operator+(Vector& othervector){
            assert(GetD() == othervector.GetD());
            Vector sum(GetD());
            for(int i = 0; i < GetD(); ++i){
                sum.SetElement(i, GetV()[i] + othervector.GetV()[i]);
            }
            return sum;
        }

        Vector operator-(Vector& othervector){
            assert(GetD() == othervector.GetD());
            Vector sub(GetD());
            for(int i = 0; i < GetD(); ++i){
                sub.SetElement(i, GetV()[i] - othervector.GetV()[i]);
            }
            return sub;
        }

        double operator*(Vector& othervector){
            assert(GetD() == othervector.GetD());
            double scalarproduct;
            for(int i = 0; i < GetD(); ++i){
                scalarproduct += GetV()[i] * othervector.GetV()[i];
            }
            return scalarproduct;
        }
};

// VECTOR FUNCTIONS:

Vector CinDimension(){
    unsigned int i = 0;
    cout<<"Input dimension of your vector: "; cin>>i;
    return Vector(i);
}

Vector CinElements(Vector myvector){
    cout<<"Input elements: "<<endl;
    for(int i = 0; i < myvector.GetD(); ++i){
        double value;
        cout<<"V["<<i+1<<"] = "; cin>>value;
        myvector.SetElement(i, value);
    }
    return myvector;
}

void CoutElements(Vector myvector){
    cout<<"["<<myvector.GetD()<<"] = { ";
    for(int i = 0; i < myvector.GetD(); ++i){
        cout<<myvector.GetV()[i]<<"; ";
    }
    cout<<"}"<<endl;
}

// VECTOR ALGEBRA:

Vector Sum(Vector addend1, Vector addend2){
    if(addend1.GetD() != addend2.GetD()){
        assert(addend1.GetD() != addend2.GetD());
    } else {
        Vector sum(addend1.GetD());
        for(int i = 0; i < addend1.GetD(); ++i){
            sum.GetV()[i] = addend1.GetV()[i] + addend2.GetV()[i];
        }
        return sum;
    }
}

Vector Sub(Vector saklebi, Vector maklebi){
    if(saklebi.GetD() != maklebi.GetD()){
        assert(saklebi.GetD() != maklebi.GetD());
    } else {
        Vector sub(saklebi.GetD());
        for(int i = 0; i < saklebi.GetD(); ++i){
            sub.GetV()[i] = saklebi.GetV()[i] - maklebi.GetV()[i];
        }
        return sub;
    }
}

double ScalarProduct(Vector v1, Vector v2){
    if(v1.GetD() != v2.GetD()){
        assert(v1.GetD() != v2.GetD());
    } else {
        double scalarproduct = 0;
        for(int i = 0; i < v1.GetD(); ++i){
            scalarproduct += v1.GetV()[i] * v1.GetV()[i];
        }
        return scalarproduct;
    }
}

double DecLength(Vector myvector){
    double declength = 0;
    for(int i = 0; i < myvector.GetD(); ++i){
        declength += myvector.GetV()[i] * myvector.GetV()[i];
    }
    return sqrt(declength);
}

// BIGGEST AND SMALLEST:

unsigned int BiggestElement(Vector myvector){
    unsigned int I = 0;
    for(int i = 1; i < myvector.GetD(); ++i){
        if(myvector.GetV()[I] < myvector.GetV()[i]){
            I = i;
        }
    }
    return I;
}

unsigned int SmallestElement(Vector myvector){
    unsigned int I = 0;
    for(int i = 1; i < myvector.GetD(); ++i){
        if(myvector.GetV()[I] > myvector.GetV()[i]){
            I = i;
        }
    }
    return I;
}

// CONSOLE OUT:

void ConsoleOut(Vector myvector1, Vector myvector2){
    system("cls");

    cout<<"V1"; CoutElements(myvector1); cout<<endl;
    cout<<"V2"; CoutElements(myvector2); cout<<endl<<endl;

    cout<<"V1 biggest n smallest elements: ";
    cout<<myvector1.GetV()[BiggestElement(myvector1)]<<" & "<<myvector1.GetV()[SmallestElement(myvector1)];
    cout<<endl;
    cout<<"V2 biggest n smallest elements: ";
    cout<<myvector2.GetV()[BiggestElement(myvector2)]<<" & "<<myvector2.GetV()[SmallestElement(myvector2)];
    cout<<endl<<endl;

    cout<<"V1 + V2 = V3"<<endl;
    cout<<"V3"; CoutElements(Sum(myvector1, myvector2));
    cout<<endl;
    cout<<"V1 - V2 = V4"<<endl;
    cout<<"V4"; CoutElements(Sub(myvector1, myvector2));
    cout<<endl<<endl;

    cout<<"Scalar product of V1 & V2 = "<<ScalarProduct(myvector1, myvector2)<<endl<<endl;

    cout<<"V1 Descartes length = "<<DecLength(myvector1)<<endl;
    cout<<"V2 Descartes length = "<<DecLength(myvector2)<<endl<<endl;
}

// ABOUT FILES:

ofstream CreateFile(string filename){
    ofstream myfile(filename);
    return myfile;
}

bool FileExists(string filename){
    fs::path myfile{filename};
    return exists(myfile);
}

void VectorToFile(ofstream myfile, Vector myvector){
    if(myfile.is_open()){
        for(int i = 0; i < myvector.GetD(); ++i){
            myfile<<myvector.GetV()[i]<<endl;
        }
        myfile.close();
    }
}

void ReadFromFile1(string filename){
    ifstream myfile(filename);
    string values;
    if(myfile.is_open()){
        while(getline(myfile, values)){
        cout<<values;
        }
        myfile.close();
    } else {
        cout<<-1;
    }
}

void ReadFromFile2(string filename, Vector myvector){
    ifstream myfile(filename);
    string value;
    if(myfile.is_open()){
        for(int i = 0; i < myvector.GetD(); ++i){
            getline(myfile, value);
            myvector.SetElement(i, stod(value));
        }
        myfile.close();
    }
}

unsigned int LineCounter(string filename){
    if(FileExists(filename)){
        ifstream myfile(filename);
        string line;
        unsigned int counter = 0;
        if(myfile.is_open()){
            while(getline(myfile, line)){
                if(line.length() == 0){
                    continue;
                } else {
                    counter++;
                }
            }
        myfile.close();
        return counter;
        } else {
            return -1;
        }
    }
}

ofstream operator<<(string filename, Vector myvector){
    ofstream myfile(filename);
    for(int i = 0; i < myvector.GetD(); ++i){
            myfile<<myvector.GetV()[i]<<endl;
    }
    return myfile;
}

void operator>>(string filename, Vector myvector){
    if(FileExists(filename)){
        ifstream myfile(filename);
        string value;
        unsigned int lines = LineCounter(filename);
        if(lines == 0){
            assert(lines > 0);
        } else if (myfile.is_open()){
            for(int i = 0; i < lines; ++i){
                getline(myfile, value);
                if(value.length() == 0){
                    continue;
                } else {
                    myvector.SetElement(i, stod(value));
                }
                // myfile.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        myfile.close();
    }
}


int main(int argc, char* argv[]){

    string filename1 = "myvector1.txt", filename2 = "myvector2.txt";
    //cout<<"Input file name & extension: "; cin>>filename1;
    //cout<<"Input file name & extension: "; cin>>filename2;

    Vector x(LineCounter(filename1));
    Vector y(LineCounter(filename2));

    filename1>>x;
    filename2>>y;

    CoutElements(x);
    CoutElements(y);
}
