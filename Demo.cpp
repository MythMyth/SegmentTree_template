#include <bits/stdc++.h>
#include "SegmentTree.h"

using namespace std;

class intWrap {
public:
    intWrap() : val(0) {}
    intWrap(int i) : val(i) {}
    intWrap& operator= (const intWrap& another) {
        val = another.val;
        return *this;
    }

    intWrap operator+ (const intWrap& another) {
        return intWrap(max(this->val, another.val));
    }

    friend istream& operator>> (istream& input, intWrap &instance) {
        input >> instance.val;
        return input;
    }

    friend ostream& operator<< (ostream& output, intWrap &instance) {
        output << instance.val;
        return output;
    }
private:
    int val;
};

int main()
{
    cout << "Len: ";
    unsigned int len; cin >> len;
    vector<intWrap> arr(len);
    for(unsigned int i = 0; i < len; ++i) {
        cin >> arr[i];
    }
    SegmentTree<intWrap> tree(arr);
    char command = ' ';
    do {
        cin >> command;
        switch(command) {
        case 'r':
        {
            unsigned int index = 0;
            int val = 0;
            cin >> index >> val;
            arr[index] = val;
            tree.Update(index, arr[index]);
            cout << endl;
            for(int i = 0; i < len; ++i) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
            break;
        case 'g':
        {
            unsigned int s, e;
            cin >> s >> e;
            if(s <= e) {
                intWrap i = tree.GetRange(s, e);
                cout << i << "\n";
            }
        }
            break;
        }
    }
    while(command != 'e');
}

































