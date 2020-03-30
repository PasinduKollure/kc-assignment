#include "Container.h"

Container::Container() {

}

Container::~Container() {

}

int Container::Add(int start, int end) {
    if (end <= start) {
        return 0;
    }

    #ifdef DEBUG_INFO
    std::cout << "Add(" << start << "," << end << ")" << std::endl; 
    #endif

    std::pair<int, RangeCoordinate> ret = AddHelper(start, end);

    while ( ret.first != RANGE_NOT_FOUND ) {
        ret = AddHelper(ret.second.start, ret.second.end);
    }

    ranges.push_back(RangeCoordinate(ret.second.start, ret.second.end));
    // std::cout << "new block: " << start << " " << end << std::endl;

    return 1;
}

std::pair<int, RangeCoordinate> Container::AddHelper(int start, int end) {
    bool startInRange;
    bool endInRange;
    std::pair<int, RangeCoordinate> ret;

    for ( int i = 0; i < ranges.size(); i++ ) {
        startInRange = (start <= ranges[i].end && start >= ranges[i].start);
        endInRange = (end <= ranges[i].end && end >= ranges[i].start);

        if ( start <= ranges[i].start && end >= ranges[i].end ) { // encloses a node
            // std::cout << "Enclose: [";
            // std::cout << start << "," << end << "]" << std::endl;
            ranges[i].start = start;
            ranges[i].end = end;

            ret.first = EXISTING_RANGE_MODIFIED;
            ret.second = ranges[i];
            ranges.erase(ranges.begin()+i);

            return ret;
        } else if ( startInRange && end >= ranges[i].end ) { // stretch end of node
            // std::cout << "Strect end: [";
            // std::cout << start << "," << end << "]" << std::endl;
            ranges[i].end = end;

            ret.first = EXISTING_RANGE_MODIFIED;
            ret.second = ranges[i];
            ranges.erase(ranges.begin()+i);

            return ret;
        } else if ( endInRange && start <= ranges[i].start ) { // stretch start of node
            // std::cout << "Strech start: [";
            // std::cout << start << "," << end << "]" << std::endl;
            ranges[i].start = start;
            
            ret.first = EXISTING_RANGE_MODIFIED;
            ret.second = ranges[i];
            ranges.erase(ranges.begin()+i);
            
            return ret;
        } 
    }

    ret.first = RANGE_NOT_FOUND;
    ret.second.start = start;
    ret.second.end = end;
    return ret;
}

bool Container::Delete(int start, int end) {
    if ( end <= start ) {
        return 0;
    }

    bool startInRange;
    bool endInRange;

    #ifdef DEBUG_INFO
    std::cout << "Delete(" << start << "," << end << ")" << std::endl; 
    #endif

    for (int i = 0; i < ranges.size(); i++) {
        startInRange = (start <= ranges[i].end && start >= ranges[i].start);
        endInRange = (end <= ranges[i].end && end >= ranges[i].start);

        if (start <= ranges[i].start && end >= ranges[i].end) {
            ranges.erase(ranges.begin()+i);
            i--;

        } else if ( startInRange && endInRange ) { // split node
            ranges.push_back(RangeCoordinate(end, ranges[i].end));
            // std::cout << "Split: [";
            // std::cout << ranges[i].start << "," << ranges[i].end << "]" << std::endl;
            ranges[i].end = start;

        } else if ( startInRange ) { // shorten end
            // std::cout << "Removed: [";
            // std::cout << ranges[i].start << "," << ranges[i].end << "]" << std::endl;
            ranges[i].end = start;

            if ( ranges[i].start == ranges[i].end ) {
                ranges.erase(ranges.begin()+i);
                i--;
            }

        } else if ( endInRange ) { // shorten start
            // std::cout << "Removed: [";
            // std::cout << ranges[i].start << "," << ranges[i].end << "]" << std::endl;
            ranges[i].start = end;

            if ( ranges[i].start == ranges[i].end ) {
                ranges.erase(ranges.begin()+i);
                i--;
            }
        }
    }

    return 1;
}

std::vector<RangeCoordinate> Container::Get(int start, int end) {
    std::vector<RangeCoordinate> ret;

    for ( auto r: ranges) {
        if ( start <= r.start && end >= r.end) {
            ret.push_back(r);
        }
    }

    return ret;
}

void Container::clear() {
    ranges.clear();
}

void Container::print(std::string title) {
    std::cout << title;
    for (auto r: ranges) {
        std::cout << "[" << r.start << "," << r.end << "] ";
    }
    std::cout << std::endl;
}