
/* Pack.h
 *
 * Represents a pack of playing cards
 * Project UID 1d9f47bfc76643019cfbf037641defe1
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * 2014-12-21
 */


#include "Card.h"
#include "Pack.h"
#include <array>
#include <string>


using namespace std;

	// EFFECTS: Initializes the Pack to be in the following standard order:
	//          the cards of the lowest suit arranged from lowest rank to
	//          highest rank, followed by the cards of the next lowest suit
	//          in order from lowest to highest rank, and so on.
	// NOTE: The standard order is the same as that in pack.in.
	// NOTE: Do NOT use pack.in in your implementation of this function
	Pack::Pack() {
		int y = 0;
		next = 0;
		for (int i = 0; i < NUM_SUITS; i++) {
			for (int x = 7; x < NUM_RANKS; x++) {
				cards[y] = Card(RANK_NAMES_BY_WEIGHT[x], SUIT_NAMES_BY_WEIGHT[i]);
				y++;
			}
		}
	}

	// REQUIRES: pack_input contains a representation of a Pack in the
	//           format required by the project specification
	// MODIFIES: pack_input
	// EFFECTS: Initializes Pack by reading from pack_input.
	Pack::Pack(std::istream& pack_input) {
		next = 0;
		string card_of;
		string card_rank;
		string card_suit;
		int i = 0;
		while (pack_input >> card_rank >> card_of >> card_suit) {
			//Suit ifs x4
			if (card_suit == Card::SUIT_SPADES) {
				card_suit = Card::SUIT_SPADES;
			}
			else if (card_suit == Card::SUIT_HEARTS) {
				card_suit = Card::SUIT_HEARTS;
			}
			else if (card_suit == Card::SUIT_CLUBS) {
				card_suit = Card::SUIT_CLUBS;
			}
			else if (card_suit == Card::SUIT_DIAMONDS) {
				card_suit = Card::SUIT_DIAMONDS;
			}
			//Rank ifs x13
			if (card_rank == Card::RANK_NINE) {
				card_rank = Card::RANK_NINE;
			}
			else if (card_rank == Card::RANK_TEN) {
				card_rank = Card::RANK_TEN;
			}
			else if (card_rank == Card::RANK_JACK) {
				card_rank = Card::RANK_JACK;
			}
			else if (card_rank == Card::RANK_QUEEN) {
				card_rank = Card::RANK_QUEEN;
			}
			else if (card_rank == Card::RANK_KING) {
				card_rank = Card::RANK_KING;
			}
			else if (card_rank == Card::RANK_ACE) {
				card_rank = Card::RANK_ACE;
			}
			cards[i] = Card(card_rank, card_suit);
			i++;
		}
	}

	// REQUIRES: cards remain in the Pack
	// EFFECTS: Returns the next card in the pack and increments the next index
	Card Pack::deal_one() {
		next++;
		int current = next - 1;
		return cards[current];
	}

	// EFFECTS: Resets next index to first card in the Pack
	void Pack::reset() {
		next = 0;
	}

	// EFFECTS: Shuffles the Pack and resets the next index. This
	//          performs an in shuffle seven times. See
	//          https://en.wikipedia.org/wiki/In_shuffle.
	void Pack::shuffle() {
		Card tempA, tempB, tempC, tempD, tempE, tempF, tempG, tempH, tempI, tempJ, tempK, tempL;
		for (int i = 0; i < 7; i++) {
		//for (int x = 0; x < 24; x++) {
			//cout << cards[x];
		//}
			tempA = cards[0];
			tempB = cards[1];
			tempC = cards[2];
			tempD = cards[3];
			tempE = cards[4];
			tempF = cards[5];
			tempG = cards[6];
			tempH = cards[7];
			tempI = cards[8];
			tempJ = cards[9];
			tempK = cards[10];
			tempL = cards[11];
			cards[0] = cards[12];
			cards[2] = cards[13];
			cards[4] = cards[14];
			cards[6] = cards[15];
			cards[8] = cards[16];
			cards[10] = cards[17];
			cards[12] = cards[18];
			cards[14] = cards[19];
			cards[16] = cards[20];
			cards[18] = cards[21];
			cards[20] = cards[22];
			cards[22] = cards[23];
			cards[1] = tempA;
			cards[3] = tempB;
			cards[5] = tempC;
			cards[7] = tempD;
			cards[9] = tempE;
			cards[11] = tempF;
			cards[13] = tempG;
			cards[15] = tempH;
			cards[17] = tempI;
			cards[19] = tempJ;
			cards[21] = tempK;
			cards[23] = tempL;
		}
		next = 0;
	}

	// EFFECTS: returns true if there are no more cards left in the pack
	bool Pack::empty() const {
		if (next > 23) {
			return true;
		}
		else {
			return false;
		}
	}

