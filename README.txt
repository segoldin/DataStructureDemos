Data Structure Demos
--------------------
Last update: 3 February 2020

This repository is a collection of demonstration programs in standard Gnu C that I have developed over many years teaching introductory data structures to undergraduate students in Computer Engineering at King Mongkut's University of Technology Thonburi, Bangkok, Thailand. 

I am making it open source in the hope that these programs will be useful for other instructors. When I began teaching this course, I had serious difficulty finding clear, readable sample code written in C. My objective is to help fill this gap.

The programs are designed to be demonstrated in the classroom, used as the basis of hands-on practice exercises, or both.

The repository is organized based on data structure category and/or main lecture topic. Since C often uses dynamically allocated elements and pointers to build flexible data structures, the repository includes one extended example intended for pointer review.

I have tried to make these demo programs clear and readable, sometimes at the expense of efficiency. These programs are definitely not intended for real world applications. My goal is to illustrate important concepts and to show students the internals of data structures that are often provided "out of the box" by other programming languages. I want students to see what goes on behind the "magic" in Java, Python and similar "modern" languages.

The collection of demos makes extensive use of the concept of Abstract Data Types (ADT) - the notion that a data type/structure can be defined by its behavior or interface, then implemented in various ways. Files with the name "abstractXXX.h" define the ADT behavior as a set of function declarations. I then provide one or more C source files that implement the ADT. 

These programs were developed under Linux and should be compiled in a compatible environment (e.g. CodeBlocks or MinGW in Windows, XCode on OSX).

I welcome your comments and suggestions. If you find any problems in this code please contact me at seg@goldin-rudahl.com.

Enjoy!
