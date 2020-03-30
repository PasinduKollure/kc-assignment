#include <vector>
#include <iostream>

struct RangeCoordinate{
    int start;
    int end;

    RangeCoordinate(int s, int e) : start(s), end(e) {

    }

    RangeCoordinate() {

    }
};

enum OverlapCases {
    INSIDE,
    PARTIAL,
    NO_OVERLAP
};

enum AddRangeStatus {
    RANGE_NOT_FOUND,
    EXISTING_RANGE_MODIFIED,
    RANGE_EXISTS
};

class Container {
    std::vector<RangeCoordinate*> ranges;

    std::pair<int, RangeCoordinate*> isRangeWithin(int start, int end);
    RangeCoordinate mergeRange(int start, int end, RangeCoordinate* range);
    void splitRange(int start, int end, RangeCoordinate *node);
    void deletePartial(int start, int end);
    void addPartial(int start, int end);
    std::pair<int, RangeCoordinate> AddHelper(int start, int end);

public:
    Container();
    ~Container();

    int Add(int start, int end);
    bool Delete(int start, int end);
    std::vector<const RangeCoordinate*> Get(int start, int end);
    void print();

};