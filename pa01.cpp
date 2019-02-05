



#include "matrix_search.h"

int main()
{

    char ** pointer = nullptr;
    int number_matrix;
    int row,col;
    string name;
    int * solution_array = new int [4];
    cin>>number_matrix;
    for(int i=0;i<number_matrix;i++)
    {

        cin>>row;
        cin>>col;

        pointer = build_matrix(row,col);
        fill_matrix(row,col,pointer);
        //print_matrix(row,col,pointer);
        cin>>name;
        matrix_search(solution_array,name,row,col,pointer);
        cout<<"Searching for \""<<name<<"\" in matrix "<<i<< " yields:"<<endl;
        if((solution_array[0] == -1) && (solution_array[1] ==-1) && (solution_array[2]==-1) && (solution_array[3]==-1))
        {
            cout<<"The pattern was not found."<<endl;

        }
        else
        {

            cout<<"Start pos:"<<"("<<solution_array[0]<<", "<<solution_array[1]<<")"<<" to End pos:"<<"("<<solution_array[2]<<", "<<solution_array[3]<<")"<<endl;

        }
        cout<<"\n";

        delete_matrix(row,pointer);

    }
    delete [] solution_array;


}
