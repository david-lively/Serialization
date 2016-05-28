{
    Type: State;
    Id: 0;
    OnDone: { goto 1 }
    Next: 1;
}

{
    Type: WaitState;
    Id: 1;
    WaitForSeconds: 5.3;

    OnDone: { goto 2 }
}