#include <gtest/gtest.h>
#include "Tree_B.hpp"

// Test fixture class
class TreeBTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if necessary
    }

    void TearDown() override {
        // Cleanup code if necessary
    }

    // Tree_B instance for testing
    Tree_B<int, 4> tree;
};

TEST_F(TreeBTest, InsertSingleElement) {
    tree.insert(10);
    std::ostringstream oss;
    tree.printTree(oss);
    std::string expected = "10\n";
    EXPECT_EQ(oss.str(), expected);
}

TEST_F(TreeBTest, InsertMultipleElements) {
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);
    tree.insert(7);
    tree.insert(17);

    std::ostringstream oss;
    tree.printTree(oss);
    std::string expected =
        "10\n"
        "  5 6 7 \n"
        "  17 20 30 \n";
    EXPECT_EQ(oss.str(), expected);
}

TEST_F(TreeBTest, SplitRoot) {
    for (int i = 1; i <= 10; ++i) {
        tree.insert(i);
    }

    std::ostringstream oss;
    tree.printTree(oss);
    std::string expected =
        "4\n"
        "  2\n"
        "    1\n"
        "    3\n"
        "  6\n"
        "    5\n"
        "    8\n"
        "      7\n"
        "      9\n"
        "        10\n";
    EXPECT_EQ(oss.str(), expected);
}

// Additional tests as needed...

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
