import csv
import sys
import copy


def main():

    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DATABASE FILENAME")

    # Read DNA sequence into memory from file
    with open(sys.argv[2], "r") as file:
        dna = file.read()  # return file content as a str

    db = []  # DNA database

    # Read DNA database into memory from csv
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)  # read in as dict

        for row in reader:
            db.append(row)  # append row to list

    # Create missing persons profile
    john_doe = copy.deepcopy(db[0])  # grab template from db
    john_doe["name"] = 'unknown'  # set name to unknown

    doe_iterator = iter(john_doe)  # create iterable
    next(doe_iterator)  # skip first element in iterator

    # Analyze DNA sequence
    for i in doe_iterator:

        john_doe[i] = 0  # initialize STR count
        str_len = len(i)  # length of working STR

        base_count = 0  # number of bases
        tmp_count = 0  # tmp STR counter
        str_count = 0  # number of consecutive repeats of STR

        while base_count != len(dna):
            nucleotide = dna[base_count:base_count + str_len]  # get nucleotide

            if nucleotide == i:  # nucleotide matches STR
                tmp_count += 1
                base_count += str_len  # update base count to account for nucleotide (x bases)

                if tmp_count > str_count:  # update largest str count
                    str_count = tmp_count

            else:  # no match
                tmp_count = 0  # reset tmp count
                base_count += 1  # check next base

        john_doe[i] = str_count  # update final STR count

    # Look for matches in db
    match_list = copy.deepcopy(db)  # working copy of db

    doe_iterator = iter(john_doe)  # create iterable
    next(doe_iterator)  # skip first element in iterator

    for i in doe_iterator:
        tmp_list = []  # tmp list to store potential candidates

        for person in match_list:  # iterate over db
            if person[i] == str(john_doe[i]):  # matching STR counts
                tmp_list.append(person)  # add person to list

        match_list = tmp_list  # resulting db after filtering out non-matches

    if not match_list:  # list is empty
        print("No match")

    else:
        print(match_list[0]['name'])  # print name of match


if __name__ == "__main__":
    main()