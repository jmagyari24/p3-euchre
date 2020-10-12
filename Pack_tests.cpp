// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"
#include <fstream>
#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
}

TEST(test_pack_input_ctor) {
    ifstream input_pack;
    input_pack.open("pack.in");
    Pack pack(input_pack);
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
    Card second = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_TEN, second.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, second.get_suit());
    pack.reset();
    Card next = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
    input_pack.close();
}

TEST(test_shuffle) {
    stringstream mypack;
    mypack << "King of Clubs\nJack of Hearts\nNine of Spades\nAce of Clubs\n"
        "Queen of Hearts\nTen of Spades\nNine of Diamonds\nKing of Hearts\n"
        "Jack of Spades\nTen of Diamonds\nAce of Hearts\nQueen of Spades\n"
        "Jack of Diamonds\nNine of Clubs\nKing of Spades\nQueen of Diamonds\n"
        "Ten of Clubs\nAce of Spades\nKing of Diamonds\nJack of Clubs\n"
        "Nine of Hearts\nAce of Diamonds\nQueen of Clubs\nTen of Hearts";
    Pack test_pack(mypack);
    Pack pack;
    pack.shuffle();
    for (int i = 0; i < 24; i++) {
        ASSERT_EQUAL(pack.deal_one(), test_pack.deal_one());
    }
}

TEST(test_empty) {
    Pack pack;
    ASSERT_FALSE(pack.empty());
    for (int i = 0; i < 24; i++) {
        pack.deal_one();
    }
    ASSERT_TRUE(pack.empty());
    pack.reset();
    ASSERT_FALSE(pack.empty());
}

TEST_MAIN()
