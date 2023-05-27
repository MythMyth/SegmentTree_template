# SegmentTree_template
Segment Tree that using C++ template<br/>
typename T must support assignment and add operator<br/>
Assignment operator use to assignment only<br/>
Add operator is operator use to combine 2 node in segment tree, it could be normal add or another type of binary operator like max, min, ...<br/>
Example for an user defined typename T<br/>

```
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
```
