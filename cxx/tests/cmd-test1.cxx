#include "util/IO.h"
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "cmd/CmdContext.h"
#include "cmd/CmdAction.h"
#include "cmd/CmdActionExit.h"

#include "util/freefree.h"


int main(int argc, char **argv) {
	CmdActionExit *cae;
	char **nl;
	int len;
	cae = new CmdActionExit();
	printf("%s\n",cae->help());
	printf("%s\n",cae->argtype());
	nl = cae->names(len);
	for (int i=0; i < len; i++) {
		printf("%s\n",nl[i]);
	}
	delete cae;
	return 0;
}
