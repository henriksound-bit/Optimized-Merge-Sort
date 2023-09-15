# Optimized Merge Sort for Joining CSV Files
## Assignment 5 for CS 440 Database Management Systems at Oregon State University

This program is designed to perform an optimized merge sort on two CSV files, `Emp.csv` and `Dept.csv`, and join them based on certain conditions. The code is written in C++ and uses the standard library for file I/O and string manipulation.
### Code Structure

The codebase is divided into two main files:

1. `main.cpp`: This file contains the main logic for reading the CSV files, sorting the records, and joining them.

2. `record_class.h`: This file defines the `Records` class, which is used to store the records from the CSV files. It also contains methods for grabbing a single record from each CSV file.
#### Key Functions

- `swap(Records &a, Records &b)`: This function is used to swap two `Records` objects.

- `Sort_Buffer(Records buffers[], int num_emp_records, string filename)`: This function sorts the records in the buffer and writes them to a temporary file.

- `Merge_Join_Runs(fstream &emp_runs, fstream &dept_runs)`: This function merges and joins the sorted runs of the Emp and Dept relations.

- `Grab_Emp_Record(fstream &empin)` and `Grab_Dept_Record(fstream &deptin)`: These functions grab a single record from the `Emp.csv` and `Dept.csv` files respectively and store them in the `Records` class.

- `main()`: This is the main function where the CSV files are read, sorted, and joined.

### How to Use

1. Ensure that the `Emp.csv` and `Dept.csv` files are in the same directory as the code files.

2. Compile the code using a C++ compiler.

3. Run the compiled code. The joined records will be written to a file named Join.csv.
4. 
### Important Notes

- The code uses a buffer of size 22 to store the records in memory. This is defined by the `buffer_size` macro.

- The `Records` class contains two structures, `EmpRecord` and `DeptRecord`, which are used to store the records from the `Emp.csv` and `Dept.csv` files respectively.

- The code uses a simple bubble sort algorithm to sort the records in the buffer. This can be replaced with a more efficient sorting algorithm if needed.

- The code assumes that the `Emp.csv` and `Dept.csv` files are formatted correctly and that each line contains a valid record.

- The code creates temporary files to store the sorted runs. These files are deleted after the join operation is completed.
Code Snippets

Here are some key code snippets:

- Sorting the records in the buffer:
```c++

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
```

- Reading the records from the CSV files and creating the sorted runs:
```c++

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
```
- Merging and joining the sorted runs:
```c++
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
```
- Main function:
```c++
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
```
