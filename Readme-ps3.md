# PS3: Sokoban

## Contact
Name:Danny Nguyen
Section: 011
Time to Complete: 
6 hours
## Description
Explain what the project does.
The goal of this project was to finish up the previous project by adding the game logic for Sokoban. I focused on handling player movement and interactions in response to certain key inputs, such as pushing crates and detecting valid or invalid moves. 
### Features
Describe what your major decisions were and why you did things that way.

#### Part a
I used an enum class for the tile types to make the code clearer and easier to manage. This way, each tile type like Wall, Crate, Storage, and Player has a specific value, making the code more readable. Enums also lets me easily check if a tile has certain properties, such as being both a crate and storage.
#### Part b
I originally used an enum class, but it caused issues with the autograder and made debugging harder. So I redid the project using a character-based tile grid, which aligned better with level files and simplified movement logic and rendering. This approach also made it easier to visually debug and match behavior with the expected test cases.

### Memory
Describe how you decided to store the level data including whether you used smart pointers.
I stored the level data as a 2D vector of characters (std::vector<std::vector<char>>) to represent the game grid, where each character encodes a tile type.
I did not use smart pointers.
### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.
I used the std::find function to check for valid tile symbols during level loading. I also wrote a lambda expression inside the movePlayer function to apply directional movement to coordinates.
### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

### Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban
