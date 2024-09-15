#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "memoryManager.cpp"
#include "../config.h"
#include <chrono>
#include <set>
#include <math.h>

using namespace std;

int main() {
    ifstream testcase_file("testcases.txt");  // Input file containing the test cases
    ofstream output_file("output.txt");       // Output file to store the results

    if (!testcase_file.is_open()) {
        cout << "Failed to open testcases.txt" << endl;
        return 1;
    }

    if (!output_file.is_open()) {
        cout << "Failed to open output.txt" << endl;
        return 1;
    }

    string line;
    MemoryManager memory_manager(MEMORY_SIZE); //8GB

    //start time
    auto start = chrono::high_resolution_clock::now();

    while (getline(testcase_file, line)) {
        istringstream iss(line);
        string command;
        iss >> command;

        if (command[0] == 'T') {
            // Commands like T1 0x03083400 4KB or T3 0x03083600 1MB
            string task_name = command;
            cout << "\nTask name:" << task_name << endl;
            string logical_addr;
            
            string size_str;
            
            size_t task_size;
            iss >> logical_addr >> size_str;

            // Convert the task size to bytes (handling both KB and MB inputs)
            if (size_str.back() == 'B') size_str.pop_back();  // Remove 'B'
            if (size_str.back() == 'K') {
                size_str.pop_back();  // Remove 'K'
                task_size = stoull(size_str);  // Size is in KB
                cout << "Task_size:" << task_size << endl;
            } else if (size_str.back() == 'M') {
                size_str.pop_back();  // Remove 'M'
                task_size = stoull(size_str) * 1024;  // Convert MB to KB
                cout << "Task_size(MB):" << task_size << endl;
            }

            memory_manager.allocateMemory(task_size * 1024, task_name, logical_addr);  // Convert to bytes

            task_size = ((task_size*1024)/PAGE_SIZE) *PAGE_SIZE;

            if (((task_size*1024)%PAGE_SIZE) != 0){
                task_size = (task_size + PAGE_SIZE)/1024;
            } else {
                task_size = (task_size)/1024;

            }

            output_file << "Task " << task_name << " allocated with " << task_size << "KB" << "\n";
        
        } else if (command == "STATUS") {
            output_file << "Total occupied memory: " << memory_manager.total_occupied_memory / 1024 << "KB\n";
            output_file << "Hits: " << memory_manager.hit_counter << "\n";
            output_file << "Misses: " << memory_manager.miss_counter << "\n";
        }
    }

    // End time
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;

    testcase_file.close();
    output_file.close();
    cout << endl;
    memory_manager.get_taskvise_summary();  


    cout << "Total time taken(in seconds): " << duration.count() << endl;
    cout << "Total Hits:" << memory_manager.hit_counter << endl;
    cout << "Total Miss:" << memory_manager.miss_counter << endl;
    cout << "Total memory occupied:" << memory_manager.total_occupied_memory << " bytes" << endl;
    cout << "Total free memory: " << MEMORY_SIZE - memory_manager.total_occupied_memory << " bytes" << endl;

    return 0;
}
