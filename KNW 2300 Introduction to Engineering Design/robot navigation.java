//parameters:
//RXTXRobot object is required to move robot
//double[] destination is an array containing coordinates of point of interest
//char[] beacon_chars is an array of the characters detected by the IR sensors, in the order they were detected from left to right
//int[] beacon_measures is an array of beacon angle measurements relative to the IR servo, in the order they were detected from left to right
public class XD{
public int moveToLocation(RXTXRobot r, double[] destination, char[] beacon_chars, int[] beacon_angles, int quadrant)
{
	Navigation nav = new Navigation();
    int return_value = nav.newton_raphson();
	double[] solution; //output of navigation class
	double[] position; //coordinates of current location
    double distance; //distance from robot to destination
	double direction; //direction robot needs to face to reach destination
	double heading; //directino robot is facing when method is run
	double angle1 = beacon_angles[1] - beacon_angles[0];
	double angle2 = beacon_angles[2] - beacon_angles[1];

	if(beacon_angles[2] == -1){
		System.out.println("need to detect two beacons");
		r.runTwoPCAMotor(8, 290, 9, -370, 300);
		return 0;
	}
	//plug angles into navigation class and get robot's location
    nav.setAngles(angle1, angle2);
    if(return_value == Navigation.RETURN_SUCCESS){
        solution = nav.getSolution();
		System.out.println("(x,y) coordinates of robot = (" + solution[0] + "," + solution[1] + ")");
	}
	else{
		System.out.println("failed to solve for current position");
		System.out.println("performing minor reposition an attempt to allow for better beacon detection, rerun this method after new beacon measurements have been made");
		r.runTwoPCAMotor(8, 290, 9, -370, 300);
		return 0;
	}
	
	switch(quadrant){
		case 1:
			if(beacon_chars[0] == 'K' && beacon_chars[1] == 'G' && beacon_chars[2] == 'V')
				position = new double[]{32 - solution[1], solution[0]};
			else if(beacon_chars[0] == 'K' && beacon_chars[1] == 'S' && beacon_chars[2] == 'N')
				position = new double[]{16 - solution[0], 16 - solution[1]};
			else if(beacon_chars[0] == 'G' && beacon_chars[1] == 'V' && beacon_chars[2] == 'S')
				position = new double[]{32 - solution[0], 16 - solution[1]};
			else if(beacon_chars[0] == 'S' && beacon_chars[1] == 'N' && beacon_chars[2] == 'M')
				position = new double[]{solution[1], 16 - solution[0]};
			else if(beacon_chars[0] == 'N' && beacon_chars[1] == 'M' && beacon_chars[2] == 'K')
				position = new double[]{solution[0], solution[1]};
			else if(beacon_chars[0] == 'M' && beacon_chars[1] == 'K' && beacon_chars[2] == 'S')
				position = new double[]{16 - solution[1], solution[0]};
			break;
		case 2:
			if(beacon_chars[0] == 'V' && beacon_chars[1] == 'S' && beacon_chars[2] == 'K')
				position = new double[]{16 - solution[0], 16 - solution[1]};
			else if(beacon_chars[0] == 'S' && beacon_chars[1] == 'K' && beacon_chars[2] == 'G')
				position = new double[]{solution[1], 16 - solution[0]};
			else if(beacon_chars[0] == 'S' && beacon_chars[1] == 'N' && beacon_chars[2] == 'M')
				position = new double[]{16 - solution[0], 32 - solution[1]};
			else if(beacon_chars[0] == 'N' && beacon_chars[1] == 'M' && beacon_chars[2] == 'K')
				position = new double[]{solution[1], 32 - solution[0]};
			else if(beacon_chars[0] == 'K' && beacon_chars[1] == 'G' && beacon_chars[2] == 'V')
				position = new double[]{solution[0], solution[1]};
			break;
		case 3:
			if(beacon_chars[0] == 'S' && beacon_chars[1] == 'K' && beacon_chars[2] == 'G')
				position = new double[]{16 - solution[0], 16 - solution[1]};
			else if(beacon_chars[0] == 'S' && beacon_chars[1] == 'N' && beacon_chars[2] == 'M')
				position = new double[]{32 - solution[1], solution[0]};
			else if(beacon_chars[0] == 'N' && beacon_chars[1] == 'M' && beacon_chars[2] == 'K')
				position = new double[]{32 - solution[0], 16 - solution[1]};
			else if(beacon_chars[0] == 'K' && beacon_chars[1] == 'G' && beacon_chars[2] == 'V')
				position = new double[]{solution[1], 16 - solution[0]};
			else if(beacon_chars[0] == 'G' && beacon_chars[1] == 'V' && beacon_chars[2] == 'S')
				position = new double[]{solution[0], solution[1]};
			else if(beacon_chars[0] == 'V' && beacon_chars[1] == 'S' && beacon_chars[2] == 'K')
				position = new double[]{16 - solution[1], solution[0]};
			break;
		case 4:
			if(beacon_chars[0] == 'M' && beacon_chars[1] == 'K' && beacon_chars[2] == 'S')
				position = new double[]{16 - solution[0], 16 - solution[1]};
			else if(beacon_chars[0] == 'K' && beacon_chars[1] == 'S' && beacon_chars[2] == 'N')
				position = new double[]{solution[1], 16 - solution[0]};
			else if(beacon_chars[0] == 'K' && beacon_chars[1] == 'G' && beacon_chars[2] == 'V')
				position = new double[]{16 - solution[0], 32 - solution[1]};
			else if(beacon_chars[0] == 'G' && beacon_chars[1] == 'V' && beacon_chars[2] == 'S')
				position = new double[]{solution[1], 32 - solution[0]};
			else if(beacon_chars[0] == 'S' && beacon_chars[1] == 'N' && beacon_chars[2] == 'M')
				position = new double[]{solution[0], solution[1]};
			break;
		default:
			System.out.println("bad ordering of beacon_chars[]");
			System.out.println("performing minor reposition an attempt to allow for better beacon detection, rerun this method after new beacon measurements have been made");
			r.runTwoPCAMotor(8, 290, 9, -370, 300);
			return 0;
	}

	//calculate robot's current heading
	double heading_corrector = 0 - (beacon_angles[0] / 167 * Math.PI) + (81 / 167 * Math.PI);
	switch(quadrant){
		case 1:
			if(beacon_chars[0] == 'K')
				heading = Math.atan((0 - position[1]) / (16 - position[0])) + heading_corrector;
			else if(beacon_chars[0] == 'G')
				heading = Math.atan((0 - position[1]) / (32 - position[0])) + heading_corrector;
			else if(beacon_chars[0] == 'V')
				heading = Math.atan((16 - position[1]) / (32 - position[0])) + heading_corrector;
			else if(beacon_chars[0] == 'S')
				heading = Math.atan((16 - position[1]) / (16 - position[0])) + heading_corrector;
			else if(beacon_chars[0] == 'N')
				heading = Math.atan((16 - position[1]) / (0 - position[0])) + heading_corrector + Math.PI;
			else if(beacon_chars[0] == 'M')
				heading = Math.atan((0 - position[1]) / (0 - position[0])) + heading_corrector + Math.PI;
			break;
		case 2:
			if(beacon_chars[0] == 'V')
				heading = Math.atan((0 - position[1]) / (16 - position[0])) + heading_corrector;
			else if(beacon_chars[0] == 'S')
				heading = Math.atan((16 - position[1]) / (16 - position[0])) + heading_corrector;
			else if(beacon_chars[0] == 'N')
				heading = Math.atan((32 - position[1]) / (16 - position[0])) + heading_corrector;
			else if(beacon_chars[0] == 'M')
				heading = Math.atan((32 - position[1]) / (0 - position[0])) + heading_corrector + Math.PI;
			else if(beacon_chars[0] == 'K')
				heading = Math.atan((16 - position[1]) / (0 - position[0])) + heading_corrector + Math.PI;
			else if(beacon_chars[0] == 'G')
				heading = Math.atan((0 - position[1]) / (0 - position[0])) + heading_corrector + Math.PI;
			break;
		case 3:
			if(beacon_chars[0] == 'S')
				heading = Math.atan((0 - position[1]) / (16 - position[0])) + heading_corrector;
			else if(beacon_chars[0] == 'N')
				heading = Math.atan((0 - position[1]) / (32 - position[0])) + heading_corrector;
			else if(beacon_chars[0] == 'M')
				heading = Math.atan((16 - position[1]) / (32 - position[0])) + heading_corrector;
			else if(beacon_chars[0] == 'K')
				heading = Math.atan((16 - position[1]) / (16 - position[0])) + heading_corrector;
			else if(beacon_chars[0] == 'G')
				heading = Math.atan((16 - position[1]) / (0 - position[0])) + heading_corrector + Math.PI;
			else if(beacon_chars[0] == 'V')
				heading = Math.atan((0 - position[1]) / (0 - position[0])) + heading_corrector + Math.PI;
			break;
		case 4:
			if(beacon_chars[0] == 'M')
				heading = Math.atan((0 - position[1]) / (16 - position[0])) + heading_corrector;
			else if(beacon_chars[0] == 'K')
				heading = Math.atan((16 - position[1]) / (16 - position[0])) + heading_corrector;
			else if(beacon_chars[0] == 'G')
				heading = Math.atan((32 - position[1]) / (16 - position[0])) + heading_corrector;
			else if(beacon_chars[0] == 'V')
				heading = Math.atan((32 - position[1]) / (0 - position[0])) + heading_corrector + Math.PI;
			else if(beacon_chars[0] == 'S')
				heading = Math.atan((16 - position[1]) / (0 - position[0])) + heading_corrector + Math.PI;
			else if(beacon_chars[0] == 'N')
				heading = Math.atan((0 - position[1]) / (0 - position[0])) + heading_corrector + Math.PI;
			break;
	}
	System.out.println("robot's current heading is " + heading + " radians");

	//calculate the distance of travel and angle relative to course
	distance = Math.sqrt(Math.pow(destination[0] - position[0], 2) + Math.pow(destination[1] - position[1], 2));
	System.out.println("distance from destination is " + distance + " feet");
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
	System.out.println("robot must turn " + (int)(direction - heading) + " degrees counterclockwise to face destination");
	
	//figure out how long to turn the robot for
	double turn_duration = 1000 * Math.abs(direction - heading); //duration of turn in seconds
	
    //determine which way to turn the robot
    if(direction > heading){ //turn left
		r.runTwoPCAMotor(8, 100, 9, -127, (int)turn_duration); //turns left motor backwards for 100 milliseconds
    }
    else if(direction < heading){
		r.runTwoPCAMotor(8, -100, 9, 127, (int)turn_duration); //turns left motor forwards for 100 milliseconds
	}
	
	//calculate how long to travel forward for after turning
	double travel_duration = 1000 * distance;

	//move forward
	r.runTwoPCAMotor(8, -145, 9, -185, (int)travel_duration);
	
	return 1;
}
}