# CS 7330 Database Management and File Organization

## Running Two-Phase Locking Simulation

Python 3 is required.

To run with basic deadlock detection:

```bash
python3 detect.py <number of items in database> < file 1> < file 2> ... <transaction file n>
```

To run with wait-die deadlock avoidance policy:

```bash
python3 wait-die.py <number of items in database> < file 1> < file 2> ... <transaction file n>
```