
#include "util/IO.h"
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "cmd/CmdContext.h"
#include "cmd/CmdAction.h"
#include "cmd/CmdActionExit.h"
#include "cmd/CmdActionHelp.h"

#include "util/freefree.h"

int main(int argc, char **argv) {
        CmdActionHelp *cae;
        char **nl;
        int len;
        cae = new CmdActionHelp();
        printf("%s\n",cae->help());
        printf("%s\n",cae->argtype());
        nl = cae->names(len);
        for (int i=0; i < len; i++) {
                printf("%s\n",nl[i]);
        }
        delete cae;
        return 0;
}

