import time
import os

# 1
T1 = time.perf_counter()
os.system("./speller_bstree -d ../exp_data/tree/sorted_50k_dict -m 0 -vvv ../exp_data/tree/binary_50k_infile")
T2 = time.perf_counter()
print("Time spend for the 50k dict is " + '%s' % ((T2-T1)*1000), "ms")

# 2
T1 = time.perf_counter()
os.system("./speller_bstree -d ../exp_data/tree/sorted_70k_dict -m 0 -vvv ../exp_data/tree/binary_70k_infile")
T2 = time.perf_counter()
print("Time spend for the 70k dict is " + '%s' % ((T2-T1)*1000), "ms")

# 3
T1 = time.perf_counter()
os.system("./speller_bstree -d ../exp_data/tree/sorted_90k_dict -m 0 -vvv ../exp_data/tree/binary_90k_infile")
T2 = time.perf_counter()
print("Time spend for the 90k dict is " + '%s' % ((T2-T1)*1000), "ms")

# 4
T1 = time.perf_counter()
os.system("./speller_bstree -d ../exp_data/tree/sorted_110k_dict -m 0 -vvv ../exp_data/tree/binary_110k_infile")
T2 = time.perf_counter()
print("Time spend for the 110k dict is " + '%s' % ((T2-T1)*1000), "ms")

# 5
T1 = time.perf_counter()
os.system("./speller_bstree -d ../exp_data/tree/sorted_130k_dict -m 0 -vvv ../exp_data/tree/binary_130k_infile")
T2 = time.perf_counter()
print("Time spend for the 130k dict is " + '%s' % ((T2-T1)*1000), "ms")

# 6
T1 = time.perf_counter()
os.system("./speller_bstree -d ../exp_data/tree/sorted_150k_dict -m 0 -vvv ../exp_data/tree/binary_150k_infile")
T2 = time.perf_counter()
print("Time spend for the 150k dict is " + '%s' % ((T2-T1)*1000), "ms")