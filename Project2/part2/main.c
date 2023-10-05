#include <stdio.h>
#include <stdlib.h>

// Declare a heap structure
struct Heap
{
  node **arr;
  int size;
  int capacity;
};

// define the struct Heap name
typedef struct Heap heap;

struct node
{
  int vertex;
  int weight;
  struct node *next;
};

struct Graph
{
  int numVertices;
  int numEdges;
  struct node **adjLists;
};

typedef struct node node;
typedef struct Graph Graph;

// forward declarations
heap *createHeap(int capacity, node **nums);
void insertHelper(heap *h, int index);
void heapify(heap *h, int index);
int extractMin(heap *h);
void insert(heap *h, int data);
node *createNode(int v, int w);
Graph *createAGraph(int vertices);
void addEdge(Graph *graph, int s, int d, int w);
void printGraph(Graph *graph);
void dijkstra(Graph *graph, int src);

//////////////////////////////// ADJ LIST GRAPH ///////////////////////////////////

// Create a node
node *createNode(int v, int w)
{
  node *newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->weight = w;
  newNode->next = NULL;
  return newNode;
}

// Create a graph
Graph *createAGraph(int vertices)
{
  Graph *graph = malloc(sizeof(Graph));
  graph->numVertices = vertices;
  graph->numEdges = 0;

  graph->adjLists = malloc(vertices * sizeof(node *));

  int i;
  for (i = 0; i < vertices; i++)
    graph->adjLists[i] = NULL;

  return graph;
}

// Add edge
void addEdge(Graph *graph, int s, int d, int w)
{
  // Add edge from s to d
  node *newNode = createNode(d, w);
  newNode->next = graph->adjLists[s];
  graph->adjLists[s] = newNode;
}

// Print the graph
void printGraph(Graph *graph)
{
  int v;
  for (v = 0; v < graph->numVertices; v++)
  {
    node *temp = graph->adjLists[v];
    printf("\n Vertex %d: ", v);
    while (temp)
    {
      printf("%d[%d] -> ", temp->vertex, temp->weight);
      temp = temp->next;
    }
    printf("\n");
  }
}

//////////////////////////////// HEAP ///////////////////////////////////

// Define a createHeap function
heap *createHeap(int capacity, node **nodes)
{
  // Allocating memory to heap h
  heap *h = (heap *)malloc(sizeof(heap));

  // Checking if memory is allocated to h or not
  if (h == NULL)
  {
    printf("Memory error");
    return NULL;
  }
  // set the values to size and capacity
  h->size = 0;
  h->capacity = capacity;

  // Allocating memory to array
  h->arr = (node **)malloc(capacity * sizeof(node *));

  // Checking if memory is allocated to h or not
  if (h->arr == NULL)
  {
    printf("Memory error");
    return NULL;
  }
  int i;
  for (i = 0; i < capacity; i++)
  {
    h->arr[i] = nodes[i];
  }

  h->size = i;
  i = (h->size - 2) / 2;
  while (i >= 0)
  {
    heapify(h, i);
    i--;
  }
  return h;
}

// Defining insertHelper function
void insertHelper(heap *h, int index)
{

  // Store parent of element at index
  // in parent variable
  int parent = (index - 1) / 2;

  if (h->arr[parent] > h->arr[index])
  {
    // Swapping when child is smaller
    // than parent element
    int temp = h->arr[parent];
    h->arr[parent] = h->arr[index];
    h->arr[index] = temp;

    // Recursively calling insertHelper
    insertHelper(h, parent);
  }
}

void heapify(heap *h, int index)
{
  int left = index * 2 + 1;
  int right = index * 2 + 2;
  int min = index;

  // Checking whether our left or child element
  // is at right index or not to avoid index error
  if (left >= h->size || left < 0)
    left = -1;
  if (right >= h->size || right < 0)
    right = -1;

  // store left or right element in min if
  // any of these is smaller that its parent
  if (left != -1 && h->arr[left] < h->arr[index])
    min = left;
  if (right != -1 && h->arr[right] < h->arr[min])
    min = right;

  // Swapping the nodes
  if (min != index)
  {
    int temp = h->arr[min];
    h->arr[min] = h->arr[index];
    h->arr[index] = temp;

    // recursively calling for their child elements
    // to maintain min heap
    heapify(h, min);
  }
}

int extractMin(heap *h)
{
  int deleteItem;

  // Checking if the heap is empty or not
  if (h->size == 0)
  {
    printf("\nHeap is empty.");
    return -999;
  }

  // Store the node in deleteItem that
  // is to be deleted.
  deleteItem = h->arr[0];

  // Replace the deleted node with the last node
  h->arr[0] = h->arr[h->size - 1];
  // Decrement the size of heap
  h->size--;

  // Call minheapify_top_down for 0th index
  // to maintain the heap property
  heapify(h, 0);
  return deleteItem;
}

int extractHeap(heap *h, int num)
{
  // Checking if the heap is empty or not
  if (h->size == 0)
  {
    printf("\nHeap is empty.");
    return -999;
  }

  // Get index of target num
  int i;
  for (i = 0; i < h->size; i++)
  {
    if (h->arr[i] == num)
    {
      break;
    }
  }
  if (i >= h->size)
  {
    return 0;
  }

  // Replace the deleted node with the last node
  h->arr[i] = h->arr[h->size - 1];
  // Decrement the size of heap
  h->size--;
  // Call minheapify_top_down for 0th index
  // to maintain the heap property
  heapify(h, 0);
  return 1;
}

// Define a insert function
void insert(heap *h, int data)
{

  // Checking if heap is full or not
  if (h->size < h->capacity)
  {
    // Inserting data into an array
    h->arr[h->size] = data;
    // Calling insertHelper function
    insertHelper(h, h->size);
    // Incrementing size of array
    h->size++;
  }
}

// Function to print the heap
void printHeap(heap *h)
{

  for (int i = 0; i < h->size; i++)
  {
    printf("%d ", h->arr[i]);
  }
  printf("\n");
}

//////////////////////////////// DIJKSTRA ///////////////////////////////////

void dijkstra(Graph *graph, int src)
{
  int graphSize = graph->numVertices; // size of graph
  // Array d holds the shortest dist
  int d[graphSize];
  // Array S is whether a node is visited. 1=true 0=false
  int S[graphSize];
  // Array pi gives parent of node in shortest path
  int pi[graphSize];

  // Initialise the arrays
  for (int i = 0; i < graphSize; i++)
  {
    d[i] = INT_MAX;
    S[i] = 0;
    pi[i] = -1;
  }

  d[src] = 0;

  // Insert all nodes into heap
  int v;
  int nums[graphSize];
  for (v = 0; v < graph->numVertices; v++)
  {
    node *temp = graph->adjLists[v];
    while (temp)
    {
      nums[v] = graph->adjLists[v]->vertex;
      temp = temp->next;
    }
  }
  heap *hp = createHeap(graphSize, nums);
  printHeap(hp);

  // Run algo
  while (hp->size > 0)
  {
    int u = extractMin(hp);
    printf("%d", u);
    S[u] = 1; // Add u to S

    node *temp = graph->adjLists[u];
    while (temp)
    {
      int v = temp->vertex;
      int weight = temp->weight;

      if (S[v] != 1 && d[v] > d[u] + weight)
      {
        d[v] = d[u] + weight;
        pi[v] = u;
      }
      temp = temp->next;
    }
  }
  printf("Shortest path by index: ");
  for (int i = 0; i < graph->numVertices; i++)
  {
    printf("%d", d[i]);
  }
}

//////////////////////////////// MAIN ///////////////////////////////////
int main()
{
  int arr[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  heap *hp = createHeap(9, arr);

  printHeap(hp);
  extractMin(hp);
  printHeap(hp);

  Graph *graph = createAGraph(9);
  addEdge(graph, 0, 1, 4);
  addEdge(graph, 0, 7, 8);
  addEdge(graph, 1, 7, 11);
  addEdge(graph, 7, 1, 11);
  addEdge(graph, 1, 2, 8);
  addEdge(graph, 7, 8, 7);
  addEdge(graph, 7, 6, 1);
  addEdge(graph, 1, 2, 8);
  addEdge(graph, 2, 8, 2);
  addEdge(graph, 2, 5, 4);
  addEdge(graph, 6, 5, 2);
  addEdge(graph, 2, 3, 7);
  addEdge(graph, 3, 5, 14);
  addEdge(graph, 3, 4, 9);
  addEdge(graph, 5, 4, 10);

  printGraph(graph);

  dijkstra(graph, 0);

  return 0;
}
