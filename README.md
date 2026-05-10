# Constrained Grid Navigation Engine

A stack-based pathfinding and navigation simulator built in C++ using SFML. This project simulates an intelligent agent navigating through a procedurally generated 2D environment containing dynamic movement constraints such as directional force vectors and rollback tunnels.

Originally developed as an algorithm design project, the system demonstrates concepts related to constrained pathfinding, procedural environment generation, intelligent traversal systems, and stack-based state management.


# Problem Statement

The environment is represented as an `N × N` two-dimensional grid where the agent always starts from the top-left corner `(0,0)` and attempts to reach a randomly generated goal position somewhere inside the map.

The challenge is that movement is not entirely controlled by the agent. Certain cells dynamically modify traversal behavior and can force the agent to move, rollback, or change traversal state.

Movement is possible in 8 directions:

```text
↖ ↑ ↗
← • →
↙ ↓ ↘
```

The environment contains three major cell types:

Normal cells allow standard traversal.

Vector cells contain directional force vectors that automatically move the agent in a specific direction for a specified number of steps immediately after entering the cell.

Tunnel cells behave as rollback traps. When the agent enters a tunnel, it is moved back to the third previously visited position using stack-based backtracking. If fewer than three previous positions exist, the agent is returned to the starting point.

The objective is to successfully reach the goal while handling all movement constraints and avoiding infinite traversal loops.



# Environment Generation

The entire environment is generated procedurally at runtime.

The goal position is randomly selected inside the grid while avoiding the starting node. A random number of tunnel cells are then inserted into the environment. After that, every valid cell has a `30%` probability of becoming a directional vector.

Each vector stores:

```text
Direction
Magnitude
```

Example:

```text
↗ × 3
```

This means the agent must move diagonally upward-right for three steps.

Each generated map behaves differently, creating a dynamic traversal environment every time the simulation runs.



# Solution Overview

The solution is based on randomized traversal combined with stack-based path management.

A custom stack implementation was developed manually using arrays instead of STL containers in order to satisfy the project constraints. The stack stores every visited position and allows the system to restore previous states whenever rollback mechanics are triggered by tunnels.

The navigation process continuously performs the following cycle:

```text
Start Exploration
        ↓
Choose Direction
        ↓
Validate Movement
        ↓
Evaluate Cell Type
        ↓
Apply Cell Mechanics
        ↓
Store Position in Stack
        ↓
Continue Until Goal Is Found
```

Whenever the agent enters a vector cell, forced movement is applied automatically according to the vector’s direction and magnitude.

Whenever a tunnel is encountered, the stack is used to pop previously visited positions and move the agent backward through its traversal history.

Visited cells are marked to prevent infinite loops and repeated exploration of the same states.

If all neighboring cells become exhausted and no further traversal is possible, the system concludes that no valid path exists.



# Visualization

The project uses SFML to visualize the generated environment and traversal state in real time.

Each cell is rendered according to its current behavior and state. Vector cells display both direction and magnitude, tunnel cells are marked with `T`, and the goal node is represented with `G`.

Visited cells are colored differently to visualize traversal history and exploration behavior.



# Technical Implementation

The project was implemented entirely in C++ using SFML for graphical rendering.

Core components include:

```text
Procedural grid generation
Custom stack implementation
Directional vector mechanics
Rollback tunnel mechanics
Traversal and exploration logic
Real-time visualization
```

The stack implementation is one of the central components of the system and is responsible for maintaining traversal history, supporting rollback operations, and reconstructing explored paths.



# Example Mechanics

Vector behavior:

```text
Agent enters vector cell
        ↓
Forced movement activates
        ↓
Agent moves automatically
        ↓
Landing cell is evaluated again
```

Tunnel behavior:

```text
Agent enters tunnel
        ↓
Previous positions popped from stack
        ↓
Agent moves backward
        ↓
Traversal resumes
```



# Compile and Run

Compile after each change:

```bash
g++ -o navigation all_in_one.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

Run:

```bash
./navigation
```

Then enter the grid size:

```text
10
```

Sample output:

```text
[0,0][1,0][2,1][3,2]...[8,7]...Goal!
```



# Applications

Although originally designed as an academic project, the concepts demonstrated in this repository are closely related to real-world topics such as robotic navigation, constrained pathfinding systems, intelligent agents, procedural simulations, game AI, and autonomous traversal systems.



# Future Improvements

Possible future extensions include implementing deterministic search algorithms such as DFS, BFS, or A*, adding weighted traversal costs, introducing obstacle systems, supporting multiple agents, and improving the visualization layer with analytics and heatmaps.
