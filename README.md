**Problem Statement**

There is a scheme that defines the computation execution flow. The scheme is a directed graph with labeled arcs. The arc labels of the scheme are specific sets of information processing actions.

If an arc originates from a certain node in the scheme, then the corresponding actions can only be started when the actions of all incoming arcs (if any) have been executed and the corresponding data for further computations has been constructed.

The computation is considered complete when all actions present in the scheme have been executed.

Two actions are considered dependent if one of them uses data obtained as a result of executing the other action and, possibly, some other actions. Actions that are not dependent can be executed concurrently. A single action cannot be distributed among multiple threads.

For each set of actions, the number of actions it contains is specified. The names of the corresponding parameters match the arc labels of the scheme. Also specified is `nt` -- the number of threads that can execute actions.

Implement the computation execution according to the scheme so that, in addition to the thread running main, `nt` threads are launched and the total computation time is minimized:
1) If there is an action available for execution that has not been started, then each of the `nt` threads must be loaded with computations of other actions;
2) If we imagine an ideal situation where the execution of each action has the same duration, then the total computation time is minimal.

When implementing the computation, assume that the i-th action (numbering starts from 1) from set x is implemented by calling `f(x, i)`. As stubs, implement `f` so that when calling `f('a', 3)`, approximately the following text is output:
`Action 3 from set a has been executed.`

At the beginning of the computation, the following must be output:
`Computation started.`
Upon completion of the computation, the following must be output:
`Computation completed.`

**Implementation Constraints**
Language: C++.
For working with threads, only the following are allowed: `thread`, `jthread`, `semaphore`, `latch`, `barrier`.
For output, use `osyncstream`.
Throughout the execution of the entire program, only `nt` threads are allowed to be launched (in addition to the one running main). If one thread is completed and another is started in its place, these threads count as two launched threads (even if they do not run concurrently).
In the thread running main, computation actions cannot be executed.
The distribution of actions to be executed across threads and adherence to the execution sequence must be hardcoded, meaning nothing is decided or distributed dynamically (as that would be a completely different task).

**Submission Requirements**
Submit: all code files needed to build the executable file; a screenshot of the executable file build result; screenshots of the program operation results; a text file with the program output.

To redirect output to a text file:
`prog.exe > results.txt`

25) scheme №12, nt=6, a=5, b=7, c=6, d=4, e=6, f=8, g=4, h=9, i=6, j=5
