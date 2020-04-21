#ifndef PLAYER
#define PLAYER

#include "DSString.h"

class Team;

class HitTracker;

class Player{
<<<<<<< HEAD
<<<<<<< HEAD
	private:
		int player_id;
		DSString player_name;
		int tag_count = 0;
		int points = 0;
		HitTracker* trackers = nullptr; //a player's hit trackers are stored as a linked list

	public:
		Player(){};
		Player(int id, const DSString name);
		~Player();

		int get_id(){return player_id;}
		DSString get_name(){return player_name;}
		void increment_tag_count(){tag_count++;}
		int get_tag_count(){return tag_count;}
		void add_points(int points){this->points += points;}
		int get_points(){return points;}
		void add_tracker(HitTracker* tracker);
		HitTracker* get_tracker_by_target_id(int target_id);
=======
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
    private:
        int player_id;
        DSString player_name;
        int tag_count;
        int points;
        HitTracker* trackers = nullptr; //a player's hit trackers are stored as a linked list

    public:
        Player(){};
        Player(int id, const DSString name);
        Player(Team &team, int id, const DSString name);
        ~Player();

        int get_id(){return player_id;}
        DSString get_name(){return player_name;}
        void increment_tag_count(){tag_count++;}
        int get_tag_count(){return tag_count;}
        void add_points(int points){this->points += points;}
        int get_points(){return points;}
        void add_tracker(HitTracker* tracker);
        HitTracker* get_tracker_by_target_id(int target_id);
<<<<<<< HEAD
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
};

struct HitTracker{ //structure to keep track of who a player object has tagged and how many times
    HitTracker(int target_id) : target_id(target_id){}

    const int target_id;
    int tag_count = 0;
    HitTracker* next_tracker = nullptr;
};

#endif
