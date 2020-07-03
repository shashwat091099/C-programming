#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void print_hand(deck_t * hand){
  for (size_t i=0; i<hand->n_cards; i++) {
    print_card(*hand->cards[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  for (int i=0; i<d->n_cards; i++) {
    if (c.value==d->cards[i]->value && c.suit==d->cards[i]->suit) {
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  for (int i=0; i<d->n_cards; i++) {
    int randomIndex = random() % d->n_cards;
    card_t * tmp = d->cards[i];
    d->cards[i] = d->cards[randomIndex];
    d->cards[randomIndex] = tmp;
  }
}

void assert_full_deck(deck_t * d) {
  assert(d->n_cards==52);
  for (unsigned i=0; i<52; i++) {
    assert(deck_contains(d, card_from_num(i))==1);
  }
}

void add_card_to(deck_t * deck, card_t c) {
  deck->n_cards++;
  deck->cards = realloc(deck->cards, deck->n_cards * sizeof(*deck->cards));
  deck->cards[deck->n_cards-1] = malloc(sizeof(*deck->cards[deck->n_cards-1]));
  *deck->cards[deck->n_cards-1] = c;
}

card_t * add_empty_card(deck_t * deck) {
  card_t c;
  c.value = 0;
  c.suit = NUM_SUITS;
  add_card_to(deck, c);
  return deck->cards[deck->n_cards-1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t * d = malloc(sizeof(*d));
  d->n_cards = 0;
  d->cards = malloc(sizeof(*d->cards));
  card_t c;
  for(unsigned i=0; i<52; i++) {
    c = card_from_num(i);
    if (deck_contains(excluded_cards, c)==0) {
      add_card_to(d, c);
    }
  }
  return d;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * d = malloc(sizeof(*d));
  d->n_cards = 0;
  d->cards = malloc(sizeof(*d->cards));
  for (size_t h=0; h<n_hands; h++) {
    for (size_t c=0; c<hands[h]->n_cards; c++) {
      add_card_to(d, *hands[h]->cards[c]);
    }
  }

  d = make_deck_exclude(d);

  return d;
}

void free_deck(deck_t * deck) {
  for (size_t i=0; i<deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
