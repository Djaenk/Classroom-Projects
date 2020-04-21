public class ObstableAvoidance{
	
public void moveToLocation(RXTXRobot r, double[] destination, char[] beacon_chars, int[] beacon_angles)
{
	Navigation nav = new Navigation();
    int return_value = nav.newton_raphson();
	double[] solution;
	double[] position; //coordinates of current location
    double distance; //distance from robot to destination
	double direction; //direction robot needs to face to reach destination
	double heading; //directino robot is facing when method is run
	double angle1 = beacon_measures[1] - beacon_measures[0];
	double angle2 = beacon_measures[2] - beacon_measures[1];
	int quadrant; //need to know which quadrant we're in, because each one has its own coordinate plane which is a rotations of adjacent quadrants and god forbid placing all four quadrants on the same cartesian system

	//determine quadrant robot is in base on which beacons were measured and what order they were detected in
	if(beacon_chars[0] == 'N' && beacon_chars[1] == 'S' && beacon_chars[2] == 'K')
		quadrant = 1;
	else if(beacon_chars[0] == 'K' && beacon_chars[1] == 'S' && beacon_chars[2] == 'V')
		quadrant = 2;
	else if(beacon_chars[0] == 'G' && beacon_chars[1] == 'K' && beacon_chars[2] == 'S')
		quadrant = 3;
	else if(beacon_chars[0] == 'S' && beacon_chars[1] == 'K' && beacon_chars[2] == 'M')
		quadrant = 4;
	else
		throw new RuntimeException("bad beacon order in char[] beacon_chars");
	
	//plug angles into navigation class and get robot's location
    nav.setAngles(angle1, angle2);
    if(return_value == Navigation.RETURN_SUCCESS){
        solution = nav.getSolution();
        System.out.println("(x,y) coordinates of robot = (" + soln[0] + "," + soln[1] + ")");
	}
	position = new double[]{16 - solution[0], 16 - solution[1]};
	
	//calculate robot's current heading
	heading = Math.atan((16 - position[1]) / (0 - position[0])) + beacon_angles[2] - (Math.PI / 3);
	direction = Math.atan((destination[1] - position[1]) / (destination[0] - position[0]));
	//calculate the distance of travel and angle relative to course
    distance = Math.sqrt(Math.pow(destination[0] - position[0], 2) + Math.pow(destination[1] - position[1], 2));
	direction = Math.atan((destination[1] - position[1]) / (destination[0] - position[0])); //Math.atan() gives angles in range from -pi/2 to pi/2, so we need to fit that to a full 0 to 2pi circle using the following if statements
    if(destination[0] > position[0] && destination[1] > position[1]){
        //if destination x and y coordinate values are both greater, do nothing to direction calculation
    }
    else if(destination[0] < position[0] && destination[1] > position[1]){
        direction += Math.PI;
    }
    else if(destination[0] < position[0] && destination[1] < position[1]){
        direction += Math.PI;
    }
    else if(destination[0] > position[0] && destination[1] < position[1]){
        direction += 2 * Math.PI;
	}
	
	//figure out how long to turn the robot for
	double turn_duration = 10 * Math.abs(direction - heading); //duration of turn in seconds
	
    //determine which way to turn the robot
    if(direction > heading){
        r.runTwoPCAMotor(8, 116, 9, -148, 100); //turns left
    }
    else if(direction < heading){
        r.runTwoPCAMotor(8, -116, 9, 148, 100); //turns right
	}
	
	//calculate how long to travel forward for after turning
	double travel_duration = 10 * distance;

	//move forward
	for(int i = 0; i < travel_duration; i++){
		r.runTwoPCAMotor(8, -145, 9, -185, 100);
		if(r.getPing(5) < 20){
			r.runTwoPCAMotor(8, 116, 9, -148, (1000 * Math.PI / 2));
			
		}
	}

    //Nathan, I need you to test various speed values in the above if
    //statements until the robot faces the correct direction when this is run
    //I also don't know which ports the motors are hooked up to
}
}