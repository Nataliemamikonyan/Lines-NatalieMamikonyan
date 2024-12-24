#include <SFML/Graphics.hpp>
#include <iostream>
// #include <vector>
// #include "includes/queue/MyQueue.h"
#include "includes/animate.h"

using namespace std;

int main()
{
    animate game;
    game.run();
    cout << endl
         << endl
         << "------ MAIN EXITING --------------------------" << endl;
    return 0;
}


// void findPath(sf::Vector2i start, sf::Vector2i end, vector<vector<int>>& paths)
// {

//     vector<vector<bool>> visited(paths.size(), vector<bool>(paths[0].size(), false));

//     // [0] up, [1] down, [2] left, [3] right
//     sf::Vector2i directions[4] = {sf::Vector2i(-1, 0), sf::Vector2i(1, 0), sf::Vector2i(0, -1), sf::Vector2i(0, 1)};

//     Queue<sf::Vector2i> q; // keeping track of the current cell to explore
//     q.push(start);  // the beginning of the traversal
//     visited[start.x][start.y] = true;  // keeping track of which cells we visit
//     paths[start.x][start.y] = 0;  // marking the starting point

//     sf::Vector2i current = q.front();
//     while (!q.empty() && current != end)  // loops until there is no more cells to visit
//     {
//         q.pop();  

//         // Explore all 4 possible directions
//         for (int i = 0; i < 4; i++)
//         {
//             int newX = current.x + directions[i].x;
//             int newY = current.y + directions[i].y;  

//             // check if the new position is valid and not visited
//             if (newX >= 0 && newY >= 0 && newX < paths.size() && newY < paths[i].size() && !visited[newX][newY])
//             {
//                 visited[newX][newY] = true; // set cell to visited
//                 paths[newX][newY] = paths[current.x][current.y] + 1;  // increment path distance
//                 q.push(sf::Vector2i(newX, newY));
//             }
//         }
//         current = q.front();
//     }

//     // Print the final path matrix
//     for (int i = 0; i < paths.size(); i++)
//     {
//         for (int j = 0; j < paths.size(); j++)
//         {
//             cout << paths[i][j] << " ";
//         }
//         cout << endl;
//     }
//     cout << endl;
// }

// const int GRID_SIZE = 3;
// const sf::Vector2i DIRECTIONS[4] = {sf::Vector2i(-1, 0), sf::Vector2i(1, 0), sf::Vector2i(0, -1), sf::Vector2i(0, 1)};

// vector<sf::Vector2i> findFinalPath(sf::Vector2i start, sf::Vector2i end, vector<vector<int>> paths)
// {
//     vector<sf::Vector2i> finalPath;
//     sf::Vector2i current = end;
//     finalPath.insert(finalPath.begin(), current);

//     while(current != start)
//     {
//         int currentNum = paths[current.x][current.y];
//         for (int i = 0; i < 4; i++)
//         {
//             int newX = current.x + DIRECTIONS[i].x;
//             int newY = current.y + DIRECTIONS[i].y;

//             if(newX >= 0 && newY >= 0 && newX < GRID_SIZE && newY < GRID_SIZE && currentNum - 1 == paths[newX][newY])
//             {   
//                 current = sf::Vector2i(newX, newY);
//                 finalPath.insert(finalPath.begin(), current);
//                 break;
//             }
//         }
//         if(finalPath.size() == 1)
//         {
//             finalPath.pop_back();
//             cout << "NO VALID PATH" << endl;
//             return finalPath; 
//         }
//     }

//     for(int i = 0; i < finalPath.size(); i++)
//     {
//         cout << "(" << finalPath[i].x << ", " << finalPath[i].y << ")" << endl;
//     }

//     return finalPath;

// }

// vector<sf::Vector2i> findPaths(sf::Vector2i start, sf::Vector2i end)
// {
//     vector<vector<int>> paths(GRID_SIZE, vector<int>(GRID_SIZE, -1)); // -1 means not visited

//     vector<vector<int>> adj_matrix(GRID_SIZE, vector<int>(GRID_SIZE, 0));
//     // adj_matrix[2][1] = 6;
//     // adj_matrix[1][1] = 6;

//     Queue<sf::Vector2i> q; // keeping track of the current cell to explore
//     q.push(start);  // the beginning of the traversal
//     paths[start.x][start.y] = 0;  // marking the starting point

//     while (!q.empty())  // loops until there is no more cells to visit
//     {
//         sf::Vector2i current = q.front();
//         q.pop();

//         if (current == end) 
//             break;

//         for (int i = 0; i < 4; i++)  // explore all 4 possible directions
//         {
//             int newX = current.x + DIRECTIONS[i].x;
//             int newY = current.y + DIRECTIONS[i].y;  

//             // check if the new position is valid and not visited
//             if (newX >= 0 && newY >= 0 && newX < GRID_SIZE && newY < GRID_SIZE && paths[newX][newY] == -1 && adj_matrix[newX][newY] == 0)
//             {
//                 paths[newX][newY] = paths[current.x][current.y] + 1;  // increment path distance
//                 q.push(sf::Vector2i(newX, newY));
//             }
//         }
//     }

//     cout << "Path matrix:" << endl;
//     for (int i = 0; i < GRID_SIZE; i++)
//     {
//         for (int j = 0; j < GRID_SIZE; j++)
//         {
//             cout << paths[i][j] << " ";
//         }
//         cout << endl;
//     }
//     cout << endl;

//     return findFinalPath(start, end, paths);

// }


// int main()
// {
//     sf::Vector2i start(2, 2);  
//     sf::Vector2i end(0, 0);   

//     vector<vector<int>> paths(GRID_SIZE, vector<int>(GRID_SIZE, -1)); // -1 means not visited

//     vector<vector<int>> adj_matrix(GRID_SIZE, vector<int>(GRID_SIZE, 0));
//     vector<vector<bool>> visited(GRID_SIZE, vector<bool>(GRID_SIZE, false));
//     Queue<sf::Vector2i> q;

//     findPaths(start, end);


//     return 0;
// }