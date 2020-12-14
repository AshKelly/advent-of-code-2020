import numpy as np

preamble = 1000
total_nums = 50_000
bad_num = 18599
numbers = np.zeros(total_nums, dtype="int64")

start = np.arange(1, preamble+1)
np.random.shuffle(start)
numbers[:preamble] = start[:preamble]

for i in range(preamble, numbers.shape[0], 1):
    if i >= bad_num:
        if i == bad_num:
            numbers[i] = np.sum(numbers[i-200:i-100])
        else:
            numbers[i] = np.random.randint(1,2)
    else:
        inds = np.random.randint(2, preamble-2, 2)
        while inds[0] == inds[1]:
            inds = np.random.randint(2, preamble-2, 2)
        numbers[i] = numbers[i - inds[0]] + numbers[i - inds[1]]


with open("input", "w") as f:
    for num in numbers:
        f.write("{0}\n".format(num))
