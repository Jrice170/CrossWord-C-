#include "../solution/matrix_search.h"

int main()
{
    int cols = 20; 
    int rows = 20;  

    char **grid = new char*[rows];

    for(int i = 0; i < rows; i++) 
    {   
        grid[i] = new char[cols];
    }   

    delete_matrix(rows, grid);

    return 0;
}

