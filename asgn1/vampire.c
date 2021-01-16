#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "names.h"

#define MAX_PLAYERS 10

int lower(int x, int y){
    return x < y ? x : y;
    }
/*--------------------------*/
int Roll(int side){         /* the outcomes are from 0 to 5*/
    return ( random() % side);
    }
/*--------------------------*/
uint32_t left(uint32_t pos, uint32_t players){
    return (pos + players - 1) % players;
    }

uint32_t right(uint32_t pos, uint32_t players){
    return (pos + 1) % players;
    }
/*--------------------------*/
int game( int Players ){        /* Players = players; random = r */
    int first, second, sum, Left, Right;
    int round = 1;
    int lives[MAX_PLAYERS] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
    int outcome[MAX_PLAYERS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int end = 0;            /* 1 : end the game */
    
    while(end == 0){        /* round, game starts */
        printf("Round %d\n", round);
        int name_index = 0;
        int lowest = 100;
        
        while(name_index <  Players){  /* every vampire rolls dice exept those have 0 lives */
            if (lives[name_index] != 0){
                first = Roll(6);
                second = Roll(6);
                sum = first + second;
                outcome[name_index] = sum;
                printf(" - %s rolls %s... ", names[name_index], rolls[first][second]);
                
                if(sum == 10){             /* sparkles and resurrects */
                    Left = left(name_index, Players);
                    Right = right(name_index, Players);
                    lives[Left] += 1;
                    lives[Right] += 1;
                    if( lives[Left]-1 == 0){
                        printf("resurrects %s ", names[Left]);
                        }
                    else{
                        printf("sparkles %s ", names[Left]);
                        }
                    
                    if( lives[Right]-1 == 0){
                        printf("resurrects %s ", names[Right]);
                        }
                    else{
                        printf("sparkles %s ", names[Right]);
                        }
                    }
                printf("\n");
                }
            else{
                outcome[name_index] = 100;
                }
            name_index++;
            }     /* now we have a outcome[] have outcomes*/
                
        int outcome_index = 0;
        for( int i = 0; i < Players; i++ ){
            lowest = lower(lowest, outcome[i]);
            if( (lowest == outcome[i]) && (lowest != outcome[outcome_index]) ){ /***********************************/
                outcome_index = i;
                }
            }
        
        lives[outcome_index] = lives[outcome_index] - 1;
        
        printf("%s is forced to eat garlic!\n", names[outcome_index]);
        if( lives[outcome_index] == 1 ){
            printf("%s has 1 life remaining.\n", names[outcome_index]);
            }
        else if( lives[outcome_index] == 0 ){
            printf("%s has died.\n", names[outcome_index]);
            }
        else{
            printf("%s has %d lives remaining.\n", names[outcome_index], lives[outcome_index]);
            }

            
        int count = 0;
        int winner;
        for( int i = 0; i < Players; i++){
            if(lives[i] == 0){
                count++;
                }
            else{
                winner = i;
                }
            }
        if(count == Players-1){
            end = 1;
            printf("%s wins the Garlic Game!\n", names[winner]);
            }
            
        round++;
        }
    return 0;
    }



/*--------------------------------------- */
int main(void){
    
    int players;
    printf("Number of players: ");
    scanf("%d", &players);
    if( !( (players >= 2) && (players <= 10) ) ){
        fprintf(stderr, "Invalid number of players.\n");
        goto end;
        }
    
    uint16_t randseed;
    printf("Random seed: ");
    scanf("%" SCNu16, &randseed);
    if( !((randseed >= 0) && (randseed <= 32768) ) ){
        fprintf(stderr, "Invalid number of players.\n");
        goto end;
        }
        
    srand(randseed);
    
    game(players);
    
    end:
        return 0;
}
