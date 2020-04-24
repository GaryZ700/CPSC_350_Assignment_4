/* Gary Zeri
  ID: 2321569
  zeri@chapman.edu
  CPSC 250-02
  Assignment 4: Registrar's Office Simulation */

#include "registrar_simulation.h"

using namespace std;

RegistrarSimulation::RegistrarSimulation(){
	this->hasSimulated = false;
	this->inputData = NULL;
	this->statsData = new StatisticsData;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

RegistrarSimulation::RegistrarSimulation(Queue<int*>* inputData){
	this->hasSimulated = false;
	this->inputData = inputData;

	this->statsData = new StatisticsData;
	this->statsData->size = inputData->Size() - 1;
	this->statsData->index = 0;
	this->statsData->waitTimes = new int[statsData->size];

	this->Simulate();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

RegistrarSimulation::~RegistrarSimulation(){
	delete[] statsData->waitTimes;
	delete[] statsData->windows;
	delete statsData;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void RegistrarSimulation::AddInputData(Queue<int*>* inputData){
	this->inputData = inputData;

	this->statsData->size = inputData->Size() - 1;
	this->statsData->index = 0;
	this->statsData->waitTimes = new int[statsData->size];
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void RegistrarSimulation::Simulate(){

	//code to set up the simulation	
	//start the simulation at time = 0
	int clockTick = 0;
	//load the amount of open windows specified from the input data
	statsData->openWindows = inputData->Dequeue()[1];
	//at the start of the simulation all of the windows are idle
	int idleWindows = statsData->openWindows;

	//set up all of the open windows
	statsData->windows = new RegistrarWindow*[statsData->openWindows];
	for(int i=0; i<statsData->openWindows; ++i)
		statsData->windows[i] = new RegistrarWindow(&idleWindows);

	//main loop for the simulation
	//end the simulation once there are no more people in the queue and there are no more people at the windows
	do{					
		for(int i=0; i<statsData->openWindows; ++i){

			//to avoid over counting window idle time
			//when a person is removed from a window but there are no more people to place at that window	
			if(statsData->windows[i]->TickPerson() && inputData->Empty())
				continue;
	
			//if there is an idle window and a person waiting in the queue, then place that person into the open window
			//otherwise, if the window is idle, but there are no people in the queue, then increment the idle time of the window
 			//has a safety guard to enusre that before retriving the front of the queue that the queue is actually empty
			if(statsData->windows[i]->IsIdle()){
		
				if(!inputData->Empty() && inputData->Front()[0] <= clockTick){
					int *data = inputData->Dequeue();
					statsData->windows[i]->AddPerson(data[1]);
					statsData->waitTimes[statsData->index++] = clockTick - data[0];
				}
				else		
					statsData->windows[i]->TickIdle();
			}
		}		

		++clockTick;
	} while(!inputData->Empty() || idleWindows != statsData->openWindows);

	hasSimulated = true;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void RegistrarSimulation::DisplayMetrics(){

	if(!HasSimulated()){
		cout << endl << "Please run the simulation before displaying the simulation metrics." << endl << endl;
		return;
	}

	ComputeStats();

	cout << endl << endl;
	cout << "Registrar Simulation Metrics" << endl;
	cout << "1. The Mean Student Wait Time: " << statsData->mean <<endl;
	cout << "2. The Median Student Wait Time: " << statsData->median << endl;
	cout << "3. The Longest Student Wait Time: " << statsData->maxWaitTime << endl;
	cout << "4. The Number of Students waiting over 10 Minutes: " << statsData->waitsOver10Min << endl;
	cout << "5. The Mean Window Idle Time: " << statsData->meanIdleTime << endl;
	cout << "6. The Longest Window Idle Time: " << statsData->maxIdleTime << endl;
	cout << "7. Number of Windows Idle for over 5 Minutes: " << statsData->idlesOver5Min << endl << endl;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool RegistrarSimulation::HasSimulated(){
	return hasSimulated;
}

//---------------------------------------------------------------------------------

void RegistrarSimulation::ComputeStats(){

	//intialize all the variables used in the statistics computation
	statsData->mean = 0;
	int *medianArray = new int[statsData->size];
	int medianArraySize = statsData->size;
	int idleTimes[statsData->openWindows];	
	statsData->waitsOver10Min = 0;
	statsData->meanIdleTime = 0;
	statsData->idlesOver5Min = 0;

	//computes the mean, waits over 10 min, and sets up the median computatoin for the persons at the rigistrar's office
	for(int i=0; i<statsData->size; ++i){
		
		statsData->mean += statsData->waitTimes[i];

		medianArray[i] = statsData->waitTimes[i];

		if(statsData->waitTimes[i] > 10)
			++statsData->waitsOver10Min;
	}

	//computes the mean idle time, the number of idles over 5 min, and sets up the max idle time for the registrar windows related data
	for(int i=0; i<statsData->openWindows; ++i){
	
		statsData->meanIdleTime += statsData->windows[i]->IdleTime();
	
		if(statsData->windows[i]->IdleTime() > 5)
			++statsData->idlesOver5Min;
	
		idleTimes[i] = statsData->windows[i]->IdleTime();
	}

	//complete mean computations
	statsData->mean /= statsData->size;
	statsData->meanIdleTime /= statsData->openWindows;

	//compute the median person wait time
	while(medianArraySize != 2 && medianArraySize != 1){
		if(medianArraySize % 2 == 0)
			RemoveMin(&medianArray, medianArraySize, false);
		else
			RemoveMin(&medianArray, medianArraySize, true);
	}
	if(medianArraySize == 1)
		statsData->median = medianArray[0];
	else 
		statsData->median = (medianArray[0] + medianArray[1]) / 2.0;
	delete[] medianArray;
	
	//compute max wait time, and max idle time
	int index;
	FindMin(statsData->waitTimes, statsData->size, statsData->maxWaitTime, index, true);
	FindMin(idleTimes, statsData->openWindows, statsData->maxIdleTime, index, true);		
}

//---------------------------------------------------------------------------------

//Removes the min or max value from an array
void RegistrarSimulation::RemoveMin(int **array, int &size, bool max){

	//locate the location of the minimum or maximum value of the array
	int deleteIndex;
	int value;	
	FindMin(*array, size, value, deleteIndex, max);

	//delete the value from the specified location
	int *tempArray = new int[--size];
	int offset = 0;	
	for(int i=0; i<size+1; ++i){
		if(i != deleteIndex)
			tempArray[i-offset] = (*array)[i];
		else
			offset = 1;
	}

	//delete the old array and replace it with the new array with the removed value
	delete[] *array;
	*array = NULL;
	
	*array = tempArray;
}

//---------------------------------------------------------------------------------

//function to find the minimum or maximum value of an array
//returns both the min/max and location of the value via pass by reference 
void RegistrarSimulation::FindMin(int *array, int size, int &value, int &index, bool max){

	//determine the intial number for value
	if(max) 
		value = numeric_limits<int>::min();
	else
		value = numeric_limits<int>::max(); 	
	
	for(int i=0; i<size; ++i){
		if( (!max && array[i] <= value) || (max && array[i] >= value) ){
			value = array[i];
			index = i;
		}
	}
}
