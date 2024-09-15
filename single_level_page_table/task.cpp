#include<string>
#include<vector>


class task {

private:
    std::string taskName;
    std::vector<std::string> single_level_page_table; // page table with 2^20 entries
    int task_size;
    int total_number_of_page_entries;
    int hit;
    int miss;

public:


    // Constructor
    task(const std::string& name) : 
        taskName(name), 
        single_level_page_table(1 << 20), // Initialize vector with 2^20 elements
        task_size(0), 
        total_number_of_page_entries(0), 
        hit(0), 
        miss(0) 
    {
        std::fill(single_level_page_table.begin(), single_level_page_table.end(), "");
    }

    // Get the task name
    std::string getTaskName() const {
        return taskName;
    }

    //get page table
    std::vector<std::string> getpagetable(){
        return single_level_page_table;
    }

    int get_total_number_of_page_entries(){
        return total_number_of_page_entries;
    }

    void update_total_number_of_page_entries(int i){
        total_number_of_page_entries = total_number_of_page_entries + i;
    }

    //add entry to page table
    void add_entry_to_page_table(std::string physical_address, int page_idx) {

        single_level_page_table[page_idx] = physical_address;

    }

    void increase_hit(){
        hit = hit+1;
    }

    void increase_miss(){
        miss = miss + 1;
    }

    void update_task_size(int bnm) {
        task_size = task_size + bnm; 
    }

    std::string get_taskname(){
        return taskName;
    }

    int get_task_size(){
        return task_size;
    }

    int get_hit(){
        return hit;
    }

    int get_miss(){
        return miss;
    }

    int get_total_page_entries(){
        return total_number_of_page_entries;
    }

};
