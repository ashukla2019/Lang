------------------------------------Python: How to List Files in Directory:
How to List Files in a Python Directory
  Use os.listdir() to print all files.
  Use os.walk() to access files deeper into a decision tree.
  Use the glob module to search by regular expression.
  Use the pathlib module to generate all path file names.
  Use the os.scandir() function to return a generator. 

1. Use os.listdir() to Print All Files:
  os.listdir(myPath)
  import os
  files = [f for f in os.listdir() if os.path.isdir(f)]
  files = [f for f in os.listdir() if os.path.isfile(f)]

2. Use os.walk() to Access Files Deeper in a Directory Tree :
  You can also list files in a Python directory using walk(), another method from the OS module.
  As its name implies, it can “walk” through a directory tree layer by layer. When you call the os.walk() method, 
  it will return a generator. Every time you call the next() method to generate its next value, it will go one layer deeper. 
  The result will be a tuple that includes three items: (dirpath, dirnames, filenames).
   from os import walk
   f = []
    layer = 1
    w = walk("/Users/yang")
    for (dirpath, dirnames, filenames) in w:
        if layer == 2:
            f.extend(dirnames)
            break
        layer += 1

3. Use Glob Module to Search by Regular Expressions:
  Person searching a file cabinet.
Image: Shutterstock / Built In
Brand Studio Logo
UPDATED BY
Brennan Whitfield | Sep 09, 2024
File and directory-related operations are basic skills for software engineers. This isn’t just copying one file into another folder on your Windows File Explorer, rather it’s understanding how to conduct automatic batch operations using software functions.

What Is a Directory in Python?
A directory is a digital structure used to store and organize files on a computer. Python modules can be used to manipulate computer directories and the files they store.

This is a big topic. Today we will dive into one specific problem: How to list all file names under a specific directory. In Python, a directory contains a group of files and subdirectories. 

I’ll introduce five ways to list and access files in a Python directory. Each of these methods are used in different scenarios.

How to List Files in a Python Directory
Use os.listdir() to print all files.
Use os.walk() to access files deeper into a decision tree.
Use the glob module to search by regular expression.
Use the pathlib module to generate all path file names.
Use the os.scandir() function to return a generator. 
More on Python
Merging Lists in Python

 

How to List Files in a Python Directory
1. Use os.listdir() to Print All Files
One way to list files in a Python directory is to use the os.listdir() method, which is from Python’s OS module:

>>> import os
>>> os.listdir()
The above code will print the names of all files and directories under the current path. If you would like to print the results based on another path, just give the os.listdir() function an argument:

>>> os.listdir(myPath)
If you only want to print all files, the os.path.isfile() will give you a hand:

>>> import os
>>> files = [f for f in os.listdir() if os.path.isfile(f)]
For directories, there is also a function named os.path.isdir():

import os
files = [f for f in os.listdir() if os.path.isdir(f)]
It’s simple and useful, but what if it returns a large list? Or what if you only need a specific type of file? Fortunately, Python provides you with plenty of options for more complex scenarios. 

2. Use os.walk() to Access Files Deeper in a Directory Tree 
You can also list files in a Python directory using walk(), another method from the OS module.

As its name implies, it can “walk” through a directory tree layer by layer. When you call the os.walk() method, it will return a generator. Every time you call the next() method to generate its next value, it will go one layer deeper. The result will be a tuple that includes three items: (dirpath, dirnames, filenames).

For example, if you want to get the names of all folders in the second layer, your code will be as follows:

from os import walk

f = []
layer = 1
w = walk("/Users/yang")
for (dirpath, dirnames, filenames) in w:
    if layer == 2:
        f.extend(dirnames)
        break
    layer += 1
3. Use Glob Module to Search by Regular Expressions
Instead of retrieving the names of all files, sometimes you might want to get the names of a specific type of file. Since the glob module is able to add regular expressions in a search, it will be your friend for this type of operation:

>>> import glob
>>> glob.glob("/sys/*.log")

