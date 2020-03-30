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

    rangeSet.Add(1,5);
    addRanges(100, 5, rangeSet);
    rangeSet.print("Adding Ranges");
    
    rangeSet.Delete(0,60);
    rangeSet.print("Removing [0,60]");

    return 0;
}
