//Name: Passant Shaaban Abdelazim Mohammed
//Purpose : A2 T2
//ID: 20231036
//Section 25
/*Game of Life
cellular automaton proposed by John Horton Conway. The universe of this game is a grid of square
cells that could have one of two states: dead or alive. Every cell interacts with its adjacent neighbors,
with the following transactions occurring on every step:
 Any live cell with fewer than two live neighbors dies, as if caused by underpopulation
 Any live cell with two or three live neighbors lives on to the next generation
 Any live cell with more than three live neighbors dies, as if by overpopulation
 Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction */

#include <iostream>    
#include <iomanip>     
#include <sstream>     
#include <vector>      
#include <fstream>     
#include <cmath>       
#include <limits>      
#include <string>     
#include <thread> 

using namespace std;

class Universe{
    private:
    // Matrix to represent the current state of the universe
    vector<vector<int>> matrix;
    // Matrix to store the next generation temporarily
    vector<vector<int>> modified_matrix; 
    vector<int> live;
    vector<int> dead;
    int count1=0;

    // Helper function to clear the console
    void clear_screen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    public:
    // Constructor to initialize both matrices with zeros (20x20 grid)
    Universe() : matrix(20,vector<int>(20,0)) ,  modified_matrix(20, vector<int>(20, 0)) {};

    // Function to initialize live cells based on user input
    void initialize(){
        int row,col ;
       
        while(true){
            cout << "Enter the coordinates of live cells seperated by space,(row and column between 0 and 19)." << endl;
            cout << "Enter -1 -1 to stop inputting cells." << endl;
            cin >> row >>col ;

            // Stop input when -1 -1 is entered
            if(row==-1 && col==-1) break;

            // Validate input and set the corresponding cell to alive (1)
            if(row>=0 && row<20 && col>=0 && col<20){
                matrix[row][col]=1 ;
                
            }else{
                cout << "Invalid coordinates. Please try again." << endl;
            }
        }

        // Display the matrix after initialization
        cout << "Matrix after initialization: " << endl;
        for (const auto &row : matrix) {
            for (int cell : row) {
                cout << (cell ? "*" : "-") << " ";
            }
            cout << endl;
        }

    }
    
    // Function to reset the universe (make all cells dead)
    void reset(){
        for(int i=0 ; i<20 ; i++){
            for(int j=0 ; j<20 ; j++){
                matrix[i][j]=0;               // 0 refers to dead
            }
        }
    }

    // Function to count the live neighbors of a cell at (row, col)
    int count_neighbors(int row,int col){
        int count = 0 ;
        for(int i=-1 ; i<=1 ; i++){
            for(int j=-1 ; j<=1 ; j++){
                if(i==0 && j==0)continue; //skip the cell itself
                int nRow = row+i , nCol = col+j ; // Calculate neighbor's coordinates
                if(nRow>=0 && nRow<20 && nCol>=0 && nCol<20){
                    count+=matrix[nRow][nCol];
                } 
            }
        }
        return count;

    }

    // Function to compute the next generation of the universe
    void next_generation(){   
        for(int i=0 ; i<20 ; i++){
            for(int j=0 ; j<20 ; j++){
                int alive_neighbors = count_neighbors(i,j);
                if(matrix[i][j]==1){
                    if(alive_neighbors < 2 || alive_neighbors > 3){
                        modified_matrix[i][j] = 0 ; // Dies due to underpopulation or overpopulation

                    }else if(alive_neighbors==2 || alive_neighbors==3){
                        modified_matrix[i][j]=1 ;
                    }
                }else{
                    if(alive_neighbors == 3){
                        modified_matrix[i][j] = 1 ; // Becomes alive by reproduction
                    }
                }
            }
        }

        // Update the current matrix with the next generation
        matrix = modified_matrix;
    }

    // Display the current state of the universe
    void display() {
        // Clear the console for better visualization
        clear_screen();
        for (const auto &row : modified_matrix) {                              
            for (int cell : row) {
                cout << (cell ? "*" : "-") << " "; // Display "*" for live and "-" for dead cells
            }
            cout << endl;
        }
    }

    // Function to run the simulation for a certain number of generations
    void run(){
        int generations;
        cout <<"Enter number of generations: " <<endl;
        cin >> generations;
        for(int i = 0 ; i<generations ; i++){
            display();
            next_generation();
            // If you want to slow down the output
            this_thread::sleep_for(chrono::milliseconds(2000)); // Optional delay to slow down the output
        }
    }
};

int main(){
    Universe universe ;
    while(true){

    // Display the main menu    
    cout << "1. Start"                     <<endl
         << "2. Exit"                      <<endl
         << "3. Info about the game"       <<endl
         << "Enter your choice (1,2 or 3)" <<endl;

    int menuChoice ;
    cin >> menuChoice;

    // Check for invalid input
    if (cin.fail()) { 
        cin.clear();  
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        cout <<"Invalid input. please enter a valid number" <<endl;
        continue;
    }

    if(menuChoice == 1){
        //initialize the universe
        universe.initialize();
        //run the simulation
        universe.run();

    //Exit the program
    }else if(menuChoice == 2){
        cout<<"Good bye!";
        break;

    //Display informations about the game    
    }else if(menuChoice == 3){
        cout << "This is a game called (Life Game) " <<endl 
             <<"firstly, you should initialize cells that you want to be alive" <<endl
             <<"Then, it will show the next generations based on the number of runs you entered with the following rules: " <<endl
             <<"Any live cell with fewer than two live neighbors dies, as if caused by underpopulation" <<endl
             <<"Any live cell with two or three live neighbors lives on to the next generation" <<endl
             <<"Any live cell with more than three live neighbors dies, as if by overpopulation" <<endl
             <<"Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction" <<endl;

    }else{
        cout << "Invalid choice. try again" <<endl;
        continue;
    }
    }
    
    return 0;
}