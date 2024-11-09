# otello
Board game Otello implemented in C

Reversi, also known as Othello, is a strategic board game for two players. The objective is to have the largest number of pieces of your color at the end of the game. Each player takes the role of Black (N) or White (B), and the game is played on an 8x8 square board.


At the start, two pieces of each color are placed in the center of the board forming a square where the N and B pieces will be crossed. On their turn, each player places a piece on an empty square so that it captures at least one of the opponent's pieces. Captured pieces are those that are between the newly placed piece and another of the same color, aligned in a straight line (vertically, horizontally or diagonally). When capturing, the opponent's pieces are flipped over to change them to the current player's color.


If a player has no valid moves, they may choose to pass their turn, although the game ends when neither player can make a move or when they decide to end the game early. The player with the most pieces at the end is the winner.
