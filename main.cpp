#include"card.h"
using namespace std;

int main(){
    cout << "=============================\n"
            "Bridge Game Simulator Ver 1.0\n"
            "     Created by Sky Hong\n"
            "     NTNU CSIE 41047033S\n"
            "=============================\n"
            "Type 'help' to see the guide.\n";
    string order;
    card_init();

    int quantity;
    int p;
    string s;
    while(cout << "\n> "){
        cin >> order;
        switch (order[0]){
        case '1':
            cout << "How many card to deal? ";
            cin >> quantity;
            deal(quantity);
            break;
        case '2':
            p = choose_player();
            cout << "Insert suit (C,D,H,S): ";
            cin >> s;
            print_in_order(p, s[0]);
            break;
        case '3':
            p = choose_player();
            cout << "Insert suit (C,D,H,S): ";
            cin >> s;
            print_in_opposite_order(p, s[0]);
            break;
        case '4':
            p = choose_player();
            cout << "Insert suit (C,D,H,S): ";
            cin >> s;
            print_sorted(p, s[0]);
            break;
        case '5':
            p = choose_player();
            delete_one(p);
            break;
        case '9':
            int playera, playerb;
            cout << "Insert the first player: ";
            cin >> playera;
            cout << "Insert the second player: ";
            cin >> playerb;
            bridge(--playera, --playerb);
            break;
        case '0':
            cout << "BYE\n";
            break;
        case 'h':    
            cout << "1 to deal a n-card deck to a new player.\n"
                    "2 to print one suit from the deck in order.\n"
                    "3 to print one suit from the deck in opposite order.\n"
                    "4 to print one suit from the deck in size order.\n"
                    "5 to delete a card from the deck.\n"
                    "9 to play bridge!\n"
                    "0 to exit.";
            break;
        default:
            cout << "wut?\n";
            break;
        }
        if(order[0] == '0'){
            break;
        }
    }
}