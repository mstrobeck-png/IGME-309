/* A01.cpp : 
MacKenzie Strobeck
Notes on A01
The only resources used was referring back to various content from DSA1, but all work is my own.

DONE(works properly)
- push
- pop
- GetSize
- IsEmpty

DONE(works somewhat)
- print -> displays data leak value

STRUGGLE
- sort
- rule of three
*/

#include "queue.h"


int main()
{
    queue<int> q(3);

    //intro to queue
    cout << "Queue: " << endl;
    cout << endl;

    //displays empty array and gets size
    q.getSize();
    q.isEmpty();
    q.print();

    //pushes in 3 data types and checks for size
    cout << "Pushing values " << endl;
    q.pushData(4);
    q.pushData(2);
    q.pushData(7); 
    q.getSize();
    q.isEmpty();
    q.print(); //not sure where the data leak is


    cout << endl;
    cout << "Popping 2 values" << endl;
    //pushes all three values out and gives us an array of 1
    q.popping();
    q.popping();
    q.getSize();
    //not sure why popped values were replaced with 0
    q.print();
    cout << endl;


    //lastly pushes three values back in and sorts
    cout << "Pushing & Sorting " << endl;
    q.pushData(7);
    q.pushData(1);
    q.print();
    q.sortValues();
    q.print();

}

