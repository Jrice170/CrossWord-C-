/**
Here in the .cpp you should define and implement the functions that are declared in the .h file, and optionally any you declared, but not defined, above main.
**/

#include "matrix_search.h"




// We're giving you this one the first time, and you should copy it into all future assignments.
// Change the information to your own email handle (S&T username)
void get_identity(string &my_id)
{
    my_id = "jmr3by";
}


char ** build_matrix(int rows, int cols)
{
    char ** p1 = new  char * [rows];
    for(int i = 0;i<rows;i++)
    {

        p1[i] = new char[cols];


    }

    return p1;


}


void fill_matrix(int rows, int cols, char **matrix)
{

    char value;
    for(int i=0;i<rows;i++)
    {

      for(int j=0;j<cols;j++)
      {

          
          cin>>value;
          matrix[i][j] = value;


      }


    }

}


void print_matrix(int rows, int cols, char **matrix)
{

    for(int i = 0;i<rows;i++)
    {

      for(int j = 0;j<cols;j++)
      {

          cout<<matrix[i][j]<<" ";



      }
        cout<<'\n';

    }



}


void delete_matrix(int rows, char **matrix)
{

    for(int i = 0;i<rows;i++)
    {

        delete [] matrix[i];


    }

    delete [] matrix;

    matrix = nullptr;



}


void matrix_search(int sol[], string word, int rows, int cols, char **matrix)
{

    int length_word = word.length();
    int x_direction[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int y_direction[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    int Track;
    bool check_end=false;

    for (int n = 0;n< rows;n++)
    {
        for(int m= 0;m<cols;m++)
        {


          /// only place you can use matrix or else it will walk off array act very weard
          if(matrix[n][m] == word[0])
          {


              int store_end_row;
              int store_end_col;
              int row_movement,col_movement;
              for(int direct =0;direct<8;direct++)
              {
                  row_movement = n + x_direction[direct];
                  col_movement = m + y_direction[direct];

                  for(Track=1;Track<length_word;Track=Track+1)
                  {

                      if((row_movement < rows) && (row_movement >= 0)){store_end_row=row_movement;}
                      if((col_movement < cols) && (col_movement >= 0)){store_end_col=col_movement;}

                      if((row_movement >= rows) || (row_movement < 0) || (col_movement >= cols) || (col_movement < 0) ){break;}
                      if(matrix[row_movement][col_movement] != word[Track]){break;}

                      row_movement += x_direction[direct];
                      col_movement += y_direction[direct];





                  }
                  if(Track==length_word)
                  {
                    sol[0]= n;
                    sol[1]= m;
                    sol[2]= store_end_row;
                    sol[3]= store_end_col;
                    check_end = true;
                  }


              }



          }


        }


    if(!check_end)
    {

        sol[0]=sol[1]=sol[2]=sol[3] = -1;

    }


  }


}
