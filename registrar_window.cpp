/* Gary Zeri
  ID: 2321569
  zeri@chapman.edu
  CPSC 250-02
  Assignment 4: Registrar's Office Simulation */

#include "registrar_window.h"

using namespace std;

RegistrarWindow::RegistrarWindow(){
	this->idle = true;
	this->idleTime = 0;
	this->personUseTime = 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

RegistrarWindow::RegistrarWindow(int *idleWindows){
	this->idle = true;
	this->idleTime = 0;
	this->personUseTime = 0;
	this->idleWindows = idleWindows;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//function to tick down the time of the person at the window
//if the person leaves during thie process, then return true, else return false
bool RegistrarWindow::TickPerson(){
	if(!IsIdle() && --personUseTime == 0){
		++(*this->idleWindows);
		idle = true;	
		return true;
	}
	
	return false;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Increase the idle time of the window by 1 tick
void RegistrarWindow::TickIdle(){
	++idleTime;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void RegistrarWindow::AddPerson(int personUseTime){
	this->personUseTime = personUseTime;
	this->idle = false;
	--(*this->idleWindows);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool RegistrarWindow::IsIdle(){
	return idle;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int RegistrarWindow::IdleTime(){
	if(idleTime < 0)
		return 0;
	else
		return idleTime;
}
