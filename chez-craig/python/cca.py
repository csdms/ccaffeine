import cca_siloon
from types import *

import sys
import re

NULL = (0, 0, (0,0,0))

def invoke_C(*args):
   return apply(cca_siloon.invoke_C, args)

def invoke_F(*args):
   return apply(cca_siloon.invoke_F, args)

def read(*args):
   return apply(cca_siloon.read, args)

def write(*args):
   return apply(cca_siloon.write, args)

def appendArgs(callArgs, *args):
   for arg in args[0]:
      if type(arg) == InstanceType:
         callArgs = callArgs + (arg.proxy,)
      else:
         callArgs = callArgs + (arg,)
   return callArgs

# ------------------------------------------------------------
# Enumerations
# ------------------------------------------------------------

false = 0
true = 1

__codecvt_ok = 0
__codecvt_partial = 1
__codecvt_error = 2
__codecvt_noconv = 3
__GCONV_OK = 0
__GCONV_NOCONV = 1
__GCONV_NODB = 2
__GCONV_NOMEM = 3
__GCONV_EMPTY_INPUT = 4
__GCONV_FULL_OUTPUT = 5
__GCONV_ILLEGAL_INPUT = 6
__GCONV_INCOMPLETE_INPUT = 7
__GCONV_ILLEGAL_DESCRIPTOR = 8
__GCONV_INTERNAL_ERROR = 9
__GCONV_IS_LAST = 1
__GCONV_IGNORE_ERRORS = 2
Unexpected = 0
Nonstandard = 1
PortNotDefined = 2
PortAlreadyDefined = 3
PortNotConnected = 4
PortNotInUse = 5
UsesPortNotReleased = 6
BadPortName = 7
BadPortType = 8
BadProperties = 9
BadPortInfo = 10
OutOfMemory = 11
NetworkError = 12
_PC_LINK_MAX = 0
_PC_MAX_CANON = 1
_PC_MAX_INPUT = 2
_PC_NAME_MAX = 3
_PC_PATH_MAX = 4
_PC_PIPE_BUF = 5
_PC_CHOWN_RESTRICTED = 6
_PC_NO_TRUNC = 7
_PC_VDISABLE = 8
_PC_SYNC_IO = 9
_PC_ASYNC_IO = 10
_PC_PRIO_IO = 11
_PC_SOCK_MAXBUF = 12
_PC_FILESIZEBITS = 13
_PC_REC_INCR_XFER_SIZE = 14
_PC_REC_MAX_XFER_SIZE = 15
_PC_REC_MIN_XFER_SIZE = 16
_PC_REC_XFER_ALIGN = 17
_SC_ARG_MAX = 0
_SC_CHILD_MAX = 1
_SC_CLK_TCK = 2
_SC_NGROUPS_MAX = 3
_SC_OPEN_MAX = 4
_SC_STREAM_MAX = 5
_SC_TZNAME_MAX = 6
_SC_JOB_CONTROL = 7
_SC_SAVED_IDS = 8
_SC_REALTIME_SIGNALS = 9
_SC_PRIORITY_SCHEDULING = 10
_SC_TIMERS = 11
_SC_ASYNCHRONOUS_IO = 12
_SC_PRIORITIZED_IO = 13
_SC_SYNCHRONIZED_IO = 14
_SC_FSYNC = 15
_SC_MAPPED_FILES = 16
_SC_MEMLOCK = 17
_SC_MEMLOCK_RANGE = 18
_SC_MEMORY_PROTECTION = 19
_SC_MESSAGE_PASSING = 20
_SC_SEMAPHORES = 21
_SC_SHARED_MEMORY_OBJECTS = 22
_SC_AIO_LISTIO_MAX = 23
_SC_AIO_MAX = 24
_SC_AIO_PRIO_DELTA_MAX = 25
_SC_DELAYTIMER_MAX = 26
_SC_MQ_OPEN_MAX = 27
_SC_MQ_PRIO_MAX = 28
_SC_VERSION = 29
_SC_PAGESIZE = 30
_SC_RTSIG_MAX = 31
_SC_SEM_NSEMS_MAX = 32
_SC_SEM_VALUE_MAX = 33
_SC_SIGQUEUE_MAX = 34
_SC_TIMER_MAX = 35
_SC_BC_BASE_MAX = 36
_SC_BC_DIM_MAX = 37
_SC_BC_SCALE_MAX = 38
_SC_BC_STRING_MAX = 39
_SC_COLL_WEIGHTS_MAX = 40
_SC_EQUIV_CLASS_MAX = 41
_SC_EXPR_NEST_MAX = 42
_SC_LINE_MAX = 43
_SC_RE_DUP_MAX = 44
_SC_CHARCLASS_NAME_MAX = 45
_SC_2_VERSION = 46
_SC_2_C_BIND = 47
_SC_2_C_DEV = 48
_SC_2_FORT_DEV = 49
_SC_2_FORT_RUN = 50
_SC_2_SW_DEV = 51
_SC_2_LOCALEDEF = 52
_SC_PII = 53
_SC_PII_XTI = 54
_SC_PII_SOCKET = 55
_SC_PII_INTERNET = 56
_SC_PII_OSI = 57
_SC_POLL = 58
_SC_SELECT = 59
_SC_UIO_MAXIOV = 60
_SC_IOV_MAX = 60
_SC_PII_INTERNET_STREAM = 61
_SC_PII_INTERNET_DGRAM = 62
_SC_PII_OSI_COTS = 63
_SC_PII_OSI_CLTS = 64
_SC_PII_OSI_M = 65
_SC_T_IOV_MAX = 66
_SC_THREADS = 67
_SC_THREAD_SAFE_FUNCTIONS = 68
_SC_GETGR_R_SIZE_MAX = 69
_SC_GETPW_R_SIZE_MAX = 70
_SC_LOGIN_NAME_MAX = 71
_SC_TTY_NAME_MAX = 72
_SC_THREAD_DESTRUCTOR_ITERATIONS = 73
_SC_THREAD_KEYS_MAX = 74
_SC_THREAD_STACK_MIN = 75
_SC_THREAD_THREADS_MAX = 76
_SC_THREAD_ATTR_STACKADDR = 77
_SC_THREAD_ATTR_STACKSIZE = 78
_SC_THREAD_PRIORITY_SCHEDULING = 79
_SC_THREAD_PRIO_INHERIT = 80
_SC_THREAD_PRIO_PROTECT = 81
_SC_THREAD_PROCESS_SHARED = 82
_SC_NPROCESSORS_CONF = 83
_SC_NPROCESSORS_ONLN = 84
_SC_PHYS_PAGES = 85
_SC_AVPHYS_PAGES = 86
_SC_ATEXIT_MAX = 87
_SC_PASS_MAX = 88
_SC_XOPEN_VERSION = 89
_SC_XOPEN_XCU_VERSION = 90
_SC_XOPEN_UNIX = 91
_SC_XOPEN_CRYPT = 92
_SC_XOPEN_ENH_I18N = 93
_SC_XOPEN_SHM = 94
_SC_2_CHAR_TERM = 95
_SC_2_C_VERSION = 96
_SC_2_UPE = 97
_SC_XOPEN_XPG2 = 98
_SC_XOPEN_XPG3 = 99
_SC_XOPEN_XPG4 = 100
_SC_CHAR_BIT = 101
_SC_CHAR_MAX = 102
_SC_CHAR_MIN = 103
_SC_INT_MAX = 104
_SC_INT_MIN = 105
_SC_LONG_BIT = 106
_SC_WORD_BIT = 107
_SC_MB_LEN_MAX = 108
_SC_NZERO = 109
_SC_SSIZE_MAX = 110
_SC_SCHAR_MAX = 111
_SC_SCHAR_MIN = 112
_SC_SHRT_MAX = 113
_SC_SHRT_MIN = 114
_SC_UCHAR_MAX = 115
_SC_UINT_MAX = 116
_SC_ULONG_MAX = 117
_SC_USHRT_MAX = 118
_SC_NL_ARGMAX = 119
_SC_NL_LANGMAX = 120
_SC_NL_MSGMAX = 121
_SC_NL_NMAX = 122
_SC_NL_SETMAX = 123
_SC_NL_TEXTMAX = 124
_SC_XBS5_ILP32_OFF32 = 125
_SC_XBS5_ILP32_OFFBIG = 126
_SC_XBS5_LP64_OFF64 = 127
_SC_XBS5_LPBIG_OFFBIG = 128
_SC_XOPEN_LEGACY = 129
_SC_XOPEN_REALTIME = 130
_SC_XOPEN_REALTIME_THREADS = 131
_SC_ADVISORY_INFO = 132
_SC_BARRIERS = 133
_SC_BASE = 134
_SC_C_LANG_SUPPORT = 135
_SC_C_LANG_SUPPORT_R = 136
_SC_CLOCK_SELECTION = 137
_SC_CPUTIME = 138
_SC_THREAD_CPUTIME = 139
_SC_DEVICE_IO = 140
_SC_DEVICE_SPECIFIC = 141
_SC_DEVICE_SPECIFIC_R = 142
_SC_FD_MGMT = 143
_SC_FIFO = 144
_SC_PIPE = 145
_SC_FILE_ATTRIBUTES = 146
_SC_FILE_LOCKING = 147
_SC_FILE_SYSTEM = 148
_SC_MONOTONIC_CLOCK = 149
_SC_MULTIPLE_PROCESS = 150
_SC_SINGLE_PROCESS = 151
_SC_NETWORKING = 152
_SC_READER_WRITER_LOCKS = 153
_SC_SPIN_LOCKS = 154
_SC_REGEXP = 155
_SC_REGEX_VERSION = 156
_SC_SHELL = 157
_SC_SIGNALS = 158
_SC_SPAWN = 159
_SC_SPORADIC_SERVER = 160
_SC_THREAD_SPORADIC_SERVER = 161
_SC_SYSTEM_DATABASE = 162
_SC_SYSTEM_DATABASE_R = 163
_SC_TIMEOUTS = 164
_SC_TYPED_MEMORY_OBJECTS = 165
_SC_USER_GROUPS = 166
_SC_USER_GROUPS_R = 167
_SC_2_PBS = 168
_SC_2_PBS_ACCOUNTING = 169
_SC_2_PBS_LOCATE = 170
_SC_2_PBS_MESSAGE = 171
_SC_2_PBS_TRACK = 172
_SC_SYMLOOP = 173
_SC_STREAMS = 174
_SC_2_PBS_CHECKPOINT = 175
_CS_PATH = 0
__GCONV_OK = 0
__GCONV_NOCONV = 1
__GCONV_NODB = 2
__GCONV_NOMEM = 3
__GCONV_EMPTY_INPUT = 4
__GCONV_FULL_OUTPUT = 5
__GCONV_ILLEGAL_INPUT = 6
__GCONV_INCOMPLETE_INPUT = 7
__GCONV_ILLEGAL_DESCRIPTOR = 8
__GCONV_INTERNAL_ERROR = 9
__GCONV_IS_LAST = 1
__GCONV_IGNORE_ERRORS = 2
round_indeterminate = 2147483647
round_toward_zero = 0
round_to_nearest = 1
round_toward_infinity = 2
round_toward_neg_infinity = 3
NO_INITIALIZATION = 0
denorm_indeterminate = 2147483647
denorm_absent = 0
denorm_present = 1
_ISupper = 256
_ISlower = 512
_ISalpha = 1024
_ISdigit = 2048
_ISxdigit = 4096
_ISspace = 8192
_ISprint = 16384
_ISgraph = 32768
_ISblank = 1
_IScntrl = 2
_ISpunct = 4
_ISalnum = 8
__ISwupper = 0
__ISwlower = 1
__ISwalpha = 2
__ISwdigit = 3
__ISwxdigit = 4
__ISwspace = 5
__ISwprint = 6
__ISwgraph = 7
__ISwblank = 8
__ISwcntrl = 9
__ISwpunct = 10
__ISwalnum = 11
_ISwupper = 16777216
_ISwlower = 33554432
_ISwalpha = 67108864
_ISwdigit = 134217728
_ISwxdigit = 268435456
_ISwspace = 536870912
_ISwprint = 1073741824
_ISwgraph = 2147483647
_ISwblank = 65536
_ISwcntrl = 131072
_ISwpunct = 262144
_ISwalnum = 524288
__GCONV_OK = 0
__GCONV_NOCONV = 1
__GCONV_NODB = 2
__GCONV_NOMEM = 3
__GCONV_EMPTY_INPUT = 4
__GCONV_FULL_OUTPUT = 5
__GCONV_ILLEGAL_INPUT = 6
__GCONV_INCOMPLETE_INPUT = 7
__GCONV_ILLEGAL_DESCRIPTOR = 8
__GCONV_INTERNAL_ERROR = 9
__GCONV_IS_LAST = 1
__GCONV_IGNORE_ERRORS = 2

# ------------------------------------------------------------
# C++ Functions
# ------------------------------------------------------------

def BuilderService_Cast_(*args):
  cmd = 'gov::cca::BuilderService *BuilderService_Cast(gov::cca::Port *)'
  return apply(invoke_C, appendArgs((cmd,), args))


# ------------------------------------------------------------
# Classes
# ------------------------------------------------------------

# ------------------------------------------------------------
# Class CcaffeineAbstractFramework
def CcaffeineAbstractFramework(*args):
  cmd = 'CcaffeineAbstractFramework &CcaffeineAbstractFramework::CcaffeineAbstractFramework(gov::cca::StringList *)'
  proxy = apply(invoke_C, appendArgs((cmd,), args))
  return CcaffeineAbstractFramework_SProxy_(proxy)

class CcaffeineAbstractFramework_SProxy_:
  def __init__(self, proxy):
    self.proxy = proxy

  def getBootstrapServices(self, *args):
    cmd = 'gov::cca::Services *CcaffeineAbstractFramework::getBootstrapServices(char *, char *, char **)'
    return apply(invoke_C, appendArgs((cmd, self.proxy), args))

  def releaseBootstrapServices(self, *args):
    cmd = 'void CcaffeineAbstractFramework::releaseBootstrapServices(gov::cca::Services *)'
    return apply(invoke_C, appendArgs((cmd, self.proxy), args))

# ------------------------------------------------------------
# Class StringList
class StringList_SProxy_:
  def __init__(self, proxy):
    self.proxy = proxy

  def get(self, *args):
    cmd = 'char *gov::cca::StringList::get(int)'
    return apply(invoke_C, (cmd, self.proxy) + args)

  def getSize(self, *args):
    cmd = 'int gov::cca::StringList::getSize()'
    return apply(invoke_C, (cmd, self.proxy) + args)

# ------------------------------------------------------------
# Class ComponentID
class ComponentID_SProxy_:
  def __init__(self, proxy):
    self.proxy = proxy

  def toString(self, *args):
    cmd = 'char *gov::cca::ComponentID::toString()'
    return apply(invoke_C, (cmd, self.proxy) + args)

# ------------------------------------------------------------
# Class Services
class Services_SProxy_:
  def __init__(self, proxy):
    self.proxy = proxy

  def createPortInfo(self, *args):
    cmd = 'gov::cca::PortInfo *gov::cca::Services::createPortInfo(char *, char *, char **)'
    return apply(invoke_C, appendArgs((cmd, self.proxy), args))

  def getPort(self, *args):
    cmd = 'gov::cca::Port *gov::cca::Services::getPort(char *)'
    return apply(invoke_C, appendArgs((cmd, self.proxy), args))

  def registerUsesPort(self, *args):
    cmd = 'int gov::cca::Services::registerUsesPort(gov::cca::PortInfo *)'
    return apply(invoke_C, appendArgs((cmd, self.proxy), args))

# ------------------------------------------------------------
# Class StringVector
class StringVector_SProxy_:
  def __init__(self, proxy):
    self.proxy = proxy

  def get(self, *args):
    cmd = 'char *jcpp::StringVector::get(int)'
    return apply(invoke_C, (cmd, self.proxy) + args)

# ------------------------------------------------------------
# Class BuilderService
class BuilderService_SProxy_:
  def __init__(self, proxy):
    self.proxy = proxy

  def getComponentClasses(self, *args):
    cmd = 'gov::cca::StringList *gov::cca::BuilderService::getComponentClasses()'
    return apply(invoke_C, (cmd, self.proxy) + args)

  def createInstance(self, *args):
    cmd = 'gov::cca::ComponentID *gov::cca::BuilderService::createInstance(char *, char *)'
    return apply(invoke_C, appendArgs((cmd, self.proxy), args))

  def getComponentID(self, *args):
    cmd = 'gov::cca::ComponentID *gov::cca::BuilderService::getComponentID(char *)'
    return apply(invoke_C, appendArgs((cmd, self.proxy), args))

  def getComponentInstanceNames(self, *args):
    cmd = 'gov::cca::StringList *gov::cca::BuilderService::getComponentInstanceNames()'
    return apply(invoke_C, (cmd, self.proxy) + args)

  def getProvidesPortStrings(self, *args):
    cmd = 'gov::cca::StringList *gov::cca::BuilderService::getProvidesPortStrings(gov::cca::ComponentID *)'
    return apply(invoke_C, appendArgs((cmd, self.proxy), args))

  def getUsesPortStrings(self, *args):
    cmd = 'gov::cca::StringList *gov::cca::BuilderService::getUsesPortStrings(gov::cca::ComponentID *)'
    return apply(invoke_C, appendArgs((cmd, self.proxy), args))

  def connect(self, *args):
    cmd = 'void gov::cca::BuilderService::connect(gov::cca::ComponentID *, char *, gov::cca::ComponentID *, char *, char *)'
    return apply(invoke_C, appendArgs((cmd, self.proxy), args))

  def go(self, *args):
    cmd = 'void gov::cca::BuilderService::go(gov::cca::ComponentID *, char *)'
    return apply(invoke_C, appendArgs((cmd, self.proxy), args))

# ------------------------------------------------------------
# Class ComponentFactory
def getPallet(*args):  ### static method
  cmd = 'jcpp::StringVector *ComponentFactory::getPallet()'
  return apply(invoke_C, appendArgs((cmd,), args))

def setComponentPath(*args):  ### static method
  cmd = 'void ComponentFactory::setComponentPath(char **)'
  return apply(invoke_C, appendArgs((cmd,), args))

def getComponentPath(*args):  ### static method
  cmd = 'char **ComponentFactory::getComponentPath()'
  return apply(invoke_C, appendArgs((cmd,), args))

def searchComponentPath(*args):  ### static method
  cmd = 'int ComponentFactory::searchComponentPath()'
  return apply(invoke_C, appendArgs((cmd,), args))

def getLoadedComponents(*args):  ### static method
  cmd = 'char **ComponentFactory::getLoadedComponents()'
  return apply(invoke_C, appendArgs((cmd,), args))

def getUnloadedComponents(*args):  ### static method
  cmd = 'char **ComponentFactory::getUnloadedComponents()'
  return apply(invoke_C, appendArgs((cmd,), args))

def getLoadedLibraries(*args):  ### static method
  cmd = 'char **ComponentFactory::getLoadedLibraries()'
  return apply(invoke_C, appendArgs((cmd,), args))

def loadPallet(*args):  ### static method
  cmd = 'int ComponentFactory::loadPallet(char *, char, char)'
  return apply(invoke_C, appendArgs((cmd,), args))

class ComponentFactory_SProxy_:
  def __init__(self, proxy):
    self.proxy = proxy

  def getPallet(self, *args):
    cmd = 'jcpp::StringVector *ComponentFactory::getPallet()'
    return apply(invoke_C, (cmd,) + args)

  def setComponentPath(self, *args):
    cmd = 'void ComponentFactory::setComponentPath(char **)'
    return apply(invoke_C, appendArgs((cmd,), args))

  def getComponentPath(self, *args):
    cmd = 'char **ComponentFactory::getComponentPath()'
    return apply(invoke_C, (cmd,) + args)

  def searchComponentPath(self, *args):
    cmd = 'int ComponentFactory::searchComponentPath()'
    return apply(invoke_C, (cmd,) + args)

  def getLoadedComponents(self, *args):
    cmd = 'char **ComponentFactory::getLoadedComponents()'
    return apply(invoke_C, (cmd,) + args)

  def getUnloadedComponents(self, *args):
    cmd = 'char **ComponentFactory::getUnloadedComponents()'
    return apply(invoke_C, (cmd,) + args)

  def getLoadedLibraries(self, *args):
    cmd = 'char **ComponentFactory::getLoadedLibraries()'
    return apply(invoke_C, (cmd,) + args)

  def loadPallet(self, *args):
    cmd = 'int ComponentFactory::loadPallet(char *, char, char)'
    return apply(invoke_C, appendArgs((cmd,), args))

# ------------------------------------------------------------
# Class ConnectionFramework
class ConnectionFramework_SProxy_:
  def __init__(self, proxy):
    self.proxy = proxy

  def getComponentClasses(self, *args):
    cmd = 'jcpp::StringVector *ConnectionFramework::getComponentClasses()'
    return apply(invoke_C, (cmd, self.proxy) + args)

# ------------------------------------------------------------
# Class BuilderModel
class BuilderModel_SProxy_:
  def __init__(self, proxy):
    self.proxy = proxy

  def getPallet(self, *args):
    cmd = 'char **BuilderModel::getPallet(int &)'
    return apply(invoke_C, appendArgs((cmd, self.proxy), args))

# ------------------------------------------------------------
# Class DefaultStringList
def DefaultStringList(*args):
  cmd = 'DefaultStringList &DefaultStringList::DefaultStringList()'
  proxy = apply(invoke_C, (cmd,) + args)
  return DefaultStringList_SProxy_(proxy)

def DefaultStringList_rDefaultStringList(*args):
  cmd = 'DefaultStringList &DefaultStringList::DefaultStringList(const DefaultStringList &)'
  proxy = apply(invoke_C, appendArgs((cmd,), args))
  return DefaultStringList_SProxy_(proxy)

class DefaultStringList_SProxy_:
  def __init__(self, proxy):
    self.proxy = proxy

  def get(self, *args):
    cmd = 'char *DefaultStringList::get(int)'
    return apply(invoke_C, (cmd, self.proxy) + args)

  def getSize(self, *args):
    cmd = 'int DefaultStringList::getSize()'
    return apply(invoke_C, (cmd, self.proxy) + args)

  def size(self, *args):
    cmd = 'int DefaultStringList::size()'
    return apply(invoke_C, (cmd, self.proxy) + args)

  def append(self, *args):
    cmd = 'void DefaultStringList::append(char *)'
    return apply(invoke_C, appendArgs((cmd, self.proxy), args))

  def clear(self, *args):
    cmd = 'void DefaultStringList::clear()'
    return apply(invoke_C, (cmd, self.proxy) + args)

  def dump(self, *args):
    cmd = 'void DefaultStringList::dump()'
    return apply(invoke_C, (cmd, self.proxy) + args)

  def op_equals(self, *args):
    cmd = 'DefaultStringList &DefaultStringList::operator=(const DefaultStringList &)'
    return apply(invoke_C, appendArgs((cmd, self.proxy), args))

# ------------------------------------------------------------
# Class VectorStringList
def VectorStringList(*args):
  cmd = 'VectorStringList &VectorStringList::VectorStringList()'
  proxy = apply(invoke_C, (cmd,) + args)
  return VectorStringList_SProxy_(proxy)

def VectorStringList_pC(*args):
  cmd = 'VectorStringList &VectorStringList::VectorStringList(char **)'
  proxy = apply(invoke_C, appendArgs((cmd,), args))
  return VectorStringList_SProxy_(proxy)

class VectorStringList_SProxy_:
  def __init__(self, proxy):
    self.proxy = proxy

  def argvList(self, *args):
    cmd = 'char **VectorStringList::argvList()'
    return apply(invoke_C, (cmd, self.proxy) + args)

  def get(self, *args):
    cmd = 'char *VectorStringList::get(int)'
    return apply(invoke_C, (cmd, self.proxy) + args)

  def getSize(self, *args):
    cmd = 'int VectorStringList::getSize()'
    return apply(invoke_C, (cmd, self.proxy) + args)

  def size(self, *args):
    cmd = 'int VectorStringList::size()'
    return apply(invoke_C, (cmd, self.proxy) + args)

  def append(self, *args):
    cmd = 'void VectorStringList::append(char *)'
    return apply(invoke_C, appendArgs((cmd, self.proxy), args))

  def clear(self, *args):
    cmd = 'void VectorStringList::clear()'
    return apply(invoke_C, (cmd, self.proxy) + args)

  def dump(self, *args):
    cmd = 'void VectorStringList::dump()'
    return apply(invoke_C, (cmd, self.proxy) + args)


# ------------------------------------------------------------
# Fortran Functions
# ------------------------------------------------------------


