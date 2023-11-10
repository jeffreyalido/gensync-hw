# EC500: Software At Scale Project: Contributing to a large open-source project
This HW project involved getting familiar with an existing open-source project and contributing meaningful and useful changes.The `issueStupidSync_v0` branch addresses the following issue:

# Issue description
Implement a new synchronization method (as a subclass of SyncMethod) that (uniformly, possibly with replacement) randomly sends its elements, one at a time, from the "client" to the "server" until the "server" sees n elements (in a row) that it already has, at which point synchronization ends.
For example, if the client has set {1,2,3,4,5} and the server has {2,4,6,8,10,12} and the parameter n is 2, then you could see the following exchange:

The client sends 1 to the server.  The server does not have 1.
The client sends 4 to the server.  The server does have 4.
The client sends 1 to the server.  The server does not have 1.
The client sends 2 to the server.  The server does have 2.
The client sends 4 to the server.  The server does have 4.

The synchronization stops, because the server got two elements in a row ( i.e., 2, 4) that it already had.

# Information
Completed in November 2023 in EC500: Software at Scale taught by Ari Trachtenberg.
