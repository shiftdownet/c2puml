

void test2_globalCall ( void ) {
    localCall();
}

static void localCall(void){
    int x = 0;
    x *= 2;
}