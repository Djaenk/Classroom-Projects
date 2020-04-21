#ifndef MATCH
#define MATCH

#include "DSString.h"
#include "team.h"
#include "player.h"

enum class Verbosity{low, med, high};

class Tag;

class Team;

class Match{
	private:
		Team* teams = new Team[2];
		Tag* tag_occurences = nullptr; //tags in the match file are recorded as a linked list of Tag objects
		int* team_scores = new int[2];

	public:
		~Match();

		void parse_team_file(std::istream&);
		int add_team(DSString team_name, int team_size);
		Team* get_team1(){return teams + 0;}
		Team* get_team2(){return teams + 1;}
		void sort_teams();
		void assign_trackers();

		void parse_match_file(std::istream&);
		Tag* get_tag(int index); //returns a pointer to index-th tag as if tag_occurences were an array
		void add_tag(Tag* tag);

		void update_scores();
		int get_team1_score(){return team_scores[0];}
		int get_team2_score(){return team_scores[1];}

		void generate_report(std::ostream&, Verbosity v);

    private:
        Team* teams = new Team[2];
        Tag* tag_occurences = nullptr; //tags in the match file are recorded as a linked list of Tag objects
        int* team_scores = new int[2];

    public:
        ~Match();

        void parse_team_file(std::istream&);
        void add_team(Team* team);
        Team* get_team1(){return teams + 0;}
        Team* get_team2(){return teams + 1;}
        void sort_teams();
        void assign_trackers();

        void parse_match_file(std::istream&);
        Tag* get_tag(int index); //returns a pointer to index-th tag as if tag_occurences were an array
        void add_tag(Tag* tag);

        void update_scores();
        int get_team1_score(){return team_scores[0];}
        int get_team2_score(){return team_scores[1];}

        void generate_report(std::ostream&, Verbosity v);
};

struct Tag{
    Tag(int tagger_id, int target_id, int timestamp, int location) :
        tagger_id(tagger_id),
        target_id(target_id),
        timestamp(timestamp),
        location(location){} //set constant member variables in initialization list, leave contructor body empty

    const int tagger_id;
    const int target_id;
    const int timestamp;
    const int location;
    Tag* next_tag = nullptr;

    int value(){ //give the point value of the tag based on where the target was hit
        if(location == 1) return 5;
        if(location == 2) return 8;
        if(location == 3) return 7;
        if(location == 4) return 4;
        return 0;
    }
};

#endif
