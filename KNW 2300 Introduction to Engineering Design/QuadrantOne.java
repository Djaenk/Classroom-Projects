import rxtxrobot.*;

public class QuadrantOne {
	static int[] beacon_angles;
	static char[] beacon_chars;
	
	public static void returnAngles(RXTXRobot r) {
		char ircharA = ' ';
		char ircharB = ' ';
		char ircharC = ' ';
		char irchar = ' ';  //give to the navigation method
		int iA = -1;
		int iB = -1;
		int iC = -1;
		int i = 0;
		
		r.runPCAServo(11, 0);
		r.sleep(1000);
		for (i = 0; i < 180; i += 2) {
			System.out.println("Moving servo to " + ((i*180)/150) + " degrees.");
			r.runPCAServo(11, i); // continue to spin until we find something
			r.sleep(0200); // wait for the servo to turn
			irchar = r.getIRChar();
			if (irchar != '0') {
				if (ircharA == ' ') {
					ircharA = irchar;
					iA = i;
					System.out.println("Sensed " + ircharA + " at " + (iA*180)/150);
					continue;
				}
				if ((ircharB == ' ') && (irchar != ircharA)) {
					ircharB = irchar;	//setting beacons A B and C (and the angles between them)
					iB = i;
					System.out.println("Sensed " + ircharB + " at " + (iB*180)/150);
					continue;
				}
				if ((ircharC == ' ') && (irchar != ircharA) && (irchar != ircharB)) {
					ircharC = irchar;
					iC = i;
					System.out.println("Sensed " + ircharC + " at " + (iC*180)/150);
					break;
				}
			}
		} // end for
		
		beacon_chars = new char[]{ircharA, ircharB, ircharC};
		beacon_angles = new int[]{iA, iB, iC};
		r.allPCAStop();
	}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	public static int moveToLocation(RXTXRobot r, double[] destination, char[] beacon_chars, int[] beacon_angles, int quadrant)
	{
		Navigation nav = new Navigation();
	    int return_value = nav.newton_raphson();
		double[] solution; //output of navigation class
		double[] position = null; //coordinates of current location
	    double distance = 0.0; //distance from robot to destination
		double direction = 0.0; //direction robot needs to face to reach destination
		double heading = 0.0; //direction robot is facing when method is run
		double angle1 = ((beacon_angles[1] - beacon_angles[0]) * 180) / 150;
		double angle2 = ((beacon_angles[2] - beacon_angles[1]) * 180) / 150;
		
		if(beacon_angles[2] == -1){
			System.out.println("failed to detect three beacons");
			System.out.println("performing minor reposition an attempt to allow for better beacon detection, rerun this method after new beacon measurements have been made");
			r.runTwoPCAMotor(8, 290, 9, -370, 300);
			return 0;
		}
		else{
			System.out.println("Angle between " + beacon_chars[0] + " and " + beacon_chars[1] + " is " + (int)angle1);
			System.out.println("Angle between " + beacon_chars[1] + " and " + beacon_chars[2] + " is " + (int)angle2);
		}

		//plug angles into navigation class and get robot's location
	    nav.setAngles(angle1, angle2);
	    if(return_value == Navigation.RETURN_SUCCESS){
	        solution = nav.getSolution();
			System.out.println("solution of robot = (" + solution[0] + "," + solution[1] + ")");
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
				else{
					System.out.println("bad ordering of beacon_chars[]");
					System.out.println("performing minor reposition an attempt to allow for better beacon detection, rerun this method after new beacon measurements have been made");
					r.runTwoPCAMotor(8, 290, 9, -370, 300);
					return 0;	
				}
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
				else if(beacon_chars[0] == 'G' && beacon_chars[1] == 'V' && beacon_chars[2] == 'S')
					position = new double[]{16 - solution[1], solution[0]};
				else{
					System.out.println("bad ordering of beacon_chars[]");
					System.out.println("performing minor reposition an attempt to allow for better beacon detection, rerun this method after new beacon measurements have been made");
					r.runTwoPCAMotor(8, 290, 9, -370, 300);
					return 0;	
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
					return 0;	
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
					return 0;	
				}
				break;
		}

		//calculate robot's current heading
		double heading_corrector = 0 - (beacon_angles[0] / 150 * Math.PI) + (.5 * Math.PI);
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
		System.out.println("robot must turn " + Math.abs((int)(direction - heading)) + " degrees to face destination");
		
		//figure out how long to turn the robot for
		double turn_duration = 500 * Math.abs(direction - heading); //duration of turn in seconds
		
	    //determine which way to turn the robot
	    if(direction > heading){ //turn left
			r.runTwoPCAMotor(8, 200, 9, -254, (int)turn_duration); //turns left motor backwards for 100 milliseconds
	    }
	    else if(direction < heading){
			r.runTwoPCAMotor(8, -200, 9, 254, (int)turn_duration); //turns left motor forwards for 100 milliseconds
		}
		r.sleep(250);
		
		//calculate how long to travel forward for after turning
		double travel_duration = 500 * distance;

		//move forward
		r.runTwoPCAMotor(8, -290, 9, -370, (int)travel_duration);
		
		r.allPCAStop();

		return 1;
	}
	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	public static void tempSense(RXTXRobot r) {
		double x=-0.3593;
	     double m= 222.99;
	     int sum = 0;
	 	r.runPCAServo(7, 140); //- extended thermistor/conductivity
			  r.refreshAnalogPins();
		for (int i = 0; i < 15; i++) {
           sum += r.getAnalogPin(0).getValue();
       }
     System.out.println("The current temperature in Celsius is: " + (((sum/15)-x)/m) + "'C");
		r.close();
	}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	public static void conductSense(RXTXRobot r) {
			double x=-16.709;
			double m= 980.14;
			int conductReading = 0;
			 r.refreshAnalogPins();
			r.runPCAServo(7, 180); //- extended thermistor/conductivity
			 r.sleep(12000);
			for (int i=0;i<5; i++){

			     int reading = r.getConductivity();
			      conductReading += reading;
			        
			   } // end for
				r.runPCAServo(7,80); //retract arm
			 System.out.println("Percent Water per gram: " + (((conductReading/5)-x)/m) + "%");
	}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	public static void inclineSense(RXTXRobot r) {
		r.runTwoPCAMotor(8, -340, 9, -400, 2200); // goes up quad 4 ramp
		int sum = 0; //sum of inclinometer readings (to take an average over several readings)
		double x=-0.9834; //1.4286;
		double m= 721.88;
		for (int i = 0; i < 3; i++) {
	            r.refreshAnalogPins();
	            sum += r.getAnalogPin(1).getValue();
	        }
		  System.out.println("Final angle reading: " + (((sum/3)-x)/m));
	      r.runPCAServo(10, 20); // deploy ball
	      r.sleep(4000);
	      r.runPCAServo(10, 80); // retract arm after ball is deployed
	}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	public static void main(String[] args) {
		int sum = 0; // dummy value
		int conductReading = 0; // dummy value
		double[] hotbox = new double[]{15.0,3.0};
		double[] volcano_base = new double[]{12.0, 4.0};
		double[] volcano = new double[]{16.0, 8.0};
		RXTXRobot r = new ArduinoUno(); // Create RXTXRobot object
		r.setPort("COM5");
		int success = 0;
		r.connect();

		r.runTwoPCAMotor(8, -290, 9, -390, 2100); // cross bridge
		while (success != 1) {
		returnAngles(r);
		success = moveToLocation(r, hotbox, beacon_chars, beacon_angles, 1);
		}
		success = 0;

		r.runTwoPCAMotor(8, -290, 9, 370, 540);
		while (r.getPing(5) > 50) { // 50 cm gives the robot ample time to stop and accounts for error of navigation
			r.sleep(300);
			r.runTwoPCAMotor(8, 290, 9, -370, 50);
		}
		
		r.runTwoPCAMotor(8, -290, 9, -370, 500);
		tempSense(r);

		while (success != 1) {
		returnAngles(r);
		success = moveToLocation(r, volcano_base, beacon_chars, beacon_angles, 1);
		}
		success = 0;
	
		while (success != 1) {
			returnAngles(r);
			success = moveToLocation(r, volcano, beacon_chars, beacon_angles, 1);
		}
		success = 0;
	
		r.allPCAStop(); // to stop the robot from crashing into the wall
		r.close();
	} //end main
} // end class
