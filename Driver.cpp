#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

#include "PinHit.h"
#include "Heap.h"
#include "MinValueHeap.h"
#include "MaxValueHeap.h"

// global variable for type of heap
std::string heapType = "--max";

//forward declare so I can define it below main
void printGreeting();

std::vector<PinHit> ReadPins(char* fileName, int* totalHits);

template<class T, int m_size>
Heap<T, m_size>* BuildHeap(std::vector<PinHit> PinHits, int slots);

// provided
template<class T, int m_size>
int Hack(Heap<T, m_size>* heap, std::vector<PinHit> PinHits, int totalHits);


const int MAX_PINS = 10002; //+2 for off-by-one errors
int main(int argc, char* argv[]) {

  std::vector<PinHit> pass;
  Heap<PinHit,MAX_PINS> *tohack;

  int numpins = 0;
  int* pins = &numpins;
  int numhacks;

  if (argv[2] != heapType)
    {
      heapType = argv[2];
    }

  printGreeting();

  pass = ReadPins(argv[1],pins);
    
  tohack = BuildHeap<PinHit,MAX_PINS>(pass,numpins);
  
  //checking
  //tohack->PrintHeap();
  
  numhacks = Hack(tohack,pass,numpins);
  std::cout << "Num pins hacked: " << numhacks << std::endl;
  
  return EXIT_SUCCESS;
}

// prints your name and section
void printGreeting() {
  std::cout << "Maria Brown, Section 05" << std::endl;
}

// implement these two functions
// takes in a file with many sample pins, and pulls all of the
//   individual pins into a vector, storing as well the number of
//   instances of each pin
std::vector<PinHit> ReadPins(char* fileName, int* totalHits) {

  // array of all posible pins, initialize count to 0
  int pins [MAX_PINS]; 
  for(int i = 0000; i < MAX_PINS; i++)
    {
      pins[i] = 0;
    } 

  // variables for each pin, input file, total # of pins, return vector
  std::string pin;
  std::ifstream ifile(fileName) ;
  int numlines = 0; //for totalHits
  std::vector<PinHit> toreturn;
  int j;//used to be a for loop 

  std::string line;
  // read in entire file
  while(! ifile.eof()){
    // read in each pin
    ifile >>  pin ;
    
    // convert string to integer
    j = atoi( pin.c_str() ) ;

    // increment count for that pin, and number of lines
    pins[j] += 1;
    numlines++;
  }
  
  pins[j] -= 1; //fixing reading in last line twice
  numlines--;
  
  // for each of the 
  for(int k = 0;k < MAX_PINS;k++)
    {
      if (pins[k] != 0) // only for pins in the file
	{
	  // allocate, save, and free
	  PinHit* temp = new PinHit(k,pins[k]);
	  toreturn.push_back(*temp) ;
	  delete(temp);
	 }
    }

  *totalHits = numlines;

  return toreturn;
  
}

template<class T, int m_size>
Heap<T, m_size>* BuildHeap(std::vector<PinHit> PinHits, int slots) {
  Heap<T,m_size> *pass; //just initialize it

  //polymorphism
  if (heapType == "--min")
    {
      pass = new MinValueHeap<T,m_size>(); 
    }
  else
    {
      pass = new MaxValueHeap<T,m_size>(); 
    }


  for (unsigned int i = 0; i < PinHits.size();i++) //already weeded out blanks
    {
      pass->Insert(PinHits[i]);
    }
  return pass;
}

// provided
template<class T, int m_size>
int Hack(Heap<T, m_size>* heap, std::vector<PinHit> PinHits, int totalHits) {
  int UPPER_BOUND = totalHits; // used for failsafes

  /*
   * His fictional bank with fictional cards and 
   * "normal pins" will allow you to incorrectly attempt 
   * to access his card 3 times per hour. You have from 
   * the start of the assignment to the end to hack as 
   * many accounts as possible (14 days * 24 hr/day * 3 
   * attempts/hr = 1008 attempts per card)
   */
  int MAX_ATTEMPTS = 1008;

  int hackAttemptsLeft = MAX_ATTEMPTS;
  int successfulHacks = 0;

  srand (time(NULL)); // seeds our random generator with the current time  
  int randomNumHits = rand() % totalHits; // generates a random hit between 0 and total hits
  //randomNumHits = 0; // change this if you want to hardcode in your hits for a specific pin
  int curHits = 0; // our variable for crawling
  int randomIndex = -1; // the index where our new random pinhit lives
  int newHits = 0; // number of hits in new "random" pin
  int failSafe = 0; // always good to have one of these in what could be an infinite loop

  /* 
   * Linearly searches through PinHits until
   * we've accrued enough hits to reach our random hits
   * which will then determine the next pin to try to hack.
   * We use newHits to make sure we don't pick a random pin
   * that's not in our heap. 
   */
  PinHit curPinHit;
  while (newHits == 0 && failSafe < UPPER_BOUND) {

    for (unsigned int i = 0; i < PinHits.size() && curHits <= randomNumHits; i++) {
      curHits += PinHits[i].GetValue();
      randomIndex = i;
    }
    // should have found the random pin by now
    curPinHit = PinHits[randomIndex];
    newHits = curPinHit.GetValue(); // make sure it's actually in our heap
    std::cout << "Random Pin: [" << curPinHit.GetKey() << ", " << curPinHit.GetValue() << "] found!" << std::endl;
    failSafe++;
  }

  // let's make a copy of the heap so we don't modify the original.
  Heap<T, m_size>* heapCopy;
  
  if (heapType == "--min") {
    heapCopy = new MinValueHeap<T, m_size>(*heap);
  } else if (heapType == "--max") {
    heapCopy = new MaxValueHeap<T, m_size>(*heap);
  } else {
    heapCopy = new Heap<T, m_size>(*heap);
  }

  failSafe = 0;

  PinHit defaultPin;

  // exit once hacking 10000 accounts, either a hacking prodigy or something is wrong
  int MAX_NUM_HACKS = 10000;

  while (0 < hackAttemptsLeft && successfulHacks < MAX_NUM_HACKS) {

    // grabs our root
    PinHit topOfHeap = heapCopy->Remove();
    if (topOfHeap == defaultPin)
      break;

    std::cout << topOfHeap.GetKey() << ", " << topOfHeap.GetValue() 
	      << " Current: " << curPinHit.GetKey() << std::endl;

    //std::cout << "Printing heap" << std::endl;
    //heap->PrintHeap();

    if (hackAttemptsLeft == 1)
      std::cout << topOfHeap.GetKey() << ", " << topOfHeap.GetValue() << " our last attempt" << std::endl;

    hackAttemptsLeft--;

    // account was hacked!
    if (topOfHeap == curPinHit) {
      std::cout << "We got them!" << std::endl;
      successfulHacks++;
      
      // reset our heap
      if (heapType == "--min") {
	heapCopy = new MinValueHeap<T, m_size>(*heap);
      } else if (heapType == "--max") {
	heapCopy = new MaxValueHeap<T, m_size>(*heap);
      } else {
      
	heapCopy = new Heap<T, m_size>(*heap);
      }

      // reset
      hackAttemptsLeft = MAX_ATTEMPTS;
      randomNumHits = rand() % totalHits;
      curHits = 0;
      randomIndex = -1;
      newHits = 0;
      failSafe = 0;
      while (newHits == 0 && failSafe < UPPER_BOUND) {

	for (unsigned int i = 0; i < PinHits.size() && curHits <= randomNumHits; i++) {
	  curHits += PinHits[i].GetValue();
	  randomIndex = i;
	}
	// should have found the random pin by now
	curPinHit = PinHits[randomIndex];
	newHits = curPinHit.GetValue(); // make sure it's actually in our heap
	std::cout << "Random Pin: [" << curPinHit.GetKey() << ", " << curPinHit.GetValue() << "] found!" << std::endl;
	failSafe++;
      }

      std::cout << "Valid Random Pin: " << curPinHit.GetKey() << " found!" << std::endl;
    }
  }

  return successfulHacks;
}
