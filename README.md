###pipex (42 project)
This is a very basic exercise to get used to pipes and processes in C.

Pipex simply mimics the behavior of this exact bash line:
```bash
< infile cmd1 | cmd2 > outfile
```
Where the arguments are the input file, first command, second command and output file in that order.
The program handles errors the same way bash does.
That's all there is to it! If you're interested in this being used practically, check out
my much bigger project [Minishell](https://github.com/N03l-MG/minishell).
