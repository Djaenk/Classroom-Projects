#include <fstream>
#include "DSString.h"
#include "match.h"
#include "team.h"
#include "player.h"

int main(int argc, char *argv[]){
	Match laser_tag = Match();

	std::ifstream team1_file(argv[1]);
	std::ifstream team2_file(argv[2]);
	std::ifstream match_file(argv[3]);
	std::ofstream output_file(argv[4]);
	Verbosity output_verbosity;

	//determine desired output verbosity by comparing passed argument to generated DSStrings,
	//defaults to low if not specified or unparseable
	DSString vlow = DSString('v') + DSString('l') + DSString('o') + DSString('w');
	DSString vmed = DSString('v') + DSString('m') + DSString('e') + DSString('d');
	DSString vhigh = DSString('v') + DSString('h') + DSString('i') + DSString('g') + DSString('h');
	if(argc >= 6){
		if(DSString(argv[5]) == vhigh){
			output_verbosity = Verbosity::high;
		}
		else if(DSString(argv[5]) == vmed){
			output_verbosity = Verbosity::med;
		}
		else if(DSString(argv[5]) == vlow){
			output_verbosity = Verbosity::low;
		}
		else{
			output_verbosity = Verbosity::low;
		}
	}

	laser_tag.parse_team_file(team1_file);
	laser_tag.parse_team_file(team2_file);
	laser_tag.assign_trackers();
	laser_tag.parse_match_file(match_file);
	laser_tag.generate_report(output_file, output_verbosity);
}