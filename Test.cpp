#include <iostream>
#include "Test.h"


int main() {
    Container rangeSet;

    // Test Adding
    std::cout << "Adding unique ranges" << std::endl;
    testAddIslands(100, 4, 0, rangeSet);
    testConcatenateStartRange(rangeSet);
    testConcatenateEndRange(rangeSet);
    testMergeExistingRanges(rangeSet);
    testMergeMultipleUniqueRanges(rangeSet);
    
    // Test Deleting
    testDeletingNonexistentRange(rangeSet);
    testPartiallyDeleteRanges(rangeSet);
    testPartiallyDeleteMultipleRanges(rangeSet);

    // Get range of ranges
    testGetRange(rangeSet);

    return 0;
}
