

Beginner Level Problem Statement: 
Managing C++ Files and Directories in Linux

`Objective`:  
Gain hands-on experience 
with basic Linux commands while working 
with a C++ project by 
    creating, 
    editing, 
    compiling, and 
    running simple programs.

---

`Tasks`:

1. Create a new directory called `my_cpp_project` for your C++ programs.

    mkdir my_cpp_project

2. Change into the `my_cpp_project` directory.

     cd my_cpp_project/

3. Create a C++ file named `greet.cpp` 
in the `my_cpp_project` directory.
    
    touch greet.cpp
     
4. Write a C++ program inside `greet.cpp` 
that asks the user for their name and prints a greeting message.
   
    nano greet.cpp

    #include<iostream>
    using namespace std;

    int main() {

        char name[20];
        cout << "Enter a name: ";
        cin >> name;
        cout << "Hello ," << name << "! Welcome to the C++ world!";
    }
     ctrl + x to save
     press y(yes) to save modified buffer
     press enter to Write: hello_name.cpp   

    
5. Compile the `greet.cpp` program into an executable.

     g++ greet.cpp

6. Run the compiled executable and ensure 
that it prompts for the user’s name and displays the greeting.

     ./a.out
     Enter a name: Abel
     Hello ,Abel! Welcome to the C++ world!

7. Use a Linux command to display the contents of `greet.cpp`.
     
      cat greet.cpp
     #include<iostream>
     using namespace std;

     int main() {

        char name[20];
        cout << "Enter a name: ";
        cin >> name;
        cout << "Hello ," << name << "! Welcome to the C++ world!" << endl;
    }

8. Modify the `greet.cpp` file 
to add a simple farewell message and save the changes.

    nano greet.cpp

    #include<iostream>
     using namespace std;

     int main() {

        char name[20];
        cout << "Enter a name: ";
        cin >> name;
        cout << "Hello ," << name << "! Welcome to the C++ world!" << endl;
        cout << "Goodbye, " << name << "! Have a great day!" ;
    }

    ctrl + x to save
    press y(yes) to save modified buffer
    press enter to Write: hello_name.cpp 


9. Compile and run the modified program 
to ensure it works as expected.
   
    g++ greet.cpp
    ./a.out
    Enter a name: Abel
    Hello ,Abel! Welcome to the C++ world!
    Goodbye, Abel! Have a great day!

     

10. Remove the `greet.cpp` file once you're done.

       rm greet.cpp
      
11. Check the contents of the `my_cpp_project` directory, and 
remove the directory if it’s empty.

       ls
       rm my_cpp_project

`Goal`:  
Through this task, I practiced 
using basic Linux commands such as 
    directory creation, 
    text file manipulation, 
    compiling, and 
    running programs, 
helping me to be more familiar 
with the Linux environment for C++ development.









 

