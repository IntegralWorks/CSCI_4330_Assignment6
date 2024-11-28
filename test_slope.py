from random import randint
import os
from time import sleep

#uncomment to recompile just in case
# os.system('g++ -o slope slope.cpp')

print('-----------------------General Test-----------------------')
general_test_record = dict()
for i in range(0,3):
    test_data  = [f'{randint(-100, 100)}.{randint(1, 100_000)}' for i in range(4)]
    test_data += [randint(3, 10)]
    test_string = f'slope {test_data[0]} {test_data[1]} {test_data[2]} {test_data[3]} {test_data[4]}'
    print(f"Test String {i}:",test_string)
    os.system(f'slope {test_data[0]} {test_data[1]} {test_data[2]} {test_data[3]} {test_data[4]}')
    print('-----------------------')
    general_test_record[i] = test_data
print("Dumping general_test data:", general_test_record)
print('-----------------------End General Test-----------------------\n\n')


print('-----------------------DIV_BY_ZERO Test-----------------------')
test_data    = [f'{randint(-100, 100)}.{randint(1, 100_000)}' for i in range(4)]
test_data   += [randint(3, 10)]

test_data[0] = str(abs(float(test_data[0])))
test_data[2] = test_data[0]

test_string = f'slope {test_data[0]} {test_data[1]} {test_data[2]} {test_data[3]} {test_data[4]}'
print(f"Test String:",test_string)
os.system(f'slope {test_data[0]} {test_data[1]} {test_data[2]} {test_data[3]} {test_data[4]}')
print('-----------------------End DIV_BY_ZERO Test-----------------------\n\n')


print('-----------------------INFINITY_REACHED Test-----------------------')
DBL_MAX = 1.7976931348623157e+308
DBL_MIN = 2.2250738585072014e-308
case_1    = [DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, 16]
case_2    = [DBL_MIN, DBL_MIN, DBL_MIN, DBL_MIN, 16]

case_1_string = f'slope {case_1[0]} {case_1[1]} {case_1[2]} {case_1[3]} {case_1[4]}'
case_2_string = f'slope {case_2[0]} {case_2[1]} {case_2[2]} {case_2[3]} {case_2[4]}'

print(f"Test case_1:", case_1_string)
os.system(case_1_string)

print(f"Test case_2:", case_2_string)
os.system(case_2_string)

print('-----------------------End INFINITY_REACHED Test-----------------------\n\n')


print('-----------------------INVALID_COORD_INPUT Test-----------------------')

case_1    = [f'{randint(-100, 100)}', f'{randint(-100, 100)}', f'{randint(-100, 100)}', f'{randint(-100, 100)}', randint(3, 10)]
case_2    = [f'lol', f'i', f'so', f'random', randint(3, 10)]

case_1_string = f'slope {case_1[0]} {case_1[1]} {case_1[2]} {case_1[3]} {case_1[4]}'
case_2_string = f'slope {case_2[0]} {case_2[1]} {case_2[2]} {case_2[3]} {case_2[4]}'

print(f"Test case_1:", case_1_string)
os.system(case_1_string)
print(f"Test case_2:", case_2_string)
os.system(case_2_string)

print('-----------------------End INVALID_COORD_INPUT Test-----------------------\n\n')

print('-----------------------INVALID_ROUNDING_PLACE_INPUT Test-----------------------')
#note: case 2 should be a warning, not an error
cases = ['16', '-14', 'L0L']
for i in range(0,3):
    test_data  = [f'{randint(-100, 100)}.{randint(1, 100_000)}' for i in range(4)]
    test_data += [cases[i]]
    test_string = f'slope {test_data[0]} {test_data[1]} {test_data[2]} {test_data[3]} {test_data[4]}'
    print(f"Test String {i}:",test_string)
    os.system(f'slope {test_data[0]} {test_data[1]} {test_data[2]} {test_data[3]} {test_data[4]}')
    print('-----------------------')
    general_test_record[i] = test_data
print('-----------------------End INVALID_ROUNDING_PLACE_INPUT Test-----------------------\n\n')
