#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(Dijkstra, small){
  Graph G;
  std::ifstream infile("../src/small.txt");
  ASSERT_TRUE(infile.is_open()) << "Failed to open small.txt";
  
  infile >> G;
  infile.close();
  
  EXPECT_EQ(G.numVertices, 4);  // Verify correct number of vertices

  vector<int> previous;
  vector<int> distances = dijkstra_shortest_path(G, 0, previous);

  // Expected distances from node 0
  vector<int> expected_distances = {0, 3, 6, 1}; 
  EXPECT_EQ(distances, expected_distances);

  // Verify the shortest path to node 2
  vector<int> path = extract_shortest_path(distances, previous, 2);
  vector<int> expected_path = {0, 3, 1, 2};
  EXPECT_EQ(path, expected_path);
}