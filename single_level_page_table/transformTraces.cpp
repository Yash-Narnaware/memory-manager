#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../config.h"

using namespace std;

void transformData(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);
    string line;

    if (!inputFile) {
        cerr << "Error opening input file." << endl;
        return;
    }

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string label, address, sizeStr;
        getline(ss, label, ':');
        getline(ss, address, ':');
        getline(ss, sizeStr);

        // int size = stoi(sizeStr.substr(0, sizeStr.find("KB"))) / 2;
        int size = stoi(sizeStr.substr(0, sizeStr.find("KB")));

        // Write the transformed line
        outputFile << label << " " << address << " " << size << "KB" << endl;

        // Write the STATUS line
        outputFile << "STATUS" << endl;
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    string inputFileName = FILENAME;
    //string inputFileName = "../tracefiles/generated_traces.txt";
    string outputFileName = "testcases.txt";
    
    transformData(inputFileName, outputFileName);
    
    cout << "Transformation complete. Check the testcases.txt file." << endl;
    
    return 0;
}
