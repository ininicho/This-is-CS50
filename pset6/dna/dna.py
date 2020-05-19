import csv, sys

database = [] # [name, STRs], [a, STRs], [b, STRs], ...
check = []

# Checks number of command line argument
if len(sys.argv) != 3:
    print("Usage: python data.csv sequence.txt ")
    sys.exit(1)

# Opens database csv and adds to list in program
with open(sys.argv[1], 'r', newline = '') as datafile:
    dataread = csv.reader(datafile)
    for row in dataread:
        database.append(row)

    # Opens sequence file and assign sequence to a variable
    sequencefile  = open(sys.argv[2], 'r', newline = '')
    sequence = sequencefile.read()

    seq = len(sequence) # Sequence number

# Counts number of STRs in sequence
for i in range(1, len(database[1])):
    string = database[0][i]
    n = len(string)
    countermax = 0 # Set max counter to 0

    for j in range(0, seq - n - 1):
        counter = 0 # Resets counter to 0 everytime cursor move
        n = len(string)
        if  string == sequence[j:j + n]: # Checks if STR sequence occur on the next few words
            counter += 1
            n1 = len(string)
            n = n + len(string)

            while (string == sequence[j + n1:j + n]): # Checks if STR sequence still occurs after previous occurence
                counter += 1
                n = n + len(string)
                n1 = n1 + len(string)

            if counter > countermax: # Changes max counter
                countermax = counter

    check.append(countermax) # Appends max counter to a list for checking

# Checks to database
for i in range(0, len(database) - 1):
    match = 0 # Number of matches between sequence and database
    for j in range(0, len(database[0]) - 1):
        if check[j] == int(database[i + 1][j + 1]): # Checks the database for similar STR occurence
            match += 1
    if match == len(database[0]) - 1: # Prints the name if number of matches equal the number of all STR occurence
        print(database[i + 1][0])
        sys.exit(0)

print("No match") # Prints "No match" if no one has the same number of STR occurence
sys.exit(1)