# Lab 12

Stephen Kim (811-411-225)

## Instructions

To clean my code (i.e., remove any compiled files), type:

```
$ make clean
```

To compile my code, type:

```
$ make
```

To run my code (after compiling it), type:

```
$ ./lab12
```

## Reflection

For my initial brainstorm, I planned to use a vector. However, I ended up using a 2D vector instead. I used a stringstream to parse
the string and then saved each element into a vector as long as it wasn't "|". I then checked to see where the special characters
occured (Ex. ">>") where I would them make the following element declared in the STDIN/OUT/ERR as necessary. Furthermore, I created
several ints and booleans to loop through the vector in order to check which arguments belonged to which processes in order to be able
to print out the Process lists. 