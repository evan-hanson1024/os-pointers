// compile: g++ -std=c++11 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <limits>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;
    double average;

    // Sequence of user input -> store in fields of `student`
    student.id = promptInt("Please enter the student's id number: ", 0, 999999999);

    student.f_name = new char[128];
    std::cout << "Please enter the student's first name: ";
    std::cin >> student.f_name;

    student.l_name = new char[128];
    std::cout << "Please enter the student's last name: ";
    std::cin >> student.l_name;

    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 1, 134217728);


    student.grades = new double[student.n_assignments];
    int i;
    std::cout << "\n";
    std::string message = "Please enter grade for assignment ";
    std::string suffix = ": ";
    for (i = 0; i < student.n_assignments; i++) {
        std::string index = std::to_string(i);
        student.grades[i] = promptDouble(message + index + suffix, 0, 1000.0);
    }

    // Call `CalculateStudentAverage(???, ???)`
    calculateStudentAverage(&student, &average);
    //Round average
    average = (double)((int)((average * 10) + 0.5))/10;

    //Set up strings for output
    std::string output_name_id = std::string("\n") + std::string("Student: ") + std::string(student.f_name) + std::string(" ") + std::string(student.l_name) + std::string(" ") + std::string("[") + std::to_string(student.id) + std::string("]\n");

    // Output `average`
    std::cout << output_name_id;
    std::cout << "  Average grade: " << average << "\n";

    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    int candidate;
    bool is_not_int_flag = false;
    std::string candidate_string;

    while(true){
        is_not_int_flag = false;
        std::cout << message;
        std::cin >> candidate_string;

        int i;
        for (i = 0; i < candidate_string.length(); i++) {
            if (isdigit(candidate_string[i]) == false) {
                is_not_int_flag = true;
            }
        }

        if (!is_not_int_flag) {
            candidate = std::stoi(candidate_string);
        }

        if(candidate > min && candidate < max && !is_not_int_flag){
            break;
        }
        else{
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return candidate;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    double candidate;
    bool is_not_double_flag = false;
    std::string candidate_string;
    int period_counter = 0;

    while(true){
        is_not_double_flag = false;
        period_counter = 0;
        std::cout << message;
        std::cin >> candidate_string;

        int i;
        for (i = 0; i < candidate_string.length(); i++) {
            if (isdigit(candidate_string[i]) == false) {
                period_counter++;
            }
        }

        if (period_counter > 1) {
            is_not_double_flag = true;
        }

        if (!is_not_double_flag) {
            candidate = std::stod(candidate_string);
        }

        if(candidate > min && candidate < max && !is_not_double_flag){
            break;
        }
        else{
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return candidate;
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    // Code to calculate and store average grade
    Student* student = (Student*)object;
    int number_assignments = student->n_assignments;
    int i = 0;
    double currentSum = 0;
    for (int i = 0; i < number_assignments; i++) {
        currentSum = currentSum + student->grades[i];
    }
    *avg = currentSum/number_assignments;

}