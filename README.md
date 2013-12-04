Vise
================

Build a game that uses a 2D game board, and graph algorithms.

Background info
---------------
When designing a simple 2D board game, you have a major design decision to make: How should your represent the board? There are some obvious possibilities:

1. A 2-D array, one row per row of the board, using math to calculate neighbors
2. A 1-D array, using row-major order, using math to calculate neighbors
3. A graph structure made of node objects, each node object having 6 edges (up, upleft, upright, down, downleft, downright)
4. An adjacency list
5. An adjacency matrix

Your goal will be to complete the implementation of the game. If time allows, you should enhance the game by improving the graphics, adding animation, adding sound, or whatever other features you think would make the game more fun to play.

In fact, you may alter the rules of the game, if you like, to make it more fun. In that case please write up a description of your alternate rules. Be sure to include screenshots in your rules explanations.

Goals/requirements
------------------
There are a few main pieces of functionality you will need to consider when selecting your data structure.

1. Given a particular (x,y) coordinate, in board space, how will you find the appropriate item in your data structure?
2. How easy will it be to implement checkNbrs()?
3. How easy will it be to implement isConnected()?
4. How will you handle wrap-around? If the pieces go off the right side of the board, it should wrap around to the left. The top should wrap around to the bototm. *Note that my demos don't do this correctly!*
5. How will you do the "find the largest connected component" step in doVise()?

Questions
=========

#### 1. Which type of data structure did you choose? Explain, in English, the main ideas behind your data structure.

We chose to implement a 2D Vector with Neighbor pointers. The reason why we chose to utilize a vector-based gameboard containing "GameNodes" was to allow for constant time access of any area on the board, and allow for changes within the logic behind the scenes as the development went along. Utilizing a "GameNode" based gameboard allowed for new variables to be created or changed to aid in conceptualizing and implementing various algorithms. Each "GameNode" contains 6 neighbor pointers, corresponding to each boarding piece. The pointers are determined when the board is created, and are used to determine which pieces are neighboring each other piece. This way, we cut down on the amount of complicated math and only have to think about the computation once during initialization, rather than across the entire project. Furthermore, the pointers are used to help conceptualize the more complicated algorithms, such as Dijkstra's Algorithm, and any graph traversal when checking for the pieces to be contiguous. Much of our choice was influenced by what we thought would be easier to code, as the relatively small total number of pieces meant that a less than an extremely efficient algorithm would still take a reasonable amount of time. Utilizing a combination of Neighbor Pointers, Node Objects, and a 2-D Vector, we felt that we had the best of all of the worlds, as we could use different methods to implement algorithms in different ways.


Portfolio Video
=========

Explain your code, as you would to a boss or colleague in the workplace. You will most likely want to use a screen-capture software. You should, at minimum, do the following:

1. Show your program running.
2. Show your code, briefly explaining what it is meant to do. You do NOT need to explain any of the provided code, unless you made some meaningful change you want to describe.
3. If something is not working (or if you aren't sure), explain that part carefully.
4. Show some gameplay between two players.

The video should certainly be less than 2 minutes long. I (or the grading assistant) ought to be able to grade your program based solely on your video, so be sure that we can see your code style, and can accurately assess what works, or doesn't work, in your program. The "Questions" above might also be things you want to talk about in your video: The video should be able to be understood even by someone that isn't in the class, and hasn't read your question answers.

#### 1. Give the link to your portfolio video on YouTube.

TODO