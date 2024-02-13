============
File Flipper
============

A very basic threaded application that reads in a given file of strings (default is input.txt) and outputs a file
containing those same strings reversed (output.txt).

.. code-block:: bash

   usage: file_flipper [input_file_path] [number_of_threads]

Sample input and expected output files can be found in the :code:`tests` directory.

This application was designed with the assumption that the number of strings in the input file was a manageable number
for a computer to hold in memory at one time. If this is not the case, the design can be modified by having the workers
read individual or groups of strings from the input file within a lock, make the reversing modifications, and then
write to the output file within a lock.
