from cca import *

def Services_Cast(ptr):
  return Services_SProxy_(ptr)

def BuilderService_Cast(ptr):
  return BuilderService_SProxy_(BuilderService_Cast_(ptr))

def StringList_Cast(ptr):
  return StringList_SProxy_(ptr)

def ComponentID_Cast(ptr):
  return ComponentID_SProxy_(ptr)

