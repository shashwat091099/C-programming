#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "future.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {

  if (fc->n_decks <= index) {
    fc->decks = realloc(fc->decks, (index+1) * sizeof(*fc->decks));
    for (size_t i=fc->n_decks; i<=index; i++) {
      fc->decks[i].cards = NULL;
      //fc->decks[i].cards = malloc(sizeof(*fc->decks[i].cards));
      fc->decks[i].n_cards = 0;
    }
    fc->n_decks = index+1;
  }

  //add_card_to(&(fc->decks[index]), *ptr);
  fc->decks[index].n_cards++;
  fc->decks[index].cards = realloc(fc->decks[index].cards, fc->decks[index].n_cards * sizeof(*fc->decks[index].cards[fc->decks[index].n_cards-1]));
  fc->decks[index].cards[fc->decks[index].n_cards-1] = ptr;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  if (deck == NULL) {
    return;
  }
  if (fc->decks == NULL) {
    return;
  }
  if (deck->n_cards == 0) {
    //fprintf(stderr, "future_cards_from_deck: shuffled_deck->n_cards == 0\n");
    return;
  }
  if (fc->n_decks == 0) {
    //fprintf(stderr, "future_cards_from_deck: fc->n_decks == 0\n");
    return;
  }

  size_t num_future_cards = 0;
  for (size_t i=0; i<fc->n_decks; i++) {
    if (fc->decks[i].n_cards > 0) {
      num_future_cards++;
    }
  }

  if (num_future_cards > deck->n_cards) {
    //fprintf(stderr, "future_cards_from_deck: num_future_cards > shuffled_deck->n_cards\n");
    return;
  }

  size_t k = 0;
  for (size_t i=0; i<fc->n_decks; i++) {
    if (fc->decks[i].n_cards > 0) {
      for (size_t j=0; j<fc->decks[i].n_cards; j++) {
	*fc->decks[i].cards[j] = *deck->cards[k];;
      }
    }
    k++;
  }
}
