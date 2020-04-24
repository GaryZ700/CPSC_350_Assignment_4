1. Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 4: Registrar's Office Simulation

2. List of Source Files
	1.)  Makefile
	2.)  Readme.txt
	3.)  doubly_linked_list_interface.h
	4.)  doubly_linked_list.h
	5.)  queue.h
	6.)  registrar_window.h
	7.)  registrar_simulation.h
	8.)  input_manager.h
        9.)  user_input.h
	10.) registrar_window.cpp
	11.) registrar_simulation.cpp
	12.) input_manager.cpp
	13.) user_input.cpp
	14.) main.cpp		

3. Description of any known compile/runtime errors:
	Reading of corrupted or non-text files may result in the program crashing. Also, reading files that 
corrupt while being read, or during a harddrive/solidstate drive failure may also result in the program crashing.

	In addition, assumptions regarding the computation of idle time and data statistics were made that were not explicity stated in the instruction sheet. 
	This may result in output values being consistently larger or smaller than the tester's expected value by the addition or subtraction of a constant value.
	Once this constant value is identified for each statistic, the difference value between expected output and actual output will remain the smae for any input provided to the program. 
	
	The use of an input file with non-Linux line endings will result in undefined and unexpected behavior of the program. 

4. References used to complete the assignment:
	Class Lectures
	Google C++ Stylesheet
	Data Structures & Algorithems in C++, 2nd Edition, Goodrich, Tamassia, & Mount
	https://www.geeksforgeeks.org/pure-virtual-functions-and-abstract-classes/
	www.cplusplus.com/doc/tutorial/inheritance	
	https://stackoverflow.com/questions/4498712/c-virtual-functions-implementation-outside-the-class/
	https://www.quora.com/How-do-I-initialize-a-dynamically-allocated-struct-object-in-C++
	www.cplusplus.com/doc/tutorial/files		
	https://en.cppreference.com/w/cpp/language/goto/
	www.cplusplus.com/reference/string/to_string/

5. Instructions for running the assignment
	1.) Run "make"
	2.) Run "./assignment4.exe" followed by the command line parameter of the simulation input data file.
