#include<string>
#include<vector>

struct page_indices {
    int outer_index;
    int inner_index;
};

class page_table_class {

public:

    std::vector<std::string> page_table;

    page_table_class() : 
        page_table(1024)
    {
        std::fill(page_table.begin(), page_table.end(), "");
    } 

};


class task {

private:
    std::string taskName;
    std::vector<page_table_class*> second_level_page_table; // page table with 2^20 entries
    int task_size;
    int total_number_of_page_entries;
    int hit;
    int miss;

public:

     // Constructor
    task(const std::string& name) : 
        taskName(name), 
        second_level_page_table(1024), // Initialize vector with 2^20 elements
        task_size(0), 
        total_number_of_page_entries(0), 
        hit(0), 
        miss(0) 
    {
        std::fill(second_level_page_table.begin(), second_level_page_table.end(), nullptr);
    }

    // Get the task name
    std::string getTaskName() const {
        return taskName;
    }

    //get page table
    std::vector<page_table_class*> getpagetable(){
        return second_level_page_table;
    }

    void set_new_page_table(int outer_idx){
        second_level_page_table[outer_idx] = new page_table_class();
    }

    int get_total_number_of_page_entries(){
        return total_number_of_page_entries;
    }

    void update_total_number_of_page_entries(int i){
        total_number_of_page_entries = total_number_of_page_entries + i;
    }

    //add entry to page table
    void add_entry_to_page_table(std::string physical_address, int outer_page_idx, int inner_page_idx) {

        second_level_page_table[outer_page_idx]->page_table[inner_page_idx] = physical_address;

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

