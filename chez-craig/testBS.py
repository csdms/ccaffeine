#! /usr/bin/python

##################################################################
##################################################################
### Please set CCA_ROOT to the proper path in line below
###
CCA_ROOT = '/home/rasmussn/dccafe'

import sys
sys.path = [CCA_ROOT+'/chez-craig/python',] + sys.path

from siloon_cca import *

lst = VectorStringList()
fwk = CcaffeineAbstractFramework(lst)

#
# Add return of Service object (and way to choose Service rather than pointer)
#

svc = fwk.getBootstrapServices("test0", "testAbstractFwk", NULL)
svc = Services_Cast(svc)

info = svc.createPortInfo("myBS", "gov.cca.BuilderService", NULL)

err = svc.registerUsesPort(info)

bs = svc.getPort("myBS")
bs = BuilderService_Cast(bs)

lst = bs.getComponentClasses()
lst = StringList_Cast(lst)

print
print "RUNNING PYTHON TESTS............................"
print

size = lst.getSize()
print "there are", size, "available classes:"
for i in range(size):
  print "  ", lst.get(i)
print

pathlist = VectorStringList()
pathlist.append('/home/rasmussn/dccafe/cxx/dc/component')
paths = pathlist.argvList()
setComponentPath(paths)
paths = getComponentPath()
lst = VectorStringList_pC(paths)
for i in range(lst.getSize()):
  print "path = ", lst.get(i)
print

numCmpt = searchComponentPath()
print "Number of components found on that path = ", numCmpt
comps = getUnloadedComponents()
lst = VectorStringList_pC(comps)
for i in range(lst.getSize()):
  print "  Component: ", lst.get(i)
print

loadPallet("PrinterComponent", true, true)
print "Here is the result of getComponentClasses() I don't think it ever returns anything:"
lst = bs.getComponentClasses()
lst = StringList_SProxy_(lst)
for i in range(lst.getSize()):
  print "   ", lst.get(i)
print

printer = bs.createInstance("PrinterComponent", "print0")
printer = ComponentID_SProxy_(printer)
print "Instantiated ", printer.toString()
starter = ComponentID_SProxy_(bs.createInstance("StarterComponent", "start0"))
print "Instantiated ", starter.toString()

bs.connect(starter, "out0", printer, "printer_port", "aConnection")
bs.go(starter, "go_port")

print
print "SUCCESSFULLY FINISHED TESTS............................"
print

