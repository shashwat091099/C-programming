#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(c.value>=2 && c.value<=VALUE_ACE);
  assert(c.suit>=SPADES && c.suit<=CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  switch(r) {
  case STRAIGHT_FLUSH:
    return "STRAIGHT_FLUSH";
    break;
  case FOUR_OF_A_KIND:
    return "FOUR_OF_A_KIND";
    break;
  case FULL_HOUSE:
    return "FULL_HOUSE";
    break;
  case FLUSH:
    return "FLUSH";
    break;
  case STRAIGHT:
    return "STRAIGHT";
    break;
  case THREE_OF_A_KIND:
    return "THREE_OF_A_KIND";
    break;
  case TWO_PAIR:
    return "TWO_PAIR";
    break;
  case PAIR:
    return "PAIR";
    break;
  default:
    return "NOTHING";
    break;
  }
}

char value_letter(card_t c) {
  if (c.value>=2 && c.value < 10) {
    return 48 + c.value;
  }
  else if (c.value==10) {
    return 48;
  }
  else if (c.value==11) {
    return 74;
  }
  else if (c.value==12) {
    return 81;
  }
  else if (c.value==13) {
    return 75;
  }
  else if (c.value==14) {
    return 65;
  }
  else {
    return 63;
  }
}


char suit_letter(card_t c) {
  switch (c.suit) {
  case SPADES:
    return 's';
    break;
  case HEARTS:
    return 'h';
    break;
  case CLUBS:
    return 'c';
    break;
  case DIAMONDS:
    return 'd';
    break;
  default:
    return 48;
    break;
  }
}

void print_card(card_t c) {
  printf("%c%c", value_letter(c), suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  if (value_let==48) {
    temp.value = 10;
  }
  else if (value_let>49 && value_let<58) {
    temp.value = value_let - 48;
  }
  else if (value_let==74) {
    temp.value = 11;
  }
  else if (value_let==81) {
    temp.value = 12;
  }
  else if (value_let==75) {
    temp.value = 13;
  }
  else if (value_let==65) {
    temp.value = 14;
  }
  else {
    temp.value = 0;
  }

  // now suits
  switch(suit_let) {
  case 's':
    temp.suit = SPADES;
    break;
  case 'h':
    temp.suit = HEARTS;
    break;
  case 'c':
    temp.suit = CLUBS;
    break;
  case 'd':
    temp.suit = DIAMONDS;
    break;
  default:
    temp.suit = NUM_SUITS;
    break;
  }

  //assert_card_valid(temp);
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  temp.value = 2 + (c % 13);
  if (c < 13) {
    temp.suit = SPADES;
  }
  else if (c>=13 && c <26) {
    temp.suit = HEARTS;
  }
  else if (c>=26 && c < 39) {
    temp.suit = CLUBS;
  }
  else if (c>=39 && c < 52) {
    temp.suit = DIAMONDS;
  }
  assert_card_valid(temp);
  return temp;
}
