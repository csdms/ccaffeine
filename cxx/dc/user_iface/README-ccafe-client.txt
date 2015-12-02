ccafe-client --name MyHostName [--file <filename>] [--type <client,interactive,gui,oneProcInteractive>] [--cafe-waitForGdbAttach] [--port][--ccafe-rc <rc file>]

  --type 
       More below: 
 
  --type  client        
       This is the "normal" position, it listens for a 
       connection, probably the GUI.  The backend right 
       now, always behaves as a client. 
 
  --type  interactive   
       Same as client but interacts in human readable form, 
       rather than the way the GUI would be expecting to 
       interact. 
 
  --type gui            
        default behavior, expecting to talk to a GUI. 
 
  --type oneProcInteractive    
        Expects that there will be only one 
        process and that it will be talking to a human 
        being. 

  --port <number>  
        Port number to listen on, default host name is localhost. 
 
  --name <host>  
        Host other than localhost to connect to. 
 
  --file <configFile>   
        A processor config file for the processor map, 
        not an initialization file. 
 
  --cafe-waitForGdbAttach 
        Spins until gdb attaches for debugging, probably not useful in 
        a parallel environment; every process would have to 
        be attached simultaneously.  
 
  --ccafe-rc <rc file> 
       Source the given file into ccaffeine. 
 
  --ccafe-remap-stdio\n"
       map stderr and stdout directly to the output files in batch mode.
       Useful only in batch mode with MPI when you are sure closing and
       reopening stdout/stderr is ok with your environment.

  --help 
       This message. 
