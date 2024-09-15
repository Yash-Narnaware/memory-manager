#include "config.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <pthread.h>

using namespace std;

// Struct to hold task traces
struct Trace {
    string task_name;
    size_t logical_address;
    size_t task_size;
};

// Struct to pass multiple arguments to threads
struct ThreadArgs {
    int task_id;
    int trace_count;
    vector<Trace>* traces;
};

// Mutex for synchronizing access to the shared vector
pthread_mutex_t trace_mutex;

// Function to generate a random aligned address
size_t generateAlignedAddress() {
    size_t min_address = PAGE_SIZE;  // Start from PAGE_SIZE (e.g., 0x1000)
    size_t max_address = VIRTUAL_MEMORY_SIZE - PAGE_SIZE;  // Maximum possible address
    size_t address;

    // Generate a random non-zero aligned address
    do {
        address = ((rand() % ((max_address - min_address) / PAGE_SIZE)) + 1) * PAGE_SIZE + min_address;
    } while (address == 0);  // Redundant safety check to avoid zero

    return address;
}

// Function to generate a random task size aligned to the page size
size_t generateTaskSize() {
    size_t min_size_kb = 1; // Minimum size in KB
    size_t max_size_kb = 10; // Maximum size in KB
    size_t task_size_kb = (rand() % (max_size_kb - min_size_kb + 1)) + min_size_kb;
    return task_size_kb * PAGE_SIZE;
}

// Thread function to generate traces for a task
void* generateTaskTraces(void* args) {
    ThreadArgs* taskArgs = (ThreadArgs*)args;
    int task_id = taskArgs->task_id;
    int trace_count = taskArgs->trace_count;
    vector<Trace>* traces = taskArgs->traces;

    for (int j = 0; j < trace_count; j++) {
        size_t logical_address = generateAlignedAddress();  // Ensure valid non-zero address
        size_t task_size = generateTaskSize();
        string task_name = "T" + to_string(task_id + 1);
        Trace trace = {task_name, logical_address, task_size};

        // Lock the mutex before modifying the shared vector
        pthread_mutex_lock(&trace_mutex);
        traces->push_back(trace);
        pthread_mutex_unlock(&trace_mutex);
    }

    return nullptr;
}

// Function to generate traces for tasks using multiple threads
void generateTraces(const vector<int>& Traces, int task_count, const string& filename) {
    srand(time(0));

    vector<Trace> traces;
    pthread_t threads[task_count];
    ThreadArgs threadArgs[task_count];

    pthread_mutex_init(&trace_mutex, nullptr);

    // Create threads for each task
    for (int i = 0; i < task_count; i++) {
        threadArgs[i].task_id = i;
        threadArgs[i].trace_count = Traces[i];
        threadArgs[i].traces = &traces;

        pthread_create(&threads[i], nullptr, generateTaskTraces, (void*)&threadArgs[i]);
    }

    // Join all threads
    for (int i = 0; i < task_count; i++) {
        pthread_join(threads[i], nullptr);
    }

    pthread_mutex_destroy(&trace_mutex);

    // Shuffle the traces to randomize their order
    random_shuffle(traces.begin(), traces.end());

    // Output the shuffled traces to a file
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    for (const auto& trace : traces) {
        outfile << trace.task_name << ": 0x" << hex << setw(8) << setfill('0') << trace.logical_address << ": " << dec << trace.task_size / 1024 << "KB" << endl;
    }

    outfile.close();
}

int main() {
    int task_count;
    cout << "Enter the number of tasks you want to have: ";
    cin >> task_count;

    vector<int> Traces;
    int traces;
    cout<<"Enter total no of traces you want too have:";
    cin>>traces;

    for (int i = 0; i < task_count; i++) {
        Traces.push_back(traces/task_count);
        cout << "The number of traces for T" << i + 1<<" is:"<<traces/task_count<<endl;
    }

    // Generate and print the traces using threads
    generateTraces(Traces, task_count, "tracefiles/generated_traces.txt");

    return 0;
}
