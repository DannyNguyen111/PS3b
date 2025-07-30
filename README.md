# PS3b
Sokoban


In this PS3B iteration, I redesigned the Sokoban game using a 2D grid of characters to represent tile states, such as walls ('#'), ground ('.'), storage ('a'), crates ('A'), player ('@'), and combinations like player or crate on storage ('2', '1'). Level data is loaded from text files and validated, with invalid tiles replaced by ground. I implemented full player movement logic with collision detection and crate pushing: the player can move into empty ground or storage tiles and push crates if the space beyond them is free, updating tile states accordingly. The isWon() function checks if any storage tiles are still uncovered by crates or player, indicating whether the puzzle is complete. Rendering uses SFML sprites stored in pairs (ground texture plus overlay) to visually layer tiles like crates and players over floors, matching each tile character. The game tracks the player’s position, supports resetting to the last loaded level, and provides grid printing for debugging. Overloaded stream operators facilitate easy file-based loading and saving of game states. This clean, character-based representation and robust logic provide a solid foundation for complete Sokoban gameplay.

<img width="638" height="676" alt="screenshot" src="https://github.com/user-attachments/assets/3a542978-bc4a-4143-aad4-63437c8b91c6" />
