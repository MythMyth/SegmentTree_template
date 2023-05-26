#include <bits/stdc++.h>

using namespace std;

template<typename T>
class SegmentTree {
public:
    explicit SegmentTree(const unsigned int len) : dataLen(len), tree(NULL) {
        const unsigned int treeHeight = (unsigned int)ceil(log2(dataLen));
        const unsigned long long treeLen = ((unsigned long long)pow(2U, treeHeight)) * 2U - 1U;
        tree = new vector<T>(treeLen);
    }

    explicit SegmentTree(const vector<T>& arr) : dataLen(arr.size()), tree(NULL) {
        const unsigned int treeHeight = (unsigned int)ceil(log2(arr.size()));
        const unsigned long long treeLen = ((unsigned long long)pow(2U, treeHeight)) * 2U - 1U;
        tree = new vector<T>(treeLen);
        constructUtil(0U, dataLen - 1U, 0U, arr);
    }

    SegmentTree(const SegmentTree& anotherTree) = delete;
    SegmentTree(SegmentTree&& anotherTree) {
        dataLen = anotherTree.dataLen;
        tree = anotherTree.tree;
        anotherTree.tree = NULL;
    }

    SegmentTree& operator =(const SegmentTree& anotherTree) = delete;
    SegmentTree& operator =(SegmentTree&& anotherTree) {
        dataLen = anotherTree.dataLen;
        tree = anotherTree.tree;
        anotherTree.tree = NULL;
        return this;
    }

    virtual ~SegmentTree() {
        if(tree != NULL) {
            delete tree;
            tree = NULL;
        }
    }

    bool SetDataArr(const vector<T> &arr) {
        if(tree != NULL) {
            return false;
        }
        if(arr.size() < dataLen) {
            dataLen = arr.size();
        }
        constructUtil(0U, dataLen - 1U, 0U, arr);
        return true;
    }

    void Update(unsigned int start, unsigned int end, const T& val) {
        UpdateUtil(start, end, 0U, dataLen - 1U, 0U, val);
    }

    T& GetRange(unsigned int start, unsigned int end) {
        return move(GetRangeUtil(start, end, 0U, dataLen - 1U, 0U));
    }

private:
    unsigned int dataLen;
    vector<T> *tree;

    void constructUtil(unsigned int start, unsigned int end, unsigned long long segNode, vector<T> &arr) {
        if(start == end) {
            (*tree)[segNode] = arr[start];
            return;
        }
        unsigned int mid = start + (end - start) / 2U;
        constructUtil(start, mid, segNode * 2U + 1U, arr);
        constructUtil(mid + 1U, end, segNode * 2U + 2U, arr);
        (*tree)[segNode] = (*tree)[segNode * 2U + 1U] + (*tree)[segNode * 2U + 2U];
    }

    void UpdateUtil(unsigned int start, unsigned int end, unsigned long long rangeStart, unsigned long long rangeEnd, unsigned long long segNode, const T& val) {
        if((end < rangeStart) || (rangeEnd < start)) {
            return;
        }
        if(start <= rangeStart && rangeEnd <= end) {
            (*tree)[segNode] = val * (rangeEnd - rangeStart);
            return;
        }
        unsigned int rangeMid = rangeStart + (rangeEnd - rangeStart) / 2U;
        UpdateUtil(start, end, rangeStart, rangeMid, segNode * 2U + 1U, val);
        UpdateUtil(start, end, rangeMid + 1U, rangeEnd, segNode * 2U + 2U, val);
        (*tree)[segNode] = (*tree)[segNode * 2U + 1U] + (*tree)[segNode * 2U + 2U];
    }

    T& GetRangeUtil(unsigned int start, unsigned int end, unsigned long long rangeStart, unsigned long long rangeEnd, unsigned long long segNode) {
        T ret = T();
        if(end < rangeStart || rangeEnd < start) {
            return move(ret);
        }
        if(start <= rangeStart && rangeEnd <= end) {
            ret = (*tree)[segNode];
            return move(ret);
        }
        unsigned int rangeMid = rangeStart + (rangeEnd - rangeStart) / 2U;
        ret += GetRangeUtil(start, end, rangeStart, rangeMid, segNode * 2U + 1U);
        ret += GetRangeUtil(start, end, rangeMid + 1U, rangeEnd, segNode * 2U + 2U);
        return move(ret);
    }
};