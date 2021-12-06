#ifndef card__
#define card__
#include<iostream>
#include<ctime>
#include<string>

struct card{
    int suit;
    int num;
};
struct node{
    int num;
    node *rlink;
    node *llink;
};
struct holder{
    int num_of_card;
    node *card_head[4];
    node *card_rear[4];
};

void card_init();
void deal(int quantity);
int suit_to_num(char suit);
int choose_player();
void print_card(node *card, int suit);
void print_in_order(int p, char s);
void print_in_opposite_order(int p, char s);
void print_sorted(int p, char s);
void print_all_card(int player_index);
int str_to_num(std::string n);
void input_card(int *suit, int *num);
card delete_card(int player_index,int suit,int num);
void delete_one(int p);
void bridge(int p1, int p2);

#endif