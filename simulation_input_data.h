/* Gary Zeri
  ID: 2321569
  zeri@chapman.edu
  CPSC 250-02
  Assignment 4: Registrar's Office Simulation */

#include "doubly_linked_list.h"

using namespace std;

class SimulationInputData{
 
	public: 
		friend class InputManager;
		friend class RegistrarSimulation;
		
		SimulationInputData();
		~SimulationInputData();
		
		bool AddData(int clockTick, int numberOfStudents, int[] students);
	private:
		//clock ticks is a list of all the clock ticks that have occured
		//the index of the clock tick in the list is also the index 
		//for the list of students that arrive at that time
		DoublyLinkedList<int> *clockTicks;	
		DoublyLinkedList<DoublyLinkedList<int>> *students;
};
