/* Gary Zeri
  ID: 2321569
  zeri@chapman.edu
  CPSC 250-02
  Assignment 4: Registrar's Office Simulation */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "doubly_linked_list.h"

using namespace std;

template <class T>
class Queue{

	public:
		Queue(){
			queueData = new DoublyLinkedList<T>;	
		}
		
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
		Queue(const T &data){
			queueData = new DoublyLinkedList<T>;
			Enqueue(data);
		}		

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		void Enqueue(const T &data){
			queueData->InsertTail(data);
		}		
	
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
		T Dequeue(){
			T data = queueData->Front();
			queueData->RemoveFront();
			return data;
		}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		
		const T& Front(){
			return queueData->Front();
		}
	
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		
		int Size(){
			return queueData->Size();
		}
	
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
		bool Empty(){
			return queueData->Empty();
		}

	//---------------------------------------------------------------------------------
	
	private:
		DoublyLinkedList<T> *queueData;
};

#endif //QUEUE_H_
