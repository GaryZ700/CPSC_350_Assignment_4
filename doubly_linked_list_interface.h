/* Gary Zeri
  ID: 2321569
  zeri@chapman.edu
  CPSC 250-02
  Assignment 4: Registrar's Office Simulation */

#ifndef DOUBLY_LINKED_LIST_INTERFACE_H_
#define DOUBLY_LINKED_LIST_INTERFACE_H_

template <class T>
class DoublyLinkedListInterface{

	public:		
		virtual void InsertFront(const T &data)=0;
		virtual void InsertTail(const T &data)=0;
		virtual const T& Front() const =0;
		virtual const T&  Tail() const =0;
		virtual void RemoveFront()=0;
		virtual void RemoveTail()=0;
		virtual void RemovePosition(int position)=0;
		virtual int Search(const T &data) const =0;
		virtual int Size() const =0;
		virtual bool Empty() const =0;
};

#endif //DOUBLY_LINKED_LIST_H_
