extern "C" {
/** A global variable that must be set to a nonzero value by gdb.*/
int gdbAttached = 0;

/** Call this to wait for the user to attach to this process. */
void gdbWaitForAttach(void){
  while(1) {
    if(gdbAttached != 0) break; /** type: "set gdbAttached=1<CR>" in gdb*/
  }
}
};
