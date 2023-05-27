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
        ConstructUtil(0U, dataLen - 1U, 0U, arr);
    }

    SegmentTree(const SegmentTree& anotherTree) = delete;
    SegmentTree(SegmentTree&& anotherTree) : dataLen(anotherTree.dataLen){
        tree = anotherTree.tree;
        anotherTree.tree = NULL;
        anotherTree.dataLen = 0U;
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
        ConstructUtil(0U, dataLen - 1U, 0U, arr);
        return true;
    }

    void Update(const unsigned int index, const T& val) {
        if(index < dataLen) UpdateUtil(index, 0U, dataLen - 1U, 0U, val);
    }

    T GetRange(const unsigned int start, const unsigned int end) const {
        return GetRangeUtil(start, ((end < dataLen) ? end : (dataLen - 1U)), 0U, dataLen - 1U, 0U);
    }

    unsigned int size() const {
        return dataLen;
    }

private:
    const unsigned int dataLen;
    vector<T> *tree;

    void ConstructUtil(const unsigned int start, const unsigned int end, const unsigned long long segNode, const vector<T> &arr) {
        if(start == end) {
            (*tree)[segNode] = arr[start];
            return;
        }
        unsigned int mid = start + (end - start) / 2U;
        ConstructUtil(start, mid, segNode * 2U + 1U, arr);
        ConstructUtil(mid + 1U, end, segNode * 2U + 2U, arr);
        (*tree)[segNode] = (*tree)[segNode * 2U + 1U] + (*tree)[segNode * 2U + 2U];
    }

    void UpdateUtil(const unsigned int index, const unsigned long long rangeStart, const unsigned long long rangeEnd, const unsigned long long segNode, const T& val) {
        if((index < rangeStart) || (rangeEnd < index)) {
            return;
        }
        if(rangeStart == rangeEnd) {
            (*tree)[segNode] = val;
            return;
        }
        unsigned int rangeMid = rangeStart + (rangeEnd - rangeStart) / 2U;
        UpdateUtil(index, rangeStart, rangeMid, segNode * 2U + 1U, val);
        UpdateUtil(index, rangeMid + 1U, rangeEnd, segNode * 2U + 2U, val);
        (*tree)[segNode] = (*tree)[segNode * 2U + 1U] + (*tree)[segNode * 2U + 2U];
    }

    T GetRangeUtil(const unsigned int start, const unsigned int end, const unsigned long long rangeStart, const unsigned long long rangeEnd, const unsigned long long segNode) const {
        if(end < rangeStart || rangeEnd < start) {
            return T();
        }
        if(start <= rangeStart && rangeEnd <= end) {
            T ret;
            ret = (*tree)[segNode];
            return ret;
        }
        unsigned int rangeMid = rangeStart + (rangeEnd - rangeStart) / 2U;
        return T(GetRangeUtil(start, end, rangeStart, rangeMid, segNode * 2U + 1U) + GetRangeUtil(start, end, rangeMid + 1U, rangeEnd, segNode * 2U + 2U));
    }
};