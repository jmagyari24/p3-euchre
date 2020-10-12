// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here
TEST(test_get_suit_) {
    //non-bower
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    const string trump = Card::SUIT_HEARTS;
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit(trump));
    //spades left bower
    Card c1(Card::RANK_JACK, Card::SUIT_CLUBS);
    const string trump1 = Card::SUIT_SPADES;
    ASSERT_EQUAL(Card::SUIT_SPADES, c1.get_suit(trump1));
    //hearts left bower
    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    const string trump2 = Card::SUIT_HEARTS;
    ASSERT_EQUAL(Card::SUIT_HEARTS, c2.get_suit(trump2));
    //clubs left bower
    Card c3(Card::RANK_JACK, Card::SUIT_SPADES);
    const string trump3 = Card::SUIT_CLUBS;
    ASSERT_EQUAL(Card::SUIT_CLUBS, c3.get_suit(trump3));
    //diamonds left bower
    Card c4(Card::RANK_JACK, Card::SUIT_HEARTS);
    const string trump4 = Card::SUIT_DIAMONDS;
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, c4.get_suit(trump4));
    //right bower
    Card c5(Card::RANK_JACK, Card::SUIT_HEARTS);
    const string trump5 = Card::SUIT_HEARTS;
    ASSERT_EQUAL(Card::SUIT_HEARTS, c5.get_suit(trump5));
}

TEST(test_is_face) {
    //Card Face
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(c.is_face())
    //Non-face
    Card c1(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_FALSE(c1.is_face())
}

TEST(test_is_right_bower) {
    //right bower
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(c.is_right_bower(Card::SUIT_HEARTS))
    //not right bower
    Card c1(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_FALSE(c1.is_right_bower(Card::SUIT_HEARTS))
}

TEST(test_is_left_bower) {
    //right bower
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_HEARTS))
    //left bower
    Card c1(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c1.is_left_bower(Card::SUIT_HEARTS))
}

TEST(test_is_trump) {
    //left bower
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(c.is_trump(Card::SUIT_DIAMONDS))
    //ace trump
    Card c1(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c1.is_trump(Card::SUIT_DIAMONDS))
    //non-trump
    Card c2(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(c2.is_trump(Card::SUIT_DIAMONDS))
}

TEST(test_operator_less) {
    //same rank different suit
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c1(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(c1 < c)
    //same suit and rank
    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(c2 < c3)
    //same suit different rank
    Card c4(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card c5(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(c4 < c5)
}

TEST(test_operator_greater) {
    //same rank different suit
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c1(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(c1 > c)
    //same suit and rank
    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(c2 > c3)
    //same suit different rank
    Card c4(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card c5(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(c4 > c5)
}

TEST(test_operator_equal) {
    //same rank different suit
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c1(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(c1 == c)
    //same suit and rank
    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c2 == c3)
    //same suit different rank
    Card c4(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card c5(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(c4 == c5)
}

TEST(test_not_same_card) {
    //same card
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c1(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(c != c1)
    //not same card
    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c2 != c3)
}

TEST(test_next_suit) {
    //spades
    ASSERT_EQUAL(Card::SUIT_SPADES,Suit_next(Card::SUIT_CLUBS))
    //hearts
    ASSERT_EQUAL(Card::SUIT_HEARTS, Suit_next(Card::SUIT_DIAMONDS))
    //clubs
    ASSERT_EQUAL(Card::SUIT_CLUBS, Suit_next(Card::SUIT_SPADES))
    //diamonds
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, Suit_next(Card::SUIT_HEARTS))
}

TEST(test_card_less) {
    //both a and b trump
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c1(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(Card_less(c, c1, Card::SUIT_DIAMONDS));
    //only a trump
    Card c2(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card c3(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(Card_less(c2, c3, Card::SUIT_HEARTS));
    //only b trump
    Card c4(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(c4, c5, Card::SUIT_CLUBS));
    //neither are trump same rank
    Card c6(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c7(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Card_less(c6, c7, Card::SUIT_SPADES));
}

TEST(test_card_less_lead_card) {
    Card cs(Card::RANK_ACE, Card::SUIT_SPADES);
    Card ch(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card cc(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card cd(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    //trump lead both a and b trump
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c1(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(Card_less(c, c1, cd, Card::SUIT_DIAMONDS));
    //trump lead a only trump
    Card c2(Card::RANK_NINE, Card::SUIT_SPADES);
    Card c3(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(Card_less(c2, c3, cs, Card::SUIT_SPADES));
    //trump lead b only trump
    Card c4(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(c4, c5, cc, Card::SUIT_CLUBS));
    //trump not lead:
        //both a and b follow suit
        Card c6(Card::RANK_JACK, Card::SUIT_DIAMONDS);
        Card c7(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
        ASSERT_TRUE(Card_less(c4, c5, cd, Card::SUIT_CLUBS));
        //only a follow suit
        Card c8(Card::RANK_KING, Card::SUIT_HEARTS);
        Card c9(Card::RANK_ACE, Card::SUIT_SPADES);
        ASSERT_FALSE(Card_less(c8, c9, ch, Card::SUIT_CLUBS));
        //only b follow suit
        Card c10(Card::RANK_ACE, Card::SUIT_DIAMONDS);
        Card c11(Card::RANK_QUEEN, Card::SUIT_CLUBS);
        ASSERT_TRUE(Card_less(c10, c11, cc, Card::SUIT_SPADES));
        //only a trump
        Card c12(Card::RANK_NINE, Card::SUIT_HEARTS);
        Card c13(Card::RANK_QUEEN, Card::SUIT_CLUBS);
        ASSERT_FALSE(Card_less(c12, c13, cc, Card::SUIT_HEARTS));
        //only b trump
        Card c14(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
        Card c15(Card::RANK_TEN, Card::SUIT_CLUBS);
        ASSERT_TRUE(Card_less(c14, c15, cd, Card::SUIT_CLUBS));
        //both a and b trump
        Card c16(Card::RANK_JACK, Card::SUIT_DIAMONDS);
        Card c17(Card::RANK_JACK, Card::SUIT_HEARTS);
        ASSERT_FALSE(Card_less(c16, c17, cc, Card::SUIT_DIAMONDS));
}
TEST_MAIN()
