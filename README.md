# March Madness Numerology
## Get Every Game Wrong, but Have Fun Doing It

Every year for March Madness, I create a numerology algorithm based on the team names to create my bracket. 
Starting in 2024, I decided to program the algorithm on my computer rather than on paper as I had in previous years.

I plan on adding my future algorithms to this repo as well.

## 2025
### Input
This script is written in Java and automates the process of inputting team names.
It takes a csv with the team names, seeds, and round numbers as input like this: (A header row is required)

The order of the teams is very important. This CSV stores all information about the tournament structure, so teams which face each other must be adjacent in the first round.
Basically, the order of the teams must match up with the starting bracket of the given tournament.

Round is an integer which represents which round of the tournament the team has their first game in. This allows you to implement brackets with 'byes', or in the case of March Madness, the First Four.

#### Example
If you have a bracket structure looking something like this with 5 teams A, B, C, D, E:

![example bracket rotated](https://github.com/user-attachments/assets/6602a69d-4e48-421b-8b61-2ca2e5fa0198)

Then, a valid CSV representing this tournament would be:
| Name              | Seed | Round |
| :---------------- | :------: | ----: |
| A        |   1   | 1 |
| B           |   1   | 1 |
| C        |   1   | 2 |
| D           |   1   | 2 |
| E        |   1   | 2 |

(All seeds are 1 since no seeds are specified in this theoretical tournament)


The Team CSVs for the 2025 men's and women's brackets (which including the First Four) exist in March-Madness-Numerology/2025. There, round 0 represents the First Four round and round 1 represents the round of 64.

### Algorithm
2025's algorithm has 2 steps.

First, it generates scores for each letter character based on the average seed of team that letter appears in.
This is done with a call to `BracketNumerology.generate_letter_scores({team csv path})`

Second, it simulates the tournament by assigning a score to each team based on the averge score of the letters that appear in its name.
This is done with a call to `BracketNumerology.simulate_tournament({team csv path})`

Individual games are simulated with `BracketNumerology.simulate_match({team name 0}, {team name 1})`. By default, the team with the higher score is always returned, 
but some options for adding randomness are commented out. The probability of a match result was expected to occur is printed out at this step, making "upsets" easy to spot

By changing `BracketNumerology.main()`, one can call these functions on other csv files and even score the letters with one csv then simulate the tournament with another

### How To Use
Really, you just have to run main with all the needed dependencies and referenced CSV's present. 
Open a Java project in your IDE of choice, resolve all errors and it should work


## 2024
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

### How To Use
1. Download the files into a folder and open the folder in terminal.
2. Type `make run` to compile and run the program.
3. Follow the instructions given by the program and select the year of the algorithm you would like to use.

You may have to download gnu/make.\
I recommend first downloading chocolatey https://chocolatey.org/install 
then running `choco install make`\
Afterwards, try doing `make run` in the project folder again.
