import cs50
from sys import argv, exit

if len(argv) != 2:
    print("Usage: python roster.py [HOUSENAME]")
    sys.exit(1)

db = cs50.SQL("sqlite:///students.db")

roster_list = db.execute("SELECT first,middle,last,birth FROM students WHERE house = ? ORDER BY last ASC, first ASC", argv[1])

for person in roster_list:
    if person['middle'] != "":
        print(person['first'] + " " + person['middle'] + " " + person['last'] + ", born " + str(person['birth']))
    else:
        print(person['first'] + " " + person['last'] + ", born " + str(person['birth']))