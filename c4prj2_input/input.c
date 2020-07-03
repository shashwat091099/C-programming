#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "future.h"
#include "input.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * deck = malloc(sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards = 0;
  int i = 0;
  char * chNewline = "\n";
  char chQuestion = '?';

  while(1) {
    // if we come upon a future card (i.e., a `?n` card)
    if (*(str+i) == chQuestion) {
      size_t index;
      int j = 1;
      //count number of digits of n in ?n
      while (isdigit(*(str+i+j))) {
	j++;
      }
      //create string of length with same number of digits as  n from ?n
      char chN[j];
      for (int k=0; k<j-1; k++) {
	chN[k] = *(str+i+k+1);
      }
      chN[j-1] = '\0';
      int n = atoi(chN);
      index = (size_t)n;
      card_t * ptr = add_empty_card(deck);
      add_future_card(fc, index, ptr);
      i+=j;
    }
    // else check if we come upon a known card (e.g., As or 3c)
    else if (isalnum(*(str+i))) {
      card_t c = card_from_letters(*(str+i), *(str+i+1));
      add_card_to(deck, c);
      i+=2;
    }
    // else check if we have come upon the end of the line.
    // that is, the end of the hand.
    else if (strcmp(str+i, chNewline)==0) {
      break;
    }
    // otherwise go to the next char in the line
    else {
      i++;
    }
  }

  // make sure there are at least 5 cards in the hand
  if (deck->n_cards < 5) {
    //fprintf(stderr, "Hand contined less than 5 cards:\nLine: %s\n", str);
    return NULL;
  }

  return deck;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  //deck_t ** deck_ts = malloc(sizeof(**deck_ts));
  deck_t ** deck_ts = NULL;

  char * line = NULL;
  size_t sz = 0;
  int i = 0;
  while(getline(&line, &sz, f) > 0) {
    (*n_hands)++;
    deck_ts = realloc(deck_ts, *n_hands * sizeof(**deck_ts));
    deck_t * deck = hand_from_string(line, fc);
    deck_ts[i] = deck;
    free(line);
    line = NULL;
    i++;
  }
  free(line);

  return deck_ts;
}
