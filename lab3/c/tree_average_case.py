import time
import os

# 1
T1 = time.perf_counter()
os.system("./speller_bstree -d ../exp_data/hash/50k_dict -m 0 -vvv ../exp_data/hash/50k_infile")
T2 = time.perf_counter()
print("Time spend for the 50k dict is " + '%s' % ((T2-T1)*1000), "ms")

# 2
T1 = time.perf_counter()
os.system("./speller_bstree -d ../exp_data/hash/70k_dict -m 0 -vvv ../exp_data/hash/70k_infile")
T2 = time.perf_counter()
print("Time spend for the 70k dict is " + '%s' % ((T2-T1)*1000), "ms")

# 3
T1 = time.perf_counter()
os.system("./speller_bstree -d ../exp_data/hash/90k_dict -m 0 -vvv ../exp_data/hash/90k_infile")
T2 = time.perf_counter()
print("Time spend for the 90k dict is " + '%s' % ((T2-T1)*1000), "ms")

# 4
T1 = time.perf_counter()
os.system("./speller_bstree -d ../exp_data/hash/110k_dict -m 0 -vvv ../exp_data/hash/110k_infile")
T2 = time.perf_counter()
print("Time spend for the 110k dict is " + '%s' % ((T2-T1)*1000), "ms")

# 5
T1 = time.perf_counter()
os.system("./speller_bstree -d ../exp_data/hash/130k_dict -m 0 -vvv ../exp_data/hash/130k_infile")
T2 = time.perf_counter()
print("Time spend for the 130k dict is " + '%s' % ((T2-T1)*1000), "ms")

# 6
T1 = time.perf_counter()
os.system("./speller_bstree -d ../exp_data/hash/150k_dict -m 0 -vvv ../exp_data/hash/150k_infile")
T2 = time.perf_counter()
print("Time spend for the 150k dict is " + '%s' % ((T2-T1)*1000), "ms")