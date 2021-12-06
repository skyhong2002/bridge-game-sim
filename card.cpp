#include"card.h"
using namespace std;

card deck[52];
int card_index;
int number_of_player;
holder *player[10];
void card_init() {
    srand(time(0));
    card_index = 0;
    number_of_player = 0;
    bool fill[52] = {false};
    for(int i = 1; i <= 52; ++i) {
        while(1) {
            int index = rand() % 52;
            if(!fill[index]) {
                deck[index].suit = (i - 1) / 13;
                int num = (i - 1) % 13;
                if(num == 0) num = 13;
                deck[index].num = num;
                fill[index] = true;
                break;
            }
        }
    }
}
void deal(int quantity){
    int n = quantity;
    int suit = 0;
    player[number_of_player] = (holder*)calloc(1, sizeof(holder));
    for(int i = 0; i < 4; ++i) {
        player[number_of_player]->card_head[i] = (node*)calloc(1, sizeof(node));
        player[number_of_player]->card_head[i]->num = -1;
        player[number_of_player]->card_head[i]->rlink = NULL;
        player[number_of_player]->card_head[i]->llink = NULL;
        player[number_of_player]->card_rear[i] = NULL;
    }
    player[number_of_player]->num_of_card = 0;
    cout << "Player " << number_of_player + 1 << "'s deck:\n";
    while(n--) {
        if(card_index >= 52) {
            cout << "the deck is full" << "\n";
            break;
        }
        node *rlink_c = (node*)calloc(1, sizeof(node));
        suit = deck[card_index].suit;
        node *head = player[number_of_player]->card_head[suit];
        while(head->rlink != NULL) head = head->rlink;
        rlink_c->num = deck[card_index].num;
        rlink_c->rlink = NULL;
        rlink_c->llink = head;
        head->rlink = rlink_c;
        player[number_of_player]->card_rear[suit] = rlink_c;
        print_card(rlink_c, suit);
        cout << "\n";
        ++card_index;
        ++player[number_of_player]->num_of_card;
    }
    ++number_of_player;
}
int suit_to_num(char suit) {
    int num;
    if(suit == 'C' || suit == 'c') num = 0;
    else if(suit == 'D' || suit == 'd') num = 1;
    else if(suit == 'H' || suit == 'h') num = 2;
    else if(suit == 'S' || suit == 's') num = 3;
    return num;
}

int choose_player() {
    int choose;
    cout << "Choose a player (1 to ";
    cout << number_of_player;
    cout << "): ";
    cin >> choose;
    return --choose;
}
void print_card(node *card, int suit) {
    int num = card->num;
    if(suit == 0) cout << 'C';
    else if(suit == 1) cout << 'D';
    else if(suit == 2) cout << 'H';
    else if(suit == 3) cout << 'S';
    if(num == 13) cout << 'A';
    else cout << num + 1;
    cout << " ";
}
void print_in_order(int p, char s) {
    int player_index = p;
    int suit = suit_to_num(s);
    node *head = player[player_index]->card_head[suit]->rlink;
    if(head == NULL) cout << "No card in this suit." << "\n";
    else {
        while(head != NULL) {
            print_card(head, suit);
            cout << "\n";
            head = head->rlink;
        }
    }
}
void print_in_opposite_order(int p, char s) {
    int player_index = p;
    int suit = suit_to_num(s);
    node *rear = player[player_index]->card_rear[suit];
    if(rear == NULL) cout << "No card in this suit." << "\n";
    else {
        while(rear != NULL && rear->num != -1) {
            print_card(rear, suit);
            cout << "\n";
            rear = rear->llink;
        }
    }
}
void print_sorted(int p, char s) {
    int player_index = p;
    int suit = suit_to_num(s);
    bool c[14] = {false};
    node *head = player[player_index]->card_head[suit]->rlink;
    if(head == NULL) cout << "No card in this suit." << "\n";
    else {
        while(head != NULL) {
            c[head->num] = true;
            head = head->rlink;
        }
    }
    for(int i = 1; i <= 13; ++i) {
        if(c[i]) {
            cout << s;
            if(i == 13) cout << 'A' << "\n";
            else cout << i+1 << "\n";
        }
    }
}
void print_all_card(int player_index) {
    for(int suit = 0; suit < 4; ++suit) {
        node *head = player[player_index]->card_head[suit]->rlink;
        if(head == NULL) continue;
        else {
            while(head != NULL) {
                print_card(head, suit);
                head = head->rlink;
            }
        }
    }
}
int str_to_num(string n) {
    int num;
    if(n == "A" || n == "a") num = 13;
    else num = stoi(n) - 1;
    return num;
}
void input_card(int *suit, int *num) {
    string card;
    cout << "Insert a card (ex: H6): ";
    cin >> card;
    *suit = suit_to_num(card[0]);
    *num = str_to_num(card.substr(1)) - 1;
}
void add_card(int player_index) {
    if(card_index >= 52) {
        cout << "The deck is empty.\n";
        return;
    }
    node *rlink_c = (node*)calloc(1, sizeof(node));
    int suit = deck[card_index].suit;
    node *head = player[player_index]->card_head[suit];
    while(head->rlink != NULL) head = head->rlink;
    rlink_c->num = deck[card_index].num;
    rlink_c->rlink = NULL;
    rlink_c->llink = head;
    head->rlink = rlink_c;
    player[player_index]->card_rear[suit] = rlink_c;
    print_card(rlink_c, suit);
    cout << "\n";
    ++card_index;
    ++player[player_index]->num_of_card;
}
card delete_card(int player_index, int suit, int num) {
    node *head = player[player_index]->card_head[suit]->rlink;
    card ret;
    int upper_bound = 1e3;
    int smallest = 1e3;
    while(head) {
        if(num < head->num && head->num < upper_bound) upper_bound = head->num;
        if(smallest > head->num) smallest = head->num;
        head = head->rlink;
    }
    head = player[player_index]->card_head[suit]->rlink;
    if(upper_bound < 1e3 || smallest < 1e3) {
        int num_delete = 0;
        if(upper_bound < 1e3) num_delete = upper_bound;
        else {
            cout << "Delete the smallest card." << "\n";
            num_delete = smallest;
        }
        while(head) {
            if(head->num != num_delete) head = head->rlink;
            else {
                if(head == player[player_index]->card_rear[suit]) {
                    player[player_index]->card_rear[suit] = head->llink;
                    head->llink->rlink = NULL;
                }
                else if(head == player[player_index]->card_head[suit]) {
                    player[player_index]->card_head[suit] = head->rlink;
                    head->rlink->llink = NULL;
                }
                else {
                    node *tn = head->rlink;
                    node *tp = head->llink;
                    tp->rlink = tn;
                    tn->llink = tp;
                }
                --player[player_index]->num_of_card;
                cout << "deleted: ";
                print_card(head, suit);
                cout << "\n";
                ret.num = num_delete;
                ret.suit = suit;
                free(head);
                break;
            }
        }
    }
    else ret.suit = -1;
    cout << "Player " << player_index + 1 << " hand: " << player[player_index]->num_of_card << "\n";
    print_all_card(player_index);
    return ret;
}
void delete_one(int p) {
    int suit, num;
    int player_index = p;
    input_card(&suit, &num);
    if(player[player_index]->card_head[suit]->rlink == NULL) cout << "此花色中沒有牌" << "\n";
    else delete_card(player_index, suit, num);
}
void bridge(int i, int j) {
    bool first = true;
    int suit, num;
    while(1) {
        for(int player_index = min(i, j); player_index < max(i, j)+1; player_index += abs(j-i)) {
            if(first) {
                num = rand() % 13 + 1;
                suit = rand() % 4;
                int i = 0;
                for(i = 0; i < 4; ++i) {
                    if(player[player_index]->card_head[suit]->rlink != NULL) break;
                    suit++;
                    if(suit >= 4) suit = 0;
                }
                if(i == 4) {
                    cout << "Winner belongs to Player " << player_index + 1 << "!" << "\n";
                    goto end;
                }
                first = false;
            }
            if(player[player_index]->card_head[suit]->rlink == NULL) {
                cout << "No card in this suit. Draw 1: ";
                add_card(player_index);
                cout << "Player " << player_index + 1 << " hand: " << player[player_index]->num_of_card << "\n";
                print_all_card(player_index);
                cout << "\n\n";
                first = true;
            }
            else {
                card c = delete_card(player_index, suit, num);
                if(c.suit != -1) {
                    suit = c.suit;
                    num = c.num;
                }
            }
            if(player[player_index]->num_of_card == 0) {
                cout << "Winner belongs to Player " << player_index + 1 << "!" << "\n";
                goto end;
            }
        }
    }
end:
    return;
}