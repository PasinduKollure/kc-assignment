#include <vector>

struct RangeCoordinate{
    int start;
    int end;
};

enum OverlapCases {
    STRETCH_START,
    INSIDE,
    STRETCH_END,
    NO_OVERLAP
};

template<typename T>
class Container {
    std::vector<T*> ranges;
    int len;

    std::pair<int, RangeCoordinate*> isUnique(int start, int end) {
        std::pair<int, RangeCoordinate*> range(NO_OVERLAP, NULL);
        
        for ( auto r:ranges ) {
            bool startBoundary = (start >= r->start);
            bool endBoundary = (end <= r->end);

            if ( startBoundary || endBoundary ) {
                if ( startBoundary && endBoundary ) {
                    range.first = INSIDE;
                    range.second = NULL;
                    return range;
                } else if ( !startBoundary && endBoundary ) {
                    range.first = STRETCH_START;
                    range.second = r; 
                } else if ( startBoundary && !endBoundary ) {
                    range.first = STRETCH_END;
                    range.second = r;
                }
            }
        }

        return range;
    }

    void mergeRange(int start, int end, std::pair<int, RangeCoordinate*> range) {
        
    }

public:
    Container();
    ~Container();

    int add(int start, int end) {
        if (end <= start) {
            return 0;
        } else if ( isExist(start, end) ) {

        }

        RangeCoordinate* range = new RangeCoordinate;
        range->start = start;
        range->end = end;

        ranges.push_back(range);
    }

    void remove(int start, int end) {

    }

    void get(int start, int end) {

    }

};