#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const char * FOUT_NAME = "reverse.dat";

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cout << "Usage: reverse.exe path/to/file/filename" << endl;
        exit(1);
    }

    ifstream ifs(argv[1]);
    ofstream ofs(FOUT_NAME);

    if (!ifs) {
        cout << "Error: Can't open input file - " << argv[1] << endl;
        exit(1);
    }
    
    if (!ofs) {
        cout << "Error: Can't open output file - " << FOUT_NAME << endl;
        exit(1);
    }

    string dType;
    size_t dSize;
    while (ifs.good()) {
        ifs >> dType >> dSize;
        ofs << left << setw(4) << dType << '\t' <<  dSize << '\t';

        if (dType == "int") {
            int * iPtr = new int[dSize];
            for ( size_t i = 0; i < dSize; ++i )
                ifs >> iPtr[i];
            for ( size_t i = 0; i < dSize; ++i )
                ofs << iPtr[dSize-i-1] <<  " ";
            delete[] iPtr;
        } else if (dType == "float") {
            float * fPtr = new float[dSize];
            for ( size_t i = 0; i < dSize; ++i )
                ifs >> fPtr[i];
            for ( size_t i = 0; i < dSize; ++i )
                ofs << fPtr[dSize-i-1] <<  " ";
            delete[] fPtr;
        }  else if (dType == "char") {
            char * cPtr = new char[dSize];
            for ( size_t i = 0; i < dSize; ++i )
                ifs >> cPtr[i];
            for ( size_t i = 0; i < dSize; ++i )
                ofs << cPtr[dSize-i-1] <<  " ";
            delete[] cPtr;
        } else {
            cout << "Error: " << dType << " record type isn't supported" << endl;
            exit(1);
        }
        
        ofs << endl;
    }
    return 0;

}
