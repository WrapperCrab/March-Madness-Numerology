import datetime
import random
import string


class Team:
    name = ""
    seed = 1
    def __init__(self, name, seed):
        self.name = name
        self.seed = seed

def main():
    # upsetCount = 0
    # testCount = 100000
    # for i in range(testCount):
    #     team1 = Team(''.join(random.choices(string.ascii_uppercase,k=10)), 2)
    #     team2 = Team(''.join(random.choices(string.ascii_uppercase,k=10)), 15)
    #     gameDate = datetime.date(2026, 3, 16)
    #     winningTeam = simulate_match(team1, team2, gameDate, True)
    #     if winningTeam == team2:
    #         upsetCount += 1
    # print("The upset ratio is about " + str(float(upsetCount)/float(testCount)))

    team1 = Team("Michigan", 1)
    team2 = Team("Harvard", 16)
    gameDate = datetime.date(2026, 3, 17)
    winningTeam = simulate_match(team1, team2, gameDate)


# Numerology Functions
def expression_number(name : str):
    # Calculates the digit core from the values of the characters in this name
    expressionNum = 0
    for char in name.upper():
        expressionNum += letter_value(char)
    expressionNum = reduce_to_core(expressionNum)
    return expressionNum
def letter_value(letter : str):
    match letter:
        case 'A' | 'J' | 'S':
            return 1
        case 'B' | 'K' | 'T':
            return 2
        case 'C' | 'L' | 'U':
            return 3
        case 'D' | 'M' | 'V':
            return 4
        case 'E' | 'N' | 'W':
            return 5
        case 'F' | 'O' | 'X':
            return 6
        case 'G' | 'P' | 'Y':
            return 7
        case 'H' | 'Q' | 'Z':
            return 8
        case 'I' | 'R':
            return 9
        case _:
            return 0
        
def life_path_number(date : datetime.date):
    # reduces the date to a 1-digit nonzero number by summing the digits
    # master numbers are not considered for compatibility
    (day, month, year) = (date.day, date.month, date.year)
    lifePathNum = reduce_to_core(day+month+year) # numerical core is closed under addition
    return lifePathNum

def reduce_to_core(num : int):
    # Reduces the number to a 1 digit core. Equivalent to modulo 9 except 0 is kept as 9
    core = num % 9 
    if core == 0:
        core = 9
    return core

    # # Check if the number has more than 1 digit
    # core = num
    # mustReduce = len(str(core)) > 1
    # while mustReduce:
    #     core = sum_digits(core)
    #     if len(str(core)) == 1:
    #         mustReduce = False
    # return core
# def sum_digits(num : int):
#     sum = 0
#     for char in str(num):
#         sum += int(char)

def compatibility(core1 : int, core2 : int):
    # inputs are assumed to be within 1 to 9
    return compatibility_map[core1-1][core2-1]
compatibility_map = [
    [3, -2, 2, -1, 2, -1, 1, 1, 1],# comp for 1
    [-2, 3, -1, 2, -1, 2, -2, 1, 1],
    [2, -1, 3, -2, 1, -1, 1, 1, 1],
    [-1, 2, -2, 3, -2, 1, 1, 2, 1],
    [2, -1, 1, -2, 3, -1, 2, -1, 1],
    [-1, 2, -1, 1, -1, 3, -1, 1, 1],
    [1, -2, 1, 1, 2, -1, 3, -1, 1],
    [1, 1, 1, 2, -1, 1, -1, 3, 2],
    [1, 1, 1, 1, 1, 1, 1, 2, 3], #comp for 9
]

# Simulation Functions

def simulate_match(team1 : Team, team2 : Team, gameDate : datetime.date, quietOutput=False):
    # Calculates the likely winner based on the compatibility of each team with the gameDate and their seeds
    expressionNum1 = expression_number(team1.name)
    expressionNum2 = expression_number(team2.name)
    
    lifePathNum = life_path_number(gameDate)
    
    compatibility1 = compatibility(expressionNum1, lifePathNum)
    compatibility2 = compatibility(expressionNum2, lifePathNum)

    performance1 = performance(compatibility1, team1.seed)
    performance2 = performance(compatibility2, team2.seed)

    if not quietOutput:
        print("")
        print(f"{"Info":<15}{str(team1.seed) + " " + team1.name:^30}{str(team2.seed) + " " + team2.name:^30}{str(gameDate):^10}")
        print(f"{"DigitCore":<15}{str(expressionNum1):^30}{str(expressionNum2):^30}{str(lifePathNum):^10}")
        print(f"{"Compatibility":<15}{str(compatibility1):^30}{str(compatibility2):^30}")
        print(f"{"Performance":<15}{str(performance1):^30}{str(performance2):^30}")

    # Best performance wins
    if performance1 > performance2:
        if not quietOutput:
            print(team1.name + " wins!")
            if team1.seed > team2.seed+8:
                print("Big upset!")
        return team1
    elif performance2 > performance1:
        if not quietOutput:
            print(team2.name + " wins!")
            if team2.seed > team1.seed+8:
                print("Big upset!")
        return team2

    # Tie: Best compatibility wins
    if not quietOutput:
        print("Performance Tie!")
    if compatibility1 > compatibility2:
        if not quietOutput:
            print(team1.name + " wins!")
            if team1.seed > team2.seed+8:
                print("Big upset!")
        return team1
    elif compatibility2 > compatibility1:
        if not quietOutput:
            print(team2.name + " wins!")
            if team2.seed > team1.seed+8:
                print("Big upset!")
        return team2

    # Evenly Matched: Random winner
    if not quietOutput:
        print("Compatibility Tie! Winner chosen randomly")
    number = random.randint(1, 2)
    if number == 1:
        if not quietOutput:
            print(team1.name + " wins!")
            if team1.seed > team2.seed+8:
                print("Big upset!")
        return team1
    else:
        if not quietOutput:
            print(team2.name + " wins!")
            if team2.seed > team1.seed+8:
                print("Big upset!")
        return team2

def performance(compatibility : int, seed : int):
    # Returns a value which represents a teams performance based on their skill (seed) and compatibility with the date
    return 8 + compatibility - seed_normalized(seed) # returns a value 0 to 10

def seed_normalized(seed : int):
    # Returns a digit representing a coarse graining of the skill of each seed
    if seed<2:
        return 1
    elif seed<4:
        return 2
    elif seed<8:
        return 3
    elif seed<12:
        return 4
    elif seed<16:
        return 5
    else:
        return 6

if __name__=='__main__':
    main()

