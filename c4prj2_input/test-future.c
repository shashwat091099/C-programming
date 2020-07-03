#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "future.h"

int main(int argc, char ** argv) {
  future_cards_t fc;
  fc.n_decks = 0;
  fc.decks = malloc(sizeof(*fc.decks));
  fc.decks->cards = NULL;
  fc.decks->n_cards = 0;
  deck_t * deck = malloc(sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards = 0;

  //create "shuffled" deck to change fc cards to
  deck_t * shuffled = malloc(sizeof(*shuffled));
  shuffled->cards = NULL;
  shuffled->n_cards = 0;
  for (unsigned i=0; i<2; i++) {
    card_t c = card_from_num(i);
    add_card_to(shuffled, c);
  }

  // add empty pointers to fc
  for (size_t i=0; i<2; i++) {
    //create empty card pointer in deck
    card_t * ptr = add_empty_card(deck);

    //add the future card to fc
    add_future_card(&fc, i, ptr);
  }

  // display the future cards
  printf("Show unknown future cards\n");
  for (int i=0; i<fc.n_decks; i++) {
    print_hand(&fc.decks[i]);
  }

  // display cards in shuffled
  printf("\nShow cards from shuffled deck\n");
  print_hand(shuffled);

  //change cards in fc to cards from shuffled
  future_cards_from_deck(shuffled, &fc);

  //display known cards from fc
  printf("\nShow known future cards\n");
  for (int i=0; i<fc.n_decks; i++) {
    print_hand(&fc.decks[i]);
  }
  printf("\n");

  //free allocated memory
  free_deck(deck);
  /*
  for (int i=0; i<fc.n_decks; i++) {
    free_deck(&fc.decks[i]);
  }
  */
  free_deck(shuffled);

  exit(EXIT_SUCCESS);
}
