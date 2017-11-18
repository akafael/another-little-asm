/**
 * Linker
 *
 * @authors Rafael Lima, João Paulo Franch , Túlio
 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#include "msgs_pt.h"

typedef struct{
    int startAddr;
    int size;
} men_chunk;

using namespace std;

int main(int argc, char** argv)
{
    if (argc< 2)
    {
        cout << MSG_ERR;
        return 1;
    }
    else if (argc == 3)
    {
        ifstream InputFILE(argv[1]); // input;
        ofstream OutputFILE(argv[2]); // output;

        // Teste se ambos os aquivos foram abertos corretamente;
        if (!(InputFILE.is_open() && OutputFILE.is_open()))
        {
            cerr << MSG_ERR_FILE;
            return 1;
        }

        string line;
        for(int lineCount = 0 ;getline(InputFILE,line);lineCount++)
        {
            OutputFILE << line << endl;
        }

        InputFILE.close();
        OutputFILE.close();
    }

    return 0;
}
