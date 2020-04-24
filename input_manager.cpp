/* Gary Zeri
  ID: 2321569
  zeri@chapman.edu
  CPSC 250-02
  Assignment 4: Registrar's Office Simulation */

#include "input_manager.h"

using namespace std;

InputManager::InputManager(string fileLocation, bool fileLocationProvided){

	this->lastClockTick = 0;
	
	if(fileLocationProvided)
		file = new fstream(fileLocation);
	else{
		file = NULL;
		BadFileError("Command line argument specifiying the location of the Registrar Office Simulation data file was not provided.");
	}

	while(!file->is_open())
		BadFileError("Warning! The specified file could not be opened! Please ensure that the file exists." );

	input = new UserInput;	

	//set data structure for holding the parsed file data	
	fileData = new Queue<int*>;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

InputManager::~InputManager(){
	file->close();
	delete file;

	delete input;
	delete fileData;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Parses the input data from the file and ensures that the input file is correctly formatted
//returns a queue consisting of integer arrays of size 2 with the following structure
//	[time the student will take up at the window, clock tick at which this student appears], [time that student will take up at window, clock tick at which this student appears]
//	the very first array in the queue has the following structure [# of open windows, 0] 
//	data is sorted in such an order that the arrays closer to the start of the queue will have an earlier time tick than the arrays at the end of the queue
//return NULL if the file format was incorrect than what was expected
Queue<int*>* InputManager::ParseFile(){

	bool firstLoopRun = false;

	//initalize the class lineNumber counter to 1
	lineNumber = 1;
	
	//parse the number of windows that should be kept open 
	if(!EnqueueFileLine("# of open windows", "clock tick at which the first student(s) arrive", 0))
		return NULL;
	
	//while loop structure to parse clock tick, number of students, and student wait times data from the file
	while(true){
		
		int clockTick;
		int numberOfStudents; 

		//get the clock tick value and set teh validating timeTick flag to true to account for fact that a 0 time tick is valid
		validatingTimeTick = true;
		if(!ParseFileLine("clock tick", "number of students coming in at clock tick " + to_string(clockTick),clockTick, firstLoopRun))
			return NULL;	
		validatingTimeTick = false;
			

		//check if the loop has run at least once sucessfully to determine whether or not the entire file has been parsed
		if(firstLoopRun && file->eof())
			break;
		else
			firstLoopRun = true;

		//get the number of students coming in at the specified clock tick
		if(!ParseFileLine("number of students coming in at clock tick " + to_string(clockTick), "time that the student will need to be at the window", numberOfStudents, firstLoopRun))
			return NULL;
		
		bool ignoreUnexpectedFileEnding = false;
		//parse all of the student wait times from the file 
		for(int i=0; i<numberOfStudents; ++i){

			//check if on the  last student window use time
			//if yes, then the next line may be empty and should be abllowed to be empty 
			if(i == numberOfStudents-1)
				ignoreUnexpectedFileEnding = true;
	
			if(!EnqueueFileLine("time that the student will need to be at the window", "time that the student will need to be at the window", clockTick, ignoreUnexpectedFileEnding))
				return NULL;
		}
	
		lastClockTick = clockTick;
	}
	
	return fileData;		
} 

//---------------------------------------------------------------------------------

void InputManager::BadFileError(string errorMsg){

	cout << endl << errorMsg << endl;	
	cout << "Please enter a new file name: ";

	if(file != NULL){	
		file->close();
		delete file;
	}
	
	string fileLocation;
	getline(cin, fileLocation);

	file = new fstream(fileLocation);
}

//---------------------------------------------------------------------------------

bool InputManager::ValidateNumber(string line, int &returnData, int lineNumber, string dataName){

	double doubleReturn;

	//check to ensure that the line is valid number to begin with 	
	if(input->StringIsNumber(line, doubleReturn))
	
		//check to ensure that the number is strictly greater than 0
		if(doubleReturn > 0 || validatingTimeTick)
				
			//check to ensure that a whole numnber and not a decimal was entered
			if(doubleReturn == round(doubleReturn)){
				returnData = doubleReturn;
				return true;
			}
			else
				cout << endl << "Error on Line Number " << lineNumber << ": Expecting a whole integer number representing the " << dataName << ", but instead found the following fractional value '" << line << "'." << endl; 
		else 
			cout << endl << "Error on Line Number " << lineNumber << ": Expecting a positive non-zero integer representing " << dataName << ", but instead found '"<< line << "'." << endl;
	else
		cout << endl <<	"Error on Line Number " << lineNumber << ": Expecting an integer representing " << dataName << ", but instead found '" << line << "'." << endl;

	cout << endl;
	 
	return false;	
}

//---------------------------------------------------------------------------------

bool InputManager::UnexpectedFileEnding(int lineNumber, string dataName){
	if(!file->eof())
		return false;
	
	cout << endl << "Expecting the " << dataName << " on lineNumber " << lineNumber << " but instead found an unexpected end of file." << endl << endl;
	return true;
}

//---------------------------------------------------------------------------------

bool InputManager::EnqueueFileLine(string numberDataName, string fileEndingDataName, int clockTick, bool ignoreBadFileEnding){

	int *data = new int[2];
	data[0] = clockTick;

	if(!ParseFileLine(numberDataName, fileEndingDataName, data[1], ignoreBadFileEnding))
		return false;

	//check if the current clock tick is greater than or equal to the previous clock tick 
	//if not inform the user of the input error
	if(!fileData->Empty() && data[0] < lastClockTick){
		cout << endl << "Error on line " << lineNumber-1 << ", found a clock tick of " << data[0] << " while the previous clock tick was at " << lastClockTick << ".\nPlase ensure that clock ticks are listed in chronological order in the input file." << endl << endl;
		return false;
	}

	fileData->Enqueue(data);
		
	return true;
}

//---------------------------------------------------------------------------------

bool InputManager::ParseFileLine(string numberDataName, string fileEndingDataName, int &returnData, bool ignoreBadFileEnding){

	string line;

	//get line data 
	getline(*file, line);

	//check to ensure that the file was meant to end
	//check to ensure that the file did not unexpectedly end
	//check to ensure the inputted number is a valid integer
	if( (!ignoreBadFileEnding || !file->eof()) &&  
	    ( (!ignoreBadFileEnding && UnexpectedFileEnding(lineNumber, fileEndingDataName)) ||
	     !ValidateNumber(line, returnData, lineNumber++, numberDataName) ) )
		return false;

	return true;
}
