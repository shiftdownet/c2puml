

void EntryPoint ( void ) {
    test2_globalCall();
    localCall();
}

static void localCall(void){
    int i = 0;
    i *= 2;
}