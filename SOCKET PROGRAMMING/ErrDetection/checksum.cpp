#include <bits/stdc++.h>

using namespace std;


uint8_t checksumgen(uint32_t dataword) {
    uint8_t checksum = 0;
    for (int i = 0; i < 4; ++i) {
        checksum += (dataword >> (i * 8)) & 0xFF; 
    }
    return ~checksum; 
}


uint64_t createCodeword(uint32_t dataword, uint8_t checksum) {
    uint64_t codeword = static_cast<uint64_t>(dataword) << 8 | checksum;
    return codeword;
}


bool verifyChecksum(uint64_t codeword) {
    uint32_t dataword = (codeword >> 8) & 0xFFFFFFFF;
    uint8_t receivedChecksum = codeword & 0xFF;
    uint8_t computedChecksum = checksumgen(dataword);
    return receivedChecksum == computedChecksum;
}

int main() {

    uint32_t dataword, datawordcpy;
    cin>>dataword;
    datawordcpy = dataword;
    uint8_t checksum = checksumgen(dataword);
    uint64_t codeword = createCodeword(dataword, checksum);

    cout << "Sender: " << endl;
    cout << "Dataword: " << bitset<32>(datawordcpy) << endl;
    cout << "Checksum: " << bitset<8>(checksum) << endl;
    cout << "Codeword: " << bitset<40>(codeword) << endl << endl;

    cout << "Receiver: " << endl;
    bool error = !verifyChecksum(codeword);
    if (error) {
        cout << "Checksum Error Detected!" << endl;
    } else {
        cout << "No Checksum Error." << endl;
    }

    return 0;
}