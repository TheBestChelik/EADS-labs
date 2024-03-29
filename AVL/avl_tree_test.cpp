#include "avl_tree.h"
#include <iostream>
#include <cassert>
#include "avl_tree_test.h"

using namespace std;
void test_clear_get_size()
{
    avl_tree<int, std::string> tree;
    assert(tree.getSize() == 0);
    assert(tree.empty());
    tree.insert(10, "A");
    tree.insert(5, "B");
    tree.insert(15, "C");
    tree.insert(2, "D");
    tree.insert(8, "E");
    tree.insert(12, "F");
    tree.insert(18, "G");
    assert(tree.getSize() == 7);
    tree.clear();
    assert(tree.empty());
    assert(tree.getSize() == 0);
    cout << "All tests clear and get size tests passed" << endl;
}

void test_insert_find()
{
    avl_tree<int, std::string> tree;

    assert(tree.empty());
    assert(tree.getSize() == 0);
    tree.insert(10, "Apple");
    assert(tree.isBalanced());
    assert(tree.getSize() == 1);
    tree.insert(5, "Banana");
    assert(tree.isBalanced());
    assert(tree.getSize() == 2);
    tree.insert(15, "Cherry");
    assert(tree.isBalanced());
    assert(tree.getSize() == 3);

    assert(tree.find(10));
    assert(tree.find(5));
    assert(tree.find(15));

    assert(tree.find(11) == false);

    cout << "All tests insert and find tests passed" << endl;
}

void test_insert_get()
{
    avl_tree<int, std::string> tree;

    tree.insert(10, "Apple");
    tree.insert(5, "Banana");
    tree.insert(15, "Cherry");
    assert(tree.isBalanced());
    assert(tree.getSize() == 3);

    assert(tree[10] == "Apple");
    assert(tree[5] == "Banana");
    assert(tree[15] == "Cherry");

    tree.insert(10, "Orange");
    assert(tree.getSize() == 3);

    assert(tree[10] == "Orange");

    tree.insert(10, "Grapes", [](const std::string &oldInfo, const std::string &newInfo)
                { return oldInfo + newInfo; });
    assert(tree.getSize() == 3);

    assert(tree[10] == "OrangeGrapes");

    cout << "All tests insert and get tests passed" << endl;
}

void test_remove()
{
    avl_tree<int, std::string> tree;
    tree.insert(10, "A");
    tree.insert(5, "B");
    tree.insert(15, "C");
    tree.insert(2, "D");
    tree.insert(8, "E");
    tree.insert(12, "F");
    tree.insert(18, "G");

    assert(tree.remove(2));
    assert(!tree.find(2));
    assert(tree.isBalanced());
    assert(tree.getSize() == 6);

    assert(tree.remove(5));
    assert(!tree.find(5));
    assert(tree.isBalanced());
    assert(tree.getSize() == 5);

    assert(tree.remove(15));
    assert(!tree.find(15));
    assert(tree.isBalanced());
    assert(tree.getSize() == 4);

    assert(!tree.remove(100));
    assert(tree.isBalanced());
    assert(tree.getSize() == 4);

    assert(tree.remove(10));
    assert(!tree.find(10));
    assert(tree.isBalanced());
    assert(tree.getSize() == 3);
    cout << "All tests passed!" << endl;
}

void test_assignment_operator()
{

    avl_tree<int, std::string> tree;
    tree.insert(10, "A");
    tree.insert(5, "B");
    tree.insert(15, "C");
    tree.insert(2, "D");
    tree.insert(8, "E");
    tree.insert(12, "F");
    tree.insert(18, "G");

    avl_tree<int, std::string> tree2;
    assert(tree2.getSize() == 0);
    assert(tree2.empty());

    tree2 = tree;

    assert(tree.getSize() == tree2.getSize());
    assert(tree2.isBalanced());

    assert(tree[10] == tree2[10]);
    assert(tree[5] == tree2[5]);
    assert(tree[2] == tree2[2]);
    assert(tree[18] == tree2[18]);

    tree2[10] = "HelloWord!";
    assert(tree2[10] == "HelloWord!");
    assert(tree[10] == "A");

    tree2.remove(10);
    assert(tree2.find(10) == false);
    assert(tree.find(10) == true);

    cout << "All tests passed!" << endl;
}

void test_copyconstructor()
{

    avl_tree<int, std::string> tree;
    tree.insert(10, "A");
    tree.insert(5, "B");
    tree.insert(15, "C");
    tree.insert(2, "D");
    tree.insert(8, "E");
    tree.insert(12, "F");
    tree.insert(18, "G");

    avl_tree<int, std::string> tree2 = tree;

    assert(tree[10] == tree2[10]);
    assert(tree[5] == tree2[5]);
    assert(tree[2] == tree2[2]);
    assert(tree[18] == tree2[18]);

    tree2[10] = "HelloWord!";
    assert(tree2[10] == "HelloWord!");
    assert(tree[10] == "A");

    tree2.remove(10);
    assert(tree2.find(10) == false);
    assert(tree.find(10) == true);

    cout << "All tests passed!" << endl;
}

void test_print()
{
    avl_tree<int, std::string> tree;
    tree.insert(10, "A");
    tree.insert(5, "B");
    tree.insert(15, "C");
    tree.insert(2, "D");
    tree.insert(8, "E");
    tree.insert(12, "F");
    tree.insert(18, "G");

    // Use ostringstream to capture the output
    std::ostringstream output;
    output << tree;

    // Check the printed output
    std::string expectedOutput =
        "            18:G\n"
        "      15:C\n"
        "            12:F\n"
        " 10:A\n"
        "            8:E\n"
        "      5:B\n"
        "            2:D\n";

    assert(output.str() == expectedOutput);

    std::cout << "Print test passed!" << std::endl;
}

void test_get_largest()
{
    avl_tree<int, std::string> tree;
    tree.insert(10, "A");
    tree.insert(5, "B");
    tree.insert(15, "C");
    tree.insert(2, "D");
    tree.insert(8, "E");
    tree.insert(12, "F");
    tree.insert(18, "G");

    int n = 3;
    std::vector<pair<int, string>> largestElements = tree.getLargest(n);

    std::vector<pair<int, string>> expectedElements = {pair<int, string>(18, "G"), pair<int, string>(15, "C"), pair<int, string>(12, "F")};

    assert(largestElements == expectedElements);

    largestElements = tree.getLargest(0);
    expectedElements = {};
    assert(largestElements == expectedElements);

    largestElements = tree.getLargest(10); // more then in array
    expectedElements = {pair<int, string>(18, "G"), pair<int, string>(15, "C"), pair<int, string>(12, "F"),
                        pair<int, string>(10, "A"), pair<int, string>(8, "E"), pair<int, string>(5, "B"), pair<int, string>(2, "D")};
    assert(largestElements == expectedElements);

    cout << "All get largest tests passed!" << endl;
}

void test_get_smallest()
{
    avl_tree<int, std::string> tree;
    tree.insert(10, "A");
    tree.insert(5, "B");
    tree.insert(15, "C");
    tree.insert(2, "D");
    tree.insert(8, "E");
    tree.insert(12, "F");
    tree.insert(18, "G");

    int n = 3;
    std::vector<std::pair<int, std::string>> smallestElements = tree.getSmallest(n);

    std::vector<std::pair<int, std::string>> expectedElements = {
        make_pair(2, "D"),
        make_pair(5, "B"),
        make_pair(8, "E")};

    assert(smallestElements == expectedElements);

    smallestElements = tree.getSmallest(0);
    expectedElements = {};
    assert(smallestElements == expectedElements);

    smallestElements = tree.getSmallest(10); // more than in the array
    expectedElements = {
        make_pair(2, "D"),
        make_pair(5, "B"),
        make_pair(8, "E"),
        make_pair(10, "A"),
        make_pair(12, "F"),
        make_pair(15, "C"),
        make_pair(18, "G")};

    assert(smallestElements == expectedElements);

    std::cout << "All get smallest tests passed!" << std::endl;
}

void test_for_each()
{
    avl_tree<int, std::string> tree;
    tree.insert(10, "A");
    tree.insert(5, "B");
    tree.insert(15, "C");
    tree.insert(2, "D");
    tree.insert(8, "E");
    tree.insert(12, "F");
    tree.insert(18, "G");

    std::vector<std::pair<int, std::string>> elements;

    auto accumulateFn = [&elements](const int &key, const std::string &info)
    {
        elements.push_back(make_pair(key, info));
    };

    tree.for_each(accumulateFn);

    std::vector<std::pair<int, std::string>> expectedElements = {
        {2, "D"},
        {5, "B"},
        {8, "E"},
        {10, "A"},
        {12, "F"},
        {15, "C"},
        {18, "G"}};

    assert(elements == expectedElements);

    std::cout << "All for_each tests passed!" << std::endl;
}

void test_maxinfo_selector()
{
    avl_tree<int, std::string> tree;
    tree.insert(10, "A");
    tree.insert(5, "B");
    tree.insert(15, "C");
    tree.insert(2, "D");
    tree.insert(8, "E");
    tree.insert(12, "F");
    tree.insert(18, "G");

    int n = 3;
    std::vector<std::pair<int, std::string>> selectedElements = maxinfo_selector(tree, n);

    std::vector<std::pair<int, std::string>> expectedElements = {
        {18, "G"},
        {12, "F"},
        {8, "E"}};

    assert(selectedElements == expectedElements);

    selectedElements = maxinfo_selector(tree, 10);
    expectedElements = {
        {18, "G"},
        {12, "F"},
        {8, "E"},
        {2, "D"},
        {15, "C"},
        {5, "B"},
        {10, "A"}};

    assert(selectedElements == expectedElements);

    selectedElements = maxinfo_selector(tree, 0);
    expectedElements = {};
    assert(selectedElements == expectedElements);

    tree[2] = "F";
    selectedElements = maxinfo_selector(tree, n);

    expectedElements = {
        {18, "G"},
        {14, "F"},
        {8, "E"}};

    std::cout << "All maxinfo_selector tests passed!" << std::endl;
}

void test_word_count()
{

    ifstream vagner("Vagner_song.txt");
    ifstream ukraine("Ukraine_Gimn.txt");
    ifstream soviet("Soviet_union_gimn.txt");
    ifstream bandera("bandera.txt");
    ifstream voyage("beagle_voyage.txt");

    auto wc = count_words(vagner);
    assert(wc.getSize() == 88);
    wc = count_words(ukraine);
    assert(wc.getSize() == 80);
    wc = count_words(soviet);
    assert(wc.getSize() == 80);
    wc = count_words(bandera);
    assert(wc.getSize() == 138);
    wc = count_words(voyage);
    // cout << wc.getSize() << endl;
    // auto most_used_words = maxinfo_selector(wc, 20);
    // for (const auto &pair : most_used_words)
    // {
    //     cout << pair.first << ": " << pair.second << endl;
    // }
    cout << "Count words tests passed" << endl;
}

void time_measurement()
{
    for (int rep = 0; rep < 5; rep++)
    {
        ifstream is("beagle_voyage.txt");
        auto start_time = std::chrono::high_resolution_clock::now();
        auto wc = count_words(is);
        auto end_time = std::chrono::high_resolution_clock::now();
        auto time = end_time - start_time;
        std::cout << "Ellapsed time: " << time / std::chrono::milliseconds(1) << "ms" << endl;
    }
}

int main()
{
    test_clear_get_size();
    test_insert_find();
    test_insert_get();
    test_remove();
    test_assignment_operator();
    test_copyconstructor();
    test_print();
    test_get_largest();
    test_get_smallest();
    test_for_each();
    cout
        << "All tests passed!" << endl;

    // External functions tests
    test_maxinfo_selector();
    test_word_count();

    time_measurement();
}