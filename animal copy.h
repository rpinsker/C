// animal.h

struct game_node {
  char *text; //animal or question
  struct game_node *prev;
  int yOrN; // answer to previous question. 0 = yes, 1 = no
  struct game_node *yesNode; // NULL when node is an animal
  struct game_node *noNode; // NULL when node is an animal
};

typedef struct game_node node;

int yesOrNo();
char *getLine();
node *new_node (char *text, node *prev, int yOrN, node *yesNode, node *noNode);

void play();

void update();
void winPlayAgain(); 
