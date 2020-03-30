#include <vector>

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

template<typename T>
class Container {
    std::vector<T*> ranges;
    int len;

    /*
        nullptr: if range is not unique, if unique range
    */
    std::pair<int, RangeCoordinate*> isRangeWithin(int start, int end) {
        RangeCoordinate* range;
        std::pair<int, RangeCoordinate*> ret;
        ret.first = NO_OVERLAP;
        ret.second = nullptr;
        
        for ( auto r:ranges ) {
            bool startInRange = (start >= r->start && start <= r->end);
            bool endInRange = (end >= r->start && end <= r->end);

            if ( startInRange && endInRange ) {
                ret.first = INSIDE;
                ret.second = r;
            } else if ( endInRange && (start <= r->start) ) {
                ret.first = PARTIAL;
                ret.second = r;
            } else if ( startInRange && (end >= r->end) ) {
                ret.first = PARTIAL;
                ret.second = r;
            }
        }

        return ret;
    }

    RangeCoordinate mergeRange(int start, int end, RangeCoordinate* range) {
        bool startInRange = (start >= range->start && start <= range->end);
        bool endInRange = (end >= range->start && end <= range->end);
        RangeCoordinate ret;

        if ( endInRange ) {
            range->start = start;
        } else if ( startInRange ) {
            range->end = end;
        }

        ret.start = range->start;
        ret.end = range->end;
        return ret;
    }

    bool splitRange(int start, int end, RangeCoordinate *node) {
        RangeCoordinate* newNode = new RangeCoordinate(end, node->end);
        node->end = start;
        ranges.push_back(newNode);
    }

    bool deletePartial(int start, int end) {
        bool startInRange;
        bool endInRange;

        for ( auto r: ranges) {
            startInRange = (start < r->end && start > r->start);
            endInRange = (end < r->end && end > r->start);

            if ( startInRange ) {
                r->end = start;
            } else if ( endInRange ) {
                r->start = end;
            }
        }
    }

    bool addPartial(int start, int end) {
        bool startInRange;
        bool endInRange;

        for ( auto r: ranges) {
            startInRange = (start <= r->end && start >= r->start); //stretch end, inside
            endInRange = (end <= r->end && end >= r->start);

            if ( startInRange ) {
                r->end = end;
            } else if ( endInRange ) {
                r->start = start;
            }
        }
    }

public:
    Container();
    ~Container();

    /* Returns 1 if a unique range has been merged 

    */
    int Add(int start, int end) {
        std::pair<int, RangeCoordinate*> ret;
        RangeCoordinate* range;

        if (end <= start) {
            return 0;
        }

        ret = isRangeWithin(start, end);
        range = ret.second;

        if (ret.first == PARTIAL) {
            addPartial(start, end);
        } else if (ret.first == NO_OVERLAP) {
            ranges.push_back(new RangeCoordinate(start, end));
        } else {
            assert(0);
        }

        return 1;
    }

    bool Delete(int start, int end) {
        if ( end <= start ) {
            return 0;
        }

        bool startInRange;
        bool endInRange;
        std::pair<int, RangeCoordinate*> ret;
        RangeCoordinate* range;

        ret = isRangeWithin(start, end);
        range = ret.second;

        if (ret.first == INSIDE) {
            splitRange(start, end, ret.second);
        } else if (ret.first == PARTIAL) {
            deletePartial(start, end);
        } else {
            assert(0);
        }

        return 1;
    }

    std::vector<const RangeCoordinate*> Get(int start, int end) {
        std::vector<const RangeCoordinate*> ret;

        for ( auto r: ranges) {
            if ( start <= r->start && end >= r->end) {
                ret.push_back(r);
            }
        }

        return ret;
    }

};