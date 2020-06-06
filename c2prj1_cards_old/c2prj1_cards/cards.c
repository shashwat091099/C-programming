#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  // this function check if the card passed has valid values
  assert(c.value >= 2 && c.value <= VALUE_ACE);
  assert(c.suit >= SPADES && c.suit <= CLUBS);

}

const char * ranking_to_string(hand_ranking_t r) {
  switch (r){
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
  case NOTHING:
    return "NOTHING";
    break;
  default:
    return "INVALID";
    break;
  }
}

char value_letter(card_t c) {
  // Return the symbol that corresponds to the value of the card
  if(c.value < 10)
    return '0'+c.value;
  else{
    switch(c.value){
    case 10:
      return '0';
      break;
    case VALUE_ACE:
      return 'A';
      break;
    case VALUE_KING:
      return 'K';
      break;
    case VALUE_QUEEN:
      return 'Q';
      break;
    case VALUE_JACK:
      return 'J';
      break;
    }
  }
}

char suit_letter(card_t c) {
  switch (c.suit){
  case SPADES:
    return 's';
    break;
  case HEARTS:
    return 'h';
    break;
  case DIAMONDS:
    return 'd';
    break;
  case CLUBS:
    return 'c';
    break;
  default:
    return ' ';
    break;
  }
}

void print_card(card_t c) {
  printf("%c%c", value_letter(c), suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  int value;
  suit_t suit;

  // convert the characters into values
  if (value_let > '0' && value_let < '0'+9)
    value = value_let-'0';
  else{
    switch (value_let){
    case '0':
      value = 10;
      break;
    case 'A':
      value = VALUE_ACE;
      break;
    case 'K':
      value = VALUE_KING;
      break;
    case 'Q':
      value = VALUE_QUEEN;
      break;
    case 'J':
      value = VALUE_JACK;
      break;
    }
  }
  // convert characters into suits
  switch(suit_let){
  case 's':
    suit = SPADES;
    break;
  case 'h':
    suit = HEARTS;
    break;
  case 'd':
    suit = DIAMONDS;
    break;
  case'c':
    suit = CLUBS;
    break;
  }

  card_t temp;
  temp.value = value;
  temp.suit = suit;
  assert_card_valid(temp);
  return temp;
}

card_t card_from_num(unsigned c) {

  int suit_n = c/13;
  int value_n = c%13+2;

  card_t temp;
  temp.value = value_n;
  temp.suit = suit_n;
  assert_card_valid(temp);

  return temp;
}
