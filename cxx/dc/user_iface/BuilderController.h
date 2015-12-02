#ifndef BuilderController_h_seen
#define BuilderController_h_seen


/** A command line controller of the Model-View-Controller pattern for
    the builder.  This reads from input and instructs the BuilderModel
    to perform actions and the BuilderView to printout information.  */
class BuilderController {

public:

  virtual ~BuilderController(){}

  /** Begin recieving input events from the user. */
  virtual int parse()  =0;

  /** Add an action to the command stream of the controller.  Right
      now the Benware does not support removal. */
  virtual void addAction(CmdAction* action) = 0;

};
#endif // BuilderController.h
