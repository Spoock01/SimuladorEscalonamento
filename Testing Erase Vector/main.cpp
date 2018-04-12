#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> test;
    int i;


    for(i = 0; i < 10; i++)
        test.push_back(i);

    test.erase(test.begin(), test.begin() + 2);


    for(i = 0; i < test.size(); i++)
        cout << test[i] << endl;

    return 0;
}
