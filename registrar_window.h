/* Gary Zeri
  ID: 2321569
  zeri@chapman.edu
  CPSC 250-02
  Assignment 4: Registrar's Office Simulation */

#include <iostream>

using namespace std;

class RegistrarWindow{
	
	public:
		RegistrarWindow();
		RegistrarWindow(int *idleWindows);
	
		bool TickPerson();
		void TickIdle();	
		void AddPerson(int personUseTime);
		bool IsIdle();
		int IdleTime();	
	private:
		bool idle;
		int idleTime;
		int personUseTime;
		int *idleWindows;
};

