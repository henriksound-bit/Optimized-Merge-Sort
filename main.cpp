/* This is a skeleton code for Optimized Merge Sort, you can make modifications as long as you meet 
   all question requirements*/  

#include <bits/stdc++.h>
#include "record_class.h"
#include <fstream>
#include <cstdio>
#include <cstdlib>

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
fstream Sort_Buffer(Records buffers[], int num_emp_records, string filename){

    fstream runs;
    runs.open(filename, ios::out | ios::app);
    if (num_emp_records == 0) {
        // Write null to the file
        cout << "No records to sort" << endl;
        runs << "NULL" << endl;
        return runs;
    }
    // Sorting the records in the buffer
    for (int i = 0; i < num_emp_records; i++) {
        for (int j = i + 1; j < num_emp_records; j++) {

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
    for (int i = 0; i < num_emp_records; i++) {
        if (buffers[i].number_of_emp_records != 0) {
            runs << buffers[i].emp_record.eid << "," << buffers[i].emp_record.ename << "," << buffers[i].emp_record.age << "," << buffers[i].emp_record.salary << endl;
        } else if (buffers[i].number_of_dept_records != 0) {
            runs << buffers[i].dept_record.did << "," << buffers[i].dept_record.dname << "," << buffers[i].dept_record.budget << "," << buffers[i].dept_record.managerid << endl;
        }
    }
    //Remember: You can use only [AT MOST] 22 blocks for sorting the records / tuples and create the runs
    return runs;
}

//Prints out the attributes from empRecord and deptRecord when a join condition is met 
//and puts it in file Join.csv
void PrintJoin() {
    
    return;
}

//Use main memory to Merge and Join tuples 
//which are already sorted in 'runs' of the relations Dept and Emp 
fstream Merge_Join_Runs(fstream &emp_runs, fstream &dept_runs){

    //TO-DO: Implement the Merge Join algorithm using the main memory (buffers)
    buffers = new Records[buffer_size];
    fstream joinout;
    joinout.open("Join.csv", ios::out | ios::app);
    //1. Read the first block from each run and store it in the main memory (buffers)
    //1.1. Read the first block from the Emp run and store it in the main memory (buffers)
    //1.2. Read the first block from the Dept run and store it in the main memory (buffers)
    //2. Repeat the following steps until all the runs are exhausted
    //2.1. Find the minimum of the first records in the main memory (buffers)
    //2.2. If the minimum is from the Emp run, then write it to the output file Join.csv
    //and read the next record from the same run and store it in the main memory (buffers)
    //2.3. If the minimum is from the Dept run, then write it to the output file Join.csv
    //and read the next record from the same run and store it in the main memory (buffers)
    //2.4. If the minimum is from both the runs, then write it to the output file Join.csv
    //and read the next record from both the runs and store it in the main memory (buffers)
    //3. Write the remaining records in the main memory (buffers) to the output file Join.csv
    //4. Close the file streams


    //and store the Joined new tuples using PrintJoin() 
    return joinout;
}

int main() {

    //Open file streams to read and write
    //Opening out two relations Emp.csv and Dept.csv which we want to join
    fstream empin;
    fstream deptin;
    empin.open("Emp.csv", ios::in);
    deptin.open("Dept.csv", ios::in);
    int num_emp_records = 0;
    int num_dept_records = 0;
    Records emp_records[buffer_size];
    Records dept_records[buffer_size];
   
    //Creating the Join.csv file where we will store our joined results
    fstream joinout;
    joinout.open("Join.csv", ios::out | ios::app);

    //1. Create runs for Dept and Emp which are sorted using Sort_Buffer()
    fstream emp_runs = fstream("runs", ios::out | ios::app);
    fstream dept_runs = fstream("runs", ios::out | ios::app);

    /*
     * Idea: In these two while loops we are reading each line from the empin and deptin files
     * and adding it to the emp_records and dept_records arrays respectively. From there, we need
     * to find a way to combine these two blocks such that they can be merged once buffer size is reached.
     * As of now we're operating such that both emp_records and dept_records are sorted into the temporary runs
     * files, but we need to find a way to merge them together.
     */

    // Read each line from the empin file and add it to emp_records
    while (empin >> emp_records[num_emp_records].emp_record.eid >> emp_records[num_emp_records].emp_record.ename >> emp_records[num_emp_records].emp_record.age >> emp_records[num_emp_records].emp_record.salary) {
        emp_records[num_emp_records].number_of_emp_records = 1;
        num_emp_records++;
        if (num_emp_records == buffer_size) {
            // Sort the records in the buffer and write them to a temporary file (emp_runs)
            emp_runs = Sort_Buffer(emp_records, num_emp_records, "emp_runs");
            num_emp_records = 0;
        }
    }
    // Do the same for department records
    // Reach each line from the deptin file and add it to dept_records
    while (deptin >> dept_records[num_dept_records].dept_record.did >> dept_records[num_dept_records].dept_record.dname >> dept_records[num_dept_records].dept_record.budget >> dept_records[num_dept_records].dept_record.managerid) {
        dept_records[num_dept_records].number_of_dept_records = 1;
        num_dept_records++;
        if (num_dept_records == buffer_size) {
            // Sort the records in the buffer and write them to a temporary file (dept_runs)
            dept_runs = Sort_Buffer(dept_records, num_dept_records, "dept_runs");
            num_dept_records = 0;
        }
    }

    //2. Use Merge_Join_Runs() to Join the runs of Dept and Emp relations 
    joinout = Merge_Join_Runs(emp_runs, dept_runs);
    // Write joinout to the Join.csv file
    joinout.close();

    //Please delete the temporary files (runs) after you've joined both Emp.csv and Dept.csv
    emp_runs.close();
    dept_runs.close();
    return 0;
}
