//#include <bits/stdc++.h>
#include <iostream>
#include <queue>

using namespace std;

void empty_q(queue<int> &q)
{
    while(!q.empty() ) q.pop();
}

int main()
{
    queue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);

    cout << " queue front:" << q.front() << endl;

    // code in comment below does not compile
    // cout << "pop return code: " << q.pop() << endl;

    cout << "pop 1 item" << endl; q.pop();
    cout << " queue front:" << q.front() << endl;

    cout << "pop 1 item" << endl; q.pop();
    cout << " queue front:" << q.front() << endl;


    q.push(4);

    q.push(5);
    q.push(6);

    cout << "queue size:" << q.size() << endl;

    empty_q(q);

    cout << "queue size:" << q.size() << endl;
}



