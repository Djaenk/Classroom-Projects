
# Graph Coloring Program

The instructions to compile and run this program assume use of a linux environment
and the GNU Compiler Collection.

## Compiling

```bash
g++ project.cpp graph_generation.cpp graph_coloring.cpp
```

## Running

The output executable which defaults to `a.out` may be run directly from the
command line. To generate a graph, provide command line arguments as follows.

```bash
./a.out <vertices> <edges> <COMPLETE|CYCLE|RANDOM> [UNIFORM|SKEWED|NORMAL]
```

Note that if `COMPLETE` or `CYCLE` are selected, the number of edges will be
ignored. If a distribution is not provided when selecting `RANDOM`, the program
will default to `NORMAL`.

To perform coloring on a graph, the input file and ordering method must be selected.

```bash
./a.out <input_file> <1|2|3|4|5|6>
```

Where the methods are as follows:
> 1 - Smallest Last Vertex Ordering
> 2 - Smallest Original Degree Ordering
> 3 - Uniform Random Ordering
> 4 - Largest Original Degree Ordering
> 5 - Breadth First Search Ordering
> 6 - Depth First Search Ordering
