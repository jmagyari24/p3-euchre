#include "Card.h"
#include "Player.h"
#include <array>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

class Simple: public Player{
public:
	Simple(string playerName) { name = playerName; }

	//EFFECTS returns player's name
	const string& get_name() const {
		return name;
	}

	//REQUIRES player has less than MAX_HAND_SIZE cards
	//EFFECTS  adds Card c to Player's hand
	void add_card(const Card& c) {
		assert(hand.size() < MAX_HAND_SIZE +1);
		hand.push_back(c);
	}

	//REQUIRES round is 1 or 2
	//MODIFIES order_up_suit
	//EFFECTS If Player wishes to order up a trump suit then return true and
	//  change order_up_suit to desired suit.  If Player wishes to pass, then do
	//  not modify order_up_suit and return false.
	bool make_trump(const Card& upcard, bool is_dealer,
		int round, string& order_up_suit) const {
		assert(round == 1 || round == 2);
		string upcard_suit = upcard.get_suit();
		int r1count = 0;
		//round 1: and two or more trump face cards -> true
		if (round == 1) {
			for (int c = 0; c < MAX_HAND_SIZE; c++) {
				if (hand[c].is_trump(upcard_suit) && hand[c].is_face()) { r1count++; }
			}
			if (r1count > 1) {
				order_up_suit = upcard_suit;
				return true;
			}
			else { return false; }
		}
		if (round == 2) {
			//round 2: and dealer true
			if (is_dealer) {
				order_up_suit = Suit_next(upcard_suit);
				return true;
			}
			//round 2: 1 or more face cards of same color -> true
			for (int c = 0; c < MAX_HAND_SIZE; c++) {
				if (hand[c].get_suit() == Suit_next(upcard_suit) && hand[c].is_face()){ 
					order_up_suit = Suit_next(upcard_suit);
					return true;
				}
			}
		}
		return false;
	}

	//REQUIRES Player has at least one card
	//EFFECTS  Player adds one card to hand and removes one card from hand.
	void add_and_discard(const Card& upcard) {
		assert(hand.size() >= 1);
		add_card(upcard);
		string trump = upcard.get_suit();
		Card lowCard;
		int lowIndex = 0;
		lowCard = hand[0];
		for (unsigned int c = 0; c < hand.size(); c++) {
			if (Card_less(hand[c], lowCard, trump)) {
				lowCard = hand[c];
				lowIndex = c;
			}
		}
		hand.erase(hand.begin() + lowIndex);
	}

	//REQUIRES Player has at least one card, trump is a valid suit
	//EFFECTS  Leads one Card from Player's hand according to their strategy
	//  "Lead" means to play the first Card in a trick.  The card
	//  is removed the player's hand.
	Card lead_card(const string& trump) {
		assert(hand.size() >= 1);
		Card highCard;
		Card highTrump;
		Card cardReturn;
		int highTrumpIndex = 0;
		int highIndex = 0;
		bool noTrump = false;
		for (unsigned int c = 0; c < hand.size(); c++) {
			if (hand[c].is_trump(trump)) {
				highTrump = hand[c];
				highTrumpIndex = c;
			}
			else {
				highCard= hand[c];
				highIndex = c;
				noTrump = true;
			}
		}
		for (unsigned int c = 0; c < hand.size(); c++) {
			if (hand[c].is_trump(trump) && hand[c] > highTrump) {
				highTrump = hand[c];
				highTrumpIndex = c;
			}
			if (!hand[c].is_trump(trump) && hand[c] > highCard) {
				highCard = hand[c];
				highIndex = c;
			}
		}
		if (noTrump) {
			cardReturn = hand[highIndex];
			hand.erase(hand.begin() + highIndex);
			return cardReturn;
		}
		else {
			cardReturn = hand[highTrumpIndex];
			hand.erase(hand.begin() + highTrumpIndex);
			return cardReturn;
		}
		
	}

	//REQUIRES Player has at least one card, trump is a valid suit
	//EFFECTS  Plays one Card from Player's hand according to their strategy.
	//  The card is removed from the player's hand.
	Card play_card(const Card& led_card, const string& trump) {
		assert(hand.size() >= 1);
		assert(trump == "Spades" || trump == "Hearts"
			|| trump == "Clubs" || trump == "Diamonds");
		Card highOnSuit = hand[0];
		int highOnSuitIndex = 0;
		Card lowOffSuit = hand[0];
		int lowOffSuitIndex = 0;
		bool haveSuit = false;
		for (unsigned int c = 0; c < hand.size(); c++) {
			if (led_card.get_suit(trump) == hand[c].get_suit(trump)) {
				if (hand[c] > highOnSuit) {
					highOnSuit = hand[c];
					highOnSuitIndex = c;
				}
				haveSuit = true;
			}
			else {
				if (hand[c] < lowOffSuit) {
					lowOffSuit = hand[c];
					lowOffSuitIndex = c;
				}
			}
		}
		if (haveSuit) {
			Card cardReturn = hand[highOnSuitIndex];
			hand.erase(hand.begin() + highOnSuitIndex);
			return cardReturn;
		}
		else {
			Card cardReturn = hand[lowOffSuitIndex];
			hand.erase(hand.begin() + lowOffSuitIndex);
			return cardReturn;
		}
	}

private:
	string name;
	vector <Card> hand;
};


class Human : public Player {
public:
	Human(string playerName) { name = playerName; }

	//EFFECTS returns player's name
	const std::string& get_name() const {
		return name;
	}

	//REQUIRES player has less than MAX_HAND_SIZE cards
	//EFFECTS  adds Card c to Player's hand
	void add_card(const Card& c) {
		assert(hand.size() < MAX_HAND_SIZE + 1);
		hand.push_back(c);
	}

	//REQUIRES round is 1 or 2
	//MODIFIES order_up_suit
	//EFFECTS If Player wishes to order up a trump suit then return true and
	//  change order_up_suit to desired suit.  If Player wishes to pass, then do
	//  not modify order_up_suit and return false.
	bool make_trump(const Card& upcard, bool is_dealer,
		int round, std::string& order_up_suit) const {
		assert(round == 1 || round == 2);
		string playerDecision;
		vector<Card> hand_copy = hand;
		sort(hand_copy.begin(), hand_copy.end());
		for (unsigned int c = 0; c < hand_copy.size(); c++) {
			cout << "Human player " << get_name() << "'s hand:[" << c << "] " 
				<< hand_copy[c] << endl;
		}
		cout << "Human player " << get_name() << ", please enter a suit, or \"pass\":" << endl;
		cin >> playerDecision;
		while (playerDecision != "Spades" || playerDecision != "Hearts" 
			|| playerDecision != "Clubs" 
			|| playerDecision != "Diamonds" || playerDecision != "pass") {
			cout << "Not a valid entry. Pleser enter a suit, or \"pass\":" << endl;
			cin >> playerDecision;
		}
		cout << endl; //appendix said to add new line after making adding or discarding
		if (playerDecision == "pass") {
			return false;
		}
		else {
			order_up_suit = playerDecision;
			return true;
		}
	}

	//REQUIRES Player has at least one card
	//EFFECTS  Player adds one card to hand and removes one card from hand.
	void add_and_discard(const Card& upcard) {
		string playerDecision;
		int cardNumber;
		sort(hand.begin(), hand.end());
		for (unsigned int c = 0; c < hand.size(); c++) {
			cout << "Human player " << get_name() << "'s hand: [" << c << "] " << hand[c] << endl;
		}
		cout << "Discard upcard: [-1]\n";
		cout << "Human player " << get_name() << ", please select a card to discard:\n";
		cin >> playerDecision;
		while (!(playerDecision == "0" || playerDecision == "1" || playerDecision == "2" 
			|| playerDecision != "3" || playerDecision != "4" || playerDecision != "-1")) {
			cout << "Human player " << get_name() << ", please select a card to discard:\n";
			cin >> playerDecision;
		}
		cout << endl; //add extra line
		cardNumber = stoi(playerDecision);
		hand.erase(hand.begin() + cardNumber);
		add_card(upcard);
	}

	//REQUIRES Player has at least one card, trump is a valid suit
	//EFFECTS  Leads one Card from Player's hand according to their strategy
	//  "Lead" means to play the first Card in a trick.  The card
	//  is removed the player's hand.
	Card lead_card(const std::string& trump) {
		sort(hand.begin(), hand.end());
		string selectedCard;
		Card playerChoice;
		unsigned int cardNumber;
		for (unsigned int c = 0; c < hand.size(); c++) {
			cout << "Human player " << get_name() << "'s hand: [" << c << "] " << hand[c] << endl;
		}
		cout << "Human player " << get_name() << ", please select a card:\n";
		cin >> selectedCard;
		cardNumber = stoi(selectedCard);
		while (cardNumber <0 && cardNumber > hand.size()) {
			cout << "Human player " << get_name() << ", please select a card:\n";
			cin >> selectedCard;
		}
		cout << endl; //add extra line
		playerChoice = hand[cardNumber];
		hand.erase(hand.begin() + cardNumber);
		return playerChoice;
	}

	//REQUIRES Player has at least one card, trump is a valid suit
	//EFFECTS  Plays one Card from Player's hand according to their strategy.
	//  The card is removed from the player's hand.
	Card play_card(const Card& led_card, const std::string& trump) {
		return lead_card(trump);
	}


private:
	string name;
	vector <Card> hand;
};


//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player* Player_factory(const string& name, const string& strategy) {
	if (strategy == "Simple") {
		return new Simple(name);
	}
	if (strategy == "Human") {
		return new Human(name);
	}
	assert(false);
	return nullptr;
}


//EFFECTS: Prints player's name to os
ostream& operator<<(ostream& os, const Player& p) {
	return os << p.get_name();
} 