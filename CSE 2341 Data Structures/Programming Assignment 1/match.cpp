#include "DSString.h"
#include "match.h"
#include "team.h"
#include "player.h"

Match::~Match(){
    delete[] teams;
<<<<<<< HEAD
<<<<<<< HEAD
	delete[] team_scores;
=======
    delete[] team_scores;
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
=======
    delete[] team_scores;
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
    Tag* current_tag;
    while(tag_occurences != nullptr){ //as long as tag_occurences isn't a null pointer...
        current_tag = tag_occurences;
        tag_occurences = tag_occurences->next_tag; //point tag_occurences to the next Tag...
        delete current_tag; //and delete what it previously pointed to
    }
}

void Match::parse_team_file(std::istream& input){
    //list of variables for temporary file data storage
    DSString team_name;
    int team_size;
    int player_id;
    DSString player_name;

    getline(input, team_name);
    input >> team_size;
<<<<<<< HEAD
<<<<<<< HEAD
	int team = this->add_team(team_name, team_size);
    for(int i = 0; i < team_size; i++){
        input >> player_id >> player_name;
		teams[team].add_player(player_id, player_name);
    }
=======
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
    Team* team = new Team(team_name, team_size);
    for(int i = 0; i < team_size; i++){
        input >> player_id >> player_name;
        team->add_player(new Player(player_id, player_name));
    }
    this->add_team(team);
<<<<<<< HEAD
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
}

void Match::parse_match_file(std::istream& input){
    //list of variables for temporary file data storage
    int match_tag_count;
    int tagger_id;
    int target_id;
    int timestamp;
    int location;

    input >> match_tag_count;
    for(int i = 0; i < match_tag_count; i++){
        input >> tagger_id >> target_id >> timestamp >> location;
        Tag* new_tag = new Tag(tagger_id, target_id, timestamp, location);
        this->add_tag(new_tag);
    }
<<<<<<< HEAD
<<<<<<< HEAD
}

int Match::add_team(DSString team_name, int team_size){
    if(teams[0].get_size() == 0){
		teams[0].~Team();
        teams[0] = Team(team_name, team_size);
		return 0;
    }
    else if(teams[1].get_size() == 0){
		teams[1].~Team();
        teams[1] = Team(team_name, team_size);
		return 1;
    }
=======
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
}

void Match::add_team(Team* team){
    if(teams[0].get_size() == 0){
        teams[0].~Team();
        teams[0] = *team;
    }
    else if(teams[1].get_size() == 0){
        teams[1].~Team();
        teams[1] = *team;
    }
}

Tag* Match::get_tag(int index){
    Tag* tag = tag_occurences;
    for(int i = 0; i < index; i++){
        tag = tag->next_tag;
    }
    return tag;
<<<<<<< HEAD
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
}

void Match::sort_teams(){
    teams[0].sort_players();
    teams[1].sort_players();
}

void Match::assign_trackers(){
    //assign tracker to each member of a team for each member of the other team
    for(int i = 0; i < teams[0].get_size(); i++){ //outer loop for each member of first team
        for(int j = 0; j < teams[1].get_size(); j++){ //inner loop for each member of second team
            //new tracker to track hits against player on team 2
<<<<<<< HEAD
<<<<<<< HEAD
			std::cout << teams[0].get_player_by_index(i)->get_name() << ' ' << '-' << ' ' << teams[0].get_player_by_index(j)->get_name();
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
            HitTracker* new_tracker_1 = new HitTracker(teams[1].get_player_by_index(j)->get_id());
            teams[0].get_player_by_index(i)->add_tracker(new_tracker_1);
            //new tracker to track hits against player on team 1
            HitTracker* new_tracker_2 = new HitTracker(teams[0].get_player_by_index(i)->get_id());
            teams[1].get_player_by_index(j)->add_tracker(new_tracker_2);
        }
    }
<<<<<<< HEAD
}

<<<<<<< HEAD
Tag* Match::get_tag(int index){
    Tag* tag = tag_occurences;
    for(int i = 0; i < index; i++){
        tag = tag->next_tag;
    }
    return tag;
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
}

=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
void Match::add_tag(Tag* new_tag){
    //adds new tag to this Match's list of tags
    Tag* tag = tag_occurences;
    if(tag == nullptr){
        tag_occurences = new_tag;
    }
    else{
        while(tag->next_tag != nullptr){
            tag = tag->next_tag;
        }
        tag->next_tag = new_tag;
    }

    //gives tagger credit for the tag
    int tagger_id = new_tag->tagger_id;
    int target_id = new_tag->target_id;
    for(int i = 0; i < 2; i++){
        if(teams[i].get_player_by_id(tagger_id) != nullptr){ //if the player is on this team...
            Player* tagger = teams[i].get_player_by_id(tagger_id);
            tagger->add_points(new_tag->value()); //points are added to their score,
            tagger->get_tracker_by_target_id(target_id)->tag_count++; //the number of tags they have on the target is incremented,
            tagger->increment_tag_count(); //and so is their total number of tags.
        }
    }
}

void Match::update_scores(){
    for(int i = 0; i < 2; i++){
        team_scores[i] = 0;
        for(int j = 0; j < teams[i].get_size(); j++){
            team_scores[i] += teams[i].get_player_by_index(j)->get_points();
        }
    }
}

void Match::generate_report(std::ostream& report, Verbosity v){
    this->sort_teams();
    this->update_scores();

    //predefine a few strings that will be repeatedly used throughout the report
    DSString points = DSString('p') + DSString('o') + DSString('i') + DSString('n') + DSString('t') + DSString('s');
    DSString tags = DSString('t') + DSString('a') + DSString('g') + DSString('s');
    DSString had_a_total_of = DSString('h') + DSString('a') + DSString('d') + DSString(' ') + DSString('a')
                            + DSString(' ') + DSString('t') + DSString('o') + DSString('t') + DSString('a')
                            + DSString('l') + DSString(' ') + DSString('o') + DSString('f');
    DSString tagged = DSString('t') + DSString('a') + DSString('g') + DSString('g') + DSString('e') + DSString('d');
    DSString times = DSString('t') + DSString('i') + DSString('m') + DSString('e') + DSString('s');
    DSString Best_score_from = DSString('B') + DSString('e') + DSString('s') + DSString('t') + DSString(' ')
                            + DSString('s') + DSString('c') + DSString('o') + DSString('r') + DSString('e')
                            + DSString(' ') + DSString('f') + DSString('r') + DSString('o') + DSString('m');
    DSString Overall = DSString('O') + DSString('v') + DSString('e') + DSString('r') + DSString('a') + DSString('l') + DSString('l');
    DSString Winners = DSString('W') + DSString('i') + DSString('n') + DSString('n') + DSString('e') + DSString('r') + DSString('s');
<<<<<<< HEAD
<<<<<<< HEAD
	DSString N_A = DSString('N') + DSString('/') + DSString ('A');
=======
    DSString N_A = DSString('N') + DSString('/') + DSString ('A');
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
=======
    DSString N_A = DSString('N') + DSString('/') + DSString ('A');
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec

    for(int i = 0; i < 2; i++){
        report << teams[i].get_name();
        if(v == Verbosity::low){
            report << ':' << ' ';
            report << team_scores[i] << ' ' << points << std::endl;
        }
        if(v == Verbosity::med){
            report << std::endl;
            for(int j = 0; j < teams[i].get_size(); j++){
                report << '\t' << teams[i].get_player_by_index(j)->get_name();
                report << ' ' << had_a_total_of << ' ';
                report << teams[i].get_player_by_index(j)->get_tag_count() << ' ';
                report << tags << std::endl;
            }
            report << std::endl;
        }
        if(v == Verbosity::high){
            Player* tagger;
            Player* target;
            report << std::endl;
            for(int j = 0; j < teams[i].get_size(); j++){
                tagger = teams[i].get_player_by_index(j);
                for(int k = 0; k < teams[(i + 1) % 2].get_size(); k++){
                    target = teams[(i + 1) % 2].get_player_by_index(k);
                    report << '\t';
                    report << tagger->get_name() << ' ' << tagged << ' ';
                    report << target->get_name() << ' ';
                    report << tagger->get_tracker_by_target_id(target->get_id())->tag_count << ' ';
                    report << times << std::endl;
                }
                report << '\t' << tagger->get_name() << ' ';
                report << had_a_total_of << ' ' << tagger->get_tag_count() << ' ' << tags << std::endl;
            }
            report << '\t' << teams[i].get_name() << ':' << ' ';
            report << team_scores[i] << ' ' << points << std::endl;
            report << std::endl;
        }
    }

<<<<<<< HEAD
<<<<<<< HEAD
	Team winning_team;
	if(team_scores[0] > team_scores[1]){
		winning_team = teams[0];
	}
	else if(team_scores[1] > team_scores[0]){
		winning_team = teams[1];
	}
	else{
		winning_team = Team(N_A, 0);
	}
=======
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
    Team winning_team;
    if(team_scores[0] > team_scores[1]){
        winning_team = teams[0];
    }
    else if(team_scores[1] > team_scores[0]){
        winning_team = teams[1];
    }
    else{
        winning_team = Team(N_A, 0);
    }
<<<<<<< HEAD
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
=======
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
    if(v == Verbosity::low){
        report << Overall << ' ' << Winners << ':' << ' ' << winning_team.get_name();
    }
    if(v == Verbosity::med){
        for(int i = 0; i < 2; i++){
            report << Best_score_from << ' ' << teams[i].get_name() << ':' << ' ';
            report << teams[i].get_highest_scoring_player()->get_name() << ' ';
            report << '(' << teams[i].get_highest_scoring_player()->get_points() << ')' <<std::endl;
        }
        for(int i = 0; i < 2; i++){
            report << teams[i].get_name() << ':' << ' ';
            report << team_scores[i] << ' ' << points << std::endl;
        }
        report << Winners << ':' << ' ' << winning_team.get_name();
    }
    if(v == Verbosity::high){
        report << Winners << ':' << ' ' << winning_team.get_name();
<<<<<<< HEAD
<<<<<<< HEAD
	}
	report << std::endl;
=======
    }
    report << std::endl;
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
=======
    }
    report << std::endl;
>>>>>>> 0f90a2fa2e0adfb9badc6f9d736e3a8e19feeaec
}
