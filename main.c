/* This program will read the first 3 lines of input 
   and print a static 2D maze
   Code by: Sai Samarth
   Date: 03/01/2021 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE   1
#define FALSE  0

// variable for debugmode
int debugMode = FALSE;

typedef struct mazeStruct {
    char **arr; // a 2D array that we can grow
    int xsize, ysize;  // variables to hold the x and y values
    int xstart, ystart;  // variables to hold the coordinates of the starting position
    int xend, yend;  // variables to hold the coordinates of the end position
} maze;

typedef struct stackNode {
    int x, y;
    struct stackNode *next;
} node;

/* prototypes of the functions used in this code  */

void init(maze * m1);
void push(node ** hd, int xVal, int yVal);
void pop(node ** hd);
int isEmpty (node * hd);
void printElement (node * hd);
node* top (node ** hd);
void clear (node ** hd);
int isEnd (maze m, int x, int y);
void checkCoins(char c, int *coins);
void printSize(int xsize, int ysize);
void printStart(int xstart, int ystart);

/********************************************************
 * Function:       init
 * Parrameters:    C-style pass-by-reference maze 
 * Return value:   none
 *******************************************************/
void init(maze * m1) {
    m1->arr = (char**)malloc(sizeof(char*)*(m1->xsize+2)); // creating a new 2D array
    for (int i = 0; i < m1->xsize+2; i++) {
        m1->arr[i] = (char*)malloc(sizeof(char)*(m1->ysize+2));
    }
}

/********************************************************
 * Function:       push
 * Parrameters:    C-style pass-by-reference head pointer 
 *                 two int x and y values to be added to the linked list
 * Return value:   none
 *******************************************************/
void push (node ** hd, int xVal, int yVal) {
    node *ptr = (node *) malloc (sizeof (node));
    ptr->x = xVal;
    ptr->y = yVal;
    ptr->next = *hd;		/* note that hd must be "de-referenced" when used */
    *hd = ptr;			/*   the unary * operator is the "de-reference" operator */
    if (debugMode) {
        printf ("(%d,%d) pushed into the stack.\n", xVal, yVal);
    }
}

/********************************************************
 * Function:       pop
 * Parrameters:    C-style pass-by-reference head pointer 
 * Return value:   None
 *******************************************************/
void pop (node ** hd) {
    int x, y;
    node *ptr = *hd;
    if (ptr != NULL) {
        x = ptr->x;
        y = ptr->y;
        *hd = ptr->next;
        free (ptr);  // freeing the pointer
    }
    if (debugMode) {  // checks for the debugMode
        printf ("(%d,%d) popped off the stack.\n", x, y);
    }
}

/********************************************************
 * Function:       isEmpty
 * Parrameters:    C-style pass-by-value head pointer 
 * Return value:   int value 
 *******************************************************/
int isEmpty (node * hd) {
    if (hd == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/********************************************************
 * Function:       printElement
 * Parrameters:    C-style pass-by-value head pointer 
 * Return value:   none
 *
 * Display the items in a list 
 *******************************************************/
void printElement (node * hd) {
    if (!hd) {
        return;
    }
    printElement (hd->next);
    printf ("(%d,%d) ", hd->x, hd->y);
}

/********************************************************
 * Function:       top
 * Parrameters:    C-style pass-by-referece head pointer 
 * Return value:   node
 *******************************************************/
node* top (node ** hd) {
    return *hd;
}

/********************************************************
 * Function:       clear
 * Parrameters:    C-style pass-by-reference head pointer 
 * Return value:   int value 
 *******************************************************/
void clear (node ** hd) {
    while (!isEmpty (*hd)) {
        pop (hd);
    }
}

/********************************************************
 * Function:       isEnd
 * Parrameters:    C-style pass-by-value maze, int x and int y 
 * Return value:   int value 
 *******************************************************/
int isEnd (maze m, int x, int y) {
    if (x == m.xend && y == m.yend) {
        return 1;
    }
    return 0;
}

/********************************************************
 * Function:       checkCoins
 * Parrameters:    Char c, int coins passed-by-reference 
 * Return value:   void 
 *******************************************************/
void checkCoins(char c, int *coins) {
    if (c == 'C') {
        (*coins)++;
    }
}

/********************************************************
 * Function:       printSize
 * Parrameters:    int xsize and int ysize 
 * Return value:   void 
 *******************************************************/
void printSize(int xsize, int ysize) {
    if (xsize <= 0 || ysize <= 0) {
        printf ("Maze sizes must be greater than 0.\n");
        exit (-1);
    }

  /* print them out to verify the input */
  printf ("size: %d, %d\n", xsize, ysize);
}

/********************************************************
 * Function:       printStart
 * Parrameters:    int xstart and int ystart 
 * Return value:   void 
 *******************************************************/
void printStart(int xstart, int ystart) {
    if (xstart < 0 || ystart < 0) {
        printf ("Start/End position outside of maze range.\n");
        exit (-1);
    }
  
   /* prints the starting coordinates*/
  printf ("start: %d, %d\n", xstart, ystart);
}

/********************************************************
 * Function:       printEnd
 * Parrameters:    int xend, int yend, int xsize and int ysize 
 * Return value:   void
 *******************************************************/
void printEnd(int xend, int yend, int xsize, int ysize) {
    if (xend > xsize || yend > ysize) {
        printf ("Start/End position outside of maze range.\n");
        exit (-1);
    }
  
   /* prints the end coordinates*/
  printf ("end: %d, %d\n", xend, yend);
}

/********************************************************
 * Function:       main
 * Parrameters:    int argc and char **argv 
 * Return value:   int value 
 *******************************************************/
int main (int argc, char **argv) {
  // creating a list with just a pointer to head
  // initializing the head to null indicating that the list is empty
  node *hd = NULL;
  node *hd1 = NULL;
  maze m1;
  int xpos, ypos;
  int i, j;
  
  // checking for the debugging character
  for (int i = 0; i < argc; i++) {
      if (strcmp (argv[i], "-d") == 0) {
          debugMode = 1;
          break;
      }
  }
  
  FILE *src;

  /* verify the proper number of command line arguments were given */
  if (argc != 2 && !(debugMode == 1 && argc == 3)) {
      printf ("Usage: %s <input file name>\n", argv[0]);
      exit (-1);
  }

  /* Try to open the input file. */
  if ((src = fopen (argv[1], "r")) == NULL) {
      printf ("Can't open input file: %s", argv[1]);
      exit (-1);
  }

  /* read in the size, starting and ending positions in the maze */
  if (fscanf (src, "%d %d", &m1.xsize, &m1.ysize) != 2) {
      printf ("Invalid data file.\n");
      exit (-1);
  }
  
  /* checks if there are two values for the starting coordinates*/
  if (fscanf (src, "%d %d", &m1.xstart, &m1.ystart) != 2) {
      printf ("Invalid data file.\n");
      exit (-1);
  }
  
  /* checks if there are two values for the end coordinates*/
  if (fscanf (src, "%d %d", &m1.xend, &m1.yend) != 2) {
      printf ("Invalid data file.\n");
      exit (-1);
  }
  
   /* checks if the x and y sizes of the maze are over 0*/
   printSize(m1.xsize, m1.ysize);
  
   /* checks if the starting coordinates are valid or in the maze*/
   printStart(m1.xstart, m1.ystart);
  
   /* checks if the end coordinates are outside the maze*/
   printEnd(m1.xend, m1.yend, m1.xsize, m1.ysize);
  
   /* initialize the maze*/
   init(&m1);

  /* initialize the maze to empty */
  for (i = 0; i < m1.xsize + 2; i++) {
      for (j = 0; j < m1.ysize + 2; j++) {
          m1.arr[i][j] = '.';
      }
  }

  /* mark the borders of the maze with *'s */
  for (i = 0; i < m1.xsize + 2; i++) {
      m1.arr[i][0] = '*';
      m1.arr[i][m1.ysize + 1] = '*';
  }
  
  for (i = 0; i < m1.ysize + 2; i++) {
      m1.arr[0][i] = '*';
      m1.arr[m1.xsize + 1][i] = '*';
  }

  /* mark the starting and ending positions in the maze */
  m1.arr[m1.xstart][m1.ystart] = 's';
  m1.arr[m1.xend][m1.yend] = 'e';
 
  int x, y;
  char c;
  // places the blocked positions and coins in the maze
  while (fscanf (src, "%d %d %c", &x, &y, &c) != EOF) {
      if (x > m1.xsize || y > m1.ysize) {
          printf ("Invalid coordinates: outside of maze range.\n"); // prints error message if the given coordinates are outside the maze
      } else if ((x == m1.xstart && y == m1.ystart) || (x == m1.xend && y == m1.yend)) {
          printf("Invalid coordinates: attempting to block start/end position.\n"); // prints error message if trying to block the start or end
      } else if (c == 'b') {
          m1.arr[x][y] = '*';  // blocked positions are marked by * in the maze
      } else if (c == 'c') {
          m1.arr[x][y] = 'C';  // coin positions are marked by C in the maze
      } else if (c != 'b' || c != 'c') {
          printf ("Invalid type: type is not recognized.\n");  // prints error if the character is invalid
      }
  }

  /*Close the file */
  fclose (src);

  for (i = 0; i < m1.xsize + 2; i++) {
      /* print out the initial maze */
      for (j = 0; j < m1.ysize + 2; j++)
      printf ("%c", m1.arr[i][j]);
      printf ("\n");
  }

  int coins = 0;
  push (&hd, m1.xstart, m1.ystart);
  int xVal = m1.xstart;
  int yVal = m1.ystart;
  
  // algorithm to find a way out of the maze
  while (!(isEmpty (hd)) && !(hd->x == m1.xend && hd->y == m1.yend)) { // keeps going until the stack is empty or if the end is found
      xVal = hd->x;
      yVal = hd->y;
      if (m1.arr[xVal + 1][yVal] != '*') { // checks if going down is possible
          xVal++;
          push (&hd, xVal, yVal);
          checkCoins(m1.arr[xVal][yVal], &coins); // checks if it has a coin
          m1.arr[xVal][yVal] = '*';
      } else if (m1.arr[xVal][yVal + 1] != '*') { // checks if going right is possible
          yVal++;
          push (&hd, xVal, yVal);
          checkCoins(m1.arr[xVal][yVal], &coins); // checks if it has a coin
          m1.arr[xVal][yVal] = '*';
      } else if (m1.arr[xVal - 1][yVal] != '*') { // checks if going up is possible
          xVal--;
	      push (&hd, xVal, yVal);
	      checkCoins(m1.arr[xVal][yVal], &coins); // checks if it has a coin
	      m1.arr[xVal][yVal] = '*';
      } else if (m1.arr[xVal][yVal - 1] != '*') { // checks if going left is possible
          yVal--;
          push (&hd, xVal, yVal);
          checkCoins(m1.arr[xVal][yVal], &coins); // checks if it has a coin
          m1.arr[xVal][yVal] = '*';
      } else {
          pop (&hd);
      }
  }
  
  // printing the results of the maze
  if (isEmpty (hd)) { // has no solution if the stack is empty
      printf ("\n");
      printf ("\n");
      printf ("This maze has no solution.\n");
  } else {
      printf ("\n");
      printf ("\n");
      // printing the details if successfully exited the maze
      printf ("The maze has a solution.\n");
      printf ("The amount of coins collected: %d\n", coins);
      printf ("The path from start to end: \n");
      printElement (hd);
      clear (&hd); // clearing the stack after everything
  }
    // freeing each column of the 2D array
    for (int i = 0; i < m1.xsize+2; i++) {
        free(m1.arr[i]);
    }
    
    // freeing the whole array
    free(m1.arr);
}