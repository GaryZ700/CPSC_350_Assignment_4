/* Gary Zeri
  ID: 2321569
  zeri@chapman.edu
  CPSC 250-02
  Assignment 4: Registrar's Office Simulation */

#ifndef REGISTRAR_SIMULATION_H_
#define REGISTRAR_SIMULATION_H_

#include <limits>
#include "queue.h"
#include "registrar_window.h"
using namespace std;

class RegistrarSimulation{

	public:
		RegistrarSimulation();
		RegistrarSimulation(Queue<int*>* inputData);
		~RegistrarSimulation();	
	
		void AddInputData(Queue<int*>* inputData);	
		void Simulate();
		void DisplayMetrics();
		bool HasSimulated();	
	private:
		bool hasSimulated;

		//inputDat is a queue consisting of integer arrays of size 2 with the following structure
		//	[time the student will take up at the window, clock tick at which this student appears], [time that student will take up at window, clock tick at which this student appears]
		//	the very first element in the queue is formatted as follows [# of open windows for the simulation, 0] 
		//	data is sorted in such an order that the arrays closer to the start of the queue will have an earlier time tick than the arrays at the end of the queue
		Queue<int*>* inputData;

		struct StatisticsData{
			public:
				int *waitTimes;
				int index;
				int size;
				
				int openWindows;
				RegistrarWindow **windows;
				
				double mean;
				double median;
				int waitsOver10Min;
				int maxWaitTime;
				double meanIdleTime;
				int longestIdleTime;
				int maxIdleTime;
				int idlesOver5Min;	
		};
		StatisticsData *statsData;
		
		void ComputeStats();
		void RemoveMin(int **array, int &size, bool max);
		void FindMin(int *array, int size, int &value, int &index, bool max);
};

#endif //REGISTRAR_SIMULATION_H_
