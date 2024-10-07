#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h> 
#include <vector>

using namespace std;

class GoBackNARQ {
public:
int windowSize;
    int totalFrames;
    int nextFrameToSend;
    int ackReceived;
    GoBackNARQ(int windowSize, int totalFrames) 
        : windowSize(windowSize), totalFrames(totalFrames), nextFrameToSend(0), ackReceived(0) {}

    void simulate() {
        while (ackReceived < totalFrames) {
            sendFrames();
            int prev= nextFrameToSend;
            vector<int> stat = receiveAckno();
            if(stat[0]<3){
                cout << "received ACK for frame: " << stat[3] << endl;
                if(stat[1]!=-1){
                    ackReceived=stat[1];
                }
                else if(stat[2]!=-1){
                    cout << "error at frame " << stat[3] << endl;
                    nextFrameToSend=stat[2];
                }
            }else{
                nextFrameToSend=prev;
                cout << "Timeout\n";
            }
        }
cout << "Done. all frames sent" << endl;
    }

    

    void sendFrames() {
        for (int i = 0; i < windowSize && nextFrameToSend < totalFrames; ++i) {
            cout << "Sending frame: " << nextFrameToSend << endl;
            ++nextFrameToSend;
        }
    }

    vector<int> receiveAckno() {
        int ack = rand() % windowSize + ackReceived;
        
        int timeout = rand()%6;
        vector<int> stat(4, -1);
        // time, ackReceived, nextFrameToSend, ack
        stat[3]=ack;
        if (ack == ackReceived) {
            stat[2]=ackReceived;
            
        } else {
            stat[1]=ack+1;
        }
        
        stat[0]=timeout;
        sleep(1);
        return stat;
    }
};

int main() {
    srand(time(0));

    int windowSize, totalFrames;
    cout << "Input window size: ";
    cin >> windowSize;
    cout << "Input total no. of frames to send: ";
    cin >> totalFrames;

    GoBackNARQ GoBackNARQ(windowSize, totalFrames);
    GoBackNARQ.simulate();

    return 0;
}
