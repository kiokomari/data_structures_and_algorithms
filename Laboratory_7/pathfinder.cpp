#include <iostream>
#include <stack>
#include <set>
#include <string>
#include <math.h>
#include<fstream>
#include <chrono>

using namespace std;

int ROW;
int COL;
string patch = "";
typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> pPair;
struct cell
{
    int parent_i, parent_j;
    double f, g, h;
};

bool isValid(int row, int col)
{ 
    return (row >= 0) && (row < ROW) &&
        (col >= 0) && (col < COL);
}

bool isUnBlocked(int **grid, int row, int col)
{
    if (grid[row][col] == 1)
        return (true);
    else
        return (false);
}

bool isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}

inline double calculateHValue(int row, int col, Pair dest)
{
    return ((double)sqrt((row - dest.first) * (row - dest.first)
        + (col - dest.second) * (col - dest.second)));
}

void tracePath(cell **cellDetails, Pair dest)
{
    printf("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;

    stack<Pair> Path;
    while (!(cellDetails[row][col].parent_i == row
        && cellDetails[row][col].parent_j == col))
    {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    Path.push(make_pair(row, col));
    while (!Path.empty())
    {
        pair<int, int> p = Path.top();
        Path.pop();
        printf("-> (%d,%d) ", p.first, p.second);
        patch += "(" + to_string(p.first) + ";" + to_string(p.second) + ")";
    }
    return;
}
bool testDots(int **grid, Pair src, Pair dest)
{
    if (isValid(src.first, src.second) == false)
    {
        printf("Source is invalid\n");
        return false;
    }
    if (isValid(dest.first, dest.second) == false)
    {
        printf("Destination is invalid\n");
        return false;
    }
    if (isDestination(src.first, src.second, dest) == true)
    {
        printf("We are already at the destination\n");
        return false;
    }
    return true;
}
void aStarSearch(int **grid, Pair src, Pair dest)
{
    bool** closedList = new bool* [ROW];
    for (int count = 0; count < ROW; count++)
        closedList[count] = new bool[COL];
    //bool closedList[ROW][COL];
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            closedList[i][j] = false;
    //memset(closedList, false, sizeof(closedList));
    cell** cellDetails = new cell* [ROW];
    for (int count = 0; count < ROW; count++)
        cellDetails[count] = new cell[COL];
    //cell cellDetails[ROW][COL];

    int i, j;

    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;


    set<pPair> openList;

    openList.insert(make_pair(0.0, make_pair(i, j)));

    bool foundDest = false;

    while (!openList.empty())
    {
        pPair p = *openList.begin();

        openList.erase(openList.begin());

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        double gNew, hNew, fNew;

        if (isValid(i - 1, j) == true)
        {

            if (isDestination(i - 1, j, dest) == true)
            {
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i - 1][j] == false &&
                isUnBlocked(grid, i - 1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i - 1][j].f == FLT_MAX ||
                    cellDetails[i - 1][j].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                        make_pair(i - 1, j)));

                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        if (isValid(i + 1, j) == true)
        {

            if (isDestination(i + 1, j, dest) == true)
            {
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            else if (closedList[i + 1][j] == false &&
                isUnBlocked(grid, i + 1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j, dest);
                fNew = gNew + hNew;

 
                if (cellDetails[i + 1][j].f == FLT_MAX ||
                    cellDetails[i + 1][j].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i + 1, j)));
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }
        if (isValid(i, j + 1) == true)
        {
            if (isDestination(i, j + 1, dest) == true)
            {
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i][j + 1] == false &&
                isUnBlocked(grid, i, j + 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j + 1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j + 1].f == FLT_MAX ||
                    cellDetails[i][j + 1].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                        make_pair(i, j + 1)));
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }
        if (isValid(i, j - 1) == true)
        {

            if (isDestination(i, j - 1, dest) == true)
            {

                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }


            else if (closedList[i][j - 1] == false &&
                isUnBlocked(grid, i, j - 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j - 1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j - 1].f == FLT_MAX ||
                    cellDetails[i][j - 1].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                        make_pair(i, j - 1)));

                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }

        if (isValid(i - 1, j + 1) == true)
        {
            if (isDestination(i - 1, j + 1, dest) == true)
            {
                cellDetails[i - 1][j + 1].parent_i = i;
                cellDetails[i - 1][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i - 1][j + 1] == false &&
                isUnBlocked(grid, i - 1, j + 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j + 1, dest);
                fNew = gNew + hNew;
                if (cellDetails[i - 1][j + 1].f == FLT_MAX ||
                    cellDetails[i - 1][j + 1].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                        make_pair(i - 1, j + 1)));
                    cellDetails[i - 1][j + 1].f = fNew;
                    cellDetails[i - 1][j + 1].g = gNew;
                    cellDetails[i - 1][j + 1].h = hNew;
                    cellDetails[i - 1][j + 1].parent_i = i;
                    cellDetails[i - 1][j + 1].parent_j = j;
                }
            }
        }
        if (isValid(i - 1, j - 1) == true)
        {
            if (isDestination(i - 1, j - 1, dest) == true)
            {
                cellDetails[i - 1][j - 1].parent_i = i;
                cellDetails[i - 1][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i - 1][j - 1] == false &&
                isUnBlocked(grid, i - 1, j - 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j - 1, dest);
                fNew = gNew + hNew;
                if (cellDetails[i - 1][j - 1].f == FLT_MAX ||
                    cellDetails[i - 1][j - 1].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i - 1, j - 1)));

                    cellDetails[i - 1][j - 1].f = fNew;
                    cellDetails[i - 1][j - 1].g = gNew;
                    cellDetails[i - 1][j - 1].h = hNew;
                    cellDetails[i - 1][j - 1].parent_i = i;
                    cellDetails[i - 1][j - 1].parent_j = j;
                }
            }
        }

        if (isValid(i + 1, j + 1) == true)
        {

            if (isDestination(i + 1, j + 1, dest) == true)
            {
                cellDetails[i + 1][j + 1].parent_i = i;
                cellDetails[i + 1][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            else if (closedList[i + 1][j + 1] == false &&
                isUnBlocked(grid, i + 1, j + 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j + 1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i + 1][j + 1].f == FLT_MAX ||
                    cellDetails[i + 1][j + 1].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                        make_pair(i + 1, j + 1)));

                    cellDetails[i + 1][j + 1].f = fNew;
                    cellDetails[i + 1][j + 1].g = gNew;
                    cellDetails[i + 1][j + 1].h = hNew;
                    cellDetails[i + 1][j + 1].parent_i = i;
                    cellDetails[i + 1][j + 1].parent_j = j;
                }
            }
        }

        if (isValid(i + 1, j - 1) == true)
        {
            if (isDestination(i + 1, j - 1, dest) == true)
            { 
                cellDetails[i + 1][j - 1].parent_i = i;
                cellDetails[i + 1][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }


            else if (closedList[i + 1][j - 1] == false &&
                isUnBlocked(grid, i + 1, j - 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j - 1, dest);
                fNew = gNew + hNew;
 
                if (cellDetails[i + 1][j - 1].f == FLT_MAX ||
                    cellDetails[i + 1][j - 1].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                        make_pair(i + 1, j - 1)));

 
                    cellDetails[i + 1][j - 1].f = fNew;
                    cellDetails[i + 1][j - 1].g = gNew;
                    cellDetails[i + 1][j - 1].h = hNew;
                    cellDetails[i + 1][j - 1].parent_i = i;
                    cellDetails[i + 1][j - 1].parent_j = j;
                }
            }
        }
    }
    if (foundDest == false)
        printf("Failed to find the Destination Cell\n");

    return;
}
void printResults(int **grid,Pair src,Pair dest)
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
            if (i == src.first && j == src.second)
                std::cout << "s ";
            else if (i == dest.first && j == dest.second)
                std::cout << "f ";
            else if (patch.find("(" + to_string(i) + ";" + to_string(j) + ")") != -1)
                std::cout << "@ ";
            else
                std::cout << grid[i][j] << " ";
        std::cout << endl;
    }
}
double getDistance(Pair currentPos, Pair dest)
{
    return sqrt(pow(dest.first-currentPos.first,2)+ pow(dest.second - currentPos.second, 2));
}
Pair findPatch(int **array,Pair currentPos,Pair dest)
{
    Pair newPos = make_pair(-1,-1);
    double dist = DBL_MAX;
    int i = currentPos.first;
    int j = currentPos.second;
    if (j+1<COL)
        if (array[i][j + 1] == 1 || make_pair(i, j + 1) == dest)
            if (getDistance(make_pair(i, j + 1), dest) < dist || make_pair(i, j + 1)==dest)
            {
                newPos = make_pair(i, j + 1);
                dist = getDistance(newPos, dest);
                if (newPos == dest)
                    goto leavFind;
            }
    if(i+1<ROW&&j+1<COL)
    if (array[i + 1][j + 1] == 1 || make_pair(i + 1, j + 1) == dest)
        if (getDistance(make_pair(i + 1, j + 1), dest) < dist || make_pair(i + 1, j + 1) == dest)
        {
            newPos = make_pair(i + 1, j + 1);
            dist = getDistance(newPos, dest);
            if (newPos == dest)
                goto leavFind;
        }
    if (i + 1 < ROW)
    if (array[i + 1][j]==1 || make_pair(i + 1, j) == dest)
        if (getDistance(make_pair(i + 1, j), dest) < dist|| make_pair(i + 1, j) == dest)
        {
            newPos = make_pair(i + 1, j);
            dist = getDistance(newPos, dest);
            if (newPos == dest)
                goto leavFind;
        }
    if (i + 1 < ROW && j - 1 > -1)
    if (array[i + 1][j - 1]==1 || make_pair(i + 1, j - 1) == dest)
        if (getDistance(make_pair(i + 1, j-1), dest) < dist|| make_pair(i + 1, j - 1)== dest)
        {
            newPos = make_pair(i + 1, j - 1);
            dist = getDistance(newPos, dest);
            if (newPos == dest)
                goto leavFind;
        }
    if (j - 1 >-1)
    if (array[i][j - 1]==1 || make_pair(i, j - 1) == dest)
        if (getDistance(make_pair(i, j - 1), dest) < dist|| make_pair(i, j - 1)==dest)
        {
            newPos = make_pair(i, j - 1);
            dist = getDistance(newPos, dest);
            if (newPos == dest)
                goto leavFind;
        }
    if (i - 1 > -1 && j - 1 >-1)
    if (array[i - 1][j - 1]==1 || make_pair(i - 1, j - 1) == dest)
        if (getDistance(make_pair(i - 1, j - 1), dest) < dist|| make_pair(i - 1, j - 1)==dest)
        {
            newPos = make_pair(i - 1, j - 1);
            dist = getDistance(newPos, dest);
            if (newPos == dest)
                goto leavFind;
        }
    if (i - 1 >-1)
    if (array[i - 1][j]==1 || make_pair(i - 1, j) == dest)
        if (getDistance(make_pair(i - 1, j), dest) < dist || make_pair(i - 1, j)==dest)
        {
            newPos = make_pair(i - 1, j);
            dist = getDistance(newPos, dest);
            if (newPos == dest)
                goto leavFind;
        }
    if (i - 1 > -1 && j + 1 < COL)
    if (array[i - 1][j + 1]==1 || make_pair(i - 1, j + 1) == dest)
        if (getDistance(make_pair(i - 1, j+1), dest) < dist || make_pair(i - 1, j + 1)==dest)
        {
            newPos = make_pair(i - 1, j + 1);
            dist = getDistance(newPos, dest);
            if (newPos == dest)
                goto leavFind;
        }
leavFind:
    return newPos;
}
void alg(int **grid, Pair src, Pair dest)
{
    patch = "The Patch is ->";
    int** array = new int* [ROW];
    for (int count = 0; count < ROW; count++)
        array[count] = new int[COL];
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            array[i][j] = grid[i][j];
    bool isPatch = true;
    bool isFound = false;
    Pair currentPos = src;
    while (isPatch && !isFound)
    {
        if (currentPos == dest)
        {
            isFound = true;
            patch += "(" + to_string(currentPos.first) + ";" + to_string(currentPos.second) + ")";
        }
        else
        {
            patch += "(" + to_string(currentPos.first) + ";" + to_string(currentPos.second) + ") -> ";
            currentPos = findPatch(array, currentPos,dest);
            if (currentPos.first == -1)
                isPatch = false;
            else
                array[currentPos.first][currentPos.second] = 0;
        }
    }
if (!isPatch)
        patch = "The Patch is -> no Patch";
}
int main()
{
    ifstream file("D:\\test.txt");
    string s;
    string delimiter = " ";
    int i = 0;
    int j = 0;
    while (getline(file, s))
    {
        string token;
        size_t pos = 0;
        j = 0;
        while ((pos = s.find(delimiter)) != std::string::npos) {

            token = s.substr(0, pos);
            s.erase(0, pos + delimiter.length());
            j++;
        }
        i++;
    }
    file.close();
    ROW = i;
    COL = j;
    int** grid = new int* [ROW];
    for (int count = 0; count < ROW; count++)
        grid[count] = new int[COL];
   
    /* Description of the Grid-
     1--> The cell is not blocked
     0--> The cell is blocked    */
    i = 0;
    j = 0;
    ifstream file1("D:\\test.txt");
    while (getline(file1, s))
    {
        string token;
        size_t pos = 0;
        j = 0;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            
            token = s.substr(0, pos);
            if (token == "0")
                grid[i][j] = 0;
            else
                grid[i][j] = 1;
            s.erase(0, pos + delimiter.length());
            j++;
        }
        i++;
    }
    file1.close();
    int x, y;
    printf("Enter start dot\n");
    std::cin >> x >> y;
    Pair src = make_pair(y, x);
    printf("Enter finish dot\n");
    std::cin >> x >> y;
    Pair dest = make_pair(y, x);
   if (testDots(grid, src, dest))
    {
       std::cout << "################ A-Star ################" << endl;
       auto begin = chrono::high_resolution_clock::now();
       aStarSearch(grid, src, dest);
       auto end = chrono::high_resolution_clock::now();
       std::cout <<endl <<"Working time = " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " nanoseconds" << endl;
       printResults(grid, src, dest);
       std::cout << endl;
       std::cout << "######## Orthogonal-diagonal-ray########" << endl;
       begin = chrono::high_resolution_clock::now();
       alg(grid, src, dest);
       end = chrono::high_resolution_clock::now();
       std::cout << patch << endl;
       printResults(grid, src, dest);
       std::cout << endl << "Working time = " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " nanoseconds" << endl;
    }
    return(0);
}