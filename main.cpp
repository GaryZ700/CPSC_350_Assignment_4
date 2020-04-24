/* Gary Zeri
  ID: 2321569
  zeri@chapman.edu
  CPSC 250-02
  Assignment 4: Registrar's Office Simulation */

#include "registrar_simulation.h"
#include "input_manager.h"

using namespace std;

int main(int argv, char **argc){

	//check if the user provided a command line argument for the file location with the simulation data
	InputManager inputManager(argc[(argv == 2)], (argv == 2));	
	Queue<int*>* inputData = inputManager.ParseFile();

	//check that the input file was parsed successully
	if(inputData != NULL){
		//call the simulation	
		RegistrarSimulation simulation(inputData);
		simulation.DisplayMetrics();	
	}
		
	return 0;
}
