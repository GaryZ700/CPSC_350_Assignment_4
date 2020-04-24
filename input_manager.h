/* Gary Zeri
  ID: 2321569
  zeri@chapman.edu
  CPSC 250-02
  Assignment 4: Registrar's Office Simulation */

#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include <cmath>
#include "queue.h"
#include "user_input.h"

using namespace std;

class InputManager{

	public:
		InputManager(string fileLocation, bool fileLocationProvided);
		~InputManager();

		Queue<int*>* ParseFile();
	private:
		bool validatingTimeTick;
		int lastClockTick;
		int lineNumber;
		fstream *file;
		UserInput *input; 
		Queue<int*> *fileData;

		void BadFileError(string errorMsg);
		bool ValidateNumber(string line, int &returnData, int lineNumber, string dataName);
		bool UnexpectedFileEnding(int lineNumber, string dataName);
		bool EnqueueFileLine(string numberDataName, string fileEndingDataName, int clockTick, bool ignoreBadFileEnding=false);  
		bool ParseFileLine(string numberDataName, string fileEndingDataName, int &returndata,  bool ignoreBadFileEnding=false);	
};

#endif //INPUT_MANAGER_H_
