#ifndef Mine_Eluder_Methods_h
#define Mine_Eluder_Methods_h

// Header Files
#include <iostream> // To use standard input and output stream
#include <random>   // To use random generator functions
#include <cmath>    // To use ceil function
#include <vector>   // To use the vector container from the C++ STL
#include <string>   // To use the string object

using namespace std; // Using the standard namespace

// Macros for Difficulty Levels
#define NEWBIE 1
#define SPECIALIST 2
#define MASTER 3

// Class Definition
class cheat_codes {

// Private data member of string type to store the cheat code
private:
    string cheat = "reveal_mine";
    
// Public member function of boolean type to return whether the cheat code matched with the user code
public:
    bool cheat_validate(string cheat) {
        return this->cheat == cheat;
    }
};

// Global variables
int SIDE;   // side length of the board
int MINES;  // number of mines on the board

// Function Prototypes
int menu();
void choose_difficulty_level();
void rules();
void play_mine_eluder();
void cheat_code(vector<vector<int>> mines);
double probability_of_mines(int difficulty);
bool is_valid_move(int x , int y);
void initialise_random_generator();
void place_mines(vector<vector<int>> &mines);
bool check_mines(vector<vector<int>> mines , int x , int y);
void print_mines(vector<vector<int>> mines);
bool is_uncovered(int x , int y , vector<vector<int>> user_moves);
void print_board_status(vector<vector<int>> user_moves);
bool make_move(vector<vector<int>> &user_moves , int index , vector<vector<int>> mines);

// -----------------------------------------------------------------------------
// A Function to display the menu of the game
//      * Description : Displays the menu and gets the input from the user
//      * Return Type - Integer
//      * Parameters  - NULL
//      * Bugs        - NULL
// -----------------------------------------------------------------------------
int menu() {
    
    int choice;
    
    cout << "\t\t\t-----------------------------------------\n";
    cout << "\t\t\t*****************************************\n";
    cout << "\t\t\t***  M  I  N  E     E  L  U  D  E  R  ***\n";
    cout << "\t\t\t*****************************************\n";
    cout << "\t\t\t-----------------------------------------\n";
    
    cout << "\n\t\tEnter your choice\n\n";
    cout << "\t\t\t *** 1. P L A Y    G A M E  ***\n";
    cout << "\t\t\t *** 2. V I E W   R U L E S ***\n";
    cout << "\t\t\t *** 3. E X I T             ***\n";
    
    cout << "\n\n\t\tInput Here : ";
    cin >> choice;
    
    return choice;
}

// -----------------------------------------------------------------------------
// A Function to choose the difficulty level of the game
//      * Description : Calculates the SIDE and MINES based on the chosen
//                      difficulty
//      * Return Type - Void
//      * Parameters  - NULL
//      * Bugs        - NULL
// -----------------------------------------------------------------------------
void choose_difficulty_level() {
    
    // NEWBIE = 5 * 5 Cells and 5 Mines
    // SPECIALIST = 7 * 7 Cells and 15 Mines
    // MASTER = 9 * 9 Cells and 33 Mines
    
    int level;
    
    cout << "\n\n\t\t\t*************************\n";
    cout << "\t\t\t*** P L A Y   G A M E ***\n";
    cout << "\t\t\t*************************";

    cout << "\n\n\n Choose the Difficulty Level\n\n";
    cout << "\tPress 1 for NEWBIE     : (5 * 5 Cells and 5 Mines)\n";
    cout << "\tPress 2 for SPECIALIST : (7 * 7 Cells and 15 Mines)\n";
    cout << "\tPress 3 for MASTER     : (9 * 9 Cells and 33 Mines)\n\n";
    
    cout << " Input Here : ";
    cin >> level;

    double probability = probability_of_mines(level);
    
    if(level == NEWBIE) {
        SIDE = 5;
        cout << "\n\n\t\t\t***********************************\n";
        cout << "\t\t\t*** W E L C O M E   N E W B I E ***\n";
        cout << "\t\t\t***********************************\n\n";
    }
    else if(level == SPECIALIST) {
        SIDE = 7;
        cout << "\n\n\t\t\t*******************************************\n";
        cout << "\t\t\t*** W E L C O M E   S P E C I A L I S T ***\n";
        cout << "\t\t\t*******************************************\n\n";
    }
    else if(level == MASTER) {
        SIDE = 9;
        cout << "\n\n\t\t\t***********************************\n";
        cout << "\t\t\t*** W E L C O M E   M A S T E R ***\n";
        cout << "\t\t\t***********************************\n\n";
    }
    
    MINES = ceil(probability * (SIDE * SIDE));
}

// -----------------------------------------------------------------------------
// A Function to display rules
//      * Description : Displays the detailed rules, difference in each
//                      difficulty levels and symbols used in this game
//      * Return Type - Void
//      * Parameters  - NULL
//      * Bugs        - NULL
// -----------------------------------------------------------------------------
void rules() {
    
    cout << "\n\n\t\t\t*****************\n";
    cout << "\t\t\t*** R U L E S ***\n";
    cout << "\t\t\t*****************\n\n";
    cout << "\n 1. The rules of the game is to uncover all the cells that do not have mines in it. \n";
    cout << "\n 2. To uncover any cell you may enter the cell location. If the cell you entered has mine it\n";
    cout << "    in, then you lose the game, else the game continues. \n";
    cout << "\n 3. You can choose the difficulty of the game. There are three difficulty options available.\n";
    cout << "    They are \n";
    cout << "\n\t\t *** NEWBIE        - (5 * 5 grid with 5 Mines)  ***.\n";
    cout << "\n\t\t *** SPECIALIST    - (7 * 7 grid with 15 Mines) ***.\n";
    cout << "\n\t\t *** MASTER        - (9 * 9 grid with 33 Mines) ***.\n";
    cout << "\n 4. Symbols used and its meaning \n";
    cout << "\n\t\t It represents * -> Mine.\n";
    cout << "\n\t\t It represents - -> Closed Location.\n";
    cout << "\n\t\t It represents O -> Uncovered Location.\n";
    cout << "\n\n GOOD LUCK!!! \n";
}

// -----------------------------------------------------------------------------
// A Function to play Mine Eluder game
//      * Description : The main course of game functioning is performed here
//      * Return Type - Void
//      * Parameters  - NULL
//      * Bugs        - NULL
// -----------------------------------------------------------------------------
void play_mine_eluder() {
    
    // Initially the game is not over
    bool game_over = false;
    
    // Initially it is considered that the user did not win
    bool win = false;
    
    // Stores (x,y) coordinates of all mines.
    vector<vector<int>> mines(MINES , vector<int> (2));
    
    // Stores (x,y) coordinates of user's moves.
    vector<vector<int>> user_moves(SIDE * SIDE - MINES, vector<int> (2));
    
    // Initialises the random function generator
    initialise_random_generator();

    // Place the Mines randomly
    place_mines(mines);

    // You are in the game until you have not opened a mine
    // So keep playing

    int cells_left = SIDE * SIDE - MINES;
    
    cheat_code(mines);
    
    cout << "\n\t\t\t -----------------------------\n";
    cout << "\t\t\t *** G A M E   S T A R T S ***";
    cout << "\n\t\t\t -----------------------------\n";
    
    while(game_over == false) {
        
        cout << "\n\n Safe cells left to uncover : " << cells_left << "\n";
        
        cout << "\n Current Status of Board : \n\n";
        
        print_board_status(user_moves);
        
        game_over = make_move(user_moves , abs(20 - cells_left) , mines);
        
        cells_left--;

        if(game_over == false && cells_left == 0) {
            win = true;
            cout << "\n\t\t\t ---------------------\n";
            cout << "\t\t\t *** Y O U   W O N ***";
            cout << "\n\t\t\t ---------------------\n";
            game_over = true;
        }
        
        if(game_over == false && cells_left != 0) {
            cout << "\n Move successfully made and you uncovered a safe cell !\n";
        }
    }
    
    if(win == true) {
        cout << "\n\n Status of Board : \n\n";
    
        print_board_status(user_moves);
        
        cout << "\n\n Location of Mines : \n\n";
        
        print_mines(mines);
        
        cout << "\n\n You are a *** W I Z A R D *** !!! Well played ! \n\n";
    }
    
    else {
        cout << "\n\t\t\t -----------------------\n";
        cout << "\t\t\t *** Y O U   L O S T ***";
        cout << "\n\t\t\t -----------------------\n";
        
        cout << "\n\n Status of Board : \n\n";
        
        print_board_status(user_moves);
            
        cout << "\n\n Location of Mines : \n\n";
            
        print_mines(mines);
        
        cout << "\n\n A *** W I Z A R D *** has lost more times than the *** G U E S T *** has ever tried !\n";
        cout << " So keep playing ! \n\n";
    }
}

// -----------------------------------------------------------------------------
// A Function to use Cheat Code
//      * Description : If the user has a cheat code and wants to use it , then
//                      he/she may get an advantage if he/she enters the correct
//                      code within the given no. of attempts
//      * Return Type - Void
//      * Parameters  - Mines (2-D Vector of Integer)
//      * Bugs        - NULL
// -----------------------------------------------------------------------------
void cheat_code(vector<vector<int>> mines) {
    
    // To check whether the user wants to use the cheat code or not
    int use_cheat;
    cout << "\n Do you have a *** C H E A T   C O D E *** and want to use it? (1 / 0) : ";
    cin >> use_cheat;
    
    if(use_cheat == 1) {
        
        // To store the no. of unsuccessful attempts left
        int attempts_left = 3;
        
        cout << "\n\n You have chosen to use *** C H E A T   C O D E *** !\n";
        cout << " \n You have to enter the 11 - digit code correctly in atmost 3 Attempts.\n";
        cout << " Else the game will start automatically without any advantage !\n";
        
        // To store the cheat code that the user enters
        string user_code = "";
        
        // Creating the object "cheats" of the class "cheat_codes"
        cheat_codes cheats;
        
        // To check whether the user entered the correct cheat code or not
        bool success = false;
        
        while(attempts_left > 0) {
            
            cout << "\n\n Unsuccessful Attempts Left : " << attempts_left;
            
            cout << "\n Enter the *** C O D E *** : ";
            cin >> user_code;
            
            if(cheats.cheat_validate(user_code)) {
                success = true;
                cout << "\n The *** C O D E *** is CORRECT ! You gain the advantage !\n\n";
                cout << "\n\n Location of Mines : \n\n";
                
                // To print the location of mines if user entered correct code
                print_mines(mines);
                break;
            }
            else if(attempts_left > 1)
                cout << "\n The *** C O D E *** is WRONG ! Try Again !\n\n";
            
            attempts_left--;
        }
        if(success == false) {
            cout << "\n The *** C O D E *** is WRONG ! You start the game without any advantage !\n\n";
        }
    }
    else {
        cout << "\n\n WOW ! You have choose to play without *** C H E A T   C O D E *** !\n";
        cout << " You have a GOOD GAME SPIRIT ! Good Luck !\n";
    }
}

// -----------------------------------------------------------------------------
// A Function to calculate the probability of mines for a difficulty level
//      * Description : It calculates the probability of mines in the grid,
//                      based on the chosen difficulty level
//      * Return Type - Double
//      * Parameters  - Difficulty (Integer)
//      * Bugs        - NULL
// -----------------------------------------------------------------------------
double probability_of_mines(int difficulty) {
    
    double probability = 0.0;
    
    if(difficulty == NEWBIE)
        probability = 0.2;
    else if(difficulty == SPECIALIST)
        probability = 0.3;
    else if(difficulty == MASTER)
        probability = 0.4;
    return probability;
}

// -----------------------------------------------------------------------------
// A Function to check whether given cell (row, col) is valid or not
//      * Description : Checks whether the move made by the user while playing
//                      the game is valid or not
//      * Return Type - Boolean
//      * Parameters  - X , Y (Integer) - represents the cell chosen by the user
//      * Bugs        - NULL
// -----------------------------------------------------------------------------
bool is_valid_move(int x , int y) {
    
    // Returns true if row number and column number is in range
    return ((x >= 0) && (x < SIDE) && (y >= 0) && (y < SIDE));
}

// -----------------------------------------------------------------------------
// A Function to initialise the random function generator
//      * Description : It initialises the random function generator such that
//                      it always seeds different values at different time
//      * Return Type - Void
//      * Parameters  - NULL
//      * Bugs        - NULL
// -----------------------------------------------------------------------------
void initialise_random_generator() {
    
    // Initiate the random number generator so that the same configuration doesn't arises
    srand((int)time(NULL));
}

// -----------------------------------------------------------------------------
// A Function to place the mines randomly on the board
//      * Description : It randomly generates MINES no. of rows and columns
//                      in the range of the chosen grid and fills the Mines
//      * Return Type - Void
//      * Parameters  - Mines (2-D Vector of Integer) - Passed by reference
//      * Bugs        - NULL
// -----------------------------------------------------------------------------
void place_mines(vector<vector<int>> &mines) {
    
    vector<bool> mark(SIDE * SIDE , false);
    
    // Continue until all random mines have been created.
    for(int i = 0; i < MINES; ) {
        int random = rand() % (SIDE * SIDE);
        int x = random / SIDE;
        int y = random % SIDE;
        
        // Add the mine if no mine is placed at this position on the board
        if(mark[random] == false) {
            // Row Index of the Mine
            mines[i][0] = x + 1;
            // Column Index of the Mine
            mines[i][1] = y + 1;
            mark[random] = true;
            i++;
        }
    }
}

// -----------------------------------------------------------------------------
// A Function to check whether the user uncovered the mines location
//      * Description : It returns whether the location has a mine or not
//      * Return Type - Boolean
//      * Parameters  - Mines (2-D Vector of Integer) , X , Y (Integer)
//      * Bugs        - NULL
// -----------------------------------------------------------------------------
bool check_mines(vector<vector<int>> mines , int x , int y) {
    
    // If there is a mine in user's move, then the game is over
    for(int i = 0; i < MINES; i++) {
        if(mines[i][0] == x && mines[i][1] == y) {
            return true;
        }
    }
    
    return false;
}

// -----------------------------------------------------------------------------
// A Function to revealing where the mines are placed
//      * Description : It prints the board and reveals the location of mines
//      * Return Type - Void
//      * Parameters  - Mines (2-D Vector of Integer)
//      * Bugs        - NULL
// -----------------------------------------------------------------------------
void print_mines(vector<vector<int>> mines) {
    
    for(int i = 0; i < SIDE; i++) {
        cout << "\t";
        for(int j = 0; j < SIDE; j++) {
            if(check_mines(mines , i + 1 , j + 1))
                cout << "* ";
            else
                cout << "- ";
        }
        cout << "\n";
    }
}

// -----------------------------------------------------------------------------
// A Function to find whether a cell is uncovered or not
//      * Description : It returns whether the location has been already
//                      uncovered or not
//      * Return Type - Boolean
//      * Parameters  - X , Y (Integer) , User_Moves (2-D Vector of Integer)
//      * Bugs        - NULL
// -----------------------------------------------------------------------------
bool is_uncovered(int x , int y , vector<vector<int>> user_moves) {
    
    // If user made this move, then the cell is uncovered
    for(int i = 0; i < SIDE * SIDE - MINES; i++) {
        if(user_moves[i][0] == x && user_moves[i][1] == y) {
            return true;
        }
    }
    
    return false;
}

// -----------------------------------------------------------------------------
// A Function to print the current gameplay board
//      * Description : It prints the status of the board , without revealing
//                      the location of mines
//      * Return Type - Void
//      * Parameters  - User_Moves (2-D Vector of Integer)
//      * Bugs        - NULL
// -----------------------------------------------------------------------------
void print_board_status(vector<vector<int>> user_moves) {
    
    for(int i = 0; i < SIDE; i++) {
        cout << "\t";
        for(int j = 0; j < SIDE; j++) {
            if(is_uncovered(i + 1 , j + 1 , user_moves))
                cout << "O ";
            else
                cout << "- ";
        }
        cout << "\n";
    }
}

// -----------------------------------------------------------------------------
// A Function to get the user's move
//      * Description : It returns whether the game is over or not using the
//                      move made by the user
//      * Return Type - Boolean
//      * Parameters  - User_Moves (2-D Vector of Integer) , Index (Integer)
//                      Mines (2-D Vector of Integer)
//      * Bugs - NULL
// -----------------------------------------------------------------------------
bool make_move(vector<vector<int>> &user_moves , int index , vector<vector<int>> mines) {
    
    int x , y;
    bool move_made;
    do {
        // Take the input move
        cout << "\n Enter your move : (row , column) : ";
        cin >> x >> y;
        
        // Considering this move was not made before
        move_made = false;
        
        // If the move is invalid
        if(is_valid_move(x - 1 , y - 1) == false)
            cout << "\n Invalid Move , Input again !\n\n";
        else {
            // If already user made this move, then the game is over
            for(int i = 0; i < index; i++) {
                if(user_moves[i][0] == x && user_moves[i][1] == y) {
                    cout << "\n You already made this move , Input again !\n\n";
                    move_made = true;
                }
            }
        }
    
    } while(is_valid_move(x - 1 , y - 1) == false || move_made == true);
      
    // If user uncovered a mine
    if(check_mines(mines , x , y)) {
        // Printing the mine location if user uncovers it
        cout << "\n You uncovered a mine placed at location : " << x << " " << y << "\n\n";
        return true;
    }
    
    // To store the move made by the user
    user_moves[index][0] = x;
    user_moves[index][1] = y;
    
    return false;
}

#endif /* Mine_Eluder_Methods_h */
