#include "system.h"
#include "random.h"
#include "constants.h"
#include "queue/MyQueue.h"
#include <iostream>


System::System() : currentCircle(0), currentPathIndex(0), inMotion(false)
{

    grid.resize(GRID_SIZE);  // resize outer vectors to hold 9 rows
    adj_matrix = vector<vector<int>>(GRID_SIZE, vector<int>(GRID_SIZE, NO_COLOR));  // initialize numerical grid to all 0's to reflect an empty grid

    for (int i = 0; i < GRID_SIZE; i++) 
    {
        grid[i].resize(GRID_SIZE);   // resize each row to have 9 columns

        for (int j = 0; j < GRID_SIZE; j++)  // initialize the cells in each row
        {
            grid[i][j].setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));  // set cell size
            grid[i][j].setOutlineColor(sf::Color(170, 51, 106));  // set outline color
            grid[i][j].setOutlineThickness(1.0);  // set outline thickness
            grid[i][j].setPosition(j * grid[i][j].getSize().x , i * grid[i][j].getSize().y);  // set position
        }
    }

    init_circles();
    // display_matrix();
}

void System::init_circles()
{
    Random r;
    int row, col, radius, color;
    float xPos, yPos; 

    int size = circles.size();
    for(int i = size; i < (size + 3); i++)
    {
        circles.push_back(sf::CircleShape(40));
        color = r.Next(1, 7);  // randomly select circle color

        circles[i].setFillColor(get_rgb(color));  // setting color depending on the number generated previously

        do // to avoid the circles being generated at the same position
        {
            row = r.Next(0, grid.size() - 1);  // getting random row position
            col = r.Next(0, grid.size() - 1);  // getting random column position
        } while (adj_matrix[row][col] != NO_COLOR);
        
        radius = circles[i].getRadius();
        xPos = grid[row][col].getPosition().x;
        yPos = grid[row][col].getPosition().y;
        adj_matrix[row][col] = color;  // updating numerical grid with added circles

        circles[i].setOrigin(radius, radius);  // setting circles origin to the center of the circle
        circles[i].setPosition(xPos + CELL_SIZE / 2 , yPos + CELL_SIZE / 2);  // setting circles position to the center of the selected rectangle
        
    }
}

sf::Color System::get_rgb(int color)
{

    switch (color)
    {
    case RED:  // 1
        return sf::Color(255,105,97);
        break;
    case ORANGE:  // 2
        return sf::Color(255, 150, 79);
        break;
    case YELLOW:  // 3
        return sf::Color(255,238,140);
        break;
    case GREEN:  // 4
        return sf::Color(179, 229, 179);
        break;
    case BLUE:  // 5
        return sf::Color(167, 199, 231);
        break;
    case PURPLE:  // 6
        return sf::Color(204, 183, 229);
        break;
    case PINK:  // 7
        return sf::Color(236, 189, 196);
        break;
    
    default:
        return sf::Color(sf::Color::Black);
        break;
    }
}

int System::get_color_number(sf::Color color)
{
    if(color == sf::Color(255,105,97))
        return RED;
    else if(color == sf::Color(255, 150, 79))
        return ORANGE;
    else if(color == sf::Color(255,238,140))
        return YELLOW;
    else if(color == sf::Color(179, 229, 179))
        return GREEN;
    else if(color == sf::Color(167, 199, 231))
        return BLUE;
    else if(color == sf::Color(204, 183, 229))
        return PURPLE;
    else if(color == sf::Color(236, 189, 196))
        return PINK;
    else
        return 99;
}

vector<sf::Vector2i> System::findPaths(sf::Vector2i start, sf::Vector2i end)
{
    vector<vector<int>> paths(GRID_SIZE, vector<int>(GRID_SIZE, -1)); // -1 means not visited

    Queue<sf::Vector2i> q; // keeping track of the current cell to explore
    q.push(start);  // the beginning of the traversal
    paths[start.x][start.y] = 0;  // marking the starting point

    while (!q.empty())  // loops until there is no more cells to visit
    {
        sf::Vector2i current = q.front();
        q.pop();

        if (current == end)  // terminate if the end position is reached
            break;

        for (int i = 0; i < 4; i++)  // explore all 4 possible directions
        {
            int newX = current.x + DIRECTIONS[i].x;
            int newY = current.y + DIRECTIONS[i].y;  

            // check if the new position is valid and not visited
            if (newX >= 0 && newY >= 0 && newX < GRID_SIZE && newY < GRID_SIZE && paths[newX][newY] == -1 && adj_matrix[newX][newY] == 0)
            {
                paths[newX][newY] = paths[current.x][current.y] + 1;  // increment path distance
                q.push(sf::Vector2i(newX, newY));
            }
        }
    }

    // cout << "Path matrix:" << endl;
    // for (int i = 0; i < GRID_SIZE; i++)
    // {
    //     for (int j = 0; j < GRID_SIZE; j++)
    //     {
    //         cout << paths[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    return findFinalPath(start, end, paths);

}

vector<sf::Vector2i> System::findFinalPath(sf::Vector2i start, sf::Vector2i end, vector<vector<int>> paths)
{
    vector<sf::Vector2i> finalPath;
    sf::Vector2i current = end;
    finalPath.insert(finalPath.begin(), current);

    while(current != start)
    {
        int currentNum = paths[current.x][current.y];
        for (int i = 0; i < 4; i++)
        {
            int newX = current.x + DIRECTIONS[i].x;
            int newY = current.y + DIRECTIONS[i].y;

            if(newX >= 0 && newY >= 0 && newX < GRID_SIZE && newY < GRID_SIZE && currentNum - 1 == paths[newX][newY])
            {   
                current = sf::Vector2i(newX, newY);
                finalPath.insert(finalPath.begin(), current);
                break;
            }
        }
        if(finalPath.size() == 1)
        {
            finalPath.pop_back();
            // cout << "NO VALID PATH" << endl;
            return finalPath; 
        }
    }

    // for(int i = 0; i < finalPath.size(); i++)
    // {
    //     cout << "(" << finalPath[i].x << ", " << finalPath[i].y << ")" << endl;
    // }

    return finalPath;

}

sf::Vector2i System::coordinatesToIndex(sf::Vector2f coords)
{
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            if(grid[i][j].getGlobalBounds().contains(coords))
                return sf::Vector2i(i,j);
        }
    }
    return sf::Vector2i(-1,-1);
}

bool System::fiveInARow(sf::Vector2i start, vector<sf::Vector2i>& coords)
{
    int newX = 0, newY = 0;
    bool sameColor = false;

    for (int i = 0; i < 4 && !sameColor; i++)
    {
        newX = start.x + DIRECTIONS[i].x;
        newY = start.y + DIRECTIONS[i].y;

        if(newX >= 0 && newY >= 0 && newX < GRID_SIZE && newY < GRID_SIZE)
            sameColor = adj_matrix[newX][newY] == adj_matrix[start.x][start.y];   // true if the same color is around the circle
    }

    if(!sameColor)
        return false;

    
    moveDirection(start, 0, coords);
    cout << "coords after up: " << coords.size() << endl;
    moveDirection(start, 1, coords);
    cout << "coords after down: " << coords.size() << endl;

    if(coords.size() < 4)
    {
        coords.clear();
        moveDirection(start, 2, coords);
        cout << "coords after left: " << coords.size() << endl;
        moveDirection(start, 3, coords);
        cout << "coords after right: " << coords.size() << endl;
    }

    coords.push_back(start);
    cout << "coords after start: " << coords.size() << endl;

    if(coords.size() >= 5)
    {
        for(int i = 0; i < coords.size(); i++)
        {
            // cout << " (" << coords[i].x << ", " << coords[i].y << ")" << endl;
            adj_matrix[coords[i].x][coords[i].y] = NO_COLOR;
        }
    }

    return coords.size() >= 5;
}

void System::moveDirection(sf::Vector2i start, int direction, vector<sf::Vector2i>& coords)
{
    int newX = start.x, newY = start.y;
    while(true)
    {
        if(newX < 0 || newY < 0 || newX >= GRID_SIZE || newY >= GRID_SIZE || adj_matrix[newX][newY] != adj_matrix[start.x][start.y])
            break;

        coords.push_back(sf::Vector2i(newX, newY));

        newX += DIRECTIONS[direction].x;
        newY += DIRECTIONS[direction].y;

    }
}

void System::display_matrix()
{
    for (int i = 0; i < GRID_SIZE; i++) 
    {
        // Initialize the cells in each row
        for (int j = 0; j < GRID_SIZE; j++) 
        {
            cout << "[ " << adj_matrix[i][j] << " ] ";
        }
        cout << endl;
    }
}


//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command, sf::Vector2f pos)
{
    if(command == LEFT_CLICK && pos.x <= WORK_PANEL && !inMotion)  // making sure there was a click and coordinates are valid
    {
        for(int i = 0; i <  circles.size(); i++)
        {
            if(circles[i].getGlobalBounds().contains(pos))  // true if a circle was selected
            {
                circles[currentCircle].setOutlineThickness(0.0);  // remove previous circle's outline
                currentCircle = i;

                circles[i].setOutlineColor(sf::Color::Black);  // outline new selected circle
                circles[i].setOutlineThickness(3.0);
                break;  // no need to keep iterating if a circle is pressed on
            }
        }

        if(currentCircle >= 0 && !circles[currentCircle].getGlobalBounds().contains(pos))  // find path if there is a valid start and end
        {
            sf::Vector2i circle = coordinatesToIndex(circles[currentCircle].getPosition());  // get starting point
            sf::Vector2i position = coordinatesToIndex(pos);  // get ending point
            path = findPaths(circle, position);  // get valid path
            currentPathIndex = 0;  // reset path index when a new path is found
        }
    }

    if (!path.empty() && currentPathIndex < path.size()) // move the circle along the path if there's a path to follow
    {
        inMotion = true;  // circle is now moving
        sf::Vector2f currentPos = circles[currentCircle].getPosition();  // current pos in path
        sf::Vector2i nextPos = path[currentPathIndex];  // next pos in path
        sf::Vector2i currentIndicies = coordinatesToIndex(currentPos);
        adj_matrix[currentIndicies.x][currentIndicies.y] = NO_COLOR;  // clear circle from previous position

        float targetX = grid[nextPos.x][nextPos.y].getPosition().x + grid[nextPos.x][nextPos.y].getSize().x / 2;  // middle of the cell x coord
        float targetY = grid[nextPos.x][nextPos.y].getPosition().y + grid[nextPos.x][nextPos.y].getSize().y / 2;  // middle of the cell y coord

        sf::Vector2f direction = sf::Vector2f(targetX, targetY) - currentPos;  // difference between current and target position
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);  // pythagorean theorem to find the distance

        float speed = 15.0f; // base speed

        if (distance < speed) 
            speed = distance;  // so we do not move past the target to avoid stalling

        if (distance > 1.0f)  // check if the circle is at the target
        {
            direction /= distance;  // ensure circle moves at an consistent speed
            circles[currentCircle].move(direction * speed);  // move circle by a small step
        } 
        else
            currentPathIndex++;  // move to the next pos once circle reaches the target 
    }
    if(currentPathIndex == path.size() && !path.empty())
    {
        inMotion = false;  // circle has stopped moving
        path.clear();  // no longer a path to follow
        adj_matrix[path[currentPathIndex - 1].x][path[currentPathIndex - 1].y] = get_color_number(circles[currentCircle].getFillColor());  // update position of the circle
        display_matrix();
        cout << endl;

        vector<sf::Vector2i> coords;

        if(fiveInARow(path[currentPathIndex - 1], coords))
            cout << "FIVE IN A ROWWWWW" << endl;
        // else
            init_circles();  // add 3 more circles to the grid
        
    }
}

void System::drawPath(sf::RenderWindow &window)
{
    for (int i = currentPathIndex; i < path.size(); i++)  // start drawing from the current path index
    {
        sf::Vector2i pos = path[i];  // Get the current path position
        sf::CircleShape pathCircle(5);  // smaller circle for the path
        pathCircle.setFillColor(circles[currentCircle].getFillColor());
        pathCircle.setOrigin(pathCircle.getRadius(), pathCircle.getRadius());

        float xPos = grid[pos.x][pos.y].getPosition().x;
        float yPos = grid[pos.x][pos.y].getPosition().y;
        pathCircle.setPosition(xPos + CELL_SIZE / 2 , yPos + CELL_SIZE / 2);
        window.draw(pathCircle);  // draw the path circle
    }
}

void System::Draw(sf::RenderWindow &window)
{
    window.clear();

    for (int i = 0; i < grid.size(); i++) 
    {
        for (int j = 0; j < grid[i].size(); j++) 
        {
            window.draw(grid[i][j]); 
        }
    }
    drawPath(window);
    for(int i = 0; i < circles.size(); i++)
    {
        window.draw(circles[i]);
    }
}

// bool System::fiveInARow(sf::Vector2i start)
// {
//     int newX = 0, newY = 0, counter = 0;
//     bool upOrDown = false, leftOrRight = false;

//     for (int i = 0; i < 4 && !upOrDown && !leftOrRight; i++)
//     {
//         newX = start.x + DIRECTIONS[i].x;
//         newY = start.y + DIRECTIONS[i].y;

//         if(newX >= 0 && newY >= 0 && newX < GRID_SIZE && newY < GRID_SIZE)
//         {
//             upOrDown = adj_matrix[newX][newY] == adj_matrix[start.x][start.y] && (i == 0 || i == 1);  // true if the same color is above or bellow the circle
//             leftOrRight = !upOrDown && adj_matrix[newX][newY] == adj_matrix[start.x][start.y];  // true if the same color is to the left or right of the circle
//         }
//     }

//     cout << "we are hereeeee" << endl;

//     if(!upOrDown && !leftOrRight)
//         return false;
    
//     sf::Vector2i current = sf::Vector2i(newX, newY);
//     counter ++;
    
//     if(upOrDown)
//     {
//         counter += moveDirection(start, 0);
//         counter += moveDirection(start, 1);
//     }
//     else if(leftOrRight)
//     {
//         counter += moveDirection(start, 2);
//         counter += moveDirection(start, 3);
//     }


//     return false;
// }