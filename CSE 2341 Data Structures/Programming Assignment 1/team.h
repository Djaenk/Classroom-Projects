#ifndef TEAM
#define TEAM

#include "DSString.h"
#include "player.h"

class Match;

class Player;

class Team{
    private:
        DSString team_name;
        int player_count = 0;
        Player* players;

<<<<<<< HEAD
<<<<<<< HEAD
		void swap_players(Player* a, Player* b); //auxiliary function to swap indices of two players in the player array
	
	public:
		Team(){};
		Team(DSString team_name, int team_size);
		~Team();

		DSString get_name(){return team_name;}
		int get_size(){return player_count;}
		void add_player(int player_id, DSString player_name);
		void sort_players(); //insertion sort to put players into alphabetical order by name
		Player* get_player_by_index(int index);
		Player* get_player_by_id(int id);
		Player* get_player_by_name(DSString name);
		Player* get_highest_scoring_player();
=======
        void swap_players(Player* a, Player* b); //auxiliary function to swap indices of two players in the player array

=======
        void swap_players(Player* a, Player* b); //auxiliary function to swap indices of two players in the player array

>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
    public:
        Team(){};
        Team(Match &match, DSString team_name, int team_size);
        Team(DSString team_name, int team_size);
        ~Team();

        DSString get_name(){return team_name;}
        int get_size(){return player_count;}
        void add_player(Player* player);
        void sort_players(); //insertion sort to put players into alphabetical order by name
        Player* get_player_by_index(int index);
        Player* get_player_by_id(int id);
        Player* get_player_by_name(DSString name);
        Player* get_highest_scoring_player();
<<<<<<< HEAD
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
};

#endif
