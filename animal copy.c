// animal.c

#include <stdio.h>
#include "animal.h"
#include <assert.h>

node *head;
node *current;
int answerToMostRecentQuestion;

int yesOrNo() {
  char choice;
  scanf(" %c",&choice);
  if (choice == 'y')
    return 0;
  else 
    return 1;
}

node *new_node (char *text, node *prev, int yOrN, node *yesNode, node *noNode) {
  node *n = (node *) malloc(sizeof(node));
  assert(n != NULL);

  n->text = text;
  n->prev = prev;
  n->yOrN = yOrN;
  n->yesNode = yesNode;
  n->noNode = noNode;

  return n;
}

int main(int argc, char *argv) {
  printf("Welcome to the Animal Game!\n");
  
  head = new_node ("Does your animal have four legs?\n",NULL,-1,NULL,NULL);
  node *horse = new_node("horse",head,0,NULL,NULL);
  node *goldfish = new_node("goldfish",head,1,NULL,NULL);
  head->yesNode = horse;
  head->noNode = goldfish;
  current = head;

  play();
}

void play () {
  if (current->yesNode == NULL) {
    printf("Is your animal a %s?\n",current->text);
    int answer = yesOrNo();
    if (answer == 0) {
      printf("I win!\n");
      winPlayAgain();
    }
    else
      update();
  }
  else {
    printf("%s",current->text);
    answerToMostRecentQuestion = yesOrNo();
    if (answerToMostRecentQuestion == 0)
      current = current->yesNode;
    else
      current = current->noNode;
    play();
  }
}

void update() {
  printf("I lose.\nYour animal is a: ");
  char answer[30];
  scanf("%30s",&answer);
  printf("\nPlease state a question that is true of a %s but false of a %s: ",answer,current->text); 
  int size = 150;
  char *question = (char *) malloc (size + 1);
  getline(&question,&size,stdin);
  getline(&question,&size,stdin);
  node *newQuestion = new_node(question,current->prev,answerToMostRecentQuestion,NULL,NULL);
  node *newAnimal = new_node(answer,newQuestion,answerToMostRecentQuestion,NULL,NULL);
  node *guessedAnimal;
  if (answerToMostRecentQuestion == 0) {
    guessedAnimal = current->prev->yesNode;
    current->prev->yesNode = newQuestion;
  }
  else {
    guessedAnimal = current->prev->noNode;
    current->prev->noNode = newQuestion;

  }
  newQuestion->yesNode = newAnimal;
  newQuestion->noNode = guessedAnimal;
  winPlayAgain();
}

void winPlayAgain() {
  printf("Would you like to play again?\n");
  int playAgain = yesOrNo();
  if (playAgain == 0) {
    current = head;
    play();
  }
  else
    printf("Goodbye.\n");
}

