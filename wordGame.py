import random
import csv
import os

# CUT NAMES

# Jerrys hangman style word game code
# psuedocode at bottom of page
# leaderboard file is "leaderboard.csv" -> name,score

# list of word and their keys, feel free to add more or delete some,
# the code will run fine
selection = {
    "color": ["red", "blue", "green", "purple", "turquoise", "black", "white", "yellow", "cyan", "orange", "magenta", "brown", "gray"],
    "animals": ["cat", "fish", "horse", "rabbit", "cheetah", "lion", "tiger", "monkey", "mouse", "cow", "snake", "horse", "sheep", "chicken"],
    "numbers": ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen" "sixteen"],
    "cars brands": ["kia", "ford", "honda", "toyota", "ferrari", "mazda", "lexus", "hyundai", "tesla", "porche", "volkswagen", "audi", "mercedes"]
}


def main():
    # detect if there is a leaderboard file, if not, create one
    Isexist = os.path.exists("leaderboard.csv")
    if Isexist == False:
        filename = "leaderboard.csv"
        with open(filename, "a") as csvfile:
            csvwriter = csv.writer(csvfile)
            fields = ["name", "score"]  # record name and score
            csvwriter.writerow(fields)

    exit = 0
    # print intro
    print("Welcome to Jerry's word game! Enter one of the numbers to continue")

    # menu, the user and pick what option they want by entering a number
    # the code will only terminate if they select 4
    while exit != 4:
        print(
            """
        1. Instructions
        2. Play game
        3. Leaderboard
        4. Exit"""
        )

        # ask user for a number, and make sure it is a number
        select = input("Please enter number: ")
        while select.isnumeric() == False or int(select) > 4 or int(select) < 1:
            select = input("Please enter a valid NUMBER: ")
        select = int(select)

        # execute appropriate code depending on what user select
        if select == 1:
            print_information()
        elif select == 2:
            score = play_game()
            if score > 0:  # if the user wins, ask them to store their info
                record_score(score)
        elif select == 3:
            leaderboard()
        elif select == 4:
            # exit
            print("Thank you for playing! :D")
            exit = 4
    # add option to return to menu


def print_information():  # print explanation codes
    print(
        """
          How to play
          For this game. You can choose a category of words. Then you will see a some blanks.
          This signifies how many characters are there. The program will ask you to enter ONE character
          If character is correct, it will display the character on the appropriete location in the word
          If the letter is incorrect, you loose some points. You will have (length of word-1) number of guesses
          If the input is invalid, the program will ask you to try again.
          Invalid and correct answer doesn't count to your guesses.

          How the game is scored
          (length of answer- wrong guesses)/length of answer)*100 + length of answer

          Enjoy!
        """,
        end="",
    )


def play_game():  # display guesses
    print("Game on! What genre of words do you want? ")

    # define what categories are there
    categories = list(selection.keys())

    # this counter counts how many types of genre are there
    counter = 0

    # tell user what genres are availble + random genre
    print("Here are the genres: ")
    for x in range(len(categories)):
        print((x + 1), categories[x])
        counter = x
    print((counter + 2), "random selection")

    pick = input("Pls enter number: ")
    while pick.isnumeric() == False or int(pick) > (counter + 2) or int(pick) < 1:
        pick = input("Pls enter a valid NUMBER: ")

    # select answer based on user input
    if int(pick) == (counter + 2):
        answer = random.choice(selection.get(random.choice(categories)))
    else:
        answer = random.choice(selection.get(categories[int(pick) - 1]))

    # print empty slots
    for x in range(len(answer)):
        print("_ ", end="")
    print()
    guess = 0  # how many wrong guesses
    guesslist = ""  # a collection of the user's character inputs
    emptyslot = 1  # how many character does the user still need to guess

    # while loop ends when user wins or loses
    while guess != len(answer) - 1 and emptyslot != 0:
        emptyslot = 0
        # prompt for a character, check if it is valid
        respond = input("Enter a character: ")
        while respond.isalpha() == False or len(respond) > 1:
            respond = input("Your response was invalid, please enter a CHARACTER: ")

        # add input to guesslist
        guesslist += respond

        # we are going to check if user got it right
        guessed_right = False
        # if we find a correct guess, print the letter instead of underdash
        for elem in answer:
            if respond == elem:
                guessed_right = True
            found = False
            for x in guesslist:
                if x == elem:  # the user guessed this character
                    print(x, end=" ")
                    found = True
                    break
            if found == False:  # the user did not guess this character
                print("_ ", end="")
                emptyslot += 1
        print()
        if guessed_right == False:  # if user guessed wrong, add 1 to guess
            guess += 1

    # reminder that the while loop above will only terminate if user loses or wins
    if guess == len(answer) - 1:  # user lost
        print("You lost!")
        print("the answer was:", answer)
        return 0  # no points given
    else:  # user won
        score = round((len(answer) - guess) / len(answer) * 100) + len(answer)
        print("YOU WON! Your score is ", score)
        return score  # this is used for recording into leaderboard


def record_score(score):  # writes to a csv file the username and score
    print()
    name = input("What is your name: ")
    while len(name) > 10 or len(name) < 1:
        name = input("Please enter a 10 letter name: ")

    filename = "leaderboard.csv"
    with open(
        filename, "a"
    ) as csvfile:  # open as an "A"ppend format. BTW there is also "R"ead and "W"rite
        csvwriter = csv.writer(csvfile)
        fields = [name, score]  # record name and score
        csvwriter.writerow(fields)
    print("SCORE RECORDED")


def leaderboard():  # prints the leaderboard in descending order
    print("LEADERBOARD")
    print("NAME SCORE")
    print()
    topname = []  # a collection of names on the leaderboard
    topscore = []  # a collection of scores on the leaderbaord

    # open file
    filename = "leaderboard.csv"
    with open(filename) as f:  # vaiable f is the file
        reader = csv.DictReader(f)  # comma seperated fie
        for guy in reader:
            topname.append(guy["name"])
            topscore.append(int(guy["score"]))

    # bubble sort
    counter = 1
    while counter != 0:
        counter = 0
        for i in range(len(topscore) - 1):
            if topscore[i] < topscore[i + 1]:
                # swaps number and name too
                numswap = topscore[i + 1]
                topscore[i + 1] = topscore[i]
                topscore[i] = numswap

                nameswap = topname[i + 1]
                topname[i + 1] = topname[i]
                topname[i] = nameswap
                counter += 1
    # print top 5 players

    if (len(topscore)) == 0:
        print("NO PLAYERS RECORDED")
    elif (len(topscore)) < 10 and (len(topscore)) != 0:
        for i in range(len(topscore)):
            print((i + 1), topname[i], end="")
            for x in range(11 - len(topname[i])):
                print(" ", end="")
            print(topscore[i])
    else:
        for i in range(10):
            print((i + 1), topname[i], end="")
            for x in range(11 - len(topname[i])):
                print(" ", end="")
            print(topscore[i])


if __name__ == "__main__":
    main()


"""
WORDGAME PSUEDOCODE

main:
      print option
      pick = inpiut(blah)

need a function to prompt user if they want to restart<-EZ

1: INTRO:
Print(a bunch of words explaining the code)

2: Play
pick random word from list (CSV?). Give hint
have word as string
len(word) -1 = amount of guesses user have
create a string with all underdashes "_ _ _ _ _"
prompt user for a character
display the letter if guessed correcly
"_ _ L L _"
if not
"Wrong!"

score calculation
len(word)*10 - 10(number of times user got it wrong)
if score == 0:
      game over

3. Leaderboard
Use a similar code useed in world cup, print leaderboard as a list

4. Exit
Exit do while loop

"""
