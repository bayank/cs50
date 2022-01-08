import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) < 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    db_path = sys.argv[1]
    seq_path = sys.argv[2]

    # TODO: Read database file into a variable
    with open(sys.argv[2]) as DB:
        DBReader = csv.reader(DB)
        for row in DBReader:
            DBlist = row
    DNA = DBlist[0]
    sequence = {}

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[1]) as peoplelist:
        person = csv.reader(peoplelist)
        for row in person:
            DNASequence = row
            DNASequence.pop(0)
            break

    # TODO: Find longest match of each STR in DNA sequence
    for x in DNASequence:
        sequence[x] = 1

    # if the pattern of sequence dicti found, count
    for pattern in sequence:
        l = len(pattern)
        Max = 0
        count = 0
        for i in range(len(DNA)):
            while count > 0:
                count -= 1
                continue
        # if seg match  the pattern && ir repeats, count
            if DNA[i: i + l] == pattern:
                while DNA[i - l: i] == DNA[i: i + l]:
                    count += 1
                    i += l
        # if previous longest sequence and if it is longer, then set the new max
                if count > Max:
                    Max = count
        sequence[pattern] += Max

    # TODO: Check database for matching profiles
    with open(sys.argv[1], newline='') as peoplelist:
        person = csv.DictReader(peoplelist)
        for person in person:
            match = 0
        # check sequence against every person and print the name, then exit
            for DNA in sequence:
                if sequence[DNA] == int(person[DNA]):
                    match += 1
            if match == len(sequence):
                print(person['name'])
                exit()
    # else no match
    print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
