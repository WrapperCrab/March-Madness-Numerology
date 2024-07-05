# March Madness Numerology
## Get Every Game Wrong, but Have Fun Doing It

Every year for March Madness, I create a numerology algorithm based on the team names to create my bracket. 
Starting in 2024, I decided to program the algorithm on my computer rather than on paper as I had in previous years.

I plan on adding my future algorithms to this repo as well.

### How To Use
1. Download the files into a folder and open the folder in terminal.
2. Type `make run` to compile and run the program.
3. Follow the instructions given by the program and select the year of the algorithm you would like to use.

You may have to download gnu/make.\
I recommend first downloading chocolatey https://chocolatey.org/install 
then running `choco install make`\
Afterwards, try doing `make run` in the project folder again.

### About the Algorithms
#### 2024
This algorithm correctly predicted that Clemson would make it to the Elite 8.

For this algorithm, you type in two team names then it tells you which team it predicts to win.

To decide the winner, a score is calculated for each team based on the characters that appear in its name.
Each team name is first truncated to the length of the shorter name, then the score is calculated as follows: 
1. Some letters like 'b' are good and add to the score
2. Other letters like 'a' are bad and subtract from the score
3. 5 letters including 'f' are wild meaning it is random whether they add or subtract from score
4. One letter, 'q' is CRAZY meaning it instead affects a multiplier. It has a 50% chance to double the score
5. other characters are ignored

Finally, a random value between -6 and 6 times the length of the team name is added to the final score to make it possible for any team to beat any other 
even if they are burdened with bad letters.

This score is recalculated each time you enter this team's name, so it will change each time. 
This can represent how well this team will perform in this specific match.

A winning team is decided based on: (ties are broken by next list item)
1. Highest Score
2. Most crazy chars
3. Most wild chars
4. Most good chars
5. coin flip
