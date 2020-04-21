#include "DSString.h"
#include "match.h"
#include "team.h"
#include "player.h"

Team::Team(Match &match, DSString team_name, int team_size){
    match.add_team(this);
    this->team_name = team_name;
    players = new Player[team_size];
}

Team::Team(DSString team_name, int team_size){
    this->team_name = team_name;
    players = new Player[team_size];
}

Team::~Team(){
    delete[] players;
}

void Team::add_player(int player_id, DSString player_name){
	players[player_count].~Player();
	players[player_count] = Player(player_id, player_name);
	player_count++;
void Team::add_player(Player* player){
    players[player_count].~Player();
    players[player_count] = *player;
    player_count++;
}

Player* Team::get_player_by_index(int index){
    if(index < player_count){
        return players + index;
    }
    else{
        return nullptr;
    }
}

Player* Team::get_player_by_id(int id){
    for(int i = 0; i < player_count; i++){
        if(players[i].get_id() == id){
            return players + i;
        }
    }
    return nullptr;
}

Player* Team::get_player_by_name(DSString name){
    for(int i = 0; i < player_count; i++){
        if(players[i].get_name() == name){
            return players + i;
        }
    }
    return nullptr;
}

void Team::sort_players(){
    for(int i = 0; i < player_count; i++){ //for every player on the team...
        for(int j = i; j > 0; j--){ //they are compared to every previous player...
            if(players[j].get_name() < players[j - 1].get_name()){ //and if they come before alphabetically...
                swap_players(&players[j], &players[j - 1]); //the two players' positions in the array are swapped...
            }
        }
    }
}

Player* Team::get_highest_scoring_player(){
    Player* highest_scorer = players;
    for(int i = 1; i < player_count; i++){
        if(players[i].get_points() > highest_scorer->get_points()){
            highest_scorer = &players[i];
        }
    }
    return highest_scorer;
}

void Team::swap_players(Player* a, Player* b){
    Player* temp = a;
    a = b;
    b = temp;
}
