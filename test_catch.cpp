/* jmsxw4@mst.edu wrote tests, taylor@mst.edu converted to catch.hpp format.
 */

#include "catch.hpp"
#include <stdexcept>
#include "../solution/matrix_search.h"

TEST_CASE("Basic searches") 
{
    int cols = 20;
    int rows = 20;  

    char **grid = new char*[rows];
    
    for(int i = 0; i < rows; i++) 
    {
        grid[i] = new char[cols];
    }

    int sol[4]{999, 999, 999, 999};

    SECTION("Word search handles numbers")
    {
        for(int i = 0; i < rows; i++) 
        {
            for(int j = 0; j < cols; j++) 
            {
                grid[i][j] = '9';
            }
        }
        
        grid[0][0] = '1';
        grid[0][1] = '2';
        grid[0][2] = '3';
        string word = "123";
        
        matrix_search(sol, word, cols, rows, grid);

        CHECK(sol[0] == 0); 
        CHECK(sol[1] == 0);
        CHECK(sol[2] == 0);
        CHECK(sol[3] == 2);
    }
    
    for(int i = 0; i < rows; i++) 
    {
        for(int j = 0; j < cols; j++) 
        {
            grid[i][j] = 'j';	
        }
    }
        
    SECTION("Finds diagonal up left")
    {
        int row_dif = 1;
        int col_dif = 1;
        int row_loc = 0;
        int col_loc = 0;
        string word = "studer";

        for(int i = 0; i < word.length(); i++) 
        {
            grid[row_loc][col_loc] = word[i];
            row_loc += row_dif;
            col_loc += col_dif;		
        }

        matrix_search(sol, word, cols, rows, grid);
        
        CHECK(sol[0] == 0);
        CHECK(sol[1] == 0);
        CHECK(sol[2] == row_loc - row_dif);
        CHECK(sol[3] == col_loc - col_dif);
    }

    SECTION("Finds words oriented up")
    {
        int row_dif = 1;
        int col_dif = 0;
        int row_loc = 0;
        int col_loc = 10;
        string word = "studer";
       
        for(int i = 0; i < word.length(); i++) 
        {
            grid[row_loc][col_loc] = word[i];
            row_loc += row_dif;
            col_loc += col_dif;		
        }
        
        matrix_search(sol, word, cols, rows, grid);
        
        CHECK(sol[0] == 0); 
        CHECK(sol[1] == 10);
        CHECK(sol[2] == row_loc - row_dif);
        CHECK(sol[3] == col_loc - col_dif);
    }

    SECTION("Finds diagonal up right")
    {
        int row_dif = 1;
        int col_dif = -1;
        int row_loc = 0;
        int col_loc = 19;
        string word = "studer";
        
        for(int i = 0; i < word.length(); i++) 
        {
            grid[row_loc][col_loc] = word[i];
            row_loc += row_dif;
            col_loc += col_dif;		
        }
        
        matrix_search(sol, word, cols, rows, grid);
 
        CHECK(sol[0] == 0); 
        CHECK(sol[1] == 19);
        CHECK(sol[2] == row_loc - row_dif);
        CHECK(sol[3] == col_loc - col_dif);
    }

    SECTION("Finds words oriented forwards")
    {
        int row_dif = 0;
        int col_dif = 1;
        int row_loc = 0;
        int col_loc = 0;
        string word = "studer";
        
        for(int i = 0; i < word.length(); i++) 
        {
            grid[row_loc][col_loc] = word[i];
            row_loc += row_dif;
            col_loc += col_dif;		
        }

        matrix_search(sol, word, cols, rows, grid);
 
        CHECK(sol[0] == 0); 
        CHECK(sol[1] == 0);
        CHECK(sol[2] == row_loc - row_dif);
        CHECK(sol[3] == col_loc - col_dif);
    }

    SECTION("Finds words oriented diagonal down right")
    {
        int row_dif = -1;
        int col_dif = -1;
        int row_loc = 19;
        int col_loc = 19;
        string word = "reduts";
        
        for(int i = 0; i < word.length(); i++) 
        {
            grid[row_loc][col_loc] = word[i];
            row_loc += row_dif;
            col_loc += col_dif;
        }
        
        matrix_search(sol, "studer", cols, rows, grid);

        CHECK(sol[0] == row_loc - row_dif);
        CHECK(sol[1] == col_loc - col_dif);
        CHECK(sol[2] == 19); 
        CHECK(sol[3] == 19);
    }

    SECTION("Finds words oriented down")
    {
        int row_dif = -1; 
        int col_dif = 0;
        int row_loc = 19; 
        int col_loc = 10; 
        string word = "reduts";

        for(int i = 0; i < word.length(); i++) 
        {
            grid[row_loc][col_loc] = word[i];
            row_loc += row_dif;
            col_loc += col_dif;         
        }   

        matrix_search(sol, "studer", cols, rows, grid);

        CHECK(sol[0] == row_loc - row_dif);
        CHECK(sol[1] == col_loc - col_dif);
        CHECK(sol[2] == 19); 
        CHECK(sol[3] == 10);
    }

    SECTION("Finds words oriented diagonal down left")
    {
        int row_dif = -1;
        int col_dif = 1;
        int row_loc = 19;
        int col_loc = 0;
        string word = "reduts";

        for(int i = 0; i < word.length(); i++)
        {
            grid[row_loc][col_loc] = word[i];
            row_loc += row_dif;
            col_loc += col_dif;
        }

        matrix_search(sol, "studer", cols, rows, grid);

        CHECK(sol[0] == row_loc - row_dif);
        CHECK(sol[1] == col_loc - col_dif);
        CHECK(sol[2] == 19); 
        CHECK(sol[3] == 0);
    }

    SECTION("Finds words oriented backwards")
    {
        int row_dif = 0;
        int col_dif = -1;
        int row_loc = 0;
        int col_loc = 5;
        string word = "studer";
        
        for(int i = 0; i < word.length(); i++) 
        {
            grid[row_loc][col_loc] = word[i];
            row_loc += row_dif;
            col_loc += col_dif;		
        }

        matrix_search(sol, word, cols, rows, grid);
 
        CHECK(sol[0] == 0); 
        CHECK(sol[1] == 5);
        CHECK(sol[2] == row_loc - row_dif);
        CHECK(sol[3] == col_loc - col_dif);
    }

    SECTION("Word does not exist")
    {
        string word = "bathtub";
        matrix_search(sol, word, cols, rows, grid);
 
        CHECK(sol[0] == -1); 
        CHECK(sol[1] == -1);
        CHECK(sol[2] == -1);
        CHECK(sol[3] == -1);
    }

    SECTION("False positive")
    {
        grid[3][3] = 's';
        grid[3][4] = 't';
        grid[3][8] = 'r';
        string word = "studer";
        matrix_search(sol, word, cols, rows, grid);
        
        CHECK(sol[0] == -1); 
        CHECK(sol[1] == -1);
        CHECK(sol[2] == -1);
        CHECK(sol[3] == -1);
    }

    for(int i = 0; i < rows; i++)
    {
        delete[] grid[i];
    }
    delete[] grid;

    SECTION("Big matrix")
    {
        int cols = 250;
        int rows = 250;
        char **big_grid = new char*[rows];
        
        for(int i = 0; i < rows; i++)
        {
            big_grid[i] = new char[cols];
        }
        
        string word = "bathtub";
        
        for(int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                big_grid[i][j] = 'a';
            }
        }
        
        big_grid[0][0] = 'b';
        big_grid[0][1] = 'a';
        big_grid[0][2] = 't';
        big_grid[0][3] = 'h';
        big_grid[0][4] = 't';
        big_grid[0][5] = 'u';
        big_grid[0][6] = 'b';
        matrix_search(sol, word, cols, rows, big_grid);
        
        CHECK(sol[0] == 0); 
        CHECK(sol[1] == 0);
        CHECK(sol[2] == 0);
        CHECK(sol[3] == 6);
        
        for(int i = 0; i < rows; i++)
        {
            delete[] big_grid[i];
        }
        delete[] big_grid;
    }

    SECTION("Build matrix")
    {
        int cols = 900;
        int rows = 900;
        char** build_grid = build_matrix(cols, rows);
        
        // Doubled for even weighting
        CHECK_NOTHROW(build_grid[898][898] = 'c');
        CHECK_NOTHROW(build_grid[898][898] = 'c');
        CHECK_NOTHROW(build_grid[898][898] = 'c');
        CHECK_NOTHROW(build_grid[898][898] = 'c');
        
        for(int i = 0; i < cols; i++) 
        {
            delete[] build_grid[i];
        }
        delete[] build_grid;
    }

    SECTION("Fill matrix")
    {
        char **fill_grid;
        int cols = 11;
        int rows = 9;
        fill_grid = new char*[rows];
        
        for(int i = 0; i < rows; i++)
        {
            fill_grid[i] = new char[cols];
        }
        
        fill_matrix(rows, cols, fill_grid);
        
        // Doubled for even weighting 
        CHECK(fill_grid[0][3] == 'r');
        CHECK(fill_grid[8][6] == 'c');
        CHECK(fill_grid[0][3] == 'r');
        CHECK(fill_grid[8][6] == 'c');
    }
}

