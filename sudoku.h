/*
 *  sudoku.h
 *  Sudoku
 *  Created by Prof. Ramavarapu Sreenivas
 *  Inspired by: http://web.eecs.utk.edu/courses/spring2012/cs140/Notes/Sudoku/index.html
*/

#ifndef sudoku
#define sudoku

#include <vector>
#include <fstream>
using std::vector;
using namespace std;
class Sudoku
{
    // Private
    int puzzle[9][9];
    
    // Private member function that checks if the named row is valid
    bool row_valid(int row, int k)
    {
        // write code that checks if "row" is valid
        for (int col=0; col<9; col++){
            if (puzzle[row][col] == k)
                return false;
        }
        return true;
    }
    
    // Private member function that checks if the named column is valid
    bool col_valid(int col, int k)
    {
        // check validity of "col"
        for(int row=0; row<9;row++){
            if(puzzle[row][col] == k)
                return false;
        }
        return true;
    }
    
    // Private member function that checks if the named 3x3 block is valid
    bool block_valid(int row, int col, int k)
    {
        // check 3 x 3 block validity
        int StartRow = row - row % 3;
        int StartCol = col - col % 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j< 3; j++)
                if (puzzle[StartRow+i][StartCol+j] == k)
                    return false;
        return true;
        
    }
    bool find_blank(int& row, int& col)
    {
        for ( row=0;row<9;row++)
            for(col=0;col<9;col++)
                if (puzzle[row][col] == 0)
                    return true;
        return false;
    }
    
public:
    // Public member function that reads the incomplete puzzle
    // we are not doing any checks on the input puzzle -- that is,
    // we are assuming they are indeed valid
    void read_puzzle(int argc, char * const argv[])
    {
        // write code that reads the input puzzle using the
        // guidelines of figure 23 of the bootcamp material

        // The input file name is "input1"
        // It contains the numbers P_1 P_2 ... P_M
        ifstream input_file(argv[1]);
        if (input_file.is_open()) {// If "input1" exists in the local directory
            // As long as your are not at the "end-of-file"
            for (int i=0;i<9;i++)
                for (int j=0;j<9;j++)
                    input_file>>puzzle[i][j];
            input_file.close();
            
        }
        else
            cout << "Input file does not exist in PWD" << endl;
    }
    
    // Public member function that prints the puzzle when called
    void print_puzzle()
    {
        std::cout << std::endl << "Board Position" << std::endl;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                // check if we have a legitimate integer between 1 and 9
                if ((puzzle[i][j] >= 1) && (puzzle[i][j] <= 9))
                {
                    // printing initial value of the puzzle with some formatting
                    std::cout << puzzle[i][j] << " ";
                }
                else {
                    // printing initial value of the puzzle with some formatting
                    std::cout << "X ";
                }
            }
            std::cout << std::endl;
        }
    }
    
    // Public member function that (recursively) implements the brute-force
    // search for possible solutions to the incomplete Sudoku puzzle
    bool Solve(int row, int col)
    {
        // this part of the code identifies the row and col number of the
        // first incomplete (i.e. 0) entry in the puzzle.  If the puzzle has
        // no zeros, the variable row will be 9 => the puzzle is done, as
        // each entry is row-, col- and block-valid...
        
        // use the pseudo code of figure 3 of the description
        if (find_blank(row,col)) {
            for (int k=1;k<=9; k++){
                if(row_valid(row, k)&&col_valid(col, k)&&block_valid(row, col, k)){
                    puzzle[row][col]=k;
                    if (Solve(row,col)){
                        return true;}
                    else {
                        puzzle[row][col]=0;
                    }
                    
                }
            } return false;
            
        }
        else
            return true;
    }
};

#endif

