#include "Sequence.hpp"
#include "split.hpp"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

void testPoppingPushingElements()
{
    // Test push_front, pop front methods
    Sequence<int, std::string> sequence1 = Sequence<int, std::string>();

    assert(sequence1.isEmpty());
    assert(sequence1.getLength() == 0);

    sequence1.push_front(1, "One");
    assert(!sequence1.isEmpty());
    assert(sequence1.getLength() == 1);

    sequence1.push_front(2, "Two");
    assert(sequence1.getLength() == 2);
    assert(!sequence1.isEmpty());

    sequence1.pop_front();
    assert(sequence1.getLength() == 1);
    assert(!sequence1.isEmpty());

    sequence1.pop_front();
    assert(sequence1.getLength() == 0);
    assert(sequence1.isEmpty());

    // Test push_back, pop_back method
    Sequence<int, std::string> sequence2;

    sequence2.push_back(1, "One");
    assert(!sequence2.isEmpty());
    assert(sequence2.getLength() == 1);

    sequence2.push_back(2, "Two");
    assert(!sequence2.isEmpty());
    assert(sequence2.getLength() == 2);

    sequence2.pop_back();
    assert(!sequence2.isEmpty());
    assert(sequence2.getLength() == 1);

    sequence2.clear();
    assert(sequence2.getLength() == 0);
    assert(sequence2.isEmpty());

    cout
        << "Push front and push back tests passed successfully!" << endl;
}

void testCopyconstructor()
{
    // Create an original sequence
    Sequence<int, std::string> originalSeq;
    originalSeq.push_back(1, "one");
    originalSeq.push_back(2, "two");
    originalSeq.push_back(3, "three");

    // Test copy constructor
    Sequence<int, std::string> copiedSeq1 = originalSeq;
    assert(copiedSeq1.getLength() == originalSeq.getLength());
    assert(copiedSeq1.exists(1));
    assert(copiedSeq1.exists(2));
    assert(copiedSeq1.exists(3));

    // Modify the original sequence
    originalSeq.remove(2);
    assert(originalSeq.getLength() == 2);
    assert(originalSeq.exists(2) == false);

    // Check if the copied sequence remains unchanged
    assert(copiedSeq1.getLength() == 3);
    assert(copiedSeq1.exists(2));

    // Test copy assignment operator
    Sequence<int, std::string> copiedSeq2;
    copiedSeq2.push_back(4, "four");
    copiedSeq2.push_back(5, "five");
    copiedSeq2 = originalSeq;
    assert(copiedSeq2.getLength() == originalSeq.getLength());
    assert(copiedSeq2.exists(1));
    assert(copiedSeq2.exists(3));

    // Modify the original sequence again
    originalSeq.remove(1);
    assert(originalSeq.getLength() == 1);
    assert(originalSeq.exists(1) == false);

    // Check if the copied sequence remains unchanged
    assert(copiedSeq2.getLength() == 2);
    assert(copiedSeq2.exists(1));

    std::cout << "Copy constructor and operator= tests passed!" << std::endl;
}

void testIterator()
{
    // Create a sample sequence
    Sequence<int, std::string> sequence;
    sequence.push_back(1, "One");
    sequence.push_back(2, "Two");
    sequence.push_back(3, "Three");
    sequence.push_back(4, "Four");

    // Test Iterator methods and begin(), end() methods
    Sequence<int, std::string>::Iterator it = sequence.begin();
    Sequence<int, std::string>::Iterator endIterator = sequence.end();

    // Test equality and inequality operators
    assert(it == sequence.begin());
    assert(it.key() == 1);
    assert(it.info() == "One");
    assert(endIterator == sequence.end());
    assert(it != endIterator);
    assert(endIterator.info() == "Four");
    assert(endIterator.key() == 4);

    // Test copyconstructor

    Sequence<int, std::string>::Iterator copiedIterator = Sequence<int, std::string>::Iterator(it);

    assert(copiedIterator.key() == it.key());

    assert(copiedIterator == it);

    // Test prefix increment operator (++)
    ++it;
    assert(it.key() == 2);
    assert(it.info() == "Two");

    // Test postfix increment operator (++)
    it++;
    assert(it.key() == 3);
    assert(it.info() == "Three");

    // Test addition operator (+)
    it = it + 1;
    assert(it.key() == 4);
    assert(it.info() == "Four");

    assert(it == endIterator);

    // Test addition operator (+) with some interval
    copiedIterator = copiedIterator + 4;
    assert(copiedIterator == it);

    // Test incrementing the ending iterator
    it = it + 1;
    assert(it.key() == 4);
    assert(it.info() == "Four");

    std::cout
        << "Iterator tests passed successfully!" << std::endl;
}

void testFindingElements()
{
    // Sample key-value pairs for testing
    Sequence<int, std::string> sequence;
    sequence.push_back(1, "One");
    sequence.push_back(2, "Two");
    sequence.push_back(1, "One Again");
    sequence.push_back(3, "Three");

    // Test find method
    Sequence<int, std::string>::Iterator it;
    assert(sequence.find(it, 1)); // Find the first occurrence of key 1
    assert(it.key() == 1 && it.info() == "One");

    assert(sequence.find(it, 1, 2)); // Find the second occurrence of key 1
    assert(it.key() == 1 && it.info() == "One Again");

    assert(!sequence.find(it, 4)); // Key 4 does not exist

    // Test findBefore method
    Sequence<int, std::string>::Iterator beforeIt;
    assert(sequence.findBefore(beforeIt, 2)); // Find the node before key 2
    assert(beforeIt.key() == 1 && beforeIt.info() == "One");

    assert(!sequence.findBefore(beforeIt, 1)); // No node before the first occurrence of key 1
    assert(!sequence.findBefore(beforeIt, 4)); // Key 4 does not exist

    // Test occurrencesOf method
    assert(sequence.occurrencesOf(1) == 2); // Key 1 occurs twice
    assert(sequence.occurrencesOf(2) == 1); // Key 2 occurs once
    assert(sequence.occurrencesOf(4) == 0); // Key 4 does not exist

    // Test exists method
    assert(sequence.exists(1));  // Key 1 exists
    assert(sequence.exists(2));  // Key 2 exists
    assert(!sequence.exists(4)); // Key 4 does not exist

    std::cout << "Find elements tests passed successfully!" << std::endl;
}

void testRemove()
{
    Sequence<int, std::string> sequence;
    sequence.push_back(1, "One");
    sequence.push_back(2, "Two");
    sequence.push_back(3, "Three");

    // 1. Remove: element is the first one
    assert(sequence.remove(1) == true); // Remove the first element
    assert(sequence.getLength() == 2);
    assert(sequence.begin().key() == 2 && sequence.begin().info() == "Two");
    assert(sequence.end().key() == 3 && sequence.end().info() == "Three");
    sequence.push_front(1, "One");

    // 2. Remove: element is in the middle
    assert(sequence.remove(2) == true); // Remove from the middle
    assert(sequence.getLength() == 2);
    assert(sequence.begin().key() == 1 && sequence.begin().info() == "One");
    assert(sequence.end().key() == 3 && sequence.end().info() == "Three");

    // 3. Remove: element is the last one
    assert(sequence.remove(3) == true); // Remove the last element
    assert(sequence.getLength() == 1);
    assert(sequence.begin().key() == 1 && sequence.begin().info() == "One");
    assert(sequence.end().key() == 1 && sequence.end().info() == "One");

    // 4. Remove: sequence has only one element
    assert(sequence.remove(1) == true); // Remove the only element
    assert(sequence.isEmpty() == true);

    // 5. Remove: element not found in the empty sequence
    assert(sequence.remove(1) == false); // No element to remove\

    sequence.push_back(1, "One");
    sequence.push_back(1, "Second One");
    sequence.push_back(3, "Three");

    assert(sequence.remove(1, 2) == true); // remove element with occurrence 2
    assert(sequence.getLength() == 2);
    assert(sequence.begin().key() == 1 && sequence.begin().info() == "One");
    assert(sequence.end().key() == 3 && sequence.end().info() == "Three");

    std::cout << "Remove elements tests passed successfully!" << std::endl;
}

void testInsertAfter()
{
    Sequence<int, std::string> sequence;
    sequence.push_back(1, "One");
    sequence.push_back(3, "Three");
    Sequence<int, std::string>::Iterator it;

    // 1. Insert after: element is the first one
    assert(sequence.insert_after(2, "Two", 1) == true); // Insert after the first element
    assert(sequence.getLength() == 3);
    it = sequence.begin();
    assert(it.key() == 1 && it.info() == "One");
    it++;
    assert(it.key() == 2 && it.info() == "Two");
    assert(sequence.end().key() == 3 && sequence.end().info() == "Three");

    // 2. Insert after: element is in the middle
    assert(sequence.insert_after(4, "Four", 2) == true); // Insert after the middle element
    assert(sequence.getLength() == 4);
    assert(sequence.begin().key() == 1 && sequence.begin().info() == "One");
    assert(it.key() == 2 && it.info() == "Two");
    it++;
    assert(it.key() == 4 && it.info() == "Four");
    assert(sequence.end().key() == 3 && sequence.end().info() == "Three");

    // 3. Insert after: element is the last one
    assert(sequence.insert_after(5, "Five", 3) == true); // Insert after the last element
    assert(sequence.getLength() == 5);
    assert(sequence.begin().key() == 1 && sequence.begin().info() == "One");
    assert(it.key() == 4 && it.info() == "Four");
    it++;
    assert(it.key() == 3 && it.info() == "Three");
    assert(sequence.end().key() == 5 && sequence.end().info() == "Five");

    // 4. Insert after: sequence has only one element
    Sequence<int, std::string> singleElementSeq;
    singleElementSeq.push_back(1, "One");
    assert(singleElementSeq.insert_after(2, "Two", 1) == true); // Insert after the only element
    assert(singleElementSeq.getLength() == 2);
    assert(singleElementSeq.begin().key() == 1 && singleElementSeq.begin().info() == "One");
    assert(singleElementSeq.end().key() == 2 && singleElementSeq.end().info() == "Two");

    // 5. Insert after: empty sequence
    Sequence<int, std::string> emptySeq;
    assert(emptySeq.insert_after(1, "One", 1) == false); // No element to insert after

    std::cout << "Insert after tests passed successfully!" << std::endl;
}

void testInsertBefore()
{
    Sequence<int, std::string> sequence;
    sequence.push_back(1, "One");
    sequence.push_back(3, "Three");
    Sequence<int, std::string>::Iterator it;

    // 1. Insert before: element is the first one
    assert(sequence.insert_before(2, "Two", 1) == true); // Insert before the first element
    assert(sequence.getLength() == 3);
    it = sequence.begin();
    assert(it.key() == 2 && it.info() == "Two");
    it++;
    assert(it.key() == 1 && it.info() == "One");
    assert(sequence.end().key() == 3 && sequence.end().info() == "Three");

    // 2. Insert before: element is in the middle
    assert(sequence.insert_before(4, "Four", 1) == true); // Insert before the middle element
    assert(sequence.getLength() == 4);
    it = sequence.begin();
    assert(it.key() == 2 && it.info() == "Two");
    it++;
    assert(it.key() == 4 && it.info() == "Four");
    it++;
    assert(it.key() == 1 && it.info() == "One");
    assert(sequence.end().key() == 3 && sequence.end().info() == "Three");

    // 3. Insert before: element is the last one
    assert(sequence.insert_before(5, "Five", 3) == true); // Insert before the last element
    assert(sequence.getLength() == 5);
    it = sequence.begin();
    assert(it.key() == 2 && it.info() == "Two");
    it++;
    assert(it.key() == 4 && it.info() == "Four");
    it++;
    assert(it.key() == 1 && it.info() == "One");
    it++;
    assert(it.key() == 5 && it.info() == "Five");
    assert(sequence.end().key() == 3 && sequence.end().info() == "Three");

    // 4. Insert before: sequence has only one element
    Sequence<int, std::string> singleElementSeq;
    singleElementSeq.push_back(1, "One");
    assert(singleElementSeq.insert_before(2, "Two", 1) == true); // Insert before the only element
    assert(singleElementSeq.getLength() == 2);
    it = singleElementSeq.begin();
    assert(it.key() == 2 && it.info() == "Two");
    it++;
    assert(it.key() == 1 && it.info() == "One");

    // 5. Insert before: empty sequence
    Sequence<int, std::string> emptySeq;
    assert(emptySeq.insert_before(1, "One", 1) == false); // No element to insert before

    std::cout << "Insert before tests passed successfully!" << std::endl;
}

void test_split_pos()
{
    Sequence<int, int> seq;
    for (int i = 0; i < 25; ++i)
    {
        seq.push_back(i, i);
    }

    Sequence<int, int> seq1, seq2;

    // Test split_pos function
    split_pos(seq, 2, 2, 3, 4, seq1, seq2);
    // Check seq
    assert(seq.getLength() == 5);
    assert(seq.exists(0));
    assert(seq.exists(1));
    assert(seq.exists(22));
    assert(seq.exists(23));
    assert(seq.exists(24));

    // Check seq1
    assert(seq1.getLength() == 8);
    assert(seq1.exists(2));
    assert(seq1.exists(3));
    assert(seq1.exists(7));
    assert(seq1.exists(8));
    assert(seq1.exists(12));
    assert(seq1.exists(13));
    assert(seq1.exists(17));
    assert(seq1.exists(18));

    // Check seq2
    assert(seq2.getLength() == 12);
    assert(seq2.exists(4));
    assert(seq2.exists(5));
    assert(seq2.exists(6));
    assert(seq2.exists(9));
    assert(seq2.exists(10));
    assert(seq2.exists(11));
    assert(seq2.exists(14));
    assert(seq2.exists(15));
    assert(seq2.exists(16));
    assert(seq2.exists(19));
    assert(seq2.exists(20));
    assert(seq2.exists(21));

    std::cout << "split_pos function tests passed!" << std::endl;
}
int main()
{

    testPoppingPushingElements();
    testCopyconstructor();
    testIterator();
    testFindingElements();
    testRemove();
    testInsertAfter();
    testInsertBefore();
    test_split_pos();
    cout
        << "End of tests!" << endl;
}