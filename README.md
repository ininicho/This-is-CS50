# This-is-CS50
This is a compilation of all CS50 problem sets that I made. It is not perfect. Therefore, feel free to check it out and improve them.

CS50 is an open coursware made by Harvard University. It is an 8 week online course and I will be posting my answers of weekly problem sets along with my experience of learning. 

https://cs50.harvard.edu/x/2020/

WEEK 1: C

Week 1 was a firehose for me. I had no prior programming experience (except for crappy computer classes in school). There were 2 pairs of problem sets. The first pair of problems is called Mario. In Mario, we have to create a program in C that prints out blocks like in the actual game. The program asks for the height input and prints the blocks accordingly. The less difficult Mario prints out an easier layout of blocks. At first, it was trial and error. But after understanding the concepts of for loops, hard Mario was a breeze. 

The latter pair is Cash and Credit. In Cash, the funciton of the program is to return the minimal number of coins needed for change. The user inputs the change and the number of coins will be printed out. Learned about modulus and floor division in C which was really helpful in writing the program. Credit was hell, period. I solved credit after finishing Week 2 problem sets. The goal is to create a function that checks the validity of a credit card using Luhn's Algorithm. The algorithm multiplies the first number and two numbers after it and adds the numbers of the multiplication. Then, add it with the numbers which wasn't multiplied. If it returns a multiple of 10, the card is valid. However, some types of cards have their own characteristcs (ex. VISA cards start with 4, MASTERCARD cards are 16 numbers in length). However, I managed to solve it.

WEEK 2: ARRAYS

Week 2 was rather a breeze for me. I am more familiarized with the C language. Started learning about arrays and command line arguments in C. There are 3 problem sets in Week 2. The first problem is Readability. The goal is to create a program that could determine the reading level of a text that the user inputs in the command line. By using for loops and if statements, I successfully made the program. 

The next problem is Caesar. In this problem, we have to write a program that encrypts a sentence according to the users input in the command line. The number that the user inputs will be added each word and encrypts the sentence. However, the output must be case sensistive meaning that if the input is in capital, so is the output in capital. From this program, I learned about dividing problems into cases. First case is if the input is in lowercase and the other in uppercase. The last problem is substitution. It is much harder since the encryption is based on a 26-letter series that the user inputs. Every word on the sentence is to be replaced by the n-th number from the series (ex. the letter E will be replaced by the fifth word in the series). In this program, more cases occur hence it gets more complicated.

WEEK 3: ALGORITHMS

In week 3, we learn about different types of searching algorithms and the big O notation. Process speed and memory are the main problems in creating algorithms. The faster the process speed, the more memory it needs. Hence, there needs to be some consideration when writing the program. There are 3 problems in this week. The first is called Plurality where we write a program that runs an election. The winner is according to the most numbers of votes the candidate got. It was an easy problem. 

However, the next problem, Runoff, was quite hard. The election is based on the voters ranking. In this system of election, if a candidate haven't won by half the voters, an algorithm will check the least voted candidate and eliminate them. Then, the next ranked candidate will be counted as their choice. Understanding the way it works is quite hard. However, I managed to write the program. The last problem, hardest ever, is Tideman. In Tideman, the election is based on locking pairs of candidates. The difference of every pair of candidate in the election will be checked and then sorted. After sorting the pairs, the program will start locking pairs starting with the greatest difference to find out the winner of the election. However, the program must not tolerate a situation where the pairs locked form a loop, causing no one to win the election. This was my problem in writing the program. I still haven't solved it yet :(

WEEK 4: MEMORY

This week was even harder. Week 4 discusses about memory allocation in programs. Functions such as malloc and free enables to create a dynamic memory in the program. It was an even greater fire hose than week 1 for me since the training wheels of are taken off (no more cs50 library). We also learned about pointers and turns out strings are just an array of characters that start from an appointed memory. The problem sets for this week includes filter and recovery.

In filter, there are two options where one is easier than the other. However, I did both to get the most of this course. In this problem, we are asked to create a function in an existing file to manipulate pixels on the bitmap file. In order to create a grayscale filter, we average the red, green and blue values to create a grey shade on all the pixels. In creating sepia, there is an algorithm that changes the value of each pixel so that it creates a film effect. In blur, we average a 3x3 grid pixel values in order to get the value of the middle pixel. It was quite hard for me since I stumbled in writing the for loop function. Minor mistakes tend to create an avalanche. The last filter is edge finding. In order to find edges on a picture, we use the Sobel operator which pretty much is a matrix that is multiplied a 3x3 grid in order to find the values of the middle pixel. 

The last problem is recover and I made one of the one of the dumbest mistake. In recover, we are given an sd card which previously stores several jpg files. Then, we write a program that iterates through every data in the sd card to find traces of a jpg file. Jpg files have a uniform starting byte and they are stored next to each other. My mistake in writing this program is that I did not iterate the following bytes following the starter byte of a jpg. Hence, I only have small bits of a jpg. Turns out, the data that I take for every iteration is only 512 bytes and the bytes following the starter bytes of a jpg are part of the file. It took me a lot of researching to get this program.

WEEK 5: DATA STRUCTURES

