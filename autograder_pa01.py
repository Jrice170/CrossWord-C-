#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Feb 25 01:02:31 2018

@author: taylor@mst.edu
"""

import os
import csv
import subprocess
import pandas as pd
import shutil
import numpy as np
import sys
import time
from glob import glob


# %%
def unit_tests(username, student_folder):
    print('\t Testing unit_tests')
    # Catch does not recover from a segfault on a given test...

    # -iquote checks following dir second for cpps in cwd,
    # so you must have this cpp in subdir without same h file.
    result_array = [username]
    compile_test = subprocess.run(['g++',
                                   'catch_tests/catch_main.cpp',
                                   'catch_tests/test_catch.cpp',
                                   student_folder + 'matrix_search.cpp',
                                   '-std=c++11',
                                   '-iquote',
                                   student_folder],
                                  stdout=subprocess.PIPE,
                                  stderr=subprocess.PIPE)
    if compile_test.returncode:
        #print(compile_test.stderr.decode())
        result_array.append('no compile on test')
        result_array.append('no compile on test')
    else:
        try:
            with open('catch_tests/test_input.txt', 'rb', 0) as input_file:
                with open(student_folder + 'unit_results.txt', 'wb', 0) as output_file:
                    unit_test = subprocess.run(['./a.out', '-s'],
                                               timeout=5,
                                               stdin=input_file,
                                               stdout=output_file,
                                               stderr=subprocess.PIPE)

            with open('catch_tests/test_input.txt', 'rb', 0) as input_file:
                unit_test = subprocess.run(['./a.out'],
                                           timeout=5,
                                           stdin=input_file,
                                           stdout=subprocess.PIPE,
                                           stderr=subprocess.PIPE)

            #print(unit_test.stdout.decode())
            for line in unit_test.stdout.decode().split('\n'):
                if "assertions:" in line:
                    options = line.split('|')
                    total = int(options[0].strip().split(' ')[-1])
                    total = total - int(options[-1].strip().split(' ')[0])
                    result_array.append(total)
                    result_array.append(line)
                    return result_array

            result_array.append('56')
            for line in unit_test.stdout.decode().split('\n'):
                if "All tests passed" in line:
                    result_array.append(line)

        except Exception as e:
            result_array.append(e)
            result_array.append(e)

    return result_array


def main_diff(student_folder):
    print('\t Testing main_diff')

    # -iquote checks following dir second for cpps in cwd,
    # so you must have this cpp in subdir without same h file.
    compile_test = subprocess.run(['g++',
                                   student_folder + 'pa01.cpp',
                                   student_folder + 'matrix_search.cpp',
                                   '-iquote',
                                   student_folder],
                                  stdout=subprocess.PIPE,
                                  stderr=subprocess.PIPE)

    if compile_test.returncode:
        #print(compile_test.stderr.decode())
        return 'no compile for main'
    else:
        try:
            with open('solution/grade_input.txt', 'rb', 0) as input_file:
                with open(student_folder + 'your_output.txt', 'wb', 0) as output_file:
                    subprocess.run('./a.out',
                                   timeout=5,
                                   stdin=input_file,
                                   stdout=output_file,
                                   stderr=subprocess.PIPE)

            diff_output = subprocess.run(['diff',
                                          student_folder + 'your_output.txt',
                                          'solution/grade_output.txt'],
                                         timeout=5,
                                         stdout=subprocess.PIPE,
                                         stderr=subprocess.PIPE)
            #print(diff_output.stdout.decode())

            with open(student_folder + 'your_diff_from_correct.txt', 'w') as output_file:
                output_file.write(diff_output.stdout.decode())

            return len(diff_output.stdout.decode())

        except Exception as e:
            return e


def get_mem_leaks():
    print('\t Testing mem_leaks')

    # -iquote checks following dir second for cpps in cwd,
    # so you must have this cpp in subdir without same h file.
    compile_test = subprocess.run(['g++',
                                   'mem_test/mem_test.cpp',
                                   student_folder + 'matrix_search.cpp',
                                   '-std=c++11',
                                   '-iquote',
                                   student_folder],
                                  stdout=subprocess.PIPE,
                                  stderr=subprocess.PIPE)
    if compile_test.returncode:
        #print(compile_test.stderr.decode())
        return 'no compile on test'
    else:
        try:
            with open('catch_tests/test_input.txt', 'rb', 0) as input_file:
                valgrind_test = subprocess.run(['valgrind',
                                                './a.out'],
                                               timeout=25,
                                               stdin=input_file,
                                               stdout=subprocess.PIPE,
                                               stderr=subprocess.PIPE)

            for line in valgrind_test.stderr.decode().split('\n'):
                if "definitely lost" in line:
                    options = line.split(':')
                    option = options[1].strip().split(' ')
                    return option[0]
            return '0'

        except Exception as e:
            return e


def time_tests(student_folder):
    print('\t Testing time')

    compile_test = subprocess.run(['g++',
                                   student_folder + 'pa01.cpp',
                                   student_folder + 'matrix_search.cpp',
                                   '-iquote',
                                   student_folder],
                                  stdout=subprocess.PIPE,
                                  stderr=subprocess.PIPE)

    if compile_test.returncode:
        #print(compile_test.stderr.decode())
        return 'no compile on test'
    else:
        try:
            time_array = []
            for run in range(200):
                t0 = time.perf_counter()

                with open('solution/grade_input.txt', 'rb', 0) as input_file:
                    run_test = subprocess.run('./a.out',
                                              timeout=20,
                                              stdin=input_file,
                                              stdout=subprocess.PIPE,
                                              stderr=subprocess.PIPE)

                time_array.append(time.perf_counter() - t0)

            return np.mean(time_array)

        except Exception as e:
            return e


def store_student_data(result_array, folder):
    print('\t Writing student data')
    with open("{}results.csv".format(folder), "w") as f:
        w = csv.writer(f)
        w.writerows(result_array)


def name_test(username, student_folder):
    print('\t Name test')
    compile_test = subprocess.run(['g++',
                                   'name_test/00name_test.cpp',
                                   student_folder + 'matrix_search.cpp',
                                   '-std=c++11',
                                   '-iquote',
                                   student_folder],
                                  stdout=subprocess.PIPE,
                                  stderr=subprocess.PIPE)
    if compile_test.returncode:
        #print(compile_test.stderr.decode())
        return 'no compile on test'
    else:
        try:
            username_test = subprocess.run(['./a.out'],
                                           timeout=5,
                                           stdout=subprocess.PIPE,
                                           stderr=subprocess.PIPE)

            if username_test.stdout.decode().split()[0] == username:
                return '0'
            else:
                return '1'

        except Exception as e:
            return e

# %%
# This helps when everyone has a different directory
# First argument is path relative to where you execute this script, e.g.,
# python3 grader.py ../../student_submissions/pa03
if(1 < len(sys.argv)):
    parent_dir_of_student_repos = sys.argv[1]
else:
    # Or, make the students directory the relative path to cwd
    parent_dir_of_student_repos = '../student_submissions/pa01'

students_to_try = os.listdir(parent_dir_of_student_repos)

# For debugging a single or couple students, uncomment this line:
#students_to_try = ['solution']

headers = ['Username (not for points)'] + ['Tests passed (out of 56)'] + ['Tests passed'] + ['Bytes definitely lost (memory leak) (0 is perfect)'] + ['Username accurate (0 good, 1 bad)'] + ['Main diff (0 is perfect)'] + ['Time (smaller better)']

aggregate_results = pd.DataFrame(columns=headers)

# Assumes there is nothing else in the parent_dir_of_student_repos
for i, username in enumerate(students_to_try):
    print('Student: ' + str(i) + ': ' + username)
    student_folder = "{}/{}/".format(parent_dir_of_student_repos, username)

    shutil.copy('solution/matrix_search.h', student_folder + 'matrix_search.h')
    shutil.copy('catch_tests/catch.hpp', student_folder + 'catch.hpp')
    shutil.copy('catch_tests/test_catch.cpp', student_folder + 'test_catch.cpp')
    shutil.copy('catch_tests/catch_main.cpp', student_folder + 'catch_main.cpp')
    shutil.copy('catch_tests/test_input.txt', student_folder + 'test_input.txt')
    shutil.copy('mem_test/mem_test.cpp', student_folder + 'mem_test.cpp')
    shutil.copy('name_test/00name_test.cpp', student_folder + 'name_test.cpp')
    shutil.copy('solution/grade_input.txt', student_folder + 'grade_input.txt')
    shutil.copy('solution/grade_output.txt', student_folder + 'grade_output.txt')
    shutil.copy('autograder_pa01.py', student_folder + 'autograder_pa01.py')

    student_results = unit_tests(username, student_folder)
    student_results.append(get_mem_leaks())
    student_results.append(name_test(username, student_folder))
    student_results.append(main_diff(student_folder))
    student_results.append(time_tests(student_folder))
    store_student_data([headers, student_results], student_folder)
    aggregate_results.loc[len(aggregate_results)] = student_results

# aggregate_results.to_csv('aggregate_results.csv')
aggregate_results.to_pickle('aggregate_results.pkl')

# Cleanup
[os.remove(file) for file in glob('vgcore.*')]
#TODO glob for a.out and if any, remove all
if os.path.isfile('a.out'):
    os.remove('a.out')

# %% Re-import for any data processing. Compute weighted means of pass/fail:
df_reloaded = pd.read_pickle('aggregate_results.pkl')

# df_reloaded['Passes'] = [int(x) for x in df_reloaded['Tests passed (out of 56)']]
df_reloaded['Passes'] = [int(x) if (type(x) == str and x.isnumeric()) or type(x) == int
                         else 0 for x in df_reloaded['Tests passed (out of 56)']]

df_reloaded['Passes'] = df_reloaded['Passes'] / 4

df_reloaded['mem_leak_pts'] = np.where(df_reloaded['Bytes definitely lost (memory leak) (0 is perfect)'] == '0', 10, 0)

df_reloaded['Main_points'] = np.where(df_reloaded['Main diff (0 is perfect)'] == 0, 10, 0)

df_reloaded['mean_time'] = pd.to_numeric(df_reloaded['Time (smaller better)'], errors='coerce')
df_reloaded['mean_time'] = np.where(df_reloaded['Passes'] == 14, df_reloaded['mean_time'], np.nan)
df_reloaded['norm_time'] = (df_reloaded['mean_time'] - df_reloaded['mean_time'].min()) / (df_reloaded['mean_time'].max() - df_reloaded['mean_time'].min())
df_reloaded['Bonus'] = 5 - (5 * df_reloaded['norm_time'])
df_reloaded['Bonus'] = df_reloaded['Bonus'].fillna(0)

df_reloaded['Grand_avg'] = df_reloaded['mem_leak_pts'] + ((df_reloaded['Passes'] / 14) * 75) + df_reloaded['Bonus'] + df_reloaded['Main_points']

df_reloaded = df_reloaded.sort_index()

df_reloaded.to_csv('Grades.csv')

