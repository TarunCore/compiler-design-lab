#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <thread>
#include <vector>
#include <chrono>
using namespace std;

void SQARQ(int totalFrames, int windowSize) {
     vector<bool> ackReceived(totalFrames, false); 
     int base = 0;
     int nextFrameToSend = 0; 
     int totalFramesSent = 0; 
     int totalTransmited = 0; 
     srand(static_cast<int>(time(0))); 
     while (base < totalFrames) {
         while (nextFrameToSend < base + windowSize && nextFrameToSend < totalFrames) {
            cout << "Sending Frame no: " << nextFrameToSend << endl;
             totalFramesSent++;
             nextFrameToSend++;
         }
        sleep(1);
         
         for (int i = base; i < nextFrameToSend; i++) {
         
             if (rand() % 12 < 9) {
                 cout << "acknoledgement " << i << " received" << endl;
                 ackReceived[i] = true;
                 totalTransmited++;
             } else {
                cout << "acknoledgement " << i << " re-transmisitting." << endl;
            }
         }
         
         while (ackReceived[base]) {
            base++;
         }	 	  	 	  	 	    	   	 	      	    	 	
        cout << endl; 
     }
 
    cout << "Frames sent: " << totalFramesSent << endl;
    cout << "Frames successfully transmitted: " << totalTransmited << endl;
}
int main() {
 int noofframes, windowSize;
 cout << "input the window size: ";
 cin >> windowSize;
 cout << "Input the total nop. of frames ";
 cin >> noofframes;
 SQARQ(noofframes, windowSize);
 return 0;
}