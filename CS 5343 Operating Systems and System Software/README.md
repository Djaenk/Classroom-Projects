# CS 7343 Operating Systems

## Compiling and Running Synchronization Programs

For base case:

```bash
gcc -synchronization_base.c numbergame.c queue.c -lpthread -o base_case
./base_case N T
```

For stage 1:

```bash
gcc -synchronization_1.c numbergame.c queue.c -lpthread -o stage_1
./stage_1 input.txt
```

For stage 2:

```bash
gcc -synchronization_2.c numbergame.c queue.c -lpthread -o stage_2
./stage_2 input.txt
```

## Compiling and Running Dining Philosopher Programs

For base case:

```bash
gcc philosopher_buffet.c bankers.c queue.c -lpthread -o base_case
./base_case input.txt
```

For stage 1:

```bash
gcc philosopher_buffet_1.c bankers.c queue.c -lpthread -o stage_1
./stage_1 input.txt
```

For stage 2:

```bash
gcc philosopher_buffet_2.c bankers.c queue.c -lpthread -o stage_2
./stage_2 input.txt
```