#include "DSString.h"
#include "match.h"
#include "team.h"
#include "player.h"

Player::Player(int id, const DSString name){
    player_id = id;
    player_name = name;
}

Player::Player(Team &team, int id, const DSString name){
    team.add_player(this);
    player_id = id;
    player_name = name;
}

<<<<<<< HEAD
Player::~Player(){
<<<<<<< HEAD
	HitTracker* current_tracker;
	while(trackers != nullptr){
		current_tracker = trackers;
		trackers = trackers->next_tracker;
		delete current_tracker;
	}
=======
Player::Player(Team &team, int id, const DSString name){
    team.add_player(this);
    player_id = id;
    player_name = name;
}

Player::~Player(){
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
    HitTracker* current_tracker;
    while(trackers != nullptr){
        current_tracker = trackers;
        trackers = trackers->next_tracker;
        delete current_tracker;
    }
<<<<<<< HEAD
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
}

void Player::add_tracker(HitTracker* new_tracker){
    if(trackers == nullptr){
        trackers = new_tracker;
    }
    else{
        HitTracker* tracker = trackers;
        while(tracker->next_tracker != nullptr){
            tracker = tracker->next_tracker;
        }
        tracker->next_tracker = new_tracker;
    }
}

HitTracker* Player::get_tracker_by_target_id(int target_id){
    HitTracker* tracker = trackers;
    while(tracker != nullptr){
        if(tracker->target_id == target_id){
            return tracker;
        }
        tracker = tracker->next_tracker;
    }
    return nullptr;
}
