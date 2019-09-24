/*
 * Anthony Dupont
 * Data Structure
 * Assignment 4
 */
#ifndef MYVECTOR_
#define MYVECTOR_
/*Defines a MyVector type which mirrors the STL vector class.  It uses templates and dynamic memory allocation*/
#include <Arduboy2.h>
#include "Pair.h"

typedef Pair T;
struct MyVector
{
    int8_t vsize;
    T *vecPtr;
    MyVector() : vsize(0), vecPtr(nullptr) {}; //constructor, initializes size to 0 and vecPtr to nullptr
    T operator[] (int8_t index){return vecPtr[index];}   //allows to use bracket with an index to the object
    
    bool isEmpty()
    {
		if(vecPtr == nullptr)
		{
			return true;
		}
		return false;
    }

    
    void pop_back()    //removes the last element that was added to the vector
    {
      if(vecPtr != nullptr)
      {
		  if(vsize - 1 == 0)
		  {
			  delete vecPtr;	//I forget if size 0 means 1 element or no element, i know array starts at 0 blah blah, either way I delete it just in case
			  vecPtr = nullptr;	//it not points to null to signify that it is empty
			  return;
		  }
        T *tempPtr = new T[vsize - 1];  //vsize has not been updated yet (compared to my push back where i updated right away)
                                            //so i have to use a size under since I'm removing an element from the dynamic array
        for(int8_t i = 0; i < vsize - 1; i++)  //I have to copy everything but the last element so I'm using vsize - 1
        {
            tempPtr[i] = vecPtr[i]; //copying content over
        }
        delete vecPtr;  //deleting old dyanmic array to not get memory leak
        vecPtr = tempPtr;   //updating pointer
        vsize--;    //decreasing the size variable
        }
    }//end of pop back
    
    
    void push_back(T value) //adds the value variable to the next available position inside the vector
    {    
    vsize++;    //since we're doing a push_back, i increase the size right away, so from the start i'm dealing with the new size
    int8_t positionToAdd = vsize - 1;  //since it's after the vsize has been increased i have to -1. doesn't have to be like that
    if(vecPtr == nullptr)   //if it's the first time creating a dynamic array
    {
        vecPtr = new T[vsize];   //Pointer now points to the new dynamic array, this dynamic array can only be accessed with the pointer
        vecPtr[positionToAdd] = value;  //adding the value to where it should be pushed back to
    }
    else    //else there already exist a dynamic array and we have to copy over, add, and delete old one
    {
        T *tempPtr = new T[vsize];  //calling it tempPtr to not lose my previous pointer just yet
        for(int8_t i = 0; i < vsize - 1; i++)  //using vsize - 1 because to copy, i have to copy the old array so i have to use the old size
        {
            tempPtr[i] = vecPtr[i]; //copying the content over to the new dynamic array
        }
        tempPtr[positionToAdd] = value; //adding the value that we wanted to push back
        delete vecPtr;  //the old dynamic array is gone
        vecPtr = tempPtr;   //vecPtr now points to the new one
    }
    }//end of push back

    void removeElement(int8_t index)
    {
		//copy everything over except for the element that is being removed unless we are deleting the last element
		if (vsize == 1)
			pop_back();
		else
		{
			T *tempPtr = new T[vsize - 1];
			int8_t j = 0;
			for (int8_t i = 0; i < vsize; i++)
			{
				if (i != index) {
					tempPtr[j] = vecPtr[i];
					j++;
				}
			}
			vsize--;
			delete vecPtr;
			vecPtr = tempPtr;
		}
    }
};






#endif
