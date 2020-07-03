#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: test-input fileName\n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("fopen");
    fprintf(stderr, "Could not open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  size_t n_hands = 0;
  future_cards_t fc;
  fc.decks = malloc(sizeof(*fc.decks));
  fc.n_decks = 0;

  deck_t ** deck_ts = read_input(f, &n_hands, &fc);

  printf("n_hands: %zu\n", n_hands);

  //display hand with unknown cards
  printf("Hand with unknown cards\n");
  for (int i=0; i<n_hands; i++) {
    print_hand(deck_ts[i]);
    printf("\n");
  }

  // create a shuffled deck to update the unknown card
  deck_t * shuffled = malloc(sizeof(*shuffled));
  shuffled->cards = NULL;
  shuffled->n_cards = 0;
  for (int i=0; i<2; i++) {
    card_t c = card_from_num(i);
    add_card_to(shuffled, c);
  }

  //display shuffled hand
  printf("Shuffled hand\n");
  print_hand(shuffled);
  printf("\n");

  //add shuffled card to hand to update unkown card
  future_cards_from_deck(shuffled, &fc);

  //display fc with known card
  printf("Hand with known cards\n");
  for (int i=0; i<fc.n_decks; i++) {
    printf("fc.deck[%d]\n", i);
    print_hand(&fc.decks[i]);
    printf("\n");
  }

  for (int i=0; i<n_hands; i++) {
    free_deck(deck_ts[i]);
  }

  free(deck_ts);

  for (int i=0; i<fc.n_decks; i++) {
    if (fc.decks[i].n_cards > 0) {
      free_deck(&fc.decks[i]);
    }
  }

  free(fc.decks);

  exit(EXIT_SUCCESS);
}
