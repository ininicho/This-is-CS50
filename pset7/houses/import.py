import csv
import cs50
from sys import argv, exit

names = []
houses = []
births = []

# Checks if command line argument given
if len(argv) != 2:
    print("Usage: python import.py [FILENAME].csv")
    sys.exit(1)

# Opens filename in command line argument
with open(argv[1], 'r') as file:
    reader = csv.DictReader(file)
    # Add items in csv to lists
    for row in reader:
        names.append(row["name"])
        houses.append(row["house"])
        births.append(int(row["birth"]))

names_fml = []

# Create list of separated names
for name in names:
    temp = name
    name_fml = []
    temp_list = []

    # Separate names
    for i in range(len(temp)):
        if temp[i] != " ":
            temp_list.append(temp[i])

        if temp[i] == " ":
            name_fml.append("".join(temp_list))
            temp_list.clear()

    name_fml.append("".join(temp_list))

    # Condition if no middle name
    if len(name_fml) == 2:
        names_fml.append([name_fml[0], "", name_fml[1]])
    else:
        names_fml.append(name_fml)

# Open SQL Database
db = cs50.SQL("sqlite:///students.db")

# Input lists into table in database
for i in range(len(names)):
    db.execute("INSERT INTO students (id,first, middle, last, house, birth) VALUES(?,?,?,?,?,?)", i, names_fml[i][0], names_fml[i][1], names_fml[i][2], houses[i], births[i])