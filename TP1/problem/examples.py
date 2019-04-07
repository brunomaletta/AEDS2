import random

total_examples = 2000

def generate_example():
    max_amount = 20
    operations = ['A', 'R', 'D']
    ids = set(range(1, max_amount + 1))
    command = ""
    added = set()

    while len(ids) > 0:
        op = random.sample(operations, 1)[0]

        if op == 'A':
            id = random.sample(ids, 1)[0]
            ids -= set([id])
            command += "A{}".format(id)
            added.add(id)
        elif op == 'D':
            if len(added) == 0:
                continue
            id = random.sample(added, 1)[0]
            added -= set([id])
            command += "D{}".format(id)
        else:
            if len(added) == 0:
                continue
            id = random.sample(added, 1)[0]
            an = random.sample(ids, 1)[0]
            ids -= set([an])
            command += "R{},{}".format(id, an)
            added.add(an)
    return command


for i in range(total_examples):
    print(generate_example())
