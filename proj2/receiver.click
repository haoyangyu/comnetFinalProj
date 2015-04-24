define($dev veth4)
FromDevice($dev) -> Print(Received, MAXLENGTH -1) -> Discard;
