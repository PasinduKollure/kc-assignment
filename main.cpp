#include <iostream>
#include "Container.h"

void addRanges(int length, int groups, Container &set) {
    int increment = length/groups;
    for (int i = 0; i < length; i+= increment*2 ) {
        set.Add(i, i+increment);
    }
}

int main() {
    Container rangeSet;

    rangeSet.print();
    rangeSet.Add(1,5);

    addRanges(100, 5, rangeSet);
    rangeSet.print();

    return 0;
}
