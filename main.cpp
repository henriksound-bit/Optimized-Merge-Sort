/* This is a skeleton code for Optimized Merge Sort, you can make modifications as long as you meet 
   all question requirements*/  

#include <bits/stdc++.h>
#include "record_class.h"
#include <fstream>

using namespace std;

//defines how many blocks are available in the Main Memory 
#define buffer_size 22

Records buffers[buffer_size]; //use this class object of size 22 as your main memory

/**
 * Swaps two records
 * @param a first record
 * @param b second record
 */
void swap(Records &a, Records &b) {
    Records temp = a;
    a = b;
    b = temp;
}

//Sorting the buffers in main_memory and storing the sorted records into a temporary file (runs) 
void Sort_Buffer(Records buffers[], int number_of_records, string filename){

    fstream runs;
    runs.open(filename, ios::out | ios::app);
    if (number_of_records == 0) {
        return;
    }
    // Sorting the records in the buffer
    for (int i = 0; i < number_of_records; i++) {
        for (int j = i + 1; j < number_of_records; j++) {

            if (buffers[i].number_of_emp_records != 0 && buffers[j].number_of_emp_records != 0) {
                // Sorting by eid
                if (buffers[i].emp_record.eid > buffers[j].emp_record.eid) {
                    swap(buffers[i], buffers[j]);
                }
            } else if (buffers[i].number_of_dept_records != 0 && buffers[j].number_of_dept_records != 0) {
                // Sorting by did
                if (buffers[i].dept_record.did > buffers[j].dept_record.did) {
                    swap(buffers[i], buffers[j]);
                }
            }
        }
    }
    // Writing the sorted records into a temporary file (runs)
    for (int i = 0; i < number_of_records; i++) {
        if (buffers[i].number_of_emp_records != 0) {
            runs << buffers[i].emp_record.eid << "," << buffers[i].emp_record.ename << "," << buffers[i].emp_record.age << "," << buffers[i].emp_record.salary << endl;
        } else if (buffers[i].number_of_dept_records != 0) {
            runs << buffers[i].dept_record.did << "," << buffers[i].dept_record.dname << "," << buffers[i].dept_record.budget << "," << buffers[i].dept_record.managerid << endl;
        }
    }
    // Closing the temporary file (runs)
    runs.close();
    //Remember: You can use only [AT MOST] 22 blocks for sorting the records / tuples and create the runs
    return;
}

//Prints out the attributes from empRecord and deptRecord when a join condition is met 
//and puts it in file Join.csv
void PrintJoin() {
    
    return;
}

//Use main memory to Merge and Join tuples 
//which are already sorted in 'runs' of the relations Dept and Emp 
void Merge_Join_Runs(){
   

    //and store the Joined new tuples using PrintJoin() 
    return;
}

int main() {

    //Open file streams to read and write
    //Opening out two relations Emp.csv and Dept.csv which we want to join
    fstream empin;
    fstream deptin;
    empin.open("Emp.csv", ios::in);
    deptin.open("Dept.csv", ios::in);
   
    //Creating the Join.csv file where we will store our joined results
    fstream joinout;
    joinout.open("Join.csv", ios::out | ios::app);

    //1. Create runs for Dept and Emp which are sorted using Sort_Buffer()
    

    //2. Use Merge_Join_Runs() to Join the runs of Dept and Emp relations 


    //Please delete the temporary files (runs) after you've joined both Emp.csv and Dept.csv

    return 0;
}
