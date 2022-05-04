#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node{
  char *data;
  struct Node* nextNode;
} Node;

void freeNode(Node* node)
{
  node->nextNode == NULL;
  free(node->data);
  free(node);
}

Node* createNode()
{
  Node* node = (Node*)malloc(1 * sizeof(Node));
  if(node == NULL)
  {
   printf("Couldn't allocate memory for node!");
  }

  node->data = NULL;
  node->nextNode == NULL;
  return node;
}

Node* addToNode(char* line)
{
  Node* node = createNode();
  node->data = (char*)calloc((strlen(line) + 1), sizeof(char));
  if(node->data == NULL)
  {
    free(node);
    return 0;
  }
  memcpy(node->data, line, (strlen(line) + 1) * sizeof(char));
  node->nextNode = NULL;
  return node;
}

void freeList(Node* head)
{
  Node* nextNode = head->nextNode;
  Node* savedNode = NULL;
  while (nextNode != NULL)
  {
    savedNode = nextNode->nextNode;
    freeNode(nextNode);
    nextNode = savedNode;
  }
  freeNode(head);
}

void printList(Node* head)
{
  Node* node;

  for (node = head->nextNode; node != NULL; node = node->nextNode)
  {
    printf("%s", node->data);
  }
}

int main()
{
 char buf[BUFSIZ];

 Node* head = createNode();
 if(head == NULL)
 {
  printf("Couldn't allocate memory for head!");
  return 0;
 }

 Node* currentNode = head;
 printf("Type a string\n");

 while(fgets(buf, BUFSIZ, stdin) != NULL)
 {
  if(buf[0] == '.')
  {
    break;
  }
  currentNode->nextNode = addToNode(buf);
    if(currentNode->nextNode == NULL)
  {
    perror("No memory");
    freeList(head);
    return 0;
  }
  currentNode = currentNode->nextNode;
 }
 printList(head);
 freeList(head);
 return 0;
}

