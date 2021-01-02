// A C++ Program to Implement Mine Eluder

#include "Mine Eluder Methods.h"

// Driver Program
int main() {
    
    int repeat;
    do {
        // To get the choice from the user
        int choice = menu();
        
        if(choice == 1) {
            // To choose difficulty level and start playing
            choose_difficulty_level();
            play_mine_eluder();
        }
        else if(choice == 2) {
            // To display rules of the game
            rules();
        }
        else {
            cout << "\n\t\t\t -------------------------------------------\n";
            cout << "\t\t\t *** T H A N K S   F O R   P L A Y I N G ***";
            cout << "\n\t\t\t -------------------------------------------\n\n";
            // To exit from the program
            exit(0);
        }
        cout << "\nDo you want to continue to menu? (1 / 0) : ";
        cin >> repeat;
        cout << "\n";
    } while(repeat);
    
    cout << "\t\t\t -------------------------------------------\n";
    cout << "\t\t\t *** T H A N K S   F O R   P L A Y I N G ***";
    cout << "\n\t\t\t -------------------------------------------\n\n";
    return 0;
}
