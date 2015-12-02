#!/usr/bin/python
import ccaffeine.AbstractFramework # load the framework
a = ccaffeine.AbstractFramework.AbstractFramework() # create it
# initialize telling the framework what components we will use and
# where they are located.
args = "--path /home/rob/cca/lib/components  --load ccafe0.PrinterComponent"
a.initialize(args)
# We create ourselves as a component in the framework by
# getting gov.cca.Services
svc = a.getServices("uber", "UberComponent", a.createTypeMap());
myid = svc.getComponentID(); # this is our ComponentID
# We wish to act as a framework, get gov.cca.BuilderServices port
svc.registerUsesPort("bs", "gov.cca.BuilderService", svc.createTypeMap())
port = svc.getPort("bs")
import gov.cca.ports.BuilderService
bs = gov.cca.ports.BuilderService.BuilderService(port) # a Babel type cast
# create a ccafe0.PrinterComponent, we receive an opaque ComponentID
# This component exports a ccafe0.StringConsumerPort instance name of "string"
cid = bs.createInstance("p", "ccafe0.PrinterComponent", svc.createTypeMap())
# register for that port
svc.registerUsesPort("out", "ccafe0.StringConsumerPort", svc.createTypeMap())
# connect ourselves to the component
bs.connect(myid, "out", cid, "string")
# get the port
port = svc.getPort("out");
out = ccafe0.StringConsumerPort(port);
# use it
out.setString("Hello CCA World");


