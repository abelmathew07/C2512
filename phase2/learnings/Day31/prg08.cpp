//race condition example - with fix
#include <iostream>
#include <thread>
using namespace std;

const long long TIMES = 5000000LL;

long long count1, count2;


void counter1() {
    for(long long I = 0; I < TIMES; I++) {
        count1 ++;
    }
}
void counter2() {
    for(long long I = 0; I < TIMES; I++) {
        count2 ++;
    }
}
int main() {
    thread thrCounter1(counter1);
    thread thrCounter2(counter2);
    thrCounter1.join();
    thrCounter2.join();
    cout << count1 + count2;
    return 0;
}