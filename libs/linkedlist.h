#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Celula {
  char * str;
  int lin;
  int col;
  struct Celula * next;
} Celula;

typedef struct {
  unsigned hash;
  struct Celula * next;
} Cabeca;

#endif /* LINKEDLIST_H */
