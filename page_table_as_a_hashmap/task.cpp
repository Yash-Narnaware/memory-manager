#include<string>
#include<vector>

class Page_table_entry {
public:
    std::string logicalAddress;
    std::string physicalAddress;    

};


class task {

private:
    std::string taskName;
    std::vector<Page_table_entry> page_table_as_map;
    int task_size;
    int total_number_of_page_entries;
    int hit;
    int miss;

public:

    // Constructor
    task(const std::string& name) : taskName(name), task_size(0) {
        // page_table_as_map.push_back(page_table);
        total_number_of_page_entries = 0;
        hit = 0;
        miss = 0;

    }

    // Get the task name
    std::string getTaskName() const {
        return taskName;
    }

    //get page table
    std::vector<Page_table_entry> getpagetable(){
        return page_table_as_map;
    }

    int get_total_number_of_page_entries(){
        return total_number_of_page_entries;
    }

    void update_total_number_of_page_entries(int i){
        total_number_of_page_entries = total_number_of_page_entries + i;
    }

    //add entry to page table
    void add_entry_to_page_table(Page_table_entry entry) {
        page_table_as_map.push_back(entry);

    }

    void increase_hit(){
        hit = hit + 1;
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
