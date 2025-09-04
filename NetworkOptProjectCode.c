#define MAX_EDGES 100 // Maximum number of edges the graph can contain
#define MAX_NODES 26 // Maximum number of nodes (A to Z)
// Structure to store each edge as a pair of nodes and its cost
typedef struct
{
int u, v, cost;
} Edge;
Edge edges[MAX_EDGES]; // Array to store all edges
int p[MAX_NODES]; // Array for Union-Find parent tracking
int numEdges = 0; // Counter to track number of edges read
// Union-Find 'find' function with path compression
int find(int x) {
return p[x] == x ? x : (p[x] = find(p[x]));
}
// Union-Find 'union' function to merge two sets
void unite(int x, int y) {
p[find(x)] = find(y);
}
// Comparator function to sort edges by cost (ascending)
int compare(const void *a, const void *b) {
return ((Edge *)a)->cost - ((Edge *)b)->cost;
}
// Convert a character node label (e.g., 'A') to an index (e.g., 0)
int nodeIndex(char c) {
return c - 'A';
}
// Read edge data from a file and store it in the edges array
void readFile() {
FILE *f = fopen("network.txt", "r"); // Open input file
if (!f) {
printf("File not found!\n");
exit(1); // Exit if file cannot be opened
}
char a, b;
int cost;
// Read each line and store as an edge
while (fscanf(f, " %c,%c,%d", &a, &b, &cost) == 3) {
edges[numEdges++] = (Edge){nodeIndex(a), nodeIndex(b), cost};
}
fclose(f); // Close the file after reading
}
int main() {
readFile(); // Load all edges from the file
// Initialise Union-Find parent array
for (int i = 0; i < MAX_NODES; i++) p[i] = i;
// Sort edges by cost in ascending order
qsort(edges, numEdges, sizeof(Edge), compare);
int total = 0; // Variable to hold total cost of the MST
printf("Edges in MST:\n");
// Kruskal’s algorithm: select edges that don’t form cycles
for (int i = 0; i < numEdges; i++) {
int u = edges[i].u, v = edges[i].v, cost = edges[i].cost;
// Check if u and v are in different components (no cycle)
if (find(u) != find(v)) {
unite(u, v); // Merge the sets
total += cost; // Add edge cost to total
// Print the selected edge (convert indices back to letters)
printf("%c - %c : %d\n", u + 'A', v + 'A', cost);
}
}
// Print total cost of the Minimum Spanning Tree
printf("Total cost: %d\n", total);
return 0;
}
