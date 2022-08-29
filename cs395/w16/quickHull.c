/*********************************************
 * Id: rome9162
 *
 * Convex Hull 
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

float sqroot(float val);
void convexHull(int[], int[], int);
bool convexCheck(int[], int[], int);
bool planeCheck(int line[], int index, int xPoints[], int yPoints[], int points);
int insertNode(int value, int index);
int getNode(int key);
int getIndex(int key);
int numNodes();
void deleteNode(int key);
void addNode(int value);

int main(int argc, char* argv[])
{
   if (argc > 1 && (argc-1) % 2 == 0)
   {
      int points = (argc - 1) / 2;

      int yPoints[points];
      int xPoints[points];

      int i, x = 0, y = 0;
      for(i = 1; i <= points*2; i++)
      {
         if(i % 2 == 0)
         {
            yPoints[y++] = atoi(argv[i]);
         }
         else
         {
            xPoints[x++] = atoi(argv[i]);
         }
      }

      convexHull(xPoints, yPoints, points);

      while(convexCheck(xPoints, yPoints, points) == false);

      printf("The points in Convex Hull are:\n");
      for(i = 0; i < numNodes(); i++)
      {
         printf("(%d, %d) ", xPoints[getNode(i)], yPoints[getNode(i)]);
      }
      printf("\n\n");
   }
   else
   {
      printf("Must include an even amount of integers\n");
   }

   return 0;
}

//This struct holds all extreme points
struct node {
   struct node *next;
   int extremePoint;
};

struct node *head = NULL;

//This function adds values to the node incrementally
void addNode(int value) {
   struct node *n = (struct node*) malloc(sizeof(struct node));
   struct node *p = (struct node*) malloc(sizeof(struct node));
   p = head;
   n->extremePoint = value;
   n->next = NULL;
   
   if(head == NULL)
   {
      head = n;
   }
   else
   {
      while(p->next != NULL) {
         p = p->next;
      }
      p->next = n;
   }
}

//This function removes nodes based on their key
void deleteNode(int key)
{
   struct node *temp = (struct node*) malloc(sizeof(struct node));
   struct node *prev = (struct node*) malloc(sizeof(struct node));
   temp = head;
   prev = NULL;

   if (temp != NULL && temp->extremePoint == key)
   {
      head = temp->next;
      free(temp);
      return;
   }
   else
   {
      while (temp != NULL && temp->extremePoint != key)
      {
         prev = temp;
         temp = temp->next;
      }

      if (temp == NULL)
      {
         return;
      }

      prev->next = temp->next;

      free(temp);
   }
}

//This function adds a vlue to a specific index
int insertNode(int value, int index) {
  
   if (!head) {
      return 0;
   }
   
   int i;
   struct node* newNode = (struct node*)malloc(sizeof(struct node));
   struct node *scan = head;
   newNode->extremePoint = value;
   newNode->next = 0;
   
   if (scan == NULL && index == 0) {
      newNode->next = head;
      head = newNode;
      return 0;
   }

   for (i = 0; scan != NULL && i <= index; i++) {
      if (i == index) {
         newNode->next = scan->next;
         scan->next = newNode;
      }
      else {
         scan = scan->next;
      }
   }
   return (scan != NULL);
}

//This function prints the linked list
void printNodes() {
   struct node *n = head;
   while(n != NULL) {
      printf("%d ", n->extremePoint);
      n = n->next;
   }
   printf("\n");
}

//This function returns the value of a given indexed node
int getNode(int key) {
   struct node *n = head;
   int incr = 0;
   while(n != NULL) {
      if (incr++ == key)
      {
         return n->extremePoint;
      }
      n = n->next;
   }
   return -1;
}

//This function returns the index of a given value
int getIndex(int key) {
   struct node *n = head;
   int incr = 0;
   int tempIncr = -1;
   while(n != NULL) {
      if (n->extremePoint == key)
      {
         tempIncr = incr++;
      }
      else
      {
         incr++;
      }
      n = n->next;
   }
   return tempIncr;
}

//This function returns the total number of nodes
int numNodes() {
   struct node *n = head;
   int incr = 0;
   while(n != NULL) {
      incr++;
      n = n->next;
   }
   return incr;
}

//This functio calculates the square root of a given value
float sqroot(float value)
{
   float temp = 0;
   float sqrt = value / 2;
   while(sqrt != temp){
      temp = sqrt;
      sqrt = ((value /temp) + temp) / 2;
   }

   return sqrt;
}

//This function adds the initial extreme points based on extremities
void convexHull(int xPoints[], int yPoints[], int points)
{
   int xMin = 0;
   int xMax = 0;
   int yMin = 0;
   int yMax = 0;

   int i;
   for(i = 0; i < points; i++)
   {
      if (xPoints[i] > xPoints[xMax])
      {
         xMax = i;
      }
      if (xPoints[i] < xPoints[xMin])
      {
         xMin = i;
      }
      if (yPoints[i] > yPoints[yMax])
      {
         yMax = i;
      }
      if (yPoints[i] < yPoints[yMin])
      {
         yMin = i;
      }
   }

   for(i = 0; i < points; i++)
   {
      if (xPoints[i] == xPoints[xMin] && i != xMin)
      {
         if (yPoints[i] < yPoints[xMin])
         {
            xMin = i;
         }
      }
      if (yPoints[i] == yPoints[yMax] && i != yMax)
      {
         if (xPoints[i] < xPoints[yMax])
         {
            yMax = i;
         }
      }
      if (xPoints[i] == xPoints[xMax] && i != xMax)
      {
         if (yPoints[i] > yPoints[xMax])
         {
            xMax = i;
         }
      }
      if (yPoints[i] == yPoints[yMin] && i != yMin)
      {
         if (xPoints[i] > xPoints[yMin])
         {
            yMin = i;
         }
      }
   }

   addNode(xMin);
   if (yMax == xMax)
   {
      addNode(xMax);
   }
   else
   {
      addNode(yMax);
      addNode(xMax);
   }
   if (yMin != xMin && yMin != xMax)
   {
      addNode(yMin);
   }
   addNode(xMin);
}

//This function returns true or false whether the convex hull is correct
bool convexCheck(int xPoints[], int yPoints[], int points)
{
   int i;
   bool hullCheck = true;

   int size = numNodes();

   int x1[size - 1];
   int y1[size - 1];
   int x2[size - 1];
   int y2[size - 1];
   int indexArr[size - 1];

   for(i = 0; i < size-1; i++)
   {
      x1[i] = xPoints[getNode(i)];
      y1[i] = yPoints[getNode(i)];
      x2[i] = xPoints[getNode(i + 1)];
      y2[i] = yPoints[getNode(i + 1)];
      indexArr[i] = getNode(i + 1);
   }

   for(i = 0; i < size-1; i++)
   {
      int line[] = {x1[i], y1[i], x2[i], y2[i], indexArr[i]};
      if (planeCheck(line, i, xPoints, yPoints, points) == false)
      {
         hullCheck = false;
      }
   }

   return hullCheck;
}

//This function checks whether there exists points outside of a given line
bool planeCheck(int line[], int index, int xPoints[], int yPoints[], int points)
{
   bool hullCheck = true;
   int x1 = line[0];
   int y1 = line[1];
   int x2 = line[2];
   int y2 = line[3];
   //printNodes();
   //printf("Checking (%d, %d) to (%d, %d)\n", x1, y1, x2, y2);

   int a = y2 - y1;
   int b = x1 - x2;
   int c = x1*y2 - x2*y1;

   int i = 0;
   int incr = 0;

   for(i = 0; i < points; i++)
   {
      int x = xPoints[i];
      int y = yPoints[i];

      if (a*x + b*y < c)
      {
         incr++;
      }
   }

   int outsidePoints[incr];
   incr = 0;
   
   for(i = 0; i < points; i++)
   {
      int x = xPoints[i];
      int y = yPoints[i];

      if (a*x + b*y < c)
      {
         hullCheck = false;
         printf("Didn't pass");

         //outsidePoints[incr++] = i;
      }
   }
   printf("\n");

   if(hullCheck == false)
   {
      int x = xPoints[outsidePoints[0]];
      int y = yPoints[outsidePoints[0]];

      int xDist1 = abs(x - x1);
      int yDist1 = abs(y - y1);
      float dist1 = sqroot(xDist1*xDist1 + yDist1*yDist1);

      int xDist2 = abs(x - x2);
      int yDist2 = abs(y - y2);
      float dist2 = sqroot(xDist2*xDist2 + yDist2*yDist2);

      float maxDist = dist1 + dist2;
      float dist;

      int node = 0;

      for(i = 0; i < incr; i++)
      {
         x = xPoints[outsidePoints[i]];
         y = yPoints[outsidePoints[i]];

         xDist1 = abs(x - x1);
         yDist1 = abs(y - y1);
         dist1 = sqroot(xDist1*xDist1 + yDist1*yDist1);

         xDist2 = abs(x - x2);
         yDist2 = abs(y - y2);
         dist2 = sqroot(xDist2*xDist2 + yDist2*yDist2);

         dist = dist1 + dist2;

         if (dist >= maxDist)
         {
            node = outsidePoints[i];
         }
      }

      if(getIndex(node) == -1)
      {
         insertNode(node, getIndex(line[4]) - 1);
      }
   }

   return hullCheck;
}
