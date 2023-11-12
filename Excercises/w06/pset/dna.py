import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DATABASEFILE SEQUENCEFILE")
    # TODO: Read database file into a variable
    dfile = open(sys.argv[1])
    data_reader = csv.DictReader(dfile)
    # TODO: Read DNA sequence file into a variable
    sfile = open(sys.argv[2])
    seq = sfile.read()

    database = []
    for dline in data_reader:
        database.append(dline)
        # print(dline)

    # print(seq)
    # print (database)
    keys_list = list(database[0].keys())
    keys_list.pop(0)
    # print(keys_list)

    # TODO: Find longest match of each STR in DNA sequence
    longest_array = []
    for key in keys_list:
        longest_array.append(str(longest_match(seq, key)))

    dic = dict(zip(keys_list, longest_array))
    # print (dic)
    # TODO: Check database for matching profiles
    for person in database:
        # print(person)
        temp = person.copy()
        # print(temp)
        del temp["name"]
        # print(temp)
        if temp == dic:
            print(f"{person['name']}")
            return
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
