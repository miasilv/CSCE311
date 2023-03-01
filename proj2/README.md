# **IPC Project:**
_A Unix Domain Socket that sends the name of a desired CSV file along with search terms to the server. The server finds all lines containing all or part of the terms and returns each one using the Domain Socket. The client formats the lines and prints each one, line-by-line_
<br/><br/>

### **unix_domain_socket.h and unix_domain_socket.cc:** 
The Unix Domain Socket builds a socket that will be utilized by the server and client.
<br/><br/>

### **text_server.h, text_server.cc, and server_main:** 
The server will build a Unix Domain Socket using the provided server name and begin listening for client connections. Once a client connection is accepted, the server acquires the name and path of the text file to parse through, the terms to search for, and the boolean opperator to use. The server will then parse through the file to find all valid lines, differing depending on whether the opperator is ``+`` or ``x``. The server then returns the valid lines and waits for another client.
#### **Usage:** ####
Type ``make text-server`` into a terminal and then type ``./text-server socketName`` with whatever socket name you would like.
<br/><br/>

### **text_client.h, text_client.cc, and client_main** 
The client takes in a single command-line argument followed by:
1. The name of the Unix Domain Socket hosted by the server
2. The name and path of the text file, relative to the root, to be searched
3. The search expression for which the file will be parsed. <br/>_Note_: the client cannot handle mixed boolean operations, e.g. ``term1 + term2 x term3``

The client then sends the data to the server using the provided Unix Domain Socket. The server will return all the lines containing the provided terms found in the csv file provided. The client prints out these lines, how many bytes it recieved, and then terminates. The client is a one time use.

#### **Usage:** ####
Type ``make text-client`` into a terminal and then type this format in to the terminal:
- ``./text-client socketName ./dat/documentName.csv term1``
- ``./text-client socketName ./dat/documentName.csv term1 + term2``
- ``./text-client socketName ./dat/documentName.csv term1 x term2``
- ``./text-client socketName ./dat/documentName.csv term1 x term2 x term3``

socketName, documentName, and termN would be whatever lables you would like.