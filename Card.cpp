// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"

using namespace std;

// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
//EFFECTS Initializes Card to the Two of Spades
Card::Card() : rank(Card::RANK_TWO), suit(Card::SUIT_SPADES) {}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const string& rank_in, const string& suit_in)
    : rank(rank_in), suit(suit_in) {}

//EFFECTS Returns the rank
string Card::get_rank() const {
    return rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
string Card::get_suit() const {
    return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
string Card::get_suit(const string& trump) const {
    assert(trump == SUIT_CLUBS || trump == SUIT_DIAMONDS ||
            trump == SUIT_SPADES || trump == SUIT_HEARTS);
    if (rank == RANK_JACK) {
        if (trump == SUIT_SPADES && suit == SUIT_CLUBS) {
            return SUIT_SPADES;
        }
        else if (trump == SUIT_HEARTS && suit == SUIT_DIAMONDS) {
            return SUIT_HEARTS;
        }
        else if (trump == SUIT_CLUBS && suit == SUIT_SPADES) {
            return SUIT_CLUBS;
        }
        else if (trump == SUIT_DIAMONDS && suit == SUIT_HEARTS) {
            return SUIT_DIAMONDS;
        }
    }
    return suit;
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const {
    if (rank == RANK_JACK || rank == RANK_QUEEN ||
        rank == RANK_KING || rank == RANK_ACE) {
        return true;
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const string& trump) const {
    assert(trump == SUIT_CLUBS || trump == SUIT_DIAMONDS ||
        trump == SUIT_SPADES || trump == SUIT_HEARTS);
    if (rank == RANK_JACK) {
        if (trump == suit) {
            return true;
        }
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const string& trump) const {
    assert(trump == SUIT_CLUBS || trump == SUIT_DIAMONDS ||
        trump == SUIT_SPADES || trump == SUIT_HEARTS);
    if (rank == RANK_JACK) {
        if (trump == get_suit(trump) && trump != get_suit()) {
            return true;
        }
    }
    return false;
}
 
//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const string& trump) const {
    assert(trump == SUIT_CLUBS || trump == SUIT_DIAMONDS ||
        trump == SUIT_SPADES || trump == SUIT_HEARTS);
    if (trump == get_suit(trump)) {
        return true;
    }
    return false;
}


//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card& lhs, const Card& rhs) {
    int weight_lhs;
    int weight_lhs_suit;
    int weight_rhs;
    int weight_rhs_suit;
    for (int i = 0; i < NUM_RANKS; i++) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            weight_lhs = i;
        }
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            weight_rhs = i;
        }
    }
    for (int i = 0; i < NUM_SUITS; i++) {
        if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
            weight_lhs_suit = i;
        }
        if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
            weight_rhs_suit = i;
        }
    }
    if (weight_lhs == weight_rhs) {
        return weight_lhs_suit < weight_rhs_suit;
    }
    return weight_lhs < weight_rhs;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card& lhs, const Card& rhs) {
    if (lhs < rhs) {
        return false;
    }
    else if (rhs < lhs) {
        return true;
    }
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card& lhs, const Card& rhs) {
    if (!(lhs < rhs) && !(lhs > rhs)) {
        return true;
    }
    return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card& lhs, const Card& rhs) {
    if (lhs == rhs) {
        return false;
    }
    return true;
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
string Suit_next(const string& suit) {
    if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    }
    else if (suit == Card::SUIT_HEARTS) {
        return Card::SUIT_DIAMONDS;
    }
    else if (suit == Card::SUIT_SPADES) {
        return Card::SUIT_CLUBS;
    }
    else {
        return Card::SUIT_HEARTS;
    }
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
ostream& operator<<(ostream& os, const Card& card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card& a, const Card& b, const string& trump) {
    if (a.is_trump(trump) && b.is_trump(trump)) {
        if (a.is_right_bower(trump)) {
            return false;
        }
        else if (b.is_right_bower(trump)) {
            return true;
        }
        else if (a.is_left_bower(trump)) {
            return false;
        }
        else if (b.is_left_bower(trump)) {
            return true;
        }
        else {
            return a < b;
        }
    }
    else if (a.is_trump(trump) && !b.is_trump(trump)) {
        return false;
    }
    else if (!a.is_trump(trump) && b.is_trump(trump)) {
        return true;
    }
    else {
        return a < b;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card& a, const Card& b, const Card& led_card,
    const string& trump) {
    if (led_card.get_suit(trump) == trump) {
        return Card_less(a, b, trump);
    }
    else {
        if (led_card.get_suit(trump) == a.get_suit(trump) && led_card.get_suit(trump) 
            == b.get_suit(trump)) {
            return a < b;
        }
        else if (a.get_suit(trump) == trump && b.get_suit(trump) == trump) {
            return a < b;
        }
        else if (a.get_suit(trump) == trump && b.get_suit(trump) != trump) {
            return Card_less(a, b, trump);
        }
        else if (a.get_suit(trump) != trump && b.get_suit(trump) == trump) {
            return Card_less(a, b, trump);
        }
        else if (led_card.get_suit(trump) == a.get_suit(trump) 
            && !(led_card.get_suit(trump)
            == b.get_suit(trump))) {
            return false;
        }
        else if (!(led_card.get_suit(trump) == a.get_suit(trump)) 
            && led_card.get_suit(trump)
            == b.get_suit(trump)) {
            return true;
        }
        else{
            return Card_less(a,b,trump);
        }
    }
}
    