# CSE2431KernelMod

Introduction
--------------------------------------
A simple white hat keylogger kernel module that logs numeric linux keycodes and looks for credit card numbers to alert the user when any card number has been entered on their machine.

Kernel Side
----------------------------------------------------
This repository houses the actual kernel module code stored in keylogger.c, which is inserted into the kernel by the user to record the key strokes in the syslog file in /var/log/. To compile this file, just run the Makefile with the keylogger.c file in the same directory. The use sudo insmod keylogger.ko to insert the kernel object into the linux kernel. Use lsmod to ensure the module has been loaded, and type away!

The basics concept of this keylogger is that the module subscribes to the notifier block of the keyboard following the observer design pattern. When paired with the reciever method, whenever the keyboard gets a key press it will broad cast to all subscried to it a struct that holds the linux keycode for what was pressed and whether it was pressed down or released or if shift was used.

User Side
------------------------------------------------------------------------------------------

The real work of this code is done within the cardChecker.c file. This file contains a simple tail code that reads the last 100 lines of the syslog file every 15 seconds. Only terminated with ctrl+c in theterminal, or closing the terminal. Within this tail code is a method that is used to convert linux keycodes for the numbers to their integer forms. Also a method containing Luhn's algorithm is provided to check through the array of possible card numbers and determine if one has been entered. If one is found by this code, it will ask the user if they meant to enter it in, if they answer yes it will continue looking. If they answer no, it will prompt the user if they would like to shutdown the computer or not to prevent their card number from being submitted, if the respond no, the algorithm will continue.

Contents
-----------------
- keylogger.c: Kernel module to log keystrokes

- Makefile: Used to compile the kernel module

- keycode.c: Standalone copy of the keyCodeToInt function for unit testing of translating linux keycodes to integers, returns a integer from 0-9 if the keycode, or tells you the keycode is not a number.

- luhnAlg.c: Standalone copy of the luhn for unit testing of verifying if an array of 16 digits translates to a vild credit card number.

- tail.c: Standalone tail function that reads the last n lines from the syslog file, and then cuts those lines up into keycode tokens and prints to the terminal.

- cardChecker.c: The complete function to read from the syslog file and look for credit cards as described above.

Instructions
-------------------------------------

* To run the keylogger:
  
  - Make sure that Makefile and keylogger.c are in the same directory.

  - Run the make file by calling make in the terminal pointed at the directory.

  - Once the make command finishes, call sudo insmod keylogger.ko to load it into the kernel, and us sudo lsmod to check that keylogger is in the kernel, and use dmesg for quick checking what is written to the syslog
  
* To run the cardChecker:

  - Open a terminal and navigate to the directory that houses the cardChecker.c file.
  
  - Use gcc -o cardChecker cardChecker.c to compile the code.
  
  - To run the code call sudo ./cardChecker
  
* To run the keycode seperate:

  - Open a terminal and navigate to the directory that houses the keycode.c file.
  
  - Use gcc -o keycode keycode.c to compile the code.
  
  - To run the code call ./keycode code where code is the command line argument for the linux keycode
  
  * To run Luhn's algorithm seperatly:
  
   - Open a terminal and navigate to the directory that houses the luhnAlg.c file.
  
  - Use gcc -o luhnalg luhnAlg.c to compile the code.
  
  - To run the code call ./luhnAlg, there are some preloaded card arrays provided in the code that may be uncommented to run, recompile after changing
  
* To run the tail code seperate:

  - Open a terminal and navigate to the directory that houses the tail.c file.
  
  - Use gcc -o keycode tail.c to compile the code.
  
  - To run the code call ./tail 
