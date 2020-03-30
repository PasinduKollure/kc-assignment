#include "Container.h"

void testAddIslands(int length, int islands, int startingIndex, Container &set) {
    set.clear();

    std::cout << "Setting up range set for the next test" << std::endl;

    int increment = (length/islands)/2;
    for (int i = startingIndex; i < (length-increment); i+= increment*2 ) {
        set.Add(i, i+increment);
    }
}

void testConcatenateStartRange(Container &set) {
    set.clear();
    testAddIslands(100, 4, 0, set);

    // Starting Set: [0,12] [24,36] [48,60] [72,84]
    std::cout << std::endl << "TEST: Stretch range sets from their start points" << std::endl;
    set.print("Starting Range Set: ");
    

    set.Add(18,30); // partial overlap case
    set.Add(40,48); // boundary case
    set.Add(40,60); // adding redundant range
    set.Add(72,100); // new range completely overlaps existing range
    set.print("Final Range Set: ");
    // expected output: [0,12] [18,36] [40,60] [72,100]
}

void testConcatenateEndRange(Container &set) {
    set.clear();
    testAddIslands(100, 4, 0, set);
    
    // Starting Set: [0,12] [24,36] [48,60] [72,84]
    std::cout << std::endl << "TEST: Stretch range sets from their end points" << std::endl;
    set.print("Starting Range Set: ");
    set.Add(-5,12); // negative range
    set.Add(30,40); // partial overlap case
    set.Add(60,70); // boundary case
    set.Add(84,100); // adding redundant rangeSet
    set.print("Final Range Set: ");
    // expected output: [-5,12] [24,40] [48,70] [72,100]
}

void testMergeExistingRanges(Container &set) {
    set.clear();
    testAddIslands(100, 4, 0, set);

    // Starting Set: [0,12] [24,36] [48,60] [72,84]
    std::cout << std::endl << "TEST: Merge existing ranges" << std::endl;
    set.print("Starting Range Set: ");
    set.Add(10,26); // Partially overlap 2 ranges
    set.Add(36,48); // Touching boundaries of 2 ranges
    set.Add(2,30); // Redundant range
    set.print("Final Range Set: ");
    // Expected output: [72,84] [0,60] [2,30]
}

void testMergeMultipleUniqueRanges(Container &set) {
    set.clear();
    testAddIslands(200,8,0,set);

    /* Starting Set: [0,12] [24,36] [48,60] [72,84] 
                     [96,108] [120,132] [144,156] [168,190]
    */
    std::cout << std::endl << "TEST: Merge mulitple unique range sets" << std::endl;
    set.print("Starting Range Set: ");
    set.Add(0,84);
    set.Add(99,200);
    set.print("Final Range Set: ");
    // Expected Set: [0,84] [99,200]
}

void testDeletingNonexistentRange(Container &set) {
    set.clear();
    testAddIslands(100, 4, 0, set);

    // Starting Set: [0,12] [24,36] [48,60] [72,84]
    std::cout << std::endl << "TEST: Delete nonexistent ranges" << std::endl;
    set.print("Starting Range Set: ");
    set.Delete(13,5);
    set.Delete(-10,-1);
    set.print("Final Range Set: ");
    // Expected Set: [0,12] [24,36] [48,60] [72,84]
}

void testPartiallyDeleteRanges(Container &set) {
    set.clear();
    testAddIslands(100, 4, 0, set);

    // Starting Set: [0,12] [24,36] [48,60] [72,84]
    std::cout << std::endl << "TEST: Delete partially covered ranges" << std::endl;
    set.print("Starting Range Set: ");
    set.Delete(-1,6); // delete staring range
    set.Delete(20,30); // delete starting range
    set.Delete(50,70); // delete end range
    set.Delete(80,100); // delete end range
    set.print("Final Range Set: ");
    // Expected Set: [6,12] [30,36] [48,50] [72,80]
}

void testPartiallyDeleteMultipleRanges(Container &set) {
    set.clear();
    testAddIslands(200, 8, 0, set);

    /* Starting Set: [0,12] [24,36] [48,60] [72,84]
                    [96,108] [120,132] [144,156] [168,180]
    */
    std::cout << std::endl << "TEST: Delete region with multiple ranges" << std::endl;
    set.print("Starting Range Set: ");
    set.Delete(10,26); // delete range covers 2 ranges
    set.Delete(36,48); // delete range covers 2 ranges, boundary to boundary
    set.Delete(75,80); // split 1 range into 2 new ranges
    set.Delete(96,200); // delete multiple ranges
    set.print("Final Range Set: ");
    /* Expected Set: [0,10] [26,36] [48,60] [72,75] [80,84]
                     [120,132] [144,156] [168,180]
    */
}

void printReturnedList(std::vector<RangeCoordinate> ret) {
    for (int i = 0; i < ret.size(); i++) {
        std::cout << "[" << ret[i].start << "," << ret[i].end << "] ";
    }

    std::cout << std::endl;
}

void testGetRange(Container &set) {
    int start;
    int end;
    set.clear();
    testAddIslands(100,4,0,set);

    // Starting Set: [0,12] [24,36] [48,60] [72,84]
    std::cout << std::endl << "TEST: Get()" << std::endl;

    start = 0;
    end = 11;
    std::cout << "The specified range (" << start << "," << end << ") is a fraction of an existing range" << std::endl;
    std::vector<RangeCoordinate> ret = set.Get(0,11);
    printReturnedList(ret);

    end = 36;
    std::cout << std::endl << "The specified range (" << start << "," << end << ") intersects the boundaries of ranges" << std::endl;
    ret = set.Get(0,36);
    printReturnedList(ret);

    start = -1;
    end = 100;
    std::cout << std::endl << "The specified range (" << start << "," << end << ") contains multiple ranges" << std::endl;
    ret = set.Get(-1,100);
    printReturnedList(ret);    
}

void invalidInput(Container &set) {
    set.clear();
    testAddIslands(100, 4, 0, set);
    
    // Starting Set: [0,12] [24,36] [48,60] [72,84]
    set.Add(5,3); // start > end
    set.Add(5,5); // start == end

    set.Delete(12,0); // start > end
    set.Delete(11,11);
}