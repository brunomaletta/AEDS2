output = "./output.txt"
answers = "./answers.txt"

correct_count = 0
wrong_count = 0

with open(output, "r") as o:
    with open(answers, "r") as a:
        for l, (correct, trial) in enumerate(zip(a, o)):
            if correct.strip().split(' ') == trial.strip().split(' '):
                correct_count += 1
            else:
                wrong_count += 1
                print("Line {} incorrect. {} != {}".format(
                    l, correct.strip(), trial.strip()))

print("{} trials correct".format(correct_count))
print("{} trials wrong".format(wrong_count))
