#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <set>
#include "../config.h"
#include "task.cpp"

class MemoryBlock {
public:
    task* task1;
    size_t startAddress;
    size_t size;
    bool isOccupied;           
    MemoryBlock* prev;
    MemoryBlock* next;

    MemoryBlock(size_t startAddress, size_t size, bool isOccupied)
        : task1(nullptr), startAddress(startAddress), size(size), isOccupied(isOccupied), prev(nullptr), next(nullptr) {}
};


class MemoryManager {
private:
    MemoryBlock* head;         // Head of the doubly linked list of memory blocks
    float page_size = PAGE_SIZE;

public:
    MemoryManager(size_t totalMemorySize) {
        head = new MemoryBlock(0, totalMemorySize, false);  // Initialize the single large free block
        head->task1 = new task("RAM");  
    }

    size_t total_occupied_memory = 0;
    int hit_counter = 0;
    int miss_counter = 0;

    MemoryBlock* get_head(){
        return head;
    }

    task* search_task_in_memory(std::string target) {

        MemoryBlock* current = head;

        while (current != nullptr){
            if (current->task1->getTaskName() == target){
                return current->task1;
            }
            current = current->next;
        }

        return nullptr;

    }

    int hex_to_dec(std::string la){

        return std::stoi(la, nullptr, 16);

    }

    bool search_la_in_page(task* task1, std::string target) {

        std::vector<Page_table_entry> temp2 = task1->getpagetable();

        for (int i = 0; i < temp2.size(); i++){
                if (hex_to_dec(temp2[i].logicalAddress) == hex_to_dec(target)){
                    return true;
                }
        }
        return false;
    }

    std::string assign_phy_addr(task* task1,size_t requestedSize) {

        MemoryBlock* current = head;

        // Find the first free block that is large enough
        while (current != nullptr) {
            if (!current->isOccupied && current->size >= requestedSize) {
                // Split the block if it's larger than the requested size
                size_t return_addr;
                std::cout << "Requested size:" << requestedSize << std::endl;
                if (current->size > requestedSize) {
                    MemoryBlock* newBlock = new MemoryBlock(current->startAddress,
                                                            requestedSize, true);
                    newBlock->task1 = task1;
                    newBlock->prev = current->prev;
                    newBlock->next = current;

                    if (current->prev != nullptr) {
                        current->prev->next = newBlock;
                    }else {
                        head = newBlock;
                    }

                    current->prev = newBlock;
                    current->startAddress = current->startAddress + requestedSize;
                    current->size = current->size - requestedSize; 
                    return_addr = newBlock->startAddress;
   
                } else {
                    current->task1 = task1;
                    current->isOccupied = true;
                    return_addr = current->startAddress;
                }

                std::stringstream ss;
                ss << reinterpret_cast<void*>(return_addr);
                return ss.str();
            }
            current = current->next;
        }

        // No suitable block found
        return "";

    }

    std::string getNextHexAddress(const std::string& hexAddress, int increase_by) {

        int num_in_decimal;

        num_in_decimal = std::stoi(hexAddress, nullptr, 16);

        num_in_decimal = num_in_decimal + increase_by;

        std::stringstream ss;
        ss << std::hex << num_in_decimal;  // Convert decimal to hexadecimal

        std::string num_in_hex = ss.str();

        return num_in_hex;

    }

    void allocateMemory(size_t requestedSize, std::string taskName, std::string logical_addr1) {
        
        std::string logical_addr = logical_addr1.substr(2,5);
        task* temp = search_task_in_memory(taskName);
        int no_of_page_entries = ceil(requestedSize/page_size);
        
        if (temp != nullptr){
            for(int i=0;i<no_of_page_entries;i++){
                std::string target1 = getNextHexAddress(logical_addr,i); 
                if (search_la_in_page(temp,target1)) {
                    std::cout << "Hit!!!" << std::endl;
                    hit_counter = hit_counter + 1;
                    temp->increase_hit();
                } else {

                    std::cout << "Miss!!!" << std::endl;
                    miss_counter = miss_counter + 1;
                    temp->increase_miss();

                    Page_table_entry entry;
                    entry.logicalAddress = target1;
                    std::string phy_addr = assign_phy_addr(temp,page_size);

                    if (phy_addr != "") {
                        entry.physicalAddress = phy_addr;
                        temp->add_entry_to_page_table(entry);
                        temp->update_task_size(page_size);

                        total_occupied_memory = total_occupied_memory + page_size;
                        std::cout << "Memory allocation successfull at " << phy_addr << std::endl;
                        temp->update_total_number_of_page_entries(1);
                    } else {
                        std::cout << "Memory not available! :(" << std::endl;
                        return;
                    }

                }
            }
            return;


        }


        //int new_pages_required = ceil(no_of_page_entries/page_entries_limit) - 1; //this many extra pages required
        task* new_task = new task(taskName);
        //new_task->add_new_pages(new_pages_required);

        for(int i=0;i<no_of_page_entries;i++){
            std::string target1 = getNextHexAddress(logical_addr,i); 

            std::cout << "Miss!!!" << std::endl;
            miss_counter = miss_counter + 1;
            new_task->increase_miss();

            Page_table_entry entry;
            entry.logicalAddress = target1;
            std::string phy_addr = assign_phy_addr(new_task,page_size);

            if (phy_addr != "") {
                entry.physicalAddress = phy_addr;
                //int page_idx = new_task->get_total_number_of_page_entries()/page_entries_limit;
                new_task->add_entry_to_page_table(entry);
                new_task->update_task_size(page_size);

                total_occupied_memory = total_occupied_memory + page_size;
                std::cout << "Memory allocation successfull at " << phy_addr << std::endl;

                new_task->update_total_number_of_page_entries(1);
                  
            } else {
                std::cout << "Memory not available! :(" << std::endl;
                return;
            }
                     
        }
  
    }

    void deallocateMemory(void* address, size_t size) {
        size_t startAddress = reinterpret_cast<size_t>(address);
        MemoryBlock* current = head;

        // Find the block that matches the start address and size
        while (current != nullptr) {
            if (current->startAddress == startAddress && current->size == size && current->isOccupied) {
                break;
            }
            current = current->next;
        }

        if (current == nullptr) {
            // Block not found or already free
            return;
        }

        // Mark the block as free
        current->isOccupied = false;

        // Merge with the previous block if it's free
        if (current->prev != nullptr && !current->prev->isOccupied) {
            current->prev->size += current->size;
            current->prev->next = current->next;
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }
            delete current;
            current = current->prev;
        }

        // Merge with the next block if it's free
        if (current->next != nullptr && !current->next->isOccupied) {
            current->size += current->next->size;
            MemoryBlock* temp = current->next;
            current->next = temp->next;
            if (temp->next != nullptr) {
                temp->next->prev = current;
            }
            delete temp;
        }
    }

    void get_taskvise_summary(){

        MemoryBlock* temp = head;
        std::set<std::string> printedTasks;
    
        while (temp != nullptr){
            if (temp->isOccupied){

                if (printedTasks.find(temp->task1->getTaskName()) == printedTasks.end()) {

                    std::cout << "Task Name:" << temp->task1->getTaskName() << std::endl;
                    std::cout << "Task Size(KB):" << temp->task1->get_task_size()/1024 << std::endl;
                    std::cout << "Total Page Entries:" << temp->task1->get_total_number_of_page_entries() << std::endl;
                    std::cout << "Page Hit:" << temp->task1->get_hit() << std::endl;
                    std::cout << "Page Miss:" << temp->task1->get_miss() << std::endl;
                    std::cout <<std::endl;

                    printedTasks.insert(temp->task1->getTaskName());

                }    

            }
            temp = temp->next;
        }
    }


    ~MemoryManager() {
        MemoryBlock* current = head;

        while (current != nullptr) {
            MemoryBlock* next = current->next;
            delete current;
            current = next;
        }
    }
};
