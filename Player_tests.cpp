// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"
#include "Card.h"
#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here
TEST(test_make_trump_first_round) {
    Player * jason = Player_factory("Jason", "Simple");
    jason->add_card(Card("Ace", "Hearts"));
    jason->add_card(Card("Nine", "Spades"));
    jason->add_card(Card("Ace", "Diamonds"));
    jason->add_card(Card("Jack", "Spades"));
    jason->add_card(Card("King", "Clubs"));
    //round 1 pass (two trump 1 trump face)
    Card upcard = Card("Jack", "Spades");
    string upcard_suit(upcard.get_suit());
    ASSERT_FALSE(jason->make_trump(upcard, false, 1, upcard_suit));
    //round 1 order up with left bower
    upcard = Card("Nine", "Clubs");
    upcard_suit = upcard.get_suit();
    ASSERT_TRUE(jason->make_trump(upcard, false, 1, upcard_suit));
    ASSERT_EQUAL(upcard_suit, "Clubs");
    delete jason;
}

TEST(test_make_trump_second_round) {
    Player* jason = Player_factory("Jason", "Simple");
    jason->add_card(Card("Ace", "Spades"));
    jason->add_card(Card("Nine", "Spades"));
    jason->add_card(Card("Ten", "Diamonds"));
    jason->add_card(Card("Nine", "Hearts"));
    jason->add_card(Card("King", "Clubs"));
    //round 2 dealer
    Card upcard = Card("King", "Hearts");
    string upcard_suit(upcard.get_suit());
    ASSERT_TRUE(jason->make_trump(upcard, true, 2, upcard_suit));
    ASSERT_EQUAL(upcard_suit, "Diamonds");
    //round 2 pass trump but not face
    ASSERT_FALSE(jason->make_trump(upcard, false, 2, upcard_suit));
    //round 2 order up
    upcard = Card("King", "Spades");
    upcard_suit = upcard.get_suit();
    ASSERT_TRUE(jason->make_trump(upcard, false, 2, upcard_suit));
    ASSERT_EQUAL(upcard_suit, "Clubs");
    delete jason;
}

TEST(test_add_and_discard) {
    Player* jason = Player_factory("Jason", "Simple");
    jason->add_card(Card("Ace", "Spades"));
    jason->add_card(Card("Ace", "Hearts"));
    jason->add_card(Card("Ace", "Diamonds"));
    jason->add_card(Card("Jack", "Clubs"));
    jason->add_card(Card("Ace", "Clubs"));
    Card upcard = Card("Jack", "Spades");
    jason->add_and_discard(upcard); //should discard Ace Hearts
    Card ledCard = Card("Ten", "Hearts");
    string ledCardSuit = ledCard.get_suit();
    Card cardPlayed = jason->play_card(ledCard, ledCardSuit);
    ASSERT_EQUAL(cardPlayed, Card("Jack", "Spades"));
    delete jason;
}

TEST(test_lead_card) {
    Player* jason = Player_factory("Jason", "Simple");
    jason->add_card(Card("Ace", "Spades"));
    jason->add_card(Card("Ace", "Hearts"));
    jason->add_card(Card("Ten", "Hearts"));
    string trump = "Hearts";
    //non-trump
    ASSERT_EQUAL(jason->lead_card(trump), Card("Ace", "Spades"));
    //only trump
    ASSERT_EQUAL(jason->lead_card(trump), Card("Ace", "Hearts"));
    delete jason;
}

TEST(test_human) {
    Player* jason = Player_factory("Jason", "Simple");
    jason->add_card(Card("Ace", "Spades"));
    jason->add_card(Card("Ace", "Hearts"));
    jason->add_card(Card("Ace", "Diamonds"));
    jason->add_card(Card("Jack", "Clubs"));
    jason->add_card(Card("Ace", "Clubs"));
    Card upcard = Card("Jack", "Spades");
    string upcard_suit = upcard.get_suit();
    jason->make_trump(upcard, 0, 1, upcard_suit);
    jason->add_and_discard(upcard);
    jason->lead_card(upcard_suit);
    jason->play_card(upcard, upcard_suit);
    delete jason;
}

TEST_MAIN()
