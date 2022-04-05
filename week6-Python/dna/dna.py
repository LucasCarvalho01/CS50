import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read database file into a variable
    database = []
    file = open(sys.argv[1], "r")
    reader = csv.DictReader(file)

    for info in reader:
        database.append(info)

    file.close()

    # Get the strings of the subsequences to check
    subs_file = open(sys.argv[1])
    subs_reader = csv.reader(subs_file)

    for row in subs_reader:
        subsequence = row
        break

    subs_file.close()

    # Read DNA sequence file into a variable
    dna_file = open(sys.argv[2])
    dna = dna_file.read()

    dna_file.close()

    # Find longest match of each STR in DNA sequence
    values = {}
    for i in range(1, len(subsequence)):
        aux = longest_match(dna, subsequence[i])
        values[subsequence[i]] = aux

    str = len(values)
    print(values)
    print(database)

    # # Check database for matching profiles
    # # for each person on database
    # for j in range(len(database)):
    #     # Compare each STR values found on DNA sequence with each on database
    #     for k in range(str):
    #         if database[j][k+1] != database[k]:
    #             break

    print(values[0])

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
    return str(longest_run)


main()
