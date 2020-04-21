import rxtxrobot.*;

public class RobotMovement{
    RXTXRobot r;
    Navigation nav = new Navigation(); //initialize new Navigation class
    private int return_value; //newton raphson returned value
    char[] beacon_chars; //raw beacon characters detected
    int[] beacon_angles; //raw beacon angle values
    private double[] destination; //coordinates of point of interest
    public double[] solution; //coordinates produced by newton raphson method
    public double[] position; //robot's current coordinates calculated from solution
    public double distance = 0.0; //distance from robot to destination
    public double direction = 0.0; //direction robot needs to face to move towards destination
    public double heading = 0.0; //direction the robot is currently facing
    private double angle1; //angle between first and second beacons
    private double angle2; //angle between second and third beacons
    private int quadrant; //which quadrant robot is operating in

    RobotMovement(RXTXRobot r, double[] destination, char[] beacon_chars, int[] beacon_angles, int quadrant){
        this.r = r;
        this.beacon_chars = beacon_chars;
        this.beacon_angles = beacon_angles;
        this.quadrant = quadrant;
        this.destination = destination;
        this.angle1 = ((beacon_angles[1] - beacon_angles[0]) * 180) / 150;
        this.angle2 = ((beacon_angles[2] - beacon_angles[1]) * 180) / 150;
    }

    public boolean reportAngles(){ //prints out the angles between beacon pairs
        if(beacon_angles[2] == -1){ //if any of the dummy values remain in int[] beacon_angles, then print error message and slightly turn robot to try again
			System.out.println("failed to detect three beacons");
			System.out.println("performing minor reposition an attempt to allow for better beacon detection, rerun this method after new beacon measurements have been made");
			r.runTwoPCAMotor(8, 290, 9, -370, 300);
			return false;
		}
		else{ //else print the angles between beacons
			System.out.println("Angle between " + beacon_chars[0] + " and " + beacon_chars[1] + " is " + (int)angle1);
            System.out.println("Angle between " + beacon_chars[1] + " and " + beacon_chars[2] + " is " + (int)angle2);
            return true;
		}
    }

    public boolean solve(){ //uses provided navigation class to solve for position based on coordinates
        nav.setAngles(angle1, angle2);
        return_value = nav.newton_raphson();
	    if(return_value == Navigation.RETURN_SUCCESS){ //if the calculation was successful, then print solution and return true
	        solution = nav.getSolution();
            System.out.println("solution of robot = (" + solution[0] + "," + solution[1] + ")");
            return true;
		}
		else{ //if the calculation fails, print an error message and slightly turn the robot to reattempt beacon readings
			System.out.println("failed to solve for current position");
			System.out.println("performing minor reposition an attempt to allow for better beacon detection, rerun this method after new beacon measurements have been made");
			r.runTwoPCAMotor(8, 290, 9, -370, 300);
			return false;
		}
    }

    public boolean findPosition(){ //takes the solve values and converts them into accurate coordinates based on which quadrant robot is in and which beacons were detected
        switch(quadrant){
			case 1: //if quadrant one, test for the following series of beacon character orders, then convert the solution into a position as needed
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
				else{
					System.out.println("bad ordering of beacon_chars[]");
					System.out.println("performing minor reposition an attempt to allow for better beacon detection, rerun this method after new beacon measurements have been made");
					r.runTwoPCAMotor(8, 290, 9, -370, 300);
					return false;	
				}
				break;
			case 2: //same applies for quadrant two, three, and four
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
				else if(beacon_chars[0] == 'G' && beacon_chars[1] == 'V' && beacon_chars[2] == 'S')
					position = new double[]{16 - solution[1], solution[0]};
				else{
					System.out.println("bad ordering of beacon_chars[]");
					System.out.println("performing minor reposition an attempt to allow for better beacon detection, rerun this method after new beacon measurements have been made");
					r.runTwoPCAMotor(8, 290, 9, -370, 300);
					return false;	
				}
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
				else{
					System.out.println("bad ordering of beacon_chars[]");
					System.out.println("performing minor reposition an attempt to allow for better beacon detection, rerun this method after new beacon measurements have been made");
					r.runTwoPCAMotor(8, 290, 9, -370, 300);
					return false;	
				}
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
				else if(beacon_chars[0] == 'N' && beacon_chars[1] == 'M' && beacon_chars[2] == 'K')
					position = new double[]{16 - solution[1], solution[0]};
				else{
					System.out.println("bad ordering of beacon_chars[]");
					System.out.println("performing minor reposition an attempt to allow for better beacon detection, rerun this method after new beacon measurements have been made");
					r.runTwoPCAMotor(8, 290, 9, -370, 300);
					return false;	
				}
                break;
        }
        return true;
    }

    public void heading(){ //calculates which direction the robot is facing in radians relative to its current quadrant
        double heading_corrector = 0 - (beacon_angles[0] / 150 * Math.PI) + (.5 * Math.PI);
		switch(quadrant){ //calculation is made based on which quadrant the robot is in and which beacon was first detected
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
    }

    public void distance(){ //calculates the distance the robot has to travel to reach its destination
        distance = Math.sqrt(Math.pow(destination[0] - position[0], 2) + Math.pow(destination[1] - position[1], 2));
		System.out.println("distance from destination is " + distance + " feet");
    }

    public void direction(){ //calculates how many degrees robot needs to turn to face destination and how long it will need to turn counterclockwise for
		direction = Math.atan((destination[1] - position[1]) / (destination[0] - position[0])); //Math.atan() gives angles in range from -pi/2 to pi/2, so we need to fit that to a full 0 to 2pi circle using the following if statements
        //because the arctangent function on returns values in a range from -pi/2 to pi/2, we need to virtually expands that range to 0 to 2pi
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
		System.out.println("robot must turn " + Math.abs((int)(direction - heading)) + " degrees to face destination");
    }

    public void turn(){ //turns the robot towards destination
        double turn_duration = 500 * Math.abs(direction - heading); //duration of turn in seconds
        if(direction > heading){ //turn left
			r.runTwoPCAMotor(8, 200, 9, -254, (int)turn_duration);
	    }
	    else if(direction < heading){ //turn right
			r.runTwoPCAMotor(8, -200, 9, 254, (int)turn_duration);
		}
		r.sleep(250);
    }

    public void forward(){//moves forward for specific duration
        double travel_duration = 500 * distance;
        r.runTwoPCAMotor(8, -290, 9, -370, (int)travel_duration);
        r.sleep(10000);
    }
}